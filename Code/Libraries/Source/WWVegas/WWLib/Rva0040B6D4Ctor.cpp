// cl: /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??0Rva0040B6D4@@QAE@XZ @ 0x0040B6D4 (51B). Default ctor with two BfmeE16 vectors plus four ints.
// Evidence: retail zeroes +0 +10 +14 +18 then constructs rowed _Vector_base E16 0x00211E58 at +4 and +1C; caller 0x0040C137 in 0x0040C125; neighbours share E16 vector and ascii shims.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva0040B6D4
{
public:
	Rva0040B6D4();
private:
	int m_00;
	_STL::vector<BfmeE16> m_04;
	int m_10;
	int m_14;
	int m_18;
	_STL::vector<BfmeE16> m_1C;
};

Rva0040B6D4::Rva0040B6D4() : m_00(0), m_10(0), m_14(0), m_18(0)
{
}
