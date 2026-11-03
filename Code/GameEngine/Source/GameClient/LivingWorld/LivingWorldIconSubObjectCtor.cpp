// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
//
// ??0Rva005C4B56@@QAE@ABUHelper005C4D4B@@_NPBH@Z @0x005C4DE0 415B
// WB 0x01566710 names LivingWorldIconSubObject::LivingWorldIconSubObject
// (LivingWorldIconSubObject.cpp:48, asserts the creation parameters are
// unused, then marks them used). Native 5C4DE0..5C4F7F RET12: base ctor
// 0x003FC58C with the parameters' name, vtable 0x00C747B8, template +0xAC,
// render object, pickbox, scale, "<name>.<name>" hierarchy animation, the
// TheLivingWorld registration (slot 0x44), the optional predicate state,
// unit scale 1,1,1 and the degree-to-radian rotation. The WB twin reads every
// template field and the render object through temporaries; the inline
// accessors below reproduce those loads. Class names stay address-derived.
#include "ascii_string.h"
#include <vector>
struct Rva005F17C6S12 {int m0,m1,m2;};
struct Rva0020F58E { int m0,m1,m2,m3; operator AsciiString(); };
struct Rva005F17C6S16 : Rva0020F58E {
 Rva005F17C6S16(const Rva005F17C6S16 &);

};
struct AsciiStringPlusText : Rva005F17C6S12 {};
AsciiStringPlusText operator+(const AsciiString &,const char *);
Rva005F17C6S16 Rva005F17C6Build(const Rva005F17C6S12 &,int);
class RenderObjClass;
class HTreeClass;
class Rva003FB65C {public:HTreeClass *rva003FC780(const AsciiString *,int);};
#include "../../../Include/GameClient/LivingWorldVisual.h"
// 0x003FCCC9 is rowed as LivingWorldVisual::rva003FCCC9(bool); the incoming
// unsigned-char predicate result keeps its byte spelling through a
// member-pointer cast (same binding as Rva005C4B96.cpp / Rva003FCD58Method.cpp).
typedef void (LivingWorldVisual::*LivingWorldVisualUcharShape)(unsigned char);
void rva0010E4F6(void *,bool);
struct SubAC005C4B56 {
 char pad00[4]; AsciiString name04; std::vector<AsciiString> names08;
 AsciiString pick14; int pad18; float value1C,scale20,angle24;
 int shadow28,animation2C,value30; char pad34[0x54-0x34]; bool colour54;
 float getScale() const { return scale20; }
 bool getUseColour() const { return colour54; }
 int getShadow() const { return shadow28; }
 int getAnimationMode() const { return animation2C; }
 int getValue30() const { return value30; }
 float getAngle() const { return angle24; }
 float getValue1C() const { return value1C; }
};
struct Helper005C4D4B {
 SubAC005C4B56 *m_00; AsciiString m_str; int m_08; bool m_0C;
 SubAC005C4B56 *getTemplate() const { return m_00; }
 int get08() const { return m_08; }
};
struct ThreeFloatBlock {float v[3]; ThreeFloatBlock(float a,float b,float c) {v[2]=c;v[1]=b;v[0]=a;} };
class Rva003FD14DBase {public:
 Rva003FD14DBase(int);
 ~Rva003FD14DBase();
 virtual void vbfunc();
 void rva003FC82C(float);
 char pad04[4]; void *primary08; char pad0C[0x30-0x0C];
 void *getRenderObject() const { return primary08; }
 int value30; char pad34[0xA0-0x34]; ThreeFloatBlock scaleA0;
};
class Rva005C41C9 {public: unsigned char rva005C4B26();};
class Rva002D3627Host {public:
#define V(n) virtual void s##n();
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08)
 V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
#undef V
 virtual void insert(void *);
};
class LivingWorld;
extern LivingWorld *TheLivingWorld;
class Rva005C4B56 : public Rva003FD14DBase {public:
 Rva005C4B56(const Helper005C4D4B &,bool,const int *);
 // 0x005C4B56 is rowed as Rva005C4B56::rva005C4B56(int,int,int); the phantom
 // derivedSlot slot that named nothing is rebound to that rowed member.
 void rva005C4B56(int,int,int);
 SubAC005C4B56 *m_ac; int m_b0; float m_b4; int m_b8;
};
Rva005C4B56::Rva005C4B56(const Helper005C4D4B &h,bool enabled,const int *colour)
 : Rva003FD14DBase(reinterpret_cast<int>(&h.m_str)),
 m_ac(h.getTemplate()),m_b0(h.get08()),m_b4(h.getTemplate()->getValue1C()),m_b8(0)
{
 const_cast<Helper005C4D4B &>(h).m_0C=true;
 LivingWorldVisual *visual=reinterpret_cast<LivingWorldVisual *>(this);
 visual->createRenderObject(m_ac->name04,m_ac->names08,m_ac->getShadow(),m_ac->getUseColour() ? colour : 0);
 visual->createPickboxObject(&m_ac->pick14);
 rva0010E4F6(getRenderObject(),false);
 visual->rva003FC291(m_ac->getScale());
 AsciiString animation=Rva005F17C6Build(m_ac->name04+".",reinterpret_cast<int>(&m_ac->name04));
 reinterpret_cast<Rva003FB65C *>(this)->rva003FC780(&animation,m_ac->getAnimationMode());
 reinterpret_cast<Rva002D3627Host *>(TheLivingWorld)->insert(getRenderObject());
 if (!enabled)
  (reinterpret_cast<LivingWorldVisual *>(this)->*reinterpret_cast<LivingWorldVisualUcharShape>(&LivingWorldVisual::rva003FCCC9))(reinterpret_cast<Rva005C41C9 *>(this)->rva005C4B26());
 value30=m_ac->getValue30();
 scaleA0=ThreeFloatBlock(1.f,1.f,1.f);
 rva003FC82C(m_ac->getAngle()*0.017453292f);
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?rva003FCCC9@Rva003FB65C@@QAEXE@Z=?rva003FCCC9@LivingWorldVisual@@QAEX_N@Z")
