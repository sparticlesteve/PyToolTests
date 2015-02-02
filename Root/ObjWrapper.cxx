#include "TROOT.h"
#include "PyToolTests/ObjWrapper.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
ObjWrapper::ObjWrapper()
{
  std::cout << "ObjWrapper constructor" << std::endl;
  m_func = new TF1("func", "gaus(0)", 0, 10);
  // I own this function. Don't let ROOT clean it up.
  gROOT->GetListOfFunctions()->Remove(m_func);
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
ObjWrapper::~ObjWrapper()
{
  std::cout << "ObjWrapper destructor" << std::endl;
  delete m_func;
}

//-----------------------------------------------------------------------------
// Initialize
//-----------------------------------------------------------------------------
void ObjWrapper::doSomething()
{
  std::cout << "ObjWrapper doSomething" << std::endl;
  m_func->Print();
  std::cout << m_func->GetParent() << std::endl;
}
