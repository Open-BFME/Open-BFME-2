// cl: -O1 -GR- -EHsc-
int __cdecl rva005AE6F8(int a, int b, int c, char* z);

// ?rva005AE78A@@YAHHHH@Z @0x005AE78A 27B: cdecl 3-arg wrapper passing a char
// scratch slot to the pinned cdecl callee.
int __cdecl rva005AE78A(int a, int b, int c)
{
	char z;
	return rva005AE6F8(a, b, c, &z);
}

struct Rva005AE7A5Class
{
	int m_0;
	int m_4;

	int rva005AE7A5(int a1);
};

// ?rva005AE7A5@Rva005AE7A5Class@@QAEHH@Z @0x005AE7A5 33B: thiscall member
// forwarding (m_0, m_4, a1) to the row above, returning its result when it
// differs from m_4 and 0 otherwise (neg/sbb select, no cmov).
int Rva005AE7A5Class::rva005AE7A5(int a1)
{
	int m4 = m_4;
	int r = rva005AE78A(m_0, m4, a1);
	int d = r - m4;
	return d ? r : 0;
}
