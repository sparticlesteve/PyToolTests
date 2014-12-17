// Local includes
#include "PyToolTests/Selector.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
Selector::Selector()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
Selector::~Selector()
{
}

//-----------------------------------------------------------------------------
// Attach tree
//-----------------------------------------------------------------------------
void Selector::Init(TTree* tree)
{
  cout << "Selector::Init" << endl;
  //m_tree = tree;
  //d3pd.ReadFrom(tree);
}

//-----------------------------------------------------------------------------
// The Begin() function is called at the start of the query.
// When running with PROOF Begin() is only called on the client.
// The tree argument is deprecated (on PROOF 0 is passed).
//-----------------------------------------------------------------------------
void Selector::Begin(TTree* /*tree*/)
{
  cout << "Selector::Begin" << endl;
}

//-----------------------------------------------------------------------------
// Main process loop function - This is just an example for testing
//-----------------------------------------------------------------------------
Bool_t Selector::Process(Long64_t entry)
{
  return kTRUE;
}
