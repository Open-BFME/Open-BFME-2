// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /I. /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// WB RespawnUpdate::triggerRevival and native 4AF79C..4AF92F.
// BF1 RespawnUpdate rule/condition helpers (9cbfb551) guide semantics;
// BFME2 layout from matched death helper4AF63E and native accesses.
#include "Code/Libraries/Include/Lib/Coord3D.h"
// ?triggerDeathBeforeRespawn@RespawnUpdate@@QAEXXZ @0x004AF63E 350B.
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
class ExitInterface;
class BodyModuleInterface;
class FXList;
class InGameUI;

class ExperienceTracker
{
public:
	char m_pad00[0x24];
	int m_level;
	int m_28;
};

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

class UpdateModule
{
public:
	void *m_vtable;
	const RespawnUpdateModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
};

class RespawnUpdate : public UpdateModule
{
public:
	void triggerDeathBeforeRespawn();
 void triggerRevival(Object *at);

private:
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned char m_40;
	unsigned char m_41;
};


#include "../../../../Include/GameLogic/Module/ExitInterface.h"
#include "../../../../Include/GameLogic/Module/BodyModule.h"
#include "../../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;
void RespawnUpdate::triggerRevival(Object *at) {
 Object *obj=m_object;
 const RespawnUpdateModuleData *data=m_moduleData;
 Coord3D pos={at->getPosition()->x,at->getPosition()->y,at->getPosition()->z};
 ExitInterface *exit=at->getObjectExitInterface();
 if(exit) exit->getNaturalRallyPoint(pos,true);
 unsigned time;
 if(m_41) {
  obj->rva001E431E(data->conditionsA4);
  time=data->m_initialSpawnAnimationTime;
  FXList::doFXObj(data->m_initialSpawnFX,obj,0);
  if(TheInGameUI) TheInGameUI->rva002A123F(obj);
 } else {
  obj->rva001E431E(data->conditions58);
  time=data->reviveTime;
  FXList::doFXObj(data->reviveFX,obj,0);
  if(TheInGameUI) TheInGameUI->rva002A1261(obj);
 }
 // Native loads the default health before clearing the two rule counters.
 static const float one=1.0f;
 RespawnRule rule;
 float health=*(const volatile float *)&one;rule.cost=0;rule.time=0;
 m_2C=4;
 rule.level=(unsigned)obj->m_experienceTracker->m_level;rule.health=health;rule.autoSpawn=false;
 RespawnRuleNode *found=(RespawnRuleNode*)reinterpret_cast<const RespawnRuleTree &>(data->m_rules).find<unsigned int>(rule.level)._M_node;
 RespawnRuleNode *end=(RespawnRuleNode*)reinterpret_cast<const BFME2RespawnRuleTree &>(data->m_rules).sentinel;
 if(found==end) {
  initializeRespawnRule(rule, 1);
  found=(RespawnRuleNode*)reinterpret_cast<const RespawnRuleTree &>(data->m_rules).find<unsigned int>(rule.level)._M_node;
  if(found==end) {setWakeFrame(obj,UPDATE_SLEEP_FOREVER);return;}
 }
 m_20=*(float*)&found->m_healthBits;
 obj->body->setInitialHealth(m_20*100.0f,false);
 m_34=(unsigned)-1;m_38=(unsigned)-1;
 if(ThePlayerList->getLocalPlayer()==obj->getControllingPlayer()) TheControlBar->field28=true;
 setWakeFrame(obj,(UpdateSleepTime)time);
}
