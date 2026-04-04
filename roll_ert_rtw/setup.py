from setuptools import setup, Extension
import pybind11
import sys

ext_modules = [
    Extension(
        name="roll_ctrl",
        sources=[
            "wrapper.cpp",
            "roll.cpp",
        ],
        include_dirs=[
            pybind11.get_include(),
            ".",
        ],
        language="c++",
        extra_compile_args=[
            "-O3",
            "-std=c++17",
            "-fPIC",
        ],
    )
]

setup(
    name="roll_ctrl",
    version="1.0.0",
    author="You",
    description="Roll DOF controller (Simulink ERT)",
    ext_modules=ext_modules,
)
