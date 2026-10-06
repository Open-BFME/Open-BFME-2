// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva000C2085@@QAE@XZ @0x000C2085 30B
// Vector-like container dtor over Rva00B9AC2 without EH frame.
// Evidence: retail calls rowed
// ??$_Destroy@PAURva00B9AC2@@@_STL@@YAXPAURva00B9AC2@@0@Z @0x000BD28D
// with (m_start, m_finish) at +0 +4 then frees m_start via rowed _free
// @0x00030830; callers @0x000C21D7 @0x000C363D; declared-only
// specialization pattern from VectorMemberRecordDtors.cpp.
#include <vector>

struct Rva00B9AC2
{
	~Rva00B9AC2();
	unsigned char m_data[0x18];
};

namespace _STL
{
template <> void _Destroy<Rva00B9AC2 *>(Rva00B9AC2 *first, Rva00B9AC2 *last);
}

extern "C" void __cdecl free(void *block);

class Rva000C2085
{
	Rva00B9AC2 *m_start;
	Rva00B9AC2 *m_finish;

public:
	~Rva000C2085();
};

Rva000C2085::~Rva000C2085()
{
	_STL::_Destroy(m_start, m_finish);
	if (m_start)
		free(m_start);
}
