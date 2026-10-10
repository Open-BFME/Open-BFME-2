// cl: /O1 /G7 /MD /EHsc
// Native5D1255..5D1260 is an11B tail forwarder, not Ghidra's39B:
// the separately owned scalar deleting dtor begins5D1260. C752A8 slot04
// and C755BC independently reference this body; owner4 points to a view
// whose pointer8 dispatches virtual04. Original owner/field names unknown.
class Rva005CF872{public:Rva005CF872(void*p):owner(p){}virtual~Rva005CF872(){}virtual void slot1();void*owner;};
class Rva005D1255State{public:virtual void slot0();virtual void slot1();};
struct Rva005D1255Owner{char pad[8];Rva005D1255State*state;};
class Rva005D1255:public Rva005CF872{public:Rva005D1255(void*p):Rva005CF872(p){}virtual void slot1();};
void Rva005D1255::slot1(){((Rva005D1255Owner*)owner)->state->slot1();}
class Rva005EB8CA{public:void rva005EB8CA();};
class Rva005EB87A{public:bool rva005EB87A();};
class Object;class Rva00575674{public:void rva00575674(Object*);Rva005D1255State*state;};
struct Rva005CFF0FOwner{char pad[0x18];void*data;Rva00575674 state;};
class Rva005CFFB8:public Rva005CF872{public:Rva005CFFB8(void*,void*);virtual~Rva005CFFB8();virtual void slot1();void*view;};
class Rva005CFEDF:public Rva005CF872{public:virtual~Rva005CFEDF();virtual void slot1();void*view;};
void*__cdecl operator new(unsigned);
void Rva005CFEDF::slot1(){
 ((Rva005EB8CA*)&view)->rva005EB8CA();
 if(((Rva005EB87A*)&view)->rva005EB87A())return;
 Rva005CFF0FOwner*impl=(Rva005CFF0FOwner*)owner;
 void*data=impl->data;if(data)impl->state.rva00575674((Object*)new Rva005CFFB8(impl,data));else impl->state.rva00575674((Object*)new Rva005D1255(impl));
 impl->state.state->slot1();
}
