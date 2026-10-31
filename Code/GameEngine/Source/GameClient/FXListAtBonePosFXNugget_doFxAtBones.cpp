// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX

enum { MAX_BONE_POINTS = 40 };

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"

// POD so world-space output does not emit a per-iteration ctor
struct WorldPos
{
	float x;
	float y;
	float z;
};

#include "../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../Common/Thing/thing.h"

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
	friend void bfmeAnchorFXListAtBonePosDoFxAtBones(const FXListAtBonePosFXNugget *, const Object *, int);

private:
	const FXList *m_fx;
	AsciiString m_boneName;
};

struct WorldMtx
{
	float m[12];
};

// ?doFxAtBones@FXListAtBonePosFXNugget@@IBEXPBVObject@@H@Z
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void FXListAtBonePosFXNugget::doFxAtBones(const Object *obj, int startIndex) const
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

// ?bfmeAnchorFXListAtBonePosDoFxAtBones absent-from-retail
void bfmeAnchorFXListAtBonePosDoFxAtBones(const FXListAtBonePosFXNugget *fXListAtBonePosFXNugget, const Object *obj, int startIndex)
{
	fXListAtBonePosFXNugget->doFxAtBones(obj, startIndex);
}

