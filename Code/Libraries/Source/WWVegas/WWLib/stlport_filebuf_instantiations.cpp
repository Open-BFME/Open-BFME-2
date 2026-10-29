// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// Ported from Open-BFME-1's game/stlport/FilebufInstantiations.cpp
// (donor revision: reference/open-bfme-1 @ a38d345e) by tools/bfme1_sweep.py:
// these STLport 4.5.3 basic_filebuf two-argument `open` instantiations are
// byte-identical between lotrbfme.exe and game.dat once relocation slots are
// set aside -- tier T1 "clean transfer", cl: /EHsc /MD /D_STLP_USE_STATIC_LIB.
//
// The donor file itself is held at copy-tier P: its destination Code/stlport/
// is not an allowed root for a new source (.githooks/pre-commit placement
// rule), so the whole-file copy cannot land. The bodies are ported here
// instead, beside Code/Libraries/Source/WWVegas/WWLib/stlport_filebuf_open.cpp,
// which already owns the row the body calls: _Filebuf_base::_M_open at
// 0x0001D390 (245B, matched).
//
// The declarations are TU-local, as Code/stlport/BasicStringNarrowSizeCtor.cpp
// does it: the vendored <fstream> defines this member inline, so a local class
// carrying the same template parameter list is what lets the single member
// this repo has a row for be instantiated on its own. Nothing else of the
// class is emitted.
//
// _Filebuf_base sits at this+0x54 in the narrow instantiation and this+0x24 in
// the wide one; the leading pad carries that per-CharT offset. No
// reverse/symbols.csv pin is needed -- the callee resolves through the ledger
// and the body reaches no global.

#include <stddef.h>

namespace _STL
{

template <class T>
class char_traits
{
};

class _Filebuf_base
{
public:
	bool _M_open(const char *name, int mode, long protection);
};

template <class CharT>
struct FilebufLeadingPad;

template <>
struct FilebufLeadingPad<char>
{
	char m_pad[0x54];
};

template <>
struct FilebufLeadingPad<wchar_t>
{
	char m_pad[0x24];
};

template <class CharT, class Traits>
class basic_filebuf : public FilebufLeadingPad<CharT>
{
public:
	basic_filebuf *open(const char *name, int mode);

	_Filebuf_base _M_base;
};

template <class CharT, class Traits>
basic_filebuf<CharT, Traits> *basic_filebuf<CharT, Traits>::open(const char *name, int mode)
{
	return _M_base._M_open(name, mode, 0x80) ? this : 0;
}

// 0x0001D7B0  36B  narrow instantiation, _Filebuf_base at this+0x54.
template basic_filebuf<char, char_traits<char> > *
basic_filebuf<char, char_traits<char> >::open(const char *, int);

// 0x0001D870  36B  wide instantiation, _Filebuf_base at this+0x24.
template basic_filebuf<wchar_t, char_traits<wchar_t> > *
basic_filebuf<wchar_t, char_traits<wchar_t> >::open(const char *, int);

}
