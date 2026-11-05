// cl: /Ireference/shims/moduledata  /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ, retail 0x0039C09C (88B,
// EH, RET0). Copies the scored-kill-tracker pointer vector at +0x304
// (rowed vector<unsigned> copy 0x002CFAB9; 4-byte elements reused as
// ScoredKillTracker pointers), unhooks each tracker through the rowed
// ScoredKillTracker::rva0055A91A, then frees the copy's buffer through the
// rowed _free 0x00030830. Identity from the WorldBuilder ScoreKeeper name and
// the 0x0039C2B5 caller (prior bank notes); neighbours 0x0039BFC5/0x0039C0F4
// set the /O1 /DNDEBUG /MD flags.
//
// Retail's copy constructor 0x002CFAB9 has no EH frame although it calls
// the out-of-line __copy_trivial 0x000179B0 after the base allocates, so
// retail's STLport declared __copy_trivial non-throwing. Declared that way
// here, the copy constructor cannot unwind and cl keeps the copy's begin in
// edi across the unhook calls for the final free, with retail's pre-tested
// loop; with the shim's plain declaration the begin is reloaded from its
// stack home and the loop is bottom-tested.
#include <stdlib.h>
#include <vector>
namespace _STL {
void *__copy_trivial(const void *__first, const void *__last, void *__result) throw();
}

#include "../ScoredKillTrackerView.h"

class ScoreKeeper
{
public:
	void unhookAllScoredKillTrackers();
private:
	char m_pad[0x304];
	_STL::vector<unsigned int> m_scoredKillTrackers; // +0x304
};

void ScoreKeeper::unhookAllScoredKillTrackers()
{
	_STL::vector<unsigned int> trackers(m_scoredKillTrackers);
	for (_STL::vector<unsigned int>::iterator it = trackers.begin(); it != trackers.end(); ++it)
		((ScoredKillTracker *)*it)->rva0055A91A();
}
