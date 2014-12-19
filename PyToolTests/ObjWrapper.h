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
    ObjWrapper(){
      std::cout << "ObjWrapper constructor" << std::endl;
      m_func = new TF1("func", "gaus(0)", 0, 10);
    }
    /// Memory cleanup is done in the destructor
    ~ObjWrapper(){
      std::cout << "ObjWrapper destructor" << std::endl;
      delete m_func;
    }

  private:
    /// Heap objects
    TF1* m_func;
};

#endif
