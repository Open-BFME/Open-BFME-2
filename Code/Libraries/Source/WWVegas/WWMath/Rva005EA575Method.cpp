// cl: /DNDEBUG /MD /EHs-c-
// ?rva005EA575@Rva005EA575@@QAEHXZ @0x005EA575 22B thiscall indexed elem address via ranges
// Computes m_i2*0x24 plus m_begin of range m_i1 from base at this+0x10; sizes 0xC and 0x24 match Rva005EA58B ranges; caller 0x005EAF82
class Rva005EA575
{
public:
	int rva005EA575();
private:
	char m_pad[0x10];
	void *m_base;
	int m_i1;
	int m_i2;
};
int Rva005EA575::rva005EA575()
{
	int a = m_i1 * 12;
	int b = m_i2 * 36;
	void *base = m_base;
	return b + *(int *)((char *)base + a + 0x1c);
}
