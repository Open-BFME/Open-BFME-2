// ?parseUpgradeDefinition@UpgradeCenter@@SAXPAVINI@@@Z
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?parseUpgradeDefinition@UpgradeCenter@@SAXPAVINI@@@Z @0x0026FA05 249B
// UpgradeCenter::parseUpgradeDefinition donor ZH Upgrade.cpp parses upgrade name via getNextToken plus nameToKey plus find plus newUpgrade plus initFromINI. Evidence: block-parse node VA 0x00DB94F8 token Upgrade parse 0x0026FA05 into theBlockParseList; rowed getNextToken 0x0002DF97 nameToKey 0x0009FA65 findUpgradeByKey 0x0026EEB8 newUpgrade 0x0026F952 unlinkUpgrade 0x0026EEF2 vector push_back 0x004DFCB0 initFromINI 0x0002DE78 Rva0026F684 ctor 0x0026F5B3 dtor 0x0026F684 releaseBuffer 0x00036410; FieldParse table g_00BFA6E8; loadType at INI+0x08.
#include "ascii_string.h"
#include <vector>

struct FieldParse;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct Rva004DFCB0Element
{
	unsigned word0;
	Rva004DFCB0Element &operator=(const Rva004DFCB0Element &other)
	{
		if (this != &other)
			word0 = other.word0;
		return *this;
	}
	bool operator<(const Rva004DFCB0Element &) const;
	bool operator==(const Rva004DFCB0Element &) const;
};

class UpgradeTemplate
{
public:
	char m_pad00[0x38];
	int m_maskBitIndex; // +0x38
	char m_pad3C[0x94 - 0x3C];
	unsigned char m_94; // +0x94
	char m_pad95[0x9C - 0x95];
};

class Rva0026F684
{
public:
	Rva0026F684();
	virtual ~Rva0026F684();

private:
	char m_pad[0x9C - 4];
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
	UpgradeTemplate *newUpgrade(const AsciiString &name, bool assignMaskBit);
	static void parseUpgradeDefinition(class INI *ini);

protected:
	void unlinkUpgrade(UpgradeTemplate *upgrade);

private:
	char m_pad00[0x18];
	_STL::vector<Rva004DFCB0Element> m_oldUpgrades; // +0x18
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
	INILoadType getLoadType() const { return m_loadType; }

private:
	char m_pad00[0x08];
	INILoadType m_loadType; // +0x08
};

extern UpgradeCenter *TheUpgradeCenter;
extern const FieldParse g_00BFA6E8[];

static const INILoadType INI_LOAD_BFME_TYPE_5 = (INILoadType)5;

void UpgradeCenter::parseUpgradeDefinition(INI *ini)
{
	const char *token = ini->getNextToken(0);
	AsciiString name(token);
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	UpgradeCenter * const center = TheUpgradeCenter;
	UpgradeTemplate *upgrade = const_cast<UpgradeTemplate *>(center->findUpgradeByKey(key));
	if (upgrade == 0)
	{
		upgrade = center->newUpgrade(name, true);
	}
	else if (ini->getLoadType() == INI_LOAD_BFME_TYPE_5)
	{
		int savedMask = upgrade->m_maskBitIndex;
		center->unlinkUpgrade(upgrade);
		// 4-byte ABI view to reuse the rowed push_back body; identity unresolved.
		TheUpgradeCenter->m_oldUpgrades.push_back(*(const Rva004DFCB0Element *)&upgrade);
		upgrade->m_94 = 1;
		upgrade = TheUpgradeCenter->newUpgrade(name, false);
		upgrade->m_maskBitIndex = savedMask;
	}
	else
	{
		Rva0026F684 tmp;
		ini->initFromINI(&tmp, g_00BFA6E8);
		return;
	}
	ini->initFromINI(upgrade, g_00BFA6E8);
}
