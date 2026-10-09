// cl: /O1 /G7 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Bounds-checked element accessor, twin of Rva0040A83AElementAt.cpp's 0x0040A83A (37B, RET 4):
// &v[i] when i < v.size(), else null, over a 0x68-byte element vector embedded at +0x18
// (stride and offset are target facts; the element type and owner are unproven). Kept as its own
// unit, mirroring the 0x28-stride copy.
#include <vector>
struct Rva0040A86CElement { char m_data[0x68]; };

class Rva0040A86C
{
public:
	Rva0040A86CElement *rva0040A86C(unsigned int index);
private:
	char m_pad[0x18];
	_STL::vector<Rva0040A86CElement> m_v;
};

Rva0040A86CElement *Rva0040A86C::rva0040A86C(unsigned int index)
{
	if (index < m_v.size())
		return &m_v[index];
	return 0;
}
