// cl: /MD /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// _STL::for_each<Rva004E5A78 **, Rva004E5CB0Deleter> @0x004E5D4D 33B, caller
// 0x004E5D6E (three pushed args: first, last and the empty functor byte).
// Target evidence: the functor is passed and returned by value (mov al from
// its stack byte) and its operator() is called thiscall with ecx = &functor
// (lea ecx, [ebp+0x10]); the callee 0x004E5CB0 null-checks, runs the rowed
// Rva004E5A78 dtor and frees, so the elements are Rva004E5A78 pointers. That
// body is rowed as a stdcall free function; its thiscall functor spelling is
// pinned in symbols.csv (identical bytes: ret 4, this unused).
// Structural inference: STLport for_each, functor operator() out of line.
#include <algorithm>

class Rva004E5A78;

struct Rva004E5CB0Deleter
{
	void operator()(Rva004E5A78 *p) const;
};

template Rva004E5CB0Deleter _STL::for_each<Rva004E5A78 **, Rva004E5CB0Deleter>(Rva004E5A78 **, Rva004E5A78 **, Rva004E5CB0Deleter);
