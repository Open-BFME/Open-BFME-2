// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /I.
// WB RespawnUpdate::triggerRevival and native 4AF79C..4AF92F.
// BF1 RespawnUpdate rule/condition helpers (9cbfb551) guide semantics;
// BFME2 layout from matched death helper4AF63E and native accesses.
#include "Code/Libraries/Include/Lib/Coord3D.h"
// ?triggerDeathBeforeRespawn@RespawnUpdate@@QAEXXZ @0x004AF63E 350B.
// RespawnUpdate death entry called by RespawnBody::apply. State 0 or 4
// looks the object's experience level up in the module-data rule tree at
// +0x10C (the same RespawnRule ctor the parser uses: cost 0 time 0 health
// 1.0 autoSpawn false). A miss retries level 1 and otherwise sleeps forever.
// A hit applies the +0x0C condition words, the death FX at +0xF0, the hero
// death UI, disabled-4, effectively-dead, and status 3, then copies the
// rule into this module. The controlling player's +0x738 table records the
// tracker's +0x28 into the slot chosen by the unrowed helper 0x0037F2C0.

enum DisabledType;
enum ObjectStatusTypes;

enum UpdateSleepTime
{
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

class Object
{
public:
	void rva001E431E(const int *conditions);
 ExitInterface *getObjectExitInterface() const;
 __forceinline const Coord3D *getPosition() const {return &m_position;}
	void setDisabled(DisabledType type);
	void setEffectivelyDead(bool dead);
	void setStatus(ObjectStatusTypes bit, bool flag);
	Player *getControllingPlayer() const;

	char m_pad00[0x38];Coord3D m_position;char m_pad44[0x254-0x44];BodyModuleInterface *m_body;char m_pad258[0xC];
	ExperienceTracker *m_experienceTracker;
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class InGameUI
{
public:
	void rva002A1283(Object *obj);
 void rva002A123F(Object *obj);void rva002A1261(Object *obj);
};

extern InGameUI *TheInGameUI;

struct RespawnRule
{
	unsigned level;
	unsigned cost;
	int time;
	float health;
	bool autoSpawn;

	RespawnRule(unsigned ruleLevel)
		: level(ruleLevel), cost(0), time(0), health(1.0f), autoSpawn(false) {}
 RespawnRule() {}
};

class BFME2RespawnRuleTree
{
public:
	void *find(const unsigned int &key) const;
	void *sentinel;
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

class RespawnUpdateModuleData
{
public:
	char m_pad00[0x0C];
	int m_conditions0C[19];
	int m_conditions58[19];
	int m_conditionsA4[19];
	const FXList *m_fx;
	const FXList *m_reviveFX;const FXList *m_initialFX;unsigned atFC;unsigned m_reviveTime;unsigned m_initialTime;unsigned at108;
	BFME2RespawnRuleTree m_rules;
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


class ExitInterface { public:
 virtual void slot0()=0;virtual void slot1()=0;virtual void slot2()=0;virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;virtual void slot7()=0;virtual void slot8()=0;
 virtual void getExitPosition(Coord3D *,bool)=0;
};
class BodyModuleInterface { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void setInitialHealth(float,bool)=0;
};
class PlayerList {public:__forceinline Player *getLocalPlayer() const{return local;}char pad[0x10];Player *local;};
extern PlayerList *ThePlayerList;
class ControlBar {public:char pad[0x28];bool dirty;};extern ControlBar *TheControlBar;
void RespawnUpdate::triggerRevival(Object *at) {
 Object *obj=m_object;
 const RespawnUpdateModuleData *data=m_moduleData;
 Coord3D pos={at->getPosition()->x,at->getPosition()->y,at->getPosition()->z};
 ExitInterface *exit=at->getObjectExitInterface();
 if(exit) exit->getExitPosition(&pos,true);
 unsigned time;
 if(m_41) {
  obj->rva001E431E(data->m_conditionsA4);
  time=data->m_initialTime;
  FXList::doFXObj(data->m_initialFX,obj,0);
  if(TheInGameUI) TheInGameUI->rva002A123F(obj);
 } else {
  obj->rva001E431E(data->m_conditions58);
  time=data->m_reviveTime;
  FXList::doFXObj(data->m_reviveFX,obj,0);
  if(TheInGameUI) TheInGameUI->rva002A1261(obj);
 }
 // Native loads the default health before clearing the two rule counters.
 static const float one=1.0f;
 RespawnRule rule;
 float health=*(const volatile float *)&one;rule.cost=0;rule.time=0;
 m_2C=4;
 rule.level=(unsigned)obj->m_experienceTracker->m_level;rule.health=health;rule.autoSpawn=false;
 RespawnRuleNode *found=(RespawnRuleNode*)data->m_rules.find(rule.level);
 RespawnRuleNode *end=(RespawnRuleNode*)data->m_rules.sentinel;
 if(found==end) {
  rule.RespawnRule::RespawnRule(1);
  found=(RespawnRuleNode*)data->m_rules.find(rule.level);
  if(found==end) {setWakeFrame(obj,UPDATE_SLEEP_FOREVER);return;}
 }
 m_20=*(float*)&found->m_healthBits;
 obj->m_body->setInitialHealth(m_20*100.0f,false);
 m_34=(unsigned)-1;m_38=(unsigned)-1;
 if(ThePlayerList->getLocalPlayer()==obj->getControllingPlayer()) TheControlBar->dirty=true;
 setWakeFrame(obj,(UpdateSleepTime)time);
}
