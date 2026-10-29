// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /Oy-
// stlport
//
// ??0Rva003F8728@@QAE@HH@Z @0x003F86F9 47B.
// Ctor of unknown class with vtable 0x00837314: stores two int args at +4/+8,
// then constructs vector<BfmeE16> at +0xC via rowed Vector_base 0x00211E58,
// then sets dword at +0x18 to -1.
// Evidence: leaf lane; callees all rowed; caller Parse body at 0x003F90E4;
// layout matches sibling Rva003F877E ctor (vector at +0xC, same flags);
// base-before-vtable order proves 2-int base; ret 8 with ecx=this proves HH.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"

struct Base003F86F9
{
	Base003F86F9(int a, int b) : m_04(a), m_phase(b) {}
	int m_04;
	int m_phase;
};

class Rva003F8728 : public Base003F86F9
{
public:
	Rva003F8728(int a, int phase);
	virtual ~Rva003F8728();
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0C;
	int m_18;
};

Rva003F8728::Rva003F8728(int a, int phase) : Base003F86F9(a, phase), m_0C(), m_18(-1)
{
}

// Rva003F90E4Parse: native boundary 0x003F90E4..0x003F91A3; 191B
// plus the compiler INT3 at +191 (192B emitted). Retail assertion names
// LogicTurnPhase::ParseINI; the original declaration and unused trailing
// parameters remain unproven, so retain an opaque cdecl/accessed-prefix name.
// Retail accesses holder +4, creates the rowed 28B object with two int args,
// then uses INI initFromINI and holder registration; these are target facts.
// No donor source: reconstructed from retail calls, accesses and EH graph.
// Canonical nontrivial INIException copying lets the compiler construct the
// thrown object directly at EBP-0x14; class type, destructor and deep-copy
// metadata match retail and the existing INIException implementation.
#include "ascii_string.h"
class INI;
typedef void (*FieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse {
 const char *token;
 FieldParseProc parse;
 const void *userData;
 int offset;
};
class INI {
public:
 AsciiString getNextQuotedAsciiString();
 int scanIndexList(const char *,const char *const *);
 void initFromINI(void *,const FieldParse *);
};
class ModuleData;
struct Rva003F9004 {
 char pad[4]; int field04;
 void rva003F9004(const ModuleData *);
};
class INIException {
public:
 char *message; int error;
 INIException(int,const char *,...);
 ~INIException();
 INIException(const INIException &);
 INIException &operator=(const INIException &);
};
// Descriptive data roles; original table names remain unproven.
extern const char *const g_logicTurnPhaseNames[8] = {
 "Planning", "MoveArmies", "ResolveBattles", "FakePhaseOne",
 "PlanRetreats", "RetreatArmies", "Complete", 0
};
namespace LivingWorldTutorial {
 class LogicTurn { public: static void ParseINI(INI *, Rva003F9004 *); };
}
// Retail C374EC: one Session callback followed by the complete null entry.
// The callback's two accessed arguments are the existing row's proven ABI;
// the INI dispatcher supplies the usual four arguments to FieldParseProc.
extern const FieldParse g_logicTurnPhaseFields[2] = {
 { "Session", reinterpret_cast<FieldParseProc>(&LivingWorldTutorial::LogicTurn::ParseINI), 0, 0 },
 { 0, 0, 0, 0 }
};
// Retail proves two accessed cdecl arguments; no trailing-parameter claim.
void Rva003F90E4Parse(INI *ini,Rva003F9004 *outer) {
 if(!ini || !outer) throw INIException(3,"Invalid data in LogicTurnPhase::ParseINI");
 AsciiString token=ini->getNextQuotedAsciiString();
 int phase=ini->scanIndexList(token.str(),g_logicTurnPhaseNames);
 Rva003F8728 *created=new Rva003F8728((outer->field04?outer->field04:outer->field04),phase);
 ini->initFromINI(created,g_logicTurnPhaseFields);
 outer->rva003F9004(reinterpret_cast<const ModuleData*>(created));
}
