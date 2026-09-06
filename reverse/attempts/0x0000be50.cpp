// ?do_put@?$money_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@_NAAVios_base@2@GO@Z
// partial score=0.859 date=2026-09-06
// ?do_put@?$money_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@_NAAVios_base@2@GO@Z
// partial score=0.859 date=2026-09-05
﻿// ?do_put@?$money_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@_NAAVios_base@2@GO@Z
// partial score=0.859 date=2026-09-05
//
// STLport 4.5.3 money_put<wchar_t>::do_put(iter, bool, ios_base&, char_type,
// long double), retail 0x0000BE50, 205 bytes. First attempt on this address.
// It is the wide twin of 0x0000BDA0, which landed byte-exact.
//
// IDENTITY IS SETTLED three independent ways.
//
// From the vtable: tools/vtable_owner.py puts this in a three-slot facet
// vtable [0x000072C0 deleting destructor, 0x0000DF20, 0x0000BE50], and the
// vtable immediately before it has the same shape with both non-destructor
// slots already attributed -- 0x00012190 and 0x0000DAA0, the latter banked as
// money_get<wchar_t>::do_get. The slot after this vtable is num_get<wchar_t>,
// so this is the wide facet neighbourhood. Same pairing as the narrow pair, so
// 0x0000DF20 is do_put(const string_type&) and this is the long-double one.
//
// From the callees, decoded from this body's own REL32 displacements:
//   +0x02D 0x00007EB0  ios_base::getloc
//   +0x04B 0x0000BF20  basic_string<unsigned short>(const unsigned short*,
//                      const allocator<unsigned short>&)  -- the WIDE c-string
//                      constructor, which is what proves the G instantiation
//   +0x099 0x00142D70  basic_string<char>::~basic_string, 14 bytes, frameless;
//                      the wide twin is ICF-folded onto it
//
// And from the frame: `sub esp,0x94` is the 128-byte wchar_t __buf[64] where
// the narrow twin needs 64, and `ret 0x20` is 4+8+4+4+4+8 as there.
//
// The upstream body is vendor/stlport/stl/_monetary.h and it ignores __units
// outright (upstream comments the parameter name out) and hands the unwritten
// buffer to the string constructor:
//
//     locale __loc = __str.getloc();
//     _CharT __buf[64];
//     return do_put(__s, __intl, __str, __fill, __buf + 0);
//
// The body below is the 0x0000BDA0 recipe with the instantiation switched to
// wchar_t, and it reproduces the whole shape: same instructions, same
// registers, same frame, right length at 205. KEEP BOTH ITS LEVERS -- the
// _INC_STDLIB prelude that gives free C++ linkage, and the completion of the
// opaque _Locale_impl after the include that lets ~locale inline. Without them
// this scores far worse; see the commit that landed 0x0000BDA0.
//
// TWO THINGS REMAIN AND THEY ARE PROBABLY ONE THING.
//
//   1. Every unwind state in retail is ONE HIGHER than this body emits:
//        retail  c7 84 24 ac .. 01 ... c6 84 24 c0 .. 02 ... c6 84 24 a4 .. 01
//        this    c7 84 24 ac .. 00 ... c6 84 24 c0 .. 01 ... c6 84 24 a4 .. 00
//      So retail tracks one more destructible object across this body than the
//      vendored source produces. The narrow twin does NOT do this -- its states
//      are 0/1/0 and it matched exactly -- so whatever the extra object is, it
//      is specific to the wide instantiation.
//
//   2. Retail CALLS ~basic_string out of line at 0x00142D70; this body inlines
//      it as `if (p) free(p)`:
//        retail  8d 4c 24 10  c6 84 24 a4 00 00 00 01  e8 82 6e 13 00
//        this    8b 44 24 10 85 c0 c6 84 24 a4 00 00 00 00 74 09 50
//                e8 3d 49 02 00 83 c4 04
//      Note this is the FRAMELESS 14-byte ~basic_string, not the framed
//      63-byte _String_base destructor at 0x0000B3C0 that 0x0000EB60 needs, so
//      the "vendored _STLP_alloc_proxy has no destructor" argument recorded
//      against that address does NOT apply here -- this destructor is small in
//      retail too, and MSVC still called it. That is why (1) and (2) are likely
//      the same cause: with an extra tracked object live, MSVC keeps the
//      destructor out of line.
//
// THE ~_String_base LEVER DOES NOT TRANSFER HERE (tested 2026-09-06).  An
// explicit specialization declared and not defined forces the out-of-line call
// for _String_base in 0x0000EB60, but for ~basic_string it cannot be written:
//
//   * after `#include <locale>` it is C2908, "explicit specialization; ...
//     has already been instantiated" -- the include instantiates the
//     destructor before we get a chance;
//   * before the include it is C2027, "use of undefined type" -- a destructor
//     specialization needs the class complete, and forward-declaring the
//     template is not enough;
//   * VC7.1 has no `extern template` to suppress the earlier instantiation.
//
// So this body needs the extra tracked object after all, exactly as the note
// below says.  Do not re-run the specialization experiment.
//
// NEXT PASS should chase the extra tracked object rather than the destructor.
// Worth trying, in order: check whether the wide string constructor at
// 0x0000BF20 takes its allocator by value rather than by reference (a by-value
// empty allocator temporary would be exactly one extra tracked object); look at
// what the already-landed narrow twin's state numbering does when its buffer is
// widened; and compare against 0x0000DF20, the wide do_put(string_type&) in the
// same vtable, once that is attempted.
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

template class _STL::money_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
