// ?rva00459E05@SiegeDockingBehavior@@AAEXXZ
// partial score=0.99 date=2026-10-10
// ?rva00459E05@SiegeDockingBehavior@@AAEXXZ
// partial score=0.99 date=2026-10-09
// ?rva00459E05@SiegeDockingBehavior@@AAEXXZ
// partial score=0.99 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00459E05, 554B: SiegeDockingBehavior::rva00459E05 (name pinned:
// the no-argument member that loadPostProcess 0x0045A16D calls before the
// base UpdateModule::loadPostProcess).
// Body: the BFME 1 port of the same routine (reference/open-bfme-1/game/
// GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingInitialize00206CB0.cpp,
// retail 0x00206CB0 there): read up to ten SIEGETOWER and then SIEGELADDER
// bones, and push a 0x24-byte dock entry (running index, type 0/1, bone
// position, negated transform X column, object id 0) for each onto the
// pointer vector at +0x24; then set the initialized flag at +0x30.
// BFME 2 target evidence: object +8; the position and (unused) direction
// arrays are built by the EH vector iterators with the shared out-of-line
// Coord3D ctor/dtor (0x0047A6A9/0x000B3FD0); each 0x30-byte transform is
// three 16-byte rows with the same out-of-line row ctor; the vector
// push_back is the ICF-shared pointer-vector body 0x004DFCB0.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// class-gate: allow Coord3D the position and direction arrays are built and torn down through BFME 2's out-of-line empty Coord3D constructor and destructor (the eh vector iterators push 0x0047A6A9 and 0x000B3FD0); the canonical data-only header cannot declare them; same three floats
struct Coord3D
{
	Coord3D();
	~Coord3D();
	float x;
	float y;
	float z;
};

// One 16-byte transform row; its empty out-of-line ctor is the shared
// 0x0047A6A9 (spelled as in SpawnPointInitializeBonePositions.cpp).
class SpawnBoneRow
{
public:
	SpawnBoneRow();
	float x;
	float y;
	float z;
	float w;
};

// The bone transform: three 16-byte rows and an empty inline constructor.
class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	SpawnBoneRow row[3];
};

struct Rva00459E05Position
{
	float x;
	float y;
	float z;
	void setNegated( float a, float b, float c ) { x = 0.0f - a; y = 0.0f - b; z = 0.0f - c; }
};

// SiegeDockingBehavior dock entry (0x24 bytes).
struct Rva00459E05Entry
{
	int m_index;
	int m_type;
	Rva00459E05Position m_position;
	Rva00459E05Position m_direction;
	int m_objectID;
};

class Object
{
public:
	int getMultiLogicalBonePosition( const char *boneNamePrefix, int maxBones, Coord3D *positions,
		Matrix3D *transforms, bool convertToWorld, int unused ) const;
};

class SiegeDockingBehavior
{
private:
	void rva00459E05();
	Object *getObject() { return m_object; }

	unsigned char m_pad00[0x08];
	Object *m_object;
	unsigned char m_pad0C[0x24 - 0x0C];
	_STL::vector<Rva00459E05Entry *> m_entries;
	bool m_initialized;
};

void SiegeDockingBehavior::rva00459E05()
{
	int index = 0;
	Coord3D positions[ 10 ];
	Matrix3D transforms[ 10 ];
	Coord3D directions[ 10 ];

	int count = m_object->getMultiLogicalBonePosition( "SIEGETOWER", 10, positions, transforms, true, 0 );
	for( ; index < count; ++index )
	{
		Rva00459E05Entry *entry = new Rva00459E05Entry;
		entry->m_index = index;
		entry->m_type = 0;
		entry->m_position = *(Rva00459E05Position *)&positions[ index ];
		Matrix3D *transform = &transforms[ index ];
		entry->m_direction.setNegated( transform->row[ 0 ].x, transform->row[ 1 ].x, transform->row[ 2 ].x );
		entry->m_objectID = 0;
		m_entries.push_back( entry );
	}

	count = m_object->getMultiLogicalBonePosition( "SIEGELADDER", 10, positions, transforms, true, 0 );
	for( int i = 0; i < count; ++i )
	{
		Rva00459E05Entry *entry = new Rva00459E05Entry;
		entry->m_index = index;
		entry->m_type = 1;
		entry->m_position = *(Rva00459E05Position *)&positions[ i ];
		Matrix3D *transform = &transforms[ i ];
		entry->m_direction.setNegated( transform->row[ 0 ].x, transform->row[ 1 ].x, transform->row[ 2 ].x );
		entry->m_objectID = 0;
		m_entries.push_back( entry );
		++index;
	}

	m_initialized = true;
}
