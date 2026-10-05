// ??0Rva0040450E@@QAE@XZ
// partial score=0.95 date=2026-10-05
// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
// ??0Rva0040450E@@QAE@XZ retail 0x00214B61 79 bytes.
// Default ctor for Rva0040450E: builds vector at +0 via rowed _Vector_base
// BfmeE16 0x00211E58, zeroes +0x10, builds two Rva0042526Member at +0x1C/+0x68
// via rowed 0x00042526, then resets via rowed rva0040450E 0x0040450E with 0.
// Evidence: chain from landed 0x0040450E; callees rowed 0x00211E58 0x00042526
// 0x0040450E; layout from Rva0040450EClear.cpp; prev/next give flags.
#include <vector>

struct BfmeE16
{
	unsigned char _pad[16];
};

class Rva0042526Member
{
public:
	Rva0042526Member();
	~Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class Rva0040450E
{
public:
	Rva0040450E();
	void rva0040450E(int arg) throw();
private:
	_STL::vector<BfmeE16> m_vec;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	Rva0042526Member m_1C;
	Rva0042526Member m_68;
};

// ??0Rva0040450E@@QAE@XZ present-unmatched
Rva0040450E::Rva0040450E()
	: m_10(0)
{
	rva0040450E(0);
}
