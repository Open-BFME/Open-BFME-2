// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?erase@?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAEPAUBfmePod28@@PAU3@@Z retail 0x00216267 47 bytes
// Evidence: __copy_ptrs pin plus abuts next pair-ctor row 0x00216296 plus callers 0x00216664 plus 0x002167E9 plus single-erase branch for last element
struct BfmePod28 { int a[7]; };

namespace _STL {
struct __false_type { __false_type() {} };
struct random_access_iterator_tag {};
template <class InputIter, class OutputIter> OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class T> class allocator {};
template <class T, class A> class vector {
public:
	typedef T *iterator;
	iterator erase(iterator pos);
private:
	iterator _M_start;
	iterator _M_finish;
	iterator _M_end;
};
}
_STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::iterator _STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::erase(iterator pos)
{
	iterator fin = _M_finish;
	if (pos + 1 != fin)
		_STL::__copy_ptrs(pos + 1, fin, pos, _STL::__false_type());
	--_M_finish;
	return pos;
}
