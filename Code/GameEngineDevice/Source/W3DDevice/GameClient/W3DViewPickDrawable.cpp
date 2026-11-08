// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// ?pickDrawable@W3DView@@UAEPAVDrawable@@PBUICoord2D@@_NH@Z, retail 0x0008B1E5..0x0008B470 (651B), thiscall RET 0xC.
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

#include "ICoord2D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

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

#include "../../../../GameEngine/Include/GameClient/DrawableInfoClass.h"

// Mask finder item (rowed Rva0008A2A3Find): a render object seen through its user-data slot (+0x15C).
class Rva0008A2A3Item
{
public:
	virtual void v000() = 0;
	virtual void v001() = 0;
	virtual void v002() = 0;
	virtual void v003() = 0;
	virtual void v004() = 0;
	virtual void v005() = 0;
	virtual void v006() = 0;
	virtual void v007() = 0;
	virtual void v008() = 0;
	virtual void v009() = 0;
	virtual void v010() = 0;
	virtual void v011() = 0;
	virtual void v012() = 0;
	virtual void v013() = 0;
	virtual void v014() = 0;
	virtual void v015() = 0;
	virtual void v016() = 0;
	virtual void v017() = 0;
	virtual void v018() = 0;
	virtual void v019() = 0;
	virtual void v020() = 0;
	virtual void v021() = 0;
	virtual void v022() = 0;
	virtual void v023() = 0;
	virtual void v024() = 0;
	virtual void v025() = 0;
	virtual void v026() = 0;
	virtual void v027() = 0;
	virtual void v028() = 0;
	virtual void v029() = 0;
	virtual void v030() = 0;
	virtual void v031() = 0;
	virtual void v032() = 0;
	virtual void v033() = 0;
	virtual void v034() = 0;
	virtual void v035() = 0;
	virtual void v036() = 0;
	virtual void v037() = 0;
	virtual void v038() = 0;
	virtual void v039() = 0;
	virtual void v040() = 0;
	virtual void v041() = 0;
	virtual void v042() = 0;
	virtual void v043() = 0;
	virtual void v044() = 0;
	virtual void v045() = 0;
	virtual void v046() = 0;
	virtual void v047() = 0;
	virtual void v048() = 0;
	virtual void v049() = 0;
	virtual void v050() = 0;
	virtual void v051() = 0;
	virtual void v052() = 0;
	virtual void v053() = 0;
	virtual void v054() = 0;
	virtual void v055() = 0;
	virtual void v056() = 0;
	virtual void v057() = 0;
	virtual void v058() = 0;
	virtual void v059() = 0;
	virtual void v060() = 0;
	virtual void v061() = 0;
	virtual void v062() = 0;
	virtual void v063() = 0;
	virtual void v064() = 0;
	virtual void v065() = 0;
	virtual void v066() = 0;
	virtual void v067() = 0;
	virtual void v068() = 0;
	virtual void v069() = 0;
	virtual void v070() = 0;
	virtual void v071() = 0;
	virtual void v072() = 0;
	virtual void v073() = 0;
	virtual void v074() = 0;
	virtual void v075() = 0;
	virtual void v076() = 0;
	virtual void v077() = 0;
	virtual void v078() = 0;
	virtual void v079() = 0;
	virtual void v080() = 0;
	virtual void v081() = 0;
	virtual void v082() = 0;
	virtual void v083() = 0;
	virtual void v084() = 0;
	virtual void v085() = 0;
	virtual void v086() = 0;
	virtual DrawableInfo *Get_User_Data() = 0;
	virtual void v088() = 0;
	virtual void v089() = 0;
	virtual void v090() = 0;
	virtual void v091() = 0;
	virtual void v092() = 0;
	virtual void v093() = 0;
	virtual void v094() = 0;
	virtual void v095() = 0;
	virtual void v096() = 0;
	virtual void v097() = 0;
	virtual void v098() = 0;
	virtual void v099() = 0;
	virtual void v100() = 0;
	virtual void v101() = 0;
	virtual void v102() = 0;
	virtual void v103() = 0;
	virtual void v104() = 0;
	virtual void v105() = 0;
	virtual void v106() = 0;
	virtual void v107() = 0;
	virtual void v108() = 0;
	virtual void v109() = 0;
	virtual void v110() = 0;
	virtual void v111() = 0;
	virtual void v112() = 0;
	virtual void v113() = 0;
	virtual void v114() = 0;
	virtual void v115() = 0;
	virtual void v116() = 0;
	virtual void v117() = 0;
	virtual void v118() = 0;
	virtual void v119() = 0;
	virtual unsigned int mask() = 0;
};

Rva0008A2A3Item *Rva0008A2A3Find(void *mapArg, unsigned int mask, bool all);

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::multimap<float, TreeOpaqueMapped00372FF4> RenderObjHitMap;

#include "../../../Include/W3DDevice/GameClient/RTS3DScene.h"

class RTS2DScene;
class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
	static RTS2DScene *m_2DScene;
	void rva0004D664(float x0, float y0, float x1, float y1, float width, int color);
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

#include "../../../../GameEngine/Include/GameClient/Bfme2GameWindow.h"

class GameWindowManager
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015(); virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019(); virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023(); virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035(); virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039(); virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047(); virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059(); virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067(); virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075(); virtual void s076();
	virtual GameWindow *getWindowUnderCursor(int x, int y, bool ignoreEnabled);
};



#include "../../../../GameEngine/Include/GameClient/GameClientClass.h"

#include "../../../../GameEngine/Include/Common/Player.h"
#include "../../../../GameEngine/Include/Common/PlayerList.h"

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
	Drawable *draw = 0;

	if (screen == 0)
		return 0;

	GameWindow *window = 0;
	GameWindowManager *windowManager = TheWindowManager;
	if (windowManager && (!TheGameLogic || !TheGameLogic->rva00085124()))
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
		Rva0008A2A3Item *a = Rva0008A2A3Find(&hits, 0x184, true);
		if (a != 0)
		{
			item = a;
		}
		else
		{
			Rva0008A2A3Item *b = Rva0008A2A3Find(&hits, 0x104, true);
			if (b != 0)
				item = b;
		}
	}
	if (item == 0)
	{
		Rva0008A2A3Item *c = Rva0008A2A3Find(&hits, 0x84, true);
		if (c != 0)
		{
			item = c;
		}
		else
		{
			Rva0008A2A3Item *d = Rva0008A2A3Find(&hits, 0x14, true);
			if (d != 0)
			{
				item = d;
			}
			else
			{
				Rva0008A2A3Item *e = Rva0008A2A3Find(&hits, pickType, false);
				if (e != 0)
					item = e;
			}
		}
	}

	if (item)
	{
		DrawableInfo *info = item->Get_User_Data();
		if (info)
		{
			Drawable *infoDrawable = info->m_drawable;
			draw = infoDrawable;
			if (!infoDrawable)
				goto afterHit;
			{
				Drawable *other = (Drawable *)((Rva0025DE76Slot *)draw)->rva000D43D0();

				if (other)
					draw = other;
				if (draw)
					goto pickedDone;
			}
afterHit:;
		}
	}

	{
		Coord3D terrain;
		screenToTerrainSlot90(screen, &terrain, false);
		PickedGhostView *ghost = (PickedGhostView *)((BfmeThingCME *)TheTerrainLogic)->bfmeGoCME(&terrain);
		if (!ghost)
			goto pickedDone;

		if (((Rva00739800 *)TheShroudManager)->rva00739800(ThePlayerList ? ThePlayerList->m_local->m_playerIndex : 0, (const Coord3D *)ghost) == OBJECTSHROUD_INVALID)
			return 0;

		if (ghost->m_field0C == 0)
			goto pickedDone;

		if (ghost->m_flagA && ghost->m_flagB)
			draw = TheGameClient->findDrawableByID((DrawableID)0x5F5E0FF);
		else if (ghost->m_flagA && !ghost->m_flagB)
			draw = TheGameClient->findDrawableByID((DrawableID)0x5F5E0FC);
		else if (!ghost->m_flagA && ghost->m_flagB)
			draw = TheGameClient->findDrawableByID((DrawableID)0x5F5E0FD);
		else
			draw = TheGameClient->findDrawableByID((DrawableID)0x5F5E0FE);
	}
pickedDone:
	return draw;
}

// Retail extent ends at 0x8B470; the GameLogic mode call has a null receiver guard.
// One common result exit keeps the retail EAX receiver without volatile locals.
