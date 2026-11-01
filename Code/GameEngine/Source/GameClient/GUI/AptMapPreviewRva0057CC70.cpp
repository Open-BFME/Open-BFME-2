// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
// ?v04@Rva0057C50C@@UAEPAXPAX0@Z @0x0057CC70 246B: slot 1 of the map preview's
// colour callback (vtable 0x0086F31C, ctor 0x0057C50C, deleting dtor 0x0057C66C);
// +0x04 is its owning AptMapPreview.
// Evidence: chain from 0x0057C525 landing; neighbours AptMapPreviewSetMapDescription
// (prev 0x0057CC43) and RvaTreeEraseClearFamily (next 0x0057CD78); callees rowed
// 0x0043DA65 0x0057CA78 0x003FF29F 0x004FCA0C 0x0057C525 0x00381373.

class GameSlot;
class AsciiString;
class Rva0057CC15Op;


class Rva0043DA65;

struct Rva0057CA78
{
	char m_pad0[0x18];
	Rva0043DA65 *m_ptr18;
	int GetNextSelectablePlayer(int start);
};

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

struct Res004FCA0C;
class Rva0020E89C;
class Sub0052BAC1
{
public:
	Res004FCA0C *Rva004FCA0C(Rva0020E89C *v);
};

class Rva004FD6F9;

class MultiplayerColorDefinition;
class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int v);
};

class LivingWorldManager;

extern LivingWorldManager *TheLivingWorldManager;
extern MultiplayerSettings *TheMultiplayerSettings;

struct Rva0057CC70Color
{
	float r;
	float g;
	float b;
};

struct CC70Arg
{
	char m_pad[0x140];
	int m_field140;
};





struct CC70ColorDefView
{
	char m_pad[0x24];
	Rva0057CC70Color m_color;
};

struct CC70LWMInner
{
	char m_pad[0x20];
	Rva0057CC70Color m_color;
};

struct CC70LWMView
{
	char m_pad[0x268];
	CC70LWMInner *m_ptr268;
};

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

class Rva004FD8A8Set;

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



void *Rva0057C50C::v04(void *color, void *arg)
{
	Rva0057CC70Color *destination = (Rva0057CC70Color *)color;
	CC70Arg *cC70Arg = (CC70Arg *)arg;
	Rva0057CC70Color def;
	def.r = 0.5f;
	def.g = 0.5f;
	def.b = 0.5f;
	GameInfo *info = (GameInfo *)m_owner->m_18->rva0043DA65();
	if (!info)
	{
		*destination = def;
		return destination;
	}
	Rva0057CC70Color slotColor;
	Rva0057CC70Color *src;
	int slot = cC70Arg->m_field140;
	if (slot == -1)
		slot = ((Rva0057CA78 *)m_owner)->GetNextSelectablePlayer(0);
	GameSlot *gs = 0;
	AptLivingWorldWindow *cC70Mid1 = 0;
	AptMapPreviewMapInfo *cC70Mid2 = 0;
	Sub0052BAC1 *t = 0;
	if ((unsigned int)slot < 8
		&& (gs = info->getSlot(slot)) != 0
		&& (cC70Mid1 = m_owner->m_livingWorldWindow) != 0
		&& (cC70Mid2 = cC70Mid1->m_info) != 0
		&& (t = (Sub0052BAC1 *)cC70Mid2->m_startRegions) != 0)
	{
		Res004FCA0C *r = t->Rva004FCA0C((Rva0020E89C *)cC70Arg);
		if (r != (Res004FCA0C *)cC70Arg)
		{
			v04(destination, r);
			return destination;
		}
		if (!m_owner->AllowsStartInRegion((int)cC70Arg))
		{
			CC70LWMInner *cC70LWMInner = ((CC70LWMView *)TheLivingWorldManager)->m_ptr268;
			src = &cC70LWMInner->m_color;
			if (!cC70LWMInner)
				src = &def;
		}
		else
		{
			int color = gs->m_color;
			MultiplayerColorDefinition *multiplayerColorDefinition = TheMultiplayerSettings->getColor(color);
			if (multiplayerColorDefinition)
			{
				slotColor = ((CC70ColorDefView *)multiplayerColorDefinition)->m_color;
				src = &slotColor;
			}
			else
				src = &def;
		}
	}
	else
		src = &def;
	*destination = *src;
	return destination;
}
