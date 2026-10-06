// cl: /DNDEBUG /MD /EHsc
// ?getSingleLogicalBonePosition@Object@@QBE_NPBDPAUCoord3D@@PAVMatrix3D@@@Z @0x0028BEE0
// (161B): Object::getSingleLogicalBonePosition, BFME1 Object.cpp verbatim
// (Object::getSingleLogicalBonePosition) with BFME2 offsets. Drawable query is
// the rowed 6-arg getPristineBonePositions at 0x0027274D (startIndex 0 maxBones
// 1 extra 0) and the world conversion is the pinned Thing at 0x0030A528.
// Fallback copies position at +0x38 (12B) and transform at +0x08 (48B) and
// returns false. Callers include 0x002CAB27 0x00463695 0x0044FBB2.

struct Coord3D
{
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
