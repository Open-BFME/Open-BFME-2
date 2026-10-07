// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// ?Rva004E1C7BParse@@YAXPAVINI@@PAX@Z @0x004E1C7B 126B
// ParseSetPlayerControlOfArmyBlockAndAddToLivingWorldCampaignAct proc: throws INIException 3 on null
// ini or instance with retail literal then builds Rva004E1B72 record inline then INI::initFromINI with
// table g_00C61884 then append 0x0056656A. Evidence: table slot 0x0086CE34 neighbour
// SetPlayerControlOfArmy plus string ParseSetPlayerControlOfArmyBlock plus vtable 0x00C61DC4 plus DoXfer
// 0x004E1355 with GetSnapshotName SetPlayerControlOfArmy.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

struct _s__ThrowInfo;

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

extern const FieldParse g_00C61884;

#include "ascii_string.h"

class Rva004E1B72
{
public:
	Rva004E1B72() : m_bool08(false) {}
	virtual ~Rva004E1B72();
private:
	AsciiString m_str04;
	bool m_bool08;
};

class Rva0052BEF0
{
	char m_pad[0xC];
};

class Rva0056656AOwner
{
public:
	void append(const Rva0052BEF0 &record);
};

// ?Rva004E1C7BParse@@YAXPAVINI@@PAX@Z
void Rva004E1C7BParse(INI *ini, void *instance)
{
	if (ini && instance)
	{
		Rva004E1B72 record;
		ini->initFromINI(&record, &g_00C61884);
		((Rva0056656AOwner *)instance)->append(*(const Rva0052BEF0 *)&record);
	}
	else
	{
		INIException e(3, "ParseSetPlayerControlOfArmyBlockAndAddToLivingWorldCampaignAct::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
}
