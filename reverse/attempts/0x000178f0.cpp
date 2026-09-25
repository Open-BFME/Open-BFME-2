// ?init@Rva000178F0StringInit@@QAE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@PBG0@Z
// partial score=0.98 date=2026-09-25
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
namespace _STL
{
struct forward_iterator_tag {};
template <class T> class char_traits {};
template <class T> class allocator {};
template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	_STLP_alloc_proxy(const Alloc &a, Pointer data) : Alloc(a), _M_data(data) {}
	Pointer _M_data;
};
template <class CharT, class Alloc>
class _String_base
{
public:
	_String_base(const Alloc &a) : _M_start(0), _M_finish(0), _M_end_of_storage(a, 0) {}
	~_String_base();
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};
template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	typedef Alloc allocator_type;
	template <class InputIter>
	basic_string(InputIter f, InputIter l, const Alloc &a) : _String_base<CharT, Alloc>(a)
	{
		forward_iterator_tag t;
		_M_range_initialize(f, l, t);
	}
	template <class InputIter>
	void _M_range_initialize(InputIter f, InputIter l, const forward_iterator_tag &);
};
typedef basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > WStr;
}
class Rva000178F0StringInit
{
public:
	_STL::WStr init(const unsigned short *a, const unsigned short *b);
};
_STL::WStr Rva000178F0StringInit::init(const unsigned short *a, const unsigned short *b)
{
	_STL::allocator<unsigned short> al;
	return _STL::WStr(a, b, al);
}
