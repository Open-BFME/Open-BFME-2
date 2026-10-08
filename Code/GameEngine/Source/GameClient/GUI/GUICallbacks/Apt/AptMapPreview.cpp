// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// AptMapPreview.cpp -- AptMapPreview members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. The preview drives its living-world window
// at +0x68 (WB member m_livingWorldWindow); start regions come from that
// window's +0x29C -> +0x1C set, asked through 0x004FD8A8 (unnamed).

// game.dat imports msvcr71's strrchr but links its own free (0x00030830,
// see bfmealloc), which the cl line gets by emptying _CRTIMP; string.h is
// read first with the import spelling.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP

#include "../../../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include <vector>
#include <map>

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

class Rva0020E89C;

class Rva004FD8A8Set
{
public:
	Bool rva004FD8A8(Int region);		// 0x004FD8A8
	Bool rva004FCA90();			// 0x004FCA90
	void rva004FD699(Int region, _STL::vector<Rva0020E89C *> *regions);	// 0x004FD699

	unsigned char m_pad00[8];
	AsciiString m_descKey;		// +0x08, passed to TheGameText->fetch
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void reset() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	// cl groups the overloads in reverse: the AsciiString one is slot 0x38,
	// the const char * one 0x3C.
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void initMapStringFile(const AsciiString &filename) = 0;
};

extern GameTextInterface *TheGameText;

struct AptMapPreviewMapInfo
{
	unsigned char m_pad00[0x1c];
	Rva004FD8A8Set *m_startRegions;		// +0x1C
};

class AptLivingWorldWindow
{
public:
	void SelectCampaign(Int campaign);	// 0x0056DB19

	unsigned char m_pad000[0x280];
	unsigned char m_listeners[0x29c - 0x280];	// +0x280, see below
	AptMapPreviewMapInfo *m_info;		// +0x29C
};

// The living-world window's +0x280 listener vector, erased through
// 0x002B7250 and appended through 0x005A0B4C (both rowed under address
// names, with their own views of the vector).
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *listener);
};

struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

// The singleton at 0x00DFE1C8 owns, at +0x268, the object that is told the
// preview's campaign (0x003EF008, unrowed and unnamed in WB).
class Rva003EF008
{
public:
	void rva003EF008();			// 0x003EF008

	void rva003EEBEF(Int value);		// 0x003EEBEF

	unsigned char m_pad00[0x38];
	unsigned char m_field38[0x44 - 0x38];	// +0x38
	Int m_field44;				// +0x44
	void *m_field48;			// +0x48
};

struct Rva00DFE1C8Host
{
	char m_pad[0x268];
	Rva003EF008 *m_field268;		// +0x268
};

extern Rva00DFE1C8Host *g_00DFE1C8;

// The same object marks a region list (0x003EEF38) and unmarks it
// (0x003EEFA0); both are rowed under address-named views taking the
// vector's address.
class Rva003EEFA0
{
public:
	void rva003EEFA0(Int regions);
};

class Rva003EEF38
{
public:
	void rva003EEF38(Int regions);
};

// A living-world region as the preview reads it.
class Rva0020E89C
{
public:
	UnicodeString rva0020E89C();	// 0x0020E89C, the translated name
	UnicodeString rva003F15D1();	// 0x003F15D1, the description

	Int getId() const { return m_id; }

	unsigned char m_pad000[0x12c];
	Int m_id;		// +0x12C, the region id
	unsigned char m_pad130[0x1a2 - 0x130];
	Bool m_1a2;		// +0x1A2
};

// The region marks rowed under address-named views: the holding slot
// (0x003EFE3E) and the +0x268 object's region updates (0x003EE8D8,
// 0x003EE89E); the start region set's region for a start (0x004FC9CE).
class Rva003EFE3E
{
public:
	void rva003EFE3E(int slot);
};

class Rva003EE8D8
{
public:
	void rva003EE8D8(int region);
};

class Rva003EE89E
{
public:
	void rva003EE89E(int region, int list);
};

class Rva0059E2FD;
class Rva004FC9CE
{
public:
	void *rva004FC9CE(const Rva0059E2FD &start);
};

// The living-world region manager (TheLivingWorldLogic +0xB0): regions by
// id (0x0020EAF6) and, at +0x08, the group holding every region.
class Rva0057DB97Group
{
public:
	unsigned char m_pad00[0x2c];
	_STL::vector<Rva0020E89C *> m_regions;	// +0x2C
};

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int id);

	unsigned char m_pad00[0x8];
	Rva0057DB97Group *m_08;	// +0x08
};

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0xb0];
	Rva0020EAF6View *m_regionManager;	// +0xB0
};

extern LivingWorldLogic *TheLivingWorldLogic;

// The holding slot each claimed region id gets (the value type is not
// retail's int map: the destructor 0x0057CF0B is this unit's own).
enum Rva0057DB97Slot
{
};

// AptMapPreviewSetMapDescription.cpp's view of the preview: the player
// slot of the given index, 0 for -1 or an empty game.
class GameSlot
{
public:
	unsigned char m_pad00[0x10];
	Int m_startPos;		// +0x10, the start region id, -1 for none
};

class Rva0057C688
{
public:
	GameSlot *rva0057C688(Int slot);
};

// The preview's ref-counted members (+0x18, +0x6C) release their referent
// through 0x0007DEEF; every instance of the dtor folds to 0x005F8F96.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : m_p(0) {}
	RefCountPtr(T *p) : m_p(p) { if (p) ++p->m_refs; }
	~RefCountPtr() { if (m_p) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_p); }
	T *operator->() const { return m_p; }
	T *get() const { return m_p; }

private:
	T *m_p;
};

// The callback the +0x6C reference holds.
class Rva0057CC15Op
{
public:
	virtual void v00();

	int m_refs;	// +0x04
};

// The preview's +0x6C callback (rowed invoke 0x0057CC15 throws when unset).
class Rva0057CC15Ref
{
public:
	void invoke(int a);

	RefCountPtr<Rva0057CC15Op> m_op;
};

// The campaign manager (0x00E02D6C): the index of a campaign in its +0x14
// vector, -1 when absent (0x003B8BC8, unrowed).
class Rva00E02D6C
{
public:
	Int rva003B8BC8(void *campaign);	// 0x003B8BC8
};

extern Rva00E02D6C *TheCampaignManager;

// A campaign as the strategic scenario list reads it: +0x1C holds the
// display label at +0x04.
struct Rva0057D4F3CampaignInfo
{
	int m_00;
	AsciiString m_label;		// +0x04, passed to TheGameText->fetch
	AsciiString m_description;	// +0x08, likewise
};

struct Rva0057D4F3Campaign
{
	unsigned char m_pad00[0x1c];
	Rva0057D4F3CampaignInfo *m_info;	// +0x1C
};

// 0x003B92B9 (rowed under an address name) collects the manager's
// campaigns into the given vector.
class ModuleData;
class Rva003B8BAA
{
public:
	void rva003B92B9(_STL::vector<const ModuleData *> *out);
	void *rva003B8BF9(int index);	// the campaign at an index
};

class Image;

class GameWindow
{
public:
	int winHide(bool hide);
	int winEnable(bool enable);
	unsigned int winSetStatus(unsigned int status);
	unsigned int winClearStatus(unsigned int status);
	void winSetUserData(void *data);
	int winSetEnabledImage(int index, const Image *image);
	GameWindow *winGetChild();
	GameWindow *winGetNext();
};

class BfmeObjENK;
void bfmeGoENK(BfmeObjENK *o, char v);
void BfmeGadgetListBoxSetAudioFeedback(GameWindow *listbox, bool enable);

void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int selectedIndex, bool dontHide);
int GadgetComboBoxGetLength(GameWindow *comboBox);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);
void GadgetComboBoxHideDropDown(GameWindow *comboBox, bool hide);
void GadgetListBoxReset(GameWindow *listbox);
int Rva00326CF0AddLines(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);
void GadgetListBoxSetTopVisibleEntry(GameWindow *window, int newPos);
void GadgetButtonSetText(GameWindow *button, UnicodeString text);
int GadgetListBoxGetNumEntries(GameWindow *listbox);
UnicodeString GadgetListBoxGetText(GameWindow *listbox, int row, int column);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);
void GadgetListBoxJustifyEntry(GameWindow *listbox, int row, int column, int justification);


// The map picture; the preview deletes one it owns through the virtual
// destructor.
class Image
{
public:
	virtual ~Image();

	unsigned char m_pad04[0x8 - 0x4];
	AsciiString m_name;	// +0x08
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;
class Display;
extern Display *TheDisplay;

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(const void *address, unsigned int size);
extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" int __cdecl strcmp(const char *a, const char *b);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);

// AptCallbackAdders.cpp's by-value callback reference (defined below).
template <class T> class AptRef;

class AptCustomRender;
class AptExternHandler;

// The Apt player (0x00DFE4CC): both adders are pinned by address.
class AptPlayer
{
public:
	void AddExternHandler(const AsciiString &name, Int arg, AptRef<AptExternHandler> handler);	// 0x0022445D
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);		// 0x0022464C
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool flag);	// 0x00225301
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#define TheAptPlayer ((AptPlayer *)g_bfmeAptWindowManager)

// 0x00411458 (pinned; see MpGameSetupSlots.cpp) stores the screen
// reference under the name; 0x0041149A drops it.
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);
void _bfme_closeAptScreen(const AsciiString &name);

// The player's custom render (0x002246B1) and extern handler (0x002244CA)
// removals, rowed under address-named views.
class Rva002246B1
{
public:
	int rva002246B1(const AsciiString *name);
};

class Rva002244CA
{
public:
	int rva002244CA(const AsciiString *name);
};

// The 0x00DFEF18 singleton (address-named view): the living-world map
// view, reset through 0x002BED10 and two virtuals when +0x19 says it is up.
class Rva002D3627Host
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0C() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1C() = 0;
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28(int value) = 0;
	virtual void v2C() = 0;
	virtual void v30() = 0;
	virtual void v34() = 0;
	virtual void v38() = 0;
	virtual void v3C() = 0;
	virtual void v40() = 0;
	virtual void v44() = 0;
	virtual void v48() = 0;
	virtual void v4C() = 0;
	virtual void v50(int value) = 0;
	void rva002BED10();

	unsigned char m_pad04[0x19 - 0x4];
	bool m_19;		// +0x19
};

extern Rva002D3627Host *g_00DFEF18;

// The preview's +0x18 holder of the game (GameInfo): 0x0043DA65 returns
// its validated +0x08 value; the registration clears that directly.
class Rva0043DA65
{
public:
	int rva0043DA65();

	int m_00;
	int m_refs;	// +0x04, the reference count
	int m_08;
};

// The cached map record (ZH MapMetaData): the preview reads the player
// count, the multiplayer flag and the waypoint map.
struct Rva0057DA21Waypoint
{
	Coord3D pos;
};

// ZH Region3D: the map extent.
struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

class MapMetaData
{
public:
	UnicodeString getDescription();		// 0x003009CD
	UnicodeString bfme_getBaseDisplayName();	// 0x00300AEA

	MapMetaData();	// 0x003031D3

	UnicodeString m_displayName;	// +0x00
	UnicodeString m_04;	// +0x04
	Region3D m_extent;	// +0x08
	Int m_numPlayers;	// +0x20
	Bool m_isMultiplayer;	// +0x24
	Bool m_25;	// +0x25
	Bool m_isOfficial;	// +0x26
	unsigned char m_pad27[0x38 - 0x27];
	_STL::map<AsciiString, Rva0057DA21Waypoint> m_waypoints;	// +0x38
	unsigned char m_pad44[0x50 - 0x44];
	AsciiString m_fileName;	// +0x50
	unsigned char m_pad54[0xf8 - 0x54];
	UnicodeString m_f8;	// +0xF8, a second display name
	UnicodeString m_fc;	// +0xFC, getDescription's cached text
};

// ZH MapCache: the map records by lower-case file name.
class MapCache : public _STL::map<AsciiString, MapMetaData>
{
public:
	const MapMetaData *findMap(AsciiString mapName);	// 0x003024BC
};

extern MapCache *TheMapCache;

Image *getMapPreviewImage(AsciiString mapName);

// SkirmishGameOptionsMenu's helpers (ZH MapUtil).
void positionAdditionalImages(MapMetaData *mmd, GameWindow *mapWindow, Bool force);
void positionStartSpotControls(GameWindow *win, GameWindow *mapWindow, Coord3D *pos, MapMetaData *mmd, GameWindow *buttonMapStartPositions[]);

class GameLogic
{
public:
	unsigned char m_pad00[0x114];
	Int m_gameMode;	// +0x114
};

extern GameLogic *TheGameLogic;

// The fields and virtuals of the game the preview reads.
class GameInfo
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual bool amIHost() const = 0;	// +0x30
	AsciiString getMap() const;		// 0x0023E943
	GameSlot *getSlot(Int index);		// 0x003FF29F

	unsigned char m_pad04[0x10 - 0x4];
	bool m_selectStartPoint;	// +0x10
	unsigned char m_pad11[0x58 - 0x11];
	int m_campaign;		// +0x58, a campaign manager index
	unsigned char m_pad5c[0x8c - 0x5c];
	bool m_8c;		// +0x8C, no region picks while set
	unsigned char m_pad8d[0xc8 - 0x8d];
	int m_c8;		// +0xC8
};

// The preview's living world region listener base (vtable 0x0086E350, its
// four slots empty; 0x0057428C is its dtor's folded copy).
class Rva0086E350Listener
{
public:
	virtual void v00(void *a) {}
	virtual void v04(void *a, void *b) {}
	virtual void v08(void *a, void *b, void *c) {}
	virtual void v0C(void *a, void *b, void *c) {}
	~Rva0086E350Listener() {}
};

// The interface the +0x04 callback implements (vtable 0x008363B8: its
// deleting dtor 0x003EE711 and a pure slot).
class Rva003EE711
{
public:
	virtual ~Rva003EE711() {}
	virtual void *v04(void *color, void *arg) = 0;
};

// The preview's +0x04 callback (vtable 0x0086F31C, ctor 0x0057C50C, dtor
// 0x0057C51E): calls back into its owner.
class Rva0057C50C : public Rva003EE711
{
public:
	Rva0057C50C(void *owner) : m_owner(owner) {}
	virtual void *v04(void *color, void *arg);

	void *m_owner;
};

// What the listener's slot 1 hands the preview: +0x1C names the region
// the highlight moves to.
struct Rva0057D8F5Event
{
	unsigned char m_pad00[0x1c];
	Rva0020E89C *m_region;	// +0x1C
};

class AptMapPreview : public Rva0086E350Listener
{
public:
	AptMapPreview(Rva0043DA65 *game);
	Bool rva0057CB7D(Int index);	// may a player start at this index
	virtual void v04(void *a, void *b);
	virtual void v0C(void *a, void *b, void *c);
	Bool AllowsStartInRegion(Int region);
	void SelectCampaign(Int campaign);
	void UpdateStrategicScenarioDesc();	// 0x0057C99E
	Int rva0057C621();
	void rva0057C5B9(const Coord2D *pos, const Coord2D *size, void *unused3, void *unused4);
	void GameMapType(int query, char *result, bool skip);
	void MapGadgetInit(const char *name, void *argument, GameWindow *window);
	void rva0057E45C();
	void rva0057D4F3();	// fills the strategic scenario combo box
	void rva0057E058();	// refreshes the preview
	void *GetStrategicScenarioComboBoxSelectedCampaign();	// 0x0057C649
	MapMetaData *rva0057D922(const AsciiString &map);	// looks the map up
	void UpdateMapTitle(MapMetaData *map);	// 0x0057C8D1
	void rva0057DDAE(MapMetaData *map);
	void rva0057D19A(MapMetaData *map);
	void bfmeSetMapDescription(MapMetaData *map);	// 0x0057C892
	void rva0057D10F(MapMetaData *map);	// the map picture
	void GetRegionsInOwnershipSet(Int region, _STL::vector<Rva0020E89C *> *regions);
	void rva0057D746(Rva0020E89C *previous, Rva0020E89C *current);
	void rva0057D85D(Rva0020E89C *region);
	void rva0057D5E5();
	void rva0057DA21(MapMetaData *map);
	void rva0057DB97();

private:
	Rva0057C50C m_field04;	// +0x04, handed to the campaign owner
	_STL::vector<Rva0020E89C *> m_regions;	// +0x0C, a region group
	RefCountPtr<Rva0043DA65> m_18;	// +0x18
	int m_mode;	// +0x1C (OpenPlay 0, Strategic 1)
	GameWindow *m_currentMap;	// +0x20
	GameWindow *m_mapPicture;	// +0x24
	GameWindow *m_mapInfo;	// +0x28
	GameWindow *m_mapDescription;	// +0x2C
	GameWindow *m_currentMapChildren[8];	// +0x30
	GameWindow *m_strategicScenarioComboBox;	// +0x50
	GameWindow *m_strategicScenarioDesc;	// +0x54
	GameWindow *m_strategicTerritoryDesc;	// +0x58
	Image *m_picture;	// +0x5C
	bool m_ownsPicture;	// +0x60
	bool m_enableStartSpots;	// +0x61, enables the start spot buttons
	unsigned char m_pad62[0x64 - 0x62];
	MapMetaData *m_defaultMap;	// +0x64, the ctor's 8-player placeholder map
	AptLivingWorldWindow *m_livingWorldWindow;	// +0x68
	Rva0057CC15Ref m_regionPicked;	// +0x6C
};

// AptMapPreview::AllowsStartInRegion, retail 0x0057C525.
Bool AptMapPreview::AllowsStartInRegion(Int region)
{
	if (m_livingWorldWindow == 0)
		return false;
	if (m_livingWorldWindow->m_info == 0)
		return false;
	if (m_livingWorldWindow->m_info->m_startRegions == 0)
		return false;
	return m_livingWorldWindow->m_info->m_startRegions->rva004FD8A8(region);
}

// AptMapPreview::SelectCampaign, retail 0x0057CA2D. WB asserts the window
// exists.
void AptMapPreview::SelectCampaign(Int campaign)
{
	if (m_livingWorldWindow == 0)
		return;
	m_livingWorldWindow->SelectCampaign(campaign);
	Rva003EF008 *owner = g_00DFE1C8->m_field268;
	if (owner)
	{
		owner->m_field44 = 1;
		if (m_livingWorldWindow->m_info)
		{
			owner->m_field48 = &m_field04;
			owner->rva003EF008();
		}
	}
	UpdateStrategicScenarioDesc();
}

// AptMapPreview::rva0057C621, retail 0x0057C621: the selected campaign's
// index in the campaign manager, -1 without the strategic scenario combo
// box (+0x50, as GetStrategicScenarioComboBoxSelectedCampaign 0x0057C649
// reads it) or a selected campaign.
Int AptMapPreview::rva0057C621()
{
	if (m_strategicScenarioComboBox != 0 && m_livingWorldWindow != 0 && m_livingWorldWindow->m_info != 0)
		return TheCampaignManager->rva003B8BC8(m_livingWorldWindow->m_info);
	return -1;
}

// ?UpdateStrategicScenarioDesc@AptMapPreview@@QAEXXZ @0x0057C99E 143B
// Evidence: pinned name; callers 0x0057CA6F SelectCampaign plus 0x0057D5BF
// 0x0057E186 0x0057E374; callees rowed GadgetListBoxReset 0x003247E5
// StringBase copy 0x00037050 AddLines 0x00326CF0 SetTop 0x0032544C
// releaseBuffer 0x00036E70; TheGameText fetch slot 0x38; living +0x68
// info +0x29C set +0x1C key +0x08 AsciiString.
void AptMapPreview::UpdateStrategicScenarioDesc()
{
	if (m_strategicScenarioDesc == 0)
		return;
	GadgetListBoxReset(m_strategicScenarioDesc);
	AptMapPreviewMapInfo *info = m_livingWorldWindow->m_info;
	if (info == 0)
		return;
	Rva004FD8A8Set *set = info->m_startRegions;
	if (set == 0)
		return;
	UnicodeString text = TheGameText->fetch(set->m_descKey, 0);
	Rva00326CF0AddLines(m_strategicScenarioDesc, text, -1, 0, -1, true);
	GadgetListBoxSetTopVisibleEntry(m_strategicScenarioDesc, 0);
}

// AptMapPreview::rva0057C5B9, retail 0x0057C5B9: the "AptMapPreview::Picture"
// custom render (bound by 0x0057E4C2): draws the +0x5C picture over the
// given rectangle, dropping a picture that is no longer readable.
void AptMapPreview::rva0057C5B9(const Coord2D *pos, const Coord2D *size, void *unused3, void *unused4)
{
	if (m_picture == 0)
		return;
	if (IsBadReadPtr(m_picture, 0x34))
	{
		m_picture = 0;
		return;
	}
	((W3DDisplay *)TheDisplay)->rva0004D6B3(m_picture, pos->x, pos->y, pos->x + size->x, pos->y + size->y, -1, 2);
}

// Retail 0x0057C549, 50 bytes: bound as "AptMapPreview::GameMapType" by
// 0x0057E45C, an Apt query answering the map type of the +0x1C mode.
void AptMapPreview::GameMapType(int query, char *result, bool skip)
{
	if (query == 0 && !skip)
	{
		switch (m_mode)
		{
		case 0:
			strcpy(result, "OpenPlay");
			break;
		case 1:
			strcpy(result, "Strategic");
			break;
		}
	}
}

// Retail 0x0057D4F3, 242 bytes. Name unknown. Refills the strategic
// scenario combo box (+0x50) with the campaign manager's labelled
// campaigns, each entry carrying the campaign's manager index, selects
// the first and refreshes the description.
void AptMapPreview::rva0057D4F3()
{
	if (m_strategicScenarioComboBox == 0)
		return;
	GadgetComboBoxReset(m_strategicScenarioComboBox);
	_STL::vector<Rva0057D4F3Campaign *> campaigns;
	((Rva003B8BAA *)TheCampaignManager)->rva003B92B9((_STL::vector<const ModuleData *> *)&campaigns);
	for (_STL::vector<Rva0057D4F3Campaign *>::iterator it = campaigns.begin(); it != campaigns.end(); ++it)
	{
		Rva0057D4F3Campaign *campaign = *it;
		if (campaign->m_info != 0)
		{
			UnicodeString text = TheGameText->fetch(campaign->m_info->m_label, 0);
			int index = GadgetComboBoxAddEntry(m_strategicScenarioComboBox, text, -1);
			GadgetComboBoxSetItemData(m_strategicScenarioComboBox, index, (void *)TheCampaignManager->rva003B8BC8(campaign));
		}
	}
	GadgetComboBoxSetSelectedPos(m_strategicScenarioComboBox, 0, false);
	UpdateStrategicScenarioDesc();
}

// Retail 0x0057D5E5, 292 bytes. Name unknown. Undoes the registration
// (0x0057E45C) and MapGadgetInit: drops the three Apt bindings, forgets
// the gadgets, leaves the living-world window (resetting the map view
// when it is up), deletes an owned picture and clears the CurrentMap
// children. Retail gives the last binding's name a fresh slot.
void AptMapPreview::rva0057D5E5()
{
	{
		AsciiString name("AptMapPreview::Picture");
		((Rva002246B1 *)g_bfmeAptWindowManager)->rva002246B1(&name);
	}
	{
		AsciiString name("AptMapPreview::MapGadgetInit");
		_bfme_closeAptScreen(name);
	}
	{
		AsciiString name("AptMapPreview::GameMapType");
		((Rva002244CA *)g_bfmeAptWindowManager)->rva002244CA(&name);
	}
	m_currentMap = 0;
	m_mapPicture = 0;
	m_mapInfo = 0;
	m_mapDescription = 0;
	m_strategicScenarioComboBox = 0;
	m_strategicScenarioDesc = 0;
	m_strategicTerritoryDesc = 0;
	if (m_livingWorldWindow != 0)
	{
		((Rva002B7250 *)m_livingWorldWindow->m_listeners)->rva002B7250((CreateAHeroData *)this);
		m_livingWorldWindow = 0;
		if (g_00DFEF18->m_19)
		{
			g_00DFEF18->rva002BED10();
			g_00DFEF18->v50(0);
			g_00DFEF18->v28(0);
		}
	}
	if (m_ownsPicture && m_picture != 0)
	{
		::delete m_picture;
		m_picture = 0;
		m_ownsPicture = false;
	}
	memset(m_currentMapChildren, 0, sizeof(m_currentMapChildren));
}

// Retail 0x0057D709, 61 bytes. Name unknown. Refills the list with the
// regions the campaign's start-region set groups with the given one.
void AptMapPreview::GetRegionsInOwnershipSet(Int region, _STL::vector<Rva0020E89C *> *regions)
{
	regions->clear();
	if (m_livingWorldWindow != 0 && m_livingWorldWindow->m_info != 0 && m_livingWorldWindow->m_info->m_startRegions != 0)
		m_livingWorldWindow->m_info->m_startRegions->rva004FD699(region, regions);
}

// Retail 0x0057D746, 279 bytes. Name unknown. Moves the region highlight:
// unmarks the previous region's group, marks the current one's when the
// campaign allows a start there, and lists the current region's name and
// description in StrategicTerritoryDescription (+0x58).
void AptMapPreview::rva0057D746(Rva0020E89C *previous, Rva0020E89C *current)
{
	if (m_strategicTerritoryDesc != 0)
		GadgetListBoxReset(m_strategicTerritoryDesc);
	Rva003EF008 *owner = g_00DFE1C8->m_field268;
	if (owner != 0)
	{
		if (previous != 0)
		{
			m_regions.clear();
			GetRegionsInOwnershipSet((Int)previous, &m_regions);
			((Rva003EEFA0 *)owner)->rva003EEFA0((Int)&m_regions);
		}
		if (current != 0)
		{
			if (AllowsStartInRegion((Int)current))
			{
				m_regions.clear();
				GetRegionsInOwnershipSet((Int)current, &m_regions);
				((Rva003EEF38 *)owner)->rva003EEF38((Int)&m_regions);
			}
			UnicodeString text = current->rva0020E89C();
			text.concat(L"\n");
			text.concat(current->rva003F15D1());
			Rva00326CF0AddLines(m_strategicTerritoryDesc, text, -1, 0, -1, true);
		}
	}
}

// Retail 0x0057D85D, 152 bytes. Name unknown. A region pick (ignored
// while the game's +0x8C is set): when the campaign allows a start there
// and the +0x6C callback is bound, reports the first region of its group
// a player slot holds (else the region itself) and highlights it.
void AptMapPreview::rva0057D85D(Rva0020E89C *region)
{
	GameInfo *info = (GameInfo *)m_18->rva0043DA65();
	if (info != 0 && info->m_8c)
		return;
	if (!AllowsStartInRegion((Int)region))
		return;
	if (m_regionPicked.m_op.get() == 0)
		return;
	Rva0020E89C *picked = region;
	GetRegionsInOwnershipSet((Int)region, &m_regions);
	for (unsigned int i = 0; i < m_regions.size(); ++i)
	{
		if (((Rva0057C688 *)this)->rva0057C688(m_regions[i]->getId()) != 0)
		{
			picked = m_regions[i];
			break;
		}
	}
	m_regionPicked.invoke((int)picked);
	rva0057D746(0, picked);
}

// Retail 0x0057E058, 499 bytes. Name unknown. Refreshes the preview from
// the game's map: title, the three map panels, description and picture;
// then points the strategic scenario combo box at the game's campaign
// (adopting the selected one when the host's game has none) and sets
// "APT:SelectStartPoint" to its text or a blank.
void AptMapPreview::rva0057E058()
{
	GameInfo *info = (GameInfo *)m_18->rva0043DA65();
	MapMetaData *map = info ? rva0057D922(info->getMap()) : 0;
	UpdateMapTitle(map);
	rva0057DDAE(map);
	rva0057D19A(map);
	bfmeSetMapDescription(map);
	rva0057D10F(map);
	if (m_strategicScenarioComboBox != 0)
	{
		bool enable = true;
		if (info != 0)
		{
			int campaign = info->m_campaign;
			int selected = (int)GetStrategicScenarioComboBoxSelectedCampaign();
			int index = rva0057C621();
			if (info->amIHost())
			{
				if (info->m_c8 == 0)
					enable = false;
				if (campaign <= 0)
					info->m_campaign = selected;
			}
			if (selected != campaign || index != campaign)
			{
				int count = GadgetComboBoxGetLength(m_strategicScenarioComboBox);
				for (int i = 0; i < count; ++i)
				{
					if ((int)GadgetComboBoxGetItemData(m_strategicScenarioComboBox, i) == campaign)
					{
						GadgetComboBoxSetSelectedPos(m_strategicScenarioComboBox, i, false);
						SelectCampaign(campaign);
					}
				}
			}
			GadgetComboBoxHideDropDown(m_strategicScenarioComboBox, enable);
		}
		else
			UpdateStrategicScenarioDesc();
	}
	if (info != 0 && info->m_selectStartPoint)
	{
		AsciiString key("APT:SelectStartPoint");
		g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:SelectStartPoint"), false);
	}
	else
		g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:SelectStartPoint"), UnicodeString(L" "), false);
}

// Retail 0x0057E25D, 382 bytes: "AptMapPreview::MapGadgetInit", the screen
// reference bound by 0x0057E45C. Files each named gadget in its member,
// hides the first eight children of "CurrentMap", moves the preview's
// listener to a new "LivingWorld" window, then refreshes the preview
// (0x0057E058).
void AptMapPreview::MapGadgetInit(const char *name, void *argument, GameWindow *window)
{
	if (window == 0)
		return;
	if (strcmp(name, "MapInfo") == 0)
	{
		m_mapInfo = window;
		bfmeGoENK((BfmeObjENK *)window, 1);
		BfmeGadgetListBoxSetAudioFeedback(m_mapInfo, true);
	}
	else if (strcmp(name, "MapDescription") == 0)
	{
		m_mapDescription = window;
		bfmeGoENK((BfmeObjENK *)window, 1);
		BfmeGadgetListBoxSetAudioFeedback(m_mapDescription, true);
	}
	else if (strcmp(name, "MapPicture") == 0)
	{
		m_mapPicture = window;
	}
	else if (strcmp(name, "CurrentMap") == 0)
	{
		int count = 0;
		m_currentMap = window;
		GameWindow *child = window->winGetChild();
		while (child != 0 && count < 8)
		{
			m_currentMapChildren[count++] = child;
			child->winHide(true);
			child->winSetStatus(0x20000);
			child = child->winGetNext();
		}
	}
	else if (strcmp(name, "StrategicScenarioType") == 0)
	{
		m_strategicScenarioComboBox = window;
		rva0057D4F3();
	}
	else if (strcmp(name, "StrategicScenarioDescription") == 0)
	{
		m_strategicScenarioDesc = window;
		UpdateStrategicScenarioDesc();
	}
	else if (strcmp(name, "StrategicTerritoryDescription") == 0)
	{
		m_strategicTerritoryDesc = window;
	}
	else if (strcmp(name, "LivingWorld") == 0)
	{
		if (m_livingWorldWindow != 0)
			((Rva002B7250 *)m_livingWorldWindow->m_listeners)->rva002B7250((CreateAHeroData *)this);
		m_livingWorldWindow = (AptLivingWorldWindow *)window;
		((Rva005A0B4CList *)m_livingWorldWindow->m_listeners)->append((Rva002BA8F1Listener *)this);
		SelectCampaign(0);
	}
	rva0057E058();
}

// The handlers are bound as {object, method} pairs, built in place by the
// rowed constructor 0x00579E47 (Rva00579E47Delegate.cpp; the user-declared
// copy constructor makes cl build it in the argument slot); the callee
// releases the reference.
typedef void (AptMapPreview::*AptMapPreviewHandler)(void);

struct DelegateDesc
{
	DelegateDesc(AptMapPreview *object, AptMapPreviewHandler method) : m_object(object), m_method(method) {}

	AptMapPreview *m_object;
	AptMapPreviewHandler m_method;
};

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(DelegateDesc desc) : Rva00579E47(desc) {}
};

// Retail 0x0057E45C, 250 bytes. Name unknown. The preview's Apt
// registration (called by AptMpGameSetup::rva0044303D on its +0x60
// member): binds "AptMapPreview::MapGadgetInit" as the screen reference,
// "AptMapPreview::Picture" as a custom render and
// "AptMapPreview::GameMapType" as extern handler 0. Retail packs the last
// block's AsciiString fresh but keeps its pair in the shared slot
// (sub esp,0x14), which needs the trailing scope.
void AptMapPreview::rva0057E45C()
{
	m_18->m_08 = 0;
	{
		AsciiString name("AptMapPreview::MapGadgetInit");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(DelegateDesc(this, reinterpret_cast<AptMapPreviewHandler>(&AptMapPreview::MapGadgetInit))));
	}
	{
		AsciiString name("AptMapPreview::Picture");
		TheAptPlayer->AddCustomRender(name, AptRef<AptCustomRender>(DelegateDesc(this, reinterpret_cast<AptMapPreviewHandler>(&AptMapPreview::rva0057C5B9))));
	}
	{
		AsciiString name("AptMapPreview::GameMapType");
		TheAptPlayer->AddExternHandler(name, 0, AptRef<AptExternHandler>(DelegateDesc(this, reinterpret_cast<AptMapPreviewHandler>(&AptMapPreview::GameMapType))));
		{
			DelegateDesc unused(0, 0);
			(void)unused;
		}
	}
}

// AptMapPreview::rva0057DA21, retail 0x0057DA21 (374 bytes). Name unknown.
// The preview's start spot pass, ZH positionStartSpots' shape: a real map
// places a button on each Player_%d_Start waypoint (multiplayer maps, game
// mode 3) and blanks the rest; no map or the placeholder map blanks all.
void AptMapPreview::rva0057DA21(MapMetaData *map)
{
	if (map != 0 && map != m_defaultMap)
	{
		m_currentMap->winEnable(true);
		positionAdditionalImages(map, m_currentMap, true);
		AsciiString waypointName;
		Int i = 0;
		if (map->m_isMultiplayer && TheGameLogic->m_gameMode == 3)
		{
			for (; i < map->m_numPlayers; ++i)
			{
				waypointName.format("Player_%d_Start", i + 1);
				_STL::map<AsciiString, Rva0057DA21Waypoint>::iterator it = map->m_waypoints.find(waypointName);
				if (it != map->m_waypoints.end())
				{
					positionStartSpotControls(m_currentMapChildren[i], m_currentMap, &(*it).second.pos, map, m_currentMapChildren);
					if (m_currentMapChildren[i] != 0)
					{
						m_currentMapChildren[i]->winEnable(m_enableStartSpots);
						m_currentMapChildren[i]->winHide(false);
					}
				}
			}
		}
		for (; i < 8; ++i)
		{
			if (m_currentMapChildren[i] != 0)
			{
				m_currentMapChildren[i]->winHide(true);
				GadgetButtonSetText(m_currentMapChildren[i], TheGameText->fetch("GUI:Blank"));
			}
		}
	}
	else
	{
		m_currentMap->winEnable(false);
		positionAdditionalImages(0, m_currentMap, true);
		for (Int i = 0; i < 8; ++i)
		{
			if (m_currentMapChildren[i] != 0)
			{
				m_currentMapChildren[i]->winHide(true);
				GadgetButtonSetText(m_currentMapChildren[i], TheGameText->fetch("GUI:Blank"));
			}
		}
	}
}

// AptMapPreview::rva0057DDAE, retail 0x0057DDAE (589 bytes). Name unknown.
// Puts the map picture on the current-map window: the living-world map in
// strategic mode, else the map's preview (ScrollShroud over _art.tga art)
// or MissingMap, then runs the start spot pass. ZH positionStartSpots'
// picture half.
void AptMapPreview::rva0057DDAE(MapMetaData *map)
{
	Int mode = m_mode;
	Bool strategic = mode == 1;
	if (strategic)
	{
		if (m_currentMap == 0)
			return;
		static const Image *livingWorldMap = TheMappedImageCollection->findImageByName(AsciiString("AptLWMap"));
		m_currentMap->winSetEnabledImage(1, 0);
		m_currentMap->winSetStatus(0x80);
		m_currentMap->winSetEnabledImage(0, livingWorldMap);
		return;
	}
	if (m_currentMap == 0)
		return;
	m_currentMap->winSetEnabledImage(1, 0);
	if (map == 0)
	{
		m_currentMap->winSetUserData(0);
		static const Image *unknownImage = TheMappedImageCollection->findImageByName(AsciiString("MissingMap"));
		if (unknownImage)
		{
			m_currentMap->winSetStatus(0x80);
			m_currentMap->winSetEnabledImage(0, unknownImage);
		}
		else
		{
			m_currentMap->winClearStatus(0x80);
		}
	}
	else
	{
		Image *image = getMapPreviewImage(map->m_fileName);
		if (image != 0 && image->m_name.endsWithNoCase("_art.tga"))
			m_currentMap->winSetEnabledImage(1, TheMappedImageCollection->findImageByName(AsciiString("ScrollShroud")));
		m_currentMap->winSetUserData(map);
		if (image != 0)
		{
			m_currentMap->winSetStatus(0x80);
			m_currentMap->winSetEnabledImage(0, image);
		}
		else
		{
			static const Image *unknownImage = TheMappedImageCollection->findImageByName(AsciiString("MissingMap"));
			if (unknownImage)
			{
				m_currentMap->winSetStatus(0x80);
				m_currentMap->winSetEnabledImage(0, unknownImage);
			}
			else
			{
				m_currentMap->winClearStatus(0x80);
			}
		}
	}
	rva0057DA21(map);
}

// AptMapPreview::rva0057DB97, retail 0x0057DB97 (535 bytes). Name unknown.
// Strategic mode: hands each player's start region, and the regions the
// start set groups with it, to that player's slot; every other region
// loses its holder (and, when start-eligible, goes back to the +0x268
// object's +0x38 list). Sole caller 0x0057DFFB.
void AptMapPreview::rva0057DB97()
{
	if (m_mode != 1)
		return;
	if (m_livingWorldWindow == 0)
		return;
	GameInfo *info = (GameInfo *)m_18->rva0043DA65();
	if (info == 0 || m_livingWorldWindow == 0 || TheLivingWorldLogic == 0)
		return;
	Rva0020EAF6View *manager = TheLivingWorldLogic->m_regionManager;
	if (manager == 0 || m_livingWorldWindow->m_info == 0)
		return;
	Rva004FD8A8Set *startRegions = m_livingWorldWindow->m_info->m_startRegions;
	if (startRegions == 0)
		return;
	Rva003EF008 *owner = g_00DFE1C8->m_field268;
	_STL::map<Int, Rva0057DB97Slot> claimed;
	for (Int i = 0; i < 8; ++i)
	{
		Int startPos = info->getSlot(i)->m_startPos;
		if (startPos == -1)
			continue;
		Rva0020E89C *region = manager->rva0020EAF6(startPos);
		if (region == 0)
			continue;
		GetRegionsInOwnershipSet((Int)region, &m_regions);
		Rva0020E89C *start = (Rva0020E89C *)((Rva004FC9CE *)startRegions)->rva004FC9CE(*(Rva0059E2FD *)region);
		claimed[start->getId()] = (Rva0057DB97Slot)i;
		((Rva003EFE3E *)start)->rva003EFE3E(i);
		if (owner != 0)
			((Rva003EE8D8 *)owner)->rva003EE8D8((int)start);
		for (_STL::vector<Rva0020E89C *>::iterator it = m_regions.begin(); it != m_regions.end(); ++it)
		{
			Rva0020E89C *other = *it;
			if (other == start)
				continue;
			claimed[other->getId()] = (Rva0057DB97Slot)i;
			((Rva003EFE3E *)other)->rva003EFE3E(i);
			if (owner != 0)
				((Rva003EE8D8 *)owner)->rva003EE8D8((int)region);
		}
	}
	Rva0057DB97Group *group = manager->m_08;
	if (group != 0)
	{
		for (_STL::vector<Rva0020E89C *>::iterator it = group->m_regions.begin(); it != group->m_regions.end(); ++it)
		{
			Rva0020E89C *region = *it;
			if (claimed.find(region->getId()) == claimed.end())
			{
				((Rva003EFE3E *)region)->rva003EFE3E(-1);
				if (owner != 0 && region->m_1a2 && !startRegions->rva004FCA90() && startRegions->rva004FD8A8((Int)region))
					((Rva003EE89E *)owner)->rva003EE89E((int)region, (int)owner->m_field38);
			}
		}
		if (info->m_8c && g_00DFE1C8 != 0 && info->m_c8 != 0 && owner != 0)
			owner->rva003EEBEF(info->m_c8);
	}
}

// AptMapPreview::rva0057D922, retail 0x0057D922 (255 bytes). Name unknown.
// The map record for a map file name: TheMapCache's entry under the lower
// case name, else the ctor's placeholder record relabelled with the
// translated file name (path stripped), one player.
MapMetaData *AptMapPreview::rva0057D922(const AsciiString &map)
{
	AsciiString lowerMap = map;
	lowerMap.toLower();
	MapCache::iterator it = TheMapCache->find(lowerMap);
	if (it != TheMapCache->end())
		return &(*it).second;
	UnicodeString name;
	AsciiString fileName;
	const char *slash = strrchr(map.str(), '\\');
	if (slash != 0)
		fileName = slash + 1;
	else
		fileName = map;
	name.translate(fileName);
	m_defaultMap->m_numPlayers = 1;
	m_defaultMap->m_displayName = name;
	m_defaultMap->m_f8 = name;
	m_defaultMap->m_fileName = map;
	return m_defaultMap;
}

// AptMapPreview::rva0057D19A, retail 0x0057D19A (852 bytes). Name unknown.
// Fills the map info list box unless it already shows this map's
// description: a campaign's name and description (strategic mode) or the
// map's base display name and description, then "Free For All" as the
// lobby game type; no map blanks both texts.
// retail stores no EH state around the comparison: string_base.cpp's
// specialization is nonthrowing, as AsciiString's compare is.
template <>
int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();

void AptMapPreview::rva0057D19A(MapMetaData *map)
{
	if (m_mapInfo == 0)
		return;
	if (map != 0 && GadgetListBoxGetNumEntries(m_mapInfo) > 0 && map->getDescription().compare(GadgetListBoxGetText(m_mapInfo, 0, 0)) == 0)
		return;
	GadgetListBoxReset(m_mapInfo);
	if (map != 0)
	{
		m_mapInfo->winEnable(true);
		Int index = -1;
		if (m_mode == 1)
		{
			GameInfo *info = (GameInfo *)m_18->rva0043DA65();
			if (info == 0)
				return;
			Int campaignIndex = info->m_campaign;
			if (campaignIndex >= 0)
			{
				Rva0057D4F3CampaignInfo *campaign = ((Rva0057D4F3Campaign *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BF9(campaignIndex))->m_info;
				UnicodeString name;
				UnicodeString description;
				if (campaign != 0)
				{
					name = TheGameText->fetch(campaign->m_label);
					description = TheGameText->fetch(campaign->m_description);
				}
				g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:CurrentMapName"), name, false);
				index = GadgetListBoxAddEntryText(m_mapInfo, description, -1, -1, -1, true);
			}
		}
		else
		{
			{
				AsciiString key("APT:CurrentMapName");
				g_bfmeAptWindowManager->bfmeSetText(key, map->bfme_getBaseDisplayName(), false);
			}
			index = GadgetListBoxAddEntryText(m_mapInfo, map->getDescription(), -1, -1, -1, true);
		}
		if (index >= 0)
			GadgetListBoxJustifyEntry(m_mapInfo, index, 0, 2);
		g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:LobbyGameType"), UnicodeString(L"Free For All"), false);
	}
	else
	{
		g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:CurrentMapName"), UnicodeString(L" "), false);
		g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:LobbyGameType"), UnicodeString(L" "), false);
	}
}

// Its two owners (0x0043AE44, 0x00441ECE) build the preview in place at
// their +0x18 around a new game holder. The default map is the 8-player
// placeholder rva0057D922 fills for maps the cache lacks; both lobby texts
// start blank.
AptMapPreview::AptMapPreview(Rva0043DA65 *game)
	: m_field04(this), m_18(game), m_mode(-1), m_currentMap(0), m_mapPicture(0), m_mapInfo(0), m_mapDescription(0),
	  m_strategicScenarioComboBox(0), m_strategicScenarioDesc(0), m_strategicTerritoryDesc(0), m_picture(0),
	  m_ownsPicture(false), m_enableStartSpots(false), m_defaultMap(0), m_livingWorldWindow(0)
{
	memset(m_currentMapChildren, 0, sizeof(m_currentMapChildren));
	m_defaultMap = new MapMetaData;
	m_defaultMap->m_04 = L"";
	m_defaultMap->m_displayName = L"";
	m_defaultMap->m_isOfficial = false;
	m_defaultMap->m_fileName = "";
	m_defaultMap->m_numPlayers = 8;
	m_defaultMap->m_isMultiplayer = true;
	m_defaultMap->m_extent.lo.x = 0.0f;
	m_defaultMap->m_extent.lo.y = 0.0f;
	m_defaultMap->m_extent.lo.z = 0.0f;
	m_defaultMap->m_extent.hi.x = 1.0f;
	m_defaultMap->m_extent.hi.y = 1.0f;
	m_defaultMap->m_extent.hi.z = 0.0f;
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:CurrentMapName"), UnicodeString(L" "), false);
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:LobbyGameType"), UnicodeString(L" "), false);
}

// Listener slot 1, retail 0x0057D8F5: moves the highlight from the region
// in b to the event's region.
void AptMapPreview::v04(void *a, void *b)
{
	rva0057D746((Rva0020E89C *)b, ((Rva0057D8F5Event *)a)->m_region);
}

// Listener slot 3, retail 0x0057D908: a region pick when b names a region
// and c is clear.
void AptMapPreview::v0C(void *a, void *b, void *c)
{
	if (b != 0 && c == 0)
		rva0057D85D((Rva0020E89C *)b);
}

// Retail 0x0057CB7D, 152 bytes. Name unknown. Whether the index is a usable
// start position: below the cached map's player count (at most 8) in open
// play, or a living world region the campaign allows a start in and whose
// +0x1A2 flag is set in strategic mode.
Bool AptMapPreview::rva0057CB7D(Int index)
{
	GameInfo *info = (GameInfo *)m_18->rva0043DA65();
	if (info == 0)
		return false;
	switch (m_mode)
	{
	case 0:
		if ((unsigned int)index > 8)
			return false;
		{
			const MapMetaData *md = TheMapCache->findMap(info->getMap());
			if (md == 0)
				return false;
			return index < md->m_numPlayers;
		}
	case 1:
		if (index == -1)
			return false;
		{
			Rva0020EAF6View *view = TheLivingWorldLogic->m_regionManager;
			if (view == 0)
				return false;
			Rva0020E89C *region = view->rva0020EAF6(index);
			if (region == 0)
				return false;
			return AllowsStartInRegion((Int)region) && region->m_1a2;
		}
	}
	return false;
}
