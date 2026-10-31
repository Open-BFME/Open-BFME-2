// cl: /DBFME_ASCII_DTOR_DECL /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?erase@?$vector@UBfmeObject476@@V?$allocator@UBfmeObject476@@@_STL@@@_STL@@QAEPAUBfmeObject476@@PAU3@0@Z @0x001FEFB9 51B: range erase over vector<BfmeObject476>. Shifts tail down with rowed __copy_ptrs 0x001FEF62 then destroys vacated tail with rowed _Destroy 0x001FD6A4 stores new finish returns first. Evidence: retail 51B push-ebp frame plus lea-tag at ebp+b plus copy then destroy shape calling rowed copy_ptrs and Destroy; callers 0x001FF21D 0x001FF26B; sibling BfmeAssignRecord172 erase 0x001EBDFA 51B prvalue false_type tag shape.
#include <vector>

struct BfmeObject476 { virtual ~BfmeObject476(); unsigned char opaque[472]; BfmeObject476(); BfmeObject476(const BfmeObject476 &); BfmeObject476 &operator=(const BfmeObject476 &); };
// Rowed in StlportObject476Vector.cpp: this unit calls them and emits no copy.
namespace _STL { template <> BfmeObject476 *__copy<BfmeObject476 *, BfmeObject476 *, int>(BfmeObject476 *, BfmeObject476 *, BfmeObject476 *, const random_access_iterator_tag &, int *); }
namespace _STL { template <> void _Destroy<BfmeObject476 *>(BfmeObject476 *, BfmeObject476 *); }

// Retail's forwarder takes the tag by const reference and keeps its own body;
// the bfmealloc shim's by-value overload is force-inlined.
namespace _STL {
template <class InputIter, class OutputIter> OutputIter __copy_ptrs(InputIter, InputIter, OutputIter, const __false_type &);
template <> __declspec(noinline) BfmeObject476 *__copy_ptrs<BfmeObject476 *, BfmeObject476 *>(BfmeObject476 *first, BfmeObject476 *last, BfmeObject476 *result, const __false_type &)
{
	random_access_iterator_tag category;
	return __copy(first, last, result, category, (int *)0);
}
template <> BfmeObject476 *vector<BfmeObject476, allocator<BfmeObject476> >::erase(BfmeObject476 *first, BfmeObject476 *last)
{
	BfmeObject476 *result = static_cast<BfmeObject476 *(*)(BfmeObject476 *, BfmeObject476 *, BfmeObject476 *, const __false_type &)>
		(&__copy_ptrs<BfmeObject476 *, BfmeObject476 *>)(last, _M_finish, first, __false_type());
	_Destroy(result, _M_finish);
	_M_finish = result;
	return first;
}
}

// vector::clear (retail 0x001FF218, rowed in StlportVectorClearForwarders.cpp) calls
// erase; instantiating it makes this file emit erase's body.
template void _STL::vector<BfmeObject476>::clear();
