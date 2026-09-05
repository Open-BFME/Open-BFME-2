// ?do_get@?$money_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// partial score=0.92 date=2026-09-06
﻿// ?do_get@?$money_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// partial score=0.92 date=2026-09-06
//
// THE 70-BYTE EXCESS IS SOLVED. It was istreambuf_iterator::_M_getc, inlined
// twice where retail calls it out of line at 0x00007C40 (35 bytes, already
// claimed in reverse/functions.csv). _istreambuf_iterator.h:85 defines
// _M_getc in-class, so it is implicitly inline and MSVC expands it; two
// expansions of a 35-byte body against two 5-byte calls is the whole excess.
//
// THE FIX IS AN EXPLICIT SPECIALIZATION DECLARED AHEAD OF THE INSTANTIATION:
//
//     namespace _STL {
//     template <> void istreambuf_iterator<char, char_traits<char> >::_M_getc() const;
//     }
//
// Declared and not defined, so MSVC must emit the external call, and the
// symbol is already in the ledger at 0x00007C40 so it resolves. This is a new
// technique in this tree and it generalises: any STLport helper defined
// in-class that retail calls out of line can be forced back to a call this
// way, as long as the address is already claimed or pinned. It is the third
// member of the family that includes completing an opaque type to recover an
// inlined destructor (see 0x0000BDA0).
//
// Measured with tools/locate.py, which reports the real emitted COMDAT size --
// NOT build.py, which prints exactly target_size bytes and shows a spurious
// match; this stash has been burned by that once already, see the 2026-09-02
// correction below.
//
//     before any levers          373 bytes
//     + _INC_STDLIB and ~locale  348 bytes
//     + the _M_getc spec         277 bytes   == retail, exactly
//
// The 0x0000BDA0 levers are also still in the source below and still needed:
// _INC_STDLIB ahead of <locale> so free carries C++ linkage, and the opaque
// _Locale_impl completed after the include so ~locale inlines.
//
// A SIDE EFFECT WORTH FOLLOWING UP: the same specialization drops the sibling
// string_type do_get in this instantiation from 3560 bytes to 2784. Whatever
// its retail size is, it was nowhere near before and is now plausible -- check
// it next, and expect the wide twins to want
// istreambuf_iterator<wchar_t, char_traits<wchar_t> >::_M_getc specialized the
// same way (0x0000DAA0 is the wide partner of this body and was over by the
// same amount, 344 against 277).
//
// WHAT IS LEFT is now genuinely the register allocation the 2026-09-02 note
// described, and only that. Same length, same instruction sequence, same
// calls -- including both restored _M_getc calls at `e8 86 bb ff ff` and
// `e8 6d bb ff ff`. Retail pushes FOUR callee-saved registers, `53 55 56 ...
// 57` (ebx, ebp, esi, edi), and keeps two more values live in ebx and ebp;
// this build pushes only `56 ... 57` (esi, edi) and spills those two values to
// stack slots instead. That is why the byte similarity reads low despite the
// structural match: the two missing pushes shift every later stack
// displacement by eight.
//
// So the next pass needs MSVC to enregister two more values. Untried: giving
// the two spilled values named locals with a longer live range; and checking
// whether the wide twin, which has the same shape, enregisters differently.
//
// CORRECTION 2026-09-02: the length agreement claimed below is not real.
// tools/build.py prints exactly target_size bytes of the compiled body, so a
// compiled length equal to the target length says nothing - ask it for 900
// bytes and it prints 900. The size locate.py reports for the emitted COMDAT
// is the real one, and here it is 373 bytes against 277, not 277 against
// 277. The identification still stands on the vtable slot and on the
// callees; only the size corroboration is withdrawn.
//
// The vendored instantiation is enough - no hand-written body is needed.
// Identified from the facet vtable rather than from any caller: nothing calls
// this address directly because it is a virtual. The three-slot vtable holding
// it is the money_get shape - deleting destructor plus the two do_get
// overloads - and the slot next to it is the string_type overload, whose
// derived boundary the ledger splits in two. The body confirms it against
// _monetary.c line 156: default-construct string_type __buf, call the other
// do_get through the vtable, push_back(0), hand __b/__e to
// __get_decimal_integer, or eofbit in when __s == __end, and free __buf.
//
// Retail's own call sites, decoded from the target's REL32 displacements, and
// every one of them now has a counterpart in the compiled body:
//   +0x022 0x00007850  basic_string<char>::basic_string()
//   +0x081 0x0000C330  basic_string<char>::push_back(char)
//   +0x0A5 0x0000C120  __get_decimal_integer<char*, long double>
//   +0x0B5 0x00007C40  istreambuf_iterator::_M_getc
//   +0x0CE 0x00007C40  ditto
//   +0x0F6 0x00030830  free
//
// Refuted: /O2, /O1, /Ox, /Og, /Ob2, /Gy, -D_STLP_USE_MALLOC and -D_CRTIMP=
// all give the identical renaming (/O1 is worse, 202 bytes). The source is
// upstream STLport and cannot be reordered to move the allocation without
// diverging from it.
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// money_put<char>::do_put(iter, bool, ios_base&, char_type, long double).
//
// _INC_STDLIB is defined ahead of <locale> to suppress the vendor <stdlib.h>,
// so that free can be declared with C++ LINKAGE. That is the spelling
// reverse/symbols.csv pins at 0x00030830, and it is what makes the call a
// direct e8 with the unwind state store beside it rather than a nothrow import
// thunk. Declaring free without suppressing the header is C2375.
//
// The declarations below are exactly the set the vendor <cstdlib> names in its
// using-declarations, which is what has to exist once <stdlib.h> is gone.
#define _INC_STDLIB

typedef unsigned int size_t;

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;

void __cdecl free(void *block);

extern "C" {
void __cdecl abort(void);
int __cdecl abs(int value);
int __cdecl atexit(void (__cdecl *routine)(void));
double __cdecl atof(const char *string);
int __cdecl atoi(const char *string);
long __cdecl atol(const char *string);
void *__cdecl bsearch(const void *key, const void *base, size_t count,
        size_t width, int (__cdecl *compare)(const void *, const void *));
void *__cdecl calloc(size_t count, size_t size);
div_t __cdecl div(int numerator, int denominator);
void __cdecl exit(int status);
char *__cdecl getenv(const char *name);
long __cdecl labs(long value);
ldiv_t __cdecl ldiv(long numerator, long denominator);
void *__cdecl malloc(size_t size);
int __cdecl mblen(const char *ch, size_t count);
size_t __cdecl mbstowcs(unsigned short *dest, const char *source, size_t count);
int __cdecl mbtowc(unsigned short *dest, const char *source, size_t count);
void __cdecl qsort(void *base, size_t count, size_t width,
        int (__cdecl *compare)(const void *, const void *));
int __cdecl rand(void);
void *__cdecl realloc(void *block, size_t size);
void __cdecl srand(unsigned int seed);
double __cdecl strtod(const char *string, char **end);
long __cdecl strtol(const char *string, char **end, int radix);
unsigned long __cdecl strtoul(const char *string, char **end, int radix);
int __cdecl system(const char *command);
size_t __cdecl wcstombs(char *dest, const unsigned short *source, size_t count);
int __cdecl wctomb(char *dest, unsigned short ch);
}

#include <locale>

// _locale.h forward-declares _Locale_impl as an opaque type and declares
// ~locale() without a body, so MSVC has to emit a call to it. Retail INLINES
// the destructor -- `mov ecx,[esp+0x74]; mov edx,[ecx]; call [edx+8]`, which is
// _M_impl->_M_decr() through vtable slot 2 -- so the definition was visible in
// the translation unit that produced retail's body. Completing the opaque type
// here and defining the destructor ahead of the instantiation restores that.
// The three-virtual layout is the one stlport_locale.cpp already establishes.
namespace _STL
{

class _Locale_impl
{
public:
	virtual ~_Locale_impl();
	virtual void _M_incr();
	virtual void _M_decr();

	locale::facet **_M_facets;
	unsigned int _M_count;
};

locale::~locale() _STLP_NOTHROW
{
	_M_impl->_M_decr();
}

}

// Retail CALLS istreambuf_iterator::_M_getc at 0x00007C40 (35 bytes, already
// claimed in reverse/functions.csv); _istreambuf_iterator.h:85 defines it
// in-class, so MSVC inlines it instead -- twice in this body, and that alone is
// the ~70 bytes both money_get twins were over. Declaring an explicit
// specialization ahead of the instantiation forces the external call back.
namespace _STL
{
template <> void istreambuf_iterator<char, char_traits<char> >::_M_getc() const;
}
template class _STL::money_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
