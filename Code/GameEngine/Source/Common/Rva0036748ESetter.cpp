// cl: /MD
// ?rva0036748E@Rva0036748E@@QAEXH_N@Z @0x0036748E 37B
// Generic bit setter for dword at +0x4B8: mask = 1u << bit; set or clear by flag.
// Evidence: three wrappers become ready on landing (0x00368654 bit7 / 0x0036940A bit5 /
// 0x0036C897 bit3 each push hardcoded index plus forwarded flag and call here);
// 0x0036C80D tests bit3 via shr3+test and 0x0036C839 clears it via wrapper with 0;
// neighbouring shr-and getters at same offset (0x003685A7 bit6 / 0x003685B4 bit8).
// Owner unproven so honest address class+method names used.
class Rva0036748E
{
public:
	void rva0036748E(int bit, bool flag);
	void rva00368654(bool flag);
	void rva0036940A(bool flag);
	void rva0036C897(bool flag);
	char m_lead[0x4B8];
	unsigned int m_flags;
};
void Rva0036748E::rva0036748E(int bit, bool flag)
{
	if (flag)
		m_flags |= 1u << bit;
	else
		m_flags &= ~(1u << bit);
}
void Rva0036748E::rva00368654(bool flag)
{
	rva0036748E(7, flag);
}
void Rva0036748E::rva0036940A(bool flag)
{
	rva0036748E(5, flag);
}
void Rva0036748E::rva0036C897(bool flag)
{
	rva0036748E(3, flag);
}
