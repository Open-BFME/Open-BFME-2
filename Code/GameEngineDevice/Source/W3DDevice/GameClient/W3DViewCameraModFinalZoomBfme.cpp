// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
// Ported from Open-BFME-1 6583b3c1ff21db4a561285717028fdafc780b7db.
// cameraModFinalZoom is target W3DView vftable VA 0x00BC756C slot 30.
// Retail 0x000865DB..0x00086702 is 295 bytes ending in RET 12.
// Target deltas: zoom virtual at +0xEC; cameraOffsetZ at +0x23F0;
// cameraLimits at +0x24C8. The source algorithm is carried from the donor.
// getHeightAroundPos is the file-static W3DView.cpp donor helper with
// target sampling order and a configurable sample distance at GlobalData +0xDD8.
// Retail 0x00085677..0x000857CD ends in RET and returns its float in XMM0.
// Both call sites in the zoom body establish its two-float cdecl ABI.
// rva0008D925 (reset-camera transition, 447B) dereferences the location through (p?p:p): the same-valued
// PHI orders the first plane multiply operand loads as retail does.
// Five getGroundHeight calls use vtable +0x18 with a null normal out pointer.
// The global bindings and member offsets are read independently from retail.

typedef float Real;
typedef int Int;
typedef bool Bool;

// Rva00086761CameraMove.cpp owns this proven runtime frame period.
extern Int g_Va00DE204C;
#define TheAnimationMsPerStep (g_Va00DE204C)

struct Coord3D;
class TerrainLogic
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual float getGroundHeight(float x, float y, Coord3D *normal = 0);
};

class GlobalData
{
public:
    char unreconstructed[0xdd8];
    float cameraTerrainSampleSize;
};
extern TerrainLogic *TheTerrainLogic;
// GameClient.cpp owns the target singleton pointer. ZH aliases TheGlobalData to it.
extern GlobalData *TheWritableGlobalData;
static float getHeightAroundPos(float x, float y)
{
    float center = TheTerrainLogic->getGroundHeight(x, y);
    float lowPlus = TheTerrainLogic->getGroundHeight(
        x - TheWritableGlobalData->cameraTerrainSampleSize, y + TheWritableGlobalData->cameraTerrainSampleSize);
    float highPlus = TheTerrainLogic->getGroundHeight(
        x + TheWritableGlobalData->cameraTerrainSampleSize, y + TheWritableGlobalData->cameraTerrainSampleSize);
    float plus = highPlus > lowPlus ? highPlus : lowPlus;
    float lowMinus = TheTerrainLogic->getGroundHeight(
        x - TheWritableGlobalData->cameraTerrainSampleSize, y - TheWritableGlobalData->cameraTerrainSampleSize);
    float highMinus = TheTerrainLogic->getGroundHeight(
        x + TheWritableGlobalData->cameraTerrainSampleSize, y - TheWritableGlobalData->cameraTerrainSampleSize);
    float minus = highMinus > lowMinus ? highMinus : lowMinus;
    float corners = minus > plus ? minus : plus;
    return center > corners ? center : corners;
}


class CameraLimit
{
public:
	virtual Real getMinimum();
	virtual Real getMaximum();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18(void *,void *);
};

#define BFME_W3D_SLOT(n) virtual void slot##n() = 0;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct WaypointXY
{
	Real x;
	Real y;
	char padding[4];
};

class Rva0030E7D0 { public: Real rva0030E67C(Real x,Real y); };

class Matrix3D;
class Rva000857F2 {public:void rva000857F2();};
#include "../../../../GameEngine/Source/GameClient/Rva000869CF.h"
class GameClient; extern GameClient *TheGameClient;
struct Rva0008D925ClientFrame {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual unsigned slot31();
};
class ParabolicEase {public:void rva0030E51F(float,float,float);};
class W3DView
{
public:
	BFME_W3D_SLOT(0)  BFME_W3D_SLOT(1)  BFME_W3D_SLOT(2)
	BFME_W3D_SLOT(3)  BFME_W3D_SLOT(4)  BFME_W3D_SLOT(5)
	BFME_W3D_SLOT(6)  BFME_W3D_SLOT(7)  BFME_W3D_SLOT(8)
	BFME_W3D_SLOT(9)  BFME_W3D_SLOT(10) BFME_W3D_SLOT(11)
	BFME_W3D_SLOT(12) BFME_W3D_SLOT(13) BFME_W3D_SLOT(14)
	BFME_W3D_SLOT(15) BFME_W3D_SLOT(16) BFME_W3D_SLOT(17)
	BFME_W3D_SLOT(18) BFME_W3D_SLOT(19) BFME_W3D_SLOT(20)
	BFME_W3D_SLOT(21) BFME_W3D_SLOT(22) BFME_W3D_SLOT(23)
	BFME_W3D_SLOT(24) BFME_W3D_SLOT(25) BFME_W3D_SLOT(26)
	BFME_W3D_SLOT(27) BFME_W3D_SLOT(28) BFME_W3D_SLOT(29)
	BFME_W3D_SLOT(30) BFME_W3D_SLOT(31) BFME_W3D_SLOT(32)
	BFME_W3D_SLOT(33) BFME_W3D_SLOT(34) BFME_W3D_SLOT(35)
	BFME_W3D_SLOT(36) BFME_W3D_SLOT(37) BFME_W3D_SLOT(38)
	BFME_W3D_SLOT(39) BFME_W3D_SLOT(40) BFME_W3D_SLOT(41)
	BFME_W3D_SLOT(42) BFME_W3D_SLOT(43) BFME_W3D_SLOT(44)
	BFME_W3D_SLOT(45) BFME_W3D_SLOT(46) BFME_W3D_SLOT(47)
	BFME_W3D_SLOT(48) BFME_W3D_SLOT(49) BFME_W3D_SLOT(50)
	BFME_W3D_SLOT(51) BFME_W3D_SLOT(52) BFME_W3D_SLOT(53)
	BFME_W3D_SLOT(54) BFME_W3D_SLOT(55) BFME_W3D_SLOT(56)
	BFME_W3D_SLOT(57) BFME_W3D_SLOT(58)
	virtual void zoomCamera(Real finalZoom, Int milliseconds,
		Real easeIn, Real easeOut);
	virtual void cameraModFinalZoom(Real finalZoom, Real easeIn, Real easeOut);

	void setZoomToDefault();
	void rva0008D925(const Coord3D *,Int,Real,Real);
private:
	void setCameraTransform();
	void buildCameraTransform(Matrix3D *);
	char m_padding0004[0x0c - 4];
	Coord3D m_pos;
	char m_padding0018[0x3c - 0x18];
	Real m_zoom, m_heightAboveGround;
	char m_padding0044[0x19c - 0x44];Int m_resetFrames,m_resetCurrent;char m_padding01a4[0x1ac-0x1a4];
	Int m_rcNumFrames;
	Int m_rcCurFrame;
	char m_padding01b4[0x1bc - 0x1b4];
	Int m_rcNumHoldFrames;
	char m_padding01c0[0x1dc - 0x1c0];
	Bool m_doingRotateCamera;
	char m_padding01dd[0x204 - 0x1dd];
	Bool m_doingPitchCamera;
	char m_padding0205[0x228 - 0x205];
	Bool m_doingZoomCamera;
	char m_padding0229[0x27c - 0x229];
	Bool m_doingScriptedCameraLock,m_CameraArrivedAtWaypointOnPathFlag;
	char m_padding027e[0x22f0 - 0x27e];
	Int m_numWaypoints;
	char m_padding22f4[0x2354 - 0x22f4];
	Int m_cameraMovementMode;
	char m_padding2358[0x23f0 - 0x2358];
	Real m_cameraOffsetZ;
	char m_padding23f4[0x241c - 0x23f4];
	Bool m_cameraConstraintValid;
	char m_padding241d[0x2458 - 0x241d];
	Rva0030E7D0 m_cameraHeightField;
	char m_padding2459[0x2474 - 0x2459];
	Bool m_useHeightField;
	char m_padding2475[0x24c8 - 0x2475];
	CameraLimit m_cameraLimits;
};

#undef BFME_W3D_SLOT

// ?cameraModFinalZoom@W3DView@@UAEXMMM@Z present-unmatched
void W3DView::cameraModFinalZoom(Real finalZoom, Real easeIn, Real easeOut)
{
	Real terrainHeightMax;
	Real maxHeight;
	Real maxZoom;
	Real time;

	if (m_doingRotateCamera)
	{
		terrainHeightMax = getHeightAroundPos(m_pos.x, m_pos.y);
		maxHeight = terrainHeightMax + m_cameraLimits.getMaximum();
		maxZoom = maxHeight / m_cameraOffsetZ;

		time = (m_rcNumFrames + m_rcNumHoldFrames - m_rcCurFrame) * TheAnimationMsPerStep;
		zoomCamera(finalZoom * maxZoom, time, time * easeIn, time * easeOut);
	}
	if (m_cameraMovementMode == 1)
	{
		if (m_numWaypoints >= 4)
		{
			Coord3D *position = (Coord3D *)((char *)this + 0x284 + m_numWaypoints * 0x14);
			WaypointXY waypoint;
			waypoint.x = position->x;
			waypoint.y = position->y;
			terrainHeightMax = getHeightAroundPos(waypoint.x, waypoint.y);
			maxHeight = terrainHeightMax + m_cameraLimits.getMaximum();
			maxZoom = maxHeight / m_cameraOffsetZ;
			time = *(Int *)((char *)this + 0x284) - *(Int *)((char *)this + 0x288);
			zoomCamera(finalZoom * maxZoom, time, time * easeIn, time * easeOut);
		}
	}
}

// Native 8D477..8D55D: guarded default-zoom update. BF1 f989/ZH
// setZoomToDefault is the semantic guide; target adds movement guards and
// the optional flat-grid height source at2458/2474. All offsets from bytes.
void W3DView::setZoomToDefault()
{
 if(m_cameraMovementMode || m_doingRotateCamera || m_doingPitchCamera ||
    m_doingZoomCamera || m_CameraArrivedAtWaypointOnPathFlag || m_doingScriptedCameraLock) return;
 Real height = getHeightAroundPos(m_pos.x,m_pos.y);
 if(m_useHeightField) height=m_cameraHeightField.rva0030E67C(m_pos.x,m_pos.y);
 Real desiredHeight=height+m_cameraLimits.getMaximum();
 m_zoom=desiredHeight/m_cameraOffsetZ;
 m_heightAboveGround=m_cameraLimits.getMaximum();
 m_doingRotateCamera=false;
 m_doingPitchCamera=false;
 m_doingScriptedCameraLock=false;
 m_doingZoomCamera=false;
 m_CameraArrivedAtWaypointOnPathFlag=false;
 m_cameraConstraintValid=false;
 setCameraTransform();
}

// Reference lead: ZH resetCamera, target native 8D925..8DAE4 RET16.
// BFME adds the remembered-position guard, camera-limit reset and paired
// transition transforms. Method name remains address-derived.
void W3DView::rva0008D925(const Coord3D *location,Int milliseconds,Real easeIn,Real easeOut)
{
 char *bytes=(char *)this;
 if(!location && bytes[0x2504])return;
 ((Rva000857F2 *)(bytes+0x24f4))->rva000857F2();
 if(!location){location=&m_pos;bytes[0x2500]=1;}
 m_cameraLimits.slot17();
 buildCameraTransform((Matrix3D *)(bytes+0x13c));
 ((Rva000869CF *)this)->rva000869CF();
 m_pos=*(location?location:location);
 Real height=getHeightAroundPos(m_pos.x,m_pos.y);
 if(m_useHeightField)height=m_cameraHeightField.rva0030E67C(m_pos.x,m_pos.y);
 Real &oldHeight=*(Real *)(bytes+0x2408);
 if(height!=oldHeight){oldHeight=height;m_cameraConstraintValid=false;}
 m_zoom=(m_cameraLimits.getMaximum()+oldHeight)/m_cameraOffsetZ;
 m_heightAboveGround=m_cameraLimits.getMaximum();
 m_cameraLimits.slot18(bytes+0x23e8,bytes+0x28);
 *(Real *)(bytes+0x23e8)*=*(Real *)(bytes+0xa0);
 *(Real *)(bytes+0x23ec)*=*(Real *)(bytes+0xa0);
 *(Real *)(bytes+0x6c)=0.87266463f;
 *(Real *)(bytes+0x70)=1.0f;
 *(Real *)(bytes+0x30)=0.0f;
 buildCameraTransform((Matrix3D *)(bytes+0x16c));
 if(milliseconds>1){
  m_cameraMovementMode=3;
  m_resetFrames=milliseconds/g_Va00DE204C;
  m_resetFrames=m_resetFrames<1?1:m_resetFrames;
  m_resetCurrent=0;
  ((ParabolicEase *)(bytes+0x1a4))->rva0030E51F(easeIn,easeOut,(Real)milliseconds);
  *(unsigned *)(bytes+0x2358)=((Rva0008D925ClientFrame *)TheGameClient)->slot31();
 }else setCameraTransform();
}
