// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004FD719Data@@QAE@XZ, retail 0x004FCCF0 36B: default ctor with one vector plus int and byte zeros.
// Evidence: pin ??0Rva004FD719Data@@QAE@XZ plus caller Rva004FD719Parse new; rowed _Vector_base BfmeE16 0x00211E58; vtable 0x00863558.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva004FD719Data
{
public:
	Rva004FD719Data();
	virtual ~Rva004FD719Data();

private:
	_STL::vector<BfmeE16 > m_04;
	int m_10;
	unsigned char m_14;
};

Rva004FD719Data::Rva004FD719Data() : m_10(0), m_14(0)
{
}
