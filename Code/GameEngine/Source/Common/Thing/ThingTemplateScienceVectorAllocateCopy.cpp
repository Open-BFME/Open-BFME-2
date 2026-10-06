// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// vector<ScienceType>::_M_allocate_and_copy, retail 0x0031B9EB, 45 bytes,
// rowed as ?dup_0031b9eb (the identical 4-byte-POD skeleton is shared with
// other instantiations, so no single element type is claimed).
//
// Allocates n slots through the end-of-storage proxy (folded allocator,
// pinned for ScienceType at 0x00068E15) and copies the range with the
// out-of-line __uninitialized_copy (ScienceType const-first spelling pinned
// at 0x001DD10D). Spelled after the STLport _Vector_base shape:
// _M_start at +0, _M_finish at +4, the allocating proxy at +8.

enum ScienceType
{
	SCIENCE_NONE = 0
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
	Type *allocate(unsigned int n, const void *hint);
};

struct ScienceAllocProxy
{
	allocator<ScienceType> m_alloc;
	ScienceType *m_data;
};

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *pointer;
	typedef const Type *const_pointer;
	typedef unsigned int size_type;

protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first,
		ForwardIter last);

private:
	pointer m_start;
	pointer m_finish;
	ScienceAllocProxy m_endOfStorage;
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

template ScienceType *
_STL::vector<ScienceType, _STL::allocator<ScienceType> >::_M_allocate_and_copy<const ScienceType *>(
	unsigned int, const ScienceType *, const ScienceType *);
