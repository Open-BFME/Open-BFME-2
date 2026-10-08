// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata

// BFME1 CollisionManagerConstructor.cpp adapted to the target base layout.
// Retail 0x758250: secondary vtable 0xCF3398 reaches the CollisionManager name
// getter; caller 0x243FB5 constructs a 0x14-byte object. The base constructor
// clears byte +4 and name storage +8; setName at 0x6F3CC confirms the latter.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_unknown04[4];
	void *m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
#pragma optimize("s", on)
#include "Common/Snapshot.h"
#pragma optimize("", on)

// Inferred target helper type: manager allocates 0xC070 bytes and calls the initializer at 0x75A000.
// The donor calls this owned object Rva009A45A0CollisionData; its type name is provisional.
class RetailCollisionManagerData
{
public:
	RetailCollisionManagerData();

private:
	unsigned char m_data[0xc070];
};

class CollisionManager : public SubsystemInterface, public Snapshot
{
public:
	CollisionManager();
	virtual ~CollisionManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();

private:
	RetailCollisionManagerData *m_data;
};

CollisionManager::CollisionManager()
{
	m_data = new RetailCollisionManagerData;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?crc@CollisionManager@@UAEXPAX@Z=?DX8_Assert@@YAXXZ")
#pragma comment(linker, "/alternatename:?xfer@CollisionManager@@UAEXPAX@Z=?name@Rva00758300Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:?loadPostProcess@CollisionManager@@UAEXXZ=?bfmeDescribe@Gen_00881040@@QAEXPAVBfmeFlagTarget@@@Z")
#pragma comment(linker, "/alternatename:?init@CollisionManager@@UAEXXZ=?DX8_Assert@@YAXXZ")
#pragma comment(linker, "/alternatename:?update@CollisionManager@@UAEXXZ=??1Coord2D@@QAE@XZ")
