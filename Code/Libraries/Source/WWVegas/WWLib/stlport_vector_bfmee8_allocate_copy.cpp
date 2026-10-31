// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_M_allocate_and_copy@PAVRva00468520@@@?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@IAEPAUBfmeE8@@IPAVRva00468520@@0@Z, retail 0x00153489, 45 bytes.
// Allocate n via allocator at +8 then uninitialized-copy first to last via rowed Rva00153425Copy.
// Evidence: push 0 push [ebp+8] add ecx 8 call allocate 0x523D6C then lea [ebp+0xB] tag push esi push [ebp+0x10] push [ebp+0x0C] call copy 0x153425 ret 0xC; same 45B ebp-tag shape as 0x00319304; caller 0x15380D; callees rowed.
#include <vector>
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
	char x; // +0x00
};
Rva00468520 *Rva00153425Copy(Rva00468520 *first, Rva00468520 *last, Rva00468520 *result, const Tag &tag);
namespace _STL { template <> BfmeE8 *allocator<BfmeE8>::allocate(unsigned int, const void *) const; }
struct Rva005F8F96;
// The row 0x00153489 names retail's folded allocate-and-copy under vector<BfmeE8>, which
// nothing here otherwise uses: only that member and the three words it needs are declared.
namespace _STL
{
template <> class vector<BfmeE8, allocator<BfmeE8> >
{
	friend class vector<Rva005F8F96, allocator<Rva005F8F96> >;
protected:
	template <class ForwardIter>
	BfmeE8 *_M_allocate_and_copy(unsigned int n, ForwardIter first, ForwardIter last);
private:
	BfmeE8 *_M_start;
	BfmeE8 *_M_finish;
	_STLP_alloc_proxy<BfmeE8 *, BfmeE8, allocator<BfmeE8> > _M_end_of_storage;
};
}
template <class ForwardIter>
BfmeE8 *_STL::vector<BfmeE8, _STL::allocator<BfmeE8> >::_M_allocate_and_copy(unsigned int n, ForwardIter first, ForwardIter last)
{
	BfmeE8 *result = _M_end_of_storage.allocate(n);
	Rva00153425Copy((Rva00468520 *)first, (Rva00468520 *)last, (Rva00468520 *)result, Tag());
	return result;
}
template BfmeE8 *_STL::vector<BfmeE8, _STL::allocator<BfmeE8> >::_M_allocate_and_copy<Rva00468520 *>(unsigned int, Rva00468520 *, Rva00468520 *);
