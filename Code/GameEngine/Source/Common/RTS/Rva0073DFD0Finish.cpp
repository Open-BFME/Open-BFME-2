// ?reset@ShroudManager@@QAEXXZ
// cl: /O2 /DNDEBUG /MD /EHsc
// stlport46
//
// ShroudManagerImpl::reset (221B @0x008FBB50): zero a Region3D,
// setRegion(&empty, 0.0f), delete[] elements, elements = new Element[1].
// BFME2's class layout is the one in ShroudManagerImpl.cpp
// (elements at +0x2C, bool enabled at +0x68) and its element is 0xA8 bytes.
// Address-derived names only.

typedef float Real;
typedef int Int;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Retail inlines these stores; no separate private Coord3D::zero body.
static __forceinline void zeroCoord3D(Coord3D &value)
{
    value.x = 0.0f;
    value.y = 0.0f;
    value.z = 0.0f;
}

#include "../../../../Libraries/Include/Lib/Region3D.h"

struct Rva0073DFD0PlayerState
{
	unsigned short status;
	unsigned short counters[2];
	unsigned short unknown06;
};

// reset's new[] constructs ShroudManagerCell (retail 0x0073B600, rowed in
// ShroudManagerImpl008FBA40.cpp); its empty destructor is the shared bare
// ret at 0x0069E440 that delete[] hands the vector destructor iterator.
class ShroudManagerCell
{
public:
	__declspec(noinline) ShroudManagerCell();
	__declspec(noinline) ~ShroudManagerCell() {}

private:
	void *cellNodes;
	Rva0073DFD0PlayerState playerStates[20];
	int unknown64;
};

class ShroudManager
{
public:
	void reset();
	void setRegion(const Region3D *region, Real cellSize);

private:
	int mode;
	Region3D region;
	Real defaultCellSize;
	Real inverseCellSize;
	unsigned int width;
	unsigned int height;
	ShroudManagerCell *elements;
	void *nodes;
	void *pendingPartitionData;
	int unknown38;
	char records[0x28];
	int unknown64;
	bool enabled;
};

#include <new>

// ?reset@ShroudManager@@QAEXXZ
void ShroudManager::reset()
{
	Region3D emptyRegion;
	zeroCoord3D(emptyRegion.lo);
	zeroCoord3D(emptyRegion.hi);
	setRegion(&emptyRegion, 0.0f);

	enabled = true;
	delete[] elements;
	elements = new ShroudManagerCell[1];
}
