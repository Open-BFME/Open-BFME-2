// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// stlport
// Keep MSVC's float math overloads local; the matched operations inline.
#define inline static inline
#include <math.h>
#undef inline
#pragma intrinsic(sin,cos)

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

#include <new>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Region3D.h"

// Opaque target32-byte queue element; its fields are not used in this unit.
// ProcessPending record stride and the rowed E32 map helper prove the size.
struct BfmeE32 { int a[8]; };

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

class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
class ICoord3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

// Retail's Version1 (0x000053EE, System/Xfer.cpp) is inlined in this unit's
// transfer: the version record is built on the stack and passed to slot 10.
class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class ShroudManagerCell;

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
	friend class ShroudManagerCell;
};

class ShroudManagerImpl;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	void unlink();
	void makeDirty();

private:
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

class ShroudManagerCell
{
public:
	__declspec(noinline) ShroudManagerCell();
	__declspec(noinline) ~ShroudManagerCell() {}
	void xfer(Xfer *xfer);
	void adjustPlayerCounter008FC1F0(int playerIndex, int counterIndex,
		int amount);
	void AddLooker(ShroudManagerImpl *manager,
		int playerIndex);
	void updatePlayerCells008FC3B0(ShroudManagerImpl *manager,
		int playerIndex);
	void ShroudIfFogged(ShroudManagerImpl *manager,
		int playerIndex);
	__declspec(noinline) int getPlayerStatus_Rva0073EA40(int playerIndex);

private:
	__forceinline void copyPlayerStatesFrom(
		const ShroudManagerCell &other)
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
	void rva0073D8B0(Xfer *xfer);
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
	void DoShroudReveal(int,int,void*,float,int);
	void UndoShroudReveal(int,int,void*,float,int);
	int mode;
	Region3D region;
	Real defaultCellSize;
	Real inverseCellSize;
	unsigned int width;
	unsigned int height;
	ShroudManagerCell *elements;
	ShroudManagerImpl008FBA40Node *nodes;
	PartitionData *pendingPartitionData;
	int unknown38;
	_STL::deque<BfmeE32,
		_STL::allocator<BfmeE32> > records;
	int unknown64;
	bool enabled;
	char padding69[3];
	ShroudManagerImpl008FBA40RefreshCallback refreshCallback;

	__declspec(noinline) void processPending(bool drainAll);
	ShroudManagerImpl008FBA40ElementLayout *elementAtByCoord_Rva0073A1D0(
		Real x, Real y) const;
	friend class ShroudManagerCell;
	friend class PartitionManager;
	friend class ShroudManager;
	friend ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
		const ShroudManagerImpl *manager, Int x, Int y);
};

class ShroudManager : public ShroudManagerImpl
{
public:
	// Method-only view of the independently recovered73AD90 provider.
	// No nested Data size, inheritance, or field layout is assumed here.
	class Data { public: void UpdateCellsTouched(); };
	void undoRevealMapForPlayerPermanently(int playerIndex);
	void ShroudMapForPlayer(int playerIndex);
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
		return reinterpret_cast<ShroudManagerCell *>(element)->
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
		ShroudManagerCell *end = elements + height * width;
		for (ShroudManagerCell *element = elements;
			element != end; ++element)
		{
			element->AddLooker(this, playerIndex);
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
		ShroudManagerCell *element = elements;
		ShroudManagerCell *end = element + height * width;
		while (element != end)
		{
			element->AddLooker(this, playerIndex);
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
		// Native _ReallocCells calls the73AD90 ShroudManager::Data owner.
		((ShroudManager::Data *)partitionData)->UpdateCellsTouched();
	}

	processPending(true);
}

// WorldBuilder's out-of-line twin (WB 0x017E1900) takes a buffer, a length and a
// seed; retail inlines it at both call sites below.
static UnsignedInt shroudCalcCRC(const void *buffer, UnsignedInt length,
	UnsignedInt crc)
{
	if (buffer == 0)
		return crc;
	const unsigned char *data = (const unsigned char *)buffer;
	for (UnsignedInt i = 0; i < length; ++i)
	{
		UnsignedInt hibit = crc >> 31;
		crc <<= 1;
		crc += *data;
		++data;
		crc += hibit;
	}
	return crc;
}

// Retail 0x0073D8B0 (818 B): the shroud manager's transfer. Statement order,
// the drainPending pair (first call out of line, second inlined), the
// element walk and the light-CRC checksum follow WorldBuilder's debug twin at
// WB 0x017E6FC0 call for call.
void ShroudManagerImpl::rva0073D8B0(Xfer *xfer)
{
	if (!xfer->IsLightCRC())
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

		{
			Xfer::Version version(1, 1);
			*xfer == version;
		}
		*xfer == *(UnsignedInt *)&mode;
		*xfer == region;
		*xfer == defaultCellSize;
		*xfer == inverseCellSize;
		*xfer == *(Int *)&width;
		*xfer == *(Int *)&height;
		*xfer == *(UnsignedInt *)&unknown38;
		if (!xfer->IsCRC())
			*xfer == unknown64;
		*xfer == enabled;

		if (xfer->IsLoading())
		{
			delete[] elements;
			elements = new ShroudManagerCell[width * height];
		}

		ShroudManagerCell *cell = elements;
		for (UnsignedInt y = 0; y < height; ++y)
		{
			for (UnsignedInt x = 0; x < width; ++x, ++cell)
				cell->xfer(xfer);
		}

		if (xfer->IsLoading())
			notify();
		else
			drainPending();
	}
	else
	{
		UnsignedInt crc = 0;
		ShroudManagerCell *cell = elements;
		for (UnsignedInt y = 0; y < height; ++y)
		{
			for (UnsignedInt x = 0; x < width; ++x, ++cell)
			{
				for (UnsignedInt i = 0; i < 20; ++i)
				{
					crc += shroudCalcCRC(&cell->playerStates[i].status, 2, 0);
					crc += shroudCalcCRC(&cell->playerStates[i].counters, 6, 0);
				}
			}
		}
		*xfer == crc;
	}
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

	ShroudManagerCell *newElements =
		new ShroudManagerCell[newWidth * newHeight];
	ShroudManagerCell *newElement = newElements;
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

	ShroudManagerCell *element = elements;
	ShroudManagerCell *end = element + width * height;
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

// Retail 0x0073D810 is ShroudManager::undoRevealMapForPlayerPermanently,
// the tail-call target of the PartitionManager undo thunk at 0x007397B0.
// It is the decrement twin of RevealMapForPlayerPermanently above:
// same 20-player guard and element sweep, but it drains pending work
// first and runs the 008FC3B0 (reveal-decrement) variant. ShroudManager
// derives from the Impl (base at +0), so the member reads and the
// processPending call need no this adjustment.


// ?undoRevealMapForPlayerPermanently@ShroudManager@@QAEXH@Z
void ShroudManager::undoRevealMapForPlayerPermanently(int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 20)
	{
		processPending(false);

		ShroudManagerCell *end = elements + height * width;
		for (ShroudManagerCell *element = elements;
			element != end; ++element)
		{
			element->updatePlayerCells008FC3B0(this, playerIndex);
		}
	}
}

void ShroudManager::ShroudMapForPlayer(int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 20)
	{
		processPending(false);

		ShroudManagerCell *end = elements + height * width;
		for (ShroudManagerCell *element = elements;
			element != end; ++element)
		{
			element->ShroudIfFogged(this, playerIndex);
		}
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?getShroudStatusForPlayer@ShroudManager@@QBE?AW4CellShroudStatus@@HPBUCoord3D@@@Z=?GetShroudStatusForPlayer@ShroudManagerImpl@@QBE?AW4CellShroudStatus@@HPBUCoord3D@@@Z")
#pragma comment(linker, "/alternatename:?revealMapForPlayerPermanently@ShroudManager@@QAEXH@Z=?RevealMapForPlayerPermanently@ShroudManagerImpl@@QAEXH@Z")

// Native 0x0073B600: array constructor used by _ReallocCells (0x73DBF0)
// and the shroud transfer (0x73D8B0). Both pass the verified 0xA8 element
// stride. Target initializes the cell link and trailing word, then twenty
// status words to shrouded and all three counter words to zero.
__declspec(noinline) ShroudManagerCell::ShroudManagerCell()
{
	cellNodes = 0;
	unknown64 = 0;
	for (int i = 0; i < 20; ++i)
	{
		playerStates[i].status = 0xffff;
		unsigned short *values = &playerStates[i].counters[0];
		for (int j = 0; j < 3; ++j)
			values[j] = 0;
	}
}
