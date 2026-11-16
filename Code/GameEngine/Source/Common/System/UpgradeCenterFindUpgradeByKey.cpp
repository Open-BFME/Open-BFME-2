// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /O1
// stlport
//
// ?findUpgradeByKey@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4NameKeyType@@@Z,
// retail 0x0026EEB8, 24 bytes. The lookup, link/unlink helpers and definition
// parser use the BFME 2 list layout of Common/Upgrade.h.
//
// Zero Hour reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source/Common/System/Upgrade.cpp,
// UpgradeCenter::findUpgradeByKey): const key-compare walk over the template
// list. BFME2 layout measured from retail: list head at UpgradeCenter+0x0C
// (ZH +0x08), name key at UpgradeTemplate+0x0C (same as ZH), next link at
// +0x64 (ZH +0x108). Leaf: no calls, no pins.

#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../Include/Common/Upgrade.h"

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
		if (key == upgrade->field38)
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

	if (upgrade->m_next)
		upgrade->m_next->m_prev = upgrade->m_prev;
	if (upgrade->m_prev)
		upgrade->m_prev->m_next = upgrade->m_next;
	else
		m_upgradeList = upgrade->m_next;
}

// ?linkUpgrade@UpgradeCenter@@QAEXPAVUpgradeTemplate@@@Z @0x0026EED0 34B.
// ZH donor Upgrade.cpp with BFME2 list head and links measured above.
void UpgradeCenter::linkUpgrade(UpgradeTemplate *upgrade)
{
	if (upgrade == 0)
		return;

	upgrade->m_prev = 0;
	upgrade->m_next = m_upgradeList;
	if (m_upgradeList)
		m_upgradeList->m_prev = upgrade;
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
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/FieldParse.h"

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

// Four-byte slot ABI shared with the verified push_back fold; original
// element spelling is unresolved. Retail stores UpgradeTemplate pointers.
#include "../../../Include/Common/Rva004DFCB0Element.h"

class Rva0026F684
{
public:
	Rva0026F684();
	virtual ~Rva0026F684();

private:
	char m_pad[0x9C - 4];
};

#include "../../../Include/Common/INI/INI.h"

// Upgrade.cpp's upgrade type names (retail RVA 0x009BB588: PLAYER, OBJECT, NULL), the
// list parseIndexList reads for an upgrade's Type.
extern const char *TheUpgradeTypeNames[];
extern "C" {
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseStringAsNameKeyType@NameKeyGenerator@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva004DBFF1Parse@@YAXPAVINI@@PAX1PBX@Z")();
}
// The retail table at 0x007FA6E8: 26 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00BFA6E8[27] = {
	{ "DisplayName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
	{ "Tooltip", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x2C },
	{ "Type", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), TheUpgradeTypeNames, 0x4 },
	{ "BuildTime", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x30 },
	{ "BuildCost", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x34 },
	{ "ButtonImage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
	{ "ResearchSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
	{ "ResearchCompleteEvaEvent", (FieldParseProc)&__identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x44 },
	{ "UnitSpecificSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
	{ "UpgradeFX", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
	{ "LocalPlayerGainsUpgradeEvaEvent", (FieldParseProc)&__identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x4C },
	{ "AlliedPlayerGainsUpgradeEvaEvent", (FieldParseProc)&__identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x50 },
	{ "EnemyPlayerGainsUpgradeEvaEvent", (FieldParseProc)&__identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x54 },
	{ "LocalPlayerLosesUpgradeEvaEvent", (FieldParseProc)&__identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x58 },
	{ "AlliedPlayerLosesUpgradeEvaEvent", (FieldParseProc)&__identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x5C },
	{ "EnemyPlayerLosesUpgradeEvaEvent", (FieldParseProc)&__identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x60 },
	{ "Cursor", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x74 },
	{ "PersistsInCampaign", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x78 },
	{ "NoUpgradeDiscount", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x79 },
	{ "SubUpgradeTemplateNames", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "UseObjectTemplateForCostDiscount", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x7C },
	{ "RequiredObjectFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x80 },
	{ "GroupName", (FieldParseProc)&__identifier("?parseStringAsNameKeyType@NameKeyGenerator@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x84 },
	{ "GroupOrder", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x88 },
	{ "StrategicIcon", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8C },
	{ "SkirmishAIHeuristic", (FieldParseProc)&__identifier("?Rva004DBFF1Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x98 },
	{ 0, 0, 0, 0 }
};

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
		int savedMask = upgrade->field38;
		center->unlinkUpgrade(upgrade);
		// 4-byte ABI view to reuse the rowed push_back body; identity unresolved.
		reinterpret_cast<_STL::vector<Rva004DFCB0Element> *>(
			reinterpret_cast<char *>(TheUpgradeCenter) + 0x18)->push_back(
				*(const Rva004DFCB0Element *)&upgrade);
		upgrade->field94 = true;
		upgrade = TheUpgradeCenter->newUpgrade(name, false);
		upgrade->field38 = savedMask;
	}
	else
	{
		Rva0026F684 ignoredUpgrade;
		ini->initFromINI(&ignoredUpgrade, g_00BFA6E8);
		return;
	}
	ini->initFromINI(upgrade, g_00BFA6E8);
}
