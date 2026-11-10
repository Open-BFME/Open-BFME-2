// cl: /GX /DNDEBUG /MD
// stlport
//
// ??0OilSpillUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048C1F7,
// 97 bytes. Behavior-side ctor over the pinned FireWeaponUpdate base
// (0x48C0C5): the implicit _STL::vector<int> member at +0x2C builds through
// the folded Vector_base at 0x211E58 (int spelling reuses the existing pin;
// MineshaftPortalBehaviour precedent: only compiler stores split
// setup/call), then setWakeFrame through the pinned 0x44DF71. Two EH
// states (base + vector): the base carries a declared-only virtual dtor
// (Devastate-V5 precedent: unwindable with no code, links via vtable).
// Class size 0x38 proven by the rowed instance factory (news 0x38, sole
// caller at 0x24CFA7). Row supersedes the ctor pin.

#include <vector>

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

class FireWeaponBaseA
{
	virtual void unusedA();
	int m_a0;

protected:
	void *m_owner08;
};

class FireWeaponBaseB
{
	virtual void unusedB();
};

class FireWeaponBaseC
{
	virtual void unusedC();
};

class FireWeaponUpdate : public FireWeaponBaseA, public FireWeaponBaseB, public FireWeaponBaseC
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate();

protected:
	void setWakeFrame(Object *obj, unsigned int frames);

private:
	unsigned char m_pad14[0x2C - 0x14];
};

class OilSpillUpdate : public FireWeaponUpdate
{
public:
	~OilSpillUpdate();	// rowed out of line; this view must not emit its own
	OilSpillUpdate(Thing *thing, const ModuleData *moduleData);

private:
	_STL::vector<int> m_items2C;
};

// ??0OilSpillUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048C1F7
OilSpillUpdate::OilSpillUpdate(Thing *thing, const ModuleData *moduleData)
	: FireWeaponUpdate(thing, moduleData)
{
	setWakeFrame(reinterpret_cast<Object *>(m_owner08), 1);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
