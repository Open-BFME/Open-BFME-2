// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// codecvt<char,char,mbstate_t> is the identity conversion, and its vftable at
// 0x007BBB08 shows how little of it is distinct: slots 1 and 2 hold the same
// body because do_out and do_in do the same two stores and return noconv, and
// slots 4 and 7 hold the same body because do_encoding and do_max_length both
// return 1. The wide codecvt's vftable at 0x007BBB2C shares four of these
// outright - only its do_out and do_in differ, because only they convert.

#include <locale>

namespace _STL
{

codecvt<char, char, mbstate_t>::result
codecvt<char, char, mbstate_t>::do_out(mbstate_t &, const char *__from,
                                       const char *, const char *&__from_next,
                                       char *__to, char *, char *&__to_next) const
{
	__from_next = __from;
	__to_next = __to;
	return noconv;
}

codecvt<char, char, mbstate_t>::result
codecvt<char, char, mbstate_t>::do_unshift(mbstate_t &, char *__to, char *,
                                           char *&__to_next) const
{
	__to_next = __to;
	return noconv;
}

int codecvt<char, char, mbstate_t>::do_encoding() const _STLP_NOTHROW
{
	return 1;
}

bool codecvt<char, char, mbstate_t>::do_always_noconv() const _STLP_NOTHROW
{
	return true;
}

int codecvt<char, char, mbstate_t>::do_length(const mbstate_t &,
                                              const char *__from,
                                              const char *__end,
                                              size_t __max) const
{
	return (int) (min) ((size_t) (__end - __from), __max);
}

int codecvt<char, char, mbstate_t>::do_max_length() const _STLP_NOTHROW
{
	return 1;
}

}
