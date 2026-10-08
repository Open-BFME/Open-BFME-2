// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /EHsc
// WorldBuilder callgraph lead: PalantirCommandInterface::Impl::OnToggleFlashLoaded
// at VA 0x013CC080, PalantirCommandInterface.cpp:1188. Target ABI and
// offsets below come from native bytes; the class name remains a donor lead.
#include "ascii_string.h"

struct CameraMarker;
class Object;
class Rva00575674 {
public:
 void rva00575674(Object *object);
private:
 void *m_ptr;
};
class Rva005C3F02 {
public:
 Rva005C3F02(void *level, void *name);
 virtual ~Rva005C3F02();
private:
 void *m_impl;
};
class Rva00528FE6 {
public:
 // ?Rva00528FE6::Rva00528FE6 present-unmatched
 __forceinline Rva00528FE6():m_ptr(0){}
 void rva00529009();
 void rva00528FE6(CameraMarker *marker);
private:
 void *m_ptr;
};
class Rva005C3932 {
public:
 Rva005C3932(int level, const AsciiString &name);
private:
 char m_data[8];
};
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// Native 0x0052991E..0x00529A21, RET4: the same toggle-clip allocation
// and lifetime as CommandUIImpl::OnToggleFlashLoaded. Target-specific
// parsers are rowed; six slots are 0x14 bytes from +0x64, holder +8.
// The owning UI class has not been established from target evidence.
bool __cdecl Rva00529628Get(const char *path, int *slot);
bool __cdecl Rva00528C30Get(const char *path, AsciiString &name);
class Rva0052991E
{
	struct Slot
	{
		char m_pad00[4];
		Rva00575674 m_subMenu;
		Rva00528FE6 m_toggleFlash;
		char m_pad0C[0x14 - 0x0C];
	};
	char m_pad00[0x64];
	Slot m_slots[6];
public:
	void rva0052991E(const char *path);
	void rva005297DD(const char *path);
};
void Rva0052991E::rva0052991E(const char *path)
{
	AsciiString name;
	Slot *button;
	{
		int slot;
		if (!Rva00529628Get(path, &slot))
			return;
		if (!Rva00528C30Get(path, name))
			return;
		button = &m_slots[slot];
	}
	if (*(void **)&button->m_toggleFlash)
		return;
	button->m_toggleFlash.rva00528FE6((CameraMarker *)new Rva005C3932(Rva004128BBGetLevel(name.str()), AsciiString(Rva00412845AfterLevel(name.str()))));
}

// Native 0x005297DD..0x005298E0, RET4; same slot/lifetime as 52991E,
// holder +4 and the rowed clip-base constructor at 5C40E7. WorldBuilder
// 0x013CBE00 names this operation OnSubMenuLoaded in the same source home.
void Rva0052991E::rva005297DD(const char *path)
{
	AsciiString name;
	Slot *button;
	{
		int slot;
		if (!Rva00529628Get(path, &slot))
			return;
		if (!Rva00528C30Get(path, name))
			return;
		button = &m_slots[slot];
	}
	if (*(void **)&button->m_subMenu)
		return;
	button->m_subMenu.rva00575674((Object *)new Rva005C3F02((void *)Rva004128BBGetLevel(name.str()), (void *)&AsciiString(Rva00412845AfterLevel(name.str()))));
}

// The owning slot lifetime is independently established by constructor529FC5:
// six elements at+64,20B stride, constructor callback2859D7/dtor529318.
// Target destructor proves owning-pointer cleanup AD6F4 at0/4, camera holder
// cleanup529009 at8, counted Apt release7DEEF atC;10 is plain zeroed state.
// Constructor2859D7 has no Ghidra entry, but is an explicit constructor callback
// in529FC5; the preceding row2859C1 ends exactly at its first byte.
// Prefix/member views remain address-derived; no donor identity or new pin claimed.
class Rva000AD6F4 {public:
// ?Rva000AD6F4::Rva000AD6F4 present-unmatched
Rva000AD6F4():p(0){}
~Rva000AD6F4();void*p;};
struct PalantirToggleHolder: Rva00528FE6 {
// ?PalantirToggleHolder::~PalantirToggleHolder present-unmatched
~PalantirToggleHolder(){rva00529009();}};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct PalantirSlotRef {
// ?PalantirSlotRef::PalantirSlotRef present-unmatched
PalantirSlotRef():p(0){}
// ?PalantirSlotRef::~PalantirSlotRef present-unmatched
~PalantirSlotRef(){if(p)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)p);}void*p;};
class Rva00529318Slot {public:Rva00529318Slot();~Rva00529318Slot();Rva000AD6F4 command,subMenu;PalantirToggleHolder toggle;PalantirSlotRef callback;int slotState;};
Rva00529318Slot::Rva00529318Slot():slotState(0){}
Rva00529318Slot::~Rva00529318Slot(){}

// Constructor529FC5 supplies owner0 and integer UI level4. Its seven callback
// strings and existing callback provider rows establish Palantir command UI use;
// original owner/class identity remains a lead, so retain Rva0052936C spelling.
// BFME1 callback-registration units and verified BFME2 CommandButtonMovieClip
// supply the reference pattern: AddCommandMapDelegate builds the reference in
// outgoing argument storage, preserving exact lifetime and unwind metadata.
// Target members: map names8; over-button name vectors14; flags2C/2D;
// pointer30; string34; rank38/24B; cost50/16B; state60; six20B slots64.
// Rank initialization is the independently rowed non-throwing straight-store38B
// provider528B72. Over-button level is reference-bound to delay its native load.
// The two-vector storage and cleanup retain existing address-derived provider
// views; these wrappers do not assert original C++ type names.
class AptCommandTarget
{
};

struct DelegateDesc
{
	// ?DelegateDesc::DelegateDesc present-unmatched
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	// ?DelegateDesc::DelegateDesc present-unmatched
	template <class T> DelegateDesc(T *object, void (T::*method)(int))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <class T> class AptRef
{
public:
	// ?AptRef::AptRef present-unmatched
	AptRef(const DelegateDesc *desc) { rva00579E47(desc); }
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
	// ?AptRef::AptRef present-unmatched
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	// ?AptRef::~AptRef present-unmatched
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	// ?AptCommandMapAdder::AddCommandMapDelegate present-unmatched
	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, &desc);
	}

private:
	char m_pad[0xC];
};


class AptOverButtonHandler {public:void*m_vtbl;int m_refCount;};
// ?AptRef::AptRef present-unmatched
template<> __forceinline AptRef<AptOverButtonHandler>::AptRef(const DelegateDesc*desc){((AptRef<AptCommandMap>*)this)->rva00579E47(desc);}
class Rva00524415 {public:Rva00524415();char data[24];};
class Rva00524436 {public:~Rva00524436();};
struct PalantirOverStorage {Rva00524415 vectors;
// ?PalantirOverStorage::~PalantirOverStorage present-unmatched
~PalantirOverStorage(){((Rva00524436*)this)->Rva00524436::~Rva00524436();}};
class AptOverButtonHandlerAdder:public PalantirOverStorage {public:
 void AddOverButtonHandler(int,const AsciiString&,AptRef<AptOverButtonHandler>);
 // ?AptOverButtonHandlerAdder::AddOverButtonHandlerDelegate present-unmatched
 __forceinline void AddOverButtonHandlerDelegate(const int&level,const AsciiString&name,DelegateDesc desc){AddOverButtonHandler(level,name,&desc);}
};
class Rva00528B72 {public:Rva00528B72*rva00528B72(void*) throw();char data[24];};
class Rva00528B98 {public:void rva00528B98();};
struct PalantirRankInterface {Rva00528B72 state;
// ?PalantirRankInterface::PalantirRankInterface present-unmatched
__forceinline PalantirRankInterface(void*p) throw(){state.rva00528B72(p);}
// ?PalantirRankInterface::~PalantirRankInterface present-unmatched
__forceinline ~PalantirRankInterface(){((Rva00528B98*)this)->rva00528B98();}};
class Rva00528BC1 {public:Rva00528BC1*rva00528BC1(void*);char data[16];};
struct PalantirCostInterface {Rva00528BC1 state;
// ?PalantirCostInterface::PalantirCostInterface present-unmatched
__forceinline PalantirCostInterface(void*p){state.rva00528BC1(p);}};
class Rva00529F3D {public:void rva00529F3D(int);};
class Rva0052936C {public:
 Rva0052936C(void*,int);void rva00529698(const char*);void rva005297A0(const char*);void rva005298E0(const char*);void rva00529A21(const char*);
 void*owner;int frame;AptCommandMapAdder maps;AptOverButtonHandlerAdder over;bool flag2c,flag2d;void*current;AsciiString label;PalantirRankInterface rank;PalantirCostInterface cost;int value60;Rva00529318Slot slots[6];
};
class Rva00528F30Target {public:void reset();};
Rva0052936C::Rva0052936C(void*p,int f):owner(p),frame(f),flag2c(false),flag2d(false),current(0),rank((void*)f),cost((void*)f),value60(0) {
 over.AddOverButtonHandlerDelegate(frame,AsciiString("CommandUI/PortraitBackground"),DelegateDesc((Rva00529F3D*)this,&Rva00529F3D::rva00529F3D));
 maps.AddCommandMapDelegate(AsciiString("PalantirCommandUI::OnButtonFrameLoaded"),DelegateDesc(this,&Rva0052936C::rva00529698));
 maps.AddCommandMapDelegate(AsciiString("PalantirCommandUI::OnButtonFrameUnloaded"),DelegateDesc(this,&Rva0052936C::rva005297A0));
 maps.AddCommandMapDelegate(AsciiString("PalantirCommandUI::OnSubMenuLoaded"),DelegateDesc((Rva0052991E*)this,&Rva0052991E::rva005297DD));
 maps.AddCommandMapDelegate(AsciiString("PalantirCommandUI::OnSubMenuUnloaded"),DelegateDesc(this,&Rva0052936C::rva005298E0));
 maps.AddCommandMapDelegate(AsciiString("PalantirCommandUI::OnToggleFlashLoaded"),DelegateDesc((Rva0052991E*)this,&Rva0052991E::rva0052991E));
 maps.AddCommandMapDelegate(AsciiString("PalantirCommandUI::OnToggleFlashUnloaded"),DelegateDesc(this,&Rva0052936C::rva00529A21));
 ((Rva00528F30Target*)this)->reset();
}
