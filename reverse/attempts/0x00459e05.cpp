// ?rva00459E05@SiegeDockingBehavior@@QAEXXZ
// partial score=0.9551 date=2026-10-05
// cl: /O1 /Ob2 /GX /DNDEBUG /MD /arch:SSE /D_STLP_USE_STATIC_LIB /Op
// stlport
// ?rva00459E05@SiegeDockingBehavior@@QAEXXZ, retail 0x00459E05, 554 bytes.
// Target evidence: callers 0x0045A16D (loadPostProcess via vtable slot 1 of
// 0x008414DC) 0x0045A199 (size via +0x24 vector) 0x0045A1B6; layout +0x08
// Object +0x24 vector +0x30 bool from SiegeDockingBehaviorDtor; donor BFME1
// SiegeDockingInitialize00206CB0 (SIEGETOWER/SIEGELADDER bone init with
// Coord3D[10] MatrixRows[10] second Coord3D[10] plus 0x24 entry push_back).
#include <vector>

struct Coord3D
{
	Coord3D() {}
	~Coord3D() {}
	float x;
	float y;
	float z;
};

class SpawnBoneRow
{
public:
	SpawnBoneRow();
	float x;
	float y;
	float z;
	float w;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	SpawnBoneRow Row[3];
};

class Object
{
public:
	int getMultiLogicalBonePosition(const char *boneNamePrefix, int maxBones,
		Coord3D *positions, Matrix3D *transforms, bool convertToWorld, int extra) const;
};

class ModuleData
{
};

struct Position
{
	void setNegated(float a, float b, float c)
	{
		x = -a;
		y = -b;
		z = -c;
	}
	float x;
	float y;
	float z;
};

struct SiegeDockEntry
{
	int m_index;
	int m_type;
	Position m_position;
	Position m_direction;
	int m_objId;
};

class SiegeDockingBehavior
{
public:
	void rva00459E05();

private:
	char m_pad00[8];
	Object *m_object;
	char m_pad0C[0x18];
	_STL::vector<const ModuleData *> m_entries;
	bool m_initialized;
};

// ?rva00459E05@SiegeDockingBehavior@@QAEXXZ present-unmatched
void SiegeDockingBehavior::rva00459E05()
{
	int index = 0;
	Coord3D positions[10];
	Matrix3D transforms[10];
	Coord3D directions[10];
	(void)directions;
	int count = m_object->getMultiLogicalBonePosition("SIEGETOWER", 10, positions, transforms, true, 0);
	const Coord3D *pos = positions;
	const Matrix3D *tr = transforms;
	while (index < count)
	{
		SiegeDockEntry *entry = new SiegeDockEntry;
		entry->m_index = index;
		entry->m_position = *(Position *)pos;
		entry->m_direction.setNegated(tr->Row[0].x, tr->Row[1].x, tr->Row[2].x);
		entry->m_objId = 0;
		entry->m_type = 0;
		m_entries.push_back((const ModuleData *)entry);
		++index;
		++pos;
		++tr;
	}
	count = m_object->getMultiLogicalBonePosition("SIEGELADDER", 10, positions, transforms, true, 0);
	pos = positions;
	int remaining = count;
	tr = transforms;
	while (remaining > 0)
	{
		SiegeDockEntry *entry = new SiegeDockEntry;
		entry->m_index = index;
		entry->m_position = *(Position *)pos;
		entry->m_type = 1;
		entry->m_direction.setNegated(tr->Row[0].x, tr->Row[1].x, tr->Row[2].x);
		entry->m_objId = 0;
		m_entries.push_back((const ModuleData *)entry);
		++index;
		--remaining;
		++tr;
		++pos;
	}
	m_initialized = true;
}
