// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// ?Rva002E1D22Parse@@YAXPAVINI@@PAX@Z @0x002E1D22 241B ParseLivingWorldPlayer free function.
// Evidence: error literals ParseLivingWorldPlayer::No name specified at 0x00804A58
// and Invalid data passed in at 0x008049A4 via INIException 0x0002F681 plus
// _CxxThrowException with TI1?AVINIException@@ at 0x008FE2FC; FieldParse table
// g_00C049D8 via initFromINI 0x0002DE78; getNextToken 0x0002DF97 plus StringBase
// set 0x000055F5 with isEmpty inline; lookups 0x002E18C3 via g_00DFF0B0 and
// g_00E03140 with bool gate; dedup append 0x0052D394; record ctor 0x002E0EF7
// plus dtor 0x002E0F1E same 0x28 layout as Rva002E0A0A copy ctor plus Snapshot
// base 0x00BBB554; callers none; prev/next share /O1 /EHsc.
#include "ascii_string.h"
#include "unicode_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva002E1D22ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva002E1D22ThrowInfoAnchor rva002E1D22ThrowInfoAnchor = { 0, 0, 0, 0 };

extern const FieldParse g_00C049D8;

class Rva002E18C3Lookup
{
public:
	AsciiString *find(const AsciiString &name);
};

extern class Rva002E18C3Lookup *Va00DFF0B0Lookup;
extern class Rva002E18C3Lookup *Va00E03140Lookup;

class Rva002E0F1E
{
public:
	virtual ~Rva002E0F1E();
	UnicodeString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	AsciiString m_10;
	AsciiString m_14;
	int m_18;
	int m_1c;
	int m_20;
	bool m_24;
};

class Rva002E0EF7 : public Rva002E0F1E
{
public:
	Rva002E0EF7();
};

class Rva002E0A0A
{
	char opaque[40];
};

class LivingWorldCampaign
{
public:
	void AddPlayer(const Rva002E0A0A &arg);
};

void Rva002E1D22Parse(INI *ini, void *instance)
{
	if (ini == 0 || instance == 0)
	{
		INIException e(3, "ParseLivingWorldPlayer::Invalid data passed in.");
		_CxxThrowException(&e, (const _s__ThrowInfo *)&rva002E1D22ThrowInfoAnchor); __assume(0);
	}
	Rva002E0EF7 record;
	const char *tok = ini->getNextToken(0);
	record.m_08 = tok;
	if (record.m_08.getLength() == 0)
	{
		INIException e(3, "ParseLivingWorldPlayer::No name specified.");
		_CxxThrowException(&e, (const _s__ThrowInfo *)&rva002E1D22ThrowInfoAnchor); __assume(0);
	}
	ini->initFromINI(&record, &g_00C049D8);
	AsciiString *found = Va00DFF0B0Lookup->find(record.m_0c);
	if (found == 0)
		goto done;
	if (record.m_24)
		goto append;
	{
		AsciiString *found2 = Va00E03140Lookup->find(record.m_10);
		if (found2 == 0)
			goto done;
	}
append:
	((LivingWorldCampaign *)instance)->AddPlayer(*(const Rva002E0A0A *)&record);
done:;
}
