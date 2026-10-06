// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??$_M_allocate_and_copy@PAUBfmeVectorRecord00319C84@@@?$vector@UBfmeVectorRecord00319C84@@V?$allocator@UBfmeVectorRecord00319C84@@@_STL@@@_STL@@IAEPAUBfmeVectorRecord00319C84@@IPAU2@0@Z @0x00319304 45B
// Evidence: caller reserve 0x00319C84 plus unclaimed 0x00319BFF; rowed allocate 0x002226BE via BfmeVectorRecord00319C84 pin plus rowed copy 0x00318D75; same 45B ebp-tag shape as 0x001FFA2D and 0x00317D5C
struct BfmeVectorRecord00319C84
{
	char m_body[16];
};
class Rva00318B5C
{
	char _m[0x10];
public:
	Rva00318B5C(const Rva00318B5C &that);
};
namespace _STL
{
struct __false_type { __false_type() {} };
template <class T> class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
template <class T, class Alloc> class vector
{
public:
	typedef T *pointer;
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
}
Rva00318B5C *Rva00318D75Copy(Rva00318B5C *first, Rva00318B5C *last, Rva00318B5C *result, const _STL::__false_type &tag);
template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last)
{
	Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
	Rva00318D75Copy((Rva00318B5C *)first, (Rva00318B5C *)last, (Rva00318B5C *)result, _STL::__false_type());
	return result;
}
template BfmeVectorRecord00319C84 *_STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >::_M_allocate_and_copy<BfmeVectorRecord00319C84 *>(unsigned int, BfmeVectorRecord00319C84 *, BfmeVectorRecord00319C84 *);
