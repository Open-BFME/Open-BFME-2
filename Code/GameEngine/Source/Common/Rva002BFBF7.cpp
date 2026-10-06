// cl: /MD /GX-
// ?rva002BFBF7@Rva002BFBF7@@QAEXXZ 0x002BFBF7 87B evidence: unlock erase vector BfmePod16 0x002BF70F plus curve set 0x00504EAD twice; caller 0x002C0205
struct BfmePod16 { int a[4]; };
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	void *m_start;
	void *m_finish;
	void *m_end;
	BfmePod16 *erase(BfmePod16 *first, BfmePod16 *last);
};
}
class Rva00504EADCurve
{
public:
	void set(float time, float value, float inTangent, float outTangent);
	char m_pad[8];
};
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
	vec.erase((BfmePod16 *)vec.m_start, (BfmePod16 *)vec.m_finish);
	m_curve.set(0.0f, 0.0f, 0.0f, 0.0f);
	m_curve.set(1.0f, 1.0f, 0.0f, 0.0f);
}
