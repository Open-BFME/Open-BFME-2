// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Region3D.h"
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
// ?rva0057D10F@AptMapPreview@@QAEXPAVMapMetaData@@@Z @0x0057D10F 139B
// Evidence: caller 0x0057E058 passes MapMetaData* (same slot as UpdateMapTitle
// 0x0057C8D1 and bfmeSetMapDescription 0x0057C892); callee bfmeCreateMapPictureImage
// 0x0057CDC3 takes MapMetaData+0x50 AsciiString; fallback uses "MissingMap" via
// rowed StringBase ctor 0x00037BA0 plus rowed findImageByName 0x002D92F6 through
// g_00DFF078 and rowed releaseBuffer 0x00036410; flag +0x60 selects ownership.
#include "ascii_string.h"

#include <new>

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

extern class ImageCollection *TheMappedImageCollection;

Image *bfmeCreateMapPictureImage(const AsciiString &mapName);

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

void AptMapPreview::rva0057D10F(MapMetaData *map)
{
	if (m_ownsPicture)
	{
		if (m_picture)
		{
			::delete m_picture;
			m_picture = 0;
		}
	}
	Image *img = 0;
	if (map)
	{
		img = bfmeCreateMapPictureImage(map->m_fileName);
		m_ownsPicture = true;
	}
	if (img == 0)
	{
		{
			AsciiString tmp("MissingMap");
			img = (Image *)TheMappedImageCollection->findImageByName(tmp);
		}
		m_ownsPicture = false;
	}
	m_picture = img;
}
