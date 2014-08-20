#!/usr/bin/env python3
# encoding: utf-8
#
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
#   Copyright 2014, Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   Copyright 2014, Philip Müller <philm@manjaro.org>
#   Copyright 2014, Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
#
#   Calamares is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Calamares is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Calamares. If not, see <http://www.gnu.org/licenses/>.

import os
import subprocess

from libcalamares import *

class PreUnpackEntry:
    __slots__= ['source', 'sourcefs', 'destination']

    def __init__(self, source, sourcefs, destination):
        self.source = source
        self.sourcefs = sourcefs
        self.destination = destination


class PreUnpackOperation:

    def __init__(self, entries):
        self.entries = entries

    def run(self):
        for entry in self.entries:
            self.mount_image(entry)
        return None

    def mount_image(self, entry):
        os.makedirs(entry.destination)
        subprocess.check_call(["mount",
                               entry.source,
                               entry.destination,
                               "-t",
                               entry.sourcefs,
                               "-o", "loop"])


def run():
    # from globalstorage: rootMountPoint
    # from job.configuration:
    # the path to where to mount the source image(s) for copying
    # an ordered list of unpack mappings for image file <-> target dir relative
    # to rootMountPoint, e.g.:
    # configuration:
    #     preunpack:
    #         - source: "/path/to/filesystem.img"
    #           sourcefs: "ext4"
    #           destination: "/path/to/mountpoint"
    #         - source: "/path/to/another/filesystem.sqfs"
    #           sourcefs: "squashfs"
    #           destination: "/path/to/another/mountpoint"

    PATH_PROCFS = '/proc/filesystems'

    root_mount_point = globalstorage.value("rootMountPoint")
    if not root_mount_point:
        return ("No mount point for root partition in globalstorage",
                "globalstorage does not contain a \"rootMountPoint\" key, "
                "doing nothing")
    if not os.path.exists(root_mount_point):
        return ("Bad mount point for root partition in globalstorage",
                "globalstorage[\"rootMountPoint\"] is \"{}\", which does not "
                "exist, doing nothing".format(root_mount_point))
    preunpack = list()

    for entry in job.configuration["preunpack"]:
        source = os.path.abspath(entry["source"])

        sourcefs = entry["sourcefs"]

        # Get supported filesystems
        fs_is_supported = False

        if os.path.isfile(PATH_PROCFS) and os.access(PATH_PROCFS, os.R_OK):
            procfile = open(PATH_PROCFS, 'r')
            filesystems = procfile.read()
            procfile.close

            filesystems = filesystems.replace("nodev", "")
            filesystems = filesystems.replace("\t", "")
            filesystems = filesystems.splitlines()

            # Check if the source filesystem is supported
            for fs in filesystems:
                if fs == sourcefs:
                    fs_is_supported = True

        if fs_is_supported == False:
            return "Bad filesystem", "sourcefs=\"{}\"".format(sourcefs)

        destination = os.path.abspath(root_mount_point + entry["destination"])

        if not os.path.isfile(source):
            return ("Bad source", "source=\"{}\"".format(source))
        if not os.path.isdir(destination):
            return ("Bad destination",
                    "destination=\"{}\"".format(destination))

        preunpack.append(PreUnpackEntry(source, sourcefs, destination))

    preunpackop = PreUnpackOperation(unpack)
    return preunpackop.run()
