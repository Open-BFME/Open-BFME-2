// stlport
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Split from GapBodiesS3E.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Table-reached INI block parsers from .text gaps no ledger row covers
// (seat-3 batch E; see GapBodiesS3A.cpp). Retail bytes establish every shape;
// field names are retail's string literals. Unrowed parse callbacks are
// pinned under address-derived names.

class INI;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

void rva00423FD8(INI *ini, void *instance, void *store, const void *userData);	// 0x00423FD8
void rva00425842(INI *ini, void *instance, void *store, const void *userData);	// 0x00425842
void parseFormationSelectionCriteriaRva00424185(INI *ini, void *instance, void *store, const void *userData);	// 0x00424185
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);	// 0x00361CA5

class Rva0022AD10Subsystem;
extern Rva0022AD10Subsystem *TheFormationAssistant;

// --- 0x00425B90 (302B): the formation assistant's INI block, parsed through
// a table built on the stack into TheFormationAssistant.
void parseFormationAssistantDefinition(INI *ini)
{
	FieldParse dataFieldParse[] =
	{
		{ "DefaultPreviewObject", INI::parseThingTemplate, 0, 0x0C },
		{ "RowPadding", INI::parseReal, 0, 0x24 },
		{ "ColumnPadding", INI::parseReal, 0, 0x28 },
		{ "FacingArrowHeadTemplate", INI::parseThingTemplate, 0, 0x10 },
		{ "FacingArrowBodyTemplate", INI::parseThingTemplate, 0, 0x14 },
		{ "FacingArrowBaseTemplate", INI::parseThingTemplate, 0, 0x18 },
		{ "ActivationDragDistance", INI::parseReal, 0, 0x2C },
		{ "ActivationTime", INI::parseReal, 0, 0x30 },
		{ "UnitDefinition", rva00423FD8, 0, 0 },
		{ "FormationTemplate", rva00425842, 0, 0 },
		{ "FormationSelection", parseFormationSelectionCriteriaRva00424185, 0, 0 },
		{ "ValidObjectFilter", iniParseObjectFilter, 0, 0x20 },
		{ 0, 0, 0, 0 }
	};
	ini->initFromINI(TheFormationAssistant, dataFieldParse);
}

// --- 0x005742A1 / 0x0057A260 (18B each): table slots parsing an INI block
// into this object through a static field table (retail 0x00C6E36C and
// 0x00C6EE98; the field names are retail's).
#include "../../Include/Common/GlobalLanguageClass.h"

// The table definition is owned by GapBodiesS3E.cpp.


// The table definition is owned by GapBodiesS3E.cpp.


// --- 0x004E12C4 / 0x004E12EF / 0x004E1342 (19B each): field-parse callbacks
// parsing a nested block into their store through the rowed tables 0x00C616C0
// (LivingWorldCampaignObjects' SpawnArmy table), 0x00C61830 and 0x00C61884.
#include "../../Include/Common/SpawnArmy.h"

extern const FieldParse g_00C61830[];
extern const FieldParse g_00C61884[];


void rva004E12EF(INI *ini, void *instance, void *store, const void *userData)
{
	ini->initFromINI(store, g_00C61830);
}

void rva004E1342(INI *ini, void *instance, void *store, const void *userData)
{
	ini->initFromINI(store, g_00C61884);
}

// --- 0x005CB288 / 0x005E3955 / 0x005E9F80 (18B each): more table slots
// parsing an INI block into this object through static field tables (retail
// 0x00C74D20, 0x00C77C10 and 0x00C780D4; the field names are retail's).
// The table definition is owned by GapBodiesS3E.cpp.


// The table definition is owned by GapBodiesS3E.cpp.


// The table definition is owned by GapBodiesS3E.cpp.


// --- 0x003F9CD2 (54B): the pupil / eye-decal anim-object block: build a
// fresh 0x74-byte Rva003F9D08 record (its ctor is rowed at 0x003F9C11), parse
// it through the static table 0x00C37668 (retail's field names) and hand it to
// TheLivingWorldManager (+0x2C4).
class Rva003F9D08
{
public:
	Rva003F9D08() throw();									// 0x003F9C11
private:
	char m_pad[0x74];
};

// The table definition is owned by GapBodiesS3E.cpp, under this class name.
class Rva003F9C11
{
public:
	static const FieldParse s_fieldParseTable[];
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva003F9CD2ManagerView
{
	char m_pad[0x2C4];
	Rva003F9D08 *m_2C4;										// +0x2C4
};

void parseEyeTowerDefinition(INI *ini)
{
	Rva003F9D08 *record = new Rva003F9D08;
	ini->initFromINI(record, Rva003F9C11::s_fieldParseTable);
	((Rva003F9CD2ManagerView *)TheLivingWorldManager)->m_2C4 = record;
}

// Native 5742B3..5742CD (26B): a file-static helper in cl 7.1's SSE register
// convention - the Rva002E0C2B object stays in ECX for the rowed 0x002E0C2B
// call and the float result returns in XMM0 - computing its int value as a
// percentage bonus factor (value * 0.01 + 1). No call to it survives in the
// image; the anchor below only forces cl to emit it in that convention.
// Identity unproven; address-derived names.
#include "../../Include/Common/Rva002E0C2B.h"

static __declspec(noinline) float Rva005742B3(Rva002E0C2B *owner)
{
	return (float)owner->rva002E0C2B() * 0.01f + 1.0f;
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
#include "../../Include/GameLogic/LivingWorldLogic.h"
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../Include/Common/Rva002B2B66.h"
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


