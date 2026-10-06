// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// vector<vector<BfmePod88>>::_M_allocate_and_copy, retail 0x00500BC8, 45 bytes.
// Allocates n slots through the end-of-storage proxy (allocator pinned at
// 0x00395928 as ICF twin of rowed BfmeE12 allocate) and copies the range
// with the rowed __uninitialized_copy at 0x00500B5B. Spelled after the
// STLport _Vector_base shape like Rva004F6352AllocateCopy.cpp: _M_start at
// +0 _M_finish at +4 the allocating proxy at +8. ForwardIter is const
// vector<BfmePod88> * to match the rowed callee. Caller at 0x00500F34 in
// FUN_00900efa.

struct BfmePod88
{
	char m_body[88];
};

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

template <class Type, class Allocator>
class vector;

typedef vector<BfmePod88, allocator<BfmePod88> > Pod88Vec;

struct Pod88VecAllocProxy
{
	allocator<Pod88Vec> m_alloc;
	Pod88Vec *m_data;
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
	Pod88VecAllocProxy m_endOfStorage;
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

template _STL::Pod88Vec *_STL::vector<_STL::Pod88Vec, _STL::allocator<_STL::Pod88Vec> >::_M_allocate_and_copy<const _STL::Pod88Vec *>(unsigned int, const _STL::Pod88Vec *, const _STL::Pod88Vec *);
