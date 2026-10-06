// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva000C20A3@@QAE@XZ @0x000C20A3 30B
// Vector-like container dtor over Rva00079554Record without EH frame.
// Evidence: retail calls rowed
// ??$_Destroy@PAURva00079554Record@@@_STL@@YAXPAURva00079554Record@@0@Z
// @0x000BD2A6 with (m_start, m_finish) at +0 +4 then frees m_start via
// rowed _free @0x00030830; caller @0x000C36F4; same recipe as rowed
// ??1Rva000C2085 @0x000C2085.
#include <vector>

struct Rva00079554Record
{
	~Rva00079554Record();
};

namespace _STL
{
template <> void _Destroy<Rva00079554Record *>(Rva00079554Record *first, Rva00079554Record *last);
}

extern "C" void __cdecl free(void *block);

class Rva000C20A3
{
	Rva00079554Record *m_start;
	Rva00079554Record *m_finish;

public:
	~Rva000C20A3();
};

Rva000C20A3::~Rva000C20A3()
{
	_STL::_Destroy(m_start, m_finish);
	if (m_start)
		free(m_start);
}
