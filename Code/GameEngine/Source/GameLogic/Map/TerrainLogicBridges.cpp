// cl: /O1 /DNDEBUG /MD /arch:SSE /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
//
// TerrainLogic's bridge methods: findBridgeAt and findBridgeLayerAt, slots 41
// and 42, objectInteractsWithBridgeLayer,
// objectInteractsWithBridgeEnd and pickBridge, slots 43..45 of the TerrainLogic
// vftable (0x007FB2C8; slots 65..67 of W3DTerrainLogic's at 0x007C5838), and
// deleteBridge and updateBridgeDamageStates, slots 48 and 49. All are Zero
// Hour's (GameLogic/Map/TerrainLogic.cpp). The interaction
// tests: the bridge on the object's layer, the point test (layer only), a
// pathfind-cell-padded box around the object tested against the bridge ends,
// the deck height within LAYER_Z_CLOSE_ENOUGH_F and (layer only) the rubble
// check; BFME 2 drops the LAYER_WALL case of the layer test. pickBridge
// returns Bool in BFME 2: Bridge::pickBridge (0x0027FBFE) reports the hit, the
// drawable lookup is split out to 0x00281BF7, and a miss falls through to the
// pathfinder's own pick (0x002E9442, which walks its +0x5C list with the same
// Bridge::pickBridge).
//
// Target facts: getFirstBridge is slot 40 (+0xA0); the bridge list links at
// Bridge+0x04, the layer sits at Bridge+0xC4 and the end corners at
// Bridge+0x28..0x58 (as Bridge::isPointOnBridge 0x0027EEAD lays them out), so
// Zero Hour's BridgeInfo starts at +0x0C and its damage state lands at +0x5C,
// compared with 3 (BODY_RUBBLE). The object's position is Object+0x38 and the
// radius it pads is Object+0xB8, which Zero Hour reads as the geometry's minor
// radius. The callees are the Bridge methods Zero Hour calls in this order:
// isPointOnBridge (rowed), isCellOnEnd (0x0027C79C) and getBridgeHeight
// (0x0027FD2A). The bridge list head is TerrainLogic+0x40 and the damage-state
// flag +0x44; deleteBridge copies the BridgeInfo out, clears the pathfinder
// layer, destroys the bridge object and frees the bridge through its slot-0
// destructor and the global operator delete; updateBridgeDamageStates calls
// Bridge::updateDamageState (0x00281C13) on each bridge.
#include "Coord2D.h"
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

#include <math.h>
#include <stddef.h>

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_LAST = 15
};

enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_DAMAGED = 1,
	BODY_REALLYDAMAGED = 2,
	BODY_RUBBLE = 3
};

#define PATHFIND_CELL_SIZE_F 10.0f
#define LAYER_Z_CLOSE_ENOUGH_F 10.0f

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real X;
	Real Y;
	Real Z;
};

class Drawable;

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class GeometryInfo
{
public:
	Real getMinorRadius() const { return m_minorRadius; }
private:
	char m_pad00[0x10];
	Real m_minorRadius; // +0x10
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
private:
	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
	char m_pad44[0xA8 - 0x44];
	GeometryInfo m_geometryInfo; // +0xA8
};

// Zero Hour's BridgeInfo, the 0xA8-byte record whose rowed constructor
// (0x0027C36A) and assignment (0x00085420) keep their address-derived class
// name. Bridge holds it at +0x0C.
class Rva0027C36A
{
public:
	Rva0027C36A();
	Rva0027C36A &operator=(const Rva0027C36A &other);

	Coord3D from; // +0x00
	Coord3D to; // +0x0C
	Real bridgeWidth; // +0x18
	Coord3D fromLeft; // +0x1C
	Coord3D fromRight; // +0x28
	Coord3D toLeft; // +0x34
	Coord3D toRight; // +0x40
	Int bridgeIndex; // +0x4C
	BodyDamageType curDamageState; // +0x50
	ObjectID bridgeObjectID; // +0x54
private:
	char m_pad58[0xA8 - 0x58];
};
typedef Rva0027C36A BridgeInfo;

class Bridge
{
public:
	virtual ~Bridge();
	Bridge *getNext() { return m_next; }
	void setNext(Bridge *next) { m_next = next; }
	void getBridgeInfo(BridgeInfo *info) { *info = m_bridgeInfo; }
	const BridgeInfo *peekBridgeInfo() const { return &m_bridgeInfo; }
	void updateDamageState();
	__forceinline void deleteInstance() { ::delete this; }
	Bool isPointOnBridge(const Coord3D *loc);
	Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	Int getLayer() const { return m_layer; }
	Bool isCellOnEnd(const Region2D *cell);
	Real getBridgeHeight(const Coord3D *loc, Coord3D *normal);
private:
	Bridge *m_next; // +0x04
	char m_pad08[0x0C - 0x08];
	BridgeInfo m_bridgeInfo; // +0x0C
	char m_padB4[0xC4 - 0xB4];
	Int m_layer; // +0xC4
};

// 0x00281BF7: the bridge object's drawable (Zero Hour's tail of
// Bridge::pickBridge, split out); the row keeps its address-derived name and
// int return.
class Rva00281BF7
{
public:
	Int rva00281BF7();
};

class Pathfinder
{
public:
	Bool rva002E9442(const Vector3 &from, const Vector3 &to, Vector3 *pos);
};

// 0x002E7205: Zero Hour's Pathfinder::changeBridgeState(layer, repaired);
// the row keeps its address-derived name.
class Rva002E7205Owner
{
public:
	void rva002E7205(Int layer, Bool repaired);
};

// TheAI's pathfinder at +0x10.
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;
extern GameLogic *TheGameLogic;

template <int N> class TerrainLogicSlots : public TerrainLogicSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class TerrainLogicSlots<1>
{
public:
	virtual void gap(char (*)[1]);
};

class TerrainLogic : public TerrainLogicSlots<40>
{
public:
	virtual Bridge *getFirstBridge() const; // +0xA0
	virtual Bridge *findBridgeAt(const Coord3D *pLoc) const; // +0xA4
	virtual Bridge *findBridgeLayerAt(const Coord3D *pLoc, PathfindLayerEnum layer, Bool clip = false) const; // +0xA8
	virtual Bool objectInteractsWithBridgeLayer(Object *obj, Int layer, Bool considerBridgeHealth = true) const; // +0xAC
	virtual Bool objectInteractsWithBridgeEnd(Object *obj, Int layer) const; // +0xB0
	virtual Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos); // +0xB4
	virtual void slot46();
	virtual void slot47();
	virtual void deleteBridge(Bridge *bridge); // +0xC0
	virtual void updateBridgeDamageStates(void); // +0xC4
private:
	char m_pad04[0x40 - 0x04];
	Bridge *m_bridgeListHead; // +0x40
	Bool m_bridgeDamageStatesChanged; // +0x44
};

// ?findBridgeAt@TerrainLogic@@UBEPAVBridge@@PBUCoord3D@@@Z @0x0027F30A
Bridge * TerrainLogic::findBridgeAt( const Coord3D *pLoc) const
{

	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		if (pBridge->isPointOnBridge(pLoc)) {
			return(pBridge);
		}
		pBridge = pBridge->getNext();
	}
	return(NULL);
}

// ?findBridgeLayerAt@TerrainLogic@@UBEPAVBridge@@PBUCoord3D@@W4PathfindLayerEnum@@_N@Z @0x0027F337
// Zero Hour's lookup; BFME 2 also refuses a layer past LAYER_LAST.
Bridge * TerrainLogic::findBridgeLayerAt( const Coord3D *pLoc, PathfindLayerEnum layer, Bool clip) const
{
	if (layer == LAYER_GROUND || layer > LAYER_LAST)
		return NULL;

	Bridge *pBridge = getFirstBridge();
	while (pBridge)
	{
		if (pBridge->getLayer() == layer && (!clip || pBridge->isPointOnBridge(pLoc)))
		{
			return(pBridge);
		}
		pBridge = pBridge->getNext();
	}
	return(NULL);
}

// ?objectInteractsWithBridgeLayer@TerrainLogic@@UBE_NPAVObject@@H_N@Z @0x002804B2
// Zero Hour's test less its LAYER_WALL case.
Bool TerrainLogic::objectInteractsWithBridgeLayer(Object *obj, Int layer, Bool considerBridgeHealth) const
{
	if (layer == LAYER_GROUND) return false;
	Bridge *pBridge = getFirstBridge();

	while (pBridge ) {
		if (pBridge->getLayer() == layer) {
			Bool match = false;
			if (pBridge->isPointOnBridge(obj->getPosition()) ) {
				match = true;
			}

			Real radius = obj->getGeometryInfo().getMinorRadius();
			radius += PATHFIND_CELL_SIZE_F/2.0f;
			Region2D bounds;
			bounds.lo.x = obj->getPosition()->x;
			bounds.lo.y = obj->getPosition()->y;
			bounds.hi = bounds.lo;
			bounds.lo.x -= radius;
			bounds.lo.y -= radius;
			bounds.hi.x += radius;
			bounds.hi.y += radius;
			if (pBridge->isCellOnEnd(&bounds)) {
				match = true;
			}

			if (match) {
				Real bridgeHeight = pBridge->getBridgeHeight(obj->getPosition(), NULL);
				Real delta = fabs(obj->getPosition()->z-bridgeHeight);
				if (delta>LAYER_Z_CLOSE_ENOUGH_F) {
					return false;
				}

				// make sure it's not destroyed. can't interact with dead bridges.
				if (considerBridgeHealth && pBridge->peekBridgeInfo()->curDamageState == BODY_RUBBLE)
				{
					return false;
				}

				return true;
			}
			return false;
		}

		pBridge = pBridge->getNext();
	}
	return(false);
}

// ?objectInteractsWithBridgeEnd@TerrainLogic@@UBE_NPAVObject@@H@Z @0x002805C1
Bool TerrainLogic::objectInteractsWithBridgeEnd(Object *obj, Int layer) const
{
	if (layer == LAYER_GROUND) return false;
	Bridge *pBridge = getFirstBridge();

	while (pBridge ) {
		if (pBridge->getLayer() == layer) {
			Bool match = false;

			Real radius = obj->getGeometryInfo().getMinorRadius();
			radius += PATHFIND_CELL_SIZE_F/2.0f;
			Region2D bounds;
			bounds.lo.x = obj->getPosition()->x;
			bounds.lo.y = obj->getPosition()->y;
			bounds.hi = bounds.lo;
			bounds.lo.x -= radius;
			bounds.lo.y -= radius;
			bounds.hi.x += radius;
			bounds.hi.y += radius;
			if (pBridge->isCellOnEnd(&bounds)) {
				match = true;
			}

			if (match) {
				Real bridgeHeight = pBridge->getBridgeHeight(obj->getPosition(), NULL);
				Real delta = fabs(obj->getPosition()->z-bridgeHeight);
				if (delta>LAYER_Z_CLOSE_ENOUGH_F)
				{
					return false;
				}
				return true;
			}
			return false;
		}

		pBridge = pBridge->getNext();
	}
	return(false);
}

// ?pickBridge@TerrainLogic@@UAE_NABVVector3@@0PAV2@@Z @0x00281ECA
// Zero Hour's pick, reporting a hit rather than the drawable; with no bridge
// under the ray the pathfinder gets the pick.
Bool TerrainLogic::pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos)
{
	Drawable *curDraw = NULL;
	Vector3 curPos(0,0,0);

	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		Vector3 thisPos;
		if (pBridge->pickBridge(from, to , &thisPos)) {
			Drawable *thisDraw = (Drawable *)((Rva00281BF7 *)pBridge)->rva00281BF7();
			if (!curDraw) {
				curDraw = thisDraw;
				curPos = thisPos;
			}
		}
		pBridge = pBridge->getNext();
	}
	if (curDraw) {
		*pos = curPos;
		return true;
	}
	return TheAI->pathfinder()->rva002E9442(from, to, pos);
}

// ?deleteBridge@TerrainLogic@@UAEXPAVBridge@@@Z @0x00281F7F
void TerrainLogic::deleteBridge( Bridge *bridge )
{

	// sanity
	if( bridge == NULL )
		return;

	// check for removing the head
	if( m_bridgeListHead == bridge )
	{

		m_bridgeListHead = bridge->getNext();

	}  // end if
	else
	{

		for( Bridge *otherBridge = getFirstBridge();
				 otherBridge;
				 otherBridge = otherBridge->getNext() )
		{

			//
			// if the next bridge is the one in question to delete, set this bridge to point
			// to the next pointer of the bridge we are deleting
			//
			if( otherBridge->getNext() == bridge )
			{

				otherBridge->setNext( bridge->getNext() );
				break;  // exit for

			}  // end if

		}  // end for, otherBridge

	}  // end else

	// delete object associated with bridge if present
	BridgeInfo bridgeInfo;
	bridge->getBridgeInfo( &bridgeInfo );
	((Rva002E7205Owner *)TheAI->pathfinder())->rva002E7205(bridge->getLayer(), false);

	GameLogic *logic = TheGameLogic;
	Object *bridgeObj = logic->findObjectByID( bridgeInfo.bridgeObjectID );
	if( bridgeObj )
		logic->destroyObject( bridgeObj );

	// delete the bridge in question
	bridge->deleteInstance();

}  // end deleteBridge

// ?updateBridgeDamageStates@TerrainLogic@@UAEXXZ @0x00281EA5
void TerrainLogic::updateBridgeDamageStates( void )
{
	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		pBridge->updateDamageState();
		pBridge = pBridge->getNext();
	}
	m_bridgeDamageStatesChanged = true;
}
