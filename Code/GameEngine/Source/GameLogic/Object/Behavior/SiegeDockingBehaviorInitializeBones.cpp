// STLport 4.5.3: typed pointer-vector instantiations preserve full retail bodies.
// BFME1 donor cee35b7d8: game/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingInitialize00206CB0.cpp.
// cl: /I. /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
// three 16-byte Vector4 rows built by the shared inline row ctor; the vector
// push_back is the ICF-shared pointer-vector body 0x004DFCB0.

#define _STLP_NO_EXCEPTIONS 1
// Existing matched pointer-vector siblings use this local overload to avoid
// offering a differently compiled max<unsigned> COMDAT to the link.
#include <stl/_algobase.h>
namespace _STL { static inline const unsigned &max(const unsigned&a,const unsigned&b) { return a<b?b:a; } }
#include <vector>

#include "Code/Libraries/Include/Lib/Coord3D.h"
// Reuse the existing 12-byte inherited lifetime ABI from W3DRadarCornerLifetimes.cpp;
// the array callbacks are owned ctor47A6A9/dtorB3FD0, with no new alias or pin.
struct BfmeRadarWorldPoint : Coord3D { BfmeRadarWorldPoint(); ~BfmeRadarWorldPoint(); };

// One 16-byte transform row (Vector4 layout); the nullary row ctor is the
// shared inline Vector4 body, so this TU's Matrix3D default ctor matches the
// linked copy instead of offering a SpawnBoneRow-ctor variant to the link.
#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

// The bone transform: three 16-byte rows and an empty inline constructor.
class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	Vector4 row[3];
};

struct Rva00459E05Position
{
	float x;
	float y;
	float z;
	__forceinline void setNegated(float const a, float const b, float const c) { ((volatile Rva00459E05Position*)this)->x=0.0f-a; ((volatile Rva00459E05Position*)this)->y=0.0f-b; ((volatile Rva00459E05Position*)this)->z=0.0f-c; }
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
	BfmeRadarWorldPoint positions[ 10 ];
	Matrix3D transforms[ 10 ];
	BfmeRadarWorldPoint directions[ 10 ];

	int count = m_object->getMultiLogicalBonePosition( "SIEGETOWER", 10, positions, transforms, true, 0 );
	for( ; index < count; ++index )
	{
		Rva00459E05Entry *entry = new Rva00459E05Entry;
		entry->m_index = index;
		entry->m_type = 0;
		entry->m_position = *(Rva00459E05Position *)&positions[ index ];
		Matrix3D *transform = &transforms[ index ];
		entry->m_direction.setNegated( transform->row[ 0 ].X, transform->row[ 1 ].X, transform->row[ 2 ].X );
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
		entry->m_direction.setNegated( transform->row[ 0 ].X, transform->row[ 1 ].X, transform->row[ 2 ].X );
		entry->m_objectID = 0;
		m_entries.push_back( entry );
		++index;
	}

	m_initialized = true;
}

// Native 0x0078A31A: complete 22-byte directions[10] cleanup.
// The exact 554-byte parent and complete native EH graph bind this action;
// its 12-byte lifetime adapter uses the existing empty destructor and EH iterator.

// Native 0x0078A304: complete 22-byte positions[10] cleanup.
// The exact 554-byte parent and complete native EH graph bind this action;
// its 12-byte lifetime adapter uses the existing empty destructor and EH iterator.
