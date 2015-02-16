#ifndef PYTOOLTESTS_PYTHONCALLER_H
#define PYTOOLTESTS_PYTHONCALLER_H

#include "AsgTools/StatusCode.h"

/// Function which takes an object, its classname, a python module name,
/// and a python function name and applies the python function to the object
StatusCode callPythonFunction(void* obj,
                              const std::string& className,
                              const std::string& fileName,
                              const std::string& funcName);

#endif
