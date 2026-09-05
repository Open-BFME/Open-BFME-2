// ?do_get_time@?$time_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// partial score=0.93 date=2026-09-06
﻿// ?do_get_time@?$time_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// partial score=0.93 date=2026-09-06
//
// FIRST: THE SIZE IS 144, NOT 209 OR 2528. The earlier banks recorded all
// three. reverse/functions.csv settles it: the next matched row,
// __get_formatted_time, starts at 0x0000D650, and add_match refuses the
// overlap, so this body is 0x0000D650 - 0x0000D5C0 = 144 bytes. The retail
// dump confirms it -- the body ends `c2 20 00` and the rest is `cc` padding.
// There is no gen_asm row for this address, so it is a fresh claim: do NOT
// pass --replace-rva, it matches zero rows.
//
// THE SOURCE BELOW CARRIES THREE LEVERS, all found on other bodies in this
// same facet neighbourhood. Keep all three.
//
//   1. _INC_STDLIB ahead of <locale>, so free carries C++ linkage rather than
//      the nothrow extern "C" import. From the 0x0000BDA0 landing.
//   2. the opaque _Locale_impl completed after the include and ~locale defined
//      ahead of the instantiation, so the destructor inlines. Same landing.
//   3. an explicit specialization of istreambuf_iterator<char,
//      char_traits<char> >::_M_getc, declared and NOT defined, so MSVC emits
//      the external call to the already-claimed 0x00007C40 instead of inlining
//      a 35-byte body at each of the two use sites. From the 0x0000C000 work,
//      where it removed a 70-byte excess exactly. BOTH _M_getc calls are
//      present in the compiled body here now (`e8 2a a6 ff ff` and
//      `e8 19 a6 ff ff` against retail's `e8 2b a6 ff ff` and
//      `e8 12 a6 ff ff`), and so is the __get_formatted_time call.
//
// FOURTH LEVER, NEW, AND IT ONLY WORKS ON THIS FAMILY: /Oa. Retail keeps FOUR
// callee-saved registers live -- `53 ... 55 ... 56 ... 57`, ebx ebp esi edi --
// and carries both dwords of __s across the __get_formatted_time call. Without
// /Oa this build pushes only esi and edi and reloads both dwords from memory
// afterwards, which is exactly the aliasing assumption /Oa relaxes. With /Oa it
// pushes THREE (`53 8b 5c 24 20 56 57`) and keeps one of them live. That is one
// register short of retail and it is the whole remaining gap.
//
// Flag results, all measured on this body, so do not re-run them:
//   /Oa            2 -> 3 callee-saved registers   <-- best, and it is what
//                                                      the source below uses
//   /Ow            back to 2
//   /Oa /Ot        back to 2
//   /Oa /Og        back to 2
//   /Oa /Ob2       back to 2
//   /Oa /Ox        back to 2
// i.e. ANY other /O switch after /Oa cancels it. Do not pair /Oa with anything.
//
// NOT TRANSFERABLE TO money_get: /Oa was tried on 0x0000C000, whose body is
// already exactly retail's 277 bytes and which has the same two-against-four
// register difference, and there it changes nothing. So the two facet families
// reach the same symptom by different routes and need different fixes.
//
// WHAT IS LEFT here is the fourth register, ebp. Untried ideas, in order:
// whether the wide twin at 0x0000EEB0 enregisters differently under /Oa and can
// be diffed against this one; whether /Oa plus a /Gs or /Gy that is not an /O
// switch survives without cancelling; and giving the second spilled dword a
// named local with a longer live range.
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
template <> void istreambuf_iterator<char, char_traits<char> >::_M_getc() const;
}
template class _STL::time_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
