// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0020E72A@Rva0020E72A@@QAE_NPAX@Z, retail 0x0020E72A, 61 bytes.
// Vector scan at +0x14/+0x18 over Rva003F498A pointers via rowed 0x003F48EF
// returning true on first hit. Callers at 0x002B5F4C 0x002BD319 0x002BD7E8.
#include <vector>

class Rva003F498A
{
public:
	bool rva003F48EF(void *p);
};

class Rva0020E72A
{
public:
	bool rva0020E72A(void *p);

private:
	unsigned char m_pad[0x14];
	_STL::vector<Rva003F498A *> m_vec;
};

bool Rva0020E72A::rva0020E72A(void *p)
{
	for (unsigned i = 0; i < m_vec.size(); ++i) {
		if (m_vec[i]->rva003F48EF(p))
			return true;
	}
	return false;
}
