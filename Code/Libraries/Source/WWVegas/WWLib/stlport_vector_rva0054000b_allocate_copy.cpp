// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??$_M_allocate_and_copy@PAVRva0054000B@@@?$vector@VRva0054000B@@V?$allocator@VRva0054000B@@@_STL@@@_STL@@IAEPAVRva0054000B@@IPAV2@0@Z @0x0054016A 45B
// Evidence: caller 0x005406B7 plus rowed allocate 0x000B4039 via Rva pin plus rowed copy 0x005400B4; same 45B ebp-tag shape as 0x00319304 and 0x001FFA2D
class Rva0054000B
{
	char m_pad[40];
public:
	Rva0054000B(const Rva0054000B &that);
};
namespace _STL
{
struct __false_type { __false_type() {} };
template <class T> class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
template <class InputIter, class ForwardIter> ForwardIter __uninitialized_copy(InputIter, InputIter, ForwardIter, const __false_type &);
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
template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last)
{
	Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
	_STL::__uninitialized_copy((const Rva0054000B *)first, (const Rva0054000B *)last, (Rva0054000B *)result, _STL::__false_type());
	return result;
}
template Rva0054000B *_STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> >::_M_allocate_and_copy<Rva0054000B *>(unsigned int, Rva0054000B *, Rva0054000B *);
