// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ?Rva00202BB2Parse@@YAXPAVINI@@@Z, retail 0x00202BB2, 126 bytes.
// Chain lane: calls 0x00202B6C (Rva00202B6C::rva00202B6C, landed just before),
// which made every callee rowed. Parses one INI token into a local
// AsciiString, maps it through the six-entry LOD table, and runs
// INI::initFromINI on the matching 0x4C-sized preset entry. Retail facts:
// - Free __cdecl function: ecx is loaded from the stack ([ebp+8]), never
//   preloaded by the caller, and the epilogue is a plain `ret`.
// - The by-value pass to rva00202B6C emits the compiler-generated
//   stack-copy construction through the PINNED StringBase copy ctor
//   (0x000365F0); the local is destroyed at the end through the ROWED
//   StringBase dtor (0x00036410), the trailing releaseBuffer call.
// - Global 0x009FE144 is spelled exactly as the sibling TU owns it
//   (TheRva00DFE144); the method call casts to Rva00202B6C* at the call
//   site because the rowed method ignores `this`.
// - FieldParse table at 0x007E3308 is DIR32-masked.

typedef int Int;
typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *dst, const FieldParse *table);
};

class Rva00202B6C
{
public:
	Int rva00202B6C(AsciiString name);
};

struct Rva00DFE144Globals;
extern Rva00DFE144Globals *TheRva00DFE144;
extern const FieldParse g_007E3308[];

// ?Rva00202BB2Parse@@YAXPAVINI@@@Z
void Rva00202BB2Parse(INI *ini)
{
	AsciiString name;
	name.set(ini->getNextToken(0));
	if (TheRva00DFE144 != 0)
	{
		Int idx = ((Rva00202B6C *)TheRva00DFE144)->rva00202B6C(name);
		if (idx != -1)
			ini->initFromINI((char *)TheRva00DFE144 + idx * 0x4c, g_007E3308);
	}
}
