// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva002E26C3@@QAE@XZ, retail 0x002E26C3, 30B.
// Vector-like container dtor over Rva002E2690Element without EH frame.
// Evidence: retail calls rowed ??$_Destroy@PAURva002E2690Element@@@_STL@@YAXPAURva002E2690Element@@0@Z @0x002AF4ED with (m_start m_finish) at +0 +4 then frees m_start via rowed _free @0x00030830; callers at 0x002E2729 in 0x002E26E1 and at 0x002E2C58 in 0x002E2BBA; same 30B recipe as rowed ??1Rva00308C13 @0x00308C13.
#include <vector>

struct Rva002E2690Element
{
	~Rva002E2690Element();
};

namespace _STL
{
template <> void _Destroy<Rva002E2690Element *>(Rva002E2690Element *first, Rva002E2690Element *last);
}

extern "C" void __cdecl free(void *block);

class Rva002E26C3
{
	Rva002E2690Element *m_start;
	Rva002E2690Element *m_finish;

public:
	~Rva002E26C3();
};

Rva002E26C3::~Rva002E26C3()
{
	_STL::_Destroy(m_start, m_finish);
	if (m_start)
		free(m_start);
}
