// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport46

// Native narrow append calls the static byte allocator at 0x307F0.
// Preserve the standard empty allocator view with that recovered ABI; the
// remaining members use STLport 4.6. This is TU-local.
#include <memory>
namespace _STL {
template <>
class allocator<char> {
public:

  typedef char        value_type;
  typedef value_type *       pointer;
  typedef const char* const_pointer;
  typedef char&       reference;
  typedef const char& const_reference;
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;
# if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };
# endif
  allocator() _STLP_NOTHROW {}
 # if defined (_STLP_MEMBER_TEMPLATES)
  template <class _Tp1> allocator(const allocator<_Tp1>&) _STLP_NOTHROW {}
 # endif    
  allocator(const allocator<char>&) _STLP_NOTHROW {}
  ~allocator() _STLP_NOTHROW {}
  pointer address(reference __x) { return &__x; }
  const_pointer address(const_reference __x) const { return &__x; }
  // __n is permitted to be 0.  The C++ standard says nothing about what the return value is when __n == 0.
  static char* __cdecl allocate(size_type __n, const void* = 0);
  // __p is permitted to be a null pointer, only if n==0.
  void deallocate(pointer __p, size_type __n) const {
    _STLP_ASSERT( (__p == 0) == (__n == 0) )
      if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
  }
  // backwards compatibility
  void deallocate(pointer __p) const {  if (__p != 0) __sgi_alloc::deallocate((void*)__p, sizeof(value_type)); }
  size_type max_size() const _STLP_NOTHROW  { return size_t(-1) / sizeof(value_type); }
  void construct(pointer __p, const char& __val) const { _STLP_STD::_Construct(__p, __val); }
  void destroy(pointer __p) const { _STLP_STD::_Destroy(__p); }
# if defined(__MRC__)||defined(__SC__)
  template <class _T2> bool operator==(const allocator<_T2>&) const  { return true; }
  template <class _T2> bool operator!=(const allocator<_T2>&) const { return false; }
# endif
};

}
#include <string>
// BFME uses its direct game free at 0x30830 rather than the CRT import.
extern "C" void __cdecl free(void *);
// In STLport 4.6 the proxy inherits this allocator's static allocate member.

// Retail folds the mutable byte-copy dispatch onto the 21-byte 4598CC
// wrapper. Its three memory pushes need size optimization: the surrounding
// /O2 profile otherwise emits a different 24-byte register-push wrapper.
// Limit that setting and the out-of-line __copy_trivial call to this helper;
// restore the TU defaults before the existing string bodies.
#pragma optimize("s", on)
namespace _STL {
template <> inline char *__uninitialized_copy<char *, char *>(char *first, char *last, char *result, const __true_type &) {
#pragma inline_depth(0)
    return (char *)__copy_trivial(first, last, result);
#pragma inline_depth()
}
template char *__uninitialized_copy<char *, char *>(char *, char *, char *, const __true_type &);
}
#pragma optimize("", on)

// Preserve the generic byte-copy caller's existing inlined trivial-copy body.
namespace _STL {
template <> inline char *uninitialized_copy<char *, char *>(char *first, char *last, char *result) {
    return (char *)__copy_trivial(first, last, result);
}
}

// Inline uses here keep the stock body (with its length_error path), but this unit,
// the first in link order to spell it, must not emit an out-of-line copy: retail's
// _String_base<char>::_M_allocate_block is the 0x00007460 body without that path,
// which stlport_narrow_string_allocate_block.cpp emits. dllimport + forceinline: no __imp_.
namespace _STL {
template <> __declspec(dllimport) __forceinline void _String_base<char, allocator<char> >::_M_allocate_block(size_t __n)
{
	if ((__n <= (max_size() + 1)) && (__n > 0)) {
		_M_start = _M_end_of_storage.allocate(__n);
		_M_finish = _M_start;
		_M_end_of_storage._M_data = _M_start + __n;
	}
	else
		_M_throw_length_error();
}
}
// Native 0x00025AD0 is supplied by stlport_vector_voidptr.cpp.
// Keep this profile from emitting a competing allocator-proxy swap.
namespace _STL {
template <> void swap(_STLP_alloc_proxy<char *, char, allocator<char> > &,
                     _STLP_alloc_proxy<char *, char, allocator<char> > &);
}
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(char const *, allocator<char> const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(const char *, const char *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_deallocate_block(); }

// Native base cleanup is supplied by the independently verified B3C0 owner.
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
// The canonical default constructor is verified at retail7850.
namespace _STL { template <> basic_string<char>::basic_string(); }


namespace _STL
{
template <>
basic_string<char, char_traits<char>, allocator<char> >::~basic_string();

template <>
basic_string<char, char_traits<char>, allocator<char> >&
basic_string<char, char_traits<char>, allocator<char> >::assign(
        const basic_string<char, char_traits<char>, allocator<char> >&);

// The retail-proven reserve body is emitted by stlport_narrow_string_reserve.cpp.
template <>
void basic_string<char, char_traits<char>, allocator<char> >::reserve(
        unsigned int);

// Owners emit these retail-proven bodies (stlport_narrow_string_copy.cpp,
// _erase_count.cpp); this unit's explicit instantiation must not.
template <>
basic_string<char, char_traits<char>, allocator<char> >::size_type
basic_string<char, char_traits<char>, allocator<char> >::copy(
        char*, size_type, size_type) const;

template <>
basic_string<char, char_traits<char>, allocator<char> >&
basic_string<char, char_traits<char>, allocator<char> >::erase(
        size_type, size_type);

// Retail's body is emitted by stlport_narrow_string_insert_aux.cpp.
template <>
char *basic_string<char, char_traits<char>, allocator<char> >::_M_insert_aux(char *, char);
}

// bfme link decl-only begin: members whose copies here are not retail's (owned or kept elsewhere)
namespace _STL { template <> char *__find_if(char *, char *, _Eq_char_bound<char_traits<char> >, const random_access_iterator_tag &); }
namespace _STL { template <> reverse_iterator<const char *> __find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Not_within_traits<char_traits<char> >, const random_access_iterator_tag &); }
namespace _STL { template <> char *find_if(char *, char *, _Eq_char_bound<char_traits<char> >); }
namespace _STL { template <> reverse_iterator<const char *> find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Not_within_traits<char_traits<char> >); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const basic_string<char, char_traits<char>, allocator<char> > &, size_t, size_t, const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(size_t, char, const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const char *, size_t, const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(_String_reserve_t, size_t, const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::operator=(const basic_string<char, char_traits<char>, allocator<char> > &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::append(const basic_string<char, char_traits<char>, allocator<char> > &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::append(size_t, char); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::append(const char *); }
namespace _STL { template <> size_t basic_string<char, char_traits<char>, allocator<char> >::find(const char *, size_t) const; }
namespace _STL { template <> size_t basic_string<char, char_traits<char>, allocator<char> >::find_last_not_of(const char *, size_t, size_t) const; }
// Retail's three-argument find (0x00027540) and its search core (0x00026C90) are
// emitted by stlport_reverse_string_search.cpp under retail's /Od /Ob2.
namespace _STL { template <> size_t basic_string<char, char_traits<char>, allocator<char> >::find(const char *, size_t, size_t) const; }
namespace _STL { template <> const char *search(const char *, const char *, const char *, const char *, _Eq_traits<char_traits<char> >); }
// Retail's insert(iterator, n, c) at 0x00029530 is emitted by
// stlport_string_insert_fill.cpp; this unit's copy precedes it in link order.
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::insert(char *, size_t, char); }
// Native substr at 0x0002AD50 belongs to stlport_narrow_string_substr.cpp.
// This earlier explicit instantiation must bind to that retail-proven body.
namespace _STL { template <> basic_string<char> basic_string<char>::substr(size_t, size_t) const; }
// bfme link decl-only end

namespace _STL {
// Keep the verified 1B3E0 body visible: declaration-only member-template
// specialization triggers VC7.1 C1001 in the range dispatch wrapper.
// Local allocation and deallocation preserve the native calls independently
// of the other members' required external _M_deallocate_block.
template <> template <> inline basic_string<char, char_traits<char>, allocator<char> > &
basic_string<char, char_traits<char>, allocator<char> >::append<const char *>(const char *__first, const char *__last,
		const forward_iterator_tag &)
{
	const char *__f = __first;
	const char *__l = __last;
	if (__f != __l) {
		const size_type __old_size = size();
		difference_type __n = __l - __f;
		if ((size_type)__n + __old_size > capacity()) {
			size_type __n_sz = (size_type)__n;
			size_type __mx = *(__old_size < __n_sz ? &__n_sz : &__old_size);
			const size_type __len = __old_size + __mx + 1;
			pointer __new_start = __len != 0 ? allocator<char>::allocate(__len,0) : 0;
			pointer __new_finish = uninitialized_copy((const char *)_M_start, (const char *)_M_finish, __new_start);

			__new_finish = uninitialized_copy(__f, __l, __new_finish);
			_M_construct_null(__new_finish);
			if (_M_start != 0) free(_M_start);
			_M_start = __new_start;
			_M_finish = __new_finish;
			_M_end_of_storage._M_data = __new_start + __len;
		}
		else {
			const char * __f1 = __f;
			++__f1;
			uninitialized_copy(__f1, __l, _M_finish + 1);
			_M_construct_null(_M_finish + __n);
			char_traits<char>::assign(*end(), *__f);
			_M_finish += __n;
		}
	}

	return *this;
}

// Mutable input ranges use the same read-only operation and fold onto
// the native 254-byte const-range body; the existing 120F0 caller proves
// the direct call to 1B3E0.
template <> template <> inline basic_string<char, char_traits<char>, allocator<char> > &
basic_string<char, char_traits<char>, allocator<char> >::append<char *>(char *__first, char *__last,
		const forward_iterator_tag &)
{
	const char *__f = __first;
	const char *__l = __last;
	if (__f != __l) {
		const size_type __old_size = size();
		difference_type __n = __l - __f;
		if ((size_type)__n + __old_size > capacity()) {
			size_type __n_sz = (size_type)__n;
			size_type __mx = *(__old_size < __n_sz ? &__n_sz : &__old_size);
			const size_type __len = __old_size + __mx + 1;
			pointer __new_start = __len != 0 ? allocator<char>::allocate(__len,0) : 0;
			pointer __new_finish = uninitialized_copy((const char *)_M_start, (const char *)_M_finish, __new_start);

			__new_finish = uninitialized_copy(__f, __l, __new_finish);
			_M_construct_null(__new_finish);
			if (_M_start != 0) free(_M_start);
			_M_start = __new_start;
			_M_finish = __new_finish;
			_M_end_of_storage._M_data = __new_start + __len;
		}
		else {
			const char * __f1 = __f;
			++__f1;
			uninitialized_copy(__f1, __l, _M_finish + 1);
			_M_construct_null(_M_finish + __n);
			char_traits<char>::assign(*end(), *__f);
			_M_finish += __n;
		}
	}

	return *this;
}

}


// Instantiate only the operations owned by this unit. A whole-class
// instantiation also emits unrelated non-retail comparison/insertion copies.
template _STL::basic_string<char>::reverse_iterator _STL::basic_string<char>::rbegin();
template _STL::basic_string<char>::reverse_iterator _STL::basic_string<char>::rend();
template _STL::basic_string<char> &_STL::basic_string<char>::append<char *>(
    char *, char *, const _STL::forward_iterator_tag &);
// Its const twin (the same 0x1B3E0 body): this unit is first in link order
// among the units that emit it, so emitting retail's copy here keeps the
// consumers' identical unproven copies (urlBuilder, stringbuf, ...) linking.
template _STL::basic_string<char> &_STL::basic_string<char>::append<const char *>(
    const char *, const char *, const _STL::forward_iterator_tag &);
template void _STL::swap<char *>(char *&, char *&);
template bool _STL::operator!=<const char *>(
    const _STL::reverse_iterator<const char *> &,
    const _STL::reverse_iterator<const char *> &);

// char_traits<char> is already a fully specialized class, so these two
// static members cannot be retained by explicit template instantiation.
// Taking their addresses emits their unchanged header bodies.
typedef char *(__cdecl *BfmeNarrowAssignBody)(char *, size_t, char);
typedef int (__cdecl *BfmeNarrowCompareBody)(const char *, const char *, size_t);
// ?bfmeEmitNarrowTraits absent-from-retail
void bfmeEmitNarrowTraits(BfmeNarrowAssignBody &assign, BfmeNarrowCompareBody &compare)
{
    assign = &_STL::char_traits<char>::assign;
    compare = &_STL::char_traits<char>::compare;
}


// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeFillV14@@YAPADPADID@Z=?assign@?$char_traits@D@_STL@@SAPADPADID@Z")
#pragma comment(linker, "/alternatename:?rva0082ADB0Fill@@YAXPAD0ABD@Z=?fill@_STL@@YAXPAD0ABD@Z")
#pragma comment(linker, "/alternatename:?bfmeCallVMC@@YAXHHH@Z=?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAssignPL@BfmeThingPL@@QAEXPAD0@Z=?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@PBD0@Z")
#pragma comment(linker, "/alternatename:?rva0082C6E0CopyValues@@YAPAURva0082C6E0Value@@PAU1@00@Z=?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")

// Row 0x000199E0 (_Construct<char,char>) was previously instantiated through _M_insert_aux.
template void _STL::_Construct<char, char>(char *, const char &);

// Retail money_put<wchar_t>::do_put(string), 0x0000DF20+0x449, calls
// the same allocator-base constructor as char strings at 0x00689600.
// Both emitted bodies are 37 bytes and call the folded 11-byte proxy
// constructor at 0x00007410. Keep the wide body available for fold proof.
template _STL::_String_base<wchar_t, _STL::allocator<wchar_t> >::_String_base(
        const _STL::allocator<wchar_t>&);


namespace _STL
{
// The char-range destruction overload in stl/_construct.h is empty.
// Native string insertion calls the shared RET at 0x0069E440 through this
// existing neutral binding; no exclusive original identity is claimed.
void Rva0069E440Destroy(char *, char *) {}
}

namespace _STL
{
// The /Od string-replace and conversion units call this char* copy out of line;
// retail folds it onto __copy_trivial (0x000179B0, pinned there). Supply that
// retail-proven copy of the name.
template <class _InputIter, class _ForwardIter>
inline _ForwardIter Rva000179B0UninitializedCopy(_InputIter __first, _InputIter __last, _ForwardIter __result)
{
	return (_ForwardIter)__copy_trivial(__first, __last, __result);
}
template char *Rva000179B0UninitializedCopy<char *, char *>(char *, char *, char *);
}
