// cl: /DNDEBUG /MD
// ??$uninitialized_fill_n@PAV?$vector@IV?$allocator@I@_STL@@@_STL@@IV12@@_STL@@YAPAV?$vector@IV?$allocator@I@_STL@@@0@PAV10@IABV10@@Z @0x003F1EEB 27B:
// _STL::uninitialized_fill_n for _STL::vector<unsigned int> (12-byte payload).
// Untagged dispatcher: forwards (first n value) to the rowed tagged worker at
// 0x003F1A8C (rowed as ?dup_003F1A8C@@YAXXZ) with a false_type tag temporary at
// ebp-1. Calls through the dup address per Rva003F1EA8UninitCopy precedent so
// the gate resolves. Caller 0x003F35E3.
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A = allocator<T> > class vector
{
public:
	void *_M_start;
	void *_M_finish;
	void *_M_end_of_storage;
};
struct __false_type {};
}
void __cdecl dup_003F1A8C(void);
typedef _STL::vector<unsigned int, _STL::allocator<unsigned int> > FillUIntVec;
typedef FillUIntVec *(__cdecl *UIntFillNFn)(FillUIntVec *, unsigned int, const FillUIntVec &, const _STL::__false_type &);
namespace _STL
{
template <class ForwardIter, class Size, class T>
ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &x)
{
	__false_type tag;
	return ((UIntFillNFn)&dup_003F1A8C)(first, n, x, tag);
}
}
template FillUIntVec *_STL::uninitialized_fill_n(FillUIntVec *, unsigned int, const FillUIntVec &);
