// cl: /MD
// ?rva000ADA6D@Rva000ADA6D@@QAEXXZ @0x000ADA6D 28B: sentinel fill. Fills
// [+0x50, +0x54) through the rowed _STL::fill char body at 0x000ABC25 after
// seeding a 0xFF sentinel local, mirroring Rva000AD9ABFinish.cpp's zero
// fill idiom. Honest address-derived names; boundary verified (frame at
// 0xADA6D, leave + ret at end).
namespace _STL { void __cdecl fill(unsigned char *first, unsigned char *last, const unsigned char &v); }
class Rva000ADA6D {
public:
	void rva000ADA6D();
private:
	unsigned char m_pad[0x50];
	unsigned char *m_first50;
	unsigned char *m_last54;
};
void Rva000ADA6D::rva000ADA6D()
{
	unsigned char marker = (unsigned char)0xFF;
	_STL::fill(m_first50, m_last54, marker);
}
