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

// lookAt support views (WW3D2 camera, ray test and vector math as ZH defines them).
class WWMath { public: static float __fastcall Inv_Sqrt(float val); };
class Vector2 { public: Real X, Y; Vector2(Real x, Real y) : X(x), Y(y) {} };
class Vector3
{
public:
	Real X, Y, Z;
	Vector3() {}
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline Real Length2() const { return X * X + Y * Y + Z * Z; }
	__forceinline void Normalize()
	{
		Real len2 = Length2();
		if (len2 != 0.0f) {
			Real oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen; Y *= oolen; Z *= oolen;
		}
	}
	__forceinline Vector3 &operator-=(const Vector3 &v) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
	__forceinline Vector3 &operator+=(const Vector3 &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	__forceinline Vector3 &operator*=(Real k) { X *= k; Y *= k; Z *= k; return *this; }
};
class LineSegClass { public: void Set(const Vector3 &p0, const Vector3 &p1); char m_pad[0x34]; };
struct CastResultStruct
{
	Bool StartBad;		// +0x00
	Real Fraction;		// +0x04
	Vector3 Normal;		// +0x08
	Int SurfaceType;	// +0x14
	Bool ComputeContactPoint;	// +0x18
	Vector3 ContactPoint;	// +0x1C
	CastResultStruct() : StartBad(false), Fraction(1.0f), Normal(0, 0, 0), SurfaceType(0), ComputeContactPoint(false), ContactPoint(0, 0, 0) {}
};
class RayCollisionTestClass { public: RayCollisionTestClass(const LineSegClass &ray, CastResultStruct *res, int collision_type, bool check_translucent, bool check_hidden); char m_pad[0x44]; };
class RenderObjClass { public: Vector3 Get_Position() const; };
class CameraClass : public RenderObjClass
{
public:
	void Un_Project(Vector3 &dest, const Vector2 &view_point) const;
	char m_pad[0xF0];
	Real Depth;
	Real Get_Depth() const { return Depth; }
};
class TerrainRenderObject
{
public:
	virtual void c0();
	virtual void c1();
	virtual void c2();
	virtual void c3();
	virtual void c4();
	virtual void c5();
	virtual void c6();
	virtual void c7();
	virtual void c8();
	virtual void c9();
	virtual void c10();
	virtual void c11();
	virtual void c12();
	virtual void c13();
	virtual void c14();
	virtual void c15();
	virtual void c16();
	virtual void c17();
	virtual void c18();
	virtual void c19();
	virtual void c20();
	virtual void c21();
	virtual void c22();
	virtual void c23();
	virtual void c24();
	virtual void c25();
	virtual void c26();
	virtual void c27();
	virtual void c28();
	virtual void c29();
	virtual void c30();
	virtual void c31();
	virtual void c32();
	virtual void c33();
	virtual void c34();
	virtual void c35();
	virtual void c36();
	virtual void c37();
	virtual void c38();
	virtual void c39();
	virtual void c40();
	virtual void c41();
	virtual void c42();
	virtual void c43();
	virtual void c44();
	virtual void c45();
	virtual void c46();
	virtual void c47();
	virtual void c48();
	virtual void c49();
	virtual void c50();
	virtual void c51();
	virtual void c52();
	virtual void c53();
	virtual void c54();
	virtual void c55();
	virtual void c56();
	virtual void c57();
	virtual void c58();
	virtual void c59();
	virtual bool Cast_Ray(RayCollisionTestClass &raytest);
};
// Native ray casting uses the terrain singleton at VA00DE1EAC. Its existing
// definition in W3DFloorDrawDtor.cpp is BaseHeightMapRenderObjClass *. Keep that
// actual global identity and use the already measured ray-test view below.
// BFME1 revision575ba2's terrain-owner repairs are a semantic lead; BFME2's
// own definition and the caller's DIR32/virtual-slot evidence establish this
// binding independently. The view does not establish the full terrain class.
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;



// The 0x000869CF reset, 0x00088D0A and 0x00086A94 sit in the same retail unit as
// W3DView::lookAt (tu_map: W3DView.cpp); defining them here is what lets cl
// keep ECX across the 869CF call in lookAt and in 88D0A.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ?rva000869CF@Rva000869CF@@QAEPAMXZ @0x000869CF 79B zero-init method, callers 0x00088D0A 0x00086F56 0x0008D477 0x0008D925, no vtable, no donor
float *Rva000869CF::rva000869CF()
{
	float *vec = m_244cArr;
	m_2354 = 0;
	m_1dc = 0;
	m_204 = 0;
	m_228 = 0;
	m_27d = 0;
	m_27c = 0;
	m_23c8 = 0;
	vec[0] = 0.0f;
	vec[1] = 0.0f;
	vec[2] = 0.0f;
	m_58 = 0;
	m_5c = 0;
	m_68 = 0.0f;
	return vec;
}

// ?rva00088D0A@Rva000869CF@@QAEXMHM@Z @0x00088D0A 91B, slot 0 of the table
// at VA 0x00BC764C: reset through 0x000869CF (same unit, so retail keeps
// ECX across the call), store the first argument at +0x4C, rescale the
// +0x24C8 member's slot-7 value from its slot 1 by the third argument, and
// pull slot 7 down to slot 0 when slot 0 exceeds slot 1. The second
// argument is unused. Retail compares with fcompi under /arch:SSE.
void Rva000869CF::rva00088D0A(float value, int unused, float scale)
{
	rva000869CF();
	m_4c = value;
	m_24c8.v7(m_24c8.v1() * scale);
	if (m_24c8.v0() > m_24c8.v1())
		m_24c8.v7(m_24c8.v0());
}


// ?rva00086A94@Rva000869CF@@QAEXHHM@Z @0x00086A94 152B; target call at 0x00089C2D reads the 768-float history and index at +0x2070.
void Rva000869CF::rva00086A94(int a, int b, float c)
{
	int index = m_2070;
	_ReadWriteBarrier();
	float *p = &m_1470[index];
	m_146c = c;
	switch (b) {
	case 2:
		p[-2] = c;
		p[-1] = m_1470[0];
		break;
	case 1:
		p[-1] = p[-2] - p[-3] + p[-2];
		break;
	case 0:
		p[-1] = p[-2];
		break;
	default:
		p[-1] = p[-2];
		break;
	}
	switch (a) {
	case 2:
		m_1468 = p[-3];
		break;
	case 1:
		m_1468 = m_146c - m_1470[0] + m_146c;
		break;
	case 0:
		m_1468 = m_146c;
		break;
	default:
		m_1468 = m_146c;
		break;
	}
}

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
	BFME_W3D_SLOT(27) virtual void slot28(Bool) = 0; BFME_W3D_SLOT(29)
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
	virtual void lookAt(const Coord3D *o);

	void setZoomToDefault();
	void rva0008D925(const Coord3D *,Int,Real,Real);
private:
	void rva000860AF(Coord3D *pos);
	void setCameraTransform();
	void buildCameraTransform(Matrix3D *);
	char m_padding0004[0x0c - 4];
	Coord3D m_pos;
	char m_padding0018[0x3c - 0x18];
	Real m_zoom, m_heightAboveGround;
	char m_padding0044[0x104 - 0x44];
	CameraClass *m_3DCamera;
	char m_padding0108[0x19c - 0x108];Int m_resetFrames,m_resetCurrent;char m_padding01a4[0x1ac-0x1a4];
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
	char m_padding23f4[0x2408 - 0x23f4];
	Real m_groundLevel;
	char m_padding240c[0x241c - 0x240c];
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

// Native 8D55D..8D805: ZH W3DView::lookAt with BFME's constrain step and
// ground-height refresh. Vtable slot 0x70 is called with false.
void W3DView::lookAt(const Coord3D *o)
{
	Coord3D pos;
	pos.x = o->x;
	pos.y = o->y;
	pos.z = o->z;

	rva000860AF(&pos);

	if (o->z > 10.0f + TheTerrainLogic->getGroundHeight(pos.x, pos.y)) {
		Vector3 rayStart, rayEnd;
		LineSegClass lineseg;
		CastResultStruct result;

		rayStart = m_3DCamera->Get_Position();
		m_3DCamera->Un_Project(rayEnd, Vector2(0.0f, 0.0f));
		rayEnd -= rayStart;
		rayEnd.Normalize();
		rayEnd *= m_3DCamera->Get_Depth();
		rayStart.Set(pos.x, pos.y, pos.z);
		rayEnd += rayStart;
		lineseg.Set(rayStart, rayEnd);

		RayCollisionTestClass raytest(lineseg, &result, 2, false, false);

		if (((TerrainRenderObject *)TheTerrainRenderObject)->Cast_Ray(raytest)) {
			pos.x = result.ContactPoint.X;
			pos.y = result.ContactPoint.Y;
		}
	}
	pos.z = 0;
	m_pos = pos;
	m_doingRotateCamera = false;
	((Rva000869CF *)this)->rva000869CF();
	slot28(false);

	Real height = getHeightAroundPos(m_pos.x, m_pos.y);
	if (m_useHeightField)
		height = m_cameraHeightField.rva0030E67C(m_pos.x, m_pos.y);
	if (height != m_groundLevel) {
		m_groundLevel = height;
		m_cameraConstraintValid = false;
	}
	setCameraTransform();
}
