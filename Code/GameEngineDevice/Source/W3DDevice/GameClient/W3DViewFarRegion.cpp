// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Target boundary: 0x00085CBD..0x00085EC7; 522 bytes; RET 4.
// Owner evidence: follows W3DView::getAxisAlignedViewRegion at 0x00085B41;
// camera at +0x104 calls the owned Update_Frustum at 0x001340B0 and virtual
// Validate_Transform at slot 0x50; translation reads at +0x24/+0x34/+0x44.
// Target accesses establish far corners 4..7 and min/max in Frustum at +0x100.
// Layout here records those accessed prefixes; the method name remains unknown.
// Semantic guide: BFME1 game/GameEngineDevice/Source/W3DDevice/GameClient/
// Rva0073B290ViewGetRegion.cpp reviewed at 575ba2b04743f190f069805fbdc59936123c45da.
// The earlier bank did not record its historical donor revision. Target bytes
// separately establish plane projection and 75 / 999999 bounds expansion.
// Volatile access to initialized slopeY preserves retail's four SSE bounds;
// declaring the inner counter before slopeY preserves the XOR/store order.
#include "Coord3D.h"

typedef float Real;
typedef int Int;

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

struct Vector3
{
	Vector3() {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real X;
	Real Y;
	Real Z;
};

struct Matrix3D
{
	Vector3 Get_Translation() const { return Vector3(Row[0][3], Row[1][3], Row[2][3]); }
	Real Row[3][4];
};

struct FrustumClass
{
	Matrix3D CameraTransform;
	Real Planes[6][4];
	Vector3 Corners[8];
	Vector3 BoundMin;
	Vector3 BoundMax;
};

struct W3DViewTerrainLogic
{
	virtual void terrainSlot00() = 0;
	virtual void terrainSlot04() = 0;
	virtual void terrainSlot08() = 0;
	virtual void terrainSlot0C() = 0;
	virtual void terrainSlot10() = 0;
	virtual void terrainSlot14() = 0;
	virtual void terrainSlot18() = 0;
	virtual void terrainSlot1C() = 0;
	virtual void getExtent(Region3D *region) = 0;
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

static const Real DRAWABLE_OVERSCAN = 75.0f;
static const Real MAP_Z_SAFE = 999999.0f;

class CameraClass
{
public:
	virtual void cameraSlot00() = 0;
	virtual void cameraSlot04() = 0;
	virtual void cameraSlot08() = 0;
	virtual void cameraSlot0C() = 0;
	virtual void cameraSlot10() = 0;
	virtual void cameraSlot14() = 0;
	virtual void cameraSlot18() = 0;
	virtual void cameraSlot1C() = 0;
	virtual void cameraSlot20() = 0;
	virtual void cameraSlot24() = 0;
	virtual void cameraSlot28() = 0;
	virtual void cameraSlot2C() = 0;
	virtual void cameraSlot30() = 0;
	virtual void cameraSlot34() = 0;
	virtual void cameraSlot38() = 0;
	virtual void cameraSlot3C() = 0;
	virtual void cameraSlot40() = 0;
	virtual void cameraSlot44() = 0;
	virtual void cameraSlot48() = 0;
	virtual void cameraSlot4C() = 0;
	virtual void Validate_Transform() = 0;	// slot 0x50
	__forceinline Vector3 Get_Position() { Validate_Transform(); return Transform.Get_Translation(); }
protected:
	void Update_Frustum() const;
	friend class W3DView;
public:
	unsigned char m_camHead[0x14];
	Matrix3D Transform;						// +0x18
	unsigned char m_camMid[0x100 - 0x48];
	FrustumClass Frustum;					// +0x100
};

class W3DView
{
public:
	void rva00085CBD(Region3D &region);
private:
	unsigned char m_viewHead[0x104];
	CameraClass *m_3DCamera;				// +0x104
};

struct Rva00085CBDFrame
{
	Region3D mapExtent;
	Coord3D pt;
};

void W3DView::rva00085CBD(Region3D &region)
{
	Rva00085CBDFrame L;
	((W3DViewTerrainLogic *)TheTerrainLogic)->getExtent(&L.mapExtent);
	CameraClass *camera = m_3DCamera;
	camera->Update_Frustum();
	Vector3 camPos = m_3DCamera->Get_Position();
	if (camPos.Z > camera->Frustum.BoundMax.Z)
	{
		Real loX = 0.0f;
		Real loY = 0.0f;
		L.pt.z = -1.0f;
		Real hiX = 0.0f;
		Real hiY = 0.0f;
		for (Int i = 0; i < 4; i++)
		{
			const Vector3 &corner = camera->Frustum.Corners[4 + i];
			Int j = 0;
			Real slopeY = (corner.Y - camPos.Y) / (corner.Z - camPos.Z);
			for (; j < 2; j++)
			{
				Real planeZ = (j == 0) ? L.mapExtent.lo.z : L.mapExtent.hi.z;
				if (planeZ > camPos.Z)
					planeZ = camPos.Z - 1.0f;
				Real dz = planeZ - camPos.Z;
				Real px = (corner.X - camPos.X) / (corner.Z - camPos.Z) * dz + camPos.X;
				Real py = *(volatile const float*)&slopeY * dz + camPos.Y;
				if (L.pt.z < 0.0f)
				{
					loX = hiX = px;
					loY = hiY = py;
					L.pt.z = 0.0f;
				}
				else
				{
					if (px < loX)
						loX = px;
					if (px > hiX)
						hiX = px;
					if (py < loY)
						loY = py;
					if (py > hiY)
						hiY = py;
				}
			}
		}
		region.lo.x = loX - DRAWABLE_OVERSCAN;
		region.lo.y = loY - DRAWABLE_OVERSCAN;
		region.lo.z = L.mapExtent.lo.z - MAP_Z_SAFE;
		region.hi.x = hiX + DRAWABLE_OVERSCAN;
		region.hi.y = hiY + DRAWABLE_OVERSCAN;
		region.hi.z = L.mapExtent.hi.z + MAP_Z_SAFE;
	}
	else
	{
		region.lo.x = camera->Frustum.BoundMin.X - DRAWABLE_OVERSCAN;
		region.lo.y = camera->Frustum.BoundMin.Y - DRAWABLE_OVERSCAN;
		region.lo.z = L.mapExtent.lo.z - MAP_Z_SAFE;
		region.hi.x = camera->Frustum.BoundMax.X + DRAWABLE_OVERSCAN;
		region.hi.y = camera->Frustum.BoundMax.Y + DRAWABLE_OVERSCAN;
		region.hi.z = L.mapExtent.hi.z + MAP_Z_SAFE;
	}
}
