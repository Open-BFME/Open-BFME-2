// cl: /DNDEBUG /MD
//
// WeaponTemplateSet FieldParse procs (retail WeaponSet.cpp run 0x002C726C..
// 0x002C8C7A), split from the Zero Hour port in WeaponSet.cpp because the BFME 2
// layout differs: six weapon slots, so the per-slot arrays sit at
//   +0x14 const WeaponTemplate *m_template[6]
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

#define NULL 0

typedef unsigned int UnsignedInt;

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, const char *const *names);
	static void parseWeaponTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parseBitString32(INI *ini, void *instance, void *store, const void *userData);
};

// KindOfMaskType self-parse (pinned 0x00256499).
class Rva00256499
{
public:
	void rva00256499(INI *ini, void *extra);
	UnsignedInt m_bits[7];
};

// ModelConditionFlags-sized (0x4C) self-parse, unrowed body at 0x000B937E.
class Rva000B937E
{
public:
	void rva000B937E(INI *ini, void *extra);
	UnsignedInt m_bits[19];
};

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
	unsigned char m_unreconstructed_00[0x14];
	const WeaponTemplate *m_template[WEAPONSLOT_COUNT];		// +0x14
	UnsignedInt m_autoChooseMask[WEAPONSLOT_COUNT];			// +0x2C
	Rva00256499 m_preferredAgainst[WEAPONSLOT_COUNT];		// +0x44
	Rva00256499 m_onlyAgainst[WEAPONSLOT_COUNT];			// +0xEC
	Rva000B937E m_onlyInCondition[WEAPONSLOT_COUNT];		// +0x194
};

// ?parseWeapon@WeaponTemplateSet@@CAXPAVINI@@PAX1PBX@Z
void WeaponTemplateSet::parseWeapon(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	WeaponTemplateSet *self = (WeaponTemplateSet *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	INI::parseWeaponTemplate(ini, instance, &self->m_template[wslot], NULL);
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
	self->m_preferredAgainst[wslot].rva00256499(ini, NULL);
}

// ?rva002C8C47@WeaponTemplateSet@@SAXPAVINI@@PAX1PBX@Z
void WeaponTemplateSet::rva002C8C47(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	WeaponTemplateSet *self = (WeaponTemplateSet *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	self->m_onlyAgainst[wslot].rva00256499(ini, NULL);
}

// ?rva002C883E@WeaponTemplateSet@@SAXPAVINI@@PAX1PBX@Z
void WeaponTemplateSet::rva002C883E(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	WeaponTemplateSet *self = (WeaponTemplateSet *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	self->m_onlyInCondition[wslot].rva000B937E(ini, NULL);
}
