// cl: /DNDEBUG /MD
//
// Thin FieldParse procs (original names unproven; address names). Each is
// referenced from a retail FieldParse table entry named below.
//
// initFromINI forwarders (sub-block parsed into a fixed table):
//   0x00219440 19B ViewInfo (0x00DBA0B8)            store            table 0x00DB9D48
//   0x0041F316 23B AIEconomyAssigment (0x00C3B658)   instance + 0x24  table 0x00C3B050
//   0x0041F32D 23B AIWallNodeAssignment (0x00C3B668) instance + 0x28  table 0x00C3B050
//   0x0033A7A2 25B ThreatBreakdown (0x00DBF708)      instance + 0x520 table 0x00C1045C
//   0x0033DBC9 28B UnitSpecificFX (0x00DBF268)       store, cleared first through the
//                                                     rowed tree clear 0x002D02FD; table 0x00C10C0C
// Flag-set self-parse through the pinned 0x000B937E (ini, 0):
//   0x000B9468 16B on the store (DependencySharedModelFlags and three
//                  Required/Excluded model-condition rows)
//   0x00288739 23B on instance + 0x58 when instance is set (ModelConditionState 0x00BFBB40)
// 0x00438176 58B InvisibilityNugget (0x00C52468 / 0x00C5C468): the store is
//   filled from a local MultiIniFieldParse (rowed ctor 0x0002BAA0, add
//   0x0002BC6E) holding table 0x00C3D3A8, through the pinned initFromINIMulti.
// 0x004FCB23 62B Teams (0x00C635D0 and three more): the rowed
//   Rva004E8EFF_ParseDisabledSlots int list, then every entry made zero-based.

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *parseTable, unsigned int extraOffset);
private:
	unsigned char m_unreconstructed_00[0x84];
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
	static void Rva004E8EFF_ParseDisabledSlots(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" {
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x009B9D48: 23 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00DB9D48[24] = {
	{ "CloseUpPitch", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x30 },
	{ "CloseUpZoom", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x34 },
	{ "CloseUpFloor", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
	{ "CloseUpDist", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
	{ "CloseUpShift", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
	{ "PortraitPitch", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
	{ "PortraitZoom", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4C },
	{ "PortraitFloor", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x50 },
	{ "PortraitDist", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x54 },
	{ "PortraitShift", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x58 },
	{ "NearPitch", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
	{ "NearZoom", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "NearFloor", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "NearDist", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "NearShift", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "FarPitch", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ "FarZoom", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
	{ "FarFloor", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ "FarDist", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x24 },
	{ "FarShift", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
	{ "NormalCam", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x60 },
	{ "CameraAngle", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
	{ "MapLocation", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
	{ 0, 0, 0, 0 }
};
extern const FieldParse g_00C3B050[];
extern const FieldParse g_00C1045C[];
extern const FieldParse g_00C10C0C[];
extern const FieldParse g_00C3D3A8[];


// Retail's packed pointer-list region at VA DC8C3C. The three table views
// begin at element 0 (InvisibilityType), 2 (ForbiddenConditions), and 12
// (Options). Keep the physical suffix through its first null; these names
// describe retail data, not inferred enum bounds.
const char *INIInvisibilityNameLists[] = {
    "STEALTH", "CAMOUFLAGE", "AWAY_FROM_TREES", "MOVING",
    "FIRING_PRIMARY", "FIRING_SECONDARY", "FIRING_TERTIARY",
    "FIRING_QUATERNARY", "FIRING_QUINARY", "FIRING_ANY",
    "TAKING_DAMAGE", "USING_ABILITY", "ALLOW_NEAR_TREES",
    "DETECTED_BY_FRIENDLIES", "DISCONTINUE_WHEN_REVEALED",
    "UNTOGGLE_HIDDEN_WHEN_LEAVING_STEALTH", "NONE", "HOLD", "KILL", "SPAWN", 0
};

extern "C" {
void __identifier("?Rva004E8E57_ParseAIKindOf@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseArbitraryFXIntoMap@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z")();
void __identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z")();
}

// These two retail tables occupy exactly one 16-byte entry: the next
// bytes are string/float data, not an invented null entry.
extern const FieldParse g_00C1045C[] = {
    { "AIKindOf", (FieldParseProc)&__identifier("?Rva004E8E57_ParseAIKindOf@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0 }
};
extern const FieldParse g_00C3B050[] = {
    { "TemplateName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0 }
};
// Null-token default callback followed by the retail null terminator.
extern const FieldParse g_00C10C0C[] = {
    { 0, (FieldParseProc)&__identifier("?parseArbitraryFXIntoMap@@YAXPAVINI@@PAX1PBX@Z"), 0, 0 },
    { 0, 0, 0, 0 }
};
extern const FieldParse g_00C3D3A8[] = {
    { "ForbiddenConditions", (FieldParseProc)&__identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), INIInvisibilityNameLists + 2, 0 },
    { "ForbiddenWeaponConditions", (FieldParseProc)&__identifier("?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 4 },
    { "DetectionRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
    { "InvisibilityType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), INIInvisibilityNameLists, 0x18 },
    { "IgnoreTreeCheckUpgrades", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0x1C },
    { "Options", (FieldParseProc)&__identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), INIInvisibilityNameLists + 12, 0x9C },
    { "BecomeStealthedFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA0 },
    { "ExitStealthFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA4 },
    { "HintDetectableConditions", (FieldParseProc)&__identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA8 },
    { 0, 0, 0, 0 }
};

class Rva002D02FD
{
public:
	void rva002D02FD();
};

class Rva000B937E
{
public:
	void rva000B937E(INI *ini, void *extra);
};

struct Rva004FCB23IntList
{
	int *m_start;
	int *m_finish;
	int *m_endOfStorage;
	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	int &operator[](unsigned int n) { return m_start[n]; }
};

// ?Rva00219440Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00219440Parse(INI *ini, void *, void *store, const void *)
{
	ini->initFromINI(store, g_00DB9D48);
}

// ?Rva0041F316Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva0041F316Parse(INI *ini, void *instance, void *, const void *)
{
	ini->initFromINI((char *)instance + 0x24, g_00C3B050);
}

// ?Rva0041F32DParse@@YAXPAVINI@@PAX1PBX@Z
void Rva0041F32DParse(INI *ini, void *instance, void *, const void *)
{
	ini->initFromINI((char *)instance + 0x28, g_00C3B050);
}

// ?Rva0033A7A2Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva0033A7A2Parse(INI *ini, void *instance, void *, const void *)
{
	ini->initFromINI((char *)instance + 0x520, g_00C1045C);
}

// ?Rva0033DBC9Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva0033DBC9Parse(INI *ini, void *, void *store, const void *)
{
	((Rva002D02FD *)store)->rva002D02FD();
	ini->initFromINI(store, g_00C10C0C);
}

// ?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva000B9468Parse(INI *ini, void *, void *store, const void *)
{
	((Rva000B937E *)store)->rva000B937E(ini, 0);
}

// ?Rva00288739Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00288739Parse(INI *ini, void *instance, void *, const void *)
{
	if (instance)
		((Rva000B937E *)((char *)instance + 0x58))->rva000B937E(ini, 0);
}

// ?Rva00438176Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00438176Parse(INI *ini, void *, void *store, const void *)
{
	MultiIniFieldParse p;
	p.add(g_00C3D3A8, 0);
	ini->initFromINIMulti(store, p);
}

// ?Rva004FCB23Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004FCB23Parse(INI *ini, void *instance, void *store, const void *userData)
{
	INI::Rva004E8EFF_ParseDisabledSlots(ini, instance, store, userData);
	Rva004FCB23IntList &list = *(Rva004FCB23IntList *)store;
	for (unsigned int i = 0; i < list.size(); ++i)
		--list[i];
}

// Four more retail FieldParse tables, each N 16-byte entries plus the retail
// null terminator (16 zero bytes, then string data); every parser is a rowed
// code owner. The six-byte getters 0x00418060, 0x0041901D, 0x00419663 and
// 0x006882D0 return their addresses.
extern "C" {
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva00418F7DParse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseDamagePerRoundIntoTable@LivingWorldAutoResolveWeaponTemplate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva004195ECParse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseFromINI@Rva00417DFB@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva00417FF0Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva006882E0Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseSubtitleText@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseSubtitleLineTable@@YAXPAVINI@@PAX1PBX@Z")();
}
// 0x00C3A730: Affects / AffectsHigherLevelFirst / BonusForLevel.
extern const FieldParse g_00C3A730[] = {
    { "Affects", (FieldParseProc)&__identifier("?parseFromINI@Rva00417DFB@@SAXPAVINI@@PAX1PBX@Z"), 0, 4 },
    { "AffectsHigherLevelFirst", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 20 },
    { "BonusForLevel", (FieldParseProc)&__identifier("?Rva00417FF0Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 8 },
    { 0, 0, 0, 0 }
};
// 0x00C3A9A8: the AutoResolve attack-priority Target entry.
extern const FieldParse g_00C3A9A8[] = {
    { "Target", (FieldParseProc)&__identifier("?Rva00418F7DParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0 },
    { 0, 0, 0, 0 }
};
// 0x00C3AAC8: the LivingWorld AutoResolve weapon fields.
extern const FieldParse g_00C3AAC8[] = {
    { "DamagePerRound", (FieldParseProc)&__identifier("?parseDamagePerRoundIntoTable@LivingWorldAutoResolveWeaponTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 20 },
    { "LevelBonus", (FieldParseProc)&__identifier("?Rva004195ECParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 4 },
    { "ReduceAttackWhenHurt", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 52 },
    { "MissPercentChance", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 16 },
    { 0, 0, 0, 0 }
};
// 0x00CE43B0: the subtitle font/type fields.
extern const FieldParse g_00CE43B0[] = {
    { "FontName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 12 },
    { "FontPitch", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 16 },
    { "SubTitleType", (FieldParseProc)&__identifier("?Rva006882E0Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 32 },
    { "SubTitle", (FieldParseProc)&__identifier("?parseSubtitleText@@YAXPAVINI@@PAX1PBX@Z"), 0, 20 },
    { "LineTable", (FieldParseProc)&__identifier("?parseSubtitleLineTable@@YAXPAVINI@@PAX1PBX@Z"), 0, 36 },
    { 0, 0, 0, 0 }
};

// Nine more retail FieldParse tables returned by six-byte getters (formerly
// literals in ConstIntGettersAddr.cpp): each is its entries plus the retail
// 16-byte null terminator, every callback a rowed code owner, userData 0.
extern "C" {
void __identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z")();
void __identifier("?Rva00339761_ParseDurationUnsignedByte@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva00403233Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva00404648Parse@@YAXPAVINI@@PAVRva004045B4@@@Z")();
void __identifier("?iniParseAnimAndDuration@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva0056A83BParseAudioMap@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?dup_002F0F7@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAudioKeyTokens@Rva003D4920@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseDeathTypeFlags@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseDelayedUpgradeTemplate@AttributeModifierContainer@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseDurationReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseFontDesc@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseICoord2D@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseNamedRadiusDecalTemplate@InGameUI@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseRGBAColorInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseSoundBlock@LargeGroupAudioAudioMap@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseStringAsNameKeyType@NameKeyGenerator@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseTerrainResourceClaimDecal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseUnsignedShort@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z")();
}
// 0x00BFC338 (getter 0x0008EFCC): 81 entries.
extern const FieldParse g_00BFC338[] = {
    { "MaxSelectionSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1388 },
    { "MessageColor1", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2068 },
    { "MessageColor2", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2072 },
    { "MessagePosition", (FieldParseProc)&__identifier("?parseICoord2D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2076 },
    { "MessagePositionLW", (FieldParseProc)&__identifier("?parseICoord2D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2084 },
    { "MessageFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2092 },
    { "MessagePointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2096 },
    { "MessageBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2100 },
    { "MessageDelayMS", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2104 },
    { "MilitaryCaptionColor", (FieldParseProc)&__identifier("?parseRGBAColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2108 },
    { "MilitaryCaptionPosition", (FieldParseProc)&__identifier("?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2124 },
    { "MilitaryCaptionCentered", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2132 },
    { "MilitaryCaptionTitleFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2136 },
    { "MilitaryCaptionTitlePointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2140 },
    { "MilitaryCaptionTitleBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2144 },
    { "MilitaryCaptionFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2148 },
    { "MilitaryCaptionPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2152 },
    { "MilitaryCaptionBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2156 },
    { "MilitaryCaptionDelayMS", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2160 },
    { "SuperweaponCountdownPosition", (FieldParseProc)&__identifier("?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1824 },
    { "SuperweaponCountdownFlashDuration", (FieldParseProc)&__identifier("?parseDurationReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1832 },
    { "SuperweaponCountdownFlashColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1864 },
    { "SuperweaponCountdownNormalFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1836 },
    { "SuperweaponCountdownNormalPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1840 },
    { "SuperweaponCountdownNormalBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1844 },
    { "SuperweaponCountdownReadyFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1848 },
    { "SuperweaponCountdownReadyPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1852 },
    { "SuperweaponCountdownReadyBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1856 },
    { "NamedTimerCountdownPosition", (FieldParseProc)&__identifier("?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1884 },
    { "NamedTimerCountdownCentered", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1896 },
    { "NamedTimerCountdownFlashDuration", (FieldParseProc)&__identifier("?parseDurationReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1900 },
    { "NamedTimerCountdownFlashColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1908 },
    { "NamedTimerCountdownNormalFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1916 },
    { "NamedTimerCountdownNormalPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1920 },
    { "NamedTimerCountdownNormalBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1924 },
    { "NamedTimerCountdownNormalColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1928 },
    { "NamedTimerCountdownReadyFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1932 },
    { "NamedTimerCountdownReadyPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1936 },
    { "NamedTimerCountdownReadyBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1940 },
    { "NamedTimerCountdownReadyColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1944 },
    { "FloatingTextTimeOut", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2212 },
    { "FloatingTextMoveUpSpeed", (FieldParseProc)&__identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2216 },
    { "FloatingTextVanishRate", (FieldParseProc)&__identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2220 },
    { "HelpBoxNameFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1964 },
    { "HelpBoxNamePointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1968 },
    { "HelpBoxNameBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1972 },
    { "HelpBoxNameColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1976 },
    { "HelpBoxCostFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1980 },
    { "HelpBoxCostPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1984 },
    { "HelpBoxCostBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1988 },
    { "HelpBoxCostColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1992 },
    { "HelpBoxShortcutFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1996 },
    { "HelpBoxShortcutPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2000 },
    { "HelpBoxShortcutBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2004 },
    { "HelpBoxShortcutColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2008 },
    { "HelpBoxDescriptionFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2012 },
    { "HelpBoxDescriptionPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2016 },
    { "HelpBoxDescriptionBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2020 },
    { "HelpBoxDescriptionColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2024 },
    { "DrawableCaptionFont", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1948 },
    { "DrawableCaptionPointSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1952 },
    { "DrawableCaptionBold", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1956 },
    { "DrawableCaptionColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1960 },
    { "DrawRMBScrollAnchor", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2243 },
    { "MoveRMBScrollAnchor", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2244 },
    { "RadiusCursorTemplate", (FieldParseProc)&__identifier("?parseNamedRadiusDecalTemplate@InGameUI@@SAXPAVINI@@PAX1PBX@Z"), 0, 0 },
    { "RadiusCursorUseWeaponScatterRadius", (FieldParseProc)&__identifier("?parseStringAsNameKeyType@NameKeyGenerator@@SAXPAVINI@@PAX1PBX@Z"), 0, 2204 },
    { "UnitHelpTextDelay", (FieldParseProc)&__identifier("?dup_002F0F7@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2436 },
    { "SelectNearestBuilderCycleTimeOut", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2440 },
    { "TerrainResourceClaimDecal", (FieldParseProc)&__identifier("?parseTerrainResourceClaimDecal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0 },
    { "PlaceTerrainResourceClaimantDecal", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1396 },
    { "PlaceTerrainResourceClaimantFont", (FieldParseProc)&__identifier("?parseFontDesc@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z"), 0, 1400 },
    { "PlaceTerrainResourceClaimantFontColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 1412 },
    { "HeroInitialSpawnNotificationMessage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2512 },
    { "HeroInitialSpawnNotificationTimeout", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2516 },
    { "HeroRespawnNotificationMessage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2520 },
    { "HeroRespawnNotificationTimeout", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2524 },
    { "HeroDeathNotificationMessage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2528 },
    { "HeroDeathNotificationTimeout", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2532 },
    { "HeroEarnedAwardNotificationMessage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2536 },
    { "HeroEarnedAwardNotificationTimeout", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 2540 },
    { 0, 0, 0, 0 }
};
// 0x00C1DB18 (getter 0x003B0E57): 3 entries.
extern const FieldParse g_00C1DB18[] = {
    { "IntrinsicSciencePurchasePoints", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 4 },
    { "MaxLevelMP", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 8 },
    { "MaxLevelSP", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 12 },
    { 0, 0, 0, 0 }
};
// 0x00C36290 (getter 0x003EE6F7): 11 entries.
extern const FieldParse g_00C36290[] = {
    { "Size", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 16 },
    { "Sound", (FieldParseProc)&__identifier("?parseSoundBlock@LargeGroupAudioAudioMap@@SAXPAVINI@@PAX1PBX@Z"), 0, 28 },
    { "StartThreshold", (FieldParseProc)&__identifier("?parseUnsignedShort@INI@@SAXPAV1@PAX1PBX@Z"), 0, 224 },
    { "StopThreshold", (FieldParseProc)&__identifier("?parseUnsignedShort@INI@@SAXPAV1@PAX1PBX@Z"), 0, 226 },
    { "HandOffModeDuration", (FieldParseProc)&__identifier("?Rva00339761_ParseDurationUnsignedByte@INI@@SAXPAV1@PAX1PBX@Z"), 0, 228 },
    { "MaximumAudioSpeed", (FieldParseProc)&__identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 20 },
    { "RequiredModelConditionFlags", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 40 },
    { "ExcludedModelConditionFlags", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 116 },
    { "RequiredObjectStatusBits", (FieldParseProc)&__identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z"), 0, 192 },
    { "ExcludedObjectStatusBits", (FieldParseProc)&__identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z"), 0, 208 },
    { "IgnoreStealthedUnits", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 229 },
    { 0, 0, 0, 0 }
};
// 0x00C38658 (getter 0x00404715): 15 entries.
extern const FieldParse g_00C38658[] = {
    { "Modifier", (FieldParseProc)&__identifier("?Rva00404648Parse@@YAXPAVINI@@PAVRva004045B4@@@Z"), 0, 0 },
    { "Duration", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 24 },
    { "ModelCondition", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 28 },
    { "ClearModelCondition", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 104 },
    { "Category", (FieldParseProc)&__identifier("?Rva00403233Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 12 },
    { "FX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 180 },
    { "FX2", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 184 },
    { "FX3", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 188 },
    { "EndFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 192 },
    { "EndFX2", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 196 },
    { "EndFX3", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 200 },
    { "Upgrade", (FieldParseProc)&__identifier("?parseDelayedUpgradeTemplate@AttributeModifierContainer@@SAXPAVINI@@PAX1PBX@Z"), 0, 0 },
    { "MultiLevelFX", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 208 },
    { "ReplaceInCategoryIfLongest", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 210 },
    { "IgnoreIfAnticategoryActive", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 211 },
    { 0, 0, 0, 0 }
};
// 0x00C5FEA0 (getter 0x004CE29D): 6 entries.
extern const FieldParse g_00C5FEA0[] = {
    { "TriggeredBy", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0 },
    { "ConflictsWith", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 128 },
    { "RequiresAllTriggers", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 268 },
    { "RequiresAllConflictingTriggers", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 269 },
    { "CustomAnimAndDuration", (FieldParseProc)&__identifier("?iniParseAnimAndDuration@INI@@SAXPAV1@PAX1PBX@Z"), 0, 256 },
    { "Permanent", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 270 },
    { 0, 0, 0, 0 }
};
// 0x00C5FFA0 (getter 0x004CE52E): 6 entries.
extern const FieldParse g_00C5FFA0[] = {
    { "DeathTypes", (FieldParseProc)&__identifier("?parseDeathTypeFlags@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0 },
    { "ExemptStatus", (FieldParseProc)&__identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z"), 0, 4 },
    { "RequiredStatus", (FieldParseProc)&__identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z"), 0, 20 },
    { "DamageAmountRequired", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 36 },
    { "MinKillerAngle", (FieldParseProc)&__identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 40 },
    { "MaxKillerAngle", (FieldParseProc)&__identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 44 },
    { 0, 0, 0, 0 }
};
// 0x00C63FD0 (getter 0x00507552): 3 entries.
extern const FieldParse g_00C63FD0[] = {
    { "RequiredUpgradeNames", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 264 },
    { "ForbiddenUpgradeNames", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 276 },
    { "SpecialObjectFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 288 },
    { 0, 0, 0, 0 }
};
// 0x00C6CFD0 (getter 0x0056A983): 3 entries.
extern const FieldParse g_00C6CFD0[] = {
    { "Sound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 12 },
    { "Key", (FieldParseProc)&__identifier("?parseAudioKeyTokens@Rva003D4920@@SAXPAVINI@@PAX1PBX@Z"), 0, 0 },
    { "Duck", (FieldParseProc)&__identifier("?Rva0056A83BParseAudioMap@@YAXPAVINI@@PAX1PBX@Z"), 0, 20 },
    { 0, 0, 0, 0 }
};
// 0x00CE4818 (getter 0x000907A1): 5 entries.
extern const FieldParse g_00CE4818[] = {
    { "Filename", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0 },
    { "Comment", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 8 },
    { "HasSubtitles", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 12 },
    { "Volume", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 16 },
    { "IsDefault", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 20 },
    { 0, 0, 0, 0 }
};

// Retail name lists the 0x00C64180 table passes as userData: each its
// string pointers plus the NULL terminator, in retail order.
extern const char *g_00DD08C8[] = {
    "SWORD_SLASH",
    "WITCH_KING_MORGUL_BLADE",
    "REFLECTED",
    "GOOD_ARROW_PIERCE",
    "EVIL_ARROW_PIERCE",
    "SMALL_ROCK",
    "BIG_ROCK",
    "CLUBBING",
    "FLAME",
    "MAGIC",
    "BALROG_SWORD",
    "BALROG_WHIP",
    "ELECTRIC",
    "GIMLI_LEAP",
    "STRUCTURAL",
    "FLOOD_HORSE",
    "BOLT",
    "BOLT2",
    "MAGIC2",
    "MAGIC3",
    "FIRE1",
    "FIRE2",
    "FIRE3",
    "SPARKS1",
    "SPARKS2",
    "EARTH1",
    "EARTH2",
    "POISON",
    "TORNADO",
    "UNDEFINED",
    0
};
extern const char *g_00DD0948[] = {
    "FORCE",
    "CRUSH",
    "SLASH",
    "PIERCE",
    "SIEGE",
    "STRUCTURAL",
    "FLAME",
    "HEALING",
    "UNRESISTABLE",
    "WATER",
    "PENALTY",
    "FALLING",
    "TOPPLING",
    "REFLECTED",
    "PASSENGER",
    "MAGIC",
    "CHOP",
    "HERO",
    "SPECIALIST",
    "URUK",
    "HERO_RANGED",
    "FLY_INTO",
    "UNDEFINED",
    "LOGICAL_FIRE",
    "CAVALRY",
    "CAVALRY_RANGED",
    "POISON",
    0
};
extern const char *g_00DD09B8[] = {
    "NORMAL",
    "BECOME_UNDEAD",
    0
};
extern const char *g_00DD09C8[] = {
    "NORMAL",
    "NONE",
    "CRUSHED",
    "BURNED",
    "EXPLODED",
    "POISONED",
    "TOPPLED",
    "FLOODED",
    "SUICIDED",
    "LASERED",
    "DETONATED",
    "SPLATTED",
    "POISONED_BETA",
    "EXTRA_2",
    "EXTRA_3",
    "EXTRA_4",
    "EXTRA_5",
    "EXTRA_6",
    "EXTRA_7",
    "EXTRA_8",
    "KNOCKBACK",
    "SUPERNATURAL",
    "FADED",
    "SLAUGHTERED",
    0
};
extern "C" {
void __identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseDamageScalar@DamageNugget@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z")();
}
// 0x00C64180 (getter 0x005088C8): 23 entries plus the null terminator.
extern const FieldParse g_00C64180[] = {
    { "Damage", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 296 },
    { "DamageTaperOff", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 300 },
    { "AcceptDamageAdd", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 328 },
    { "Radius", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 304 },
    { "MinRadius", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 308 },
    { "DamageArc", (FieldParseProc)&__identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 312 },
    { "DamageArcInverted", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 316 },
    { "DamageMaxHeight", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 320 },
    { "DamageMaxHeightAboveTerrain", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 324 },
    { "DelayTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 340 },
    { "DamageType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DD0948, 344 },
    { "DeathType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DD09C8, 348 },
    { "DamageFXType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DD08C8, 352 },
    { "DamageSubType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DD09B8, 356 },
    { "DamageScalar", (FieldParseProc)&__identifier("?parseDamageScalar@DamageNugget@@SAXPAVINI@@PAX1PBX@Z"), 0, 360 },
    { "DamageSpeed", (FieldParseProc)&__identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 372 },
    { "LostLeadershipUselessAgainst", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 376 },
    { "FlankingBonus", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 332 },
    { "FlankedScalar", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 336 },
    { "DrainLife", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 404 },
    { "DrainLifeMultiplier", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 408 },
    { "CylinderAOE", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 416 },
    { "ForceKillObjectFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 412 },
    { 0, 0, 0, 0 }
};
