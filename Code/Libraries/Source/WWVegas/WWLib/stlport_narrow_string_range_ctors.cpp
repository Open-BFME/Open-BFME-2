// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow-string range constructions that retail keeps as
// small out-of-line bodies next to the string TU's own emissions.
//
// WHAT THE BYTES SHOW. Five unclaimed bodies in the 0x000177E0-0x00019D30
// band share one shape: an SEH prolog, three zeroed dwords into the
// destination, then a single call into the ledger's matched narrow 2-arg
// range initialiser at 0x00008D00, returning the destination:
//
// - 0x000177E0 (80B): genuine thiscall over (first, last, alloc); the
//   allocator is stateless so the third parameter is ignored. Same
//   signature as the template range ctor rowed at 0x00017830, but retail
//   keeps the 2-arg initialiser out of line here instead of inlining down
//   to the 3-arg tag overload, so this address is a dup_ of that name.
// - 0x00017890 (82B): collate<char>::do_transform, slot 2 of retail's
//   RTTI-named vftable ??_7?$collate@D@_STL@@6B@ (0x007BBB50; the wide twin
//   sits in the same slot of 0x007BBB64). Hidden-pointer shape (this unused)
//   over the two range parameters; the temporary range ctor
//   range-initialises directly into the hidden result. Retail calls the
//   char* 2-arg initialiser at 0x00008D00 (the const char* instantiation
//   folded onto it), so the range is passed as char*.
// - 0x00017A40 / 0x00017AA0 / 0x00019D30 (85B each; the last is
//   moneypunct<char, true>::do_grouping, see below): hidden-pointer shape
//   over no parameters; methods returning a copy of a static narrow string.
//   The copy constructor zeroes first and only then reads the
//   static's start/finish, which is why the global loads sit below the
//   zeroing (a temporary would evaluate its arguments first). Each static
//   uses the existing initializer-owned storage named below.
//
// WHY THIS MODEL. The TU mirrors the Code/WWLib/stlport_narrow_string_cstr_ctor.cpp
// precedent: minimal _STL replicas with an inline base (so the zeroing is
// inlined) and a declared-only 2-arg range initialiser (so the call stays
// out of line and resolves by name to 0x00008D00). The temporary/copy
// constructions inline into the hidden result exactly like retail.

namespace _STL
{

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
		_M_range_initialize(f, l);
	}

	basic_string(const basic_string &src) : _String_base<CharT, Alloc>(allocator_type())
	{
		_M_range_initialize(src._M_start, src._M_finish);
	}

	const allocator_type &get_allocator() const;

	template <class InputIter>
	void _M_range_initialize(InputIter f, InputIter l);
};

typedef basic_string<char, char_traits<char>, allocator<char> > NStr;

// 0x000177E0: the out-of-line template range ctor (dup_ of the name rowed
// at 0x00017830, whose TU inlines down to the 3-arg tag overload instead).
template NStr::basic_string(char *, char *, const allocator<char> &);

}

// Rva007AB8D0StringInits.cpp owns these native string storage addresses and
// constructs "true", "false" and "", respectively. Use its existing names;
// the copy reads the established narrow-string view at +0 and +4.
extern unsigned int g_Va00DDEF08[3];
extern unsigned g_Va00DDEEFC;
extern unsigned g_Va00DDEF38;

namespace _STL
{

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

// 0x00017890: build a narrow string from the input range.
template <>
collate<char>::string_type collate<char>::do_transform(const char *low, const char *high) const
{
	allocator<char> al;
	return NStr(const_cast<char *>(low), const_cast<char *>(high), al);
}

}

namespace _STL
{

template <class CharT>
class numpunct;

template <>
class numpunct<char> : public locale::facet
{
protected:
	virtual NStr do_truename() const;
	virtual NStr do_falsename() const;
};

// 0x00017A40: numpunct<char>::do_truename, slot 4 of retail's RTTI-named
// vftable 0x007BBB78 (.?AV?$numpunct@D@_STL@@): copy of the static "true"
// string at 0x00DDEF08.
NStr numpunct<char>::do_truename() const
{
	return *reinterpret_cast<const NStr *>(&g_Va00DDEF08);
}

// 0x00017AA0: numpunct<char>::do_falsename, slot 5 of 0x007BBB78: copy of the
// static "false" string at 0x00DDEEFC.
NStr numpunct<char>::do_falsename() const
{
	return *reinterpret_cast<const NStr *>(&g_Va00DDEEFC);
}

}

namespace _STL
{

template <class CharT, bool International>
class moneypunct;

template <>
class moneypunct<char, true> : public locale::facet
{
protected:
	virtual NStr do_grouping() const;
};

// 0x00019D30: moneypunct<char, true>::do_grouping, slot 3 of retail's
// RTTI-named vftable 0x007BC810 (.?AV?$moneypunct@D$00@_STL@@). STLport
// 4.5.3 returns its file-static empty string (storage 0x00DDEF38) from
// do_grouping / do_curr_symbol / do_positive_sign / do_negative_sign of both
// narrow moneypuncts and do_grouping of both wide ones; retail folds all ten
// onto this body (slots 3-6 of 0x007BC810 / 0x007BC83C, slot 3 of 0x007BC868 /
// 0x007BC894). The other nine names bind here through the moneypunct units'
// /alternatename lines.
NStr moneypunct<char, true>::do_grouping() const
{
	return *reinterpret_cast<const NStr *>(&g_Va00DDEF38);
}

}
