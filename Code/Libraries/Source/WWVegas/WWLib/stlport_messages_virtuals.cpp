// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
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

#include <locale>

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
