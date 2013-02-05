Maui Installer
==============

This is the Maui graphical installer.

## Dependencies

In order to build and install this project, you will need a complete
and up to date Qt 5 copy.

More information about building Qt 5 can be found here:

  http://qt-project.org/wiki/Building-Qt-5-from-Git

## Build

Assuming you are in the source directory, just create a build directory
and run cmake:

    mkdir build
    cd build
    cmake ..

To do a debug build the last command can be:

    cmake -DCMAKE_BUILD_TYPE=Debug ..

To do a release build instead it can be:

    cmake -DCMAKE_BUILD_TYPE=Release ..

If not passed, the CMAKE_INSTALL_PREFIX parameter defaults to /usr/local.
You have to specify a path that fits your needs, /opt/hawaii is just an example.

The CMAKE_BUILD_TYPE parameter allows the following values:

    Debug: debug build
    Release: release build
    RelWithDebInfo: release build with debugging information

## Installation

It's really easy, it's just a matter of typing:

    make install

from the build directory.
