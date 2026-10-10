// cl: /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include/Lib
// ZH OCLSpecialPower.cpp at BF1 2f243e26d is the semantic guide.
// Target WB125D170 proves OCL selection; data ctor4C32BC proves7C/88 offsets.
// Retail folds this science-controlled 32-bit selection with CashHack's amount
// selection (WB125B670 selector / WB125B700 action4C26D0). The word payload is a pointer in OCL
// and an unsigned amount in CashHack. This neutral owner records their common
// ABI and access pattern without giving the folded address a second real name.
// Word-view layout is a structural reconciliation: Module data4/Object8,
// vector7C..88, fallback88; source semantic guides remain the distinct ZH
// findOCL and findAmountToSteal methods. No shared target class is asserted.
// Target OCL interface is +10; Module data4/Object8 and Behavior interfaceC
// are also used by the verified SpecialPowerModuleDo.cpp. ZH doSpecialPower
// is the semantic guide; BFME2 removes the disabled check and angle argument.
#include "Coord3D.h"
class ObjectCreationList;
enum ScienceType { SCIENCE_INVALID = -1 };
class Player { public: bool hasScience(ScienceType)const; };

struct Rva004C31A8ScienceWord { ScienceType science; unsigned value; };
struct Rva004C31A8DataWords {
 char prefix[0x7C];
 Rva004C31A8ScienceWord *begin,*end,*capacity;
 unsigned fallback;
};

template<int N> class BitFlags {public:bool any()const;};
class Object {char pad[0x38];public:Coord3D pos;Player *getControllingPlayer()const;};
class ObjectCreationList {public:void create(void*,void*,void*,void*,int);};
int __cdecl Rva004C30BC(ObjectCreationList*,void*,void*);
class Module {public:virtual ~Module();protected:Rva004C31A8DataWords *m_data;};
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
class Rva004C31A8ScienceSelector { public: unsigned select() const; private: void *vtable; Rva004C31A8DataWords *m_data; Object *m_object; };
class OCLSpecialPower:public SpecialPowerModule {protected:
 
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
 ObjectCreationList *ocl=reinterpret_cast<ObjectCreationList*>(((const Rva004C31A8ScienceSelector*)this)->select());
 if(ocl) ocl->create(m_object,&coord,0,0,0);
}
bool OCLSpecialPower::rva0049466D(const Coord3D *loc)
{
 if(((const BitFlags<11>*)((const char*)m_object+0x1C8))->any()) return false;
 unsigned char ready=1;
 ObjectCreationList *ocl=reinterpret_cast<ObjectCreationList*>(((const Rva004C31A8ScienceSelector*)this)->select());
 if(ocl && loc && m_object) ready=(unsigned char)Rva004C30BC(ocl,m_object,(void*)loc);
 return ready && SpecialPowerModule::rva0049466D(loc);
}

unsigned Rva004C31A8ScienceSelector::select()const
{
 const Rva004C31A8DataWords *data=m_data;
 Player *player=m_object->getControllingPlayer();
 if(player) {
  for(const Rva004C31A8ScienceWord *entry=data->begin;entry!=data->end;++entry)
   if(player->hasScience(entry->science)) return entry->value;
 }
 return data->fallback;
}
