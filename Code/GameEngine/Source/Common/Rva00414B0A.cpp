// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?rva00414B0A@Rva00414B0A@@QAEXXZ retail 0x00414B0A 26B. Vector erase plus two int clears.
// Evidence: rowed erase 0x00414760 vector<ScoredKillTracker>; caller 0x00414B89 iterates 0x30 entries; layout matches Rva00414932Dtor vector at +0x1C.
#include <vector>

#include "ascii_string.h"

#include "ScoredKillTrackerView.h"

// Retail calls the verified range-erase owner at0x00414760. Declare it
// instead of emitting erase and its layout-dependent assignment helpers.
namespace _STL {
template <> ScoredKillTracker *vector<ScoredKillTracker, allocator<ScoredKillTracker> >::erase(ScoredKillTracker *, ScoredKillTracker *);
}

class Rva00414B0A
{
public:
	void rva00414B0A();
private:
	char m_pad00[0x1C];
	_STL::vector<ScoredKillTracker, _STL::allocator<ScoredKillTracker> > m_vec1C;
	int m_28;
	int m_2C;
};

void Rva00414B0A::rva00414B0A()
{
	_STL::vector<ScoredKillTracker, _STL::allocator<ScoredKillTracker> > &v = m_vec1C;
	v.erase(v.begin(), v.end());
	m_28 = 0;
	m_2C = 0;
}
