// cl: /O1 /Ob2 /arch:SSE /G6 /DNDEBUG /MD /GX-

enum { MAX_SPAWN_POINTS = 10 };

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data + 1) : "";
	}

private:
	BfmeAsciiStringData *m_data;
};

class SpawnBoneRow
{
public:
	SpawnBoneRow();
	void Set(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

	float Get_X_Translation() const { return Row[0].W; }
	float Get_Y_Translation() const { return Row[1].W; }
	float Get_Z_Translation() const { return Row[2].W; }
	float Get_Z_Rotation() const;

	SpawnBoneRow Row[3];
};

class Drawable
{
public:
	int getPristineBonePositions(const char *boneNamePrefix, int startIndex,
		Coord3D *positions, Matrix3D *transforms, int maxBones, int extra) const;
};

class Thing
{
public:
	Drawable *getDrawable() const;
	void convertBonePosToWorldPos(const Coord3D *bonePos,
		const Matrix3D *boneTransform, Coord3D *worldPos,
		Matrix3D *worldTransform) const;
};

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
