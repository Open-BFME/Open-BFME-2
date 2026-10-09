// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
// ?Rva00415481Parse@@YAXPAVINI@@PAX1PBX@Z @0x00415481 185B.
// INI field parser of the "CrowdResponseKey" entry (FieldParse row at
// 0x009BF278: name 0x00C0F248 parser VA 0x00815481 offset 0x49C) and its only
// reference. Throws INIException(8) when TheCrowdResponseStore (0x00A0307C)
// is not set up yet; otherwise reads one token into an AsciiString and looks
// it up through the store's rowed 0x003EF328 find; the found entry (or null)
// goes to the store slot and an unknown non-"None" name throws
// INIException(8 "Unknown CrowdResponse name '%s'"). Texts 0x0083A238 and
// 0x0083A218 sit next to the CrowdResponse block parser 0x00415D33
// (CrowdResponseBlockParse.cpp) which shares the ThrowInfo 0x00CFE2FC and the
// direct _CxxThrowException of the constructed local. Callees: rowed
// INIException ctor 0x0002F681 getNextToken 0x0002DF97 StringBase(const
// char*) 0x00037BA0 isNone 0x00037DE0 and releaseBuffer 0x00036410.
// Original name unknown; WorldBuilder twin 0xC65F60 is unnamed.
#include "ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps);
};

// The store's lookup (Rva003EF328Lookup.cpp): finds the key in the bucket
// table at +0x0C and returns the entry payload or null.
class Rva003EF328
{
public:
	void *rva003EF328(const AsciiString *key);
};

class Rva0022A809Subsystem;
extern Rva0022A809Subsystem *TheCrowdResponseStore;

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

void __cdecl Rva00415481Parse(INI *ini, void *instance, void *store, const void *userData)
{
	if (TheCrowdResponseStore == 0)
	{
		INIException e(8, "Attemping to parse a CrowdResponse name before TheCrowdResponseStore is set up");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	AsciiString name(ini->getNextToken(0));
	void *response = ((Rva003EF328 *)TheCrowdResponseStore)->rva003EF328(&name);
	*(void **)store = response;
	if (response == 0 && !name.isNone())
	{
		INIException e(8, "Unknown CrowdResponse name '%s'", name.str());
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
}
