// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// AptMapPreview.cpp -- AptMapPreview members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. The preview drives its living-world window
// at +0x68 (WB member m_livingWorldWindow); start regions come from that
// window's +0x29C -> +0x1C set, asked through 0x004FD8A8 (unnamed).

#include "../../../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include <vector>
#include <map>

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

class Rva004FD8A8Set
{
public:
	Bool rva004FD8A8(Int region);		// 0x004FD8A8
	void rva004FD699(Int region, _STL::vector<void *> *regions);	// 0x004FD699

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

	unsigned char m_pad00[0x44];
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

	unsigned char m_pad000[0x12c];
	Int m_slot;		// +0x12C, the slot of the player holding it
};

// AptMapPreviewSetMapDescription.cpp's view of the preview: the player
// slot of the given index, 0 for -1 or an empty game.
class GameSlot;
class Rva0057C688
{
public:
	GameSlot *rva0057C688(Int slot);
};

// The preview's +0x6C callback (rowed invoke 0x0057CC15 throws when unset).
class Rva0057CC15Ref
{
public:
	void invoke(int a);

	void *m_op;
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
};

class GameWindow
{
public:
	int winHide(bool hide);
	int winEnable(bool enable);
	unsigned int winSetStatus(unsigned int status);
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


// The map picture; the preview deletes one it owns through the virtual
// destructor.
class Image
{
public:
	virtual ~Image();
};
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
	int m_04;
	int m_08;
};

// The cached map record (ZH MapMetaData): the preview reads the player
// count, the multiplayer flag and the waypoint map.
struct Rva0057DA21Waypoint
{
	Coord3D pos;
};

class MapMetaData
{
public:
	unsigned char m_pad00[0x20];
	Int m_numPlayers;	// +0x20
	Bool m_isMultiplayer;	// +0x24
	unsigned char m_pad25[0x38 - 0x25];
	_STL::map<AsciiString, Rva0057DA21Waypoint> m_waypoints;	// +0x38
};

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

	unsigned char m_pad04[0x10 - 0x4];
	bool m_selectStartPoint;	// +0x10
	unsigned char m_pad11[0x58 - 0x11];
	int m_campaign;		// +0x58, a campaign manager index
	unsigned char m_pad5c[0x8c - 0x5c];
	bool m_8c;		// +0x8C, no region picks while set
	unsigned char m_pad8d[0xc8 - 0x8d];
	int m_c8;		// +0xC8
};

class AptMapPreview
{
public:
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
	void rva0057D709(Int region, _STL::vector<void *> *regions);
	void rva0057D746(Rva0020E89C *previous, Rva0020E89C *current);
	void rva0057D85D(Rva0020E89C *region);
	void rva0057D5E5();
	void rva0057DA21(MapMetaData *map);

private:
	unsigned char m_pad00[0x4];
	unsigned char m_field04[0xc - 0x4];	// +0x04, handed to the campaign owner
	_STL::vector<void *> m_regions;	// +0x0C, Rva0020E89C pointers
	Rva0043DA65 *m_18;	// +0x18
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
			owner->m_field48 = m_field04;
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
void AptMapPreview::rva0057D709(Int region, _STL::vector<void *> *regions)
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
			rva0057D709((Int)previous, &m_regions);
			((Rva003EEFA0 *)owner)->rva003EEFA0((Int)&m_regions);
		}
		if (current != 0)
		{
			if (AllowsStartInRegion((Int)current))
			{
				m_regions.clear();
				rva0057D709((Int)current, &m_regions);
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
	if (m_regionPicked.m_op == 0)
		return;
	Rva0020E89C *picked = region;
	rva0057D709((Int)region, &m_regions);
	for (unsigned int i = 0; i < m_regions.size(); ++i)
	{
		if (((Rva0057C688 *)this)->rva0057C688(((Rva0020E89C *)m_regions[i])->m_slot) != 0)
		{
			picked = (Rva0020E89C *)m_regions[i];
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
