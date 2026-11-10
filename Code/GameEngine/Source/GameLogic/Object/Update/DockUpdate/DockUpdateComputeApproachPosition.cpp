// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?computeApproachPosition@DockUpdate@@IAE?AUCoord3D@@HPAVObject@@@Z, retail
// 0x00589B7D (449 bytes, RET 0xC). Zero Hour's DockUpdate::computeApproachPosition
// (BFME 1 carries the same body in DockUpdateComputeApproachPositionBfme.cpp):
// load the dock positions on demand, convert the indexed pristine bone position
// (this+0x54 array of Coord3D, 12 bytes each) to the world through the owner
// (+0x08, Thing::convertBonePosToWorldPos 0x0030A528), and for a boneless
// building (+0x4C == 0) bias it by the owner's major radius (+0xB8) halved along
// the normalised direction to the caller (WB's Vector3 normalise: Inv_Sqrt
// 0x0004233A over a non-zero length). Then ask PartitionManager::findPositionAround
// (0x00285202; radius 0..100, a spot the caller can path to, the owner ignored
// for airborne callers) and return the spot found, else the working position.
// Called by the matched advanceApproachPosition 0x00589D3E.
#include "../../../../Common/PartitionRangeQueryCallView.h"

// Coord3D: retail user ctors, opt-in view (Lib/Coord3DCtorView.h); no private copy.
#include "../../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

class Matrix3D;
class Object;

#include "../../../../../../Libraries/Source/WWVegas/WWMath/WWMathClass.h"

#include "../../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	bool isUsingAirborneLocomotor() const; // 0x0028B81E
	float getMajorRadius() const { return m_majorRadius; }
private:
	unsigned char m_pad60[0xB8 - 0x60];
	float m_majorRadius; // +0xB8
};

struct FindPositionOptions
{
	int flags;
	float minRadius;
	float maxRadius;
	float startAngle;
	float maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
	FindPositionOptions()
	{
		flags = 0;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}
};

#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// Zero Hour's inline Vector3::Normalize body; retail inlines it here.
static __forceinline void bfmeNormalizeV3(Vector3 &vec)
{
	float len2 = vec.X * vec.X + vec.Y * vec.Y + vec.Z * vec.Z;
	if (len2 != 0.0f)
	{
		float oolen = WWMath::Inv_Sqrt(len2);
		vec.X *= oolen;
		vec.Y *= oolen;
		vec.Z *= oolen;
	}
}

__declspec(dllimport) __forceinline Vector3 operator*(const Vector3 &a, float k)
{
	return Vector3(a.X * k, a.Y * k, a.Z * k);
}

static __forceinline void copyCoord3D(Coord3D *dst, const Coord3D *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

static __forceinline Coord3D makeCoord3D(const Coord3D *src)
{
	Coord3D result;
	copyCoord3D(&result, src);
	return result;
}

class DockUpdate
{
protected:
	Coord3D computeApproachPosition(int positionIndex, Object *forWhom);
	void loadDockPositions(); // 0x005897FB
	Object *getObject() const { return m_object; }
private:
	unsigned char m_pad00[0x08];
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x4C - 0x0C];
	int m_numberApproachPositionBones; // +0x4C
	bool m_positionsLoaded; // +0x50
	unsigned char m_pad51[0x54 - 0x51];
	Coord3D *m_approachPositions; // +0x54, start of the position vector
};

// ?computeApproachPosition@DockUpdate@@IAE?AUCoord3D@@HPAVObject@@@Z @0x00589B7D
Coord3D DockUpdate::computeApproachPosition(int positionIndex, Object *forWhom)
{
	if (m_positionsLoaded == false)
		loadDockPositions();

	Coord3D bestPosition;
	Coord3D workingPosition;
	FindPositionOptions fpOptions;

	Object *us = getObject();
	us->convertBonePosToWorldPos(&m_approachPositions[positionIndex], 0, &workingPosition, 0);

	if (m_numberApproachPositionBones == 0)
	{
		Coord3D ourPosition = *us->getPosition();
		Coord3D theirPosition = *forWhom->getPosition();
		Vector3 offset(theirPosition.x - ourPosition.x, theirPosition.y - ourPosition.y, theirPosition.z - ourPosition.z);
		bfmeNormalizeV3(offset);
		offset = offset * (us->getMajorRadius() / 2);

		workingPosition.x += offset.X;
		workingPosition.y += offset.Y;
		workingPosition.z += offset.Z;
	}

	fpOptions.minRadius = 0.0f;
	fpOptions.maxRadius = 100.0f;
	fpOptions.sourceToPathToDest = forWhom;
	if (forWhom->isUsingAirborneLocomotor())
		fpOptions.ignoreObject = getObject();

	bool spotFound = PartitionManager::findPositionAround(&workingPosition, &fpOptions, &bestPosition);

	if (spotFound)
		return bestPosition;
	return workingPosition;
}
