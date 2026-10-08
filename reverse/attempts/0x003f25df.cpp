// ?Rva003F25DF@@YAXPAX000@Z
// partial score=0.8 date=2026-10-08
// cl: /GX /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// stlport
//
// ?Rva003F25DF@@YAXPAXPAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@PAX@Z
// retail 0x003F25DF (202B), cdecl, four pointer arguments. Appends a new
// two-string pair to the list at the third argument, hands the first and
// second arguments plus that pair and the fourth argument to the rowed-by-address
// helper 0x003F005F (cdecl, pinned), then compares the new pair against every
// earlier pair: a matching first string throws the World duplicate message and a
// matching second string throws the RTS duplicate message, both naming the new
// pair's first string. Names are address-derived; the pair layout is target fact.
#include "ascii_string.h"

#include <vector>

class ModuleData;
class INI;

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

// Address-named helper pinned at retail 0x003F005F (cdecl, four pointer arguments).
void Rva003F005F(void *a, void *b, void *c, void *d);

// Retail literals at VA 0x00BBAC1C (empty text), 0x00C36F58 and 0x00C36F10 (the
// two duplicate messages), named by address and pinned in reverse/symbols.csv.
extern const char g_00BBAC1C[];
extern const char g_00C36F58[];
extern const char g_00C36F10[];

struct Rva003F25DFPair
{
	AsciiString first;
	AsciiString second;
};

// AsciiString text as str() reads it: the first word holds the Header pointer,
// the text starts 8 bytes into the header, and an empty string is the retail
// empty literal at 0x00BBAC1C.
static const char *Rva003F25DFText(const AsciiString &s)
{
	const char *header = *(const char *const *)&s;
	return header ? header + 8 : g_00BBAC1C;
}

typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > Rva003F25DFList;

void Rva003F25DF(void *a1, void *a2, void *list, void *a4)
{
	Rva003F25DFList *vec = (Rva003F25DFList *)list;
	vec->push_back((const ModuleData *)new Rva003F25DFPair);
	Rva003F005F(a1, a2, (void *)*(vec->end() - 1), a4);

	const ModuleData *const *last = vec->end() - 1;
	for (const ModuleData *const *it = vec->begin(); it != last; ++it)
	{
		Rva003F25DFPair *pair = (Rva003F25DFPair *)*it;
		Rva003F25DFPair *newest = (Rva003F25DFPair *)*last;
		if (pair->first.compare(newest->first) == 0)
			throw INIException(3, g_00C36F58, Rva003F25DFText(newest->first));
		if (pair->second.compare(newest->second) == 0)
			throw INIException(3, g_00C36F10, Rva003F25DFText(newest->second));
	}
}
