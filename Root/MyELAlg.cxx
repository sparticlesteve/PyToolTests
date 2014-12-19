#include "EventLoop/Job.h"
#include "EventLoop/StatusCode.h"
#include "EventLoop/Worker.h"
#include "EventLoop/OutputStream.h"
#include "PyToolTests/MyELAlg.h"

// CP includes
#include "JetSelectorTools/JetCleaningTool.h"
#include "JetInterface/IJetSelector.h"
#include "JetResolution/IJERSmearingTool.h"

// EDM includes
#include "xAODEventInfo/EventInfo.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/ElectronAuxContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODMuon/MuonAuxContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"

const double GeV = 1000.;

// this is needed to distribute the algorithm to the workers
ClassImp(MyELAlg)



MyELAlg :: MyELAlg()
    : m_jetCleaning("JetCleaningTool"),
      m_jerTool("JERSmearingTool")
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode MyELAlg :: setupJob(EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.
  job.useXAOD();

  // Initialize the algo to use xAODRootAccess
  xAOD::Init("MyELAlg").ignore();

  // Output stream
  EL::OutputStream out("outputLabel");
  job.outputAdd(out);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyELAlg :: histInitialize()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyELAlg :: fileExecute()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyELAlg :: changeInput(bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyELAlg :: initialize()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  m_event = wk()->xaodEvent();

  // Try to retrieve the jet cleaning tool
  if(m_jetCleaning.retrieve().isFailure()){
    Error("initialize()", "Unable to retrieve the jet cleaning tool");
    return EL::StatusCode::FAILURE;
  }

  // Retrieve the JER smearing tool
  if(m_jerTool.retrieve().isFailure()){
    Error("initialize()", "Unable to retrieve the JER smearing tool");
    return EL::StatusCode::FAILURE;
  }

  // Initialize and configure jet tool
  /*
  m_jetCleaning = new JetCleaningTool("JetCleaning");
  m_jetCleaning->msg().setLevel(MSG::DEBUG);
  if(m_jetCleaning->setProperty("CutLevel", "MediumBad").isFailure())
    return EL::StatusCode::FAILURE;
  if(m_jetCleaning->initialize().isFailure())
    return EL::StatusCode::FAILURE;
  */

  Info("initialize()", "Number of events = %lli", m_event->getEntries());

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyELAlg :: execute()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  // Print every 100 events
  static Long64_t eventCounter = 0;
  if((eventCounter % 100) == 0) Info("execute()", "Event number = %lli", eventCounter);
  eventCounter++;

  // Event information
  const xAOD::EventInfo* eventInfo = 0;
  if(!m_event->retrieve(eventInfo, "EventInfo").isSuccess()){
    Error("execute()", "Failed to retrieve event info collection. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  // Get input jet container
  const xAOD::JetContainer* jets = 0;
  if(!m_event->retrieve(jets, "AntiKt4LCTopoJets").isSuccess()){
    Error("execute()", "Failed to retrieve AntiKt4LCTopoJets container");
    return EL::StatusCode::FAILURE;
  }
  //Info("execute()", " number of jets = %lu", jets->size());

  // Loop over jets in the container
  for(const auto jet : *jets){
    // Select good jets
    if(!m_jetCleaning->keep(*jet)) continue;

    // Correct a copy of the jet
    xAOD::Jet* jetCopy = 0;
    if(m_jerTool->correctedCopy(*jet, jetCopy) != CP::CorrectionCode::Ok)
      return EL::StatusCode::FAILURE;
    //Info("execute()", "  jet pt = %.2f GeV", jet->pt() * 0.001);
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyELAlg :: postExecute()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyELAlg :: finalize()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  //if(m_jetCleaning) delete m_jetCleaning;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyELAlg :: histFinalize()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}
