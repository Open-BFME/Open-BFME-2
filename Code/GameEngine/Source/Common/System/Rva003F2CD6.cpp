// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??$_M_allocate_and_copy@PAVLivingWorldRegionConnection@@@?$vector@UBfmeStringRecord000B9534@@V?$allocator@UBfmeStringRecord000B9534@@@_STL@@@_STL@@IAEPAUBfmeStringRecord000B9534@@IPAVLivingWorldRegionConnection@@0@Z @0x003F2CD6 45B
// vector<BfmeStringRecord000B9534>::_M_allocate_and_copy, same 45B ebp-tag shape as 0x00319304 and 0x004F6C05.
// Allocates n 24B slots through the end-of-storage proxy (rowed BfmeStringRecord000B9534 allocate at 0x00395944,
// same 24B stride as LivingWorldRegionConnection) and copies the range with the 4-arg Living copy twin at
// 0x003F29D2 (tag unused, same 38B loop as rowed 3-arg CopyRange). Casts like Rva00318D75Copy precedent.
// Evidence: unlock lane, all callees rowed or pinned, caller 0x003F318C, landing unblocks it.
struct BfmeStringRecord000B9534
{
	char m_body[24];
};
class LivingWorldRegionConnection
{
	char _m[0x18];
public:
	LivingWorldRegionConnection(const LivingWorldRegionConnection &that);
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
LivingWorldRegionConnection *Rva003F29D2_CopyRange(LivingWorldRegionConnection *first, LivingWorldRegionConnection *last, LivingWorldRegionConnection *result, const _STL::__false_type &tag);
template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last)
{
	Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
	Rva003F29D2_CopyRange((LivingWorldRegionConnection *)first, (LivingWorldRegionConnection *)last, (LivingWorldRegionConnection *)result, _STL::__false_type());
	return result;
}
template BfmeStringRecord000B9534 *_STL::vector<BfmeStringRecord000B9534, _STL::allocator<BfmeStringRecord000B9534> >::_M_allocate_and_copy<LivingWorldRegionConnection *>(unsigned int, LivingWorldRegionConnection *, LivingWorldRegionConnection *);
