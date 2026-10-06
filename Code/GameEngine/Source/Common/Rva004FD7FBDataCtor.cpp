// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004FD7FBData@@QAE@XZ, retail 0x004FCE41 50B: default ctor with two vectors plus two zeros.
// Evidence: pin ??0Rva004FD7FBData@@QAE@XZ plus caller Rva004FD7FBParse new plus record size 0x24; rowed _Vector_base BfmeE16 0x00211E58 twice; vtable 0x00863560.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva004FD7FBData
{
public:
	Rva004FD7FBData();
	virtual ~Rva004FD7FBData();

private:
	_STL::vector<BfmeE16 > m_04;
	int m_10;
	_STL::vector<BfmeE16 > m_14;
	int m_20;
};

Rva004FD7FBData::Rva004FD7FBData() : m_10(0), m_20(0)
{
}
