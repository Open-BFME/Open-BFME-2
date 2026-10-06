// ?rva00459E05@SiegeDockingBehavior@@AAEXXZ
// partial score=0.98 date=2026-10-06
// cl: /O1 /Ob2 /GX /DNDEBUG /MD /arch:SSE /D_STLP_USE_STATIC_LIB
// stlport
// Target boundary: Ghidra 0x00459E05/554B. Retail callers at 0x0045A16D,
// 0x0045A199 and 0x0045A1B6 support this SiegeDockingBehavior member.
// Target layout: Object at +0x08, vector at +0x24 and initialized byte at
// +0x30 are cross-checked by the constructor, destructor and xfer TUs. Each
// target allocation is 0x24 bytes. The initialization algorithm follows the
// BFME1 SiegeDockingBehavior donor; BFME2 instructions determine the local
// offsets, helper calls, loop shape and field stores below.
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
		volatile float *values = &x;
		values[0] = -a;
		values[1] = -b;
		values[2] = -c;
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
	private:
	void rva00459E05();
	char m_pad00[8];
	Object *m_object;
	char m_pad0C[0x18];
	_STL::vector<const ModuleData *> m_entries;
	bool m_initialized;
};

// ?rva00459E05@SiegeDockingBehavior@@AAEXXZ present-unmatched
void SiegeDockingBehavior::rva00459E05()
{
	int index = 0;
	Coord3D positions[10];
	Matrix3D transforms[10];
	Coord3D directions[10];
	(void)directions;
	Coord3D *pos;
	Matrix3D *tr;
	int count = m_object->getMultiLogicalBonePosition("SIEGETOWER", 10, positions, transforms, true, 0);
	if (count > 0)
	{
		for (pos = positions, tr = transforms; index < count; ++index, ++pos, ++tr)
		{
			SiegeDockEntry *entry = new SiegeDockEntry;
			Position *current = (Position *)pos;
			_ReadWriteBarrier();
			entry->m_index = index;
			_ReadWriteBarrier();
			entry->m_type = 0;
			entry->m_position = *current;
			entry->m_direction.setNegated(tr->Row[0].x, tr->Row[1].x, tr->Row[2].x);
			entry->m_objId = 0;
			m_entries.push_back((const ModuleData *)entry);
		}
	}
	count = m_object->getMultiLogicalBonePosition("SIEGELADDER", 10, positions, transforms, true, 0);
	if (count > 0)
	{
		pos = positions;
		tr = transforms;
		int remaining = count;
		while (remaining > 0)
		{
			SiegeDockEntry *entry = new SiegeDockEntry;
			Position *current = (Position *)pos;
			_ReadWriteBarrier();
			entry->m_index = index;
			_ReadWriteBarrier();
			entry->m_type = 1;
			entry->m_position = *current;
			entry->m_direction.setNegated(tr->Row[0].x, tr->Row[1].x, tr->Row[2].x);
			entry->m_objId = 0;
			m_entries.push_back((const ModuleData *)entry);
			++index;
			++pos;
			++tr;
			--remaining;
		}
	}
	m_initialized = true;
}
