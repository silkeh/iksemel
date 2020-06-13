[![Travis Status](https://travis-ci.org/Zaryob/iksemel.svg?branch=master)](https://travis-ci.org/Zaryob/iksemel) ![Language](https://img.shields.io/badge/language-c-blue.svg) ![License](https://img.shields.io/badge/license-LGPL2-purple.svg)

                      iksemel 1.6

            http://code.google.com/p/iksemel

Owner:
Copyright (c) 2000-2011 Gurer Ozen <meduketto at gmail.com>

Changes and adaptations:
Copyright (c) 2016-2020 Suleyman Poyraz <zaryob.dev at gmail.com>

Introduction:
-------------

This is an XML parser library mainly designed for Jabber applications.
It provides SAX, DOM, and special Jabber stream APIs. Library is coded
in ANSI C except the network code (which is POSIX compatible), thus
highly portable. Iksemel is released under GNU Lesser General Public
License. A copy of the license is included in the COPYING file.


Requirements:
-------------

Meson and Ninja packages are required for compiling cvs versions.

TLS support requires OpenSSL (>1.1.0) or GNUTLS (>2.0.0) library.

Python bindings requires Python (>3.3).


Compiling & Install:
--------------------

If you got the source from CVS, type

  meson build_dir

for creating configuration script and files.

Then type

  ninja -C build

now library is compiled. You can test it with

  ninja test -C build

and install it with

  (become root if necessary)
  ninja install -C build
