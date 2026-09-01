// ??$__lower_bound@PBIIU?$less@I@_STL@@H@_STL@@YAPBIPBI0ABIU?$less@I@0@PAH@Z
// partial score=0.9 date=2026-09-02
// ??$__lower_bound@PBIIU?$less@I@_STL@@H@_STL@@YAPBIPBI0ABIU?$less@I@0@PAH@Z
// partial score=0.9 date=2026-09-02
// 0x00568D2F, 57 bytes, named by reverse/reloc_names.csv and never a dump row -
// landing it would be new coverage, not a conversion.
//
// 63 bytes against 57 and the structure is identical: same prologue, same
// sar-by-2 length, same jle, same unsigned compare, same `or -1 / sub / add`
// length update, same tail. The whole difference is that retail materialises
// `middle` into esi - `lea esi,[eax+ecx*4]`, then `cmp [esi],edi` and
// `lea eax,[esi+4]` - while MSVC 7.1 folds the addressing into both uses:
// `cmp [eax+ecx*4],esi` and `lea eax,[eax+ecx*4+4]`.
//
// Refuted: `middle = first + half`, `middle = first; advance(middle, half)`
// with advance as a separate inline, and `first = middle + 1` against
// `first = middle; ++first`. All three fold the same way.
//
// Next lever: something that keeps middle live across the comparison - a use
// the addressing cannot absorb.

// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __lower_bound over unsigned ints with less<unsigned int>, the
// binary search the int hash map uses.

namespace _STL
{

template <class T>
struct less
{
	bool operator()(const T &a, const T &b) const { return a < b; }
};

template <class Iter, class Distance>
inline void advance(Iter &i, Distance n)
{
	i += n;
}

template <class ForwardIter, class T, class Compare, class Distance>
ForwardIter __cdecl __lower_bound(ForwardIter first, ForwardIter last, const T &value,
		Compare comp, Distance *)
{
	Distance len = last - first;
	Distance half;
	ForwardIter middle;

	while (len > 0)
	{
		half = len >> 1;
		middle = first;
		advance(middle, half);
		if (comp(*middle, value))
		{
			first = middle + 1;
			len = len - half - 1;
		}
		else
			len = half;
	}
	return first;
}

template const unsigned int *__cdecl __lower_bound<const unsigned int *, unsigned int,
		less<unsigned int>, int>(const unsigned int *, const unsigned int *,
		const unsigned int &, less<unsigned int>, int *);

}
