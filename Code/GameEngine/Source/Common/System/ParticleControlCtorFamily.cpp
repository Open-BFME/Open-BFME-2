// cl: /D_CRTIMP= /D_STLP_USE_STATIC_LIB /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Include
// stlport
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
#include <vector>
// STLport has already included VC7 <new>; suppress WWLib duplicate placement overloads.
#define _OPERATOR_NEW_DEFINED_
#include "matrix3.h"
#include "matrix3d.h"
#include "coord3d.h"
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(float xv,float yv,float zv) {x=xv;y=yv;z=zv;}
template<class T> struct StringInlineData { int m_refCount,m_length;T m_text[1]; };
#include "ascii_string.h"
namespace _STL {
template<> vector<AsciiString>::~vector();
template<> __declspec(noinline) _Vector_base<AsciiString,allocator<AsciiString> >::_Vector_base(const allocator<AsciiString> &a) : _M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
}
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
class BfmeAnimationReceiver
{
public:
	virtual void slot00(void); virtual void slot01(void);
	virtual void slot02(void); virtual void slot03(void);
	virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void);
	virtual void slot08(void); virtual void slot09(void);
	virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void);
	virtual void slot14(void); virtual void slot15(void);
	virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void);
	virtual void updatePayload(void);
	virtual void applyPayload(const Matrix3D *payload);

	unsigned char m_beforePayload[0x14];
	Matrix3D m_payload;
	float m_objectScale;
	float Get_ObjectScale() const { return m_objectScale; }
};

class Rva003FD14DBase { public:
 Rva003FD14DBase(int);
 void rva003FC82C(float angle);
 void rva003FCA58();
 virtual void vbfunc();
 AsciiString name;
 BfmeAnimationReceiver *m_primary; // +08
 int f0C,f10;
 BfmeAnimationReceiver *m_secondary; // +14
 int f18;
 RvaSmartPtr12 handle;
 int f28,f2C,f30,f34,f38,f3C,f40,f44,f48,f4C,f50;
 float f54;bool f58;
 Coord3D v5c,v68;
 float f74;bool f78;
 float f7C,f80,f84;bool f88;
 float f8C,f90,f94,f98,f9C,fA0,fA4,fA8;
};
Rva003FD14DBase::Rva003FD14DBase(int arg) : name(*reinterpret_cast<const AsciiString *>(arg)),
 m_primary(0),f0C(0),f10(0),m_secondary(0),f18(0),f28(0),f2C(0),f30(0),f34(1),f38(0),f3C(0),f40(1),f44(0),f48(1),f4C(0),f50(0),f54(0),f58(false),
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

// Donor575ba2b0 BfmeAnimationHolderRotation; native3FC82C proves secondary+14
// and scale preservation from receiver+48. Original method spelling unknown.
void Rva003FD14DBase::rva003FC82C(float angle)
{
	if (m_primary == 0)
		return;

	Matrix3 rotation(true);
	rotation.Rotate_Z(angle);
	BfmeAnimationReceiver *primary = m_primary;
	primary->updatePayload();
	Matrix3D payload(primary->m_payload);
	payload.Set_Rotation(rotation);
	payload.Scale(m_primary->Get_ObjectScale());
	m_primary->applyPayload(&payload);
	if (m_secondary != 0)
		m_secondary->applyPayload(&payload);
}

// Retail vtable C37C30 slot6 reaches this body. The address-named
// nonvirtual member is a callable body view; original virtual declaration
// and the incomplete legacy vtable are not claimed as recovered here.
void Rva003FD14DBase::rva003FCA58()
{
	if (m_primary == 0 || !f88)
		return;

	float angle = f94 + f8C;
	if (angle < 0.0f) angle += 6.2831855f;
	else if (angle > 6.2831855f) angle -= 6.2831855f;
	Matrix3 rotation(true);
	rotation.Rotate_Z(angle);
	BfmeAnimationReceiver *primary = m_primary;
	primary->updatePayload();
	Matrix3D payload(primary->m_payload);
	payload.Set_Rotation(rotation);
	payload.Scale(m_primary->Get_ObjectScale());
	m_primary->applyPayload(&payload);
	if (m_secondary != 0)
		m_secondary->applyPayload(&payload);
}

class RenderObjClass;
class LivingWorldVisual { public:
 RenderObjClass *createRenderObject(const AsciiString &,const _STL::vector<AsciiString> &,int,const int *);
};
// Reuse the existing scene-pointer owner spelling; no new global pin or definition.
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class BfmeRenderSceneView { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void insertObject(RenderObjClass *);
};
// Get_HAnim is the existing provider binding. Native +04 refcount and virtual
// slot5 frame count prove this minimal animation view; it is never instantiated.
class HAnimClass { public:
 virtual void Delete_This(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
 virtual int frameCount();
 int refs;
 void release() { if(--refs==0) Delete_This(); }
};
extern HAnimClass *Get_HAnim(const char *);
class BfmeAnimationObjectView { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void setAnimation(HAnimClass *,float,int);
};
class BfmeVisualPositionView { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void setPosition(const Coord3D *);
};
// Native3FD849..3FD9A3 and WB105DBD0 prove the complete 346B initializer.
// WB name refcount.h is an inlined assertion attribution, not the owner identity.
// Fields are independently read here; this neutral owner has no name/type pin.
class Rva003FD849 { public:
 bool rva003FD849();
 int key; Rva003FD14DBase *visual; float phase;
 AsciiString model; bool animate; float angle; unsigned short shadowType;
 AsciiString name; Coord3D position;
};
bool Rva003FD849::rva003FD849()
{
 visual=new Rva003FD14DBase(reinterpret_cast<int>(&name));
 RenderObjClass *created;
 { _STL::vector<AsciiString> subObjects;
   created=reinterpret_cast<LivingWorldVisual *>(visual)->createRenderObject(model,subObjects,shadowType,0);
 }
 if (created) {
 reinterpret_cast<BfmeVisualPositionView *>(visual)->setPosition(&position);
 visual->rva003FC82C(angle*0.017453292f);
 if (visual->m_primary) {
 reinterpret_cast<BfmeRenderSceneView *>(g_00DFEF18)->insertObject(reinterpret_cast<RenderObjClass *>(visual->m_primary));
 if (animate) {
  AsciiString animationName(model); animationName.concat("."); animationName.concat(model);
  HAnimClass *animation=Get_HAnim(animationName.str());
  if(animation) {
   float frame=animation->frameCount()*phase;
   reinterpret_cast<BfmeAnimationObjectView *>(visual->m_primary)->setAnimation(animation,frame,1);
   animation->release();
  }
 }
 return true;
 }
 }
 return false;
}
