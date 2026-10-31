// cl: /I. /O1 /arch:SSE /G7 /MD /EHsc
// stlport
// EmotionTrackerUpdate::update, native 0x004B1633..0x004B1ECB (2200 B).
// WB 0x01230DD0 (EmotionTrackerUpdate::update) gives the name, the flow and the
// accessed fields; retail (patch 1.03) differs from WB in details. ECX is the
// update interface at module+0x10, so the module data and the tracked object
// sit at ECX-0xC/-8. Layouts below expose only the fields this body uses;
// offsets are native. Native scans the EmotionSystem ObjectIDs before the
// nested nugget eligibility scans.
// Evidence: reverse/attempt_support/0x004b1633-20261019-claude2.md,
// reverse/attempt_support/0x004b1633-20261020-w2/readme.md and
// reverse/attempt_support/emotiontracker-w5-20261020/readme.md.
#define _STLP_USE_STATIC_LIB

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"

#include <hash_map>
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectPtrHash &map = *reinterpret_cast<ObjectPtrHash *>(reinterpret_cast<char *>(this) + 0xB4);
	ObjectPtrHash::iterator it = map.find(id);
	if (it == map.end())
		return 0;
	return (*it).second;
}

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
enum ObjectStatusTypes {};
enum Relationship { REL_ENEMY = 0, REL_NEUTRAL = 1, REL_ALLY = 2 };

class Player
{
public:
	__forceinline int getPlayerIndex() const { return index; }
	char m_pad00[0x54];
	int index; // +0x54
};
class ThingTemplate {
public:
    bool isEquivalentTo(const ThingTemplate *) const;
    char pad[0x10b]; unsigned char flags10b;
    char pad10c[0x113-0x10c]; unsigned char flags113;
    char pad114[0x11a-0x114]; unsigned char flags11a;
};
class ExperienceTracker { public: char pad[0x24]; int level; };
class Object {
public:
    const Coord3D *getPosition() const { return &pos; }
    const ThingTemplate *getTemplate() const { return m_template; }
    ObjectID getID() const { return id; }
    bool status6() const { return (status94 & 0x40)!=0; }
    float rva00263763(const void *) const;
    int rva0028B511() const;
    bool testStatus(ObjectStatusTypes) const;
    Player *getControllingPlayer() const;
    Relationship getRelationship(const Object *) const;
    float getShroudClearingRange() const;
    char pad0[4]; ThingTemplate *m_template;
    char pad8[0x38-8]; Coord3D pos;
    char pad44[0x74-0x44]; ObjectID id;
    char pad78[0x94-0x78]; unsigned int status94;
    char pad98[0x264-0x98]; ExperienceTracker *m_tracker;
    char pad268[0x274-0x268]; Object *m_274;
    Object *getContainedBy() const { return m_274; }
    char pad278[0x454-0x278]; bool flag454;
    bool isEmotionTarget() const { return flag454; }
};
class Rva0028F326Owner { public: unsigned char rva0028F326(unsigned int, float); };
class Rva2225E0Filter
{
public:
	bool accepts(Object *, Player *);
	void *value; // +0x00
};
struct EmotionUpdateData {
    char pad0[8]; float range; int interval;
    char pad10[4]; Rva2225E0Filter filter14,filter18,filter1c;
    float range20,range24,probability;
    unsigned char flag2c; char pad2d[3]; int level30;
};
struct EmotionEntry { char pad0[4]; int kind; char pad8[4]; int duration; };
struct Rva004DD018Arg;
class EmotionNugget {
public:
    bool CanBeActivatedFor(int,int,Rva004DD018Arg *);
    void OnDeactivation();
    void OnActivation(Object *,int);
    int getType() const { return entry->kind; }
    char pad0[4]; EmotionEntry *entry;
};
class Emotion : public EmotionNugget { public: bool rva004DCEC4(); };

class Rva004DCC84 { public: void rva004DCC84(Object *,int); };

class EmotionTrackerUpdate;
// And's canonical owner is a call view. The native polymorphic prefix below
// uses the existing partition-filter providers (table BC26E0, +4 next link).
class PartitionFilter { public: PartitionFilter &And(PartitionFilter &); };
class Rva000421C8 {
public:
    Rva000421C8():next(0) {}
    virtual ~Rva000421C8() {}
    virtual bool allow(Object *) = 0;
    virtual int getPlayerMask();
    Rva000421C8 *next;
};

class EmotionModuleBase {
public:
    virtual ~EmotionModuleBase();
    Object *getObject() const { return m_object; }
    const EmotionUpdateData *getModuleData() const { return m_data; }
    EmotionUpdateData *getEmotionTrackerUpdateModuleData() const { return (EmotionUpdateData *)getModuleData(); }
    EmotionUpdateData *m_data;
    Object *m_object;
};
class EmotionBehaviorInterface { public: virtual void behaviorSlot0(); };
class EmotionUpdateInterface { public: virtual UpdateSleepTime update() = 0; };
class EmotionTrackerUpdate : public EmotionModuleBase, public EmotionBehaviorInterface, public EmotionUpdateInterface {
public:
    class TauntPointFilter;
    virtual UpdateSleepTime update();
    EmotionNugget *rva004B13D8();
    void PulseEmotion(int,void *,int);
    char pad14[0x24-0x14];
    bool flags[12];
    unsigned int expiry[12];
    ObjectID targetID[12];
    std::vector<EmotionNugget *> nuggets;
    EmotionNugget *active;
    int countdown;
    char pad94[0xa0-0x94];
    int forcedKind,forcedFrames;
    ObjectID forcedTarget;
    unsigned int nextFrame;
    bool foundLatch;
};
// The out-of-line constructor owns table C56520. This unit only needs its
// three-slot ABI and base cleanup; do not emit a second local table.
class __declspec(novtable) EmotionTrackerUpdate::TauntPointFilter:public Rva000421C8 {
public:
    TauntPointFilter(EmotionTrackerUpdate *);
    virtual bool allow(Object *);
    virtual int getPlayerMask();
    EmotionTrackerUpdate *module;
    Object *object;
    Player *player;
    int enemyCount,allyCount;
    Object *cached;
    bool tested;
    bool wasTested() const { return tested; }
};
// Native update stores C0719C and BF8FE4 for these two filters. Their slot-1
// providers and +8/+C/+10 fields are already recovered under these names.
class Rva00261513Filter:public Rva000421C8 {
public:
    Rva00261513Filter(Object *o,float r):object(o),flag(true),range(r) {}
    virtual bool allow(Object *);
    Object *object;
    bool flag;
    float range;
};
class Rva00261058:public Rva000421C8 {
public:
    Rva00261058(Player *p):player(p),flag(false) {}
    virtual bool allow(Object *);
    Player *player;
    bool flag;
};
class PlayerList { public: int getPlayersWithRelationship(int,unsigned int,bool); };
struct BfmePointFD;
class Rva00739830 { public: int rva00739830(const BfmePointFD *,int,unsigned int) const; };
class EmotionSystem { public: const _STL::vector<ObjectID> &getObjects() const { return objects; } char pad[0x24]; _STL::vector<ObjectID> objects; };
class GlobalData;
class TerrainLogic;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
class TerrainView {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual float height(float,float,int);
};
class DebugDrawView {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void va(); virtual void vb();
    virtual void circle(const Coord3D *,float,unsigned long);
};
extern GameLogic *TheGameLogic;
extern EmotionSystem *TheEmotionSystem;
extern GlobalData *TheWritableGlobalData;
extern TerrainLogic *TheTerrainLogic;
class View;
extern View *TheTacticalView;
extern PartitionManager *ThePartitionManager;
inline unsigned long GameMakeColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a) { return (a<<24)|(r<<16)|(g<<8)|b; }
extern PartitionManager *TheShroudManager;
extern PlayerList *ThePlayerList;
extern ThingFactory *TheThingFactory;
extern int BfmeLogicFramesPerSecond;
float GetGameLogicRandomValueReal(float,float,char *,int);


UpdateSleepTime EmotionTrackerUpdate::update()
{
    // Inert locals. cl breaks the operand-order tie of the second layer
    // compare (getObject()->rva0028B511()==other->rva0028B511(), native
    // +0x572) by symbol number: retail calls `other` first, which this body
    // reproduces with 29 to 35 more numbered locals (docs/recipes.md, "Local
    // count decides commutative operand order").
    int unused0 = 0, unused1 = 0, unused2 = 0, unused3 = 0, unused4 = 0, unused5 = 0, unused6 = 0, unused7 = 0, unused8 = 0, unused9 = 0, unused10 = 0, unused11 = 0, unused12 = 0, unused13 = 0, unused14 = 0, unused15 = 0, unused16 = 0, unused17 = 0, unused18 = 0, unused19 = 0, unused20 = 0, unused21 = 0, unused22 = 0, unused23 = 0, unused24 = 0, unused25 = 0, unused26 = 0, unused27 = 0, unused28 = 0;
    EmotionUpdateData *data=getEmotionTrackerUpdateModuleData();
    if(!data) return (UpdateSleepTime)0x3fffffff;
    Object *obj=getObject();
    if(!obj) return (UpdateSleepTime)0x3fffffff;
    if(obj->getContainedBy()) {
        if(active) {
            active->OnDeactivation();
            active=0;
        }
        return (UpdateSleepTime)1;
    }
    if(forcedFrames>0) --forcedFrames;
    if(*((unsigned char *)TheWritableGlobalData+0xe9c)) {
        Coord3D pos;
        pos.x=obj->pos.x; pos.y=obj->pos.y; pos.z=obj->pos.z;
        pos.z=((TerrainView *)TheTerrainLogic)->height(pos.x,pos.y,0);
        if(data->interval) ((DebugDrawView *)TheTacticalView)->circle(&pos,data->range,GameMakeColor(0,0,255,255));
        if(data->range20!=0.0f) ((DebugDrawView *)TheTacticalView)->circle(&pos,data->range20,GameMakeColor(0,255,255,255));
        if(data->range24!=0.0f) ((DebugDrawView *)TheTacticalView)->circle(&pos,data->range24,GameMakeColor(255,0,0,255));
    }
    Object *closest=0;
    float closestDist=3.402823466e+38f;
    --countdown;
    if(countdown<=0 && data->interval && forcedFrames==0) {
        countdown=data->interval;
        TauntPointFilter filter(this);
        Rva00261513Filter distance(obj,data->range);
        Rva00261058 player(obj->getControllingPlayer());
        ((PartitionFilter *)&filter)->And(*(PartitionFilter *)&distance);
        ((PartitionFilter *)&filter)->And(*(PartitionFilter *)&player);
        if(!obj->testStatus((ObjectStatusTypes)0x44))
            closest=ThePartitionManager->getClosestObject(obj->getPosition(),data->range,0,(Rva000421C8 *)&filter);
        if(!closest) {
            if(filter.wasTested()) {
                flags[9]=true; flags[3]=false; flags[0]=false;
            } else {
                flags[9]=false; flags[3]=false; flags[0]=false;
            }
        } else if(!data->filter1c.accepts(closest,0) &&
                  !data->filter14.accepts(closest,0) &&
                  !data->filter18.accepts(closest,0)) {
            flags[9]=false;
            flags[0]=true;
            flags[3]=false;
        } else {
            flags[9]=false;
            flags[0]=false;
            flags[3]=true;
            closestDist=obj->rva00263763(closest);
        }
    }
    Object *bestNeutral=0;
    Object *bestAlly=0;
    if((data->range20>0.0f || data->range24>0.0f) && forcedFrames==0) {
        bool found=false;
        int enemyCount=0,allyCount=0;
        Player *player=obj->getControllingPlayer();
        if(player) {
            unsigned allies=ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),3,false);
            unsigned enemies=ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(),4,false);
            enemyCount=((Rva00739830 *)TheShroudManager)->rva00739830(
                (const BfmePointFD *)getObject()->getPosition(),1,enemies);
            allyCount=((Rva00739830 *)TheShroudManager)->rva00739830(
                (const BfmePointFD *)getObject()->getPosition(),1,allies);
        }
        float shroudRange=obj->getShroudClearingRange();
        float shroudDist=shroudRange*shroudRange;
        if(shroudDist<closestDist) closestDist=shroudDist;
        float neutralDist=data->range20*data->range20;
        float allyDist=data->range24*data->range24;
        const _STL::vector<ObjectID> &objects=TheEmotionSystem->getObjects();
        for(_STL::vector<ObjectID>::const_iterator it=objects.begin();it!=objects.end();++it) {
            Object *other=TheGameLogic->findObjectByID(*it);
            if(!other || !other->isEmotionTarget()) continue;
            Relationship rel=obj->getRelationship(other);
            if((other->getTemplate()->flags11a & 1) &&
               (rel!=REL_ALLY || data->filter18.accepts(other,0))) {
                float dist=obj->rva00263763(other);
                if(dist<allyDist &&
                   (data->filter14.accepts(other,0) || data->filter18.accepts(other,0)) &&
                   ((Rva0028F326Owner *)obj)->rva0028F326((unsigned int)other,data->range24)) {
                    if(other->status6() ||
                       getObject()->rva0028B511()==other->rva0028B511()) {
                        std::vector<EmotionNugget *>::iterator n;
                        for(n=nuggets.begin();n!=nuggets.end();++n) {
                            EmotionNugget *nugget=*n;
                            if(nugget->getType()==4 && nugget->CanBeActivatedFor(enemyCount,allyCount,(Rva004DD018Arg *)other)) break;
                        }
                        if(n!=nuggets.end()) {
                            bestAlly=other;
                            allyDist=dist;
                            continue;
                        }
                    }
                }
                if(dist<closestDist &&
                   (data->filter14.accepts(other,0) || data->filter18.accepts(other,0) || data->filter1c.accepts(other,0)) &&
                   ((Rva0028F326Owner *)obj)->rva0028F326((unsigned int)other,obj->getShroudClearingRange())) {
                    std::vector<EmotionNugget *>::iterator n;
                    for(n=nuggets.begin();n!=nuggets.end();++n) {
                        EmotionNugget *nugget=*n;
                        if(nugget->getType()==3 && nugget->CanBeActivatedFor(enemyCount,allyCount,(Rva004DD018Arg *)other)) break;
                    }
                    if(n!=nuggets.end()) {
                        closest=other;
                        closestDist=dist;
                        if(other->status6() ||
                           getObject()->rva0028B511()==other->rva0028B511()) {
                            flags[0]=false;
                            flags[3]=true;
                        } else {
                            flags[0]=true;
                            flags[3]=false;
                        }
                    }
                }
            }
            if(other!=obj && (other->getTemplate()->flags113 & 4)) {
                const ThingTemplate *tmpl=TheThingFactory->findTemplate(AsciiString("NeutralGollum"));
                if(tmpl && tmpl->isEquivalentTo(other->getTemplate())) continue;
                if(rel==REL_ALLY) {
                    float dist=obj->rva00263763(other);
                    if(dist<neutralDist &&
                       ((Rva0028F326Owner *)obj)->rva0028F326((unsigned int)other,data->range20)) {
                        bestNeutral=other;
                        neutralDist=dist;
                        found=true;
                    }
                }
            }
        }
        if(!found) foundLatch=false;
        unsigned frame=TheGameLogic->getFrame();
        if(frame>nextFrame && bestNeutral && !foundLatch) {
            nextFrame=frame+BfmeLogicFramesPerSecond*0x3c;
            flags[2]=true;
            foundLatch=true;
        } else flags[2]=false;
        if(!flags[4] || targetID[4]==0 || frame>expiry[4]) flags[4]=(bestAlly!=0);
    }
    if(!obj->testStatus((ObjectStatusTypes)0x46) &&
       GetGameLogicRandomValueReal(0.0f,1.0f,
           "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\EmotionTrackerUpdate.cpp",0x25e)<data->probability &&
       obj->rva0028B511()==1)
        PulseEmotion(8,0,1);
    EmotionNugget *selected=rva004B13D8();
    bool changed=false;
    if(selected && closest && (selected->getType()==0 || selected->getType()==3) &&
       closest->getID()!=targetID[selected->getType()]) {
        Object *oldObj=TheGameLogic->findObjectByID(targetID[selected->getType()]);
        Object *newObj=TheGameLogic->findObjectByID(closest->getID());
        if(oldObj && oldObj->getContainedBy()) oldObj=oldObj->getContainedBy();
        if(newObj && newObj->getContainedBy()) newObj=newObj->getContainedBy();
        if(oldObj!=newObj) changed=true;
    }
    if(selected==active && !changed) {
        if(active && !((Emotion *)active)->rva004DCEC4()) {
            active->OnDeactivation();
            active=0;
        }
    } else {
        if(active) active->OnDeactivation();
        active=selected;
        if(active) {
            if(active->getType()==0 || active->getType()==3) {
                if(closest) targetID[active->getType()]=closest->getID();
            } else if(active->getType()==2) {
                if(bestNeutral) targetID[2]=bestNeutral->getID();
            } else if(active->getType()==4) {
                if(bestAlly) targetID[4]=bestAlly->getID();
            }
            if(forcedFrames>0)
                active->OnActivation(TheGameLogic->findObjectByID(forcedTarget),forcedFrames);
            else
                active->OnActivation(TheGameLogic->findObjectByID(targetID[active->getType()]),0);
        }
    }
    for(int i=0;i<12;++i) {
        if(expiry[i] && TheGameLogic->getFrame()>=expiry[i]) {
            flags[i]=false;
            expiry[i]=0;
        }
    }
    return (UpdateSleepTime)1;
}
