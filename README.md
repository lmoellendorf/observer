# README                                                             {#mainpage}
    @code

     ___ _____ _   ___ _  _____ ___  ___  ___ ___
    / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
    \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
    |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
    embedded.connectivity.solutions.==============

    @endcode

# Introduction                                                   {#introduction}

## Purpose                                                            {#purpose}

The STACKFORCE Observer abstracts the use of the observer/subject pattern.

## Features                                                           {#feature}

The Observer provides base classes to be implemented by concrete
observers and subjects.

Baically a concrete subject has to implement the Attach and Detach methods and
store registered observers e.g. in an observers vector.
The observer class has to implement the Update method which is used by the
subject to pass events to the oberver.

@code
                                    +----------------------------------------------+
 +--------------------------+       |                                              |
 |                          |       |  Subject                                     |
 |  Observer                +-----<>|                                              |
 |                          |       +----------------------------------------------+
 +--------------------------+       |                                              |
 |                          |       +----------------------------------------------+
 +--------------------------+       |                                              |
 |                          |       | +Attach ( Observer *observer )               |
 | +Update ( Event *event ) |       | +Detach ( Observer *observer )               |
 |                          |       | +Notify ( Observer *observer, Event *event ) |
 +--------------------------+       |                                              |
             /_\                    +----------------------------------------------+
              |                                           /_\
              |                                            |
              |                                            |
              |                                            |
 +------------+-------------+             +----------------+---------------+
 |                          |             |                                |
 |  ConcreteObserverA       |             | ConcreteSubject                |
 |                          |             |                                |
 +--------------------------+             +--------------------------------+
 |                          |             |                                |
 +--------------------------+             | +ObserverCollection            |
 |                          |             |                                |
 | +Update ( Event *event ) |             +--------------------------------+
 |                          |             |                                |
 +--------------------------+             | +Attach ( Observer *observer ) |
                                          | +Detach ( Observer *observer ) |
                                          |                                |
                                          +--------------------------------+
@endcode

## Build instructions                                                   {#build}

The STACKFORCE Observer uses CMake as build system. How to build:
Go to root, create build directory:

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

To generate the doxygen documentation run:

    make doc

To generate packages run:

	make package

	This will generyte by default a tar.gz archive, and installer shell script
	and if run under Ubuntu, Debian or LinuxMint, a debian package that can be installed
	with "dpkg".
