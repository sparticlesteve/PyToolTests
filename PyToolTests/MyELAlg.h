#ifndef PYTOOLTESTS_MYELALG_H
#define PYTOOLTESTS_MYELALG_H

// Infrastructure includes
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "AsgTools/ToolHandle.h"
#include "EventLoop/Algorithm.h"


class JetCleaningTool;
class IJetSelector;
class IJERSmearingTool;

class MyELAlg : public EL::Algorithm
{

  public:

    // Standard constructor
    MyELAlg();

    // Algorithm methods
    virtual EL::StatusCode setupJob(EL::Job& job);
    virtual EL::StatusCode fileExecute();
    virtual EL::StatusCode histInitialize();
    virtual EL::StatusCode changeInput(bool firstFile);
    virtual EL::StatusCode initialize();
    virtual EL::StatusCode execute();
    virtual EL::StatusCode postExecute();
    virtual EL::StatusCode finalize();
    virtual EL::StatusCode histFinalize();


    // Public configuration variables
    float lepPtMin;
    float jetPtMin;

    ClassDef(MyELAlg, 1);

  protected:

    xAOD::TEvent* m_event; //!

    #ifndef __CINT__
    //JetCleaningTool* m_jetCleaning; //!
    ToolHandle<IJetSelector> m_jetCleaning;
    ToolHandle<IJERSmearingTool> m_jerTool;
    #endif

}; // class MyELAlg

#endif
