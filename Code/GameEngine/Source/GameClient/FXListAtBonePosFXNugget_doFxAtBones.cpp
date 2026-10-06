// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX

enum { MAX_BONE_POINTS = 40 };

struct Coord3D
{
	Coord3D();
	~Coord3D();
	float x;
	float y;
	float z;
};

// POD so world-space output does not emit a per-iteration ctor
struct WorldPos
{
	float x;
	float y;
	float z;
};

class Vector4
{
public:
	Vector4();
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	Vector4 Row[3];
};

#include "ascii_string.h"

class FXList
{
public:
	bool rva001E2EF1() const;
	void doFXPos(const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *secondary) const;
};

class Drawable
{
public:
	int getCurrentClientBonePositions(const char *boneNamePrefix, int startIndex,
		Coord3D *positions, Matrix3D *transforms, int maxBones) const;
};

class Thing
{
public:
	void convertBonePosToWorldPos(const Coord3D *bonePos, const Matrix3D *boneTransform,
		Coord3D *worldPos, Matrix3D *worldTransform) const;
};

class Object : public Thing
{
public:
	Drawable *getDrawable() const;
};

class Rva001DFEAABase
{
public:
	virtual ~Rva001DFEAABase();
protected:
	unsigned char m_pad[0x148 - 4];
};

class FXListAtBonePosFXNugget : public Rva001DFEAABase
{
protected:
	void doFxAtBones(const Object *obj, int startIndex) const;

private:
	const FXList *m_fx;
	AsciiString m_boneName;
};

struct WorldMtx
{
	float m[12];
};

// ?doFxAtBones@FXListAtBonePosFXNugget@@IBEXPBVObject@@H@Z
void FXListAtBonePosFXNugget::doFxAtBones(const Object *obj, int startIndex) const
{
	Coord3D bonePositions[MAX_BONE_POINTS];
	Matrix3D boneTransforms[MAX_BONE_POINTS];

	Drawable *drawable = obj->getDrawable();
	if (drawable)
	{
		int boneCount = drawable->getCurrentClientBonePositions(m_boneName.str(), startIndex, bonePositions, boneTransforms, MAX_BONE_POINTS);
		for (int boneIndex = 0; boneIndex < boneCount; ++boneIndex)
		{
			WorldPos worldPosition;
			WorldMtx worldMtx;
			obj->convertBonePosToWorldPos(&bonePositions[boneIndex], &boneTransforms[boneIndex],
				reinterpret_cast<Coord3D *>(&worldPosition), reinterpret_cast<Matrix3D *>(&worldMtx));
			const FXList *fxList = m_fx;
			if (fxList && !fxList->rva001E2EF1())
				fxList->doFXPos(reinterpret_cast<const Coord3D *>(&worldPosition), reinterpret_cast<const Matrix3D *>(&worldMtx), 0.0f, 0);
		}
	}
}
