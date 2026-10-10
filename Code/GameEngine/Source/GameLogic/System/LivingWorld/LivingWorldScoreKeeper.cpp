// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// LivingWorldScoreKeeper.cpp. WB 0x010EF240 names the constructor
// (LivingWorldScoreKeeper.cpp:70); the debug body lists the eight observer
// bases behind Snapshot and the Observable each one joins.
// Target facts: retail 0x004EEADE..0x004EECFC (ret 8). Base vtables
// 0x00BBB554 (Snapshot), then observer tables at +4..+0x20; the final tables
// 0x00C62AC4..0x00C62A60 are the ones the destructor 0x004EED02 reinstalls.
// The owner LivingWorldPlayer constructs it at +0x2C8 (calls 0x002E28BD and
// 0x002E2A66) passing its +0x14 word and itself; the Player observer list is
// at the player's +0. Members: the vector whose out-of-line teardown is
// 0x004EE501 at +0x28, three POD vectors, a bit vector, the start time,
// four int-to-pointer maps and the word block to +0xF8.
// Member roles and element types are structural inference; the observer
// interfaces carry only the slots the base tables need to exist.
#include <vector>
#include <map>
#include "Common/Snapshot.h"

extern "C" __declspec(dllimport) long __cdecl time(long *);

class LivingWorldPhaseObserver { public: virtual ~LivingWorldPhaseObserver() {} };
class LivingWorldBuildingObserver { public: virtual ~LivingWorldBuildingObserver() {} };
class LivingWorldAutoResolveEventObserver { public: virtual ~LivingWorldAutoResolveEventObserver() {} };
class LivingWorldRTSEventObserver { public: virtual ~LivingWorldRTSEventObserver() {} };
class LivingWorldRegionObserver { public: virtual ~LivingWorldRegionObserver() {} };
class LivingWorldPlayerObserver { public: virtual ~LivingWorldPlayerObserver() {} };
class LivingWorldLogicObserver { public: virtual ~LivingWorldLogicObserver() {} };
class LivingWorldBuildingNuggetSpawnArmyObserver { public: virtual ~LivingWorldBuildingNuggetSpawnArmyObserver() {} };

struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
class Rva002B7250;
extern Rva002B7250 g_00E04424, g_00E02E88, g_00E044F0;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldPlayer;

struct Rva004EE501 : public _STL::_Vector_base<int, _STL::allocator<int> >
{
	__forceinline Rva004EE501() : _STL::_Vector_base<int, _STL::allocator<int> >(_STL::allocator<int>()) {}
	~Rva004EE501();
};

class LivingWorldScoreKeeper : public Snapshot,
	public LivingWorldPhaseObserver,
	public LivingWorldBuildingObserver,
	public LivingWorldAutoResolveEventObserver,
	public LivingWorldRTSEventObserver,
	public LivingWorldRegionObserver,
	public LivingWorldPlayerObserver,
	public LivingWorldLogicObserver,
	public LivingWorldBuildingNuggetSpawnArmyObserver
{
public:
	LivingWorldScoreKeeper(int playerIndex, LivingWorldPlayer *player);
	virtual ~LivingWorldScoreKeeper();
protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
private:
	LivingWorldPlayer *m_player;		// +0x24
	Rva004EE501 m_28;
	_STL::vector<int> m_34, m_40, m_4C;
	_STL::vector<bool> m_58;
	int m_6C;
	long m_startTime;			// +0x70
	int m_74, m_78, m_7C;
	int m_80[5];
	int m_94, m_98;
	_STL::map<int, void *> m_9C;
	int m_A8, m_AC, m_B0;
	_STL::map<int, void *> m_B4, m_C0, m_CC;
	int m_D8, m_DC, m_E0, m_E4, m_E8, m_EC, m_F0;
	int m_playerIndex;			// +0xF4
	bool m_F8;
};

#define LW_OBSERVERS(offset) ((Rva005A0B4CList *)((char *)TheLivingWorldLogic + (offset)))

LivingWorldScoreKeeper::LivingWorldScoreKeeper(int playerIndex, LivingWorldPlayer *player) :
	m_player(player), m_6C(0), m_startTime(time(0)), m_74(0), m_78(-1), m_7C(-1),
	m_94(0), m_98(0), m_A8(0), m_AC(0), m_B0(0),
	m_D8(0), m_DC(0), m_E0(0), m_E4(0), m_E8(0), m_EC(0), m_F0(0),
	m_playerIndex(playerIndex), m_F8(false)
{
	for (int i = 0; i < 5; ++i)
		m_80[i] = 0;
	LW_OBSERVERS(0x1C)->append((Rva002BA8F1Listener *)(LivingWorldPhaseObserver *)this);
	LW_OBSERVERS(0x2C)->append((Rva002BA8F1Listener *)(LivingWorldAutoResolveEventObserver *)this);
	LW_OBSERVERS(0x3C)->append((Rva002BA8F1Listener *)(LivingWorldRTSEventObserver *)this);
	LW_OBSERVERS(0x4C)->append((Rva002BA8F1Listener *)(LivingWorldLogicObserver *)this);
	((Rva005A0B4CList *)&g_00E04424)->append((Rva002BA8F1Listener *)(LivingWorldBuildingObserver *)this);
	((Rva005A0B4CList *)&g_00E02E88)->append((Rva002BA8F1Listener *)(LivingWorldRegionObserver *)this);
	((Rva005A0B4CList *)&g_00E044F0)->append((Rva002BA8F1Listener *)(LivingWorldBuildingNuggetSpawnArmyObserver *)this);
	((Rva005A0B4CList *)m_player)->append((Rva002BA8F1Listener *)(LivingWorldPlayerObserver *)this);
}
