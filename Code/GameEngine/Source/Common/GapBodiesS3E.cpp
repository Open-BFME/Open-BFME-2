// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Table-reached INI block parsers from .text gaps no ledger row covers
// (seat-3 batch E; see GapBodiesS3A.cpp). Retail bytes establish every shape;
// field names are retail's string literals. Unrowed parse callbacks are
// pinned under address-derived names.

class INI;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);	// 0x0002EFC0
	static void parseThingTemplate(INI *ini, void *instance, void *store, const void *userData);	// 0x0033940F
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);	// 0x0002F11E
	static void parseColorInt(INI *ini, void *instance, void *store, const void *userData);		// 0x0002F3FE
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);			// 0x0002EF56
};

void rva00423FD8(INI *ini, void *instance, void *store, const void *userData);	// 0x00423FD8
void rva00425842(INI *ini, void *instance, void *store, const void *userData);	// 0x00425842
void parseFormationSelectionCriteriaRva00424185(INI *ini, void *instance, void *store, const void *userData);	// 0x00424185
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);	// 0x00361CA5

class Rva0022AD10Subsystem;
extern Rva0022AD10Subsystem *TheFormationAssistant;


// --- 0x005742A1 / 0x0057A260 (18B each): table slots parsing an INI block
// into this object through a static field table (retail 0x00C6E36C and
// 0x00C6EE98; the field names are retail's).
class GlobalLanguage
{
public:
	static void parseFontDesc(INI *ini, void *instance, void *store, const void *userData);	// 0x0037691C
};

class Rva005742A1
{
public:
	virtual void rva005742A1(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva005742A1::s_fieldParseTable[] =
{
	{ "Title", INI::parseAsciiString, 0, 0x08 },
	{ "Help", INI::parseAsciiString, 0, 0x0C },
	{ 0, 0, 0, 0 }
};

void Rva005742A1::rva005742A1(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

class Rva0057A260
{
public:
	virtual void rva0057A260(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva0057A260::s_fieldParseTable[] =
{
	{ "ItemFont", GlobalLanguage::parseFontDesc, 0, 0x08 },
	{ "ItemNormalColor", INI::parseColorInt, 0, 0x14 },
	{ "ItemImportantColor", INI::parseColorInt, 0, 0x18 },
	{ "ItemNewColor", INI::parseColorInt, 0, 0x1C },
	{ "ItemVerticalSpacing", INI::parseReal, 0, 0x20 },
	{ 0, 0, 0, 0 }
};

void Rva0057A260::rva0057A260(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

// --- 0x004E12C4 / 0x004E12EF / 0x004E1342 (19B each): field-parse callbacks
// parsing a nested block into their store through the rowed tables 0x00C616C0
// (LivingWorldCampaignObjects' SpawnArmy table), 0x00C61830 and 0x00C61884.
class SpawnArmy
{
public:
	static const FieldParse m_fieldParseTable[];			// 0x00C616C0
};

extern const FieldParse g_00C61830;
extern const FieldParse g_00C61884;

void parseSpawnArmy(INI *ini, void *instance, void *store, const void *userData)
{
	ini->initFromINI(store, SpawnArmy::m_fieldParseTable);
}



// --- 0x005CB288 / 0x005E3955 / 0x005E9F80 (18B each): more table slots
// parsing an INI block into this object through static field tables (retail
// 0x00C74D20, 0x00C77C10 and 0x00C780D4; the field names are retail's).
class Rva005CB288
{
public:
	virtual void rva005CB288(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva005CB288::s_fieldParseTable[] =
{
	{ "BuildPlotsTitle", INI::parseAsciiString, 0, 0x08 },
	{ "BuildPlotsHelp", INI::parseAsciiString, 0, 0x0C },
	{ "ArmoryPointsTitle", INI::parseAsciiString, 0, 0x10 },
	{ "ArmoryPointsHelp", INI::parseAsciiString, 0, 0x14 },
	{ "CommandPointsTitle", INI::parseAsciiString, 0, 0x18 },
	{ "CommandPointsHelp", INI::parseAsciiString, 0, 0x1C },
	{ 0, 0, 0, 0 }
};

void Rva005CB288::rva005CB288(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

class Rva005E3955
{
public:
	virtual void rva005E3955(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva005E3955::s_fieldParseTable[] =
{
	{ "BackButtonTooltip", INI::parseAsciiString, 0, 0x08 },
	{ 0, 0, 0, 0 }
};

void Rva005E3955::rva005E3955(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

class Rva005E9F80
{
public:
	virtual void rva005E9F80(INI *ini);
private:
	static const FieldParse s_fieldParseTable[];
};

const FieldParse Rva005E9F80::s_fieldParseTable[] =
{
	{ "BattleRoundsPerStep", INI::parseInt, 0, 0x08 },
	{ 0, 0, 0, 0 }
};

void Rva005E9F80::rva005E9F80(INI *ini)
{
	ini->initFromINI(this, s_fieldParseTable);
}

// --- 0x003F9CD2 (54B): the pupil / eye-decal anim-object block: build a
// fresh 0x74-byte 0x003F9C11 record, parse it through the static table
// 0x00C37668 (retail's field names) and hand it to TheLivingWorldManager
// (+0x2C4).
class Rva003F9C11
{
public:
	Rva003F9C11() throw();									// 0x003F9C11
	static const FieldParse s_fieldParseTable[];
private:
	char m_pad[0x74];
};

const FieldParse Rva003F9C11::s_fieldParseTable[] =
{
	{ "PupilAnimObject", INI::parseAsciiString, 0, 0x04 },
	{ "PupilBeamAnimObject", INI::parseAsciiString, 0, 0x08 },
	{ "EyeDecalAnimObject", INI::parseAsciiString, 0, 0x0C },
	{ "EyeDecalBeamAnimObject", INI::parseAsciiString, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva003F9CD2ManagerView
{
	char m_pad[0x2C4];
	Rva003F9C11 *m_2C4;										// +0x2C4
};


// Native 5742B3..5742CD (26B): a file-static helper in cl 7.1's SSE register
// convention - the Rva002E0C2B object stays in ECX for the rowed 0x002E0C2B
// call and the float result returns in XMM0 - computing its int value as a
// percentage bonus factor (value * 0.01 + 1). No call to it survives in the
// image; the anchor below only forces cl to emit it in that convention.
// Identity unproven; address-derived names.
class Rva002E0C2B
{
public:
	int rva002E0C2B();
};

static __declspec(noinline) float Rva005742B3(Rva002E0C2B *owner)
{
	return (float)owner->rva002E0C2B() * 0.01f + 1.0f;
}

// ?Rva005742B3Anchor absent-from-retail
float Rva005742B3Anchor(Rva002E0C2B *owner)
{
	return Rva005742B3(owner);
}

// --- 0x005CB29A (56B) / 0x005CB2D2 (47B), RET 0: two file-static helpers
// that feed a LivingWorld region's numbers to a display object through its
// virtual slots. Retail passes the display in ESI (0x005CB29A) or EDI
// (0x005CB2D2) and the region on the stack, the private convention cl 7.1
// picks for a file-static noinline function; no retail call reaches either
// copy (their callers were folded away), so source-only callers emit them.
// 0x005CB29A: the local player's upgradeable troops in the region (rowed
// LivingWorldLogic::GetNumUpgradeableTroopsInRegionForPlayer) as (total -
// first, total) to slot 5. 0x005CB2D2: two per-player region values
// (rowed LivingWorldRegion 0x003EFD6F / 0x003F0189) of the logic's +0x98
// player to slot 6. Names are address-derived.
class Rva003F287F;
class Rva002E2903Player;
class LivingWorldLogic
{
public:
	void GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F *region, int player, int *first, int *total);
};
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002B2B66
{
public:
	int rva002B2B66();
};
struct Rva005CB2D2LogicView
{
	char m_pad00[0x98];
	Rva002E2903Player *m_player98;	// +0x98
};
class Rva005CB29ADisplay
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void setPair(int a, int b);	// +0x14
	virtual void setPair6(int a, int b);	// +0x18
};
class LivingWorldRegion;
static __declspec(noinline) void Rva005CB2D2(Rva005CB29ADisplay *display, LivingWorldRegion *region);
class LivingWorldRegion
{
	friend void Rva005CB2D2(Rva005CB29ADisplay *display, LivingWorldRegion *region);
private:
	int rva003EFD6F(Rva002E2903Player *owner) const;
public:
	int rva003F0189(Rva002E2903Player *owner) const;
};

static __declspec(noinline) void Rva005CB29A(Rva005CB29ADisplay *display, Rva003F287F *region)
{
	int first, total;
	int player = ((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66();
	TheLivingWorldLogic->GetNumUpgradeableTroopsInRegionForPlayer(region, player, &first, &total);
	display->setPair(total - first, total);
}

static __declspec(noinline) void Rva005CB2D2(Rva005CB29ADisplay *display, LivingWorldRegion *region)
{
	Rva002E2903Player *player = ((Rva005CB2D2LogicView *)TheLivingWorldLogic)->m_player98;
	int value = region->rva003EFD6F(player);
	int other = region->rva003F0189(player);
	display->setPair6(other, value);
}

// ?Rva005CB29ACaller absent-from-retail
void Rva005CB29ACaller(Rva005CB29ADisplay *display, Rva003F287F *region)
{
	Rva005CB29A(display, region);
}

// ?Rva005CB2D2Caller absent-from-retail
void Rva005CB2D2Caller(Rva005CB29ADisplay *display, LivingWorldRegion *region)
{
	Rva005CB2D2(display, region);
}
