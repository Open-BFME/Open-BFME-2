// cl: /O1 /DNDEBUG /MD /arch:SSE /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
//
// TerrainLogic's bridge methods: findBridgeAt and findBridgeLayerAt, slots 41
// and 42, objectInteractsWithBridgeLayer,
// objectInteractsWithBridgeEnd and pickBridge, slots 43..45 of the TerrainLogic
// vftable (0x007FB2C8; slots 65..67 of W3DTerrainLogic's at 0x007C5838), and
// deleteBridge and updateBridgeDamageStates, slots 48 and 49, with
// loadPostProcess (slot 1) and the non-virtual getHighestLayerForDestination,
// which reads the ground height through slot 6 (+0x18) and has no wall
// layer. All are Zero Hour's (GameLogic/Map/TerrainLogic.cpp). The interaction
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
// Bridge::updateDamageState (0x00281C13, defined here) on each bridge. That
// update reads the bridge object's body module (Object+0x254, slot 8), the
// object's layer through the rowed 0x0028B511, its id at +0x74 and the next
// object at +0x8C, and keeps Zero Hour's damageStateChanged at BridgeInfo+0x68.
// The Bridge cell tests isCellOnEnd, isCellOnSide and isCellEntryPoint
// (0x0027C79C..0x0027CD63) follow LineInRegion (0x0027C4F4) in retail and are
// defined after it here; their frames need it in the same unit.
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
	LAYER_LAST = 15,
	LAYER_RAMP = 16 // BFME 2: the pathfinder's ramp test reports it
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

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class Drawable;

#include "../../../../Libraries/Include/Lib/Region2D.h"

// LineInRegion (0x0027C4F4) is defined here, ahead of the Bridge cell tests
// that call it, as retail's adjacent layout has it: Zero Hour's TerrainLogic.cpp
// body, verbatim. Seen from another unit it leaves those callers' frames and
// xmm allocation unlike retail's.
// ?LineInRegion@@YA_NPBVCoord2D@@0PBURegion2D@@@Z @0x0027C4F4
Bool LineInRegion( const Coord2D *p1, const Coord2D *p2, const Region2D *clipRegion )
{
	enum { CLIP_LEFT  = 0x01,
				CLIP_RIGHT  = 0x02,
				CLIP_BOTTOM = 0x04,
				CLIP_TOP	  = 0x08 };
	Real x1, y1, x2, y2;
	Real clipLeft;
	Real clipRight;
	Real clipTop;
	Real clipBottom;
	Int clipCode1;
	Int clipCode2;
	Real diff;

	// Use clip window that includes bottom right pixel
	clipLeft = clipRegion->lo.x;
	clipRight = clipRegion->hi.x;
	clipTop = clipRegion->lo.y;
	clipBottom = clipRegion->hi.y;

	x1 = p1->x;
	y1 = p1->y;
	x2 = p2->x;
	y2 = p2->y;
		
	// Test first point
	clipCode1 = 0;

	if (x1 < clipLeft)
		clipCode1 = CLIP_LEFT;
	else
	if (x1 > clipRight)
		clipCode1 = CLIP_RIGHT;

	if (y1 < clipTop)
		clipCode1 |= CLIP_TOP;
	else
	if (y1 > clipBottom)
		clipCode1 |= CLIP_BOTTOM;


	// Test second point
	clipCode2 = 0;

	if (x2 < clipLeft)
		clipCode2 = CLIP_LEFT;
	else
	if (x2 > clipRight)
		clipCode2 = CLIP_RIGHT;

	if (y2 < clipTop)
		clipCode2 |= CLIP_TOP;
	else
	if (y2 > clipBottom)
		clipCode2 |= CLIP_BOTTOM;


	// Both points inside window?
	if ((clipCode1 | clipCode2) == 0)
	{
		return true;
	}  // end if

	// Both points outside window?
	if (clipCode1 & clipCode2)
		return false;

	// First point outside window?
	if (clipCode1)
	{
		if (clipCode1 & CLIP_TOP)
		{
			if ((diff = (y2 - y1)) == 0)
				return false;
			x1 += (x2 - x1) * (clipTop - y1) / diff;
			y1 = clipTop;
		}
		else
		if (clipCode1 & CLIP_BOTTOM)
		{
			if ((diff = (y2 - y1)) == 0)
				return false;
			x1 += (x2 - x1) * (clipBottom - y1) / diff;
			y1 = clipBottom;
		}

		if (x1 > clipRight)
		{
			if ((diff = (x2 - x1)) == 0)
				return false;
			y1 += (y2 - y1) * (clipRight - x1) / diff;
			x1 = clipRight;
		}
		else
		if (x1 < clipLeft)
		{
			if ((diff = (x2 - x1)) == 0)
				return false;
			y1 += (y2 - y1) * (clipLeft - x1) / diff;
			x1 = clipLeft;
		}
	}

	// Second point outside window?
	if (clipCode2)
	{
		if (clipCode2 & CLIP_TOP)
		{
			if ((diff = (y2 - y1)) == 0)
				return false;
			x2 += (x2 - x1) * (clipTop - y2) / diff;
			y2 = clipTop;
		}
		else
		if (clipCode2 & CLIP_BOTTOM)
		{
			if ((diff = (y2 - y1)) == 0)
				return false;
			x2 += (x2 - x1) * (clipBottom - y2) / diff;
			y2 = clipBottom;
		}

		if (x2 > clipRight)
		{
			if ((diff = (x2 - x1)) == 0)
				return false;
			y2 += (y2 - y1) * (clipRight - x2) / diff;
			x2 = clipRight;
		}
		else
		if (x2 < clipLeft)
		{
			if ((diff = (x2 - x1)) == 0)
				return false;
			y2 += (y2 - y1) * (clipLeft - x2) / diff;
			x2 = clipLeft;
		}
	}

	// Line is visible
	return (x1 >= clipLeft && x1 <= clipRight &&
		    y1 >= clipTop && y1 <= clipBottom &&
			x2 >= clipLeft && x2 <= clipRight &&
			y2 >= clipTop && y2 <= clipBottom);

}  // end LineInRegion

class GeometryInfo
{
public:
	__declspec(dllimport) __forceinline Real getMinorRadius() const { return m_minorRadius; }
private:
	char m_pad00[0x10];
	Real m_minorRadius; // +0x10
};

#include "../../../Include/GameLogic/Module/BodyModule.h"

// The 0x7C-byte damage record; its constructor is the rowed 0x00263895.
#include "../../../Include/GameLogic/Damage.h"

#define HUGE_DAMAGE_AMOUNT 999999.0f

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() { return m_next; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Int rva0028B511() const; // the rowed getLayer
	void attemptDamage(DamageInfo *damageInfo);
private:
	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
	char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_pad78[0x8C - 0x78];
	Object *m_next; // +0x8C
	char m_pad90[0xA8 - 0x90];
	GeometryInfo m_geometryInfo; // +0xA8
	char m_padBC[0x254 - 0xBC];
	BodyModuleInterface *m_body; // +0x254
};

class BridgeBehaviorInterface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual Bool isScaffoldPresent(); // +0x14
};

// Zero Hour's BridgeInfo, the 0xA8-byte record whose rowed constructor
// (0x0027C36A) and assignment (0x00085420) keep their address-derived class
// name. Bridge holds it at +0x0C.
#include "../../../Include/GameLogic/BridgeClass.h"
typedef Rva0027C36A BridgeInfo;


// 0x00281BF7: the bridge object's drawable (Zero Hour's tail of
// Bridge::pickBridge, split out); the row keeps its address-derived name and
// int return.
#include "../../../Include/GameLogic/Rva00281BF7.h"

// 0x002ED236 takes the position by value as a 12-byte type with a
// non-trivial destructor: its caller copies the three words into the
// argument and saves the argument's address, the callee-destroyed parameter
// shape, and the callee passes the argument's address on as a Coord3D. Its
// real name is unknown.
struct Rva002ED236Pos
{
	Real x;
	Real y;
	Real z;
	Rva002ED236Pos(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
	~Rva002ED236Pos() {}
};

#include "../../../Include/GameLogic/AIPathfind.h"

// TheAI's pathfinder at +0x10.
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
extern GameLogic *TheGameLogic;

// N unnamed vftable slots appended to Base.
template <class Base, int N> class TerrainLogicSlots : public TerrainLogicSlots<Base, N - 1>
{
public:
	virtual void gap(Base *, char (*)[N]);
};
template <class Base> class TerrainLogicSlots<Base, 0> : public Base
{
};

class TerrainLogicHead
{
public:
	virtual void slot0();
protected:
	virtual void loadPostProcess(void); // +0x04
};

class TerrainLogicGround : public TerrainLogicSlots<TerrainLogicHead, 4>
{
public:
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const; // +0x18
};

#include "../../../Include/GameLogic/TerrainLogic.h"

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
	if( field40 == bridge )
	{

		field40 = bridge->getNext();

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
	TheAI->pathfinder()->SetBridgeStateRepaired(bridge->getLayer(), false);

	GameLogic *logic = TheGameLogic;
	Object *bridgeObj = logic->findObjectByID( bridgeInfo.bridgeObjectID );
	if( bridgeObj )
		logic->destroyObject( bridgeObj );

	// delete the bridge in question
	bridge->deleteInstance();

}

// ?loadPostProcess@TerrainLogic@@MAEXXZ @0x002820A0
// After a load, drop every bridge whose bridge object did not come back.
void TerrainLogic::loadPostProcess( void )
{
	Bridge *pBridge = getFirstBridge();
	Bridge *pNext;
	while (pBridge) {
		pNext = pBridge->getNext();
		Object *obj = TheGameLogic->findObjectByID(pBridge->peekBridgeInfo()->bridgeObjectID);
		if (obj == NULL)
			deleteBridge(pBridge);
		pBridge = pNext;
	}
}



extern TerrainLogic *TheTerrainLogic;


// Inline here as in Zero Hour's BaseType.h. The cell tests still call the
// out-of-line normalize (rowed in coord3d.cpp with length, 0x000035B6 and
// 0x00003571), but isCellEntryPoint's frame and xmm allocation match retail
// only while both bodies are visible.
inline float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

inline void Coord3D::normalize()
{
	float len = length();
	if (len != 0.0f) {
		float scale = 1.0f / len;
		x *= scale;
		y *= scale;
		z *= scale;
	}
}

// ?isCellOnEnd@Bridge@@QAE_NPBURegion2D@@@Z @0x0027C79C
// Zero Hour's cell tests (isCellOnEnd, isCellOnSide, isCellEntryPoint). The
// corners are copied member-wise: an aggregate copy emits movsd and homes the
// unused z. BFME 2 offsets a bridge with an outline polygon (+0xC8) at its far
// end along that end's own vector, and isCellEntryPoint reports the near (or
// far) left corner's height through a second argument.
Bool Bridge::isCellOnEnd(const Region2D *cell)
{
	Coord3D endVector;
	endVector.x = m_bridgeInfo.fromRight.x;
	endVector.y = m_bridgeInfo.fromRight.y;
	endVector.z = m_bridgeInfo.fromRight.z;
	endVector.x -= m_bridgeInfo.fromLeft.x;
	endVector.y -= m_bridgeInfo.fromLeft.y;
	endVector.z -= m_bridgeInfo.fromLeft.z;
	endVector.normalize();
	// Offset by 1 pathfind cell.
	endVector.x *= PATHFIND_CELL_SIZE_F;
	endVector.y *= PATHFIND_CELL_SIZE_F;

	Coord3D fromLeft;
	fromLeft.x = m_bridgeInfo.fromLeft.x;
	fromLeft.y = m_bridgeInfo.fromLeft.y;
	fromLeft.z = m_bridgeInfo.fromLeft.z;
	fromLeft.x += endVector.x;
	fromLeft.y += endVector.y;

	Coord3D fromRight;
	fromRight.x = m_bridgeInfo.fromRight.x;
	fromRight.y = m_bridgeInfo.fromRight.y;
	fromRight.z = m_bridgeInfo.fromRight.z;
	fromRight.x -= endVector.x;
	fromRight.y -= endVector.y;

	if (m_c8) {
		endVector = m_bridgeInfo.toRight;
		endVector.x -= m_bridgeInfo.toLeft.x;
		endVector.y -= m_bridgeInfo.toLeft.y;
		endVector.z -= m_bridgeInfo.toLeft.z;
		endVector.normalize();
		endVector.x *= PATHFIND_CELL_SIZE_F;
		endVector.y *= PATHFIND_CELL_SIZE_F;
	}

	Coord3D toLeft;
	toLeft.x = m_bridgeInfo.toLeft.x;
	toLeft.y = m_bridgeInfo.toLeft.y;
	toLeft.z = m_bridgeInfo.toLeft.z;
	toLeft.x += endVector.x;
	toLeft.y += endVector.y;

	Coord3D toRight;
	toRight.x = m_bridgeInfo.toRight.x;
	toRight.y = m_bridgeInfo.toRight.y;
	toRight.z = m_bridgeInfo.toRight.z;
	toRight.x -= endVector.x;
	toRight.y -= endVector.y;

	Coord2D line1, line2;
	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = fromRight.x;
	line2.y = fromRight.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	line1.x = toLeft.x;
	line1.y = toLeft.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	return(false);
}

// ?isCellOnSide@Bridge@@QAE_NPBURegion2D@@@Z @0x0027C95B
Bool Bridge::isCellOnSide(const Region2D *cell)
{
	Coord3D endVector;
	endVector.x = m_bridgeInfo.fromRight.x - m_bridgeInfo.fromLeft.x;
	endVector.y = m_bridgeInfo.fromRight.y - m_bridgeInfo.fromLeft.y;
	endVector.z = m_bridgeInfo.fromRight.z - m_bridgeInfo.fromLeft.z;
	endVector.normalize();
	// Offset by 1 pathfind cell.
	endVector.x *= PATHFIND_CELL_SIZE_F*0.51f;
	endVector.y *= PATHFIND_CELL_SIZE_F*0.51f;

	Coord3D fromLeft;
	fromLeft.x = m_bridgeInfo.fromLeft.x;
	fromLeft.y = m_bridgeInfo.fromLeft.y;
	fromLeft.z = m_bridgeInfo.fromLeft.z;
	fromLeft.x -= endVector.x;
	fromLeft.y -= endVector.y;

	Coord3D fromRight;
	fromRight.x = m_bridgeInfo.fromRight.x;
	fromRight.y = m_bridgeInfo.fromRight.y;
	fromRight.z = m_bridgeInfo.fromRight.z;
	fromRight.x += endVector.x;
	fromRight.y += endVector.y;

	Coord3D toLeft;
	toLeft.x = m_bridgeInfo.toLeft.x;
	toLeft.y = m_bridgeInfo.toLeft.y;
	toLeft.z = m_bridgeInfo.toLeft.z;
	toLeft.x -= endVector.x;
	toLeft.y -= endVector.y;

	Coord3D toRight;
	toRight.x = m_bridgeInfo.toRight.x;
	toRight.y = m_bridgeInfo.toRight.y;
	toRight.z = m_bridgeInfo.toRight.z;
	toRight.x += endVector.x;
	toRight.y += endVector.y;

	Coord2D line1, line2;
	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = toLeft.x;
	line2.y = toLeft.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	line1.x = fromRight.x;
	line1.y = fromRight.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	fromLeft.x -= endVector.x;
	fromLeft.y -= endVector.y;

	fromRight.x += endVector.x;
	fromRight.y += endVector.y;

	toLeft.x -= endVector.x;
	toLeft.y -= endVector.y;

	toRight.x += endVector.x;
	toRight.y += endVector.y;

	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = toLeft.x;
	line2.y = toLeft.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	line1.x = fromRight.x;
	line1.y = fromRight.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	return(false);
}

// ?isCellEntryPoint@Bridge@@QAE_NPBURegion2D@@PAM@Z @0x0027CB7F
Bool Bridge::isCellEntryPoint(const Region2D *cell, Real *z)
{
	Coord3D endVector;
	endVector.x = m_bridgeInfo.fromRight.x - m_bridgeInfo.fromLeft.x;
	endVector.y = m_bridgeInfo.fromRight.y - m_bridgeInfo.fromLeft.y;
	endVector.z = m_bridgeInfo.fromRight.z - m_bridgeInfo.fromLeft.z;
	endVector.normalize();
	// Offset by 1 pathfind cell.
	endVector.x *= PATHFIND_CELL_SIZE_F;
	endVector.y *= PATHFIND_CELL_SIZE_F;
	Coord3D bridgeVector;
	bridgeVector.x = m_bridgeInfo.to.x - m_bridgeInfo.from.x;
	bridgeVector.y = m_bridgeInfo.to.y - m_bridgeInfo.from.y;
	bridgeVector.z = m_bridgeInfo.to.z - m_bridgeInfo.from.z;
	bridgeVector.normalize();
	// Offset by 1/2 pathfind cell.
	bridgeVector.x *= PATHFIND_CELL_SIZE_F/2;
	bridgeVector.y *= PATHFIND_CELL_SIZE_F/2;

	Coord3D fromLeft;
	fromLeft.x = m_bridgeInfo.fromLeft.x;
	fromLeft.y = m_bridgeInfo.fromLeft.y;
	fromLeft.z = m_bridgeInfo.fromLeft.z;
	fromLeft.x -= bridgeVector.x;
	fromLeft.y -= bridgeVector.y;
	fromLeft.x += endVector.x;
	fromLeft.y += endVector.y;

	Coord3D fromRight;
	fromRight.x = m_bridgeInfo.fromRight.x;
	fromRight.y = m_bridgeInfo.fromRight.y;
	fromRight.z = m_bridgeInfo.fromRight.z;
	fromRight.x -= bridgeVector.x;
	fromRight.y -= bridgeVector.y;
	fromRight.x -= endVector.x;
	fromRight.y -= endVector.y;

	Coord3D toLeft;
	toLeft.x = m_bridgeInfo.toLeft.x;
	toLeft.y = m_bridgeInfo.toLeft.y;
	toLeft.z = m_bridgeInfo.toLeft.z;
	toLeft.x += bridgeVector.x;
	toLeft.y += bridgeVector.y;
	toLeft.x += endVector.x;
	toLeft.y += endVector.y;

	Coord3D toRight;
	toRight.x = m_bridgeInfo.toRight.x;
	toRight.y = m_bridgeInfo.toRight.y;
	toRight.z = m_bridgeInfo.toRight.z;
	toRight.x += bridgeVector.x;
	toRight.y += bridgeVector.y;
	toRight.x -= endVector.x;
	toRight.y -= endVector.y;

	Coord2D line1, line2;
	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = fromRight.x;
	line2.y = fromRight.y;
	if (LineInRegion(&line1, &line2, cell)) {
		*z = fromLeft.z;
		return true;
	}
	line1.x = toLeft.x;
	line1.y = toLeft.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell)) {
		*z = toLeft.z;
		return true;
	}
	return(false);
}

// ?loadPostProcess@W3DTerrainLogic@@MAEXXZ @0x00062E4A 5B: slot 1 of vtable
// 0x007C5890, the device terrain logic (??_7Rva0062AF7, whose slot 2 returns
// "W3DTerrainLogic"). Zero Hour's W3DTerrainLogic::loadPostProcess only
// extends the base, so it is a tail jump to TerrainLogic::loadPostProcess
// above (slot 1 of TerrainLogic's vtable 0x007FB2C8).
#include "../../../../GameEngineDevice/Include/W3DDevice/GameLogic/W3DTerrainLogicClass.h"

void W3DTerrainLogic::loadPostProcess(void)
{
	TerrainLogic::loadPostProcess();
}
