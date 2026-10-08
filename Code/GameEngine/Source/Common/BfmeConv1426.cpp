// cl: /Od /Ob1

// Native 276B0 passes five stack words; the final one is an empty object.
// Its type name is structural; no original STL template identity is asserted.
struct Rva00026E40Tag {};

inline bool bfmeEqVMD(const char &a, const char &b)
{
	return a == b;
}

const char *bfmeFindFirstOfVMD(const char *first1, const char *last1, const char *first2, const char *last2, Rva00026E40Tag)
{
	for (; first1 != last1; ++first1)
	{
		for (const char *n1 = first2; n1 != last2; ++n1)
		{
			if (bfmeEqVMD(*first1, *n1))
				return first1;
		}
	}
	return last1;
}
