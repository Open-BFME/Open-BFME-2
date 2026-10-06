// cl: /O1 /MD
//
// ?rva004E8D3E@Rva004E8D3E@@QAEHHHH@Z @0x004E8D3E 72B.
// Triple-guarded bool: a pinned row-test hit, two magic/zero rejects, a
// member compare, then the pinned 0x4E8820 touch all funnel to shared
// true/false tails. Retail 0x004E8D3E..0x004E8D84. Pins are honest
// address-derived candidates (0x4E8820 is an in-range target).

class Rva0051274F
{
public:
	int rva0051274F(int a, int b, int c);
};

class Rva004E8820
{
public:
	void rva004E8820(int flag);
};

class Rva004E8D3E
{
public:
	int rva004E8D3E(int a, int b, int c);

private:
	char m_pad[0x284];
	int m_284;
};

// ?rva004E8D3E@Rva004E8D3E@@QAEHHHH@Z
int Rva004E8D3E::rva004E8D3E(int a, int b, int c)
{
	if (((Rva0051274F *)this)->rva0051274F(a, b, c) == 1)
		return 1;
	if (a != 0x4031 || c != 0)
		return 0;
	if (b == m_284)
		((Rva004E8820 *)this)->rva004E8820(0);
	return 1;
}
