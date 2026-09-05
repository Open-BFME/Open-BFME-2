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

template class _STL::money_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
