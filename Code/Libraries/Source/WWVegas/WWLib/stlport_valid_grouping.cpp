// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __valid_grouping. Walks the digit-group counts backwards
// against the grouping string, holding on the last group spec once it runs out,
// and lets the leading group be short.

namespace _STL
{

bool __cdecl __valid_grouping(const char *first1, const char *last1,
		const char *first2, const char *last2)
{
	if (first1 == last1 || first2 == last2)
		return true;

	--last1;
	--last2;

	while (first1 != last1)
	{
		if (*last1 != *first2)
			return false;

		--last1;

		if (first2 != last2)
			++first2;
	}

	return *last1 <= *first2;
}

}
