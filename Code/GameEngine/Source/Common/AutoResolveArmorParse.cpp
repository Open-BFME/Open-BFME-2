// cl: /Oy- /DNDEBUG /MD /EHsc
// ?Rva00542B61Parse@@YAXPAVINI@@PAX11@Z, retail 0x00542B61, 64 bytes.
// INI field parser: initFromINI(instance) via rowed 0x0002DE78 with table
// g_00C69638, then if first dword of instance is 0 throw INIException code 8
// with retail literal "AutoResolveArmor entry in Object block: Armor name MUST
// be specified" (string_xrefs.tsv). Sibling weapon parser at 0x00542997 uses
// the same shape with its own table. Evidence: packet disassembly, caller
// 0x00542BA1 (4 __cdecl args, caller cleans 0x10), prev/next flags.
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };

#include "../../Include/Common/INI/INI.h"

extern "C" {
void __identifier("?Rva00427294Parse@@YAXPAVINI@@PAX11@Z")();
void __identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z")();
}
// The retail table at 0x00869638: 3 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_autoResolveArmorFieldParse[4] = {
	{ "Armor", (FieldParseProc)&__identifier("?Rva00427294Parse@@YAXPAVINI@@PAX11@Z"), 0, 0x0 },
	{ "RequiredUpgrades", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0x4 },
	{ "ExcludedUpgrades", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0x84 },
	{ 0, 0, 0, 0 }
};
extern "C" {
void __identifier("?Rva00419726Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z")();
}
// The retail table at 0x008695B0: 3 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_autoResolveWeaponFieldParse[4] = {
	{ "Weapon", (FieldParseProc)&__identifier("?Rva00419726Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "RequiredUpgrades", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0x4 },
	{ "ExcludedUpgrades", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0x84 },
	{ 0, 0, 0, 0 }
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
};

extern "C" void rva002f681_fill(void *e, int argCount, const char *format, ...);

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva00542B61ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva00542B61ThrowInfoAnchor rva00542B61ThrowInfoAnchor = { 0, 0, 0, 0 };

class Rva005429D7
{
public:
	Rva005429D7 *rva005429D7();
private:
	char m_pad[0x104];
};

struct BfmeFixedObject260
{
	char m_pad[0x104];
};

namespace _STL
{
template <typename T> class allocator;
template <typename T, typename A> class vector
{
public:
	void push_back(const T &x);
};
}

void __cdecl Rva00542B61Parse(INI *ini, void *formal, void *instance, void *a4)
{
	INIException exception;
	ini->initFromINI(instance, g_autoResolveArmorFieldParse);
	if (*(void **)instance == 0)
	{
		rva002f681_fill(&exception, 8, "AutoResolveArmor entry in Object block: Armor name MUST be specified");
		_CxxThrowException(&exception, (const _s__ThrowInfo *)&rva00542B61ThrowInfoAnchor);
	}
}

// Retail 0x00542BA1 61B. Append-then-parse: clear stack 0x104 record via rowed
// 0x005429D7, push_back rowed 0x00542AEA into vector at a3, then parse the new
// tail element (finish-0x104) via rowed 0x00542B61. Evidence: packet
// disassembly, callees all rowed, twin 0x00542B24 same shape.
void __cdecl Rva00542BA1Parse(INI *ini, void *formal, void *vecPtr, void *a4)
{
	Rva005429D7 armor;
	((_STL::vector<BfmeFixedObject260, _STL::allocator<BfmeFixedObject260> > *)vecPtr)->push_back(*(const BfmeFixedObject260 *)(const void *)armor.rva005429D7());
	Rva00542B61Parse(ini, formal, (char *)*(void **)((char *)vecPtr + 4) - 0x104, a4);
}

// ?Rva00542997Parse@@YAXPAVINI@@PAX11@Z, retail 0x00542997, 64 bytes.
// INI field parser twin of 0x00542B61: initFromINI(instance) via rowed 0x0002DE78
// with table g_00C695B0, then if first dword of instance is 0 throw INIException
// code 8 with retail literal "AutoResolveWeapon entry in Object block: Weapon
// name MUST be specified" (string_xrefs.tsv). Evidence: packet disassembly,
// caller 0x00542B56 (4 __cdecl args), prev/next flags, sibling armor parser.
void __cdecl Rva00542997Parse(INI *ini, void *formal, void *instance, void *a4)
{
	INIException exception;
	ini->initFromINI(instance, g_autoResolveWeaponFieldParse);
	if (*(void **)instance == 0)
	{
		rva002f681_fill(&exception, 8, "AutoResolveWeapon entry in Object block: Weapon name MUST be specified");
		_CxxThrowException(&exception, (const _s__ThrowInfo *)&rva00542B61ThrowInfoAnchor);
	}
}

// Retail 0x00542B24 61B. Append-then-parse twin of 0x00542BA1: clear stack 0x104
// record via rowed 0x005429D7, push_back rowed 0x00542AEA into vector at a3,
// then parse the new tail element (finish-0x104) via rowed 0x00542997.
// Evidence: chain packet (calls landed 0x00542997), callees all rowed.
void __cdecl Rva00542B24Parse(INI *ini, void *formal, void *vecPtr, void *a4)
{
	Rva005429D7 weapon;
	((_STL::vector<BfmeFixedObject260, _STL::allocator<BfmeFixedObject260> > *)vecPtr)->push_back(*(const BfmeFixedObject260 *)(const void *)weapon.rva005429D7());
	Rva00542997Parse(ini, formal, (char *)*(void **)((char *)vecPtr + 4) - 0x104, a4);
}
