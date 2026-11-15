// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide istreambuf_iterator numeric input specialization. Numeric
// text is accumulated in a narrow string before the long-double conversion.

namespace _STL
{

// Retail calls free directly (the game allocator at 0x00030830), not through
// the CRT import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

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
	basic_string();
	__forceinline ~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

class ios_base
{
public:
	typedef int iostate;

	enum
	{
		goodbit = 0,
		eofbit = 2,
		failbit = 4
	};
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	__declspec(dllimport) __forceinline bool equal(
			const istreambuf_iterator &other) const
	{
		if (_M_buf != 0)
			_M_getc();
		if (other._M_buf != 0)
			other._M_getc();
		return _M_eof == other._M_eof;
	}

private:
	void _M_getc() const;

	void *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

typedef istreambuf_iterator<char, char_traits<char> > narrow_iterator;

template <class InputIter, class CharT>
bool __cdecl _M_read_float(
		narrow_string &, InputIter &, InputIter &, ios_base &, CharT *);

void __cdecl __string_to_float(const narrow_string &, long double &);

template <class CharT, class InputIter>
class num_get
{
protected:
	virtual InputIter do_get(
			InputIter, InputIter, ios_base &, ios_base::iostate &,
			long double &) const;
};

template <class CharT, class InputIter>
InputIter num_get<CharT, InputIter>::do_get(
		InputIter in, InputIter end, ios_base &stream,
		ios_base::iostate &error, long double &value) const
{
	narrow_string buffer;
	bool ok = _M_read_float(buffer, in, end, stream, (CharT *)0);
	__string_to_float(buffer, value);
	error = static_cast<ios_base::iostate>(
			ok ? ios_base::goodbit : ios_base::failbit);
	if (in.equal(end))
		error |= ios_base::eofbit;
	return in;
}

template narrow_iterator num_get<char, narrow_iterator>::do_get(
		narrow_iterator, narrow_iterator, ios_base &, ios_base::iostate &, long double &) const;

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva0007FAB3Vector@@QAE@XZ=??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1CollapseFXVec@@QAE@XZ=??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1CollapseOCLVec@@QAE@XZ=??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1RubbleFXVec@@QAE@XZ=??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1RubbleOCLVec@@QAE@XZ=??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ")
