// Native 003F25DF..003F26A9, WB 0103AE30 corresponding parse-list.
// Fix prior bank with exact retail literals and correct RTS second-string message.
// cl: /O1 /G7 /Oy- /GX /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// stlport
//
// ?Rva003F25DF@@YAXPAX000@Z
// retail 0x003F25DF (202B), cdecl, four pointer arguments. Appends a new
// two-string pair to the list at the third argument, hands the first and
// second arguments plus that pair and the fourth argument to the rowed-by-address
// helper 0x003F005F (cdecl and independently byte verified), then compares the new pair against every
// earlier pair: a matching first string throws the World duplicate message and a
// matching second string throws the RTS duplicate message, naming the corresponding new string. Names are address-derived; the pair layout is target fact.
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

// Address-derived helper: native direct call to retail 0x003F005F (cdecl, four pointer arguments).
void Rva003F005F(void *a, void *b, void *c, void *d);

struct Rva003F25DFPair
{
	AsciiString first;
	AsciiString second;
};

static inline bool RvaPairEqual(const AsciiString &a, const AsciiString &b)
{
 return ((const StringBase<char> *)&a)->compare(*(const StringBase<char> *)&b) == 0;
}

typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > Rva003F25DFList;

void Rva003F25DF(void *a1, void *a2, void *list, void *a4)
{
	Rva003F25DFList *vec = (Rva003F25DFList *)list;
	vec->push_back((const ModuleData *)new Rva003F25DFPair);
	Rva003F005F(a1, a2, (void *)*(vec->end() - 1), a4);

	const ModuleData *const *it = vec->begin();
	const ModuleData *const *last = vec->end() - 1;
	for (; it != last; ++it)
	{
		if (RvaPairEqual(((Rva003F25DFPair *)*it)->first, ((Rva003F25DFPair *)*last)->first))
			throw INIException(3, "Duplicate World Player names '%s' in PlayerWorldToMapMatchingData vector", ((Rva003F25DFPair *)*last)->first.str());
		if (RvaPairEqual(((Rva003F25DFPair *)*it)->second, ((Rva003F25DFPair *)*last)->second))
			throw INIException(3, "Duplicate RTS Player names '%s' in PlayerWorldToMapMatchingData vector", ((Rva003F25DFPair *)*last)->second.str());
	}
}
