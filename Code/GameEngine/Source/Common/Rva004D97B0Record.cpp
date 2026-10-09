// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// Native4D97B0/9874 resolve an eight-byte counted value from Drawable14 and
// optional provider18 then call the independently rowed two-value setter.
// WB1293550/1293730 confirm branch-local temporaries and default path.
// 4D990E scans Object244 modules for a movement-sensitive template and feeds
// the name-based resolver. Original owner and method names remain unknown.
class OpaqueRefCounted { public: void Release_Ref(); };
class Rva002390CB { public:
    Rva002390CB();
    Rva002390CB(const Rva002390CB&);
    ~Rva002390CB() { if(ref) ref->Release_Ref(); }
    int id; OpaqueRefCounted *ref;
};
struct Rva002C99FB { int id; OpaqueRefCounted *ref; };
inline const Rva002C99FB &asStruct(const Rva002390CB &v) {return *(const Rva002C99FB*)&v;}
class Rva004D977D { public: void rva004D977D(const Rva002C99FB&,const Rva002C99FB&); };
class Rva004D9750 { public: Rva002390CB rva004D9750(int); };
#include "ascii_string.h"
class Rva0041541B { public: const Rva002390CB &rva0041541B(const AsciiString&); };
class Drawable { public: Rva002390CB rva0027675F(int); Rva002390CB rva00274CD8(const AsciiString&); };
class Rva004D97B0 {
 char pad[0x14]; Drawable *drawable; Rva004D9750 *extra;
public: void rva004D97B0(int); void rva004D9874(const AsciiString&);
};
void Rva004D97B0::rva004D97B0(int index) {
 if(index!=-1) ((Rva004D977D*)this)->rva004D977D(asStruct(drawable->rva0027675F(index)), asStruct(extra == 0 ? Rva002390CB() : extra->rva004D9750(index)));
}

void Rva004D97B0::rva004D9874(const AsciiString &name) {
 if(!name.isEmpty()) ((Rva004D977D*)this)->rva004D977D(asStruct(drawable->rva00274CD8(name)), asStruct(extra == 0 ? (const Rva002390CB&)Rva002390CB() : ((Rva0041541B*)extra)->rva0041541B(name)));
}
#include "Coord3D.h"
struct Rva004388E3Template;
class Object { public: Object *rva002931F5(bool); };
class Rva004389AE { public: bool rva004389AE(Object*,const Coord3D*,Rva004388E3Template*); };
class Rva004D9596 { public: bool rva004D9596(); };
class Rva004D990EBehavior { public:
 virtual void slot0();
 virtual const AsciiString &slot1();
 virtual const AsciiString &slot2();
 virtual Rva004388E3Template *slot3();
};
class Rva004D990EModule { public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
 virtual void s8(); virtual void s9(); virtual void sA();
 virtual Rva004D990EBehavior *sB();
};
struct Rva004D990EObjectView {
 char pad38[0x38]; Coord3D position; char pad44[0x200];
 Rva004D990EModule **modules;
};
class GameLogic; extern GameLogic *TheGameLogic;
struct Rva004D990ELogicView { char pad[0x178]; Rva004389AE *manager; };
bool __cdecl Rva004D933BIs(int);
void __cdecl Rva004D990E(int command, Object *obj, Rva004D97B0 *out, const Coord3D *location) {
 Rva004389AE *manager=((Rva004D990ELogicView*)TheGameLogic)->manager;
 if(!manager) return;
 Rva004D990EModule **modules=((Rva004D990EObjectView*)obj)->modules;
 if(!modules) return;
 while(!((Rva004D9596*)out)->rva004D9596()) {
  if(!*modules) break;
  Rva004D990EBehavior *b=(*modules)->sB();
  if(b) {
   Object *container=obj->rva002931F5(false);
   Coord3D from;
   if(container) from=((Rva004D990EObjectView*)container)->position;
   else from=((Rva004D990EObjectView*)obj)->position;
   Rva004388E3Template *tmpl=b->slot3();
   if(!manager->rva004389AE(obj,&from,tmpl) && manager->rva004389AE(obj,location,tmpl))
    out->rva004D9874(Rva004D933BIs(command) ? b->slot2() : b->slot1());
  }
  ++modules;

 }
}
