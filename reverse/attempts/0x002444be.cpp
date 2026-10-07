// ?populateRandomSideAndColor@@YAXPAVGameInfo@@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
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
#include <set>
#include <vector>
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

typedef _STL::list<int, _STL::allocator<int> > IntList;

struct Rva00239D49Element { Rva00239D49Element();Rva00239D49Element(const Rva00239D49Element&);~Rva00239D49Element();Rva00239D49Element&operator=(const Rva00239D49Element&);char bytes[1]; bool operator<(const Rva00239D49Element&)const; bool operator==(const Rva00239D49Element&)const; };
typedef _STL::list<Rva00239D49Element, _STL::allocator<Rva00239D49Element> > TocList;

namespace _STL
{
template<> void _List_base<Rva00239D49Element, allocator<Rva00239D49Element> >::clear();
}

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
	virtual void s02(void); virtual void s03(void); virtual void s04(void);
	virtual void s05(void); virtual void s06(void); virtual void s07(void);
	virtual void s08(void);
	virtual void reset(void);                                            // +0x24
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

class GhostObjectManager
{
public:
	virtual ~GhostObjectManager(void);
	virtual void g01(void); virtual void g02(void); virtual void g03(void);
	virtual void reset(void);                                            // +0x10
};

class AI : public SubsystemInterface
{
};

class ScriptEngine : public SubsystemInterface
{
};

class Overridable
{
public:
	Overridable *deleteOverrides(void);
};

struct Rva00200BD9Holder;

class StatsCollector;

class Rva0048BA39StatsCollector
{
public:
	~Rva0048BA39StatsCollector(void);
};

class Rva000427195
{
public:
	void rva003A2A41(void);
};

class Rva00240CAB
{
public:
	void rva0024191A(void);
};

class Rva001DBCDCTarget
{
public:
	void rva001DBCDC(void);
};

class Rva0053F1ECSub
{
public:
	void note(int buckets);
};

class Rva0023E7D9
{
public:
	void rva0023E7D9(void);
};

class Rva0035A1D8
{
public:
	void rva0035A1D8(void);
};

class DOTManager
{
public:
	void rva0043B725(void);
};

class Rva00439920
{
public:
	void rva00439920(void);
};

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
	virtual void v10(void); virtual void v11(void); virtual void v12(void); virtual void v13(void);
	virtual TerrainLogic *createTerrainLogic(void);                      // +0x38
	virtual GhostObjectManager *createGhostObjectManager(void);          // +0x3C
	virtual BuffLogic *createBuffLogic(void);                            // +0x40

	virtual void reset(void);

	void rva00240E18(bool loadingSaveGame);
	void rva0023D17D(void);
	void destroyAllObjectsImmediate(void);
	void rva00376D49(void);

	char m_pad00C[0x10 - 0x0c];
	char m_10[0x24 - 0x10];
	char m_24[0x40 - 0x24];
	int m_40;
	bool m_44;
	char m_pad045[0x48 - 0x45];
	int m_48;
	int m_4c;
	IntList m_50;
	char m_pad054[0x70 - 0x54];
	bool m_70;
	bool m_71;
	char m_pad072[0x94 - 0x72];
	int m_94;
	bool m_98;
	bool m_99;
	bool m_9a;
	bool m_9b;
	char m_pad09C[0x9f - 0x9c];
	bool m_9f;
	int m_a0;
	int m_a4;
	char m_pad0A8[0xb4 - 0xa8];
	char m_b4[0x10c - 0xb4];
	int m_10c;
	char m_pad110[0x11d - 0x110];
	bool m_11d;
	char m_pad11E[0x124 - 0x11e];
	bool m_124;
	bool m_125;
	bool m_126;
	bool m_127;
	bool m_128[8];
	int m_130[8];
	bool m_150;
	char m_pad151[0x154 - 0x151];
	int m_154;
	int m_158;
	int m_15c;
	int m_160;
	char m_pad164[0x170 - 0x164];
	Rva00359E13 *m_170;
	Rva0043B660 *m_174;
	Rva00243177 *m_178;
	int m_17c;
	int m_180;
	char m_pad184[0x1b0 - 0x184];
	int m_1b0;
	int m_1b4;
	char m_pad1B8[0x1c0 - 0x1b8];
	TocList m_1c0;
	char m_pad1C4[0x2a4 - 0x1c4];
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
extern AI *TheAI;
extern ScriptEngine *TheScriptEngine;
extern StatsCollector *g_00E032F8;
extern Rva00200BD9Holder *g_rva00200BD9Holder;

// 0x0004224C (rowed as a this-returning member) is the out-of-line
// constructor of a scope guard: when TheGameLogic exists it sets the FP mode
// on the first nesting level and counts TheGameLogic+0x1B4 up. The matching
// count-down (0x00042212) is expanded at scope exit.
class Rva0004224C
{
public:
	Rva0004224C(void);
	~Rva0004224C(void)
	{
		if (TheGameLogic)
			TheGameLogic->m_1b4--;
	}
};

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

// ?reset@GameLogic@@UAEXXZ @0x002442A4 538B (ret at 0x002444BD; next body
// 0x002444BE). Donor: BFME 1 GameLogicReset.cpp (GameLogic::reset), same
// order: map clears, flag resets, setFPMode, destroyAllObjectsImmediate, the
// subsystem resets, progress arrays, StatsCollector delete, TOC list clear,
// the defaults call 0x00240E18 (shared with init) and the trailing field
// resets. BFME 2 resets every SubsystemInterface through slot 0x24 and the
// ghost manager through slot 0x10, resets the three owned members at
// +0x170/+0x174/+0x178 when present, wraps the body in the FP-mode guard
// 0x0004224C, and deletes StatsCollector through its out-of-line destructor
// (ICF-folded with the AsciiString release at 0x0048BA39).
void GameLogic::reset(void)
{
	Rva0004224C fpModeGuard;

	((Rva000427195 *)m_10)->rva003A2A41();
	((Rva00240CAB *)m_24)->rva0024191A();
	((Rva001DBCDCTarget *)m_b4)->rva001DBCDC();
	((Rva0053F1ECSub *)m_b4)->note(0x2000);

	m_11d = false;
	m_124 = false;
	m_125 = false;
	m_126 = true;
	m_127 = true;
	m_9f = true;

	setFPMode();
	m_154 = 0;
	m_158 = 0;
	m_15c = 0;
	m_160 = 0;
	destroyAllObjectsImmediate();
	m_10c = 1;
	m_180 = 0;

	TheGhostObjectManager->reset();
	ThePartitionManager->reset();
	TheShroudManager->reset();
	TheCollisionManager->reset();
	((SubsystemInterface *)g_Va00DFE750)->reset();
	TheTerrainLogic->reset();
	TheAI->reset();
	TheScriptEngine->reset();
	if (m_170)
		((Rva0035A1D8 *)m_170)->rva0035A1D8();
	if (m_174)
		((DOTManager *)m_174)->rva0043B725();
	if (m_178)
		((Rva00439920 *)m_178)->rva00439920();
	TheLargeGroupAudio->reset();
	TheBuffLogic->reset();

	for (int i = 0; i < 8; ++i) {
		m_128[i] = false;
		m_130[i] = 0;
	}
	m_150 = false;

	if (g_00E032F8) {
		delete (Rva0048BA39StatsCollector *)g_00E032F8;
		g_00E032F8 = 0;
	}

	m_1c0.clear();

	rva00240E18(false);

	m_a0 = -1;
	m_98 = true;
	m_99 = true;
	m_9a = true;
	m_9b = true;
	m_a4 = 1;

	g_rva00200BD9Holder = (Rva00200BD9Holder *)((Overridable *)g_rva00200BD9Holder)->deleteOverrides();

	m_94 = 0;
	m_17c = 0;
	((Rva0023E7D9 *)this)->rva0023E7D9();
	m_71 = false;
	rva00376D49();
	m_44 = false;
	m_40 = 0;
	m_2a4 = 2;
}

// populateRandomSideAndColor @0x002444BE 926B (Ghidra FUN_006444be, ret at
// 0x0024485B; next body 0x0024485C). Target evidence: the GameLogic.cpp
// __FILE__ literal with lines 1923/1988/2011, GetGameLogicRandomSeed() % 7
// discards, GameInfo::getSlot/isOccupied/setPlayerTemplate/isColorTaken and
// MapCache::findMap(getMap()). Donor: BFME 1 GameLogicPopulateRandomSideAndColor
// (same slot walk, start-position faction set at MapMetaData+0x54 + pos*0x14 + 8,
// color pick). BFME 2 differs: the playable byte is PlayerTemplate+0x151, a
// second vector keeps each template's 0x001FD234 value (7 without a template),
// the side pool is a copy narrowed in place (swap) by the faction set and then
// by the slot's hero faction mask (CreateAHeroManager::GetFactionMaskType on
// the GameSlot+0x64 record when +0x60 is set), and the observer/out-of-range
// fallback is gone. The vector helpers are ICF folds shared with other
// element types; the address-named allocator and element type below only
// give those folded instantiations a placeholder name.
#define GAMELOGIC_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\GameLogic.cpp"

template <class T> class Rva002444BEAllocator : public _STL::allocator<T>
{
};
typedef _STL::vector<int, Rva002444BEAllocator<int> > Rva002444BEIndexVector;

enum Rva002444BEFaction
{
	RVA002444BE_FACTION_NONE = 7
};

unsigned int GetGameLogicRandomSeed(void);
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class PlayerTemplate
{
public:
	int rva001FD234() const;
	AsciiString getName() const;

	char m_pad00[0x151];
	bool m_151;
};

struct Rva002444BETemplateSlot
{
	char m_bytes[0x1dc];
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
	int getPlayerTemplateCount() const { return m_10 - m_0c; }

	char m_pad00[0x0c];
	Rva002444BETemplateSlot *m_0c;
	Rva002444BETemplateSlot *m_10;
};

struct Rva002444BEStartPosition
{
	char m_pad00[8];
	_STL::set<AsciiString> m_factions;
};

class MapMetaData
{
public:
	char m_pad00[0x54];
	Rva002444BEStartPosition m_positions[8];
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

struct Rva002444BEHero
{
	char m_pad00[0x0c];
	unsigned int m_0c;
	unsigned int m_10;
};

class GameSlot
{
public:
	bool isOccupied() const;
	void setPlayerTemplate(int playerTemplate);
	const Rva002444BEHero *getHero() const { return m_60 ? &m_64 : 0; }

	char m_pad00[0x0c];
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	char m_pad1C[0x60 - 0x1c];
	bool m_60;
	Rva002444BEHero m_64;
};

class GameInfo
{
public:
	GameSlot *getSlot(int index);
	AsciiString getMap() const;
	bool isColorTaken(int colorIdx, int slotToIgnore = -1) const;
};

class MultiplayerSettings
{
public:
	int getNumColors()
	{
		if (m_40 == 0)
			m_40 = m_38;
		return m_40;
	}

	char m_pad00[0x38];
	int m_38;
	int m_3c;
	int m_40;
};

class CreateAHeroManager
{
public:
	void *GetFactionMaskType(unsigned int classIndex, unsigned int subClassIndex);
};

class Rva0021A54A;

extern PlayerTemplateStore *ThePlayerTemplateStore;
extern MapCache *TheMapCache;
extern Rva0021A54A *TheHeroManager;
extern MultiplayerSettings *TheMultiplayerSettings;

void populateRandomSideAndColor(GameInfo *game)
{
	if (!game)
		return;
	int i;

	Rva002444BEIndexVector startSlots;
	_STL::vector<Rva002444BEFaction> templateFactions;
	for (i = 0; i < ThePlayerTemplateStore->getPlayerTemplateCount(); ++i)
	{
		const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(i);
		templateFactions.push_back((Rva002444BEFaction)(pt ? pt->rva001FD234() : RVA002444BE_FACTION_NONE));
		if (pt && pt->m_151)
			startSlots.push_back(i);
	}

	for (i = 0; i < 8; ++i)
	{
		GameSlot *slot = game->getSlot(i);
		if (!slot || !slot->isOccupied())
			continue;

		int playerTemplateIdx = slot->m_18;
		while (playerTemplateIdx != -2 && (playerTemplateIdx < 0 || playerTemplateIdx >= ThePlayerTemplateStore->getPlayerTemplateCount()))
		{
			unsigned int silly = GetGameLogicRandomSeed() % 7;
			for (int poo = 0; poo < silly; ++poo)
				GetGameLogicRandomValue(0, 1, GAMELOGIC_SOURCE_FILE, 1923);

			Rva002444BEIndexVector candidates(startSlots);
			const MapMetaData *md = TheMapCache->findMap(game->getMap());
			if (md)
			{
				const Rva002444BEStartPosition &position = md->m_positions[slot->m_10];
				const _STL::set<AsciiString> &factions = position.m_factions;
				if (factions.size() != 0)
				{
					Rva002444BEIndexVector possible;
					for (Rva002444BEIndexVector::iterator it = candidates.begin(); it != candidates.end(); ++it)
					{
						int idx = *it;
						AsciiString name = ThePlayerTemplateStore->getNthPlayerTemplate(idx)->getName();
						if (factions.find(name) != factions.end())
							possible.push_back(idx);
					}
					candidates.swap(possible);
				}
			}

			const Rva002444BEHero *hero = slot->getHero();
			if (hero)
			{
				unsigned int classIndex = hero->m_0c;
				const unsigned int *mask = (const unsigned int *)((CreateAHeroManager *)TheHeroManager)->GetFactionMaskType(classIndex, hero->m_10);
				Rva002444BEIndexVector allowed;
				for (Rva002444BEIndexVector::iterator it = candidates.begin(); it != candidates.end(); ++it)
				{
					int idx = *it;
					unsigned int faction = templateFactions[idx];
					if (mask[faction >> 5] & (1 << (faction & 31)))
						allowed.push_back(idx);
				}
				candidates.swap(allowed);
			}

			unsigned int count = candidates.size();
			int *pool = candidates.begin();
			playerTemplateIdx = pool[GetGameLogicRandomValue(0, 1000, GAMELOGIC_SOURCE_FILE, 1988) % count];
			const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(playerTemplateIdx);
			if (pt && pt->m_151)
				slot->setPlayerTemplate(playerTemplateIdx);
			else
				playerTemplateIdx = -1;
		}

		int colorIdx = slot->m_0c;
		if (colorIdx < 0 || colorIdx >= TheMultiplayerSettings->getNumColors())
		{
			while (colorIdx == -1)
			{
				colorIdx = GetGameLogicRandomValue(0, TheMultiplayerSettings->getNumColors() - 1, GAMELOGIC_SOURCE_FILE, 2011);
				if (game->isColorTaken(colorIdx))
					colorIdx = -1;
			}
			slot->m_0c = colorIdx;
		}
	}
}
