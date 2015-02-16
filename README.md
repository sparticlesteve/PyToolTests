PyToolTests
===========

Testing code using PyROOT bindings for dual-use tool configuration.

## Python <-> C++ tool configuration

In this example, the tool is instantiated in C++ and passed to a user-specified
python function for configuration. TPython is used for the PyObject binding,
and some Python API code is used to pass the tool to python functions. The tool
is first pythonized so that tool properties can be set as attributes.

* TestTool - a trivial dual-use tool with string, int, and float properties.
* callPythonFunction - a standalone function in PythonCaller.h which passes
  the tool to the python wrapper code.
    * Uses TPython, the reflex dictionary, and the python API to bind the tool.
* wrapper - a python module containing the python utilities to prepare the tool
  and call the user python function
* toolconfig - an example user python module containing the function which
  configures the tool.
* testPythonCaller - an executable which steers the example.

## Python -> EventLoop

## ROOT TF1 cleanup test

