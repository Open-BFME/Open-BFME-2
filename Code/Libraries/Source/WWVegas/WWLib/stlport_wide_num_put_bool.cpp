// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// STLport num_put<wchar_t>::do_put(bool), retail RVA 0x0000EB60, 371 bytes.
// The boolalpha body is _num_put.c's algorithm. Retail destroys the two
// conditional return-value temporaries through _String_base out of line,
// but frees the named string inline. A separate storage owner expresses that
// distinction without changing the string constructor or facet identities.
//
// Suppress stdlib.h so free retains the C++ linkage and throwing declaration
// needed for retail's direct call and exception-state stores. These are the
// declarations consumed by the vendor cstdlib wrapper.
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

// The locale implementation is opaque in _locale.h. Its three vtable slots
// are established by stlport_locale.cpp; visibility here inlines _M_decr.
namespace _STL {
class _Locale_impl {
public:
    virtual ~_Locale_impl();
    virtual void _M_incr();
    virtual void _M_decr();
    locale::facet **_M_facets;
    unsigned int _M_count;
};
locale::~locale() _STLP_NOTHROW { _M_impl->_M_decr(); }

// Both return-value temporaries call the 63-byte ICF-folded destructor.
template <> _String_base<unsigned short, allocator<unsigned short> >::~_String_base();
}

// The storage is owned by the caller, so failed construction has no allocation
// to release. A tagged placement overload with no matching placement delete
// also avoids an extra unwind state that ordinary placement new introduces.
struct _BoolStorageTag {};
__forceinline void *operator new(size_t, void *storage, _BoolStorageTag) { return storage; }

namespace _STL {
typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > _WideOut;
typedef basic_string<wchar_t> _BoolString;

// The stored string contains wchar_t elements and the malloc allocator.
// Its named owner releases the buffer directly, as retail does at +0x135.
class _BoolNameStorage {
    union { unsigned char _storage[sizeof(_BoolString)]; void *_align; };
public:
    __forceinline _BoolNameStorage(const _BoolString& value) {
        new (_storage, _BoolStorageTag()) _BoolString(value);
    }
    ~_BoolNameStorage() {
        wchar_t *data = const_cast<wchar_t*>(c_str());
        if (data) free(data);
    }
    const wchar_t *c_str() const {
        return reinterpret_cast<const _BoolString*>(_storage)->c_str();
    }
    unsigned int size() const {
        return reinterpret_cast<const _BoolString*>(_storage)->size();
    }
};

template <> _WideOut
num_put<wchar_t, _WideOut>::do_put(_WideOut __s, ios_base& __f,
                                  wchar_t __fill, bool __val) const {
    if (!(__f.flags() & ios_base::boolalpha))
        return this->do_put(__s, __f, __fill, static_cast<long>(__val));
    locale __loc = __f.getloc();
    const numpunct<wchar_t>& __np = *(const numpunct<wchar_t>*)__f._M_numpunct_facet();
    _BoolNameStorage __str(__val ? __np.truename() : __np.falsename());
    ios_base::fmtflags __flags = __f.flags();
    if ((__flags & ios_base::adjustfield) == ios_base::internal)
        __flags = (__flags & ~ios_base::adjustfield) | ios_base::right;
    return __copy_integer_and_fill(__str.c_str(), __str.size(), __s,
                                   __flags, __f.width(0), __fill,
                                   (wchar_t)0, (wchar_t)0);
}
}
