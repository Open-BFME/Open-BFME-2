// ?IsEndPortalAboveWall@DynamicPortalBehaviour@@QAE_NPAUCoord3D@@@Z
// partial score=0.8102923538230884 date=2026-10-10
// ?IsEndPortalAboveWall@DynamicPortalBehaviour@@QAE_NPAUCoord3D@@@Z
// cl: /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE /I.
// ?getSingleLogicalBonePosition@Object@@QBE_NPBDPAUCoord3D@@PAVMatrix3D@@@Z @0x0028BEE0
// (161B): Object::getSingleLogicalBonePosition, BFME1 Object.cpp verbatim
// (Object::getSingleLogicalBonePosition) with BFME2 offsets. Drawable query is
// the rowed 6-arg getPristineBonePositions at 0x0027274D (startIndex 0 maxBones
// 1 extra 0) and the world conversion is the pinned Thing at 0x0030A528.
// Fallback copies position at +0x38 (12B) and transform at +0x08 (48B) and
// returns false. Callers include 0x002CAB27 0x00463695 0x0044FBB2.

struct Coord3D
{
 Coord3D();
 ~Coord3D();
	float x;
	float y;
	float z;
};

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;
	Vector4() {}
	__forceinline Vector4(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
};

class Matrix3D
{
public:
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}
	Vector4 Row[3];
};

class Thing
{
public:
	void convertBonePosToWorldPos(const Coord3D *bonePos, const Matrix3D *boneTransform,
		Coord3D *worldPos, Matrix3D *worldTransform) const;
	__forceinline const Coord3D *getPosition() const { return &m_cachedPos; }
	__forceinline const Matrix3D *getTransformMatrix() const { return &m_transform; }

private:
	unsigned char m_pad00[8];
	Matrix3D m_transform; // +0x08
	Coord3D m_cachedPos; // +0x38
	unsigned char m_pad44[0x84 - 0x44];
};

class Drawable : public Thing
{
public:
	int getPristineBonePositions(const char *boneNamePrefix, int startIndex,
		Coord3D *positions, Matrix3D *transforms, int maxBones, int extra) const;
};

class Object : public Thing
{
public:
	bool getSingleLogicalBonePosition(const char *boneName, Coord3D *position, Matrix3D *transform) const;
	int getMultiLogicalBonePosition(const char *boneNamePrefix, int maxBones,
		Coord3D *positions, Matrix3D *transforms, bool convertToWorld, int extra) const;

private:
	Drawable *m_drawable; // +0x84
};

bool Object::getSingleLogicalBonePosition(const char *boneName, Coord3D *position, Matrix3D *transform) const
{
	if (m_drawable &&
		m_drawable->getPristineBonePositions(boneName, 0, position, transform, 1, 0) == 1)
	{
		m_drawable->convertBonePosToWorldPos(position, transform, position, transform);
		return true;
	}
	else
	{
		if (position)
			*position = *getPosition();
		if (transform)
			*transform = *getTransformMatrix();
		return false;
	}
}

int Object::getMultiLogicalBonePosition(const char *boneNamePrefix, int maxBones,
	Coord3D *positions, Matrix3D *transforms, bool convertToWorld, int extra) const
{
	int count;
	if (m_drawable &&
		(count = m_drawable->getPristineBonePositions(boneNamePrefix, 1, positions, transforms, maxBones, extra)) > 0)
	{
		if (convertToWorld)
		{
			for (int i = 0; i < count; ++i)
			{
				m_drawable->convertBonePosToWorldPos(
					positions ? &positions[i] : 0,
					transforms ? &transforms[i] : 0,
					positions ? &positions[i] : 0,
					transforms ? &transforms[i] : 0);
			}
		}
		return count;
	}
	return 0;
}

// WB10AD000 IsEndPortalAboveWall and native460DF6..460F18 RET4.
// Default coordinate callbacks are already rowed at47A6A9/B3FD0. Existing
// TU's coordinate view retains those declarations without a header-wide edit.
struct PortalQueryPoint {float x,y,z;__forceinline PortalQueryPoint(const Coord3D&r){x=r.x;y=r.y;z=r.z;}};
// stlport
#include <vector>
struct PortalWaypointDescriptor {int boneIndex,observed4;};
class DynamicPortalBehaviourModuleData {public:
 char pad0[0x118];int numberOfBones;const char *nameBuffer;
 std::vector<PortalWaypointDescriptor> waypoints;
 char pad12C[0x140-0x12C];int aboveWallIndex;
};
class Pathfinder {public:bool IsPointOnWall(int,bool);};
class AI;
extern AI *TheAI;
struct PortalAIView {char pad0[0x10];Pathfinder *pathfinder;};
class DynamicPortalBehaviour {public:
 bool IsEndPortalAboveWall(Coord3D *out);
 void *vptr;const DynamicPortalBehaviourModuleData *data;Object *object;
};
bool DynamicPortalBehaviour::IsEndPortalAboveWall(Coord3D *out)
{
 const DynamicPortalBehaviourModuleData *portalData=data;
 if(portalData->aboveWallIndex<0 || portalData->aboveWallIndex>=(int)portalData->waypoints.size()){
  if(out)*out=*object->getPosition();return true;
 }
 Coord3D bones[16];
 const char *buf=portalData->nameBuffer;Object *obj=object;
 obj->getMultiLogicalBonePosition(buf ? buf+8 : "", portalData->numberOfBones,bones,0,true,0);
 PortalQueryPoint selected(bones[portalData->waypoints[portalData->aboveWallIndex].boneIndex]);
 if(out)*out=*(const Coord3D*)&selected;
 return ((PortalAIView*)TheAI)->pathfinder->IsPointOnWall((int)&selected,false);
}
