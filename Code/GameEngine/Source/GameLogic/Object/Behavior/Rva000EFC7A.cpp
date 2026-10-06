// cl: /MD
// ?rva000EFC7A@Rva000EFC7A@@QAEPAGHPAG@Z @0x000EFC7A 61B: Word triple load from base plus idx times 6 into out plus return base plus idx times 2. Evidence: unlock lane between 0x000EFB68 and 0x000EFCB7 same flags plus caller 0x000F478F plus imul6 word-copy lea-return shape.
class Rva000EFC7A {
public:
	unsigned short *rva000EFC7A(int idx, unsigned short *out);
private:
	char _pad0[4];
	char *m_base;
};
unsigned short *Rva000EFC7A::rva000EFC7A(int idx, unsigned short *out)
{
	int off = idx * 6;
	*out = *(unsigned short *)(m_base + off);
	++out;
	out[0] = *(unsigned short *)(m_base + off + 2);
	out[1] = *(unsigned short *)(m_base + off + 4);
	return (unsigned short *)(m_base + idx * 2);
}
