# libcpuid

Extensible CPUID interaction library

## Introduction

__CPUID__ is utility that provides critical information about a system that can help systems engineers when designing low-level applications.

## Features

* __Extensible Base C library__ - libcpuid provides a _base_ library that can easily be plugged into any programming language through FFI (or the language's API, if permittable). There are Python bindings available with this library.

* __Easy-to-use methods__ - libcpuid utilizes straightforward and simple methods for users.

## Usage

To build the Python (3.6.x) bindings:

```
$ python setup.py install
$ python
...
> import cpuid
```
