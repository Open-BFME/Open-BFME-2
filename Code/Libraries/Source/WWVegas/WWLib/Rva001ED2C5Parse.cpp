// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva001ED2C5Parse@@YAXPAVINI@@PAXPAV?$vector@UBfmeRecord001ECAF9@@V?$allocator@UBfmeRecord001ECAF9@@@_STL@@@_STL@@@Z @0x001ED2C5 115B
// Banked attempt reverse/attempts/0x001ed2c5.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// stlport
// ?Rva001ED2C5Parse@@YAXPAVINI@@PAXPAV?$vector@UBfmeRecord001ECAF9@@V?$allocator@UBfmeRecord001ECAF9@@@_STL@@@_STL@@@Z @0x001ED2C5 115B. REF via table slot 0x007DF20C neighbour Mission. INI token to record push then parse last. Honest free-function name shape per naming line.
// TU-local honest-address views; offsets prove operations not type names.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

class INI
{
public:
	const char *getNextToken(const char *s);
};

template <class T> class StringBase;
template <> class StringBase<char>
{
public:
	StringBase(const char *s);
	~StringBase();
	void releaseBuffer();
};

struct BfmeRecord001ECAF9
{
	char m_pad[36];
	BfmeRecord001ECAF9(const StringBase<char> &s);
	~BfmeRecord001ECAF9();
	void rva001EB329(INI *ini);
};

void Rva001ED2C5Parse(INI *ini, void *unused, _STL::vector<BfmeRecord001ECAF9> *vec)
{
	const char *tok = ini->getNextToken(0);
	{
		StringBase<char> tmp(tok);
		vec->push_back(BfmeRecord001ECAF9(tmp));
	}
	vec->back().rva001EB329(ini);
}
