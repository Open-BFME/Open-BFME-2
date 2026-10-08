// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?do_transform@?$collate@G@_STL@@MBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@PBG0@Z
// @0x000178F0 (87B)
//
// STLport 4.5.3 collate<wchar_t>::do_transform, identified by slot 2 of
// ??_7?$collate@G@_STL@@6B@. Its _collate.h declaration places this virtual
// between do_compare and do_hash. Retail initializes the returned basic_string
// from the input range through the matched _M_range_initialize body at 0xBF90.
// BFME1 e8d95f1561 Bfme5WideStringRanges.cpp proves that exposing the
// unused tag argument enables reuse of the hidden-result stack slot.

typedef unsigned short wchar_t;

namespace _STL
{

struct forward_iterator_tag {};

template <class T>
class char_traits {};

template <class T>
class allocator {};

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
	__declspec(noinline) void _M_range_initialize(InputIter f, InputIter l, const forward_iterator_tag &);
private:
	void _M_allocate_block(unsigned int count);
	__declspec(dllimport) __forceinline void _M_terminate_string() { *_M_finish = CharT(); }
};

void *__cdecl __copy_trivial(const void *first, const void *last, void *result);

__declspec(dllimport) __forceinline unsigned short *uninitialized_copy(
        const unsigned short *first, const unsigned short *last, unsigned short *result)
{
    return static_cast<unsigned short *>(__copy_trivial(first, last, result));
}

// Keep allocation and copying out of line, as in the retail 53-byte helper.
// Its visible unused tag is also needed by do_transform's stack allocation.
template <class CharT, class Traits, class Alloc>
template <class InputIter>
__declspec(noinline) void basic_string<CharT, Traits, Alloc>::_M_range_initialize(
        InputIter first, InputIter last, const forward_iterator_tag &)
{
    int count = static_cast<int>(last - first);
    _M_allocate_block(count + 1);
    _M_finish = uninitialized_copy(first, last, _M_start);
    _M_terminate_string();
}

class locale
{
public:
	class facet
	{
	protected:
		virtual ~facet();
	};
};

template <class CharT>
class collate : public locale::facet
{
public:
	typedef basic_string<CharT, char_traits<CharT>, allocator<CharT> > string_type;
protected:
	virtual ~collate();
	virtual int do_compare(const CharT *, const CharT *, const CharT *, const CharT *) const;
	virtual string_type do_transform(const CharT *low, const CharT *high) const;
	virtual long do_hash(const CharT *, const CharT *) const;
};

template <>
class collate<wchar_t> : public locale::facet
{
public:
	typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > string_type;
protected:
	virtual ~collate();
	virtual int do_compare(const wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *) const;
	virtual string_type do_transform(const wchar_t *low, const wchar_t *high) const;
	virtual long do_hash(const wchar_t *, const wchar_t *) const;
};

collate<wchar_t>::string_type collate<wchar_t>::do_transform(
	const wchar_t *low, const wchar_t *high) const
{
	allocator<wchar_t> a;
	return string_type(low, high, a);
}

}
