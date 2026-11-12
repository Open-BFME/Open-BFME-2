// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00220FC4Parse@@YAXPAVINI@@PAXPAV?$vector@UBfmeStringRecord0022074B@@V?$allocator@UBfmeStringRecord0022074B@@@_STL@@@_STL@@@Z, retail 0x00220FC4 (78 bytes).
// Chain from just-landed push_back 0x00220F8D: temp LocomotorStore (ctor
// 0x0022078E dtor 0x002207C4) parsed via INI::initFromINI 0x0002DE78 with
// table LocomotorStoreFieldParse (VA 0x00BE6AD0) then appended via rowed push_back. No callers. Evidence:
// annotated disassembly, prev push_back row, LocomotorStore ctor/dtor rows.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/BfmeStringRecord0022074B.h"

class LocomotorStore
{
public:
	LocomotorStore();
	~LocomotorStore();
private:
	unsigned m_pad[3];
};

class INI;
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

// Retail's LocomotorStore field table at VA 0x00BE6AD0 (.rdata, 64 bytes: three
// records and the zero sentinel), transcribed from retail's own bytes.
extern const FieldParse LocomotorStoreFieldParse[] =
{
	{ "Name",       &INI::parseAsciiString, 0, 0x0 },
	{ "PluralName", &INI::parseAsciiString, 0, 0x4 },
	{ "Filter",     &iniParseObjectFilter,  0, 0x8 },
	{ 0, 0, 0, 0 }
};

void Rva00220FC4Parse(INI *ini, void *dummy, _STL::vector<BfmeStringRecord0022074B> *vec)
{
	LocomotorStore tmp;
	ini->initFromINI(&tmp, LocomotorStoreFieldParse);
	vec->push_back(reinterpret_cast<const BfmeStringRecord0022074B &>(tmp));
}
