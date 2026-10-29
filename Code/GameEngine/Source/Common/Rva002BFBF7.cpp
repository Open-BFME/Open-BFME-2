// cl: /MD /GX-
// stlport
// ?rva002BFBF7@Rva002BFBF7@@QAEXXZ 0x002BFBF7 87B evidence: unlock erase vector BfmePod16 0x002BF70F plus curve set 0x00504EAD twice; caller 0x002C0205
#include <vector>
struct BfmePod16 { int a[4]; };
class Rva00504EADCurve
{
public:
	bool set(float time, float value, float inTangent, float outTangent);
	char m_pad[8];
};
namespace _STL
{
// Bind the erase to the rowed BfmePod16 erase at 0x002BF70F.
template <> BfmePod16 *vector<BfmePod16, allocator<BfmePod16> >::erase(BfmePod16 *first, BfmePod16 *last);
}
struct Rva002BFBF7
{
	void rva002BFBF7();
	char m_pad[0x28];
	Rva00504EADCurve m_curve;
	_STL::vector<BfmePod16, _STL::allocator<BfmePod16> > m_vec;
};
void Rva002BFBF7::rva002BFBF7()
{
	_STL::vector<BfmePod16, _STL::allocator<BfmePod16> > &vec = m_vec;
	vec.erase(vec.begin(), vec.end());
	m_curve.set(0.0f, 0.0f, 0.0f, 0.0f);
	m_curve.set(1.0f, 1.0f, 0.0f, 0.0f);
}
