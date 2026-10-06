// cl: /MD
// ?rva002DB9CB@Rva002DB9CB@@QAEPAV1@XZ @0x002DB9CB 36B
// Evidence: unlock lane; caller 0x002DD173 lea ecx esi+0x10 clears 16B; prev 0x002DB9B6 next 0x002DB9EF same dir; mov eax ecx save suggests return this.
class Rva002DB9CB
{
public:
	Rva002DB9CB *rva002DB9CB();
private:
	unsigned short m_00;
	unsigned short m_02;
	unsigned short m_04;
	unsigned short m_06;
	unsigned short m_08;
	unsigned short m_0a;
	unsigned short m_0c;
	unsigned short m_0e;
};
Rva002DB9CB *Rva002DB9CB::rva002DB9CB()
{
	m_00 = 0;
	m_02 = 0;
	m_04 = 0;
	m_06 = 0;
	m_08 = 0;
	m_0a = 0;
	m_0c = 0;
	m_0e = 0;
	return this;
}
