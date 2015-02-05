#include "Python.h"

#include <iostream>

#include "TPython.h"

#include "PyToolTests/PythonCaller.h"


/// Convenience macro for checking errors
#define PYCHECK(ptr, msg)                               \
  do{                                                   \
    if(!ptr){                                           \
      std::cerr << "ERROR - " << msg << std::endl;      \
      return StatusCode::FAILURE;                       \
    }                                                   \
  } while(false)


/// Function which takes an object, its classname, a python module name,
/// and a python function name and applies the python function to the object
///
/// TODO: consider simplifying this. I don't need to do the user imports here.
/// I could instead do them on the python side. In fact, I could probably
/// forego using TPython altogether, initialize the python interpreter myself,
/// and import ROOT in Batch mode on the python side.
///
StatusCode callPythonFunction(void* obj,
                              const std::string& className,
                              const std::string& moduleName,
                              const std::string& funcName)
{

  std::cout << "::callPythonFunction Begin" << std::endl;
  std::cout << "obj " << obj << " className " << className << std::endl;
  std::cout << "moduleName " << moduleName
            << " funcName " << funcName << std::endl;

  // First, use PyROOT to get a PyObject binding.
  // This does some PyROOT initialization, which I think unfortunately
  // does more than we need (e.g. graphics).
  PyObject* pyObj = TPython::ObjectProxy_FromVoidPtr(obj, className.c_str());
  PYCHECK( pyObj, "unable to bind user object" );

  // Import the user python module
  PyObject* pyUserModule = PyImport_ImportModule(moduleName.c_str());
  PYCHECK( pyUserModule, "unable to import user module" );

  // Get the user function
  PyObject* pyUserFunc = PyObject_GetAttrString(pyUserModule, funcName.c_str());
  PYCHECK( pyUserFunc, "unable to retrieve user function" );

  // Import the wrapper module
  PyObject* pyWrapperModule = PyImport_ImportModule("PyToolTests.wrapper");
  PYCHECK( pyWrapperModule, "unable to import wrapper.py" );

  // Get the wrapper function
  PyObject* pyWrapperFunc =
    PyObject_GetAttrString(pyWrapperModule, "execute_user_func");
  PYCHECK( pyWrapperFunc, "unable to call wrapper.py" );

  // Call the wrapper function
  PyObject* pyReturn =
    PyObject_CallFunctionObjArgs(pyWrapperFunc, pyObj, pyUserFunc, NULL);
  PYCHECK( pyReturn, "failure in " << moduleName << "." << funcName );

  // Garbage collection
  // TODO: restructure to guarantee these are called in event of error
  Py_XDECREF(pyReturn);
  Py_DECREF(pyWrapperFunc);
  Py_DECREF(pyWrapperModule);
  Py_DECREF(pyUserFunc);
  Py_DECREF(pyUserModule);
  //Py_DECREF(pyUserModuleName);

  std::cout << "::callPythonFunction Finished" << std::endl;
  return StatusCode::SUCCESS;

}
