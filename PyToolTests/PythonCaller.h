#ifndef PYTOOLTESTS_PYTHONCALLER_H
#define PYTOOLTESTS_PYTHONCALLER_H

#include <iostream>

#include "Python.h"
#include "TPython.h"

#include "AsgTools/StatusCode.h"

/// Function which takes an object, its classname, a python module name,
/// and a python function name and applies the python function to the object
StatusCode callPythonFunction(void* obj, const std::string& className,
                              const std::string& fileName, const std::string& funcName)
{

  StatusCode sc = StatusCode::SUCCESS;

  std::cout << "::callPythonFunction Begin" << std::endl;
  std::cout << "obj " << obj << " className " << className << std::endl;
  std::cout << "fileName " << fileName << " funcName " << funcName << std::endl;

  // First, use PyROOT to get a PyObject binding
  PyObject* pyObj = TPython::ObjectProxy_FromVoidPtr(obj, className.c_str());
  std::cout << "pyObj " << pyObj << std::endl;

  // Import the python module
  PyObject* pyModuleName = PyString_FromString(fileName.c_str());
  std::cout << "pyModuleName " << pyModuleName << std::endl;
  PyObject* pyModule = PyImport_Import(pyModuleName);
  std::cout << "pyModule " << pyModule << std::endl;

  // Get the function
  PyObject* pyFunc = PyObject_GetAttrString(pyModule, funcName.c_str());
  std::cout << "pyFunc " << pyFunc << " callable " << PyCallable_Check(pyFunc)
            << std::endl;

  // Call the function
  PyObject* pyReturn = PyObject_CallFunctionObjArgs(pyFunc, pyObj, NULL);
  std::cout << "pyReturn " << pyReturn << std::endl;

  if(!pyReturn){
    std::cerr << "ERROR in " << fileName << "." << funcName << std::endl;
    sc = StatusCode::FAILURE;
  }

  std::cout << "Collecting garbage" << std::endl;
  Py_XDECREF(pyReturn);
  Py_DECREF(pyFunc);
  Py_DECREF(pyModule);
  Py_DECREF(pyModuleName);

  std::cout << "::callPythonFunction Finished" << std::endl;
  return sc;

}


#endif
