// cl: /DNDEBUG /MD /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00360E64@Rva00360F55@@QAE_NABV1@@Z, retail 0x00360E64, 241 bytes.
// Equality for the 0x94-byte ObjectFilter science-cluster record (ctor 0x00360F55).
// Skips refcount at +0x8C; scalars +0x80/+0x90/+0x88/+0x84, 0x1C blobs via
// Rva00360C1FEqual, ScienceType vectors at +0x30/+0x3C/+0x18/+0x24, AsciiRange
// at +0x00/+0x0C via Rva002ADD75Equal. Order follows retail early-outs.
// Evidence: unlock lane; callees 0x00360C1F 0x00360C73 0x002ADD75 rowed;
// callers 0x003617BF 0x0036238F; neighbours 0x00360D26 0x00360F55.
enum ScienceType
{
	SCIENCE_NONE = 0
};
namespace _STL
{
	template <class _Tp, class _Alloc> class vector;
	template <class _Tp> class allocator;
	template <class _Tp, class _Alloc>
	bool operator==(const vector<_Tp, _Alloc> &, const vector<_Tp, _Alloc> &);
}
struct AsciiRange002ADD75
{
	char m_data[12];
};
int Rva00360C1FEqual(const void *a, const void *b);
int Rva002ADD75Equal(const AsciiRange002ADD75 *a, const AsciiRange002ADD75 *b);
class Rva00360F55
{
public:
	bool rva00360E64(const Rva00360F55 &other);
private:
	AsciiRange002ADD75 m_00;
	AsciiRange002ADD75 m_0C;
	char m_18[12];
	char m_24[12];
	char m_30[12];
	char m_3C[12];
	char m_48[28];
	char m_64[28];
	int m_80;
	int m_84;
	unsigned char m_88;
	char m_pad89[3];
	int m_8C;
	int m_90;
};
bool Rva00360F55::rva00360E64(const Rva00360F55 &other)
{
	if (m_80 == other.m_80) {
	if (m_90 == other.m_90) {
	if (m_88 == other.m_88) {
	if (m_84 == other.m_84) {
	if ((unsigned char)Rva00360C1FEqual(&m_48, &other.m_48)) {
	if ((unsigned char)Rva00360C1FEqual(&m_64, &other.m_64)) {
	typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > SciVec;
	if ((const SciVec &)m_30 == (const SciVec &)other.m_30) {
	if ((const SciVec &)m_3C == (const SciVec &)other.m_3C) {
	if ((const SciVec &)m_18 == (const SciVec &)other.m_18) {
	if ((const SciVec &)m_24 == (const SciVec &)other.m_24) {
	if ((unsigned char)Rva002ADD75Equal(&m_00, &other.m_00)) {
	if ((unsigned char)Rva002ADD75Equal(&m_0C, &other.m_0C)) {
		return true;
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	return false;
}
