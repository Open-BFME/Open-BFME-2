// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??0ProductionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0049E03A 258B
// ProductionUpdate behavior ctor over rowed UpdateModule base 0x253390 with two
// extra interface bases at +0x20/+0x24 (implicit vtables give early c513f0/
// c1c780 plus real five before members, Bezier double-store shape with members
// present so body stores cannot precede member ctors). Doors array at +0x3c
// (4x0x10 Rva0029BC80 zeroing ctor via rowed vector_constructor_iterator
// 0x1423), Rva members at +0x7c/+0xc8 via rowed memset ctor 0x42526, list<int>
// at +0x124 via rowed List_base 0x4EC36C, vector<BfmeE16> at +0x130 via rowed
// Vector_base 0x211E58 (16B stand-in, no erase so size unproven), trivial
// zeros/ones in init-list in declaration order (0 via ebx, 1 via edi juggled
// once and preserved callee-saved across member ctors), redundant doors zero
// loop in body (BFME1 donor for-loop kept after adding ctors, push-4/pop-ecx
// size idiom with +0x13c store hoisted between push and pop). No setWakeFrame
// (donor has none). Evidence: pin name, friend factory 0x24E87E news 0x140,
// BFME1 donor ProductionUpdate.cpp:197 (queue NULLs, uniqueID 1, doors loop,
// clear/setFlags, flagsDirty FALSE).
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::_List_base(const allocator<int> &);
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <vector>

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::~_Vector_base(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

class Thing;
class ModuleData;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

// ProductionUpdate's UpdateModuleInterface table (0x00C514F4): update and the
// getDisabledTypesToProcess override, then UpdateModule's 0x0044DF8D.
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
#include "../../../../Include/Common/BitFlagsTemplate.h"
typedef BitFlags<11> DisabledMaskType;
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class Rva0049E03AIface20
{
public:
	Rva0049E03AIface20();
	virtual void rva0049E03ASlot20() = 0;
	// Retail table 0x00C513F0: 30 __purecall entries follow.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
};
// ??0Rva0049E03AIface20@@QAE@XZ @0x0049CC0C 9B: the default constructor, storing the
// class's own vtable (VA 0x00C513F0) and returning this.
Rva0049E03AIface20::Rva0049E03AIface20()
{
}

class Rva0049E03AIface24
{
public:
	Rva0049E03AIface24() {}
	virtual void rva0049E03ASlot24() = 0;
};

class Rva0029BC80
{
public:
	Rva0029BC80();
	int m_at00;
	int m_at04;
	int m_at08;
	unsigned char m_at0C;
};

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class ProductionUpdate : public UpdateModule, public Rva0049E03AIface20, public Rva0049E03AIface24
{
public:
	~ProductionUpdate();	// rowed out of line; this view must not emit its own
	ProductionUpdate(Thing *thing, const ModuleData *moduleData);
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;

private:
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	Rva0029BC80 m_doors[4];
	Rva0042526Member m_7C;
	Rva0042526Member m_C8;
	unsigned char m_114;
	unsigned char m_pad115[3];
	int m_118;
	unsigned char m_11C;
	unsigned char m_11D;
	unsigned char m_pad11E[2];
	int m_120;
	_STL::list<int> m_list124;
	int m_128;
	int m_12C;
	_STL::vector<BfmeE16> m_vec130;
	unsigned char m_13C;
public:
	// retail slot 4: the rowed ?getModuleNameKey@ProductionUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

ProductionUpdate::ProductionUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData),
	m_28(0),
	m_2C(0),
	m_30(1),
	m_34(0),
	m_38(0),
	m_114(0),
	m_118(0),
	m_11C(0),
	m_11D(0),
	m_120(0),
	m_128(0),
	m_12C(1),
	m_13C(0)
{
	for (int i = 0; i < 4; ++i)
	{
		m_doors[i].m_at00 = 0;
		m_doors[i].m_at04 = 0;
		m_doors[i].m_at08 = 0;
		m_doors[i].m_at0C = 0;
	}
}
