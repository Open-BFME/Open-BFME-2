// ?do_get_date@?$time_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// partial score=0.93 date=2026-09-06
// ?do_get_date@?$time_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// partial score=0.93 date=2026-09-06
//
// STLport 4.5.3 time_get<wchar_t>::do_get_date, retail 0x0000F470.
//
// SHARED STATE OF THE time_get FAMILY, 2026-09-06. All four bodies --
// do_get_time and do_get_date, narrow and wide, at 0x0000D5C0, 0x0000DA00,
// 0x0000EEB0 and 0x0000F470 -- are emitted by a whole-class instantiation and
// now carry four levers. Keep all four; each was found on a different body in
// this same facet neighbourhood and each is load-bearing.
//
//   1. _INC_STDLIB ahead of <locale>, so free has C++ linkage rather than the
//      nothrow extern "C" import. From the 0x0000BDA0 landing.
//   2. the opaque _Locale_impl completed after the include and ~locale defined
//      ahead of the instantiation, so the destructor inlines. Same landing.
//   3. an explicit specialization of istreambuf_iterator<T, char_traits<T>
//      >::_M_getc, DECLARED AND NOT DEFINED, so MSVC emits the external call
//      instead of inlining a 35-byte body at every use site. The narrow
//      iterator's _M_getc is claimed at 0x00007C40 and the wide one at
//      0x0000A0A0. On money_get this removed a 70-byte excess exactly; here it
//      restores both _M_getc calls in every one of the four bodies. An earlier
//      sweep concluded "the recipe buys nothing for time_get" -- that sweep
//      predates this lever and is superseded.
//   4. /Oa, and it must STAND ALONE. Retail carries values in callee-saved
//      registers across the __get_formatted_time call where an ordinary build
//      reloads them from memory, which is exactly the aliasing assumption /Oa
//      relaxes.
//
// WHAT IS LEFT, uniformly, is callee-saved register count. Retail pushes FOUR
// in every one of the four bodies -- ebx, ebp, esi, edi. Measured here:
//
//     0x0000D5C0  do_get_time narrow   /Oa gives 3   retail 4
//     0x0000EEB0  do_get_time wide     /Oa gives 3   retail 4
//     0x0000DA00  do_get_date narrow   /Oa gives 2   retail 4
//     0x0000F470  do_get_date wide     untested at time of writing
//
// So /Oa buys one register on the do_get_time pair and none on do_get_date,
// and the two shapes want different remaining work despite being siblings in
// one instantiation.
//
// FLAGS ALREADY REFUTED, do not re-run: /Ow, /Oa /Ot, /Oa /Og, /Oa /Ob2 and
// /Oa /Ox all revert to the baseline allocation -- any other /O switch after
// /Oa cancels it. /O2 is already the default, and /G6, /G7, /Oi and /GB change
// nothing. /Oa also does nothing at all for money_get at 0x0000C000, whose body
// is already exactly retail's size and shows the same register shortfall, so
// the two facet families need different fixes.
//
// SIZES: trust reverse/functions.csv, not the older re_attempts entries, which
// disagree with each other. add_match refuses a range that overlaps the next
// matched row and names it, which gives the true boundary for free -- that is
// how 0x0000D5C0 was corrected from 209 to 144. Retail pads with cc.

// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Oa
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
template class _STL::time_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
