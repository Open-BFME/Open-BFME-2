// cl: /EHs-c- /O1 /arch:SSE /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?Rva002E2612Parse@@YAXPAVINI@@PAX1PBX@Z 0x002E2612 125
// Evidence: REF slots AvailableTo Sides Sides; string Unknown Living World player type; find 0x002E18C3 via global 0x00DFF0B0; push_back 0x004DFCB0; getNextToken 0x0002DF97 plus getNextTokenOrNull 0x0002DEED; INIException 0x0002F681 plus TI1
#include <vector>
#include "ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
};

class ModuleData;

class Rva002E18C3Lookup
{
public:
	AsciiString *find(const AsciiString &name);
};

extern Rva002E18C3Lookup *Va00DFF0B0Lookup;

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

struct _s__ThrowInfo;

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

// ?Rva002E2612Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva002E2612Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken(0);
	while (token != 0)
	{
		union
		{
			AsciiString *as;
			const ModuleData *md;
		} found;
		{
			AsciiString key(token);
			found.as = Va00DFF0B0Lookup->find(key);
		}
		if (found.as == 0)
		{
			INIException e(3, "Unknown Living World player type '%s'", token);
			_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
			__assume(0);
		}
		((_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *)store)->push_back(found.md);
		token = ini->getNextTokenOrNull(0);
	}
}
