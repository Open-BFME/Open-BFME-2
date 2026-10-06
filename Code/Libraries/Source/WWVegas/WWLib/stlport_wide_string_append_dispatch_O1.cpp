// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$_M_append_dispatch@PBG@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@AAEAAV01@PBG0ABU__false_type@1@@Z
// @0x001EFC42 22B: STLport basic_string<unsigned short>::_M_append_dispatch for
// const unsigned short * iterators (the non-integral branch of the template
// append), /O1 EBP frame, ret 0xC. It forwards to the forward_iterator_tag
// append at 0x001EF83A, which the ledger rows under the honest
// rva001EF83A spelling (see stlport_wide_string_append_O1.cpp), so the call is
// spelled the same way here. Precedents: the narrow PBD (0x00015E80) and wide
// PAG (0x00019CA0) _M_append_dispatch rows. No REL32 caller found.

namespace _STL
{

struct forward_iterator_tag {};
struct __false_type {};

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
private:
	template <class InputIter>
	basic_string<CharT, Traits, Alloc> &_M_append_dispatch(InputIter first, InputIter last,
			const __false_type &)
	{
		forward_iterator_tag tag;
		return rva001EF83A(first, last, tag);
	}

	template <class ForwardIter>
	basic_string<CharT, Traits, Alloc> &rva001EF83A(ForwardIter first, ForwardIter last,
			const forward_iterator_tag &);

	CharT *_M_start;
	CharT *_M_finish;
	CharT *_M_end_of_storage;
};

template basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> > &
basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> >::_M_append_dispatch<const unsigned short *>(
		const unsigned short *, const unsigned short *, const __false_type &);

}
