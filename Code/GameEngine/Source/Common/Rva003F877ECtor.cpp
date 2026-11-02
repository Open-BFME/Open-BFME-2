// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /Oy-
// stlport
//
// ??0Rva003F87A9@@QAE@HH@Z @0x003F877E 43B.
// The class is Rva003F87A9: vtable 0x00C37318 slot 0 is ??_GRva003F87A9
// (0x003F8DDC), which calls the rowed dtor 0x003F87A9 (Rva003F87A9Dtor.cpp).
// Ctor of unknown class with vtable 0x00837318: stores two int args at +4/+8,
// then constructs vector<BfmeE16> at +0xC via rowed Vector_base 0x00211E58.
// Evidence: leaf lane; callees all rowed; caller Parse body at 0x003F91A4;
// layout matches sibling Rva003F8ED6 ctor (vector at +0xC, same flags);
// base-before-vtable order proves 2-int base; ret 8 with ecx=this proves HH.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

struct Base003F877E
{
	Base003F877E(int a, int b) : m_04(a), m_08(b) {}
	int m_04;
	int m_08;
};

class Rva003F87A9 : public Base003F877E
{
public:
	Rva003F87A9(int a, int b);
	virtual ~Rva003F87A9();
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0C;
};

Rva003F87A9::Rva003F87A9(int a, int b) : Base003F877E(a, b), m_0C()
{
}
// Rva003F91A4Parse: native 0x003F91A4..0x003F9258 including INT3 tail.
// The retail assertion names LogicTurn::ParseINI; original declaration and
// unused trailing arguments remain unproven. Keep the opaque cdecl prefix.
// Target evidence: scanInt token; 24B allocation; constructor receives the
// holder pointer bits and scanned int; INI field table then holder append.
// The constructor's int-typed first argument is the existing opaque ABI,
// not proof that the original source represented that pointer as an int.
// Reconstructed from retail; canonical INIException copying gives native
// direct exception construction. The EH and throw-data graphs are verified.
#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAUBfmeE16@@U1@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAEXPA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE16;
namespace _STL { template <> void _STLP_alloc_proxy<BfmeE16 *, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16 *, size_t); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UBfmeE16@@@_STL@@QBEXPAUBfmeE16@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE16;
namespace _STL { template <> void allocator<BfmeE16>::deallocate(BfmeE16 *, size_t) const; }
class INI;
typedef void (*FieldParseProc)(INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
class ModuleData;
struct Rva003F9048 {
 void rva003F9048(const ModuleData *);
};
// LogicTurn's field table (retail .rdata VA 0xC37514, read from the image):
// "Phase" -> the rowed phase parser 0x003F90E4, no user data, offset 0, then
// the null terminator. Descriptive name; the original remains unproven.
struct Rva003F9004;
void Rva003F90E4Parse(INI *ini, Rva003F9004 *outer);
extern const FieldParse g_logicTurnFields[2] = {
 { "Phase", (FieldParseProc)&Rva003F90E4Parse, 0, 0 },
 { 0, 0, 0, 0 }
};
// Retail proves two accessed cdecl arguments; no trailing-parameter claim.
void Rva003F91A4Parse(INI *ini,Rva003F9048 *outer) {
 if(!ini || !outer) throw INIException(3,"Invalid data in LogicTurn::ParseINI");
 AsciiString token=ini->getNextQuotedAsciiString();
 int phase=ini->scanInt(token.str());
 Rva003F87A9 *created=new Rva003F87A9(reinterpret_cast<int>(outer),phase);
 ini->initFromINI(created,g_logicTurnFields);
 outer->rva003F9048(reinterpret_cast<const ModuleData*>(created));
}
