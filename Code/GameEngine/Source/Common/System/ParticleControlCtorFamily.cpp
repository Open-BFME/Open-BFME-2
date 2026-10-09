// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// Native311B3FC58C/WB106E280 exposes name4, handle1C, two vectors5C/68,
// scalar defaults throughA8 and manager registration2129A1. The pre-existing
// address-derived Rva003FD14DBase(int) pin is an opaque four-byte ABI view:
// its argument contains the reference address forwarded to StringBase copy.
// It is preserved here so established derived callers remain byte-matched;
// int is not asserted as the original source parameter type.
// BFME1 2f243 intrinsic handle and full WWMath Coord3D lifetimes guide types;
// target independently proves the exact stores/constants and owner relationship.
// Existing ModuleData-typed registration is an explicit pointer ABI view;
// no ModuleData inheritance or original class identity is asserted.
// Member initializer order plus real float-vector constructors reproduce
// native string/handle EH states and SSE store schedule. No new pin/global.
#include "coord3d.h"
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(float xv,float yv,float zv) {x=xv;y=yv;z=zv;}
template<class T> struct StringInlineData { int m_refCount,m_length;T m_text[1]; };
#include "ascii_string.h"
class ModuleData;
class Rva002129A1 { public: void rva002129A1(const ModuleData *); };
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class RvaSmartPtr12 { public:
 RvaSmartPtr12() { ptr=0;next=0;prev=0; }
 void rva0004CBC0() throw();
 ~RvaSmartPtr12() throw() {if(ptr)rva0004CBC0();}
 void *ptr,*prev,*next;
};
class Rva003FD14DBase { public:
 Rva003FD14DBase(int);
 virtual void vbfunc();
 AsciiString name;
 int f08,f0C,f10,f14,f18;
 RvaSmartPtr12 handle;
 int f28,f2C,f30,f34,f38,f3C,f40,f44,f48,f4C,f50;
 float f54;bool f58;
 Coord3D v5c,v68;
 float f74;bool f78;
 float f7C,f80,f84;bool f88;
 float f8C,f90,f94,f98,f9C,fA0,fA4,fA8;
};
Rva003FD14DBase::Rva003FD14DBase(int arg) : name(*reinterpret_cast<const AsciiString *>(arg)),
 f08(0),f0C(0),f10(0),f14(0),f18(0),f28(0),f2C(0),f30(0),f34(1),f38(0),f3C(0),f40(1),f44(0),f48(1),f4C(0),f50(0),f54(0),f58(false),
 v5c(0.f,0.f,0.f),v68(0.f,0.f,0.f),f74(.1f),f78(false),f7C(1.f),f80(1.f),f84(.001f),f88(false),f8C(0.f),f90(6.27f),f94(.3f),f98(1.f),f9C(1.f),fA0(1.f),fA4(1.f),fA8(1.f) {
 reinterpret_cast<Rva002129A1 *>(TheLivingWorldManager)->rva002129A1(reinterpret_cast<const ModuleData *>(this));
}

// Derived61B3FDAAE/WB1072630 takes an owning string by value, forwards
// its reference address through the existing base ABI, installs its own
// vtable, then releases the parameter. No additional fields are initialized.
class Rva003FDAAE : public Rva003FD14DBase { public:
 Rva003FDAAE(AsciiString name);
 virtual void vfunc();
};
Rva003FDAAE::Rva003FDAAE(AsciiString name):Rva003FD14DBase(reinterpret_cast<int>(&name)) {}
