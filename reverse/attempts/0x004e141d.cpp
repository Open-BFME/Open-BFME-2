// ?Rva004E141DParse@@YAXPAVINI@@PAX@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
//
// ?Rva004E141DParse@@YAXPAVINI@@PAX@Z @0x004E141D 110B
// ParseMoveCameraBlock proc: throws INIException 3 on null ini or instance
// with retail literal then constructs Rva004E13EB record 0x004E13EB then
// INI::initFromINI 0x0002DE78 with table g_00C61940 then append 0x00566547.
// Evidence: table slot 0x0086CDC4 neighbour MoveCamera plus string
// ParseMoveCameraBlock plus sibling LivingWorld append thunks.

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

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

extern const FieldParse g_00C61940;

class Rva004E13EB
{
public:
	Rva004E13EB();
	virtual ~Rva004E13EB() { }
	int m04;
	float m08;
	float m0c;
	float m10;
	float m14;
	int m18;
	unsigned char m1c;
};

class Rva003A6F70
{
	char m_pad[0x20];
};

class Rva00566547Owner
{
public:
	void append(const Rva003A6F70 &record);
};

// ?Rva004E141DParse@@YAXPAVINI@@PAX@Z
void Rva004E141DParse(INI *ini, void *instance)
{
	if (!ini || !instance)
	{
		INIException e(3, "ParseMoveCameraBlock::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@")); __assume(0);
	}
	Rva004E13EB record;
	ini->initFromINI(&record, &g_00C61940);
	((Rva00566547Owner *)instance)->append(*(const Rva003A6F70 *)&record);
}
