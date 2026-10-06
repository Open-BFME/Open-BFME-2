// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004FADF4@@QAE@II@Z @0x004FADF4 64B evidence: base II ctor 0x0059B7CB plus base 0x004FAC6B plus BfmeE16 Vector_base 0x00211E58; vptrs 0x00863438 0x008633FC; vector at +0x20 int at +0x2c; caller 0x004FAFB6.
// Honest Rva ctor with II args ret-8 returning this.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva0059B7CB
{
public:
	Rva0059B7CB(unsigned int field04, unsigned int field08);
	virtual void slot00();
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

class Rva004FAC6B
{
public:
	Rva004FAC6B();
	virtual void slot00();
private:
	char m_pad[0x10];
};

class Rva004FADF4 : public Rva0059B7CB, public Rva004FAC6B
{
public:
	Rva004FADF4(unsigned int a, unsigned int b);
	virtual void slot00();
private:
	_STL::vector<BfmeE16> m_vec;
	int m_2c;
};

Rva004FADF4::Rva004FADF4(unsigned int a, unsigned int b)
	: Rva0059B7CB(a, b), Rva004FAC6B(), m_vec(_STL::allocator<BfmeE16>()), m_2c(0)
{
}
