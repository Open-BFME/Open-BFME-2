// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// partial score=0.92 date=2026-09-06
﻿// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// partial score=0.92 date=2026-09-06
//
// THE ~70-BYTE EXCESS IS SOLVED HERE TOO, by the same fix the narrow twin at
// 0x0000C000 carries: istreambuf_iterator::_M_getc was being inlined twice
// where retail calls it out of line. _istreambuf_iterator.h:85 defines it
// in-class, so it is implicitly inline; an explicit specialization declared and
// NOT defined ahead of the instantiation forces the external call back, and it
// links because the address is already claimed in reverse/functions.csv. For
// the wide instantiation that is 0x0000A0A0 (68 bytes):
//
//     namespace _STL {
//     template <> void istreambuf_iterator<wchar_t, char_traits<wchar_t> >::_M_getc() const;
//     }
//
// Emitted sizes, from tools/locate.py -- NOT build.py, which prints exactly
// target_size bytes and shows a spurious match:
//
//     before any levers          373 (narrow) / 344 (wide)
//     + _INC_STDLIB and ~locale  348 (narrow) / 344 (wide)
//     + the _M_getc spec         277 (narrow) / 281 (wide)
//     retail                     277           / 277
//
// So the narrow twin is now exactly the right size and this one is FOUR BYTES
// over. That is the whole remaining structural difference here, and four bytes
// is one instruction: the likely candidate is a widening or a movzx that the
// wide element needs and the narrow one does not. Find it by diffing this
// body's instruction stream against the narrow twin's rather than against
// retail -- the twins should differ only in element width.
//
// The 0x0000BDA0 levers are in the source below and still needed: _INC_STDLIB
// ahead of <locale> so free carries C++ linkage, and the opaque _Locale_impl
// completed after the include so ~locale inlines.
//
// BEYOND THE FOUR BYTES the remaining difference is register allocation, the
// same as the narrow twin: retail pushes four callee-saved registers and keeps
// two more values live in ebx and ebp, where this build pushes two and spills
// them to stack slots, shifting every later displacement by eight. /O2 was
// re-tested on the narrow twin AFTER the size was corrected and produces
// byte-identical output, so it is already the default and the earlier
// refutation of /O2, /O1, /Ox, /Og, /Ob2 and /Gy still stands under the new
// shape. Do not re-run that sweep; the next idea is to give the two spilled
// values named locals with a longer live range.
//
// A side effect worth following up: the same specialization drops the sibling
// wide string_type do_get from 3692 bytes to 3376. Its retail size is 2528 per
// reverse/re_attempts.log (the ledger's 122-byte gen row at 0x00011230 covers
// only part of it -- the boundary is split), so that one is still well over
// and needs its own investigation.
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
template <> void istreambuf_iterator<wchar_t, char_traits<wchar_t> >::_M_getc() const;
}
template class _STL::money_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
