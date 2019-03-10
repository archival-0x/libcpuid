"""
setup.py

    Basic setup script for initializing Python
    module through C FFI with extension.Extension

"""

from setuptools import setup, find_packages
from setuptools.extension import Extension

CPUID_EXTENSION = Extension('cpuid', ['cpuid/cpuid-python.c'],
                             extra_compile_args=["-Wall"])

setup(
    name            = "libcpuid",
    version         = "0.1.0",
    author          = "Alan <ex0dus@codemuch.tech",
    description     = "Wrapper library for interfacing CPUID operations for Python written in C",
    url             = "https://github.com/ex0dus-0x/libcpuid",
    ext_modules     = [CPUID_EXTENSION]
)
