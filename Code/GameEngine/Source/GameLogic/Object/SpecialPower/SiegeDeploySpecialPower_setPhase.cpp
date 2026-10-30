// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /ICode/Libraries/Include /ICode/GameEngine/Source/Common /Ireference/shims/bfmealloc /I. /ICode/GameEngine/Include/GameLogic
// stlport
enum NameKeyType { NAMEKEY_INVALID = 0 };
typedef unsigned int UnsignedInt;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
#include "Lib/Coord3D.h"
#include "Lib/Coord3DBase.h"
// ?setPhase@SiegeDeploySpecialPower@@AAEXH@Z
// stlport
// WB1264270 is the semantic guide for SiegeDeploySpecialPower::setPhase.
// Retail4C5BE3 proves primary this, phase38/frame3C/target40 and Object condition offsets.
#include "ContainmentListView.h"
#include "GameLogicObjectLookupView.h"
namespace _STL {
template<class T,class Traits> static inline bool operator!=(const _List_iterator<T,Traits>&a,const _List_iterator<T,Traits>&b){return a._M_node!=b._M_node;}
template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();
}
enum ObjectStatusTypes { STATUS_ZERO=0 };

enum CommandSourceType { SOURCE_ZERO=0 };
enum AttitudeType { ATTITUDE_ZERO=0 };
class Object;
class Rva001E46E1 {public:void rva001E53D8(float,Object*);};
struct Rva0028AC4EEntry;
class Module;
struct Coord3D;
class DynamicPortalBehaviour
{
public:
	static Module *rva004608E0(Object *obj);
	void rva0046094C();
	void createWaypoints();
	bool IsEndPortalAboveWall(Coord3D *pos);
};
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiEvacuate(bool,CommandSourceType);
	void aiExit(Object*,CommandSourceType);
	void rva0045003E(int arg, CommandSourceType cmdSource);
	void aiFacePosition(const Coord3D *pos, int cmdSource);
};
class AIUpdateInterfaceHead
{
	unsigned char m_pad00[0x20];
};
class AIUpdateInterface : public AIUpdateInterfaceHead, public AICommandInterface
{
public:
    void ignoreObstacle(const Object *obj);
    AttitudeType getAttitude() const;
    void rva0026DE3B(int);
};
template<int N> class SiegePhaseSlots : public SiegePhaseSlots<N-1> {public:virtual void gap(char(*)[N])=0;};
template<> class SiegePhaseSlots<0> {};
class SiegePhaseContain : public SiegePhaseSlots<70> {public:virtual Rva0036AE51ListView slot70()=0;virtual Rva0036AE51ListView slot71()=0;};

struct Rva004598F2Point
{
public:
	Rva004598F2Point() {}
	Rva004598F2Point(const Rva004598F2Point &other) : x(other.x), y(other.y), z(other.z) {}
	Rva004598F2Point(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
};
enum DisabledType { DISABLED_ZERO=0 };
struct Rva0028AC4EEntry;
class SiegePhaseContain;
class AIUpdateInterface;
struct SiegePhaseConditions {unsigned words[19];__forceinline unsigned test(int i)const{return words[i>>5]&(1u<<(i&31));}__forceinline void set(int i){words[i>>5]|=1u<<(i&31);}__forceinline void clear(int i){words[i>>5]&=~(1u<<(i&31));}};
class Object
{
	friend class SiegeDeploySpecialPower;
public:
	void setStatus(ObjectStatusTypes bit, bool flag);
    void setDisabledUntil(DisabledType, unsigned);
    void rva0028AE6D();
    const Rva0028AC4EEntry *rva0028AC4E() const;
	const Rva004598F2Point *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x08];
	float m_xAxis;
	unsigned char m_pad0C[0x18 - 0x0C];
	float m_yAxis;
	unsigned char m_pad1C[0x28 - 0x1C];
	float m_zAxis;
	unsigned char m_pad2C[0x38 - 0x2C];
	Rva004598F2Point m_position;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad78[0x10C - 0x78];
    SiegePhaseConditions conditions; // +0x10C
    unsigned char m_pad158[0x250 - 0x158];
    SiegePhaseContain *contain; // +0x250
    unsigned char m_pad254[4];
	AIUpdateInterface *m_ai;
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
};
struct SiegeDeployModuleDataView
{
public:
	char m_pad00[0x18];
    unsigned int m_delay; // +0x18
    unsigned int m_disabledDuration; // +0x1C
    bool m_evacuate; // +0x20
    bool m_exit; // +0x21
	bool m_noAdjust; // +0x22
	char m_pad23[0x1];
	float m_searchRadius; // +0x24 +0x24
	float m_pushDistance; // +0x28 +0x28
	float m_approachScale; // +0x2C
};
extern GameLogic *TheGameLogic;
#include "../../../../Include/Common/ObjectModule.h"

class SpecialPowerTemplate;
class Waypoint;
struct BehaviorModuleInterface { virtual void f0C(); };
struct UpdateModuleInterface
{
    virtual void f10();
    virtual void u1();
    virtual void u2();
    virtual void u3();
    virtual void u4();
    virtual void u5();
    virtual void u6();
    virtual void u7();
    virtual void u8();
    virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
    virtual ~UpdateModule();
    void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
    unsigned int m_14;
    int m_18;
    int m_1C;
};
class SpecialPowerUpdateInterface
{
public:
    virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
        const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way) = 0;
    virtual void gap1();
    virtual bool rva004C575F();
};
class SpecialPowerStopInterface
{
public:
    virtual void gap0() = 0;
    virtual bool rva004C5751() = 0;
    virtual void gap2() = 0;
    virtual void gap3() = 0;
    virtual void gap4() = 0;
    virtual void gap5() = 0;
    virtual void gap6() = 0;
    virtual void gap7() = 0;
    virtual void gap8() = 0;
    virtual void gap9() = 0;
    virtual void gap10() = 0;
    virtual void gap11() = 0;
    virtual void gap12() = 0;
    virtual void gap13() = 0;
    virtual void gap14() = 0;
    virtual void gap15() = 0;
    virtual void gap16() = 0;
    virtual void stopSpecialPower() = 0;
};
class WeaponModeSpecialPowerUpdateBase : public UpdateModule,
    public SpecialPowerUpdateInterface, public SpecialPowerStopInterface
{
public:
    WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);
protected:
    unsigned int m_28;
    int m_2C;
    unsigned int m_30;
    float m_34;
};
class SiegeDeploySpecialPower : public WeaponModeSpecialPowerUpdateBase
{
public:
    SiegeDeploySpecialPower(Thing *thing, const ModuleData *moduleData);
    virtual ~SiegeDeploySpecialPower();
    virtual NameKeyType getModuleNameKey() const;
    virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
        const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way);
    virtual bool rva004C575F();
    virtual bool rva004C5751();
    virtual void stopSpecialPower();
    virtual UpdateSleepTime update();
    Rva004598F2Point computeApproachPoint(Object *target, Rva004598F2Point *dockPosition, bool *docked) throw();
    void rva004C5E62();
    void rva004C573C();
private:
    void setPhase(int state);
    const SiegeDeployModuleDataView *data() const { return (const SiegeDeployModuleDataView *)m_moduleData; }
    int m_phase; // +0x38
    unsigned int m_frame; // +0x3C
    ObjectID m_dockID; // +0x40
    ObjectID m_44; // +0x44
    Coord3DBase m_48; // +0x48
    Rva004598F2Point m_approachPoint; // +0x54
    bool m_docked; // +0x60
    unsigned char m_pad61[3];
    Rva004598F2Point m_dockPosition; // +0x64
    bool m_stop; // +0x70
};
// WorldBuilder SiegeDeploySpecialPower::setPhase, WB VA 0x01264270 (callgraph lead, score 1).
void SiegeDeploySpecialPower::setPhase(int next)
{
 if(next==m_phase)return;
 Object *obj=m_object;
 switch(m_phase){
 case 2:if(obj->conditions.test(96)){obj->conditions.clear(96);obj->rva0028AE6D();}break;
 case 3:obj->setStatus((ObjectStatusTypes)59,false);if(obj->conditions.test(100)){obj->conditions.clear(100);obj->rva0028AE6D();}rva004C573C();break;
 case 4:m_dockID=INVALID_OBJECT_ID;if(obj->conditions.test(94)){obj->conditions.clear(94);obj->rva0028AE6D();}break;
 }
 m_phase=next;m_frame=0;
 switch(m_phase){
 case 2:{
  if(!obj->conditions.test(96)){obj->conditions.set(96);obj->rva0028AE6D();}
  if(obj->rva0028AC4E())((Rva001E46E1*)obj->rva0028AC4E())->rva001E53D8(0.0f,obj);
  SiegePhaseContain *contained=obj->contain;
  if(contained){Rva0036AE51ListView view=contained->slot70();for(ContainmentList::iterator it=view.b->begin();it!=view.b->end();++it){Object *child=(Object*)containmentFirstWord(*it);if(!child->conditions.test(96)){child->conditions.set(96);child->rva0028AE6D();}}}
  break;}
 case 3:
  obj->setStatus((ObjectStatusTypes)59,true);
  if(!obj->conditions.test(100)){obj->conditions.set(100);obj->rva0028AE6D();}
  if(obj->conditions.test(61)){obj->conditions.clear(61);obj->rva0028AE6D();}
  {Module *portal=DynamicPortalBehaviour::rva004608E0(obj);if(portal)((DynamicPortalBehaviour*)portal)->createWaypoints();}
  if(data()->m_evacuate){AIUpdateInterface *ai=obj->m_ai;if(ai)ai->aiEvacuate(0,(CommandSourceType)2);}
  if(data()->m_exit){SiegePhaseContain *contain=m_object->contain;if(contain){ContainmentList list=contain->slot71().rva0036AE51();for(ContainmentList::iterator it=list.begin();it!=list.end();++it){Object *child=(Object*)containmentFirstWord(*it);AIUpdateInterface *ai=child->m_ai;if(ai){ai->rva0026DE3B((m_object->m_ai?m_object->m_ai:m_object->m_ai)->getAttitude());Object *owner=m_object;(child->m_ai?child->m_ai:child->m_ai)->aiExit(owner,(CommandSourceType)2);}}}}
  break;
 case 4:
  if(!obj->conditions.test(94)){obj->conditions.set(94);obj->rva0028AE6D();}
  obj->setDisabledUntil((DisabledType)8,TheGameLogic->getFrame()+data()->m_disabledDuration);break;
 }
}
