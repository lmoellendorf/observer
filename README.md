# README
```
     ___ _____ _   ___ _  _____ ___  ___  ___ ___
    / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
    \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
    |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
    embedded.connectivity.solutions.==============
```

# Introduction

## Purpose

The STACKFORCE Observer abstracts the use of the observer/subject pattern.

## Features

The Observer is an interface class inherited by concrete observers/subjects.

Basically a concrete subject has to implement the Attach and Detach methods and
store registered observers e.g. in an observers vector.

A concrete observer class has to implement the Update method which is used by the
subject to pass events to the oberver. The observer is responsible of handling the
received events when its update method is called.

```
                                    +----------------------------------------------+
 +--------------------------+       |  Subject                                     |
 |  Observer                |       +----------------------------------------------+
 +--------------------------+       |                                              |
 |                          |       +----------------------------------------------+
 +--------------------------+       |                                              |
 | +Update ( Event *event ) |       | +Attach ( Observer *observer )               |
 +--------------------------+       | +Detach ( Observer *observer )               |
             /_\                    | +Notify ( Observer *observer, Event *event ) |
              |                     +----------------------------------------------+
              |                                           /_\
              |                                            |
              |                                            |
              |                                            |
 +------------+-------------+             +----------------+---------------+
 |  ConcreteObserver        +-----------<>| ConcreteSubject                |
 +--------------------------+             +--------------------------------+
 |                          |             | -ObserverCollection            |
 +--------------------------+             +--------------------------------+
 | +Update ( Event *event ) |             | +Attach ( Observer *observer ) |
 +--------------------------+             | +Detach ( Observer *observer ) |
                                          +--------------------------------+
```

## Build instructions

The STACKFORCE Observer uses CMake as build system.
Note that, once built, the library can be used by other cmake projects with the
`find_package()` command without requiring to install the library on the system.
Therefore running a `make install` is not mandatory to be able to build other
projects that link to the observer library.

Go to the project directory and create a build directory:

    cd observer
    mkdir build

and run:

    cmake ..
    make
    sudo make install

or to define a custom install directory e.g. devroot:

    cmake .. -DCMAKE_INSTALL_PREFIX=devroot
    make
    make install

To generate packages run:

	make package

This will generate a tar.gz archive, and installer shell script by default.
If run under Ubuntu, Debian or LinuxMint, a debian package will be generated.

    dpkg -i package_name.deb
