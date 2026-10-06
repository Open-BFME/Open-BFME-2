// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /G7
//
// ?rva00540301@@YAPAUBfmePod40@@PAU1@0ABU1@@Z @ 0x00540301 35B
// Evidence: lower_bound wrapper mirror of the verified 0x005414C2 wrap
// (less temp plus null distance tag around the rowed Pod40
// __lower_bound at 0x00540253). The 200B sorted-key locator caller at
// 0x0054034A is banked as a partial (same TU shape stashed) pending
// fast-path regalloc work: hint must stay in ECX with late push-edi,
// EDI divisor and real imul-40 (this TU's /G7 emits the imul).
// Names are generated.
struct BfmePod40
{
	int m_00;
	char m_pad04[0x24];
};

namespace _STL
{
	template <class _Tp>
	struct less
	{
	};
	template <class _Fwd, class _T, class _C, class _D>
	_Fwd __lower_bound(_Fwd, _Fwd, const _T &, _C, _D *);
}

BfmePod40 *rva00540301(BfmePod40 *first, BfmePod40 *last, const BfmePod40 &value)
{
	return _STL::__lower_bound(first, last, value, _STL::less<BfmePod40>(), (int *)0);
}
