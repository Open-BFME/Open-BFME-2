// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /Ireference/shims/moduledata
// stlport
//
// ??1FireWeaponUpdateModuleData@@UAE@XZ, retail 0x0048BC46, 117 bytes. Virtual dtor for
// the rowed base ctor 0x0048BC03 (vtable 0x00C4C110, slot0 deleting dtor
// 0x0048C098 calls this). Shape follows FireWeaponUpdate dtor 0x0048BD11:
// vptr store plus watch-list drain loop (per value: AsciiString teardown via
// folded 0x36410 plus operator delete 0x2FD60 plus list<int>::remove 0x47BAF7)
// plus implicit list-base dtor 0x4EC395 plus Snapshot base restore to
// 0xBBB554. List at +8 with unk dword at +4 and three flag bytes at
// +0xC/+0xD/+0xE per the ctor TU (news 0x10 via factory 0x24CF56). The 0x18
// nugget's first member is the AsciiString (WeaponName per table 0xC4C0C0),
// so its teardown folds to the StringBase spelling at the same address.

// Link: declare ~AsciiString only (the shim's documented per-unit switch) so this TU calls the out-of-line
// retail destructor instead of emitting a non-retail ??_GAsciiString copy; the // cl: line is untouched.
#ifndef BFME_ASCII_DTOR_DECL
#define BFME_ASCII_DTOR_DECL
#endif
#include <list>

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

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/Snapshot.h"

#include "ascii_string.h"

typedef bool Bool;

class FireWeaponUpdateModuleData : public Snapshot
{
public:
	virtual ~FireWeaponUpdateModuleData();
	int m_unk04; // +4
	_STL::list<int> m_nuggets; // +0x08
	Bool m_heroModeTrigger; // +0x0C
	Bool m_chargingModeTrigger; // +0x0D
	Bool m_aliveOnly; // +0x0E
};

FireWeaponUpdateModuleData::~FireWeaponUpdateModuleData()
{
	_STL::list<int> *trackedList = &m_nuggets;
	_STL::list<int>::iterator it = trackedList->begin();
	while (it != trackedList->end()) {
		int trackedValue = *it;
		++it;
		if (trackedValue != 0) {
			((AsciiString *)trackedValue)->~AsciiString();
			::operator delete((void *)trackedValue);
		}
		trackedList->remove(trackedValue);
	}
}
