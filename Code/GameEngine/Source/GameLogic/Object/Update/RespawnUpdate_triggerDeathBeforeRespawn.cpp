// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /I. /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ?triggerDeathBeforeRespawn@RespawnUpdate@@QAEXXZ @0x004AF63E 350B.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
// RespawnUpdate death entry called by RespawnBody::apply. State 0 or 4
// looks the object's experience level up in the module-data rule tree at
// +0x10C (the parser's rule initialization: cost 0 time 0 health
// 1.0 autoSpawn false). A miss retries level 1 and otherwise sleeps forever.
// A hit applies the +0x0C condition words, the death FX at +0xF0, the hero
// death UI, disabled-4, effectively-dead, and status 3, then copies the
// rule into this module. The controlling player's +0x738 table records the
// tracker's +0x28 into the slot chosen by the unrowed helper 0x0037F2C0.

enum DisabledType;
enum ObjectStatusTypes;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1,
    UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Object;
class Player;
class FXList;
class InGameUI;

#include "../../../../Include/GameLogic/ExperienceTracker.h"

enum DisabledType;
enum ObjectStatusTypes;
enum ObjectID;
class Player;
class ExitInterface;
class BodyModuleInterface;
class AIUpdateInterface;
class ThingTemplate;
class ExperienceTracker;
class Object
{
public:
    ExitInterface *getObjectExitInterface() const;
    void restoreObjectToWorld(const Coord3D *);
    void rva001E42F2(const int *);
    void rva001E431E(const int *);
    void setStatus(ObjectStatusTypes, bool);
    bool clearDisabled(DisabledType);
    void setDisabledUntil(DisabledType, unsigned);
    void setDisabled(DisabledType);
    void setEffectivelyDead(bool);
    Player *getControllingPlayer() const;
    __forceinline const Coord3D *getPosition() const { return &position; }
    __forceinline ThingTemplate *getTemplate() const { return m_template; }

    char pad00[4];
    ThingTemplate *m_template;
    char pad08[0x38 - 0x08];
    Coord3D position;
    char pad44[0x74 - 0x44];
    int m_heroKey;
    ObjectID producer;
    char pad7C[0x254 - 0x7C];
    BodyModuleInterface *body;
    AIUpdateInterface *ai;
    char pad25C[0x264 - 0x25C];
    ExperienceTracker *m_experienceTracker;
    char pad268[0x45C - 0x268];
    int handle;
};

class FXList
{
public:
	static void doFXObj(const FXList *,const Object *,const Object *);
};

#include "../../../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

struct RespawnRule
{
    unsigned level;
    unsigned cost;
    int time;
    float health;
    bool autoSpawn;
};

static __forceinline void initializeRespawnRule(RespawnRule &rule, unsigned level=1)
{
    rule.level=level; rule.cost=0; rule.time=0; rule.health=1.0f; rule.autoSpawn=false;
}

// The rule tree uses the rowed private STLport _Rb_tree<unsigned, pair<const unsigned,
// void *> >::_M_find<unsigned> at 0x00357180 through public find and its iterator's node.
class RespawnUpdate;
#include <map>
typedef _STL::pair<const unsigned int, void *> RespawnRuleTreeValue;
typedef _STL::_Rb_tree<unsigned int, RespawnRuleTreeValue, _STL::_Select1st<RespawnRuleTreeValue>,
	_STL::less<unsigned int>, _STL::allocator<RespawnRuleTreeValue> > RespawnRuleTree;

struct RespawnInsertResult;

struct BFME2RespawnRuleTree
{
public:
    void *sentinel;
    RespawnInsertResult insert(const RespawnRule &);
    RespawnInsertResult *insertUnique(RespawnInsertResult *out, const RespawnRule &rule);
};

struct RespawnRuleNode
{
	char m_pad00[0x10];
	unsigned m_level;
	unsigned m_cost;
	int m_time;
	unsigned m_healthBits;
	bool m_autoSpawn;
};

#include "Common/Snapshot.h"
#include "ascii_string.h"

class Rva00360D26Member
{
public:
    ~Rva00360D26Member();
    Rva00360D26Member();
    char m_pad00[0x4];
};

struct BfmePod20
{
    unsigned a[5];
};

inline bool operator<(const BfmePod20 &x, const BfmePod20 &y)
{
    return x.a[0] < y.a[0];
}

typedef _STL::_Rb_tree<BfmePod20, BfmePod20, _STL::_Identity<BfmePod20>, _STL::less<BfmePod20>, _STL::allocator<BfmePod20> > UBfmePod20SetTree;

class MultiIniFieldParse;
class FXList;

class __declspec(novtable) RespawnUpdateModuleData : public Snapshot
{
public:
    RespawnUpdateModuleData();
    virtual ~RespawnUpdateModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    int calcCostToBuild(int value);
    int calcTimeToBuild(unsigned int value);

    unsigned m_field04; // +0x04
    Rva00360D26Member m_filter; // +0x08
    int conditions0C[19]; // +0x0C
    int conditions58[19]; // +0x58
    int conditionsA4[19]; // +0xA4
    const FXList *deathFX; // +0xF0
    const FXList *reviveFX; // +0xF4
    const FXList *m_initialSpawnFX; // +0xF8
    unsigned m_fieldFC; // +0xFC
    unsigned reviveTime; // +0x100
    unsigned m_initialSpawnAnimationTime; // +0x104
    unsigned char m_flag108; // +0x108
    char m_pad109[3];
    UBfmePod20SetTree m_rules; // +0x10C
    AsciiString m_deadImageName; // +0x118
    AsciiString m_respawnAsTemplate; // +0x11C
};

class Rva0037F2C0
{
public:
	int rva0037F2C0(Object *obj, bool autoSpawn);
};

class Rva0037E421
{
public:
	void *rva0037E421(int index);
};

struct RevivalSlot
{
	char m_pad00[0xC8];
	int m_c8;
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/RespawnUpdate.h"


void RespawnUpdate::triggerDeathBeforeRespawn()
{
	const RespawnUpdateModuleData *data = reinterpret_cast<const RespawnUpdateModuleData *>(m_moduleData);
	Object *obj = m_object;
	if (m_2C != 0 && m_2C != 4)
		return;

	RespawnRule rule;
	initializeRespawnRule(rule, (unsigned)obj->m_experienceTracker->m_24);
	RespawnRuleNode *found = (RespawnRuleNode *)reinterpret_cast<const RespawnRuleTree &>(data->m_rules).find<unsigned int>(rule.level)._M_node;
	RespawnRuleNode *end = (RespawnRuleNode *)reinterpret_cast<const BFME2RespawnRuleTree &>(data->m_rules).sentinel;
	if (found == end)
	{
		initializeRespawnRule(rule, 1);
		found = (RespawnRuleNode *)reinterpret_cast<const RespawnRuleTree &>(data->m_rules).find<unsigned int>(rule.level)._M_node;
		if (found == end)
		{
			setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
			return;
		}
	}

	obj->rva001E431E(data->conditions0C);
	FXList::doFXObj(data->deathFX, obj, 0);
	if (TheInGameUI)
		TheInGameUI->rva002A1283(obj);
	obj->setDisabled((DisabledType)4);
	obj->setEffectivelyDead(true);
	obj->setStatus((ObjectStatusTypes)3, true);

	m_40 = found->m_autoSpawn == 0;
	m_38 = (unsigned)found->m_time;
	m_3C = found->m_cost;
	*(unsigned *)&m_20 = found->m_healthBits;

	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return;

	char *table = (char *)player + 0x738;
	int index = ((Rva0037F2C0 *)table)->rva0037F2C0(obj, m_40 == 0);
	ExperienceTracker *tracker = obj->m_experienceTracker;
	if (tracker == 0)
		return;
	RevivalSlot *slot = (RevivalSlot *)((Rva0037E421 *)table)->rva0037E421(index);
	if (slot == 0)
		return;
	slot->m_c8 = tracker->m_28;
}
