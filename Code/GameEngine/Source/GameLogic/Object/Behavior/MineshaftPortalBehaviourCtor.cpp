// cl: /Oy- /DNDEBUG /MD
// stlport
//
// ??0MineshaftPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00373096, 96 bytes. Behavior-side ctor over the rowed
// UpdateModule base (0x253390, 61B): two derived interfaces at +0x20/+0x24
// (their stores overwrite the re-stored inherited values, UpdateModule
// double-store precedent), the implicit _STL::vector<int> member at +0x28
// builds through the folded Vector_base at 0x211E58 (int spelling reuses
// the existing pin; ProductionQueueHordeContain precedent: only compiler
// stores split setup/call), then the trailing int/byte/byte. Framed via
// /Oy- (the 1-byte allocator temp lives at [ebp+0xF]); no /GX so no EH
// prolog draws. Class size 0x3C proven by the rowed instance factory
// (news 0x3C, sole caller at 0x24B625). Row supersedes the ctor pin.

#include <vector>
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<int, allocator<int> >::_Vector_base(allocator<int> const &); }
// bfme link decl-only end

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

class Thing;
class ModuleData;

class Object;
class BehaviorModuleBase
{
private:
	virtual void unused();
public:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual void update();
};

class MineshaftPortalInterfaceA
{
public:
	virtual void ifaceA() = 0;
};

class MineshaftPortalInterfaceB
{
public:
	virtual void ifaceB() = 0;
};

class MineshaftPortalBehaviour : public UpdateModule, public MineshaftPortalInterfaceA, public MineshaftPortalInterfaceB
{
public:
	MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData);

private:
	_STL::vector<int> m_items28;
	int m_count34;
	unsigned char m_flag38;
	unsigned char m_mode39;
	unsigned char m_pad3A[2];
};

// ??0MineshaftPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z @0x00373096
MineshaftPortalBehaviour::MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_count34 = 0;
	m_flag38 = 0;
	m_mode39 = 1;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleBase@@EAEXXZ=??_GRva0037343B@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?update@UpdateModule@@UAEXXZ=?update@Rva0037343B@@UAE?AW4UpdateSleepTime@@XZ")
