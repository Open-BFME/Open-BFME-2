// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// Native 0x00297612..0x0029766B, 89B, RET. Object's adjacent rowed
// restoreObjectToWorld and the helper's +0x438 status/+0x84 Drawable accesses
// establish the owner. The entry meaning remains unresolved. BFME1 and ZH
// Object.cpp provide no corresponding countdown-list body.
#include <list>

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

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

struct Rva00297612Entry
{
	unsigned char unmodelled00[0x28];
	float remaining;
	unsigned char unmodelled2c[0x40 - 0x2c];
	float field40;
};

class Rva002975ACBody
{
public:
	virtual void slot00(Rva00297612Entry *entry);
};
#include "../../../Include/GameClient/Drawable.h"
#include "../../../Include/GameClient/BfmeSubBIC.h"

class Object
{
public:
	void rva002975AC(Rva00297612Entry *entry);
	void rva00296065(Rva00297612Entry *entry);
	void rva00297612();
private:
	unsigned char unmodelled00[0x84];
	Drawable *drawable;
	unsigned char unmodelled88[0x254 - 0x88];
	Rva002975ACBody *body;
	unsigned char unmodelled258[0x438 - 0x258];
	unsigned char status438;
	unsigned char unmodelled439[0x440 - 0x439];
	// An int-list view exposes the shared node links and node+8 value address.
	// Native erase 0x00438539 only relinks and frees the node; it does not
	// access its payload, so the already rowed int specialization is its ABI.
	_STL::list<int, _STL::allocator<int> > entries;
};

// Native 0x002975AC..0x00297612, RET4. The rowed countdown loop passes
// each expired entry here. Status bit0, body slot0, the entry's float40 and
// Drawable flag43c govern these calls; the record's higher meaning is open.
void Object::rva002975AC(Rva00297612Entry *entry)
{
	if (!(status438 & 1))
	{
		Rva002975ACBody *currentBody = body;
		if (currentBody)
			currentBody->slot00(entry);
	}
	if (!(status438 & 1) || entry->field40 > 0.0f)
		rva00296065(entry);
	Drawable *draw = drawable;
	if (draw && draw->m_selected)
		draw->rva0027295B((void *)((BfmeSubBIC *)this)->bfmeAskBIC());
}

void Object::rva00297612()
{
	typedef _STL::list<int, _STL::allocator<int> > EntryList;
	for (EntryList::iterator it = entries.begin(); it != entries.end(); )
	{
		Rva00297612Entry *entry = (Rva00297612Entry *)&*it;
		entry->remaining -= 1.0f;
		if (entry->remaining < 0.0f)
		{
			rva002975AC(entry);
			it = entries.erase(it);
		}
		else
			++it;
	}
}
