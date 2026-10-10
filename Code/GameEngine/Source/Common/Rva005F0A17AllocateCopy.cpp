// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// vector<Rva005EFD53Element>::_M_allocate_and_copy, retail 0x005F0A17, 45 bytes.
// Element is the 4-byte non-trivial view used by push_back 0x005EFD53.
// Allocates n slots via allocator pin 0x00068E15 and copies with the rowed
// __uninitialized_copy at 0x005EF3FE. Same ebp-frame allocate-then-copy shape
// as Rva004F6352AllocateCopy.cpp. Prior ObjectID pin at this RVA was a false
// identity: ObjectID emits the 31B trivial copy, retail calls the 38B ctor copy.

#include "RegionIconSlotReferenceView.h"

namespace _STL
{

struct __false_type
{
	__false_type()
	{
	}
};

template <class Type>
class allocator
{
public:
	Type *allocate(unsigned int n, const void *hint) const;
};

struct RvaAllocProxy
{
	allocator<Rva005EFD53Element> m_alloc;
	Rva005EFD53Element *m_data;
};

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *pointer;
	typedef unsigned int size_type;

protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first,
		ForwardIter last);

private:
	pointer m_start;
	pointer m_finish;
	RvaAllocProxy m_endOfStorage;
};

template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last,
	OutputIter result, const __false_type &tag);

}

template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n,
	ForwardIter first, ForwardIter last)
{
	Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
	__uninitialized_copy(first, last, result, __false_type());
	return result;
}

template Rva005EFD53Element *_STL::vector<Rva005EFD53Element, _STL::allocator<Rva005EFD53Element> >::_M_allocate_and_copy<Rva005EFD53Element *>(unsigned int, Rva005EFD53Element *, Rva005EFD53Element *);

// ??$_Construct@URva005EFD53Element@@U1@@_STL@@YAXPAURva005EFD53Element@@ABU1@@Z @0x005F09FF 24B.
// Copy-constructs Element with AddRef at +8. Called by 6 matched rows.
// Evidence: retail null-check p plus copy ptr plus null-check plus inc refs.
namespace _STL
{
template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);
}

// The exact element placement-copy provider is owned by Rva005EFD53ElementConstruct.cpp.
