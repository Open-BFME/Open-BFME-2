// cl: /MD
// stlport
//
// ??0Rva002B644A@@QAE@XZ @0x002B644A 44B
// Ctor with vtable 0x007FE280 plus BfmeE16 vector at +8 via rowed
// Vector_base 0x00211E58 plus ints +4=-1 +0x14=0 +0x18=-1 +0x1C=0.
// Evidence: vtable store; Vector_base call; int stores; caller 0x002B9D5B;
// prev 0x002B62DE assign; same BfmeE16 stand-in as stlport_vector_e16_o1.cpp.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva002B644A
{
	virtual ~Rva002B644A();
	int m_4;
	_STL::vector<BfmeE16> m_vec8;
	int m_14;
	int m_18;
	unsigned char m_1C;
public:
	Rva002B644A();
};

Rva002B644A::Rva002B644A() : m_4(-1), m_14(0), m_18(-1), m_1C(0)
{
}
