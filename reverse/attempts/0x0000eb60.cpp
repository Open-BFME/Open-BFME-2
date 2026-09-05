// ?do_put@?$num_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@AAVios_base@2@G_N@Z
// partial score=0.879 date=2026-09-05
﻿// ?do_put@?$num_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@AAVios_base@2@G_N@Z
// partial score=0.879 date=2026-09-05
//
// STLport 4.5.3 num_put<wchar_t>::do_put(iter, ios_base&, wchar_t, bool) --
// the boolalpha overload -- retail 0x0000EB60, 371 bytes.
//
// IDENTITY IS SETTLED and the upstream body is
// vendor/stlport/stl/_num_put.c:422-447, which maps onto the disassembly
// instruction for instruction. Callee map, decoded from this body's own REL32
// displacements (target = 0xEB60 + offset + 5 + int32_le):
//
//   +0x068 0x00007EB0  ios_base::getloc
//   +0x085 0x0000EA30  numpunct<char>::truename    (ICF-folded; the wide twins
//   +0x09B 0x0000EA50  numpunct<char>::falsename    share the narrow bodies)
//   +0x0B2 0x0000EA90  basic_string<unsigned short> copy ctor  -- wide, and
//                      this is what proves the G instantiation rather than D
//   +0x0CF 0x0000B3C0  _String_base<char>::~_String_base  (ICF-folded, x2)
//   +0x0E6 0x0000B3C0  ditto
//   +0x130 0x0000ECE0  __copy_integer_and_fill<G, ostreambuf_iterator<G> >
//   +0x146 0x00030830  free, C++-linkage spelling ?free@@YAXPAX@Z
//
// TWO OF THE THREE BLOCKERS THE PREVIOUS BANK NAMED ARE NOW SOLVED, and both
// fixes came from landing money_put::do_put(long double) at 0x0000BDA0. They
// are in the body below; do not undo them.
//
//   1. free with C++ LINKAGE inside a TU that includes <locale>. The previous
//      bank recorded this as unreachable, because declaring it is C2375
//      against the vendor stdlib.h. Defining _INC_STDLIB ahead of the include
//      suppresses that header; what then has to be declared by hand is exactly
//      the set of names the vendor <cstdlib> lists in its using-declarations,
//      which is the bounded list written out below. This turns the three
//      inlined string destructors from nothrow import thunks into retail's
//      direct `e8` calls to 0x00030830 and restores the unwind state stores
//      beside them.
//
//   2. ~locale. _locale.h forward-declares _Locale_impl as an OPAQUE type and
//      declares ~locale() with no body, so MSVC has to emit a call; retail
//      inlines it as `mov ecx,[esp+0x48]; mov eax,[ecx]; call [eax+8]`, i.e.
//      _M_impl->_M_decr() through vtable slot 2. An incomplete type may be
//      completed later in the same TU, so the body below closes _Locale_impl
//      after the include and defines the destructor ahead of the
//      instantiation. The whole tail from +0x14E to the ret is now byte-exact.
//
// Similarity 0.735 -> 0.879, and the body is the right length at 371.
//
// THE ONE REMAINING GAP is the two EH-tracked temporaries' destructors.
// Retail CALLS _String_base::~_String_base out of line at 0x0000B3C0; this
// build inlines the deallocation at both sites, costing eight bytes each:
//
//   retail  +0xC2  74 10  83 e3 fd  8d 4c 24 18  89 5c 24 08  e8 8c c7 ff ff
//   this    +0xC2  74 18  8b 44 24 18 83 e3 fd 85 c0 89 5c 24 08 74 09 50
//                  e8 f7 1b 02 00 83 c4 04
//
// Same ebx live-temporary mask, same spill slot, same instruction -- only
// inlined rather than called.
//
// AND IT CANNOT BE FIXED FROM THIS ROUTE. Retail's 0x0000B3C0 is 63 bytes and
// carries its own /EHsc frame; the note in
// Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_base_dtor.cpp
// explains that the frame only appears when the allocator proxy has a
// destructor the front end cannot see through. The VENDORED _STLP_alloc_proxy
// (vendor/stlport/stl/_alloc.h:480) HAS NO DESTRUCTOR AT ALL -- its only
// members are a constructor, _M_data and allocate/deallocate -- so
// ~_String_base here is just _M_deallocate_block(), small enough that MSVC
// will always inline it. That is a header-version difference between the
// vendored 4.5.3 copy and the one retail built against, not a flag, so no
// combination of switches on a whole-class instantiation will produce the
// out-of-line call. STOP TESTING FLAGS FOR IT.
//
// NEXT PASS must hand-roll, in the stlport_wide_string_reserve.cpp style, and
// it is now a much smaller job than the previous bank estimated: keep the
// _INC_STDLIB prelude and the _Locale_impl completion from below, and declare
// _String_base<unsigned short, allocator<unsigned short> >::~_String_base
// DECLARED-NOT-DEFINED, pinned at 0x0000B3C0 in reverse/symbols.csv as an ICF
// alias of the narrow one. Run tools/pin_consistency.py --symbol before
// pinning and --check after. Every other callee in the map above is already
// claimed or pinned.
//
// FLAGS ALREADY RULED OUT, do not re-test: /D_STLP_USE_TEMPLATE_EXPORT alone
// (the header's own _STLP_EXPORT_TEMPLATE_CLASS becomes an extern template and
// nothing is emitted); the same with an explicit `template class num_put<...>`
// (C2949); /D_STLP_USE_TEMPLATE_EXPORT with /D_STLP_DESIGNATED_DLL (C2908 in
// stl/_ios.h:158,165); an explicit instantiation of _String_base (forces the
// COMDAT to exist but does not stop the inline); and _STLP_USE_MALLOC on its
// own without the C++-linkage free.
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

template class _STL::num_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
