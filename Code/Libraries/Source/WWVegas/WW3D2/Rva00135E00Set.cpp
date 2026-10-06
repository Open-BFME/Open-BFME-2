// cl: /DNDEBUG /MD
// ?rva00135E00@Rva00135E00@@QAEXHHH@Z @0x00135E00 35B.
// Flag-plus-three setter: low two bits of +0 forced to 3 keeping bit 31
// then three args stored at +4 +8 +0xC. Evidence: unlock lane; neighbour
// 0x00135E86 same flags; caller 0x001371F9; ret 0xC three args.
class Rva00135E00
{
public:
	void rva00135E00(unsigned int a, unsigned int b, unsigned int c);
private:
	unsigned int m_0;
	unsigned int m_4;
	unsigned int m_8;
	unsigned int m_c;
};
void Rva00135E00::rva00135E00(unsigned int a, unsigned int b, unsigned int c)
{
	unsigned int v = m_0;
	v &= 0x80000003;
	v |= 3;
	m_0 = v;
	m_4 = a;
	m_8 = b;
	m_c = c;
}
