// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// stlport

#include <deque>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern const Real g_bfmeK1253;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

__forceinline Int shroudFloatToLong(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

__forceinline Real shroudFloor(Real value)
{
	return (Real)floor((double)value);
}

__forceinline Real shroudCeil(Real value)
{
	return (Real)ceil((double)value);
}

void *operator new[](unsigned int bytes);
void operator delete[](void *pointer);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

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

class ShroudManagerImpl008FBA40;
class PartitionManager;
struct ShroudManagerImpl008FBA40ElementLayout;
__forceinline ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
	const ShroudManagerImpl008FBA40 *manager, Int x, Int y);

class BfmePartVRA;

class BfmeShroudVRA
{
public:
	char bfmeUpdateVRA(int x, int y, int radius);
	BfmePartVRA *m_bfme00;
	int m_bfme04;
};

bool processShroudRevealCircle008F9A70(Int cellX, Int cellY, Int cellRadius,
	ShroudManagerImpl008FBA40 *manager, Int playerMask);
bool processShroudRevealCircle008F9B10(Int cellX, Int cellY, Int cellRadius,
	ShroudManagerImpl008FBA40 *manager, Int playerMask);

class ShroudManagerImpl008FBA40Element;

struct ShroudManagerImpl008FBA40CellObject
{
	char padding00[0x24];
	int playerState[16];
};

class BfmeThingCDE
{
public:
	void d_008f7ec0();
	void d_008f7990();

	char unknown00[0x10];
	BfmeThingCDE *next;
	char unknown14[0x10];
	int playerShroudState[20];			// +0x24, cleared by notify()
};

class ShroudManagerImpl008FBA40Node
{
public:
	~ShroudManagerImpl008FBA40Node();

private:
	int unknown00;
	ShroudManagerImpl008FBA40CellObject *object;
	int unknown08;
	ShroudManagerImpl008FBA40Node *next;
	friend class ShroudManagerImpl008FBA40Element;
};

class ShroudManagerImpl008FBA40;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	void unlink();
	void makeDirty();

private:
	void updateCellsTouched();
	friend class ShroudManagerImpl008FBA40;

};

struct ShroudManagerImpl008FBA40PlayerState
{
	unsigned short status;
	unsigned short counters[2];
	unsigned short unknown06;
};

__forceinline int shroudStatusFromCount(unsigned short status)
{
	return status == 0xffff ? 2 : status == 0;
}

__forceinline int shroudStatusFromRaw(unsigned short status)
{
	if (status == 0xffff)
		return CELLSHROUD_SHROUDED;
	return status == 0;
}

typedef void (__cdecl *ShroudManagerImpl008FBA40RefreshCallback)(
	int x, int y, int status);

class ShroudManagerImpl008FBA40Element
{
public:
	ShroudManagerImpl008FBA40Element();
	~ShroudManagerImpl008FBA40Element();
	void adjustPlayerCounter008FC1F0(int playerIndex, int counterIndex,
		int amount);
	void updatePlayerCells008FC300(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);
	void updatePlayerCells008FC3B0(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);
	void updatePlayerCells008FC450(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);

private:
	__forceinline void copyPlayerStatesFrom(
		const ShroudManagerImpl008FBA40Element &other)
	{
		for (int i = 0; i < 20; ++i)
			playerStates[i] = other.playerStates[i];
	}

	ShroudManagerImpl008FBA40Node *cellNodes;
	ShroudManagerImpl008FBA40PlayerState playerStates[20];
	int unknown64;
	friend class ShroudManagerImpl008FBA40;
};

class ShroudManagerImpl008FBA40
{
public:
	ShroudManagerImpl008FBA40();
	~ShroudManagerImpl008FBA40();
	__declspec(noinline) CellShroudStatus getShroudStatusForPlayer(
		Int playerIndex, Int x, Int y) const;
	ObjectShroudStatus getPropShroudStatusForPlayer(Int playerIndex,
		const Coord3D *loc) const;
	void drainPending();
	void updatePlayerCells008FB010(int playerIndex);
	void updatePlayerCells008FB060(int playerIndex);
	void reset();
	void setRegion(const Region3D *region, Real cellSize);
	void configure(Region3D region, Real cellSize);
	__declspec(noinline) void notify();
	__declspec(noinline) void doShroudReveal(Int cellX, Int cellY,
		Int cellRadius, UnsignedInt playerMask);
	__declspec(noinline) void undoShroudReveal(Int cellX, Int cellY,
		Int cellRadius, UnsignedInt playerMask);

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
	friend class PartitionManager;
	friend ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
		const ShroudManagerImpl008FBA40 *manager, Int x, Int y);
};

struct ShroudManagerImpl008FBA40ElementLayout
{
	ShroudManagerImpl008FBA40Node *cellNodes;
	unsigned short playerStates[20][4];
	int unknown64;
};

__forceinline ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
	const ShroudManagerImpl008FBA40 *manager, Int x, Int y)
{
	if (x < 0 || x >= (Int)manager->width || y < 0 ||
		y >= (Int)manager->height)
		return 0;

	return reinterpret_cast<ShroudManagerImpl008FBA40ElementLayout *>(
		manager->elements + manager->width * y + x);
}

__declspec(noinline) CellShroudStatus
ShroudManagerImpl008FBA40::getShroudStatusForPlayer(
	Int playerIndex, Int x, Int y) const
{
	ShroudManagerImpl008FBA40ElementLayout *element =
		shroudElementAt(this, x, y);
	CellShroudStatus result = element
		? (CellShroudStatus)shroudStatusFromRaw(
			element->playerStates[playerIndex][0])
		: CELLSHROUD_SHROUDED;

	if (result == CELLSHROUD_FOGGED && !enabled)
		result = CELLSHROUD_CLEAR;
	return (CellShroudStatus)result;
}

ObjectShroudStatus ShroudManagerImpl008FBA40::getPropShroudStatusForPlayer(
	Int playerIndex, const Coord3D *loc) const
{
	if (playerIndex < 0 || playerIndex >= 20)
		return OBJECTSHROUD_SHROUDED;

	Int x = shroudFloatToLong((Real)floor((loc->x - defaultCellSize *
		0.5f - region.lo.x) *
		inverseCellSize));
	Int y = shroudFloatToLong((Real)floor((loc->y - defaultCellSize *
		0.5f - region.lo.y) *
		inverseCellSize));

	CellShroudStatus cellStatus = getShroudStatusForPlayer(playerIndex, x, y);
	if (cellStatus != getShroudStatusForPlayer(playerIndex, x + 1, y))
		return OBJECTSHROUD_PARTIAL_CLEAR;
	if (cellStatus != getShroudStatusForPlayer(playerIndex, x, y + 1))
		return OBJECTSHROUD_PARTIAL_CLEAR;
	if (cellStatus != getShroudStatusForPlayer(playerIndex, x + 1, y + 1))
		return OBJECTSHROUD_PARTIAL_CLEAR;
	switch (cellStatus)
	{
	case CELLSHROUD_CLEAR:
		_ReadWriteBarrier();
		return OBJECTSHROUD_CLEAR;
	case CELLSHROUD_SHROUDED:
		_ReadWriteBarrier();
		return OBJECTSHROUD_SHROUDED;
	default:
		_ReadWriteBarrier();
		return OBJECTSHROUD_FOGGED;
	}
}

// Retail inlines drainPending into configure; the same body is also emitted
// out of line from ShroudManagerImpl008FBA40CtorDrain.cpp (0x0073D7D0).
inline void ShroudManagerImpl008FBA40::drainPending()
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

// Transferred from BFME 1; the element is BFME 2's 20-player layout.
void ShroudManagerImpl008FBA40::configure(Region3D newRegion, Real cellSize)
{
	drainPending();

	for (BfmeThingCDE *node = reinterpret_cast<BfmeThingCDE *>(nodes);
		node != 0; node = node->next)
	{
		node->d_008f7ec0();
		node->d_008f7990();
		reinterpret_cast<PartitionData *>(node)->makeDirty();
	}

	processPending(false);

	if (newRegion.width() < 1.0f)
		newRegion.hi.x = newRegion.lo.x + 1.0f;
	if (newRegion.height() < 1.0f)
		newRegion.hi.y = newRegion.lo.y + 1.0f;

	Real newInverseCellSize = 1.0f / cellSize;
	int newWidth = shroudFloatToLong(shroudCeil(
		newRegion.width() * newInverseCellSize));
	if (newWidth < 1)
		newWidth = 1;
	int newHeight = shroudFloatToLong(shroudCeil(
		newRegion.height() * newInverseCellSize));
	if (newHeight < 1)
		newHeight = 1;

	ShroudManagerImpl008FBA40Element *newElements =
		new ShroudManagerImpl008FBA40Element[newWidth * newHeight];
	ShroudManagerImpl008FBA40Element *newElement = newElements;
	for (unsigned int y = 0; y < (unsigned int)newHeight; ++y)
	{
		int oldY = shroudFloatToLong(shroudFloor(
			((Real)y * cellSize + newRegion.lo.y - region.lo.y)
				* inverseCellSize));
		if (oldY >= 0 && oldY < (int)height)
		{
			for (unsigned int x = 0; x < (unsigned int)newWidth;
				++x, ++newElement)
			{
				int oldX = shroudFloatToLong(shroudFloor(
					((Real)x * cellSize + newRegion.lo.x - region.lo.x)
						* inverseCellSize));
				if (oldX >= 0 && oldX < (int)width)
				{
					newElement->copyPlayerStatesFrom(
						elements[oldY * width + oldX]);
				}
			}
		}
		else
		{
			newElement += newWidth;
		}
	}

	delete[] elements;
	elements = newElements;
	region = newRegion;
	inverseCellSize = newInverseCellSize;
	width = newWidth;
	height = newHeight;
	defaultCellSize = cellSize;

	if (!nodes)
	{
		unknown38 = 0;
	}
	else
	{
		drainPending();
		notify();
	}
}


// Transferred from BFME 1's ShroudManagerImpl008FBA40Notify.cpp: report every
// cell's status for the active player through the refresh callback, then
// clear that player's state on each node. BFME 2 tracks 20
// players (BFME 1: 16) in its 0xA8-byte element.
void ShroudManagerImpl008FBA40::notify()
{
	if (unknown64 < 0 || unknown64 >= 20)
		return;

	ShroudManagerImpl008FBA40Element *element = elements;
	ShroudManagerImpl008FBA40Element *end = element + width * height;
	int y = 0;
	int x = 0;
	while (element != end)
	{
		unsigned short state = element->playerStates[unknown64].status;
		int status = state == 0xffff ? 2 : state == 0;
		refreshCallback(x, y, status);

		++x;
		if (x == width)
		{
			x = 0;
			++y;
		}
		++element;
	}

	for (BfmeThingCDE *node = reinterpret_cast<BfmeThingCDE *>(nodes);
		node; node = node->next)
		node->playerShroudState[unknown64] = 0;
}

// Transferred from BFME 1's ShroudManagerImpl008FBA40.cpp verbatim: saturating
// adjust of one player's counter word inside the 0xA8-byte element.
void ShroudManagerImpl008FBA40Element::adjustPlayerCounter008FC1F0(
	int playerIndex, int counterIndex, int amount)
{
	unsigned short *counter =
		&playerStates[playerIndex].counters[counterIndex];
	amount += *counter;
	if (amount < 0)
		amount = 0;
	else if (amount > 0xffff)
		amount = 0xffff;
	*counter = (unsigned short)amount;
}

// Transferred from BFME 1's ShroudManagerImpl008FBA40.cpp verbatim: the
// reveal-count-increment variant refreshes through the manager callback when
// the visible status word changes.
void ShroudManagerImpl008FBA40Element::updatePlayerCells008FC300(
	ShroudManagerImpl008FBA40 *manager, int playerIndex)
{
	ShroudManagerImpl008FBA40PlayerState &playerState =
		playerStates[playerIndex];
	int oldStatus = shroudStatusFromCount(playerState.status);
	++playerState.status;
	if (playerState.status == 0)
		playerState.status = 1;
	int newStatus = shroudStatusFromCount(playerState.status);
	if (newStatus != oldStatus)
	{
		for (ShroudManagerImpl008FBA40Node *node = cellNodes;
			node; node = node->next)
		{
			node->object->playerState[playerIndex] = 0;
		}

		if (playerIndex == manager->unknown64)
		{
			int index = this - manager->elements;
			manager->refreshCallback(index % manager->width,
				index / manager->width, newStatus);
		}
	}
}

// Transferred from BFME 1's ShroudManagerImpl008FBA40.cpp verbatim: the
// reveal-count-decrement variant refreshes through the manager callback when
// the visible status word changes.
void ShroudManagerImpl008FBA40Element::updatePlayerCells008FC3B0(
	ShroudManagerImpl008FBA40 *manager, int playerIndex)
{
	ShroudManagerImpl008FBA40PlayerState &playerState =
		playerStates[playerIndex];
	int oldStatus = playerState.status == 0xffff
		? 2 : playerState.status == 0;
	--playerState.status;
	int newStatus = playerState.status == 0xffff
		? 2 : playerState.status == 0;
	if (newStatus != oldStatus)
	{
		for (ShroudManagerImpl008FBA40Node *node = cellNodes;
			node; node = node->next)
		{
			node->object->playerState[playerIndex] = 0;
		}

		if (playerIndex == manager->unknown64)
		{
			int index = this - manager->elements;
			manager->refreshCallback(index % manager->width,
				index / manager->width, newStatus);
		}
	}
}
