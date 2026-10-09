// cl: /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include/Lib
// ZH OCLSpecialPower.cpp at BF1 2f243e26d is the semantic guide.
// Target WB125D170 proves selection; data ctor4C32BC proves7C/88 offsets.
// Target OCL interface is +10; Module data4/Object8 and Behavior interfaceC
// are also used by the verified SpecialPowerModuleDo.cpp. ZH doSpecialPower
// is the semantic guide; BFME2 removes the disabled check and angle argument.
#include "Coord3D.h"
class ObjectCreationList;
enum ScienceType { SCIENCE_INVALID = -1 };
class Player { public: bool hasScience(ScienceType)const; };

struct OCLScienceEntry { ScienceType science; const ObjectCreationList *value; };
struct OCLSpecialPowerDataView {
 char prefix[0x7C];
 OCLScienceEntry *begin,*end,*capacity;
 const ObjectCreationList *fallback;
};

template<int N> class BitFlags {public:bool any()const;};
class Object {char pad[0x38];public:Coord3D pos;Player *getControllingPlayer()const;};
class ObjectCreationList {public:void create(void*,void*,void*,void*,int);};
int __cdecl Rva004C30BC(ObjectCreationList*,void*,void*);
class Module {public:virtual ~Module();protected:OCLSpecialPowerDataView *m_data;};
class ObjectModule:public Module {protected:Object *m_object;};
class BehaviorModuleInterface {public:virtual void behaviorSlot0();};
class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {};
class SpecialPowerModuleInterface {public:
 virtual void doSpecialPower(unsigned)=0;
 virtual void doSpecialPowerAtObject(Object*,unsigned)=0;
 virtual void doSpecialPowerAtLocation(const Coord3D*,unsigned)=0;
 virtual bool rva0049466D(const Coord3D*)=0;
};
class SpecialPowerModule:public BehaviorModule,public SpecialPowerModuleInterface {public:
 virtual void doSpecialPower(unsigned);
 virtual void doSpecialPowerAtObject(Object*,unsigned);
 virtual void doSpecialPowerAtLocation(const Coord3D*,unsigned);
 virtual bool rva0049466D(const Coord3D*);
};
class OCLSpecialPower:public SpecialPowerModule {protected:
 const ObjectCreationList *findOCL()const;
public:
 virtual void doSpecialPower(unsigned);
 virtual bool rva0049466D(const Coord3D*);
};
void OCLSpecialPower::doSpecialPower(unsigned flags)
{
 Coord3D coord;
 const Coord3D *pos=&m_object->pos;
 coord.x=pos->x;coord.y=pos->y;coord.z=pos->z;
 SpecialPowerModule::doSpecialPowerAtLocation(&coord,flags);
 ObjectCreationList *ocl=const_cast<ObjectCreationList*>(findOCL());
 if(ocl) ocl->create(m_object,&coord,0,0,0);
}
bool OCLSpecialPower::rva0049466D(const Coord3D *loc)
{
 if(((const BitFlags<11>*)((const char*)m_object+0x1C8))->any()) return false;
 unsigned char ready=1;
 ObjectCreationList *ocl=const_cast<ObjectCreationList*>(findOCL());
 if(ocl && loc && m_object) ready=(unsigned char)Rva004C30BC(ocl,m_object,(void*)loc);
 return ready && SpecialPowerModule::rva0049466D(loc);
}

const ObjectCreationList *OCLSpecialPower::findOCL()const
{
 const OCLSpecialPowerDataView *data=m_data;
 Player *player=m_object->getControllingPlayer();
 if(player) {
  for(const OCLScienceEntry *entry=data->begin;entry!=data->end;++entry)
   if(player->hasScience(entry->science)) return entry->value;
 }
 return data->fallback;
}
