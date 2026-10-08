// ?Rva0021A859Parse@@YAXHPAXPAVRva0014921EVector@@PBX@Z
// partial score=0.97 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /MD /EHs
// ?Rva00219453Validate@@YA_NHPBD@Z @0x00219453 90B CreateAHero stat validator throws INIException 3 callers 0x00220484
#include "ascii_string.h"
struct INIException
{
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
};

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

class Rva0040BAD0
{
public:
	int rva0040AAF8(int x);
};
// Data ledger 0x00A02F74 owns g_00E02F74 as Rva0040AAD5*; pin 0x0040AAF8 is a
// Rva0040BAD0 member on the same manager. View the ledger type as derived so
// the data ref keeps its ledger mangling while the call keeps its pin mangling.
class Rva0040AAD5 : public Rva0040BAD0
{
};
extern Rva0040AAD5 *g_00E02F74;

bool __cdecl Rva00219453Validate(int stat, const char *name)
{
	if (stat == 0)
	{
		INIException e(3, "%s has not been set in CreateAHeroSystem.ini.", name);
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	if (g_00E02F74->rva0040AAF8(stat) == 0)
	{
		INIException e(3, "%s is not a valid statInfo in CreateAHeroSystem.ini.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	return true;
}

// Native 0021A859..0021A90E is a cdecl FieldParse-shaped worker. It calls
// the existing 00149002 parser with a true byte's address, then checks every
// four-byte key against the same award-manager lookup used above. The native
// error string establishes stat validation; the original parser name is open.
// Preserve the existing address-named worker's four-word ABI: its fourth word
// transports the flag pointer. No application record layout is inferred here.
class Rva0014921EVector
{
public:
	int *m_begin;
	int *m_end;
};
void rva00149002(int a, int b, Rva0014921EVector *buffer, int d);

enum NameKeyType { NAMEKEY_INVALID = 0, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// ?Rva0021A859Parse present-unmatched
void __cdecl Rva0021A859Parse(int input, void *, Rva0014921EVector *keys, const void *)
{
	bool flag = true;
	rva00149002(input, 0, keys, reinterpret_cast<int>(&flag));
	for (unsigned int i = 0; i < static_cast<unsigned int>(keys->m_end - keys->m_begin); ++i)
	{
		if (g_00E02F74->rva0040AAF8(keys->m_begin[i]) == 0)
		{
			int *volatile &begin = keys->m_begin;
			AsciiString name(TheNameKeyGenerator->keyToName(static_cast<NameKeyType>(begin[i])));
			INIException e(3, "The Stat %s does not exist in the AwardSystemManager.", name.str());
			_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
			__assume(0);
		}
	}
}
