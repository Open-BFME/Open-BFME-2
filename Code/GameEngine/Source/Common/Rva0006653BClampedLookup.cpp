// cl: /MD
// ?rva0006653B@Rva0006653B@@QAEGHH@Z @ 0x0006653B 64B
// Clamped 2D ushort lookup: each index is pinned to [0, dim), dims at +0x08
// and +0x0C, ushort table at +0x24, column-major index dim8 * c + r.
// Evidence: 12 callers (0x00067CD6 0x00068AA3 0x0006AA5C plus 9 more),
// test+jge zero clamp plus cmp+jl dim clamp plus imul/add/mov-ax shape,
// ret 8 two-int thiscall. Owner class unproven; name stays address-derived.
// // cl: /O1 /MD (defaults mismatch register allocation; /O1 matches).
class Rva0006653B
{
public:
	unsigned short rva0006653B(int a, int b);

private:
	char m_pad0[8];
	int m_dim8;
	int m_dimC;
	char m_pad10[0x24 - 0x10];
	unsigned short *m_data24;
};

unsigned short Rva0006653B::rva0006653B(int a, int b)
{
	if (a < 0)
		a = 0;
	else if (a >= m_dim8)
		a = m_dim8 - 1;
	if (b < 0)
		b = 0;
	else if (b >= m_dimC)
		b = m_dimC - 1;
	int d = m_dim8;
	unsigned short *t = m_data24;
	return t[d * b + a];
}
