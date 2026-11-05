// cl: /DNDEBUG /MD /EHsc
// ?getSingleLogicalBonePosition@Object@@QBE_NPBDPAUCoord3D@@PAVMatrix3D@@@Z @0x0028BEE0
// (161B): Object::getSingleLogicalBonePosition, BFME1 Object.cpp verbatim
// (Object::getSingleLogicalBonePosition) with BFME2 offsets. Drawable query is
// the rowed 6-arg getPristineBonePositions at 0x0027274D (startIndex 0 maxBones
// 1 extra 0) and the world conversion is the pinned Thing at 0x0030A528.
// Fallback copies position at +0x38 (12B) and transform at +0x08 (48B) and
// returns false. Callers include 0x002CAB27 0x00463695 0x0044FBB2.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
// Preserve the original inline row-by-row assignment in this unit.
static __forceinline Matrix3D &copyLogicalBoneTransform(Matrix3D &out,const Matrix3D &in) {out.Row[0]=in.Row[0];out.Row[1]=in.Row[1];out.Row[2]=in.Row[2];return out;}



#include "../../Common/Thing/thing.h"
#include "../../../Include/GameClient/Drawable.h"


class Object : public Thing
{
public:
	bool getSingleLogicalBonePosition(const char *boneName, Coord3D *position, Matrix3D *transform) const;
	int getMultiLogicalBonePosition(const char *boneNamePrefix, int maxBones,
		Coord3D *positions, Matrix3D *transforms, bool convertToWorld, int extra) const;

private:
	unsigned char m_pad60[0x84 - 0x60];
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
			copyLogicalBoneTransform(*transform, *getTransformMatrix());
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
