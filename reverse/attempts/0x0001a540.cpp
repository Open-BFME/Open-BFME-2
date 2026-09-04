// ?__insert_grouping@_STL@@YAHPAG0ABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@1@GGGH@Z
// partial score=0.85 date=2026-09-04
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __insert_grouping, the wide instantiation. num_put runs this
// thousands-separator pass over a formatted digit buffer. It lives in STLport's
// src/, which the vendored tree does not carry, so this is reconstructed from
// retail; the char twin sits next door at 0x0001A4A0.
//
// The name is the full gate's reloc-sweep identity from the num_get and
// num_put call sites already landed: only the buffer and the three separator
// characters widen, the grouping string stays NARROW. Retail writes it as a
// plain __cdecl free function, not a template - a template gains the @G@
// argument in the mangled name and stops matching the reloc name.
//
// Two details the bytes fix. grouping.size() is recomputed on every pass - the
// loop reloads both string pointers and subtracts them rather than hoisting -
// and the group size is read through movsx, so the grouping bytes are signed
// and a negative entry ends the loop the same way a zero does.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *destination,
		const void *source, unsigned int count);

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

	__declspec(dllimport) __forceinline size_type size() const
	{
		return static_cast<size_type>(_M_finish - _M_start);
	}
	__declspec(dllimport) __forceinline const CharT *data() const
	{
		return _M_start;
	}

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

typedef unsigned short Char;

int __cdecl __insert_grouping(Char *first, Char *last,
		const narrow_string &grouping, Char separator, Char Plus, Char Minus,
		int basechars)
{
	if (first == last)
		return 0;

	int groupsize = 0;
	int sign = 0;
	if (*first == Plus || *first == Minus)
	{
		sign = 1;
		++first;
	}

	first += basechars;

	unsigned int n = 0;
	Char *cur_group = last;

	for (;;)
	{
		if (n < grouping.size())
			groupsize = grouping.data()[n];
		++n;

		if (groupsize <= 0)
			break;
		if (groupsize >= cur_group - first)
			break;

		cur_group -= groupsize;
		++last;

		if (last - cur_group > 0)
			memmove(cur_group + 1, cur_group, (last - cur_group) * sizeof(Char));
		*cur_group = separator;
	}

	return (int)(last - first) + sign + basechars;
}

}
