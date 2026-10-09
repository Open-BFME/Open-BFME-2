// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ
// partial score=0.7 date=2026-10-09
// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/moduledata /I. /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ @0x0039C09C 88B
// Evidence: LINK BONUS via 0x0039C2B5; rowed _free at 0x00030830 releases the copied buffer. The allocator name is redirected only while including the TU-scoped STLport allocator header, using existing target name Rva00030830FreeAllocation. retail calls rowed vector<unsigned> copy 0x002CFAB9
// plus rowed Rva0055A91A::rva0055A91A 0x0055A91A plus rowed _free 0x00030830 plus __EH_prolog;
// member vector at +0x304 (4B elements reused as Rva0055A91A pointers); neighbours
// 0x0039BFC5/0x0039C0F4 prove /O1 /DNDEBUG /MD /EHsc TU flags; loop over temp copy
// calling Clear on each pointee then freeing temp matches retail pointer-chase shape.

#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free

#include "Code/GameEngine/Source/Common/ScoredKillTrackerView.h"
template _STL::vector<unsigned>::vector(const _STL::vector<unsigned>&);
class ScoreKeeper
{
public:
	void unhookAllScoredKillTrackers();
private:
	char m_pad[0x304];
	std::vector<unsigned int> m_vec;
};

// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ present-unmatched
void ScoreKeeper::unhookAllScoredKillTrackers()
{
	const std::vector<unsigned int> tmp(m_vec);
	const unsigned int *begin = tmp.begin();
	
	if (tmp.end() != begin)
	{
		const unsigned int *it = begin;
		do
		{
			((ScoredKillTracker *)*it)->rva0055A91A();
			it++;
		} while (it != tmp.end());
	}
}
