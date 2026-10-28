// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// INI field-parse callbacks from .text gaps no ledger row covers (seat-3
// batch L; see GapBodiesS3A.cpp). Retail bytes establish every shape; the
// error text is retail's own literal.
#include "ascii_string.h"
#include "unicode_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps);				// 0x0002DF97
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);	// 0x0002EF56
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);	// 0x0002E850
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);	// 0x0002EFC0
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);	// 0x00338B30
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);				// 0x00148E1A
};

extern NameKeyGenerator *TheNameKeyGenerator;

class InGameUI
{
public:
	bool rva0029FCD9(const char *cursorName);				// 0x0029FCD9
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void __cdecl message(UnicodeString format, ...);
};

extern InGameUI *TheInGameUI;

// The release-build crash report stream (debug_purecall.cpp's view).
class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;
void _bfme_debugRecordCallsite(int kind);					// 0x00038790
bool bfmeRva000387C0();										// 0x000387C0

// --- 0x0035AED4 (142B): parse a radius-cursor name into its name key; a name
// InGameUI does not know (rowed-by-pin 0x0029FCD9) raises the crash report
// and leaves the store untouched.
void rva0035AED4(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(0);
	if (TheInGameUI && !TheInGameUI->rva0029FCD9(token))
	{
		if (bfmeRva000387C0())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "Error, radius cursor \"" << token << "\" doesn't seem to exist in InGameUI.ini").CrashDone(2);
		}
		return;
	}
	*(NameKeyType *)store = TheNameKeyGenerator->nameToKey(token);
}

// --- 0x0041516C (55B): when own slot 2 allows it, announce the crowd-response
// reload on TheInGameUI (retail's literal) and latch +0x20; returns the latch.
class Rva0041516C
{
public:
	virtual void s0();
	virtual void s1();
	virtual bool s2();
	virtual bool rva0041516C(int unused);
private:
	char m_pad04[0x20 - 4];
	bool m_reloaded;										// +0x20
};

bool Rva0041516C::rva0041516C(int)
{
	if (s2())
	{
		TheInGameUI->message(UnicodeString((const unsigned short *)L"RIF: CrowdResponses reloaded"));
		m_reloaded = true;
	}
	return m_reloaded;
}

// --- 0x005114C6 (122B, EH): the Apt messenger factory: the online messenger
// (rowed AptMessengerOnline ctor 0x005AEF6B) when GameSpy is up, else the
// LAN messenger (rowed 0x005AE3A6) when TheLAN exists; 0x2A4 bytes each.
class GameSpyInfoInterface;
class LANAPI;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern LANAPI *TheLAN;

class Rva005114C6Messenger
{
public:
	virtual void m0();
};

class AptMessengerOnline : public Rva005114C6Messenger
{
public:
	AptMessengerOnline(void *owner);						// 0x005AEF6B
private:
	char m_pad[0x2A4 - 4];
};

class Rva005AE30A : public Rva005114C6Messenger
{
public:
	Rva005AE30A(void *owner);								// 0x005AE3A6
private:
	char m_pad[0x2A4 - 4];
};

class Rva005114C6
{
public:
	virtual Rva005114C6Messenger *createMessenger(void *owner);
};

Rva005114C6Messenger *Rva005114C6::createMessenger(void *owner)
{
	Rva005114C6Messenger *messenger = 0;
	if (TheGameSpyInfo)
		messenger = new AptMessengerOnline(owner);
	else if (TheLAN)
		messenger = new Rva005AE30A(owner);
	if (messenger)
		return messenger;
	return 0;
}

// --- 0x00419BB8 (19B): append the third argument to the +0x08 text while the
// +0x04 flag is set.
class Rva00419BB8
{
public:
	virtual void rva00419BB8(int a, int b, const char *text);
private:
	bool m_enabled;											// +0x04
	char m_pad05[3];
	AsciiString m_text;										// +0x08
};

void Rva00419BB8::rva00419BB8(int, int, const char *text)
{
	if (m_enabled)
		((StringBase<char> *)&m_text)->concat(text);
}

// --- 0x004FA5B8 (28B): a module data's field-parse builder: the base's
// (folded, empty) builder, then the QueueSize / ArmyToSpawn table at
// 0x00C63344 (retail's field names).
class Xfer;

class FXParticleSystem
{
public:
	class EmissionVelocityInfo
	{
	public:
		virtual void DoXfer(Xfer &xfer);					// 0x0047A69C (the folded empty body)
	};
};

struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *table, unsigned int offset);	// 0x0002BC6E
};

// 0x004E3BD8 is rowed with its own (INI *, int, vector<BfmePod88> *) signature
// (LivingWorldCampaignObjects.cpp); the table stores it as a parse callback.
struct BfmePod88;
namespace _STL { template <class T> class allocator; template <class T, class A> class vector; }
void rva004E3BD8(INI *ini, int instance, _STL::vector<BfmePod88, _STL::allocator<BfmePod88> > *store);
typedef void (*Rva004E3BD8Parse)(INI *, void *, void *, const void *);

class Rva004FA5B8 : public FXParticleSystem::EmissionVelocityInfo
{
public:
	virtual void buildFieldParse(MultiIniFieldParse &p);
private:
	static const FieldParse s_dataFieldParse[];
};

const FieldParse Rva004FA5B8::s_dataFieldParse[] =
{
	{ "QueueSize", INI::parseInt, 0, 0x14 },
	{ "ArmyToSpawn", (Rva004E3BD8Parse)rva004E3BD8, 0, 0x08 },
	{ 0, 0, 0, 0 }
};

void Rva004FA5B8::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	FXParticleSystem::EmissionVelocityInfo::DoXfer((Xfer &)multiIniFieldParse);
	multiIniFieldParse.add(s_dataFieldParse, 0);
}

// --- 0x00584C69 / 0x00587217 (19B each): module-data field-parse builders
// adding the follow-leader table 0x00C6FD28 and the facing / idle-activation
// table 0x00C6FE88 (retail's field names).
void Rva000B9468Parse(INI *ini, void *instance, void *store, const void *userData);	// 0x000B9468

class Rva00584C69
{
public:
	virtual void buildFieldParse(MultiIniFieldParse &p);
private:
	static const FieldParse s_dataFieldParse[];
};

const FieldParse Rva00584C69::s_dataFieldParse[] =
{
	{ "FollowLeader", INI::parseBool, 0, 0x04 },
	{ "DistanceToActiveLeader", INI::parseReal, 0, 0x08 },
	{ "DistanceToPassiveLeader", INI::parseReal, 0, 0x0C },
	{ 0, 0, 0, 0 }
};

void Rva00584C69::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	multiIniFieldParse.add(s_dataFieldParse, 0);
}

class Rva00587217
{
public:
	virtual void buildFieldParse(MultiIniFieldParse &p);
private:
	static const FieldParse s_dataFieldParse[];
};

const FieldParse Rva00587217::s_dataFieldParse[] =
{
	{ "FacingBonus", INI::parseReal, 0, 0x04 },
	{ "AngleLimitCos", INI::parseReal, 0, 0x08 },
	{ "InnerRange", INI::parseReal, 0, 0x0C },
	{ "OuterRange", INI::parseReal, 0, 0x10 },
	{ "OuterRangeBuildings", INI::parseReal, 0, 0x14 },
	{ "IdleModelConditions", Rva000B9468Parse, 0, 0x18 },
	{ "DelayUntilIdle", INI::parseDurationUnsignedInt, 0, 0x64 },
	{ "DelayRandomActivateMin", INI::parseDurationUnsignedInt, 0, 0x68 },
	{ "DelayRandomActivateMax", INI::parseDurationUnsignedInt, 0, 0x6C },
	{ 0, 0, 0, 0 }
};

void Rva00587217::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	multiIniFieldParse.add(s_dataFieldParse, 0);
}

// --- 0x00343EE5 (21B): 1 when the pinned 0x00343DD8 test fails, else 0.
bool rva00343DD8(void *a, void *b);							// 0x00343DD8

int inWeaponRangeObject(void *thisState, void *b)
{
	return !rva00343DD8(thisState, b);
}
