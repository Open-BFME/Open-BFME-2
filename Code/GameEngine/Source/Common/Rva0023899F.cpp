// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0023899FParse@@YAXPAVINI@@HPAH@Z @0x0023899F 193B
// No callers; cdecl void(INI*, int*) parses EASY/NORMAL/HARD/BRUTAL to 0-3
// else throws INIException 3. Honest address name.
#include "ascii_string.h"

class INI
{
public:
	AsciiString getNextAsciiString();
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva0023899FThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva0023899FThrowInfoAnchor rva0023899FThrowInfoAnchor = { 0, 0, 0, 0 };

void __cdecl Rva0023899FParse(INI *ini, int unused, int *out)
{
	AsciiString tok = ini->getNextAsciiString();
	if (((const StringBase<char> &)tok).compare("EASY") == 0)
		*out = 0;
	else if (((const StringBase<char> &)tok).compare("NORMAL") == 0)
		*out = 1;
	else if (((const StringBase<char> &)tok).compare("HARD") == 0)
		*out = 2;
	else if (((const StringBase<char> &)tok).compare("BRUTAL") == 0)
		*out = 3;
	else
	{
		INIException exc(3, "invalid GameDifficulty data: should be one of (EASY, NORMAL, HARD, BRUTAL)");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva0023899FThrowInfoAnchor); __assume(0);
	}
}
