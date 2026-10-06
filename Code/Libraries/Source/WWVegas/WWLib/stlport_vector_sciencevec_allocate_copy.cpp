// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??$_M_allocate_and_copy@PAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@?$vector@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@V?$allocator@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@2@@_STL@@IAEPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@1@IPAV21@0@Z @0x001FFA2D 45B
// Chain lane: vector<FillSciVec>::_M_allocate_and_copy via allocator twin
// 0x00395928 (pinned) and rowed __uninitialized_copy 0x00339962. Caller
// 0x001FFDAA. Spelled after _Vector_base shape: start +0 finish +4 proxy +8.
enum ScienceType { SCIENCE_NONE = 0 };
namespace _STL {
struct __false_type { __false_type() {} };
template <class T> class allocator {
public:
	T *allocate(unsigned int n, const void *hint) const;
};
template <class T, class Alloc> class vector {
public:
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef unsigned int size_type;
protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
private:
	pointer m_start;
	pointer m_finish;
	struct Proxy { allocator<T> m_alloc; pointer m_data; };
	Proxy m_endOfStorage;
};
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}
typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > FillSciVec;
template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last)
{
	Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
	__uninitialized_copy(first, last, result, __false_type());
	return result;
}
template FillSciVec *_STL::vector<FillSciVec, _STL::allocator<FillSciVec> >::_M_allocate_and_copy<FillSciVec *>(unsigned int, FillSciVec *, FillSciVec *);
