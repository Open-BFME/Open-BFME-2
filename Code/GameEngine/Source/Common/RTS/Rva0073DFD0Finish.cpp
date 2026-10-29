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

class Rva0073DFD0Element
{
public:
	Rva0073DFD0Element();
	~Rva0073DFD0Element();

private:
	void *cellNodes;
	Rva0073DFD0PlayerState playerStates[20];
	int unknown64;
};

// ?Rva0073DFD0Element::Rva0073DFD0Element present-unmatched
Rva0073DFD0Element::Rva0073DFD0Element() : cellNodes(0), unknown64(0) {}
// Retail's element destructor is the shared empty body at 0x0069E440 (a bare
// ret): reset's delete[] hands that address to the vector destructor iterator.
Rva0073DFD0Element::~Rva0073DFD0Element() {}

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
	Rva0073DFD0Element *elements;
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
	elements = new Rva0073DFD0Element[1];
}
