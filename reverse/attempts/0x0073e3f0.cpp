// ??1ShroudManagerImpl@@QAE@XZ
// partial score=0.97 date=2026-10-08
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

// Native deque helpers use the already rowed 32-byte opaque element.
struct BfmeE32 { int a[8]; };

struct Gen_t_008fb350_p12pod
{
	unsigned int timestamp;
	int x;
	int y;
	int radius;
	unsigned int playerMask;
};

class ShroudManagerImpl;
class PartitionManager;
struct ShroudManagerImpl008FBA40ElementLayout;
__forceinline ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
	const ShroudManagerImpl *manager, Int x, Int y);

class BfmePartVRA;

class BfmeShroudVRA
{
public:
	char bfmeUpdateVRA(int x, int y, int radius);
	BfmePartVRA *m_bfme00;
	int m_bfme04;
};

bool processShroudRevealCircle008F9A70(Int cellX, Int cellY, Int cellRadius,
	ShroudManagerImpl *manager, Int playerMask);
bool processShroudRevealCircle008F9B10(Int cellX, Int cellY, Int cellRadius,
	ShroudManagerImpl *manager, Int playerMask);

// Native _ReallocCells (0x73DBF0) destroys 0xA8-byte elements through the
// empty ret at 0x69E440, not the 0x68-byte Snapshot-derived owner at 0x3A795A.
// Bind the proven empty ICF destructor to the existing empty-body provider.
#pragma comment(linker, "/alternatename:??1ShroudManagerImpl008FBA40Element@@QAE@XZ=?DX8_Assert@@YAXXZ")
class ShroudManagerImpl008FBA40Element;

struct ShroudManagerImpl008FBA40CellObject
{
	char padding00[0x24];
	int playerState[16];
};

class BfmeThingCDE
{
public:
	void bfmeDtorCDE();
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

class ShroudManagerImpl;

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
	void updatePlayerCells008FC300(ShroudManagerImpl *manager,
		int playerIndex);
	void updatePlayerCells008FC3B0(ShroudManagerImpl *manager,
		int playerIndex);
	void updatePlayerCells008FC450(ShroudManagerImpl *manager,
		int playerIndex);
	__declspec(noinline) int getPlayerStatus_Rva0073EA40(int playerIndex);

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
	friend class ShroudManagerImpl;
};

class ShroudManagerImpl
{
public:
	ShroudManagerImpl();
	~ShroudManagerImpl();
	__declspec(noinline) CellShroudStatus GetShroudStatusForPlayer(
		Int playerIndex, Int x, Int y) const;
	CellShroudStatus GetShroudStatusForPlayer(
		Int playerIndex, const Coord3D *loc) const;
	int GetLookerCount(
		Int playerIndex, const Coord3D *loc) const;
	void setEnabled_Rva0073B460(bool value);
	void RevealMapForPlayerPermanently(int playerIndex);
	void RevealMapForPlayer(int playerIndex);
	ObjectShroudStatus GetPropShroudStatusForPlayer(Int playerIndex,
		const Coord3D *loc) const;
	void drainPending();
	void updatePlayerCells008FB010(int playerIndex);
	void updatePlayerCells008FB060(int playerIndex);
	void reset();
	void setRegion(const Region3D *region, Real cellSize);
	void _ReallocCells(Region3D region, Real cellSize);
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
	_STL::deque<BfmeE32, _STL::allocator<BfmeE32> > records;
	int unknown64;
	bool enabled;
	char padding69[3];
	ShroudManagerImpl008FBA40RefreshCallback refreshCallback;

	__declspec(noinline) void processPending(bool drainAll);
	ShroudManagerImpl008FBA40ElementLayout *elementAtByCoord_Rva0073A1D0(
		Real x, Real y) const;
	friend class ShroudManagerImpl008FBA40Element;
	friend class PartitionManager;
	friend class ShroudManager;
	friend ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
		const ShroudManagerImpl *manager, Int x, Int y);
};

struct ShroudManagerImpl008FBA40ElementLayout
{
	ShroudManagerImpl008FBA40Node *cellNodes;
	unsigned short playerStates[20][4];
	int unknown64;
};

__forceinline ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
	const ShroudManagerImpl *manager, Int x, Int y)
{
	if (x < 0 || x >= (Int)manager->width || y < 0 ||
		y >= (Int)manager->height)
		return 0;

	return reinterpret_cast<ShroudManagerImpl008FBA40ElementLayout *>(
		manager->elements + manager->width * y + x);
}

__declspec(noinline) CellShroudStatus
ShroudManagerImpl::GetShroudStatusForPlayer(
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

// Retail 0x0073B940 is the coordinate overload of the cell-status getter: it
// floors the world point through elementAtByCoord and maps the status word the
// same way. No direct callers remain in retail; the name is descriptive.
CellShroudStatus ShroudManagerImpl::GetShroudStatusForPlayer(
	Int playerIndex, const Coord3D *loc) const
{
	if (playerIndex < 0 || playerIndex >= 20)
		return CELLSHROUD_SHROUDED;

	ShroudManagerImpl008FBA40ElementLayout *element =
		elementAtByCoord_Rva0073A1D0(loc->x, loc->y);
	if (!element)
		return CELLSHROUD_SHROUDED;

	return (CellShroudStatus)shroudStatusFromRaw(
		element->playerStates[playerIndex][0]);
}

// Retail 0x0073B890 is the raw-word sibling of the coordinate getter above:
// out-of-range players report 2, a missed element reports 0, otherwise the
// element's unmapped status word comes back through getPlayerStatus_Rva0073EA40.
// No direct callers remain in retail; the name is descriptive.
int ShroudManagerImpl::GetLookerCount(
	Int playerIndex, const Coord3D *loc) const
{
	if (playerIndex < 0 || playerIndex >= 20)
		return CELLSHROUD_SHROUDED;

	ShroudManagerImpl008FBA40ElementLayout *element =
		elementAtByCoord_Rva0073A1D0(loc->x, loc->y);
	if (element)
		return reinterpret_cast<ShroudManagerImpl008FBA40Element *>(element)->
			getPlayerStatus_Rva0073EA40(playerIndex);
	return CELLSHROUD_CLEAR;
}

// Retail 0x0073B460 stores one byte into the manager's enabled flag at +0x68.
// No BFME 1 donor names it; descriptive Rva-qualified name.
void ShroudManagerImpl::setEnabled_Rva0073B460(bool value)
{
	enabled = value;
}

// Retail 0x0073B410 runs the increment variant over every element for one
// player. It matches the BFME 1 updatePlayerCells008FB010/008FB060 loop shape
// but calls only the 008FC300 variant, so it lands under a descriptive
// Rva-qualified name instead of a donor name.
void ShroudManagerImpl::RevealMapForPlayerPermanently(
	int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 20)
	{
		ShroudManagerImpl008FBA40Element *end = elements + height * width;
		for (ShroudManagerImpl008FBA40Element *element = elements;
			element != end; ++element)
		{
			element->updatePlayerCells008FC300(this, playerIndex);
		}
	}
}

// Retail 0x0073B3B0 runs the increment variant immediately followed by the
// decrement variant over every element for one player. Same sweep shape as
// the 0x0073B410 body with the element-first declaration order; descriptive
// Rva-qualified name.
void ShroudManagerImpl::RevealMapForPlayer(
	int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 20)
	{
		ShroudManagerImpl008FBA40Element *element = elements;
		ShroudManagerImpl008FBA40Element *end = element + height * width;
		while (element != end)
		{
			element->updatePlayerCells008FC300(this, playerIndex);
			element->updatePlayerCells008FC3B0(this, playerIndex);
			++element;
		}
	}
}

ObjectShroudStatus ShroudManagerImpl::GetPropShroudStatusForPlayer(
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

	CellShroudStatus cellStatus = GetShroudStatusForPlayer(playerIndex, x, y);
	if (cellStatus != GetShroudStatusForPlayer(playerIndex, x + 1, y))
		return OBJECTSHROUD_PARTIAL_CLEAR;
	if (cellStatus != GetShroudStatusForPlayer(playerIndex, x, y + 1))
		return OBJECTSHROUD_PARTIAL_CLEAR;
	if (cellStatus != GetShroudStatusForPlayer(playerIndex, x + 1, y + 1))
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

// Retail inlines drainPending into _ReallocCells; the same body is also emitted
// out of line from ShroudManagerImpl008FBA40CtorDrain.cpp (0x0073D7D0).
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

// Transferred from BFME 1; the element is BFME 2's 20-player layout.
void ShroudManagerImpl::_ReallocCells(Region3D newRegion, Real cellSize)
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
void ShroudManagerImpl::notify()
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

// Transferred from BFME 1's ShroudManagerImpl.cpp verbatim: saturating
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

// Transferred from BFME 1's ShroudManagerImpl.cpp verbatim: the
// reveal-count-increment variant refreshes through the manager callback when
// the visible status word changes.
void ShroudManagerImpl008FBA40Element::updatePlayerCells008FC300(
	ShroudManagerImpl *manager, int playerIndex)
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

// Transferred from BFME 1's ShroudManagerImpl.cpp verbatim: the
// reveal-count-decrement variant refreshes through the manager callback when
// the visible status word changes.
void ShroudManagerImpl008FBA40Element::updatePlayerCells008FC3B0(
	ShroudManagerImpl *manager, int playerIndex)
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

// Transferred from BFME 1's ShroudManagerImpl.cpp verbatim: the
// full-shroud variant sets the status word and reports constant status 2.
void ShroudManagerImpl008FBA40Element::updatePlayerCells008FC450(
	ShroudManagerImpl *manager, int playerIndex)
{
	ShroudManagerImpl008FBA40PlayerState &playerState =
		playerStates[playerIndex];
	if (playerState.status == 0)
	{
		playerState.status = 0xffff;
		for (ShroudManagerImpl008FBA40Node *node = cellNodes;
			node; node = node->next)
		{
			node->object->playerState[playerIndex] = 0;
		}

		if (playerIndex == manager->unknown64)
		{
			int index = this - manager->elements;
			manager->refreshCallback(index % manager->width,
				index / manager->width, 2);
		}
	}
}

// Retail 0x0073A1D0 outlines the float-coordinate variant of shroudElementAt:
// floor the world-space point into cell indices and bounds-check them. BFME 1
// only inlines the integer form, so this lands under a descriptive
// Rva-qualified name.
ShroudManagerImpl008FBA40ElementLayout *
ShroudManagerImpl::elementAtByCoord_Rva0073A1D0(Real x, Real y) const
{
	Int cellX = shroudFloatToLong(shroudFloor(
		(x - region.lo.x) * inverseCellSize));
	if (cellX < 0 || cellX >= (Int)width)
		return 0;
	Int cellY = shroudFloatToLong(shroudFloor(
		(y - region.lo.y) * inverseCellSize));
	if (cellY < 0 || cellY >= (Int)height)
		return 0;
	return reinterpret_cast<ShroudManagerImpl008FBA40ElementLayout *>(
		elements + width * cellY + cellX);
}

// Retail 0x0073EA50 is this TU's adjustPlayerCounter008FC1F0; the 12B reader
// at 0x0073EA40 loads the same element's status word for one player. No BFME 1
// donor names it (its only caller is 0x0073B890), so it lands under a
// descriptive Rva-qualified name.
__declspec(noinline) int ShroudManagerImpl008FBA40Element::getPlayerStatus_Rva0073EA40(
	int playerIndex)
{
	return playerStates[playerIndex].status;
}

// Retail 0x0073D810 is ShroudManager::undoRevealMapForPlayerPermanently,
// the tail-call target of the PartitionManager undo thunk at 0x007397B0.
// It is the decrement twin of RevealMapForPlayerPermanently above:
// same 20-player guard and element sweep, but it drains pending work
// first and runs the 008FC3B0 (reveal-decrement) variant. ShroudManager
// derives from the Impl (base at +0), so the member reads and the
// processPending call need no this adjustment.
class ShroudManager : public ShroudManagerImpl
{
public:
	void undoRevealMapForPlayerPermanently(int playerIndex);
	void updatePlayerCells450_Rva0073D860(int playerIndex);
};

// ?undoRevealMapForPlayerPermanently@ShroudManager@@QAEXH@Z
void ShroudManager::undoRevealMapForPlayerPermanently(int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 20)
	{
		processPending(false);

		ShroudManagerImpl008FBA40Element *end = elements + height * width;
		for (ShroudManagerImpl008FBA40Element *element = elements;
			element != end; ++element)
		{
			element->updatePlayerCells008FC3B0(this, playerIndex);
		}
	}
}

void ShroudManager::updatePlayerCells450_Rva0073D860(int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 20)
	{
		processPending(false);

		ShroudManagerImpl008FBA40Element *end = elements + height * width;
		for (ShroudManagerImpl008FBA40Element *element = elements;
			element != end; ++element)
		{
			element->updatePlayerCells008FC450(this, playerIndex);
		}
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?getShroudStatusForPlayer@ShroudManager@@QBE?AW4CellShroudStatus@@HPBUCoord3D@@@Z=?GetShroudStatusForPlayer@ShroudManagerImpl@@QBE?AW4CellShroudStatus@@HPBUCoord3D@@@Z")
#pragma comment(linker, "/alternatename:?revealMapForPlayerPermanently@ShroudManager@@QAEXH@Z=?RevealMapForPlayerPermanently@ShroudManagerImpl@@QAEXH@Z")

// Native 73E3F0..73E47C destroys this manager's +30 CDE chain and +2C
// A8-byte cell array, then its +3C deque. BFME1's ba7ddda donor supplies
// the ownership algorithm; the three target accesses and rowed providers
// establish the target layout independently. CDE cleanup unlinks the head.
ShroudManagerImpl::~ShroudManagerImpl()
{
	while (nodes)
	{
		BfmeThingCDE *node = reinterpret_cast<BfmeThingCDE *>(nodes);
		node->bfmeDtorCDE();
		operator delete(node);
	}
	delete[] elements;
}
