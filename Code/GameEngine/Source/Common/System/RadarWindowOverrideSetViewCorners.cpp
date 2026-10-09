// cl: /O1 /DNDEBUG /MD
// Native [002D55D2,002D55EF),29B, RET4. Thiscall on theRadarWindowOverrideSource
// (the radar view box draw 0x0004DBD5 hands it the four pixel corners): copy
// the four 8-byte corners into the inner window record (+0x10) at +0xFC
// through the rowed STLport __copy_ptrs<BfmePod8> 0x002D4633. The method
// name is address-derived; the corner record keeps the established 8-byte
// POD view.

struct BfmePod8 { int a[2]; };

namespace _STL {
template <class _InputIter, class _OutputIter>
_OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result);
}

struct RadarWindowOverrideInner
{
	unsigned char m_pad00[0xFC];
	BfmePod8 m_viewCorners[4];
};

class RadarWindowOverrideSource
{
public:
	void rva002D55D2(const BfmePod8 *corners);

private:
	unsigned char m_pad00[0x10];
	RadarWindowOverrideInner *m_inner;
};

void RadarWindowOverrideSource::rva002D55D2(const BfmePod8 *corners)
{
	_STL::__copy_ptrs(corners, corners + 4, m_inner->m_viewCorners);
}
