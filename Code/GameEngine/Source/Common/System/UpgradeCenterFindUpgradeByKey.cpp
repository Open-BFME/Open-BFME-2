// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /O1
// stlport
//
// ?findUpgradeByKey@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4NameKeyType@@@Z,
// retail 0x0026EEB8, 24 bytes. This unit supplies the BFME 2 list layout
// used by the lookup, link/unlink helpers and definition parser.
//
// Zero Hour reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source/Common/System/Upgrade.cpp,
// UpgradeCenter::findUpgradeByKey): const key-compare walk over the template
// list. BFME2 layout measured from retail: list head at UpgradeCenter+0x0C
// (ZH +0x08), name key at UpgradeTemplate+0x0C (same as ZH), next link at
// +0x64 (ZH +0x108). Leaf: no calls, no pins.

#include "ascii_string.h"
#include <vector>

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class UpgradeTemplate
{
public:
	NameKeyType getUpgradeNameKey() const { return m_nameKey; }
	int getMaskIndex() const { return m_maskIndex; }
	void setMaskIndex(int index) { m_maskIndex = index; }
	const UpgradeTemplate *friend_getNext() const { return m_next; }
	UpgradeTemplate *friend_getNext() { return m_next; }
	const UpgradeTemplate *friend_getPrev() const { return m_prev; }
	UpgradeTemplate *friend_getPrev() { return m_prev; }
	void friend_setNext(UpgradeTemplate *n) { m_next = n; }
	void friend_setPrev(UpgradeTemplate *p) { m_prev = p; }

private:
	unsigned char m_unreconstructed_000[0x0C];
	NameKeyType m_nameKey; // +0x0C
	unsigned char m_pad010[0x38 - 0x10];
	int m_maskIndex; // +0x38 mask bit index retail-measured
	unsigned char m_pad03C[0x64 - 0x3C];
	UpgradeTemplate *m_next; // +0x64
	UpgradeTemplate *m_prev; // +0x68
};

class UpgradeCenter
{
public:
	__declspec(noinline) const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
	UpgradeTemplate *newUpgrade(const AsciiString &name, bool assignMaskBit);
	static void parseUpgradeDefinition(class INI *ini);
	const UpgradeTemplate *rva0026EEA0(int key) const;
	void linkUpgrade(UpgradeTemplate *upgrade);

protected:
	void unlinkUpgrade(UpgradeTemplate *upgrade);

private:
	unsigned char m_unreconstructed_000[0x0C];
	UpgradeTemplate *m_upgradeList; // +0x0C
};

// ?findUpgradeByKey@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4NameKeyType@@@Z
const UpgradeTemplate *UpgradeCenter::findUpgradeByKey(NameKeyType key) const
{
	const UpgradeTemplate *upgrade;

	// search list
	for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext())
		if (upgrade->getUpgradeNameKey() == key)
			return upgrade;

	// item not found
	return 0;
}

//
// rva0026EEA0 at UpgradeCenter (mangled ?rva0026EEA0@UpgradeCenter@@QBEPBVUpgradeTemplate@@H@Z rowed),
// retail 0x0026EEA0, 24 bytes. Adjacent to findUpgradeByKey (ends at 0x0026EEB8).
// Same list walk but comparing mask bit index at +0x38 (UpgradeMuxData TU
// measures it as plain int). Callers pass TheUpgradeCenter (0x009FEB60) with a
// 0..0x400 index and use template+8 (m_name) or +0x28 fields on hit.
//
const UpgradeTemplate *UpgradeCenter::rva0026EEA0(int key) const
{
	const UpgradeTemplate *upgrade;

	// search list
	for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext())
		if (key == upgrade->getMaskIndex())
			return upgrade;

	// item not found
	return 0;
}

// unlinkUpgrade at retail 0x0026EEF2 44 bytes: ZH Upgrade.cpp unlink verbatim
// with BFME2 links at +0x64 next and +0x68 prev and head at +0x0C.
void UpgradeCenter::unlinkUpgrade(UpgradeTemplate *upgrade)
{
	if (upgrade == 0)
		return;

	if (upgrade->friend_getNext())
		upgrade->friend_getNext()->friend_setPrev(upgrade->friend_getPrev());
	if (upgrade->friend_getPrev())
		upgrade->friend_getPrev()->friend_setNext(upgrade->friend_getNext());
	else
		m_upgradeList = upgrade->friend_getNext();
}

// ?linkUpgrade@UpgradeCenter@@QAEXPAVUpgradeTemplate@@@Z @0x0026EED0 34B.
// ZH donor Upgrade.cpp with BFME2 list head and links measured above.
void UpgradeCenter::linkUpgrade(UpgradeTemplate *upgrade)
{
	if (upgrade == 0)
		return;

	upgrade->friend_setPrev(0);
	upgrade->friend_setNext(m_upgradeList);
	if (m_upgradeList)
		m_upgradeList->friend_setPrev(upgrade);
	m_upgradeList = upgrade;
}

// parseUpgradeDefinition, 0x0026FA05..0x0026FAFE (249 bytes).
// ZH Upgrade.cpp via BFME1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20
// supplies name lookup and INI parsing. Retail's Upgrade block entry at
// VA 0x00DB94F8 establishes the parser identity; load type 5 replaces an
// existing definition, parks the old template in the +0x18 vector, and
// preserves its mask index. Other duplicate definitions parse into a
// temporary 0x9C-byte template. These are target-specific adaptations.
// Keep the matched lookup visible: it preserves EDX across the lookup,
// reproducing the parser's cached-centre register without a duplicate TU.
struct FieldParse;

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

// Four-byte slot ABI shared with the verified push_back fold; original
// element spelling is unresolved. Retail stores UpgradeTemplate pointers.
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

class Rva0026F684
{
public:
	Rva0026F684();
	virtual ~Rva0026F684();

private:
	char m_pad[0x9C - 4];
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
		int savedMask = upgrade->getMaskIndex();
		center->unlinkUpgrade(upgrade);
		// 4-byte ABI view to reuse the rowed push_back body; identity unresolved.
		reinterpret_cast<_STL::vector<Rva004DFCB0Element> *>(
			reinterpret_cast<char *>(TheUpgradeCenter) + 0x18)->push_back(
				*(const Rva004DFCB0Element *)&upgrade);
		*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(upgrade) + 0x94) = 1;
		upgrade = TheUpgradeCenter->newUpgrade(name, false);
		upgrade->setMaskIndex(savedMask);
	}
	else
	{
		Rva0026F684 tmp;
		ini->initFromINI(&tmp, g_00BFA6E8);
		return;
	}
	ini->initFromINI(upgrade, g_00BFA6E8);
}
