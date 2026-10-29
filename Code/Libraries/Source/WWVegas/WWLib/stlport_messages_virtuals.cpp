// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// messages<char> and messages<wchar_t> are pure forwarders onto a _Messages
// held at this+0xC, and the image says which slot each reaches: do_open
// tail-jumps [_M_impl->vptr], do_close tail-jumps [+0xC], the narrow do_get
// calls [+8] and the wide do_get calls [+4].
//
// That last pair identifies _Messages' own shape. STLport keeps the class out
// of the shipped headers - only the forward declaration is there - so it is
// declared here from those offsets, and the two do_get overloads have to be
// declared narrow-then-wide for the wide one to land in the lower slot. Same
// reversed-overload rule as num_put and ctype, read here from the other side:
// the call offsets were known first and the declaration order follows from
// them.

#include <string>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<unsigned short, allocator<unsigned short> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t); }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// Nothing here destroys a string out of line: keep the string destructors
// inline, since this unit's own copies of them are not retail's.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline _String_base<unsigned short, allocator<unsigned short> >::~_String_base() { _M_deallocate_block(); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline basic_string<char, char_traits<char>, allocator<char> >::~basic_string() { _Destroy(this->_M_start, this->_M_finish + 1); }
template <> __declspec(dllimport) __declspec(nothrow) __forceinline basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::~basic_string() { _Destroy(this->_M_start, this->_M_finish + 1); }
}
#include <locale>
#include <cstddef>

namespace _STL
{

class _Messages
{
public:
	typedef messages_base::catalog catalog;

	virtual catalog do_open(const string &__fn, const locale &__loc) const = 0;
	virtual string do_get(catalog __c, int __set, int __msgid,
	                      const string &__dfault) const = 0;
	virtual wstring do_get(catalog __c, int __set, int __msgid,
	                       const wstring &__dfault) const = 0;
	virtual void do_close(catalog __c) const = 0;
};

messages_base::catalog
messages<char>::do_open(const string &__fn, const locale &__loc) const
{
	return _M_impl->do_open(__fn, __loc);
}

string messages<char>::do_get(catalog __c, int __set, int __msgid,
                              const string &__dfault) const
{
	return _M_impl->do_get(__c, __set, __msgid, __dfault);
}

void messages<char>::do_close(catalog __c) const
{
	_M_impl->do_close(__c);
}

messages_base::catalog
messages<wchar_t>::do_open(const string &__fn, const locale &__loc) const
{
	return _M_impl->do_open(__fn, __loc);
}

wstring messages<wchar_t>::do_get(catalog __c, int __set, int __msgid,
                                  const wstring &__dfault) const
{
	return _M_impl->do_get(__c, __set, __msgid, __dfault);
}

void messages<wchar_t>::do_close(catalog __c) const
{
	_M_impl->do_close(__c);
}

}
