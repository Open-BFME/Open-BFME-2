// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?erase@?$vector@URva0054107FRecord@@V?$allocator@URva0054107FRecord@@@_STL@@@_STL@@QAEPAURva0054107FRecord@@PAU3@@Z @0x005412E2 47B single erase
// Evidence: chain lane calls rowed copy wrapper 0x00541214 which folds pin __copy_ptrs for this 28-byte record; shape-identical 47B single erase precedent 0x00216267 pod28; range-erase sibling 0x0054152D same vector; caller 0x00541883
struct Rva0054107FRecord { Rva0054107FRecord(); Rva0054107FRecord(const Rva0054107FRecord&); Rva0054107FRecord& operator=(const Rva0054107FRecord&); private: char bytes[28]; };

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
_STL::vector<Rva0054107FRecord, _STL::allocator<Rva0054107FRecord> >::iterator _STL::vector<Rva0054107FRecord, _STL::allocator<Rva0054107FRecord> >::erase(iterator pos)
{
	iterator fin = _M_finish;
	if (pos + 1 != fin)
		_STL::__copy_ptrs(pos + 1, fin, pos, _STL::__false_type());
	--_M_finish;
	return pos;
}
