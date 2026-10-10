// ?update@StealthDetectorUpdate@@UAE?AW4UpdateSleepTime@@XZ
// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /I. /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// StealthDetectorUpdate native 004A2D93..004A33BE; Zero Hour update is the semantic lead.
// Native module constructor/name/field table establish ownership; native accesses below supply offsets.
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "GameLogic/ContainmentListView.h"
class Player; class Object;extern PartitionManager *ThePartitionManager;
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a
// player, +0x0C whether a hit allows.
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D; the out-of-line ctor 0x00261058.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);	// 0x00261058
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00C0719C, allow 0x00261513: +0x08 an object, +0x0C a flag,
// +0x10 a float.
class Rva00261513Filter : public Rva000421C8
{
public:
	Rva00261513Filter(const Object *obj, bool flag, float value)
		: m_obj(obj), m_flag(flag), m_value(value) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	bool m_flag;
	float m_value;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C
// relationship flags, +0x10 whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// The 224-bit KindOf mask; the (unused, bit, bit) constructor is 0x0006EE7A.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit1, int bit2) throw();	// 0x0006EE7A
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
enum UpdateSleepTime{UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff};
enum Relationship{ENEMIES,NEUTRAL,ALLIES};
enum CellShroudStatus{SHROUD_CLEAR=0};
enum ObjectStatusTypes{STATUS_DUMMY=-1};enum KindOfType{KIND_DUMMY=-1};class Module;
enum NameKeyType{NAMEKEY_INVALID=0};
class NameKeyGenerator{public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator *TheNameKeyGenerator;
class SpecialDisguiseUpdate{public:void rva004B05F5(bool);};
class Rva00373EC6{public:void rva00374815(); char pad[0x31];bool oneRing;};
class StealthUpdate{public:void markAsDetected(unsigned,int,Object*,bool);};
class Matrix3D;
class Drawable{public:int getPristineBonePositions(const char*,int,Coord3D*,Matrix3D*,int,int) const;char pad[0x358];float opacity;};
class Thing{public:Drawable *getDrawable() const;};
class ParticleSystemTemplate;
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12{public:void rva0004CBC0() throw();};
class BfmeParticleSystemHandle{public:__forceinline ~BfmeParticleSystemHandle(){if(m_system)((RvaSmartPtr12*)this)->rva0004CBC0();}ParticleSystem *m_system;void *m_prev,*m_next;
 operator bool()const{return m_system!=0;}ParticleSystem *operator->()const{return m_system?m_system:Make001FCBD7();}};
class ParticleSystemManager{public: BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate*,bool);};
extern ParticleSystemManager *TheParticleSystemManager;
struct Rva001F3899Arg{float x,y,z;};class Rva001F3899Slot{public:void set(const Rva001F3899Arg&);};
class Rva0055A88BDwordField;class Rva001F3C20Slot{public:void set(const Rva0055A88BDwordField*);};
struct Rva001F3C43Arg;class Rva001F3C43Slot{public:void set(const Rva001F3C43Arg*);};
class Rva002D9C2F{public:OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4&);};
class Rva002D9531{public:void rva002D9531(int);};
template<int N>class Slots:public Slots<N-1>{public:virtual void slot(char(*)[N])=0;};template<>class Slots<0>{};
class AudioManager:public Slots<25>{public:virtual int addAudioEvent(const BfmeAudioEventPrefix136*);};extern AudioManager *TheAudio;
class ContainModuleInterface:public Slots<4>{public:virtual bool isGarrisonable();};
class ContainListInterface:public Slots<70>{public:virtual Rva0036AE51ListView rva70();virtual void gap71();virtual void gap72();virtual int getStealthUnitsContained();};
class UpgradeTemplate;class UpgradeCenter{public:const UpgradeTemplate *findUpgrade(const AsciiString&)const;};extern UpgradeCenter *TheUpgradeCenter;
class Player{public:char pad[0x54];int m_index;};class PlayerList{public:char pad[0x10];Player *m_local;};extern PlayerList *ThePlayerList;
class Rva00439E0C{public:void rva00439E0C(Object*,int,int,int);};extern GameLogic *TheGameLogic;
class Object{public:bool testStatus(ObjectStatusTypes) const;bool isKindOf(KindOfType) const;bool rva00290D2B(const UpgradeTemplate*) const;float getVisionRange()const;
 int rva0028F4EF();int rva002933CD();Rva00373EC6 *rva0028F4BC();protected:Module *findModule(NameKeyType)const;friend class StealthDetectorUpdate;public:
 Player *getControllingPlayer()const;Relationship getRelationship(const Object*)const;CellShroudStatus getShroudStatusForPlayer(int) const;
 char pad[0x38];Coord3D m_pos;char pad44[0x74-0x44];ObjectID m_id;char pad78[0x250-0x78];ContainModuleInterface *m_contain;
 char pad254[0x274-0x254];Object *m_container;char pad278[0x438-0x278];unsigned char m_privateStatus;unsigned char m_pad439[0x43C-0x439];
 bool isEffectivelyDead()const{return (m_privateStatus&1)!=0;}
};
struct StealthDetectorUpdateModuleData{char pad[8];int m_rate;float m_range;bool initiallyDisabled;OpaqueRefElement4 m_sound,m_loud;const ParticleSystemTemplate *m_beacon,*m_ping,*m_bright,*m_grid;AsciiString m_bone;BfmeFixedStorage0004543D m_require,m_forbid;bool m_garrison,m_transport,m_cancelRing;AsciiString m_upgrade;};
class DetectorPrimary{public:virtual void primary();const StealthDetectorUpdateModuleData *m_data;Object *m_object;};
class DetectorOther{public:virtual void other();};class UpdateModuleInterface{public:virtual UpdateSleepTime update()=0;};
class StealthDetectorUpdate:public DetectorPrimary,public DetectorOther,public UpdateModuleInterface{public:virtual UpdateSleepTime update();Object *getObject()const{return m_object;}};
UpdateSleepTime StealthDetectorUpdate::update(){
 const StealthDetectorUpdateModuleData *data=m_data;Object *self=getObject();
 if(self->testStatus((ObjectStatusTypes)0x58))return UPDATE_SLEEP_NONE;
 if(self->isEffectivelyDead())return UPDATE_SLEEP_FOREVER;
 if(self->testStatus((ObjectStatusTypes)2))return UPDATE_SLEEP_NONE;
 if(self->testStatus((ObjectStatusTypes)0x13))return UPDATE_SLEEP_FOREVER;
 Object *containedBy=self->m_container;
 if(containedBy){ContainModuleInterface *contain=containedBy->m_contain;if(contain){if(contain->isGarrisonable()){if(!data->m_garrison)return (UpdateSleepTime)data->m_rate;}else if(!data->m_transport)return (UpdateSleepTime)data->m_rate;}}
 if(data->m_upgrade.compare(AsciiString::TheEmptyString)!=0){const UpgradeTemplate *upgrade=TheUpgradeCenter->findUpgrade(data->m_upgrade);if(!upgrade||!self->rva00290D2B(upgrade))return UPDATE_SLEEP_NONE;}
 float range=self->getVisionRange();if(data->m_range>0.0f)range=data->m_range;
 bool foundSomeone=false;
 BfmeWideResult iter=ThePartitionManager->iterateObjectsInRange(&self->m_pos,range,0,
  Rva00260EB1Filter(self,3,false).link(Rva0004584D(data->m_require,data->m_forbid).link(Rva00261513Filter(self,true,range).link(&Rva002611BFFilter(getObject())))),0);
 for(Object *them=iter.next();them;them=iter.next()){
  if(them->isEffectivelyDead())continue;
  bool forceUnstealth;
  if(them->rva0028F4EF()==2&&!them->isKindOf((KindOfType)0x12c))forceUnstealth=false;else forceUnstealth=true;
  if(them->isKindOf((KindOfType)0x12c)){static NameKeyType key_SpecialDisguiseUpdate=TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");SpecialDisguiseUpdate *disguise=(SpecialDisguiseUpdate*)them->findModule(key_SpecialDisguiseUpdate);if(disguise)disguise->rva004B05F5(false);}
  if(forceUnstealth&&!(unsigned char)them->rva002933CD()&&!them->testStatus((ObjectStatusTypes)0x11))forceUnstealth=false;else forceUnstealth=true;
  TheGameLogic->getManager178()->rva00439E0C(them,(int)self,data->m_rate+1,2);
  StealthUpdate *stealth=(StealthUpdate*)them->rva0028F4BC();
  if(stealth&&them->testStatus((ObjectStatusTypes)0x12)){
   foundSomeone=true;stealth->markAsDetected(data->m_rate+1,2,self,true);
   if(data->m_cancelRing&&((Rva00373EC6*)stealth)->oneRing)((Rva00373EC6*)stealth)->rva00374815();
   if(data->m_grid){BfmeParticleSystemHandle sys=TheParticleSystemManager->createParticleSystem(data->m_grid,true);
    if(sys){Coord3D gridPosition;gridPosition.x=them->m_pos.x;gridPosition.y=them->m_pos.y;gridPosition.z=them->m_pos.z;gridPosition.z=self->m_pos.z+17.0f;gridPosition.x-=((int)gridPosition.x)%12;gridPosition.y-=((int)gridPosition.y)%12;((Rva001F3899Slot*)sys.m_system)->set(*(const Rva001F3899Arg*)&gridPosition);}}
  }else{ContainModuleInterface *contain=them->m_contain;if(contain&&contain->isGarrisonable()&&((ContainListInterface*)contain)->getStealthUnitsContained()){
   Rva0036AE51ListView view=((ContainListInterface*)contain)->rva70();
   for(ContainmentList::const_iterator item=view.b->begin();item!=view.b->end();++item){Object *rider=(Object*)containmentFirstWord(*item);StealthUpdate *riderStealth=(StealthUpdate*)rider->rva0028F4BC();if(riderStealth){foundSomeone=true;if(self->getControllingPlayer()!=rider->getControllingPlayer()&&self->getRelationship(rider)!=ALLIES){riderStealth->markAsDetected(data->m_rate+2,2,self,true);TheGameLogic->getManager178()->rva00439E0C(rider,(int)self,data->m_rate+2,2);}}}
  }}
  if(!forceUnstealth){Drawable *draw=((Thing*)them)->getDrawable();if(draw)draw->opacity=1.0f;}
 }
 if(data->m_grid&&self->getShroudStatusForPlayer(ThePlayerList->m_local->m_index)<=2){
  Drawable *draw=((Thing*)self)->getDrawable();Coord3D bone;bone.x=-1.66f;bone.y=5.5f;bone.z=15.0f;if(draw)draw->getPristineBonePositions(data->m_bone.str(),0,&bone,0,1,0);
  const ParticleSystemTemplate *ping=foundSomeone?data->m_bright:data->m_ping;
  if(ping){BfmeParticleSystemHandle sys=TheParticleSystemManager->createParticleSystem(ping,true);if(sys){if(draw)((Rva001F3C20Slot*)sys.m_system)->set((const Rva0055A88BDwordField*)draw);else ((Rva001F3C43Slot*)sys.m_system)->set((const Rva001F3C43Arg*)self);((Rva001F3899Slot*)sys.operator->())->set(*(const Rva001F3899Arg*)&bone);}}
  if(data->m_beacon){BfmeParticleSystemHandle sys=TheParticleSystemManager->createParticleSystem(data->m_beacon,true);if(sys){if(draw)((Rva001F3C20Slot*)sys.m_system)->set((const Rva0055A88BDwordField*)draw);else ((Rva001F3C43Slot*)sys.m_system)->set((const Rva001F3C43Arg*)self);((Rva001F3899Slot*)sys.operator->())->set(*(const Rva001F3899Arg*)&bone);}}
  // Native temporary cleanup conditionally releases the referent; use the
  // shared empty reference holder rather than a string-destructor alias.
  BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4*)&BfmePoolRef08(),0);if(foundSomeone)((Rva002D9C2F*)&sound)->rva002D9C2F(data->m_loud);else ((Rva002D9C2F*)&sound)->rva002D9C2F(data->m_sound);((Rva002D9531*)&sound)->rva002D9531(self->m_id);TheAudio->addAudioEvent(&sound);
 }
 // A compiled-out string local reproduces the retail EH state map and
 // saved secondary receiver home. This source shape is a codegen inference.
 if (0) { AsciiString unused; }
 return (UpdateSleepTime)data->m_rate;
}
