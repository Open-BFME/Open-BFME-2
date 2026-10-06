// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva002D0C44@ProductionPrerequisite@@QAEAAV1@ABV1@@Z @0x002D0C44 45B: ProductionPrerequisite assign via rowed BfmeStringRecord assign 0x002D0927 plus int assign pin 0x0021C21B plus uint assign pin 0x0026F4F4. Evidence: caller vector ProductionPrerequisite copy loop 0x0033E9DE stride 0x24; 3x12B members at +0x00/+0x0C/+0x18 per copy ctor 0x002D08DA; middle ScienceVec folded to int per 4B POD ICF.
#include <vector>

#include "ascii_string.h"

struct BfmeStringRecord002CF5B1
{
	unsigned int word0;
	unsigned int word1;
	AsciiString text;
	BfmeStringRecord002CF5B1();
	BfmeStringRecord002CF5B1(const BfmeStringRecord002CF5B1 &other);
	~BfmeStringRecord002CF5B1();
};

class ProductionPrerequisite
{
public:
	ProductionPrerequisite &rva002D0C44(const ProductionPrerequisite &other);
private:
	_STL::vector<BfmeStringRecord002CF5B1> m_vec0;
	_STL::vector<int> m_vecC;
	_STL::vector<unsigned int> m_vec18;
};

ProductionPrerequisite &ProductionPrerequisite::rva002D0C44(const ProductionPrerequisite &other)
{
	m_vec0 = other.m_vec0;
	m_vecC = other.m_vecC;
	m_vec18 = other.m_vec18;
	return *this;
}
