// cl: /O1 /G7 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Bounds-checked element accessors over an embedded STLport vector, two copies of one shape
// (37B, RET 4): &v[i] when i < v.size(), else null. Element strides 0x28 (vector at +0x0C) at
// 0x0040A83A and 0x68 (vector at +0x18) at 0x0040A86C are target facts (idiv/imul immediates and
// field loads); the element types and owning classes are unproven, so everything keeps address
// names. Neighbours 0x0040A7D5/7F1/80F are index getters over similar records.
#include <vector>
struct Rva0040A83AElement { char m_data[0x28]; };

class Rva0040A83A
{
public:
	Rva0040A83AElement *rva0040A83A(unsigned int index);
private:
	char m_pad[0x0C];
	_STL::vector<Rva0040A83AElement> m_v;
};

Rva0040A83AElement *Rva0040A83A::rva0040A83A(unsigned int index)
{
	if (index < m_v.size())
		return &m_v[index];
	return 0;
}
