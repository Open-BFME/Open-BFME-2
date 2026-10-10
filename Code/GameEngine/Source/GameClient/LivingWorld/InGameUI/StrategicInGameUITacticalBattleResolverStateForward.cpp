// cl: /O1 /G7 /MD /EHsc
// TacticalBattleResolver constructor family and state forwarder.
// Native ctor boundaries: 5D1064..5D10B0/76, 5D1175..5D1210/155,
// 5D1296..5D12E3/77. WB15BB8A0/15BBB70/15BBE90 identify the family;
// address-derived owners retain uncertainty about the exact source names.
// Retail/owned destructors establish base8, owning view4 and Impl12.
// The two state branches separately hand their new state to the owned
// reset worker, preserving native MOV ECX then PUSH scheduling.
// C755A4 slot04 independently proves the 10B owner4->state0 forwarder.
class Rva005EC832Owner{public:Rva005EC832Owner*rva005EC832(int);};
class Rva005EC422{public:Rva005EC422(void*p){((Rva005EC832Owner*)this)->rva005EC832((int)p);}~Rva005EC422();void*ptr;};
class Rva005D1035{public:Rva005D1035(void*p):owner(p){}virtual ~Rva005D1035(){}virtual void slot1()=0;void*owner;};
class StrategicVeterancy{public:bool Show();};
class Rva005D10F9:public Rva005D1035{public:Rva005D10F9(void*,void*);virtual ~Rva005D10F9();virtual void slot1();Rva005EC422 view;};

void*__cdecl operator new(unsigned);void*__cdecl rva005ED198(const void*);
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Object;
class Rva00575674{public:void rva00575674(Object*);};
class Rva000AD6F4{public:Rva000AD6F4():ptr(0){}~Rva000AD6F4();void clear();void*ptr;};
class Rva005D10B0State {public:virtual void slot0();virtual void slot1();};
struct Rva005D10B0Owner{Rva005D10B0State*state;};
class Rva005D10D6:public Rva005D1035{public:Rva005D10D6(void*p):Rva005D1035(p){}virtual ~Rva005D10D6();virtual void slot1();};
class Rva005D1210{public:Rva005D1210(void*);~Rva005D1210();void*owner;void*object;Rva000AD6F4 state;};
Rva005D1210::Rva005D1210(void*p):owner(p),object(0){
 object=TheLivingWorldLogic?rva005ED198(TheLivingWorldLogic):0;
 if(object)((Rva00575674*)&state)->rva00575674((Object*)new Rva005D10F9(this,object));
 else ((Rva00575674*)&state)->rva00575674((Object*)new Rva005D10D6(this));
}

Rva005D10F9::Rva005D10F9(void*p,void*s):Rva005D1035(p),view(s){((StrategicVeterancy*)&view)->Show();}

void Rva005D10D6::slot1(){((Rva005D10B0Owner*)owner)->state->slot1();}

class Rva005D12E3Base{public:virtual ~Rva005D12E3Base(){}};
class Rva005D127C{public:void clear();void*ptr;};
class Rva005D12E3:public Rva005D12E3Base{public:Rva005D12E3();virtual ~Rva005D12E3();Rva005D127C holder;};
Rva005D12E3::Rva005D12E3(){holder.ptr=new Rva005D1210(this);}
