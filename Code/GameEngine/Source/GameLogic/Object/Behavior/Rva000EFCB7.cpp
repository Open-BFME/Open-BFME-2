// cl: /MD
// ?rva000EFCB7@Rva000EFCB7@@QAEHHPAG@Z @0x000EFCB7 55B: Word triple copy via base plus idx times 6 with reloads plus return 3. Evidence: unlock lane prev 0x000EFB68 same flags plus 6 callers in 0x000EFDF6 plus imul6 word-store push3 shape.
class Rva000EFCB7 {
public:
	int rva000EFCB7(int idx, unsigned short *src);
private:
	char _pad0[4];
	char *m_base;
};
int Rva000EFCB7::rva000EFCB7(int idx, unsigned short *src)
{
	int off = idx * 6;
	*(unsigned short *)(m_base + off + 0) = src[0];
	*(unsigned short *)(m_base + off + 2) = src[1];
	*(unsigned short *)(m_base + off + 4) = src[2];
	return 3;
}
