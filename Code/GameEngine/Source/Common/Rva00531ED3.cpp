// cl: /MD
// ?rva00531ED3@Rva00531ED3@@QAEGG@Z @ 0x00531ED3 (35B): __thiscall union-find Find with path compression over inline word table at +0; callers 0x00532480 0x0053248C 0x00532AE4 0x00532BB8.
class Rva00531ED3
{
public:
	unsigned short rva00531ED3(unsigned short idx);
	unsigned short m_table[1];
};
unsigned short Rva00531ED3::rva00531ED3(unsigned short idx)
{
	if (idx != m_table[idx])
		m_table[idx] = rva00531ED3(m_table[idx]);
	return m_table[idx];
}
