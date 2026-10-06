// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00220FC4Parse@@YAXPAVINI@@PAXPAV?$vector@UBfmeStringRecord0022074B@@V?$allocator@UBfmeStringRecord0022074B@@@_STL@@@_STL@@@Z, retail 0x00220FC4 (78 bytes).
// Chain from just-landed push_back 0x00220F8D: temp LocomotorStore (ctor
// 0x0022078E dtor 0x002207C4) parsed via INI::initFromINI 0x0002DE78 with
// table g_00BE6AD0 then appended via rowed push_back. No callers. Evidence:
// annotated disassembly, prev push_back row, LocomotorStore ctor/dtor rows.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);
private:
	void *m_data;
};

struct BfmeStringRecord0022074B
{
	AsciiString text0;
	AsciiString text1;
	unsigned int word;
	BfmeStringRecord0022074B(const BfmeStringRecord0022074B &other);
};

class LocomotorStore
{
public:
	LocomotorStore();
	~LocomotorStore();
private:
	unsigned m_pad[3];
};

struct FieldParse;
extern const FieldParse g_00BE6AD0[];

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

void Rva00220FC4Parse(INI *ini, void *dummy, _STL::vector<BfmeStringRecord0022074B> *vec)
{
	LocomotorStore tmp;
	ini->initFromINI(&tmp, g_00BE6AD0);
	vec->push_back(reinterpret_cast<const BfmeStringRecord0022074B &>(tmp));
}
