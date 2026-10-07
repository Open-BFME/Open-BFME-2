// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?init@GameLogic@@UAEXXZ @0x00243EE7 957B (Ghidra FUN_00643ee7, ret at
// 0x002442A3; next body 0x002442A4).
// Target evidence: the setName literals name every subsystem it creates and
// the global each is stored in: ThePartitionManager (0x009FE748, ctor
// 0x006253F0), TheShroudManager (0x009FE74C, ctor 0x007398D0) and
// TheCollisionManager (0x009FE754, ctor 0x00758250), each new'd at 0x14 bytes,
// then TheTerrainLogic (0x009FEC50, own virtual 0x38, SubsystemInterface at
// +4), TheLargeGroupAudio (0x009FE1A8, new 0x40 with ctor 0x0020DD59) and
// TheBuffLogic (0x009FF190, own virtual 0x40, base at +4); TheGhostObjectManager
// (0x009FF188) comes from own virtual 0x3C. setName is the out-of-line
// SubsystemInterface member 0x0006F3CC taking an AsciiString by value.
// Donor: BFME 1 game/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (GameLogic::init, same subsystem order, region zero, partition 7, sides
// list pair and the trailing field resets). BFME 2 differs from the donor
// with three owned members new'd at +0x170/+0x174/+0x178 between the region
// setup and the ghost manager, an out-of-line player-leave reset
// (0x0023D17D through TheGameLogic) and moved field offsets. Field names
// stay offset names: only the donor knows their meaning.
#include <list>
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

typedef _STL::list<int, _STL::allocator<int> > IntList;

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

void setFPMode(void);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);
	virtual void init(void) = 0;
	void setName(AsciiString name);

private:
	int m_04;
	AsciiString m_name;
};

class PartitionManager : public SubsystemInterface
{
public:
	void setRegion(const Region3D *extent, float cellSize);
	void rva00625310(int value);

private:
	int m_impl[2];
};

class Rva006253F0 : public PartitionManager
{
public:
	Rva006253F0(void);
	virtual void init(void);
};

class Open2Store8F75D0 : public PartitionManager
{
public:
	Open2Store8F75D0(void);
	virtual void init(void);
};

class Rva00739720
{
public:
	void rva00739720(int value);
};

class CollisionManager : public SubsystemInterface
{
public:
	CollisionManager(void);
	virtual void init(void);

private:
	int m_impl[2];
};

class Rva00758210
{
public:
	void rva00758210(void);
};

class Rva006C0810
{
public:
	void rva006C0810(const Region3D *extent, float cellSize);
};

class TerrainLogic : public Snapshot, public SubsystemInterface
{
};

class BuffLogic : public Snapshot, public SubsystemInterface
{
};

class GhostObjectManager;

class LargeGroupAudio : public SubsystemInterface
{
public:
	LargeGroupAudio(void);
	virtual void init(void);

private:
	int m_body[13];
};

class Rva0035A2DC
{
public:
	void rva0035A2DC(Region3D *extent, float cellSize);
};

class Rva00359E13
{
public:
	Rva00359E13(void);
	void rva0035AA3E(void);

private:
	int m_body[17];
};

class Rva0043B660
{
public:
	Rva0043B660(void);
	void rva000B3FD0(void);

private:
	int m_body[4];
};

class Rva0043821C
{
public:
	void rva0043821C(void);
};

class Rva00243177
{
public:
	Rva00243177(void);

private:
	int m_body[6];
};

class SidesList
{
public:
	void rva0032D554(void);
	void rva0032F84F(void);
};

class GlobalData
{
public:
	char m_pad000[0xd4];
	float m_d4;
	float m_d8;
	char m_pad0DC[0xbd0 - 0xdc];
	int m_bd0;
};

class GameLogic : public SubsystemInterface
{
public:
	virtual void init(void);
	virtual void v02(void); virtual void v03(void);
	virtual void v04(void); virtual void v05(void); virtual void v06(void); virtual void v07(void);
	virtual void v08(void); virtual void v09(void); virtual void v10(void); virtual void v11(void);
	virtual void v12(void); virtual void v13(void);
	virtual TerrainLogic *createTerrainLogic(void);                      // +0x38
	virtual GhostObjectManager *createGhostObjectManager(void);          // +0x3C
	virtual BuffLogic *createBuffLogic(void);                            // +0x40

	void rva00240E18(bool loadingSaveGame);
	void rva0023D17D(void);

private:
	char m_pad00C[0x48 - 0x0c];
	int m_48;
	int m_4c;
	IntList m_50;
	char m_pad054[0x70 - 0x54];
	bool m_70;
	char m_pad071[0x94 - 0x71];
	int m_94;
	bool m_98;
	bool m_99;
	bool m_9a;
	bool m_9b;
	char m_pad09C[0xa0 - 0x9c];
	int m_a0;
	int m_a4;
	char m_pad0A8[0x11d - 0xa8];
	bool m_11d;
	char m_pad11E[0x124 - 0x11e];
	bool m_124;
	bool m_125;
	bool m_126;
	bool m_127;
	bool m_128[8];
	int m_130[8];
	bool m_150;
	char m_pad151[0x170 - 0x151];
	Rva00359E13 *m_170;
	Rva0043B660 *m_174;
	Rva00243177 *m_178;
	char m_pad17C[0x1b0 - 0x17c];
	int m_1b0;
	char m_pad1B4[0x2a4 - 0x1b4];
	int m_2a4;
};

extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern void *g_Va00DFE750;
extern CollisionManager *TheCollisionManager;
extern GlobalData *TheWritableGlobalData;
extern GhostObjectManager *TheGhostObjectManager;
extern TerrainLogic *TheTerrainLogic;
extern LargeGroupAudio *TheLargeGroupAudio;
extern BuffLogic *TheBuffLogic;
extern SidesList *TheSidesList;
extern GameLogic *TheGameLogic;

void GameLogic::init(void)
{
	setFPMode();

	rva00240E18(false);

	ThePartitionManager = new Rva006253F0;
	ThePartitionManager->init();
	ThePartitionManager->setName("ThePartitionManager");

	TheShroudManager = new Open2Store8F75D0;
	TheShroudManager->init();
	TheShroudManager->setName("TheShroudManager");

	TheCollisionManager = new CollisionManager;
	TheCollisionManager->init();
	TheCollisionManager->setName("TheCollisionManager");
	((Rva00758210 *)TheCollisionManager)->rva00758210();

	Region3D extent;
	extent.lo.x = 0.0f;
	extent.lo.y = 0.0f;
	extent.lo.z = 0.0f;
	extent.hi.x = 0.0f;
	extent.hi.y = 0.0f;
	extent.hi.z = 0.0f;
	TheShroudManager->setRegion(&extent, TheWritableGlobalData->m_d4);
	((Rva00739720 *)TheShroudManager)->rva00739720(TheWritableGlobalData->m_bd0);
	ThePartitionManager->rva00625310(7);
	((Rva006C0810 *)g_Va00DFE750)->rva006C0810(&extent, TheWritableGlobalData->m_d4);

	m_170 = new Rva00359E13;
	m_170->rva0035AA3E();
	((Rva0035A2DC *)m_170)->rva0035A2DC(&extent, TheWritableGlobalData->m_d8);

	m_174 = new Rva0043B660;
	m_174->rva000B3FD0();

	m_178 = new Rva00243177;
	((Rva0043821C *)m_178)->rva0043821C();

	TheGhostObjectManager = createGhostObjectManager();

	TheTerrainLogic = createTerrainLogic();
	TheTerrainLogic->init();
	TheTerrainLogic->setName("TheTerrainLogic");

	TheLargeGroupAudio = new LargeGroupAudio;
	if (TheLargeGroupAudio) {
		TheLargeGroupAudio->init();
		TheLargeGroupAudio->setName("TheLargeGroupAudio");
	}

	TheBuffLogic = createBuffLogic();
	TheBuffLogic->init();
	TheBuffLogic->setName("TheBuffLogic");

	TheSidesList->rva0032D554();
	TheSidesList->rva0032F84F();

	m_11d = false;
	m_124 = false;
	m_125 = false;
	m_126 = true;
	m_127 = true;
	for (int i = 0; i < 8; ++i) {
		m_128[i] = false;
		m_130[i] = 0;
	}
	m_150 = false;

	m_98 = true;
	m_99 = true;
	m_9a = true;
	m_9b = true;
	m_a0 = -1;
	m_a4 = 1;

	m_70 = false;
	m_94 = 0;
	m_48 = 0;
	m_50.clear();

	TheGameLogic->rva0023D17D();
	m_1b0 = -1;
	m_2a4 = 2;
}
