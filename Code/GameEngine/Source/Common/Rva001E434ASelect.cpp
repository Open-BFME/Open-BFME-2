// cl: /MD
// ?rva001E434A@Rva001E434A@@QAEPAXXZ @0x001E434A 19B: select member pointer by flag at +0x1a6.
// Evidence: 3 callers at 0x001E62E6 0x001E8460 0x00274C4B; offsets +0x38 +0x198 +0x1a6.
class Rva001E434A
{
public:
	void *rva001E434A();
	char _0[0x38];
	int m_38;
	char _pad[0x198-0x38-4];
	int m_198;
	char _pad2[0x1a6-0x198-4];
	unsigned char m_flag;
};

void *Rva001E434A::rva001E434A()
{
	return m_flag ? (void *)&m_198 : (void *)&m_38;
}
