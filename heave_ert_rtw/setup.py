from setuptools import setup, Extension
import pybind11
import os

include_dirs = [
    pybind11.get_include(),
    "."
]

extra_compile_args = [
    "-O3",
    "-std=c++17",
    "-fPIC"
]

ext_modules = [
    Extension(
        "heave_rt",
        sources=[
            "wrapper.cpp",
            "heave.cpp"
        ],
        include_dirs=include_dirs,
        language="c++",
        extra_compile_args=extra_compile_args,
    )
]

setup(
    name="heave_rt",
    version="1.0.0",
    ext_modules=ext_modules,
)
