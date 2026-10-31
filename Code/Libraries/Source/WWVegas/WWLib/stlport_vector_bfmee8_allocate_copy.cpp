// cl: /O1
// ??$_M_allocate_and_copy@PAVRva00468520@@@?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@IAEPAUBfmeE8@@IPAVRva00468520@@0@Z, retail 0x00153489, 45 bytes.
// Allocate n via allocator at +8 then uninitialized-copy first to last via rowed Rva00153425Copy.
// Evidence: push 0 push [ebp+8] add ecx 8 call allocate 0x523D6C then lea [ebp+0xB] tag push esi push [ebp+0x10] push [ebp+0x0C] call copy 0x153425 ret 0xC; same 45B ebp-tag shape as 0x00319304; caller 0x15380D; callees rowed.
struct BfmeE8
{
	int a;
	int b;
};
class Rva00468520;
// ??0Tag@@QAE@XZ present-unmatched
struct Tag
{
public:
	Tag() {}
	char x; // +0x00 +0x00
};
Rva00468520 *Rva00153425Copy(Rva00468520 *first, Rva00468520 *last, Rva00468520 *result, const Tag &tag);
namespace _STL
{
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
	struct Proxy
	{
		allocator<T> m_alloc;
		pointer m_data;
	};
	Proxy m_endOfStorage;
};
}
template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last)
{
	Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
	Rva00153425Copy((Rva00468520 *)first, (Rva00468520 *)last, (Rva00468520 *)result, Tag());
	return result;
}
template BfmeE8 *_STL::vector<BfmeE8, _STL::allocator<BfmeE8> >::_M_allocate_and_copy<Rva00468520 *>(unsigned int, Rva00468520 *, Rva00468520 *);
