// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// Native5F501E..5F5087 and callbacks5F4B37/5F4B41 establish this34B
// handler view. Existing constructor523F proves owner8/sideC/context10,
// copied selection14/28B and changed30. Native vtablesC79510/C794FC
// prove independent three/five-slot interfaces at0/4; common base tables
// C79544/C77BE8 contain only RET4/RET8 callbacks. Their parameter words
// are intentionally opaque. The +4 interface's overrides use adjusted ECX
// (native changed+2C), reproduced by real MSVC multiple inheritance.
// WB16280C0 independently names ArmyUnitSwapperDialog::Impl::ArmyHandler
// destructor; the method names and original callback argument types remain
// unknown. Inline getObserved preserves native EAX load then LEA ECX+4.
// Native detach2B7250 and selection cleanup5F23B2 have existing owners.
// Constructor523F is banked separately; no nonmatching definition here.
class Rva005FPrimaryCallbacks {public:

 virtual void primary0(void*,void*){}

 virtual void primary1(void*){}

 virtual void primary2(void*,void*){}
 __forceinline ~Rva005FPrimaryCallbacks(){}
};
class Rva005FSecondaryCallbacks {public:

 virtual void secondary0(void*,void*){}

 virtual void secondary1(void*){}

 virtual void secondary2(void*,void*){}

 virtual void secondary3(void*,void*){}

 virtual void secondary4(void*,void*){}
 __forceinline ~Rva005FSecondaryCallbacks(){}
};
class Rva005F54DA;
class Rva005F23B2 {public:~Rva005F23B2();};
class Rva005F24F0 {public:Rva005F24F0(const Rva005F24F0&);__forceinline ~Rva005F24F0(){((Rva005F23B2*)this)->~Rva005F23B2();}char bytes[28];};
struct Rva002BA8F1Listener;
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener*);};
class CreateAHeroData;
class Rva002B7250 {public:void rva002B7250(CreateAHeroData*);};
struct Rva005FArmyObserve {char pad[4];};
struct Rva005FArmyContext {char pad[0x78];Rva005FArmyObserve*observed; __forceinline Rva005FArmyObserve*getObserved(){return observed;}};
struct Rva005F54DAState {char pad[0x18];bool enabled;};
class Rva005F501E:public Rva005FPrimaryCallbacks,public Rva005FSecondaryCallbacks {public:
 Rva005F501E(Rva005F54DA*,int,void*,void*);~Rva005F501E();
 virtual void primary0(void*,void*);virtual void primary2(void*,void*);
 virtual void secondary2(void*,void*);virtual void secondary3(void*,void*);
 Rva005F54DA*owner;int side;void*context;Rva005F24F0 selected;bool changed;
};
void Rva005F501E::primary0(void*,void*){((Rva005F54DAState*)owner)->enabled=true;}
void Rva005F501E::primary2(void*,void*){((Rva005F54DAState*)owner)->enabled=true;}
void Rva005F501E::secondary2(void*,void*){changed=true;}
void Rva005F501E::secondary3(void*,void*){changed=true;}
Rva005F501E::~Rva005F501E(){
 ((Rva002B7250*)&selected)->rva002B7250((CreateAHeroData*)this);
 ((Rva002B7250*)((char*)((Rva005FArmyContext*)context)->getObserved()+4))->rva002B7250((CreateAHeroData*)(Rva005FSecondaryCallbacks*)this);
}
