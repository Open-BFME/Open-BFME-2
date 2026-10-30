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
// Suppress this TU's non-retail copy of ?push_back@?$vector@UBfmeRecord001ECAF9@@V?$allocator@UBfmeRecord001ECAF9@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeRecord001ECAF9;
namespace _STL { template <> void vector<BfmeRecord001ECAF9,allocator<BfmeRecord001ECAF9> >::push_back(BfmeRecord001ECAF9 const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmeRecord001ECAF9@@V?$allocator@UBfmeRecord001ECAF9@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeRecord001ECAF9;
namespace _STL { template <> void vector<BfmeRecord001ECAF9,allocator<BfmeRecord001ECAF9> >::_M_insert_overflow(BfmeRecord001ECAF9 *,BfmeRecord001ECAF9 const &,__false_type const &,unsigned int,bool); }

enum INILoadType { INI_LOAD_INVALID, INI_LOAD_OVERWRITE };
struct FieldParse;
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	__declspec(dllimport) __forceinline INILoadType getLoadType() const { return loadType; }
	void initFromINI(void *, const FieldParse *);
	char m_pad00[0x8];
	INILoadType loadType; // +0x08 +0x08, overwrite for the startup files
};

template <class T> class StringBase;
template <> class StringBase<char>
{
public:
	StringBase(const char *s);
	~StringBase();
	void releaseBuffer();
};

class Rva001EB329 { public: void rva001EB329(INI *); };
struct BfmeRecord001ECAF9
{
	char m_pad[36];
	BfmeRecord001ECAF9(const StringBase<char> &s);
	~BfmeRecord001ECAF9();
	/* the rowed Rva001EB329::rva001EB329 */ __declspec(dllimport) __forceinline void rva001EB329(INI * p0) { ((Rva001EB329 *)this)->rva001EB329(p0); }
};

// Retail's record ctor/dtor are folded onto the 0x001EC311 and 0x001EC349
// rows: same thiscall shapes over the same 36-byte record, and this unit's
// verified row resolves the calls there.
#pragma comment(linker, "/alternatename:??0BfmeRecord001ECAF9@@QAE@ABV?$StringBase@D@@@Z=??0Rva001EC311@@QAE@ABV?$StringBase@D@@@Z")
#pragma comment(linker, "/alternatename:??1BfmeRecord001ECAF9@@QAE@XZ=??1Rva001EC349@@QAE@XZ")

void Rva001ED2C5Parse(INI *ini, void *unused, _STL::vector<BfmeRecord001ECAF9> *vec)
{
	const char *tok = ini->getNextToken(0);
	{
		StringBase<char> tmp(tok);
		vec->push_back(BfmeRecord001ECAF9(tmp));
	}
	vec->back().rva001EB329(ini);
}

// Names this unit references that no unit defines under that spelling. Each is
// bound to the row that owns the pinned retail address (same address, same
// body); the pin keeps the name, the row supplies the definition.
#pragma comment(linker, "/alternatename:??0BfmeRecord001ECAF9@@QAE@ABV?$StringBase@D@@@Z=??0Rva001EC311@@QAE@ABV?$StringBase@D@@@Z")
#pragma comment(linker, "/alternatename:??1BfmeRecord001ECAF9@@QAE@XZ=??1Rva001EC349@@QAE@XZ")
