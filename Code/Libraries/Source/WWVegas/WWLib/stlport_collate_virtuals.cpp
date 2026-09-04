// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// collate's virtuals, identified by vftable slot: the ledger already holds
// slot 0 of both 0x007BBB50 and 0x007BBB64, so slots 1..3 are do_compare,
// do_transform and do_hash in declaration order.
//
// do_hash is the whole body, five-times-plus-character over the range, and the
// lea eax,[eax+eax*4] and movsx pair say the accumulator is scaled by five and
// the character is signed.

#include <locale>

namespace _STL
{

int collate<char>::do_compare(const char *__low1, const char *__high1,
                              const char *__low2, const char *__high2) const
{
	return __lexicographical_compare_3way(__low1, __high1, __low2, __high2);
}

long collate<char>::do_hash(const char *__low, const char *__high) const
{
	unsigned long __result = 0;
	for ( ; __low < __high; ++__low)
		__result = 5 * __result + *__low;
	return __result;
}

int collate<wchar_t>::do_compare(const wchar_t *__low1, const wchar_t *__high1,
                                 const wchar_t *__low2, const wchar_t *__high2) const
{
	return __lexicographical_compare_3way(__low1, __high1, __low2, __high2);
}

long collate<wchar_t>::do_hash(const wchar_t *__low, const wchar_t *__high) const
{
	unsigned long __result = 0;
	for ( ; __low < __high; ++__low)
		__result = 5 * __result + *__low;
	return __result;
}

}
