// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva00308C13@@QAE@XZ, retail 0x00308C13, 30B.
// Vector-like container dtor over Rva0027EA49 without EH frame.
// Evidence: retail calls rowed
// ??$_Destroy@PAURva0027EA49@@@_STL@@YAXPAURva0027EA49@@0@Z
// @0x00281AD4 with (m_start, m_finish) at +0 +4 then frees m_start via
// rowed _free @0x00030830; caller @0x00282906 in 0x00282870; same 30B recipe
// as rowed ??1Rva000C20A3 @0x000C20A3.
#include <vector>

struct Rva0027EA49
{
	~Rva0027EA49();
};

namespace _STL
{
template <> void _Destroy<Rva0027EA49 *>(Rva0027EA49 *first, Rva0027EA49 *last);
}

extern "C" void __cdecl free(void *block);

class Rva00308C13
{
	Rva0027EA49 *m_start;
	Rva0027EA49 *m_finish;

public:
	~Rva00308C13();
};

Rva00308C13::~Rva00308C13()
{
	_STL::_Destroy(m_start, m_finish);
	if (m_start)
		free(m_start);
}
