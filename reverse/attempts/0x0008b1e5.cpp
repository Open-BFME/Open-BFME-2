// ?pickDrawable@W3DView@@UAEPAVDrawable@@PBUICoord2D@@_NH@Z
// partial score=0.92 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// ?pickDrawable@W3DView@@UAEPAVDrawable@@PBUICoord2D@@_NH@Z, retail 0x0008B1E5..0x0008B472 (651B), thiscall RET 0xC.
// BFME 2 W3DView::pickDrawable (TheTacticalView slot 9; the screen-pick helper Rva00431012PickObject calls it as
// pickDrawable(pixel, false, pickType)). Donor (Zero Hour W3DView.cpp pickDrawable, read as a guide, facts carried from
// the donor): the opaque-window early out, getPickRay + LineSegClass, CastResultStruct with ComputeContactPoint = forceAttack,
// RayCollisionTestClass and the scene ray cast. Target-only (read from retail bytes): the window test is skipped while the
// GameLogic mode predicate 0x00085124 holds; the cast is the rowed all-hits RTS3DScene::rva00072109 into a float-keyed
// hit map walked by the rowed mask finder 0x0008A2A3 (collision mask 0x184, 0x104 when pickType bit 8 is set, then 0x84, 0x14
// and the pick type itself), the raytest's extra +0x42 flag is set, the hit's user data drawable goes through the 3-byte
// ICF stub 0x000D43D0, and when nothing is hit the screen point is projected to the terrain (vslot 90) and looked up through
// the rowed 0x0027F0D3; shrouded results give null and flagged results one of four reserved drawable ids from TheGameClient
// slot 16. The map local is built by the 25B empty-tree constructor (rowed under neutral aliases) and torn down by the
// tree destructor 0x0008A612.
#include <map>
#include "Coord3D.h"

struct ICoord2D { int x; int y; };

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X;
	float Y;
	float Z;
};

class LineSegClass
{
public:
	void Set(const Vector3 &p0, const Vector3 &p1);
	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	float Length;
};

struct CastResultStruct
{
	CastResultStruct() { Reset(); }
	void Reset()
	{
		StartBad = false;
		Fraction = 1.0f;
		Normal.Set(0, 0, 0);
		SurfaceType = 0;
		ComputeContactPoint = false;
		ContactPoint.Set(0, 0, 0);
	}
	bool StartBad;
	float Fraction;
	Vector3 Normal;
	unsigned int SurfaceType;
	bool ComputeContactPoint;
	Vector3 ContactPoint;
};

class RenderObjClass;

enum
{
	COLL_TYPE_ALL = 0x01,
	COLL_TYPE_0 = 0x02
};

class CollisionTestClass
{
public:
	CastResultStruct *Result;
	int CollisionType;
	RenderObjClass *CollidedRenderObj;
};

class RayCollisionTestClass : public CollisionTestClass
{
public:
	RayCollisionTestClass(const LineSegClass &ray, CastResultStruct *res, int collision_type = COLL_TYPE_0, bool check_translucent = false, bool check_hidden = false);
	LineSegClass Ray;
	bool CheckTranslucent;
	bool CheckHidden;
	bool _bfme_flag42;
};

class Drawable;

struct DrawableInfo
{
	int m_shroudStatusObjectID;
	Drawable *m_drawable;
};

// Mask finder item (rowed Rva0008A2A3Find): a render object seen through its user-data slot (+0x15C).
class Rva0008A2A3Item
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015(); virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019(); virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023(); virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035(); virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039(); virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047(); virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059(); virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067(); virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075(); virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079(); virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083(); virtual void s084(); virtual void s085(); virtual void s086();
	virtual DrawableInfo *Get_User_Data();
};

Rva0008A2A3Item *Rva0008A2A3Find(void *mapArg, unsigned int mask, bool all);

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::multimap<float, TreeOpaqueMapped00372FF4> RenderObjHitMap;

class RTS3DScene
{
public:
	void rva00072109(RayCollisionTestClass &raytest, int collisionType, RenderObjHitMap &hits);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

// Hit-map local: constructed through the rowed 25B empty-tree constructor and destroyed through the rowed tree destructor.
class Rva004DD206TreeView
{
public:
	Rva004DD206TreeView();
	char m_storage[12];
};

class Rva0006F318
{
public:
	~Rva0006F318();
	char m_storage[12];
};

struct PickHitMap
{
	PickHitMap() : tree() {}
	~PickHitMap() { ((Rva0006F318 *)&tree)->~Rva0006F318(); }
	Rva004DD206TreeView tree;
};

class GameWindow
{
public:
	unsigned int winGetStatus();
	GameWindow *winGetParent();
	int winNextTab();
};

class GameWindowManager
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015(); virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019(); virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023(); virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035(); virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039(); virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047(); virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059(); virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067(); virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075(); virtual void s076();
	virtual GameWindow *getWindowUnderCursor(int x, int y, bool ignoreEnabled);
};

class GameLogic
{
public:
	bool rva00085124();
};

class GameClient
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015();
	virtual Drawable *findDrawableByID(int id);
};

class PlayerList
{
public:
	unsigned char m_pad00[0x10];
	unsigned char *m_localPlayer;
};

class PartitionManager;
enum ObjectShroudStatus { OBJECTSHROUD_INVALID = 4 };

class Rva00739800
{
public:
	ObjectShroudStatus rva00739800(int playerIndex, const Coord3D *position) const;
};

class TerrainLogic;

// Terrain-point pick record returned by the rowed 0x0027F0D3 lookup (only the fields read here).
struct PickedGhostView
{
	unsigned char m_pad00[0xc];
	int m_field0C;
	unsigned char m_pad10[0x2c - 0x10];
	unsigned char m_flagA;
	unsigned char m_flagB;
};

class BfmeThingCME
{
public:
	int bfmeGoCME(void *position);
};

class Rva0025DE76Slot
{
public:
	int rva000D43D0();
};

extern GameWindowManager *TheWindowManager;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern PartitionManager *TheShroudManager;
extern TerrainLogic *TheTerrainLogic;
extern GameClient *TheGameClient;

class W3DView
{
public:
	virtual void sv0(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007(); virtual void s008();
	virtual Drawable *pickDrawable(const ICoord2D *screen, bool forceAttack, int pickType);
	virtual void s010(); virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015(); virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019(); virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023(); virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035(); virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039(); virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047(); virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059(); virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067(); virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075(); virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079(); virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083(); virtual void s084(); virtual void s085(); virtual void s086(); virtual void s087(); virtual void s088(); virtual void s089();
	virtual void screenToTerrainSlot90(const ICoord2D *screen, Coord3D *world, bool flag);

private:
	void getPickRay(const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd);
};

Drawable *W3DView::pickDrawable(const ICoord2D *screen, bool forceAttack, int pickType)
{
	Drawable *volatile draw = 0;

	if (screen == 0)
		return 0;

	GameWindow *window = 0;
	GameWindowManager *windowManager = TheWindowManager;
	if (windowManager && !(TheGameLogic && TheGameLogic->rva00085124()))
		window = windowManager->getWindowUnderCursor(screen->x, screen->y, false);

	while (window)
	{
		if (!(window->winGetStatus() & 0x10000))
			return 0;
		window = window->winGetParent();
	}

	Vector3 rayStart, rayEnd;
	getPickRay(screen, &rayStart, &rayEnd);

	LineSegClass lineseg;
	lineseg.Set(rayStart, rayEnd);

	CastResultStruct result;
	if (forceAttack)
		result.ComputeContactPoint = true;

	RayCollisionTestClass raytest(lineseg, &result, COLL_TYPE_ALL, false, false);
	raytest._bfme_flag42 = true;

	int collisionMask = pickType | 0x194;
	PickHitMap hits;
	W3DDisplay::m_3DScene->rva00072109(raytest, collisionMask, *(RenderObjHitMap *)&hits);

	Rva0008A2A3Item *item = 0;
	if (pickType & 0x100)
	{
		item = Rva0008A2A3Find(&hits, 0x184, true);
		if (!item)
			item = Rva0008A2A3Find(&hits, 0x104, true);
	}
	if (!item)
	{
		item = Rva0008A2A3Find(&hits, 0x84, true);
		if (!item)
			item = Rva0008A2A3Find(&hits, 0x14, true);
		if (!item)
			item = Rva0008A2A3Find(&hits, pickType, false);
	}

	if (item)
	{
		DrawableInfo *info = item->Get_User_Data();
		if (info)
		{
			draw = info->m_drawable;
			if (draw)
			{
				Drawable *other = (Drawable *)((Rva0025DE76Slot *)draw)->rva000D43D0();
				if (other)
					draw = other;
				if (draw)
					return draw;
			}
		}
	}

	Coord3D terrain;
	screenToTerrainSlot90(screen, &terrain, false);
	PickedGhostView *ghost = (PickedGhostView *)((BfmeThingCME *)TheTerrainLogic)->bfmeGoCME(&terrain);
	if (!ghost)
		return draw;

	if (((Rva00739800 *)TheShroudManager)->rva00739800(ThePlayerList ? *(int *)(ThePlayerList->m_localPlayer + 0x54) : 0, (const Coord3D *)ghost) == OBJECTSHROUD_INVALID)
		return 0;

	if (ghost->m_field0C == 0)
		return draw;

	if (ghost->m_flagA && ghost->m_flagB)
		draw = TheGameClient->findDrawableByID(0x5F5E0FF);
	else if (ghost->m_flagA && !ghost->m_flagB)
		draw = TheGameClient->findDrawableByID(0x5F5E0FC);
	else if (!ghost->m_flagA && ghost->m_flagB)
		draw = TheGameClient->findDrawableByID(0x5F5E0FD);
	else
		draw = TheGameClient->findDrawableByID(0x5F5E0FE);
	return draw;
}
