// cl: /MD
// ?rva005D1F14@Rva005D1F14@@QAEHHH@Z @0x005D1F14 14B: byte-flag at +0x10 selecting 5 versus -1 ignoring two stack args. Evidence: unlock lane; callers 0x00577324 0x005CDE31 forward two args plus compare to -1.
class Rva005D1F14
{
public:
	int rva005D1F14(int a, int b);
private:
	unsigned char m_pad[0x10];
	unsigned char m_10;
};
int Rva005D1F14::rva005D1F14(int a, int b)
{
	(void)a;
	(void)b;
	return m_10 ? 5 : -1;
}
