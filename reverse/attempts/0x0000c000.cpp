// ?do_get@?$money_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// partial score=0.9 date=2026-09-05
﻿// ?do_get@?$money_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// partial score=0.9 date=2026-09-05
//
// UPDATE 2026-09-05: the two levers that landed money_put::do_put(long double)
// at 0x0000BDA0 have been applied here and they help, but they do NOT close
// this body. Both are in the source below; keep them.
//
//   * _INC_STDLIB ahead of <locale>, so free carries C++ linkage. See the
//     0x0000BDA0 landing for why the extern "C" spelling is wrong: it is
//     nothrow, so MSVC reaches it through the import and drops the unwind
//     state store retail carries beside it.
//   * the opaque _Locale_impl completed after the include and ~locale defined
//     ahead of the instantiation, so the destructor inlines as
//     _M_impl->_M_decr() rather than being called out of line.
//
// Measured with tools/locate.py, which reports the real emitted COMDAT size --
// NOT with build.py, which prints exactly target_size bytes and would show a
// spurious 277 (the correction below made that mistake once already):
//
//     before the levers   373 bytes
//     after  the levers   348 bytes
//     retail              277 bytes
//
// So the recipe removed 25 bytes of the 96-byte excess and 71 remain. The
// register-allocation difference the note below describes is still there --
// the first divergence is at +0x28, `8b 7c 24 50` in retail against
// `8b 6c 24 50` here, retail's edi where MSVC picks ebp -- but that is a
// same-length substitution and cannot account for 71 bytes. Something in this
// body is still structurally larger than retail's, and THAT is what the next
// pass should find, before touching registers again.
//
// CORRECTION 2026-09-02: the length agreement claimed below is not real.
// tools/build.py prints exactly target_size bytes of the compiled body, so a
// compiled length equal to the target length says nothing - ask it for 900
// bytes and it prints 900. The size locate.py reports for the emitted COMDAT
// is the real one, and here it is 373 bytes against 277, not 277 against
// 277. The identification still stands on the vtable slot and on the
// callees; only the size corroboration is withdrawn.
//
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
// The two _M_getc calls with the [esp+0x3e]/[esp+0x46] byte compare after
// them are istreambuf_iterator::equal inlined.
//
// The whole difference is which callee-saved register holds which value: retail
// loads [esp+0x50] into edi and [esp+0x40] into ebp, cl 13.10 loads them into
// ebp and ebx. Both push the same four registers in the same order, so the
// prologue matches and the first difference is at 0x28.
//
// Refuted: /O2, /O1, /Ox, /Og, /Ob2, /Gy, -D_STLP_USE_MALLOC and -D_CRTIMP=
// all give the identical 277 bytes with the identical renaming (/O1 is worse,
// 202 bytes). The source is upstream STLport and cannot be reordered to move
// the allocation without diverging from it.
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

template class _STL::money_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
