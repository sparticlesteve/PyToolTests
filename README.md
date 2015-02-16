PyToolTests
===========

Testing code using PyROOT bindings for dual-use tool configuration.

## Python <-> C++ tool configuration

In this example, the tool is instantiated in C++ and passed to a user-specified
python function for configuration. TPython is used for the PyObject binding,
and some Python API code is used to pass the tool to python functions. The tool
is first pythonized so that tool properties can be set as attributes.

* *TestTool* - a trivial dual-use tool with string, int, and float properties.
* *PythonCaller.h* - Contains a standalone function, callPythonFunction, which
  communicates with the python wrapper code to call the user function.
    * Uses TPython, the reflex dictionary, and the python API to bind the tool.
* *python/wrapper.py* - a python module containing the python utilities to
  prepare the tool and call the user python function
* *python/toolconfig.py* - an example user python module containing the
  function which actually configures the tool.
* *util/testPythonCaller.cxx* - an executable which steers the example.

## Python -> EventLoop

In this example, I demonstrate the usage of python as the steering language
for a local EventLoop job. Tools are created on the python side using the
reflex dictionary, and are retrieved in the EL algorithm via the ToolStore.

## ROOT TF1 cleanup test

Debugging an issue with TF1s getting cleaned up early by ROOT in PyROOT
resulting in invalid pointers on the C++ side.
