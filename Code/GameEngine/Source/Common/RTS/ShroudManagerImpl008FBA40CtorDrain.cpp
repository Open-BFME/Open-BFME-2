// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// stlport
// Distinct TU for the BFME1 ShroudManagerImpl donor's constructor and
// drainPending (retail 0x0073E310 214B + 0x0073D7D0 54B). The donor path is
// occupied by the near-miss getShroudStatus pair, so the two bodies live here
// with declarations only for their callees (all pinned, none defined).

#include <deque>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Retail inlines these three zero stores; the canonical Coord3D::zero is the out-of-line owner.
static inline void zeroInline(Coord3D &c) { c.x = 0.0f; c.y = 0.0f; c.z = 0.0f; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	__forceinline Region3D() {}

	__forceinline Region3D(const Region3D &other)
	{
		lo.x = other.lo.x;
		lo.y = other.lo.y;
		lo.z = other.lo.z;
		hi.x = other.hi.x;
		hi.y = other.hi.y;
		hi.z = other.hi.z;
	}

	__forceinline ~Region3D() {}

	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }

	Coord3D lo;
	Coord3D hi;
};

struct Gen_t_008fb350_p12pod
{
	unsigned int timestamp;
	int x;
	int y;
	int radius;
	unsigned int playerMask;
};

class ShroudManagerImpl;
class ShroudManagerImpl008FBA40Node;
class ShroudManagerImpl008FBA40Element;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	void unlink();
	void makeDirty();

private:
	void updateCellsTouched();
	friend class ShroudManagerImpl;
};

typedef void (__cdecl *ShroudManagerImpl008FBA40RefreshCallback)(
	int x, int y, int status);

class ShroudManagerImpl
{
public:
	ShroudManagerImpl();
	void drainPending();
	void _ReallocCells(Region3D region, Real cellSize);

private:
	int mode;
	Region3D region;
	Real defaultCellSize;
	Real inverseCellSize;
	unsigned int width;
	unsigned int height;
	ShroudManagerImpl008FBA40Element *elements;
	ShroudManagerImpl008FBA40Node *nodes;
	PartitionData *pendingPartitionData;
	int unknown38;
	_STL::deque<Gen_t_008fb350_p12pod,
		_STL::allocator<Gen_t_008fb350_p12pod> > records;
	int unknown64;
	bool enabled;
	char padding69[3];
	ShroudManagerImpl008FBA40RefreshCallback refreshCallback;

	__declspec(noinline) void processPending(bool drainAll);
	friend class ShroudManagerImpl008FBA40Element;
};

ShroudManagerImpl::ShroudManagerImpl()
	: mode(2),
	  defaultCellSize(1.0f),
	  width(0),
	  height(0),
	  elements(0),
	  nodes(0),
	  pendingPartitionData(0),
	  unknown38(0),
	  records(),
	  unknown64(-1),
	  enabled(true),
	  refreshCallback(0)
{
	zeroInline(region.lo);
	zeroInline(region.hi);
	_ReallocCells(region, 1.0f);
}

inline void ShroudManagerImpl::drainPending()
{
	++unknown38;
	while (pendingPartitionData)
	{
		PartitionData *partitionData = pendingPartitionData;
		partitionData->unlink();
		partitionData->updateCellsTouched();
	}

	processPending(true);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeShroudManagerImpl008FBA40InlineAnchor@@YAXPAVShroudManagerImpl@@@Z absent-from-retail
void _bfmeShroudManagerImpl008FBA40InlineAnchor(ShroudManagerImpl *p)
{
    p->drainPending();
}
#pragma inline_depth()
