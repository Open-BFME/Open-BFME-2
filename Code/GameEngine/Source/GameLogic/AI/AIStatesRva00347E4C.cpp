// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native347E4C..347EA8 RET0. Machine owner18/+14 and getter29439D prove
// receiver transport. WB ModelConditionFlagType construction plus native
// virtualslot106 prove two76B bitflags (312/313), passed byvalue with 50/60.
// Native helperD43D0 is folded zero result, ECX same state. Original names unknown.
typedef int Int;enum StateReturnType{STATE_CONTINUE=0,STATE_FAILURE=-2};
struct Rva0028F59A{unsigned int bits[19];Rva0028F59A(int,int)throw();Rva0028F59A(const Rva0028F59A&)throw();};
template<int N>class State347Slots:public State347Slots<N-1>{public:virtual void gap(char(*)[N])=0;};
template<>class State347Slots<0>{};
class Rva00347E4CDrawView:public State347Slots<106>{public:virtual void setModels(int,int,Rva0028F59A,Rva0028F59A)=0;};
class Object{public:void*rva0029439D();};
class Rva00347E4CMachine{public:unsigned char pad[0x14];Object*owner;};
class Rva00347E4CState{public:
 StateReturnType onEnter();
 int rva000D43D0();
 unsigned char pad[0x18];Rva00347E4CMachine*machine;
};

StateReturnType Rva00347E4CState::onEnter(){
 Object*owner=machine->owner;
 if(!owner)return STATE_FAILURE;
 Rva00347E4CDrawView*draw=(Rva00347E4CDrawView*)owner->rva0029439D();
 if(!draw)return STATE_FAILURE;
 draw->setModels(50,60,Rva0028F59A(0,312),Rva0028F59A(0,313));
 rva000D43D0();
 return STATE_CONTINUE;
}
