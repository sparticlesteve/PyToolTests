#ifndef PYTOOLTESTS_SELECTOR_H
#define PYTOOLTESTS_SELECTOR_H

#include "TSelector.h"

/// Selector class for testing tool configuration in python
///
/// @author Steve Farrell <Steven.Farrell@cern.ch>
///
class Selector : public TSelector
{

  public:

    /// Default constructor
    Selector();
    ~Selector();

    ///
    /// TSelector methods
    ///

    /// Init is called every time a new TTree is attached
    virtual void    Init(TTree *tree);
    /// Begin is called before looping on entries
    virtual void    Begin(TTree *tree);
    /// Called at the first entry of a new file in a chain
    virtual Bool_t  Notify() { return kTRUE; }
    /// Terminate is called after looping is finished
    virtual void    Terminate();
    /// Due to ROOT's stupid design, need to specify version >= 2 or the tree will not connect automatically
    virtual Int_t   Version() const {
      return 2;
    }

    /// Main event loop function
    virtual Bool_t  Process(Long64_t entry);

    /// Update the event store
    virtual Int_t   GetEntry(Long64_t e, Int_t getall = 0);

  protected:

}; // class Selector

#endif
