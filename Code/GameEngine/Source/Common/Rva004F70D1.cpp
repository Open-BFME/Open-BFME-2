// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva004F70D1@Rva004F70D1@@QAEP AUTreeHintRef00217D4C@@PAU2@@Z @ 0x004F70D1 (57B). Vector erase for
// TreeHintRef00217D4C: copy [pos+1 finish) to pos via rowed __copy_ptrs 0x004F6A35 then --finish
// and destroy last via rowed deleting 0x005F8FCC returning pos. Evidence: ret 4 one ptr arg,
// finish at this+4, callers 0x005E1C6F 0x002B5BBA 0x004F9C8E.
struct TreeHintRef00217D4C
{
	void *m_target;
};

struct Rva005F8FCC
{
	void *rva005F8FCC(unsigned int flags);
};

namespace _STL
{
struct __false_type
{
};
template <class _InputIter, class _OutputIter>
_OutputIter __copy_ptrs(_InputIter first, _InputIter last, _OutputIter result, const __false_type &tag);
}

class Rva004F70D1
{
public:
	TreeHintRef00217D4C *rva004F70D1(TreeHintRef00217D4C *pos);
private:
	TreeHintRef00217D4C *m_begin;
	TreeHintRef00217D4C *m_finish;
};

TreeHintRef00217D4C *Rva004F70D1::rva004F70D1(TreeHintRef00217D4C *pos)
{
	TreeHintRef00217D4C *last = m_finish;
	TreeHintRef00217D4C *first = pos + 1;
	if (first != last) {
		_STL::__false_type tag;
		_STL::__copy_ptrs(first, last, pos, tag);
	}
	--m_finish;
	((Rva005F8FCC *)m_finish)->rva005F8FCC(0);
	return pos;
}
