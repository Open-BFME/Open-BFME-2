// cl: /Ireference/shims/bfme2_ascii /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0042755D@Rva0042755D@@QAE_NII@Z @0x0042755D 89B.
// Leaf with two index args over vector<Rva004F5436 *> at +0x10; returns
// false if either valid element has rowed Count 0x004F5436 nonzero else true.
// Evidence: rowed callee 0x004F5436, caller at 0x004667E3, ret 8 two uints,
// +0x10/+0x14 begin/end with sar count like vector size.
#include <vector>

class BfmeTab1026;

class Rva004F5436
{
public:
	int rva004F5436(BfmeTab1026 *tab);
};

class Rva0042755D
{
public:
	bool rva0042755D(unsigned a, unsigned b);
private:
	char m_pad00[0x10];
	_STL::vector<Rva004F5436 *> m_vec10;
};

bool Rva0042755D::rva0042755D(unsigned a, unsigned b)
{
	if (m_vec10.size() > a) {
		Rva004F5436 *p = m_vec10[a];
		if (p != 0) {
			if (p->rva004F5436(0) > 0u)
				return false;
		}
	}
	if (m_vec10.size() > b) {
		Rva004F5436 *p = m_vec10[b];
		if (p != 0) {
			if (p->rva004F5436(0) > 0u)
				return false;
		}
	}
	return true;
}
