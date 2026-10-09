// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
// Native helpers49D07A..49D0DE (100B), callback49DF72..49DF81 (15B)
// and parent49DF81..49E03A (185B). The earlier Ghidra154B helper extent
// includes already-owned54B49D0DE; actual RET at49D0DD is independently
// cross-checked against that ledger boundary. Names remain address-derived.
// Target parent resolves input objectID3C, builds the context pair from
// Object holder274 and argument2, visits the object and kind109 children.
// ZH ProductionUpdate has no matching target extension; existing STLport
// vector<Object*> owners and native field/virtual/call evidence guide this.
// Keep helper and real caller in this TU: private noinline static helper
// uses native ESI object and EDI context under MSVC internal convention.
// All container methods retain slot names. Native RET8 establishes parent
// stdcall. All300B and parent EH exact; no new pins/headers/flag overrides.
#include <vector>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
class Object;
template<int N> class ProductionTransferSlots : public ProductionTransferSlots<N-1> {public:virtual void gap(char(*)[N])=0;};template<> class ProductionTransferSlots<0>{};
class ProductionTransferResult : public ProductionTransferSlots<42> {public:virtual void slot42(Object*)=0;};
class ProductionTransferSub : public ProductionTransferSlots<31> {public:virtual ProductionTransferResult *slot31()=0;};
class TransferContainView : public ProductionTransferSlots<1> {public:virtual Object *slot1()=0;
virtual void c2()=0;
virtual void c3()=0;
virtual void c4()=0;
virtual void c5()=0;
virtual void c6()=0;
virtual void c7()=0;
virtual void c8()=0;
virtual void c9()=0;
virtual void c10()=0;
virtual void c11()=0;
virtual void c12()=0;
virtual void c13()=0;
virtual void c14()=0;
virtual void c15()=0;
virtual void c16()=0;
virtual void c17()=0;
virtual void c18()=0;
virtual void c19()=0;
virtual void c20()=0;
virtual void c21()=0;
virtual void c22()=0;
virtual void c23()=0;
virtual void c24()=0;
virtual void c25()=0;
virtual void c26()=0;
virtual void c27()=0;
virtual void c28()=0;
virtual void c29()=0;
virtual void c30()=0;
virtual void c31()=0;
virtual void c32()=0;
virtual void c33()=0;
virtual void c34()=0;
virtual void c35()=0;
virtual void c36()=0;
virtual void c37()=0;
virtual void c38()=0;
virtual void slot39(Object*)=0;
virtual void c40()=0;virtual void slot41(Object*,int)=0;
virtual void c42()=0;
virtual void c43()=0;
virtual void c44()=0;
virtual void c45()=0;
virtual void c46()=0;
virtual void c47()=0;
virtual void c48()=0;
virtual void c49()=0;
virtual void c50()=0;
virtual void c51()=0;
virtual void c52()=0;
virtual void c53()=0;
virtual void c54()=0;
virtual void c55()=0;
virtual void c56()=0;
virtual void c57()=0;
virtual void c58()=0;
virtual void c59()=0;
virtual void c60()=0;
virtual void c61()=0;
virtual void c62()=0;
virtual void c63()=0;
virtual void c64()=0;
virtual void c65()=0;
virtual void c66()=0;
virtual void c67()=0;
virtual void slot68(void(__cdecl*)(Object*,void*),void*,bool)=0;
};
class ProductionTransferTemplate {public:char pad[0x115];unsigned char flag;};
class Object {public:char pad0[4];ProductionTransferTemplate *thing;char pad8[0x250-8];TransferContainView *contain;char pad254[0x274-0x254];Object *holder;};
struct Rva0049DF81Context {Object *first,*second;};
static __declspec(noinline) void Rva0049D07A(Object *obj,const Rva0049DF81Context &context){
 if(obj->holder->thing->flag & 0x20){
 context.first->contain->slot41(obj,0);
 Object *host=obj->holder->contain->slot1();
 ((ProductionTransferSub*)((char*)host+0x20))->slot31()->slot42(obj);
 }else context.first->contain->slot41(obj,0);
 context.second->contain->slot39(obj);
}
void __cdecl Rva0049DF72(Object *object,void *context){((_STL::vector<Object*>*)context)->push_back(object);}
struct Rva0049DF81Input {char pad[0x3C];ObjectID id;};
extern GameLogic *TheGameLogic;
void __stdcall Rva0049DF81(Rva0049DF81Input *input,Object *other){
 if(!input->id)return;
 Object *object=TheGameLogic->findObjectByID(input->id);
 Rva0049DF81Context context={object->holder,other};
 Rva0049D07A(object,context);
 if(object->thing->flag & 0x20){
 TransferContainView *contain=object->contain;
 if(contain){
 _STL::vector<Object*> children;
 contain->slot68(Rva0049DF72,&children,true);
 for(_STL::vector<Object*>::iterator i=children.begin();i!=children.end();++i)Rva0049D07A(*i,context);
 }
 }
}
