#ifndef PYTOOLTESTS_OBJWRAPPER_H
#define PYTOOLTESTS_OBJWRAPPER_H

#include <map>
#include <iostream>

#include "TF1.h"

/// Simple class to test memory issue with PyROOT
class ObjWrapper
{
  public:
    /// Memory initialization is done in the constructor
    ObjWrapper();
    /// Memory cleanup is done in the destructor
    ~ObjWrapper();

    /// Do some work
    void doSomething();

  private:
    /// Heap objects
    TF1* m_func;
};

#endif
