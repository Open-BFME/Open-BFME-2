// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?Rva00219453Validate@@YA_NHPBD@Z @0x00219453 90B CreateAHero stat validator throws INIException 3 callers 0x00220484
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
