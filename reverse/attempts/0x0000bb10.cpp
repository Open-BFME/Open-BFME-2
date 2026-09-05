// ??8locale@_STL@@QBE_NABV01@@Z
// partial score=0.98 date=2026-09-05
//
// Body unchanged from the previous version of this stash; what is added is the
// callee map and a precise statement of the remaining gap, so the next attempt
// does not have to rediscover either.
//
// Every callee is identified, by decoding this body's own REL32 displacements
// (target = 0x0000BB10 + offset + 5 + disp) and looking each address up in
// both ledgers:
//
//   +0x37, +0x52, +0x87 -> 0x0000BAE0  locale::name(), the three calls the
//                          source makes. functions.csv already claims it
//                          (stlport_locale_name.cpp, 34 bytes).
//   +0x97 -> 0x000077B0   operator!=(const basic_string<char>&, const
//                          basic_string<char>&), pops 2 dwords.
//                          functions.csv claims it at 65 bytes.
//   +0xC4, +0xE9, +0x10A -> 0x00030830  free, pops 1 dword. symbols.csv pins
//                          ?free@@YAXPAX@Z there; it is the same body as
//                          _free, the three inlined string destructors.
//
// Note there is NO call for the equality: retail inlines
// `name() == that.name()` as a length compare followed by `repe cmpsb`
// (`2b ce 2b d7 3b ca ... 33 c0 f3 a6`), which is what the inline operator==
// over memcmp with #pragma intrinsic already produces here. Only the
// inequality against _Nameless is out of line. _Nameless itself is the object
// at 0x00DDEB2C, pushed directly (`68 2c eb dd 00`).
//
// The remaining gap is exception-state bookkeeping, and it is four
// instructions, not a shape difference. Retail writes the state exactly twice
// (`c7 44 24 40 00 00 00 00` and `c7 44 24 38 ff ff ff ff`) and tracks which
// temporaries are live in ebx as a bitmask (`bb 03`, `bb 07`, `83 e3 fb`,
// `f6 c3 04`), which this body reproduces exactly. This body additionally
// emits, and retail does not:
//
//   c7 44 24 48 02 00 00 00   state 2, before the operator!= call
//   89 5c 24 14               spilling the ebx mask alongside it
//   c7 44 24 40 01 00 00 00   state 1, after the result byte is stored
//
// Those 12 extra bytes before the call are what turn the `74 79` at +0x2E into
// a near `0f 84 85 00 00 00` and push the whole tail out of alignment; the
// body is otherwise the same instructions in the same registers. So the
// question is what makes MSVC collapse three try-region transitions into one
// here, i.e. why retail needs no state change around the _Nameless
// comparison when three string temporaries are live across it.
//
// Ruled out: the EH model. /EHsc, /EHs /EHc- and /O2 /EHsc all produce
// byte-identical output for this body; /O1 produces a 237-byte body that is
// not close.
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 locale::operator==. Two impls that are the same object are
// the same locale; otherwise the names decide, and a nameless locale is
// never equal to anything.

void __cdecl free(void *block);

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
	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

	basic_string(const basic_string<CharT, Traits, Alloc> &that);
	~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}

	const CharT *data() const { return _M_start; }
	size_type size() const { return (size_type)(_M_finish - _M_start); }

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

template <class CharT, class Traits, class Alloc>
bool __cdecl operator!=(const basic_string<CharT, Traits, Alloc> &x,
	const basic_string<CharT, Traits, Alloc> &y);

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);
#pragma intrinsic(memcmp)

template <class CharT, class Traits, class Alloc>
inline bool __cdecl operator==(const basic_string<CharT, Traits, Alloc> &x,
	const basic_string<CharT, Traits, Alloc> &y)
{
	return x.size() == y.size() && memcmp(x.data(), y.data(), x.size()) == 0;
}

class _Locale_impl;

class locale
{
public:
	string name() const;
	bool operator==(const locale &that) const;

private:
	_Locale_impl *_M_impl;
};

extern const string _Nameless;

bool locale::operator==(const locale &that) const
{
	return _M_impl == that._M_impl ||
		(name() == that.name() && name() != _Nameless);
}

}
