#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
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

import libcalamares
from libcalamares.utils import check_chroot_call

CONF_DIR = "/boot/extlinux"

def find_boot_partition(partitions):
    import re

    root_device = ""
    boot_device = ""

    for partition in partitions:
        if partition["mountPoint"] == "/":
            root_device = partition["device"]
        if partition["mountPoint"] == "/boot":
            boot_device = partition["device"]
            break

    # If a /boot partition was not found it means that
    # /boot is on the root file system
    if not boot_device:
        boot_device = root_device

    m = re.search(r'([1-9]|[1-9][0-9])', boot_device)
    return m.group(1)

def run():
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    install_path = libcalamares.globalstorage.value("installPath")
    partitions = libcalamares.globalstorage.value("partitions")

    boot_partition = find_boot_partition(partitions)

    mbr_bak = os.path.join(CONF_DIR, "mbr.bak")
    mbr_bin = os.path.join(rootMountPoint, "usr/share/syslinux/mbr.bin")

    check_chroot_call(["/sbin/extlinux", "-i", CONF_DIR])
    check_chroot_call(["/bin/dd", "if=" + install_path, "of=" + mbr_bak, "count=1", "bs=512"])
    check_chroot_call(["/bin/dd", "if=" + mbr_bin, "of=" + install_path])
    check_chroot_call(["sfdisk", "--activate=" + boot_partition, install_path])
    return None
