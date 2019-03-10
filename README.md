# libcpuid

cpuid interaction library

## intro

`cpuid` is an instruction supported in various architectures that performs processor introspection, grabbing information about processor type and feature support (i.e SSE).

We create a simple wrapper to `cpuid` to C and Python.

## features

* __Extensible Base C library__ - libcpuid provides a _base_ library that can easily be plugged into any programming language through FFI (or the language's API, if permittable). There are Python bindings available with this library.

* __Easy-to-use methods__ - libcpuid utilizes straightforward and simple methods for users.

## usage

To build the Python (3.6.x) bindings:

```
$ python setup.py install
$ python
...
> import cpuid
```

## license

[mit](https://codemuch.tech/license.txt)
