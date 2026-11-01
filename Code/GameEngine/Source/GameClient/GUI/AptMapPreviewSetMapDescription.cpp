// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Region3D.h"
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
// Recovered map-preview description update at RVA 0x0057C892.
// Descriptive bfme names do not claim original source spellings. The metadata
// getter calls the cached map.str text loader, then returns its first line.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "unicode_string.h"


class GameWindow
{
public:
	int winEnable(bool enable);
};
void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
    int color, int row, int column, bool overwrite);
int __cdecl Rva00322910(GameWindow *comboBox);
void *__cdecl GadgetComboBoxGetItemData(GameWindow *comboBox, int index);

struct Rva0057DA21Waypoint
{
	Coord3D pos;
};

class MapMetaData
{
public:
	UnicodeString bfme_getDescriptionFirstLine();
	UnicodeString getDescription();		// 0x003009CD
	UnicodeString bfme_getBaseDisplayName();	// 0x00300AEA

	MapMetaData();	// 0x003031D3

	UnicodeString m_displayName;	// +0x00
	UnicodeString m_04;	// +0x04
	Region3D m_extent;	// +0x08
	int m_numPlayers;	// +0x20
	bool m_isMultiplayer;	// +0x24
	bool m_25;	// +0x25
	bool m_isOfficial;	// +0x26
	unsigned char m_pad27[0x38 - 0x27];
	_STL::map<AsciiString, Rva0057DA21Waypoint> m_waypoints;	// +0x38
	unsigned char m_pad44[0x50 - 0x44];
	AsciiString m_fileName;	// +0x50
	unsigned char m_pad54[0xf8 - 0x54];
	UnicodeString m_f8;	// +0xF8, a second display name
	UnicodeString m_fc;	// +0xFC, getDescription's cached text
};

class GameSlot;
class GameSlot;
class AsciiString;
class Rva0057CC15Op;

class Rva0043DA65;

class AptMapPreview;
class GameSlot;
class GameWindow;
class MapMetaData;
class AptLivingWorldWindow;
class Rva0020E89C;
class Image;
class Rva0057CC15Op;
struct Rva0057CC43Node;

typedef int Int;
typedef bool Bool;

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


class Rva0043DA65
{
public:
	int rva0043DA65();
	int m_00; // +0x00
	int m_refs; // +0x04 +0x04, the reference count
	int m_08; // +0x08
};

class Rva0057CC15Op
{
public:
	virtual ~Rva0057CC15Op();
	virtual void invoke(int a);

	int m_refs;	// +0x04
};

class Rva0057CC15Ref
{
public:
	void invoke(int a);

	RefCountPtr<Rva0057CC15Op> m_op;
};

class Rva0086E350Listener
{
public:
	virtual void v00(void *a) {}
	virtual void v04(void *a, void *b) {}
	virtual void v08(void *a, void *b, void *c) {}
	virtual void v0C(void *a, void *b, void *c) {}
	~Rva0086E350Listener() {}
};

class Rva003EE711
{
public:
	__forceinline Rva003EE711() {}
	virtual ~Rva003EE711() {}
	virtual void *v04(void *color, void *arg) = 0;
};

class Rva0057C50C : public Rva003EE711
{
public:
	Rva0057C50C(void *owner) : m_owner((AptMapPreview *)owner) {}
	virtual void *v04(void *color, void *arg);

	AptMapPreview *m_owner;
};

class AptMapPreview : public Rva0086E350Listener
{
public:
	AptMapPreview(Rva0043DA65 *game);
	~AptMapPreview();
	void rva0057C597(bool show);
	void rva0057CC43(Rva0057CC43Node *head);
	void rva0057CD66();
	int rva0057C57B(int value);
	GameSlot *rva0057C688(Int slot);	// 0x0057C688
	Bool IsValidStartPosition(Int index);	// may a player start at this index
	virtual void v04(void *a, void *b);
	virtual void v0C(void *a, void *b, void *c);
	Bool AllowsStartInRegion(Int region);
	void SelectCampaign(Int campaign);
	void UpdateStrategicScenarioDesc();	// 0x0057C99E
	Int GetCurrentStrategicScenario();
	void PictureCustomRender(const Coord2D *pos, const Coord2D *size, void *unused3, void *unused4);
	void GameMapType(int query, char *result, bool skip);
	void MapGadgetInit(const char *name, void *argument, GameWindow *window);
	void rva0057E45C();
	void PopulateStrategicScenario();	// fills the strategic scenario combo box
	void rva0057E058();	// refreshes the preview
	void *GetStrategicScenarioComboBoxSelectedCampaign();	// 0x0057C649
	MapMetaData *rva0057D922(const AsciiString &map);	// looks the map up
	void UpdateMapTitle(MapMetaData *map);	// 0x0057C8D1
	void rva0057DDAE(MapMetaData *map);
	void rva0057D19A(MapMetaData *map);
	void bfmeSetMapDescription(MapMetaData *map);	// 0x0057C892
	void rva0057D10F(MapMetaData *map);	// the map picture
	void GetRegionsInOwnershipSet(Int region, _STL::vector<Rva0020E89C *> *regions);
	void OnMouseoverRegionChanged_internal(Rva0020E89C *previous, Rva0020E89C *current);
	void rva0057D85D(Rva0020E89C *region);
	void rva0057D5E5();
	void UpdateMapStartSpots(MapMetaData *map);
	void UpdateStrategicStartSpots();

private:
	friend class Rva0057C50C;
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

struct Rva0057CC43Node
{
    char m_pad00[8];
    Rva0057CC43Node *m_next;
    Rva0057CC43Node *m_child;
};

void AptMapPreview::bfmeSetMapDescription(MapMetaData *map)
{
    if (m_mapDescription)
    {
        GadgetListBoxReset(m_mapDescription);
        if (map)
            GadgetListBoxAddEntryText(m_mapDescription,
                map->bfme_getDescriptionFirstLine(), -1, -1, -1, true);
    }
}

void AptMapPreview::rva0057C597(bool show)
{
    for (int i = 0; i < 8; ++i) {
        GameWindow *gameWindow = m_currentMapChildren[i];
        if (gameWindow) {
            gameWindow->winEnable(show);
        }
    }
}

void AptMapPreview::rva0057CC43(Rva0057CC43Node *head)
{
    for (Rva0057CC43Node *node = head; node; ) {
        rva0057CC43(node->m_child);
        Rva0057CC43Node *next = node->m_next;
        free(node);
        node = next;
    }
}

void *AptMapPreview::GetStrategicScenarioComboBoxSelectedCampaign()
{
    if (!m_strategicScenarioComboBox)
        return (void *)-1;
    int index = Rva00322910(m_strategicScenarioComboBox);
    return GadgetComboBoxGetItemData(m_strategicScenarioComboBox, index);
}

// ?rva0057CD66@AptMapPreview@@QAEXXZ @0x0057CD66 18B
// Evidence: callees rowed 0x0057C649 GetStrategicScenarioComboBoxSelectedCampaign
// and 0x0057CA2D SelectCampaign; caller 0x0057CDA1; neighbours AptMapPreview.
void AptMapPreview::rva0057CD66()
{
    SelectCampaign((int)GetStrategicScenarioComboBoxSelectedCampaign());
}

int AptMapPreview::rva0057C57B(int value)
{
    for (int i = 0; i < 8; ++i)
    {
        if (value == (int)m_currentMapChildren[i])
            return i;
    }
    return -1;
}


class GameSlot
{
public:
	bool isAI() const;
	virtual void reset();
	int m_state; // +0x04
	char m_pad08[0x4];
	int m_color; // +0x0C +0x0C
	int m_startPos; // +0x10 +0x10, the start region id, -1 for none
	char m_pad14[0x4];
	int m_playerTemplate; // +0x18 +0x18
};

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
	virtual int v34() const = 0;	// +0x34
	AsciiString getMap() const;		// 0x0023E943
	GameSlot *getSlot(int index);		// 0x003FF29F
	const GameSlot *getConstSlot(int slotNum) const;	// 0x003FF2BE

	unsigned char m_pad04[0x10 - 0x4];
	bool m_selectStartPoint;	// +0x10
	unsigned char m_pad11[0x58 - 0x11];
	int m_campaign;		// +0x58, a campaign manager index
	unsigned char m_pad5c[0x8c - 0x5c];
	bool m_8c;		// +0x8C, no region picks while set
	unsigned char m_pad8d[0xc8 - 0x8d];
	int m_c8;		// +0xC8
};

GameSlot *AptMapPreview::rva0057C688(int value)
{
	if (value == -1)
		return 0;
	GameInfo *info = (GameInfo *)m_18->rva0043DA65();
	if (!info)
		return 0;
	for (int i = 0; i < 8; ++i)
	{
		GameSlot *slot = info->getSlot(i);
		if (!slot)
			continue;
		if (slot->m_startPos == value)
			return slot;
	}
	return 0;
}
