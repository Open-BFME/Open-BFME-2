// cl: /GX- /DNDEBUG /MD
// platformsdk
//
// More thin FieldParse procs (original names unproven; address names):
//   0x004DC674 34B ModelConditions / ModelConditionsClear (0x00C61480 /
//       0x00C61490): the store's 0x4C-byte flag set self-parses through the
//       rowed Rva000B9468Parse, then is copied to store + 0x4C.
//   0x001DEA65 49B OtherEvaEventsToBlock (0x00BDC0E8): each token's Eva event
//       index (pinned Eva lookup 0x001DE9C4 on TheEva) is appended to the
//       4-byte enum vector at the store (push_back fold 0x002E01C6).
//   0x00339D26 49B Buildings (0x00C36EE0): each token's index in the name
//       table passed as userData is appended to the 4-byte vector at the
//       store (push_back fold 0x004DFCB0).
//   0x00200893 53B LinePart (0x00BE29FC): news a ShellMenuSchemeLine (rowed
//       ctor 0x002004A5; no unwinding), fills it from table 0x00BE2AA0 and
//       hands it to the rowed guarded list push 0x002007A7.

#include <windows.h>
#include <new>

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/FieldParse.h"

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanIndexList(const char *token, const char *const *names);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseICoord2D(INI *, void *, void *, const void *);
	static void parseColorInt(INI *, void *, void *, const void *);
	static void parseInt(INI *, void *, void *, const void *);
};

void Rva000B9468Parse(INI *ini, void *instance, void *store, const void *userData);

struct Rva004DC674Flags
{
	unsigned int m_bits[19];
};

enum EvaMessage
{
	EVA_Invalid = -1
};

class Eva
{
public:
	int iniScanEvaEventID(const char *name);
};
extern Eva *TheEva;

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<EvaMessage, allocator<EvaMessage> >
{
public:
	void push_back(const EvaMessage &x);
private:
	EvaMessage *m_start;
	EvaMessage *m_finish;
	EvaMessage *m_endOfStorage;
};
template <> class vector<long, allocator<long> >
{
public:
	void push_back(const long &x);
private:
	long *m_start;
	long *m_finish;
	long *m_endOfStorage;
};
}

// The retail table at 0x007E2AA0: 4 entries and the null terminator; every parser is rowed.
extern const FieldParse g_00BE2AA0[5] = {
	{ "StartPosition", (FieldParseProc)&INI::parseICoord2D, 0, 0x0 },
	{ "EndPosition", (FieldParseProc)&INI::parseICoord2D, 0, 0x8 },
	{ "Color", (FieldParseProc)&INI::parseColorInt, 0, 0x14 },
	{ "Width", (FieldParseProc)&INI::parseInt, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

class ShellMenuSchemeLine
{
public:
	ShellMenuSchemeLine(void);
private:
	unsigned char m_unreconstructed_00[0x18];
};

class Gen_00581350
{
public:
	void m(void *line);
};

// ?Rva004DC674Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004DC674Parse(INI *ini, void *, void *store, const void *)
{
	Rva000B9468Parse(ini, NULL, store, NULL);
	((Rva004DC674Flags *)store)[1] = ((Rva004DC674Flags *)store)[0];
}

// ?Rva001DEA65Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva001DEA65Parse(INI *ini, void *, void *store, const void *)
{
	const char *token;
	while ((token = ini->getNextTokenOrNull()) != NULL)
	{
		EvaMessage message = (EvaMessage)TheEva->iniScanEvaEventID(token);
		((_STL::vector<EvaMessage, _STL::allocator<EvaMessage> > *)store)->push_back(message);
	}
}

// ?Rva00339D26Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00339D26Parse(INI *ini, void *, void *store, const void *userData)
{
	const char *token;
	while ((token = ini->getNextTokenOrNull()) != NULL)
	{
		long index = ini->scanIndexList(token, (const char *const *)userData);
		((_STL::vector<long, _STL::allocator<long> > *)store)->push_back(index);
	}
}

// ?Rva00200893Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00200893Parse(INI *ini, void *instance, void *, const void *)
{
	ShellMenuSchemeLine *line = new ShellMenuSchemeLine;
	ini->initFromINI(line, g_00BE2AA0);
	((Gen_00581350 *)instance)->m(line);
}
