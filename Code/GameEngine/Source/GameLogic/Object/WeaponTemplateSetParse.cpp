// cl: /DNDEBUG /MD
// platformsdk
//
// WeaponTemplateSet FieldParse procs (retail WeaponSet.cpp run 0x002C726C..
// 0x002C8C7A), split from the Zero Hour port in WeaponSet.cpp because the BFME 2
// layout differs: six weapon slots, so the per-slot arrays sit at
//   +0x14 const WeaponTemplate *m_weapons[6]
//   +0x2C UnsignedInt m_autoChooseMask[6]
//   +0x44 KindOfMaskType m_preferredAgainst[6]   (0x1C each)
//   +0xEC KindOfMaskType [6]                      ("OnlyAgainst")
//   +0x194 ModelConditionFlags [6]                (0x4C each, "OnlyInCondition")
// Target evidence: the WeaponTemplateSet FieldParse table maps Weapon
// (0x00C00AA0) -> 0x002C726C, AutoChooseSources (0x00C00AB0) -> 0x002C729F,
// PreferredAgainst (0x00C00AC0) -> 0x002C8C16, OnlyAgainst (0x00C00AD0) ->
// 0x002C8C47 and OnlyInCondition (0x00C00AE0) -> 0x002C883E. The first three
// are Zero Hour's statics; the last two are BFME 2 additions whose names stay
// address-derived. The slot index goes through the member scanIndexList with
// explicit null seps (as in INI_parseIndexList.cpp) over the VA 0x00DBC284
// slot-name table; the mask table at VA 0x00DBC2B4 is the command-source list.
// KindOfMaskType's self-parse is the pinned 0x00256499; the 0x4C flag set's
// self-parse 0x000B937E is unrowed and pinned by address.

#include <windows.h>

typedef unsigned int UnsignedInt;

#include "../../../Include/Common/INI/INI.h"

// KindOfMaskType self-parse (pinned 0x00256499).
class Rva00256499
{
public:
	void rva00256499(INI *ini, void *extra);
	UnsignedInt m_bits[7]; // +0x00
};

// ModelConditionFlags-sized (0x4C) self-parse, unrowed body at 0x000B937E.
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva000B937E.h"

// The matched attack/selection bodies use these same 28-byte KindOf and
// 76-byte model-condition masks at +0x44/+0xEC and +0x194. The parser's
// address-owned call views describe the existing callees, not member types.
template<int N> class BitFlags;
template<> class BitFlags<218> { public: bool any() const; private: unsigned m_bits[7]; };
#include "../../../Include/GameClient/ModelConditionFlags.h"

class WeaponTemplate;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	WEAPONSLOT_COUNT = 6
};

extern const char *TheWeaponSlotTypeNames[];
// ZH AI.h supplies the command-source table semantics. Target VA 0x00DBC2B4
// retains exactly these three names and a null sentinel, rather than ZH's
// additional FROM_DOZER and DEFAULT_SWITCH_WEAPON entries. Full strings and
// all three pointer relocations are checked against the retail image.
const char *TheCommandSourceMaskNames[] =
{
	"FROM_PLAYER",
	"FROM_SCRIPT",
	"FROM_AI",
	NULL
};

enum WeaponChoiceCriteria
{
 PREFER_MOST_DAMAGE=0, PREFER_LONGEST_RANGE=1, PREFER_SPECIAL=2,
 PREFER_SMALLEST_RANGE_ERROR=3, PREFER_RANDOM=4, PREFER_TEMPLATE_DEFAULT=5
};
class WeaponTemplateSet
{
private:
	static void parseWeapon(INI *ini, void *instance, void *store, const void *userData);
	static void parseAutoChoose(INI *ini, void *instance, void *store, const void *userData);
	static void parsePreferredAgainst(INI *ini, void *instance, void *store, const void *userData);
public:
	static void rva002C8C47(INI *ini, void *instance, void *store, const void *userData);
	static void rva002C883E(INI *ini, void *instance, void *store, const void *userData);
private:
	unsigned char m_unreconstructed_00[0x14]; // +0x00
public:
	const WeaponTemplate *m_weapons[WEAPONSLOT_COUNT]; // +0x14 +0x14
	unsigned int m_autoChooseMask[WEAPONSLOT_COUNT]; // +0x2C +0x2C
	BitFlags<218> m_preferredAgainst[WEAPONSLOT_COUNT]; // +0x44 +0x44
	BitFlags<218> m_onlyAgainst[WEAPONSLOT_COUNT]; // +0xEC +0xEC
	ModelConditionFlags m_onlyInCondition[WEAPONSLOT_COUNT]; // +0x194 +0x194
	bool m_sharedReload; // +0x35C
	bool m_sharedLock; // +0x35D
	char m_pad35E[0x2];
	WeaponChoiceCriteria m_defaultCriteria; // +0x360
	bool m_364; // +0x364
	char m_pad365[0x3];
};

// ?parseWeapon@WeaponTemplateSet@@CAXPAVINI@@PAX1PBX@Z
void WeaponTemplateSet::parseWeapon(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	WeaponTemplateSet *self = (WeaponTemplateSet *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	INI::parseWeaponTemplate(ini, instance, &self->m_weapons[wslot], NULL);
}

// ?parseAutoChoose@WeaponTemplateSet@@CAXPAVINI@@PAX1PBX@Z
void WeaponTemplateSet::parseAutoChoose(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	WeaponTemplateSet *self = (WeaponTemplateSet *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	INI::parseBitString32(ini, instance, &self->m_autoChooseMask[wslot], TheCommandSourceMaskNames);
}

// ?parsePreferredAgainst@WeaponTemplateSet@@CAXPAVINI@@PAX1PBX@Z
void WeaponTemplateSet::parsePreferredAgainst(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	WeaponTemplateSet *self = (WeaponTemplateSet *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	((Rva00256499 *)&self->m_preferredAgainst[wslot])->rva00256499(ini, NULL);
}

// ?rva002C8C47@WeaponTemplateSet@@SAXPAVINI@@PAX1PBX@Z
void WeaponTemplateSet::rva002C8C47(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	WeaponTemplateSet *self = (WeaponTemplateSet *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	((Rva00256499 *)&self->m_onlyAgainst[wslot])->rva00256499(ini, NULL);
}

// ?rva002C883E@WeaponTemplateSet@@SAXPAVINI@@PAX1PBX@Z
void WeaponTemplateSet::rva002C883E(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	WeaponTemplateSet *self = (WeaponTemplateSet *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	((Rva000B937E *)&self->m_onlyInCondition[wslot])->rva000B937E(ini, NULL);
}
