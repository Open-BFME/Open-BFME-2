// ?erase@?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAEPAUBfmePod28@@PAU3@0@Z
// partial score=0.97 date=2026-09-24
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
// STLport range erase over a 28-byte POD. The prvalue __false_type tag is the
// sibling stlport_vector_record_2154f3_erase shape: it keeps the tag at
// [ebp+0xb] under /O1 instead of the [ebp+0xf] a named local produces.
struct BfmePod28 { int a[7]; };
// Retail's forwarder 0x002161A5 calls the 5-arg worker 0x00215FEF, rowed as
// __copy over Rva00215FEFElement (StlSweepW5Rva00215FEF.cpp), the same 28-byte
// stride. Calling that rowed name makes this copy retail's (no unrowed
// __copy<BfmePod28*> left unresolved).
struct Rva00215FEFElement { char bytes[28]; };

#include <vector>
namespace _STL {
template <class InputIter, class OutputIter> OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}
extern template __declspec(noinline) Rva00215FEFElement *
_STL::__copy<Rva00215FEFElement *, Rva00215FEFElement *, int>(Rva00215FEFElement *first,
	Rva00215FEFElement *last, Rva00215FEFElement *result, const _STL::random_access_iterator_tag &tag, int *distance);

// ??$__copy_ptrs@PAUBfmePod28@@PAU1@@_STL@@YAPAUBfmePod28@@PAU1@00ABU__false_type@0@@Z present-unmatched
template <> __declspec(noinline) BfmePod28 *_STL::__copy_ptrs<BfmePod28 *, BfmePod28 *>(BfmePod28 *first, BfmePod28 *last, BfmePod28 *result, const _STL::__false_type &tag)
{
	return (BfmePod28 *)_STL::__copy((Rva00215FEFElement *)first, (Rva00215FEFElement *)last, (Rva00215FEFElement *)result, _STL::random_access_iterator_tag(), (int *)0);
}

template <> __declspec(noinline)
_STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::iterator _STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::erase(iterator first, iterator last)
{
	typedef iterator (*CopyFunction)(iterator, iterator, iterator, const _STL::__false_type &);
	iterator result = static_cast<CopyFunction>(&_STL::__copy_ptrs<iterator, iterator>)(
		last, _M_finish, first, _STL::__false_type());
	_M_finish = result;
	return first;
}

template _STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::iterator _STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::erase(BfmePod28 *, BfmePod28 *);
