// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native274DD4..274E5B135B lazily creates a static counted owner.
// Native27974B..27979776B initializes its receiver, then assigns that
// owner to the handle at10C. Provider433390 proves a polymorphic D0-byte
// object with one int constructor argument; its remaining layout is opaque.
// Existing A8CE5 setter/A8C7C copy/239099 assignment and50ED3 release prove
// the four-byte handle and atomic counted-object ABI.
// Guard9FEBE8 bit1, holder9FEBE4 and registered cleanup7B77EC are target
// facts. The compiler-local callback independently matches all16B; its
// generic _$E2 name already belongs to another TU, so no extra row is claimed.
// Original factory/receiver names unknown; addresses remain honest names.
class OpaqueRefCounted {public:void Release_Ref();void*vtable;long volatile count;};
class Rva000A8C9B {public:void rva000A8CE5(OpaqueRefCounted*);};
class Rva0036CA00Str {public:
 __declspec(nothrow) Rva0036CA00Str():item(0){}
 __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str&);
 ~Rva0036CA00Str(){if(item)item->Release_Ref();}
 void assign(const Rva0036CA00Str&);
 OpaqueRefCounted*item;
};
class Rva00433390 {public:virtual ~Rva00433390();Rva00433390(int);char unknown[0xD0-4];};
Rva0036CA00Str Rva00274DD4(){
 static Rva0036CA00Str value;
 if(!value.item)((Rva000A8C9B*)&value)->rva000A8CE5((OpaqueRefCounted*)new Rva00433390(0));
 return value;
}
class Rva00279354Host {public:void rva00279354(bool);};
class Rva0027974B {public:void rva0027974B();char unknown0[0x10C];Rva0036CA00Str held;};
void Rva0027974B::rva0027974B(){
 ((Rva00279354Host*)this)->rva00279354(false);
 held.assign(Rva00274DD4());
}
