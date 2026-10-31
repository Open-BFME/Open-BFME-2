// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /ICode/Libraries/Include
// BFME 1 W3DProjectedShadowDecalHelpers.cpp, donor revision
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20, compiled with BFME 2 flags above.
// These file-static algorithms come from ZH queueDecal: flatten/normalise the
// transform axes, and find the extrema of four projected corner coordinates.
// Their original private names are unknown, so names retain target addresses.
// Native axes body 0x108E7A..0x108FBD (323B), Ghidra FUN_00508e7a. Calls at
// 0x10ACAB / 0x10ACBF / 0x10CB9C pass Matrix3D in ESI and two Vector3 outputs
// in ECX/EDX. X/Y basis elements are +0/+0x10 and +4/+0x14; output Z is zero.
// Native extrema body 0x108E33..0x108E7A (71B), immediately after the thunk
// at 0x108E28. Inputs use XMM1/2/3 and one stack float; hidden Vector2 output
// is EAX. The projected-range body at 0x108FBD inlines the same extrema logic.
// A compiler-visible caller preserves both private conventions, as MSVC 7.1
// derives them from same-unit calls. It is an emission pattern, not a retail
// caller recovery. All body bytes and compiler float literals are verified.
// Native layer helper1086EC..108790164: ZH queueDecal bridge-layer
// semantic guide; WB queueDualDecal names the caller. Object getter28B511
// confirms layer40C/override48C; native user-data slot87 and drawableFC.
// Raw byte access to drawable object preserves private EAX/EBX/ESI ABI.
// W3DProjectedShadowManager::queueDualDecal (native 0x10A736..0x10B9B5, 4737B,
// RET 4, EH) is the real same-unit caller of the axes, layer and range helpers;
// WB 0x8CEAC0 names it and is the source-shape guide (per-decal size/offset
// arrays, per-loop counters, getDecalOffset/getAngle/getPosition accessors),
// ZH queueDecal the semantic guide. Its getDecalOffset(1) call is the
// out-of-line accessor copy at 0x1089EA (cl inlines the [0] call only).
// The remaining emission pattern anchors only the extrema helper.

// Keep the unused math.h wrapper local to this translation unit.
extern "C" { static float __cdecl floorf(float); }
#include "wwmath.h"
#include "vector3.h"
#include "matrix3d.h"
#include "Lib/Coord3D.h"
#include "../../../../../GameEngine/Source/Common/PartitionRangeQueryCallView.h"
// std::max as VC7.1 <xutility> spells it (<algorithm> collides with WWLib's
// placement operator new definitions in this unit).
namespace std { template<class _Ty> inline const _Ty &max(const _Ty &_Left, const _Ty &_Right) { return (_Left < _Right ? _Right : _Left); } }
#include <math.h>
#include <stdlib.h>

// Scoped storage views use the evidenced 12B vector, 8B pair, and 3x4 matrix
// representations without defining copies of the public math-library methods.
class Rva00108E7AVector
{
public:
    float X, Y, Z;
    WWINLINE Rva00108E7AVector() {}
    WWINLINE Rva00108E7AVector(float x, float y, float z) { X=x; Y=y; Z=z; }
    WWINLINE Rva00108E7AVector &operator=(const Rva00108E7AVector &v)
    { X=v.X; Y=v.Y; Z=v.Z; return *this; }
    WWINLINE Rva00108E7AVector &operator*=(float k)
    { X=X*k; Y=Y*k; Z=Z*k; return *this; }
    WWINLINE void Set(float x, float y, float z) { X=x; Y=y; Z=z; }
    WWINLINE float Length() const { return WWMath::Sqrt(X*X+Y*Y+Z*Z); }
};
class Rva00108E33Pair
{
public:
    float X, Y;
    WWINLINE Rva00108E33Pair() : X(0.0f), Y(0.0f) {}
    WWINLINE Rva00108E33Pair(float x, float y) { X=x; Y=y; }
};
class Rva00108E7AMatrix
{
public:
    float Row[3][4];
    WWINLINE Rva00108E7AVector Get_X_Vector() const
    { return Rva00108E7AVector(Row[0][0],Row[1][0],Row[2][0]); }
    WWINLINE Rva00108E7AVector Get_Y_Vector() const
    { return Rva00108E7AVector(Row[0][1],Row[1][1],Row[2][1]); }
};

static void decalAxesRva00108E7A(const Rva00108E7AMatrix &objXform, Rva00108E7AVector &uVector, Rva00108E7AVector &vVector)
{
	uVector = objXform.Get_X_Vector();
	uVector.Z = 0.0f;
	float vecLength = uVector.Length();
	//prevent divide by zero
	if (vecLength != 0.0f) {
		uVector *= 1.0f / vecLength;
		vVector.Set(uVector.Y, -uVector.X, 0.0f);
	} else {
		vVector = objXform.Get_Y_Vector();
		vVector.Z = 0.0f;
		vecLength = vVector.Length();
		//prevent divide by zero
		if (vecLength != 0.0f)
			vVector *= 1.0f / vecLength;
		else
			vVector.Set(0.0f, -1.0f, 0.0f); //Point uvector in default direction
		uVector.Set(-vVector.Y, vVector.X, 0.0f);
	}
}

static Rva00108E33Pair minMax4Rva00108E33(float a, float b, float c, float d)
{
	float lo, hi;
	if (a < b) {
		lo = a;
		hi = b;
	} else {
		lo = b;
		hi = a;
	}
	if (c < d) {
		if (c < lo)
			lo = c;
		if (d > hi)
			hi = d;
	} else {
		if (d < lo)
			lo = d;
		if (c > hi)
			hi = c;
	}
	return Rva00108E33Pair(lo, hi);
}
// Native projected-range body 0x108FBD..0x109129 (364B, RET 0): ZH queueDecal's
// box-corner extents for the dual decal (queueDualDecal 0x10A736 and 0x10C841
// call it). Axis inputs arrive in ECX/EAX, the x/y range outputs in EDX/ESI,
// size and offset pairs on the stack; cl derives that private convention from
// the same-unit caller below. The extrema are the minMax4 logic inlined, the
// ranges are 8-byte pair copies (integer moves through a stack temporary).
static __forceinline Rva00108E33Pair minMax4Inline(float a, float b, float c, float d)
{
	float lo, hi;
	if (a < b) {
		lo = a;
		hi = b;
	} else {
		lo = b;
		hi = a;
	}
	if (c < d) {
		if (c < lo)
			lo = c;
		if (d > hi)
			hi = d;
	} else {
		if (d < lo)
			lo = d;
		if (c > hi)
			hi = c;
	}
	return Rva00108E33Pair(lo, hi);
}

static WWINLINE Rva00108E7AVector operator+(const Rva00108E7AVector&a,const Rva00108E7AVector&b){return Rva00108E7AVector(a.X+b.X,a.Y+b.Y,a.Z+b.Z);}
static void projectRangesRva00108FBD(const Rva00108E7AVector &axisA, const Rva00108E7AVector &axisB, float sizeA, float sizeB,
	float offA, float offB, Rva00108E33Pair &xr, Rva00108E33Pair &yr)
{
	//Compute bounding box of projection
	Rva00108E7AVector a0(axisA.X * (-((offA + 0.5f) * sizeA)), axisA.Y * (-((offA + 0.5f) * sizeA)), 0.0f);
	Rva00108E7AVector a1(axisA.X * ((0.5f - offA) * sizeA), axisA.Y * ((0.5f - offA) * sizeA), 0.0f);
	Rva00108E7AVector b0(axisB.X * (-((offB + 0.5f) * sizeB)), axisB.Y * (-((offB + 0.5f) * sizeB)), 0.0f);
	Rva00108E7AVector b1(axisB.X * ((0.5f - offB) * sizeB), axisB.Y * ((0.5f - offB) * sizeB), 0.0f);
	///@todo: Optimize this bounding box calculation to use transformed extents
	//Also skip bounding box calculation if object has not moved.
	Rva00108E7AVector c0 = b0 + a0;
	Rva00108E7AVector c1 = b0 + a1;
	Rva00108E7AVector c2 = b1 + a1;
	Rva00108E7AVector c3 = b1 + a0;
	xr = minMax4Inline(c0.X, c1.X, c2.X, c3.X);
	yr = minMax4Inline(c0.Y, c1.Y, c2.Y, c3.Y);
}

class Object {public:int rva0028B511()const;};
class Drawable {public:bool rva0027267D(int,int,int,int);bool rva002726C3(int,int,int,int);int rva0027261D();int rva0027264D();char pad[0xfc];Object*object;};
struct DrawableInfo {void*unknown;Drawable*drawable;};
class AABoxClass;
class RenderObjClass{public:
virtual void Delete_This();
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
virtual void Validate_Transform() const;
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
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual const AABoxClass &Get_Bounding_Box() const;
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual DrawableInfo*Get_User_Data();
Vector3 Get_Position()const;
void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
int NumRefs;char pad08[0x10];Matrix3D transform;
const Matrix3D &Get_Transform() const { Validate_Transform(); return transform; }
};
class TerrainLogic {public:
virtual void pad0();
virtual void pad1();
virtual void pad2();
virtual void pad3();
virtual void pad4();
virtual void pad5();
virtual void pad6();
virtual float getLayerHeight(float,float,int,Rva00108E7AVector*,bool);
virtual void pad8();
virtual void pad9();
virtual void pad10();
virtual void pad11();
virtual void pad12();
virtual void pad13();
virtual void pad14();
virtual void pad15();
virtual void pad16();
virtual void pad17();
virtual void pad18();
virtual void pad19();
virtual void pad20();
virtual void pad21();
virtual void pad22();
virtual void pad23();
virtual void pad24();
virtual void pad25();
virtual void pad26();
virtual class BridgeView10C841 *findBridgeAt(float x, float y, float z);
virtual void pad28();
virtual void pad29();
virtual float getBridgeHeight(class BridgeView10C841 *bridge);
virtual void pad31();
virtual void pad32();
virtual void pad33();
virtual void pad34();
virtual void pad35();
virtual void pad36();
virtual void pad37();
virtual void pad38();
virtual void pad39();
virtual class BridgeView10C841 *getFirstBridge();
};extern TerrainLogic*TheTerrainLogic;
static float layerHeightRva001086EC(RenderObjClass*robj,const Rva00108E7AVector&pos,Rva00108E7AVector&normal){
 if(robj&&robj->Get_User_Data()){
 Drawable*draw=robj->Get_User_Data()->drawable;char*drawBytes=(char*)draw;Object*object=*(Object**)(drawBytes+0xfc);
 if(object){int layer=object->rva0028B511();if(layer!=1&&TheTerrainLogic){Rva00108E7AVector n;float height=TheTerrainLogic->getLayerHeight(pos.X,pos.Y,layer,&n,true);normal=n;return height+1.5f;}}
 }
 normal.Set(0,0,1);return 0;
}

// ?Rva00108E33EmissionPattern absent-from-retail
void Rva00108E33EmissionPattern(float a, float b, float c, float d, Rva00108E33Pair *out)
{
    out[0] = minMax4Rva00108E33(a, b, c, d);
    out[1] = minMax4Rva00108E33(b, c, d, a);
}

class W3DShadowTexture;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
enum ShadowType { SHADOW_NONE = 0 };

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_CEIL(x)		(fast_float2long_round(ceilf(x)))
#define REAL_TO_INT_FLOOR(x)	(fast_float2long_round(floorf(x)))

#define MAP_XY_FACTOR		(10.0f)
#define MAP_HEIGHT_SCALE	(MAP_XY_FACTOR/256.0f)

// The decal halves of a dual projected shadow (target offsets).
struct DualDecalChild
{
	char m_pad00[8];
	Coord3D m_position;					// +0x08
	char m_pad14[0xC];
	Real m_angle;						// +0x20
	char m_pad24[0x34];
	Real m_decalSizeX;					// +0x58
	Real m_decalSizeY;					// +0x5C
	char m_pad60[8];
	W3DShadowTexture *m_shadowTexture;	// +0x68
	Real m_decalOffsetU;				// +0x6C
	Real m_decalOffsetV;				// +0x70
};

class W3DDualProjectedShadow
{
public:
	W3DShadowTexture *getTexture(Int i) const { return m_child[i] ? m_child[i]->m_shadowTexture : 0; }
	void getSize(Int i, Real *x, Real *y) const { DualDecalChild *dualDecalChild = m_child[i]; *x = dualDecalChild->m_decalSizeX; *y = dualDecalChild->m_decalSizeY; }
	Real getAngle(Int i) const { return m_child[i]->m_angle; }
	Real getAngle() const { return m_angle; }
	void getPosition(Int i, Coord3D *pos) const { DualDecalChild *dualDecalChild = m_child[i]; *pos = dualDecalChild->m_position; }
	void getDecalOffset(Int i, Real *u, Real *v) const { DualDecalChild *dualDecalChild = m_child[i]; if (dualDecalChild) { *u = dualDecalChild->m_decalOffsetU; *v = dualDecalChild->m_decalOffsetV; } }

	char m_pad00[8];
	Coord3D m_position;					// +0x08
	Coord3D m_normal;					// +0x14
	Real m_angle;						// +0x20
	Int m_pad24;
	UnsignedInt m_diffuse;				// +0x28
	char m_pad2c[8];
	ShadowType m_type;					// +0x34
	char m_pad38[0x20];
	DualDecalChild *m_child[2];			// +0x58
	RenderObjClass *m_robj;				// +0x60
};

struct SHADOW_DECAL_DUAL_VERTEX { Real x, y, z; UnsignedInt diffuse; Real u0, v0, u1, v1; };
class VertexBufferClass { public: class AppendLockClass { public: AppendLockClass(VertexBufferClass *, unsigned, unsigned, int); ~AppendLockClass(); void *Get_Vertex_Array() { return m_vertices; } VertexBufferClass *m_buffer; void *m_vertices; char m_lock[4]; }; };
class IndexBufferClass { public: class AppendLockClass { public: AppendLockClass(IndexBufferClass *, unsigned, unsigned, int); ~AppendLockClass(); unsigned short *Get_Index_Array() { return m_indices; } IndexBufferClass *m_buffer; unsigned short *m_indices; char m_lock[4]; }; };
class BoundedShortGrid { public: short load(int, int); };
class Gen_0074B410 { public: bool bfmeBitA(int, int) const; };
class WorldHeightMap
{
public:
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->load(x, y); }
	Real getDisplayHeight(Int x, Int y) { return getHeight(x, y) * MAP_HEIGHT_SCALE; }
	// getFlipState is the bounds-checked bit-plane body rowed at 0x000ADF41
	// (Gen_0074B410::bfmeBitA); retail's decal batch calls it directly.
	char m_pad00[0x10];
	Int m_borderSize;					// +0x10
};
class BaseHeightMapRenderObjClass { public: char m_pad[0x37c0]; WorldHeightMap *m_map; };
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
// Terrain draw extents for decals (file statics of W3DProjectedShadow.cpp in ZH;
// retail 0xDEC2DC/E0/E4/E8, set by the shadow render pass).
static Int drawEdgeX = 0;
static Int drawEdgeY = 0;
static Int drawStartX = 0;
static Int drawStartY = 0;

class W3DProjectedShadowManager
{
public:
	void queueDualDecal(W3DDualProjectedShadow *shadow);
	void rva0010C841(struct ShadowRenderEntry10DF33 *shadow, Int unused, Int flushFlags);
	void flushDecals(ShadowType type, W3DShadowTexture *texture0, W3DShadowTexture *texture1, Int flags);
	char m_pad[0x254];
	VertexBufferClass *m_dynamicDecalVertexBuffer;	// +0x254
	IndexBufferClass *m_dynamicDecalIndexBuffer;	// +0x258
	Int m_numDecalVertsInBuffer;		// +0x25C
	Int m_decalStartVertex;				// +0x260
	Int m_numDecalIndicesInBuffer;		// +0x264
	Int m_decalStartIndex;				// +0x268
	Int m_numDecalPolysInBatch;			// +0x26C
	Int m_numDecalVertsInBatch;			// +0x270
};

void W3DProjectedShadowManager::queueDualDecal(W3DDualProjectedShadow *shadow)
{
	W3DShadowTexture *w3DShadowTexture = shadow->getTexture(0);
	W3DShadowTexture *texture1 = shadow->getTexture(1);
	if (!w3DShadowTexture || !texture1)
		return;

	Real decalSizeX[2], decalSizeY[2];
	shadow->getSize(0, &decalSizeX[0], &decalSizeY[0]);
	shadow->getSize(1, &decalSizeX[1], &decalSizeY[1]);
	if ((decalSizeX[0] == 0.0f || decalSizeY[0] == 0.0f) && (decalSizeX[1] == 0.0f || decalSizeY[1] == 0.0f))
		return;

	Matrix3D objXform(true);
	Vector3 objPos;
	Vector3 normal;
	Real layerHeight = 0.0f;
	RenderObjClass *robj = shadow->m_robj;
	if (robj)
	{
		objPos = robj->Get_Position();
		objPos.Z = 0.0f;
		robj->Validate_Transform();
		objXform = robj->transform;
		layerHeight = layerHeightRva001086EC(robj, *(Rva00108E7AVector *)&objPos, *(Rva00108E7AVector *)&normal);
	}
	else
	{
		Coord3D pos;
		pos = shadow->m_position;
		objPos.X = pos.x;
		objPos.Y = pos.y;
		objPos.Z = 0.0f;
		objXform.Rotate_Z(shadow->m_angle);
		normal = Vector3(shadow->m_normal.x, shadow->m_normal.y, shadow->m_normal.z);
	}

	Matrix3D rotations[2];
	rotations[0].Make_Identity();
	rotations[1].Make_Identity();
	rotations[0].Rotate_Z(shadow->getAngle(0) + shadow->getAngle());
	rotations[1].Rotate_Z(shadow->getAngle() + shadow->getAngle(1));

	Vector3 uVector[2], vVector[2];
	decalAxesRva00108E7A(*(Rva00108E7AMatrix *)&rotations[0], *(Rva00108E7AVector *)&uVector[0], *(Rva00108E7AVector *)&vVector[0]);
	decalAxesRva00108E7A(*(Rva00108E7AMatrix *)&rotations[1], *(Rva00108E7AVector *)&uVector[1], *(Rva00108E7AVector *)&vVector[1]);

	Vector3 decalPos[2];
	Coord3D pos;
	shadow->getPosition(0, &pos);
	decalPos[0].X = pos.x;
	decalPos[0].Y = pos.y;
	decalPos[0].Z = 0.0f;
	shadow->getPosition(1, &pos);
	decalPos[1].X = pos.x;
	decalPos[1].Y = pos.y;
	decalPos[1].Z = 0.0f;
	objXform.mulVector3(decalPos[0]);
	objXform.mulVector3(decalPos[1]);

	Real uOffset[2], vOffset[2];
	shadow->getDecalOffset(0, &uOffset[0], &vOffset[0]);
	shadow->getDecalOffset(1, &uOffset[1], &vOffset[1]);

	Rva00108E33Pair xRange[2];
	Rva00108E33Pair yRange[2];
	projectRangesRva00108FBD(*(Rva00108E7AVector *)&uVector[0], *(Rva00108E7AVector *)&vVector[0], decalSizeX[0], decalSizeY[0], uOffset[0], vOffset[0], xRange[0], yRange[0]);
	projectRangesRva00108FBD(*(Rva00108E7AVector *)&uVector[1], *(Rva00108E7AVector *)&vVector[1], decalSizeX[1], decalSizeY[1], uOffset[1], vOffset[1], xRange[1], yRange[1]);

	decalPos[0].X += objPos.X;
	decalPos[1].X += objPos.X;
	decalPos[0].Y += objPos.Y;
	decalPos[1].Y += objPos.Y;

	Rva00108E33Pair boundsX(WWMath::Min(xRange[0].X + decalPos[0].X, xRange[1].X + decalPos[1].X),
		WWMath::Max(xRange[0].Y + decalPos[0].X, xRange[1].Y + decalPos[1].X));
	Rva00108E33Pair boundsY(WWMath::Min(yRange[0].X + decalPos[0].Y, yRange[1].X + decalPos[1].Y),
		WWMath::Max(yRange[0].Y + decalPos[0].Y, yRange[1].Y + decalPos[1].Y));

	if (decalSizeX[0] == 0.0f)
		uVector[0].X = uVector[0].Y = uVector[0].Z = 0.0f;
	else
		uVector[0] /= decalSizeX[0];
	if (decalSizeX[1] == 0.0f)
		uVector[1].X = uVector[1].Y = uVector[1].Z = 0.0f;
	else
		uVector[1] /= decalSizeX[1];
	if (decalSizeY[0] == 0.0f)
		vVector[0].X = vVector[0].Y = vVector[0].Z = 0.0f;
	else
		vVector[0] /= decalSizeY[0];
	if (decalSizeY[1] == 0.0f)
		vVector[1].X = vVector[1].Y = vVector[1].Z = 0.0f;
	else
		vVector[1] /= decalSizeY[1];

	uOffset[0] += 0.5f;
	uOffset[1] += 0.5f;
	vOffset[0] += 0.5f;
	vOffset[1] += 0.5f;

	Real mapScaleInv = 1.0f / MAP_XY_FACTOR;
	WorldHeightMap *hmap = TheTerrainRenderObject->m_map;
	Int borderSize = hmap->m_borderSize;

	Int startX = REAL_TO_INT_FLOOR(boundsX.X * mapScaleInv) + borderSize;
	Int endX = REAL_TO_INT_CEIL(boundsX.Y * mapScaleInv) + borderSize;
	Int startY = REAL_TO_INT_FLOOR(boundsY.X * mapScaleInv) + borderSize;
	Int endY = REAL_TO_INT_CEIL(boundsY.Y * mapScaleInv) + borderSize;

	startX = __max(startX, drawStartX);
	startX = __min(startX, drawEdgeX);
	startY = __max(startY, drawStartY);
	startY = __min(startY, drawEdgeY);

	endX = __max(endX, drawStartX);
	endX = __min(endX, drawEdgeX);
	endY = __max(endY, drawStartY);
	endY = __min(endY, drawEdgeY);

	Int numExtraX = (endX - startX + 1) - 104;
	if (numExtraX > 0)
	{
		Int numStartExtraX = REAL_TO_INT_FLOOR((float)numExtraX / 2.0f);
		Int numEdgeExtraX = numExtraX - numStartExtraX;
		startX += numStartExtraX;
		endX -= numEdgeExtraX;
	}
	Int numExtraY = (endY - startY + 1) - 104;
	if (numExtraY > 0)
	{
		Int numStartExtraY = REAL_TO_INT_FLOOR((float)numExtraY / 2.0f);
		Int numEdgeExtraY = numExtraY - numStartExtraY;
		startY += numStartExtraY;
		endY -= numEdgeExtraY;
	}

	Int vertsPerRow = endX - startX + 1;
	Int vertsPerColumn = endY - startY + 1;
	if (vertsPerRow <= 1 || vertsPerColumn <= 1)
		return;

	Int numVerts = vertsPerRow * vertsPerColumn;
	Int numIndex = (endX - startX) * (endY - startY) * 6;

	Bool flushed = false;
	if (m_numDecalVertsInBuffer + numVerts > 0x8000 || m_numDecalIndicesInBuffer + numIndex > 0x10000)
	{
		flushDecals(shadow->m_type, w3DShadowTexture, texture1, 0);
		m_decalStartVertex = 0;
		m_decalStartIndex = 0;
		m_numDecalPolysInBatch = 0;
		m_numDecalVertsInBatch = 0;
		m_numDecalVertsInBuffer = 0;
		m_numDecalIndicesInBuffer = 0;
		flushed = true;
	}

	{
	VertexBufferClass::AppendLockClass lockVtxBuffer(m_dynamicDecalVertexBuffer, m_numDecalVertsInBuffer, numVerts, flushed ? 0x2000 : 0x1000);
	SHADOW_DECAL_DUAL_VERTEX *pvVertices = (SHADOW_DECAL_DUAL_VERTEX *)lockVtxBuffer.Get_Vertex_Array();
	if (!pvVertices)
		return;
	IndexBufferClass::AppendLockClass lockIdxBuffer(m_dynamicDecalIndexBuffer, m_numDecalIndicesInBuffer, numIndex, flushed ? 0x2000 : 0x1000);
	UnsignedShort *pvIndices = lockIdxBuffer.Get_Index_Array();
	if (!pvIndices)
		return;

	Vector3 hmapVertex;
	Vector3 decalVertex[2];
	UnsignedInt diffuse = shadow->m_diffuse;
	if (layerHeight)
	{
		for (Int j = startY; j <= endY; j++)
		{
			hmapVertex.Y = (float)(j - borderSize) * MAP_XY_FACTOR;
			for (Int i = startX; i <= endX; i++)
			{
				hmapVertex.X = (float)(i - borderSize) * MAP_XY_FACTOR;
				hmapVertex.Z = __max((float)hmap->getHeight(i, j) * MAP_HEIGHT_SCALE, layerHeight);
				decalVertex[0] = hmapVertex - decalPos[0];
				decalVertex[1] = hmapVertex - decalPos[1];
				pvVertices->x = hmapVertex.X;
				pvVertices->y = hmapVertex.Y;
				pvVertices->z = hmapVertex.Z;
				pvVertices->diffuse = diffuse;
				pvVertices->u0 = Vector3::Dot_Product(uVector[0], decalVertex[0]) + uOffset[0];
				pvVertices->v0 = Vector3::Dot_Product(vVector[0], decalVertex[0]) + vOffset[0];
				pvVertices->u1 = Vector3::Dot_Product(uVector[1], decalVertex[1]) + uOffset[1];
				pvVertices->v1 = Vector3::Dot_Product(vVector[1], decalVertex[1]) + vOffset[1];
				pvVertices++;
			}
		}
	}
	else
	{
		for (Int j = startY; j <= endY; j++)
		{
			hmapVertex.Y = (float)(j - borderSize) * MAP_XY_FACTOR;
			for (Int i = startX; i <= endX; i++)
			{
				hmapVertex.X = (float)(i - borderSize) * MAP_XY_FACTOR;
				hmapVertex.Z = (float)hmap->getHeight(i, j) * MAP_HEIGHT_SCALE + 0.01f * MAP_XY_FACTOR;
				decalVertex[0] = hmapVertex - decalPos[0];
				decalVertex[1] = hmapVertex - decalPos[1];
				pvVertices->x = hmapVertex.X;
				pvVertices->y = hmapVertex.Y;
				pvVertices->z = hmapVertex.Z;
				pvVertices->diffuse = diffuse;
				pvVertices->u0 = Vector3::Dot_Product(uVector[0], decalVertex[0]) + uOffset[0];
				pvVertices->v0 = Vector3::Dot_Product(vVector[0], decalVertex[0]) + vOffset[0];
				pvVertices->u1 = Vector3::Dot_Product(uVector[1], decalVertex[1]) + uOffset[1];
				pvVertices->v1 = Vector3::Dot_Product(vVector[1], decalVertex[1]) + vOffset[1];
				pvVertices++;
			}
		}
	}

	Int rowStart, j;
	for (j = startY, rowStart = 0; j < endY; j++, rowStart += vertsPerRow)
	{
		for (Int i = rowStart, k = startX; k < endX; i++, k++)
		{
			if (((const Gen_0074B410 *)hmap)->bfmeBitA(k, j))
			{
				pvIndices[0] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[1] = i + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[2] = i + m_numDecalVertsInBatch;
				pvIndices[3] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[4] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[5] = i + vertsPerRow + m_numDecalVertsInBatch;
			}
			else
			{
				pvIndices[0] = i + m_numDecalVertsInBatch;
				pvIndices[1] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[2] = i + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[3] = i + m_numDecalVertsInBatch;
				pvIndices[4] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[5] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
			}
			pvIndices += 6;
		}
	}
	}

	m_numDecalPolysInBatch += (endX - startX) * (endY - startY) * 2;
	m_numDecalVertsInBuffer += numVerts;
	m_numDecalVertsInBatch += numVerts;
	m_numDecalIndicesInBuffer += numIndex;
}
class Rva000421C8 {
public:
 Rva000421C8():m_next(0) {}
 virtual ~Rva000421C8() {}
 virtual bool allow(Object*)=0;
 virtual int getPlayerMask();
 Rva000421C8* link(Rva000421C8*);
 Rva000421C8* m_next;
};
struct Rva00045411BitSet { unsigned m_bits[7]; Rva00045411BitSet(int,int); };
class BfmeFixedStorage0004543D {
public: BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&) throw();
private: unsigned char bytes[28];
};
class Rva0004584D:public Rva000421C8 {
public:
 Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&) throw();
 virtual bool allow(Object*);
 BfmeFixedStorage0004543D m08,m24;
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
extern PartitionManager* ThePartitionManager;

// ---- single projected decal: W3DProjectedShadowManager 0x10C841 ----
struct BridgeInfoView10C841
{
	char m_pad00[0x6c];
	Vector3 m_corners[4];				// bridge +0x78
	unsigned short m_polys[2][3];		// bridge +0xA8
};
class BridgeView10C841
{
public:
	BridgeInfoView10C841 *getBridgeInfo() { return &m_info; }
	BridgeView10C841 *getNext() { return m_next; }
	void *m_vtbl;
	BridgeView10C841 *m_next;			// +0x04
	int m_pad08;
	BridgeInfoView10C841 m_info;		// +0x0C
};
class Rva00281BF7 { public: int rva00281BF7(); };
class Rva0055A88BDwordField { public: int get() const; };
class Rva000FE9E3PointBounds { public: Rva000FE9E3PointBounds *rva000FE9E3(Vector3 *points, int count); float m_box[6]; };
class AABoxClass { public: WWINLINE AABoxClass(const Vector3 &center, const Vector3 &extent) : Center(center), Extent(extent) {} Vector3 Center; Vector3 Extent; };
class CollisionMath { public: enum OverlapType { POS = 1 }; static OverlapType Overlap_Test(const AABoxClass &a, const AABoxClass &b); };
#include "../../../../../GameEngine/Source/Common/Thing/thing.h"
class PartitionObjectView10C841 : public Thing {};
float Rva000930C0(float x, float y);

// Retail's Coord3D is copy-constructed member-wise (user copy constructor) with
// header-inline sub/lengthSqr; this unit keeps the canonical POD Coord3D for its
// other bodies, so the scan delta uses an equivalent local value type.
struct ScanDelta10C841
{
	Real x, y, z;
	ScanDelta10C841(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
	Real lengthSqr() const { return x * x + y * y + z * z; }
};

struct ShadowGridOverlay10C841 { char m_pad[0x3c]; Real m_cellSize; };
class TerrainResourceManager { public: void rva0035A61F(UnsignedInt *diffuse, Int x, Int y, Int playerIndex); };
class GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicView10C841 { char m_pad[0x170]; TerrainResourceManager *m_terrainResources; };
struct PlayerView10C841 { char m_pad[0x54]; Int m_playerIndex; Int getPlayerIndex() const { return m_playerIndex; } };
class PlayerList;
extern PlayerList *ThePlayerList;
struct PlayerListView10C841 { char m_pad[0x10]; PlayerView10C841 *m_local; PlayerView10C841 *getLocalPlayer() { return m_local; } };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView10C841 { char m_pad[0x9a7]; Bool m_shadowAlphaOverride; Real m_shadowAlpha; };

struct MeshShareView10C841 { char m_pad[0xc]; void *m_array; };
struct MeshModelView10C841
{
	char m_pad00[0x24];
	Int m_polyCount;					// +0x24
	Int m_vertexCount;					// +0x28
	MeshShareView10C841 *m_poly;		// +0x2C
	MeshShareView10C841 *m_vertex;		// +0x30
	Vector3 *Get_Vertex_Array() { return (Vector3 *)m_vertex->m_array; }
	unsigned short *get_polys() { return (unsigned short *)m_poly->m_array; }
};
struct MeshView10C841 { char m_pad[0xc4]; MeshModelView10C841 *m_model; };

class GameClient
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual Drawable *findDrawableByID(Int id);	// +0x40
};
extern GameClient *TheGameClient;

struct ShadowRenderEntry10DF33
{
	char m_pad00[8];
	Coord3D m_position;					// +0x08
	Coord3D m_normal;					// +0x14
	Real m_angle;						// +0x20
	Int m_pad24;
	UnsignedInt m_diffuse;				// +0x28
	char m_pad2c[4];
	Bool m_isRotating;					// +0x30
	char m_pad31[3];
	ShadowType m_type;					// +0x34
	char m_pad38[0x20];
	Real m_decalSizeX;					// +0x58
	Real m_decalSizeY;					// +0x5C
	Real m_maxHeight;					// +0x60
	Bool m_useTerrainHeight;			// +0x64
	char m_pad65[3];
	W3DShadowTexture *m_shadowTexture[2];	// +0x68
	RenderObjClass *m_robj;				// +0x70
	Int m_pad74;
	Real m_decalOffsetU;				// +0x78
	Real m_decalOffsetV;				// +0x7C
	char m_pad80[8];
	Coord3D m_lastScanPosition;			// +0x88
	Int m_casterDrawableID[16];			// +0x94
	BridgeView10C841 *m_casterBridge[16];	// +0xD4
};

// Single projected decal (native 0x10C841..0x10DA71, RET 0xC, EH); WB 0x8C9A10 is the shape guide.
// The caller W3DProjectedShadowRenderShadows.cpp proves receiver and arguments; the name is address-derived.
void W3DProjectedShadowManager::rva0010C841(ShadowRenderEntry10DF33 *shadow, Int unused, Int flushFlags)
{
	Matrix3D objXform(true);
	Vector3 objPos;
	Vector3 normal;
	Real height = 0.0f;
	RenderObjClass *robj = shadow->m_robj;
	ShadowType type;

	if (shadow->m_decalSizeX == 0.0f || shadow->m_decalSizeY == 0.0f)
		return;

	if (robj)
	{
		objPos = robj->Get_Position();
		if (shadow->m_isRotating)
		{
			robj->Validate_Transform();
			objXform = robj->transform;
		}
		height = objPos.Z;
		type = shadow->m_type;
	}
	else
	{
		//no render object so use shadow's local position and default orientation
		objPos.Set(shadow->m_position.x, shadow->m_position.y, shadow->m_position.z);
		if (shadow->m_isRotating)
			objXform.Rotate_Z(shadow->m_angle);
		normal.Set(shadow->m_normal.x, shadow->m_normal.y, shadow->m_normal.z);
		height = shadow->m_position.z;
		type = shadow->m_type;
	}

	switch (type)
	{
		case 0x2000:
		{
			ShadowGridOverlay10C841 *grid = (ShadowGridOverlay10C841 *)((GameLogicView10C841 *)TheGameLogic)->m_terrainResources;
			if (grid)
			{
				Real cellSize = grid->m_cellSize;
				objPos.X -= Rva000930C0(objPos.X, cellSize);
				objPos.Y -= Rva000930C0(objPos.Y, cellSize);
			}
			break;
		}
	}

	Real terrainHeight = 0.0f;
	Real bridgeHeight = -100.0f;
	if (TheTerrainLogic)
	{
		terrainHeight = TheTerrainLogic->getLayerHeight(objPos.X, objPos.Y, 1, NULL, true);
		BridgeView10C841 *bridge = TheTerrainLogic->findBridgeAt(objPos.X, objPos.Y, 0.0f);
		if (bridge)
			bridgeHeight = TheTerrainLogic->getBridgeHeight(bridge) + 1.0f;
		terrainHeight = std::max(terrainHeight, bridgeHeight);
	}

	Bool useTerrainHeight = false;
	if (shadow->m_useTerrainHeight)
	{
		useTerrainHeight = true;
		objPos.Z = terrainHeight;
		height = terrainHeight;
	}

	//Find size of heightmap sub-rectangle affected by shadow
	//If user supplied size values, ignore bounding box
	Vector3 uVector, vVector;
	decalAxesRva00108E7A(*(Rva00108E7AMatrix *)&objXform, *(Rva00108E7AVector *)&uVector, *(Rva00108E7AVector *)&vVector);

	Rva00108E33Pair xRange;
	Rva00108E33Pair yRange;
	projectRangesRva00108FBD(*(Rva00108E7AVector *)&uVector, *(Rva00108E7AVector *)&vVector, shadow->m_decalSizeX, shadow->m_decalSizeY,
		shadow->m_decalOffsetU, shadow->m_decalOffsetV, xRange, yRange);
	xRange.X += objPos.X;
	xRange.Y += objPos.X;
	yRange.X += objPos.Y;
	yRange.Y += objPos.Y;

	if (shadow->m_decalSizeX == 0.0f)
		uVector.X = uVector.Y = uVector.Z = 0.0f;
	else
		uVector /= shadow->m_decalSizeX;
	if (shadow->m_decalSizeY == 0.0f)
		vVector.X = vVector.Y = vVector.Z = 0.0f;
	else
		vVector /= shadow->m_decalSizeY;

	Real uOffset = shadow->m_decalOffsetU + 0.5f;
	Real vOffset = shadow->m_decalOffsetV + 0.5f;
	UnsignedInt diffuse = shadow->m_diffuse;
	if (shadow->m_type == 0x1000 && ((GlobalDataView10C841 *)TheWritableGlobalData)->m_shadowAlphaOverride)
	{
		Int alpha = (Int)(((GlobalDataView10C841 *)TheWritableGlobalData)->m_shadowAlpha * 255.0f);
		alpha = alpha < 0 ? 0 : (alpha > 255 ? 255 : alpha);
		diffuse = (diffuse & 0xffffff) | (alpha << 24);
	}

	Coord3D pos;
	pos.x = objPos.X;
	pos.y = objPos.Y;
	pos.z = objPos.Z;

	if (!useTerrainHeight)
	{
		AABoxClass box(objPos, Vector3(shadow->m_decalSizeX, shadow->m_decalSizeY, shadow->m_maxHeight));
		ScanDelta10C841 delta(shadow->m_lastScanPosition);
		delta.sub(&pos);
		if (flushFlags == 0 && ThePartitionManager && delta.lengthSqr() > 50.0f * 50.0f)
		{
			Real radius = sqrtf(shadow->m_decalSizeY * shadow->m_decalSizeY + shadow->m_decalSizeX * shadow->m_decalSizeX) + 50.0f;
			BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(&pos, radius, 1,
				&Rva0004584D((const BfmeFixedStorage0004543D &)Rva00045411BitSet(0, 0x3c), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE), 0);
			Int count;
			for (count = 0; count < 16; count++)
			{
				Object *obj = iter.next();
				if (!obj)
					break;
				shadow->m_casterDrawableID[count] = ((Rva0055A88BDwordField *)((PartitionObjectView10C841 *)obj)->getDrawable())->get();
				shadow->m_casterBridge[count] = NULL;
			}
			for (BridgeView10C841 *bridge = TheTerrainLogic->getFirstBridge(); count < 16 && bridge; bridge = bridge->getNext())
			{
				BridgeInfoView10C841 *info = bridge->getBridgeInfo();
				if (info)
				{
					Rva000FE9E3PointBounds bounds;
					bounds.rva000FE9E3(info->m_corners, 4);
					if (CollisionMath::Overlap_Test(box, *(AABoxClass *)&bounds) != CollisionMath::POS && ((Rva00281BF7 *)bridge)->rva00281BF7())
					{
						shadow->m_casterDrawableID[count] = ((Rva0055A88BDwordField *)((Rva00281BF7 *)bridge)->rva00281BF7())->get();
						shadow->m_casterBridge[count] = bridge;
						count++;
					}
				}
			}
			if (count < 16)
				shadow->m_casterDrawableID[count] = 0;
			shadow->m_lastScanPosition = pos;
		}

		for (Int caster = 0; caster < 16; caster++)
		{
			Int id = shadow->m_casterDrawableID[caster];
			if (!id)
				break;
			Drawable *draw = TheGameClient->findDrawableByID(id);
			if (!draw)
				continue;
			BridgeView10C841 *bridge = shadow->m_casterBridge[caster];
			for (Int part = 0; part < 4; part++)
			{
				RenderObjClass *casterObj = NULL;
				MeshModelView10C841 *model = NULL;
				Int numVerts = 0;
				Int numPolys = 0;
				Int numIndex = 0;
				if (bridge)
				{
					if (part != 0)
						break;
					numVerts = 4;
					numPolys = 2;
					numIndex = numPolys * 3;
				}
				else
				{
					if (part == 0)
						draw->rva0027267D(0, 0, (Int)&casterObj, 0);
					else if (part == 1)
						draw->rva002726C3(0, 0, (Int)&casterObj, 0);
					else if (part == 2)
						casterObj = (RenderObjClass *)draw->rva0027261D();
					else
						casterObj = (RenderObjClass *)draw->rva0027264D();
					if (!casterObj)
						continue;
					if (CollisionMath::Overlap_Test(box, casterObj->Get_Bounding_Box()) == CollisionMath::POS)
					{
						if (casterObj)
						{
							casterObj->Release_Ref();
							casterObj = NULL;
						}
						continue;
					}
					model = ((MeshView10C841 *)casterObj)->m_model;
					numVerts = model->m_vertexCount;
					numPolys = model->m_polyCount;
					numIndex = numPolys * 3;
				}

				Bool flushed = false;
				if (m_numDecalVertsInBuffer + numVerts > 0x8000 || m_numDecalIndicesInBuffer + numIndex > 0x10000) //check if room for model verts
				{
					//flush the buffer by drawing the contents and re-locking again
					flushDecals(shadow->m_type, shadow->m_shadowTexture[0], shadow->m_shadowTexture[1], flushFlags);
					m_decalStartVertex = 0;
					m_decalStartIndex = 0;
					m_numDecalPolysInBatch = 0; //reset number of polys in texture batch
					m_numDecalVertsInBatch = 0;
					m_numDecalVertsInBuffer = 0;
					m_numDecalIndicesInBuffer = 0;
					flushed = true;
				}

				{
				VertexBufferClass::AppendLockClass lockVtxBuffer(m_dynamicDecalVertexBuffer, m_numDecalVertsInBuffer, numVerts, flushed ? 0x2000 : 0x1000);
				SHADOW_DECAL_DUAL_VERTEX *pvVertices = (SHADOW_DECAL_DUAL_VERTEX *)lockVtxBuffer.Get_Vertex_Array();
				if (!pvVertices)
				{
					if (!bridge && casterObj)
					{
						casterObj->Release_Ref();
						casterObj = NULL;
					}
					return;
				}
				IndexBufferClass::AppendLockClass lockIdxBuffer(m_dynamicDecalIndexBuffer, m_numDecalIndicesInBuffer, numIndex, flushed ? 0x2000 : 0x1000);
				UnsignedShort *pvIndices = lockIdxBuffer.Get_Index_Array();
				if (!pvIndices)
				{
					if (!bridge && casterObj)
					{
						casterObj->Release_Ref();
						casterObj = NULL;
					}
					return;
				}

				Vector3 vertex;
				Vector3 decalVertex;
				if (pvVertices)
				{
					Vector3 *src;
					if (bridge)
						src = bridge->getBridgeInfo()->m_corners;
					else
						src = model->Get_Vertex_Array();
					for (Int v = 0; v < numVerts; v++, src++)
					{
						if (bridge)
							vertex = *src;
						else
						{
							const Vector3 &sourceVertex = *src;
							const Matrix3D &transform = casterObj->Get_Transform();
							Vector3 tmp;
							const Vector3 *v;
							if (&vertex == &sourceVertex) { tmp = sourceVertex; v = &tmp; } else v = &sourceVertex;
							vertex.X = (transform[0][0] * v->X + transform[0][1] * v->Y + transform[0][2] * v->Z + transform[0][3]);
							vertex.Y = (transform[1][0] * v->X + transform[1][1] * v->Y + transform[1][2] * v->Z + transform[1][3]);
							vertex.Z = (transform[2][0] * v->X + transform[2][1] * v->Y + transform[2][2] * v->Z + transform[2][3]);
						}
						vertex.Z += 0.0f;
						decalVertex = vertex - objPos;
						pvVertices->x = vertex.X;
						pvVertices->y = vertex.Y;
						pvVertices->z = vertex.Z;
						pvVertices->diffuse = diffuse;
						pvVertices->u0 = Vector3::Dot_Product(uVector, decalVertex) + uOffset;
						pvVertices->v0 = Vector3::Dot_Product(vVector, decalVertex) + vOffset;
						pvVertices->u1 = 0.0f;
						pvVertices->v1 = 0.0f;
						pvVertices++;
					}
				}
				if (pvIndices)
				{
					unsigned short *srcIndex;
					if (bridge)
						srcIndex = &bridge->getBridgeInfo()->m_polys[0][0];
					else
						srcIndex = model->get_polys();
					for (Int p = 0; p < numPolys; p++, srcIndex += 3)
					{
						pvIndices[0] = srcIndex[0] + m_numDecalVertsInBatch;
						pvIndices[1] = srcIndex[1] + m_numDecalVertsInBatch;
						pvIndices[2] = srcIndex[2] + m_numDecalVertsInBatch;
						pvIndices += 3;
					}
				}
				}
				m_numDecalPolysInBatch += numPolys;
				m_numDecalIndicesInBuffer += numIndex;
				m_numDecalVertsInBuffer += numVerts;
				m_numDecalVertsInBatch += numVerts;
				if (casterObj)
				{
					casterObj->Release_Ref();
					casterObj = NULL;
				}
			}
		}
	}

	if (!useTerrainHeight && !(pos.z - terrainHeight < shadow->m_maxHeight))
		return;

	objPos.Z = 0.0f; //we don't care about object height since shadows project top-down
	height = 0.0f;

	Real mapScaleInv = 1.0f / MAP_XY_FACTOR;
	WorldHeightMap *hmap = TheTerrainRenderObject->m_map;
	Int borderSize = hmap->m_borderSize;

	//Get terrain cell index for area with shadow
	Int startX = REAL_TO_INT_FLOOR(xRange.X * mapScaleInv) + borderSize;
	Int endX = REAL_TO_INT_CEIL(xRange.Y * mapScaleInv) + borderSize;
	Int startY = REAL_TO_INT_FLOOR(yRange.X * mapScaleInv) + borderSize;
	Int endY = REAL_TO_INT_CEIL(yRange.Y * mapScaleInv) + borderSize;

	startX = __max(startX, drawStartX);
	startX = __min(startX, drawEdgeX);
	startY = __max(startY, drawStartY);
	startY = __min(startY, drawEdgeY);

	endX = __max(endX, drawStartX);
	endX = __min(endX, drawEdgeX);
	endY = __max(endY, drawStartY);
	endY = __min(endY, drawEdgeY);

	//Check if decal too large to fit inside 65536 index buffer.
	//try clipping each direction to < 104 since that's more than
	//enough to cover typical map.
	Int numExtraX = (endX - startX + 1) - 104;
	if (numExtraX > 0)
	{	//figure out how much to clip out at each edge of decal
		Int numStartExtraX = REAL_TO_INT_FLOOR((float)numExtraX / 2.0f);
		Int numEdgeExtraX = numExtraX - numStartExtraX;
		startX += numStartExtraX;
		endX -= numEdgeExtraX;
	}
	Int numExtraY = (endY - startY + 1) - 104;
	if (numExtraY > 0)
	{
		Int numStartExtraY = REAL_TO_INT_FLOOR((float)numExtraY / 2.0f);
		Int numEdgeExtraY = numExtraY - numStartExtraY;
		startY += numStartExtraY;
		endY -= numEdgeExtraY;
	}

	Int vertsPerRow = endX - startX + 1; //number of cells +1
	Int vertsPerColumn = endY - startY + 1; //number of cells +1
	if (vertsPerRow <= 1)
		return; //nothing to render
	if (vertsPerColumn <= 1)
		return;

	Int numVerts = vertsPerRow * vertsPerColumn; //number of terrain vertices
	Int numPolys = (endX - startX) * (endY - startY) * 2;
	Int numIndex = numPolys * 3; //6 indices per terrain cell (2 triangles).

	Bool flushed = false;
	if (m_numDecalVertsInBuffer + numVerts > 0x8000 || m_numDecalIndicesInBuffer + numIndex > 0x10000) //check if room for model verts
	{
		//flush the buffer by drawing the contents and re-locking again
		flushDecals(shadow->m_type, shadow->m_shadowTexture[0], shadow->m_shadowTexture[1], flushFlags);
		m_decalStartVertex = 0;
		m_decalStartIndex = 0;
		m_numDecalPolysInBatch = 0; //reset number of polys in texture batch
		m_numDecalVertsInBatch = 0;
		m_numDecalVertsInBuffer = 0;
		m_numDecalIndicesInBuffer = 0;
		flushed = true;
	}

	{
	VertexBufferClass::AppendLockClass lockVtxBuffer(m_dynamicDecalVertexBuffer, m_numDecalVertsInBuffer, numVerts, flushed ? 0x2000 : 0x1000);
	SHADOW_DECAL_DUAL_VERTEX *pvVertices = (SHADOW_DECAL_DUAL_VERTEX *)lockVtxBuffer.Get_Vertex_Array();
	if (!pvVertices)
		return;
	IndexBufferClass::AppendLockClass lockIdxBuffer(m_dynamicDecalIndexBuffer, m_numDecalIndicesInBuffer, numIndex, flushed ? 0x2000 : 0x1000);
	UnsignedShort *pvIndices = lockIdxBuffer.Get_Index_Array();
	if (!pvIndices)
		return;

	Vector3 hmapVertex;
	Vector3 decalVertex;
	SHADOW_DECAL_DUAL_VERTEX *firstVertex = pvVertices;
	//insert each cell's bottom/left edge vertex
	for (Int j = startY; j <= endY; j++)
	{
		hmapVertex.Y = (float)(j - borderSize) * MAP_XY_FACTOR;
		for (Int i = startX; i <= endX; i++)
		{
			hmapVertex.X = (float)(i - borderSize) * MAP_XY_FACTOR;
			Real terrainZ = (float)hmap->getHeight(i, j) * MAP_HEIGHT_SCALE;
			hmapVertex.Z = std::max(terrainZ, bridgeHeight);
			decalVertex = hmapVertex - objPos;
			pvVertices->x = hmapVertex.X;
			pvVertices->y = hmapVertex.Y;
			pvVertices->z = hmapVertex.Z;
			pvVertices->diffuse = diffuse;
			pvVertices->u0 = Vector3::Dot_Product(uVector, decalVertex) + uOffset;
			pvVertices->v0 = Vector3::Dot_Product(vVector, decalVertex) + vOffset;
			pvVertices->u1 = 0.0f;
			pvVertices->v1 = 0.0f;
			pvVertices++;
		}
	}

	if (shadow->m_type == 0x2000)
	{
		TerrainResourceManager *resources = ((GameLogicView10C841 *)TheGameLogic)->m_terrainResources;
		if (resources)
		{
			Int playerIndex = -1;
			PlayerView10C841 *player = ((PlayerListView10C841 *)ThePlayerList)->getLocalPlayer();
			if (player)
				playerIndex = player->getPlayerIndex();
			pvVertices = firstVertex;
			for (Int j = startY; j <= endY; j++)
			{
				for (Int i = startX; i <= endX; i++)
				{
					resources->rva0035A61F(&pvVertices->diffuse, i - borderSize, j - borderSize, playerIndex);
					pvVertices++;
				}
			}
		}
	}

	//fill each cell's vertex indices
	Int rowStart, j;
	for (j = startY, rowStart = 0; j < endY; j++, rowStart += vertsPerRow)
	{
		for (Int i = rowStart, k = startX; k < endX; i++, k++)
		{
			///@todo: fix the winding order in heightmap to be in strip order like above!
			if (((const Gen_0074B410 *)hmap)->bfmeBitA(k, j))
			{
				pvIndices[0] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[1] = i + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[2] = i + m_numDecalVertsInBatch;
				pvIndices[3] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[4] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[5] = i + vertsPerRow + m_numDecalVertsInBatch;
			}
			else
			{
				pvIndices[0] = i + m_numDecalVertsInBatch;
				pvIndices[1] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[2] = i + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[3] = i + m_numDecalVertsInBatch;
				pvIndices[4] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[5] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
			}
			pvIndices += 6;
		}
	}
	}

	m_numDecalPolysInBatch += numPolys;
	m_numDecalVertsInBuffer += numVerts;
	m_numDecalVertsInBatch += numVerts;
	m_numDecalIndicesInBuffer += numIndex;
}
