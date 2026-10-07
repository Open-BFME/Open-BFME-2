// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004CDA35@Rva004CDA35@@QAEXXZ at retail 0x004CDA35 (20B). Address-derived member name; caller establishes thiscall, but not class identity.
#include <vector>

enum ScienceType { };

class Rva004CDA35
{
public:
	virtual ~Rva004CDA35();
	void rva004CDA35();

private:
	unsigned char m_pad0[0x84];
	std::vector<ScienceType> m_scienceTypes;
};

void Rva004CDA35::rva004CDA35()
{
	m_scienceTypes.clear();
}
