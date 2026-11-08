// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /GX-

enum { MAX_SPAWN_POINTS = 10 };

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

#include "ascii_string.h"

// Use the existing canonical 16-byte row, empty ctor and Set implementation.
#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

#include "../../../../Common/Thing/thing.h"
#include "../../../../../Include/GameClient/Drawable.h"


class SpawnPointProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[8];
	AsciiString m_spawnPointBoneNameData;
};

class SpawnPointProductionExitUpdate
{
private:
	void initializeBonePositions();
	void *m_vptr;
	const SpawnPointProductionExitUpdateModuleData *m_moduleData;
	Thing *m_object;
	unsigned char m_updatePad[0x18];
	bool m_bonesInitialized;
	unsigned char m_boolPad[3];
	int m_spawnPointCount;
	Coord3D m_worldCoordSpawnPoints[MAX_SPAWN_POINTS];
	float m_worldAngleSpawnPoints[MAX_SPAWN_POINTS];
};

void SpawnPointProductionExitUpdate::initializeBonePositions()
{
	Thing *me = m_object;
	Drawable *myDrawable = me->getDrawable();
	if (myDrawable == 0)
		return;

	Matrix3D boneTransforms[MAX_SPAWN_POINTS];
	for (int matrixIndex = 0; matrixIndex < MAX_SPAWN_POINTS; ++matrixIndex)
		boneTransforms[matrixIndex].Make_Identity();

	m_spawnPointCount = myDrawable->getPristineBonePositions(
		m_moduleData->m_spawnPointBoneNameData.str(), 1, 0,
		boneTransforms, MAX_SPAWN_POINTS, 0);

	for (matrixIndex = 0; matrixIndex < m_spawnPointCount; ++matrixIndex) {
		Matrix3D *currentTransform = &boneTransforms[matrixIndex];
		me->convertBonePosToWorldPos(0, currentTransform, 0, currentTransform);

		Coord3D worldPosition;
		worldPosition.x = currentTransform->Get_X_Translation();
		worldPosition.y = currentTransform->Get_Y_Translation();
		worldPosition.z = currentTransform->Get_Z_Translation();
		m_worldCoordSpawnPoints[matrixIndex] = worldPosition;
		m_worldAngleSpawnPoints[matrixIndex] = currentTransform->Get_Z_Rotation();
	}

	m_bonesInitialized = true;
}
