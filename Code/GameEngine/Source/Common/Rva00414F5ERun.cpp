// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?run@Rva00414F5EHost@@QAEXXZ @0x00414F5E 39B: vector clear via rowed erase 0x00414760 on the +0x1C vector plus global load at 0x00DFEEE8 plus ScoredKillEvaAnnouncer::addMoreTrackersForNewPlayers at 0x00414DAA. Evidence: erase pushes plus global->[0x10] plus and-0 at +0x2C plus tail jmp; sibling 0x00414B0A pattern.
#include <vector>

#include "ascii_string.h"
#include "ScoredKillEvaAnnouncerView.h"


// Retail calls the verified range-erase owner at0x00414760. Declare it
// instead of emitting erase and its layout-dependent assignment helpers.
namespace _STL {
template <> ScoredKillTracker *vector<ScoredKillTracker, allocator<ScoredKillTracker> >::erase(ScoredKillTracker *, ScoredKillTracker *);
}

struct Rva00414F5EGlobal
{
	char m_pad[0x10];
	int m_10;
};
extern class PlayerList *ThePlayerList;

class Rva00414F5EHost
{
public:
	void run();
private:
	char m_00[0x1C];
	_STL::vector<ScoredKillTracker, _STL::allocator<ScoredKillTracker> > m_vec1C;
	int m_28;
	int m_2C;
};

void Rva00414F5EHost::run()
{
	_STL::vector<ScoredKillTracker, _STL::allocator<ScoredKillTracker> > &v = m_vec1C;
	v.erase(v.begin(), v.end());
	m_28 = (*(Rva00414F5EGlobal **)&ThePlayerList)->m_10;
	m_2C = 0;
	return reinterpret_cast<ScoredKillEvaAnnouncer *>(this)->addMoreTrackersForNewPlayers();
}
