// cl: /O1 /MD /EHsc /DNDEBUG /G7
// ?rva000AFA92@Rva000AFA92@@QAE_NHHHHH@Z @0x000AFA92 68B
// Banked attempt reverse/attempts/0x000afa92.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
//
// ?rva000AFA92@Rva000AFA92@@QAE_NHHHHH@Z @0x000AFA92 68B: index-gated
// forward. Forms idx from two +0x120E4-spaced ints, the +8 factor and two
// arguments; when idx is below +0x20 and the +0x98 word table is set,
// forwards (idx, table[idx], plus three args) to the pinned same-object
// 0x000AE490, else returns false. Honest address-derived names; boundary
// verified (frame at 0xAFA92, xor/pop/ret at end).

class Rva000AFA92
{
public:
	bool rva000AE490(int idx, unsigned short w, int c, int d, int e);
	bool rva000AFA92(int a, int b, int c, int d, int e);

private:
	char m_pad00[0x8];
	int m_8;
	char m_pad0C[0x20 - 0x0C];
	int m_20;
	char m_pad24[0x98 - 0x24];
	unsigned short *m_98;
	char m_pad9C[0x120E0 - 0x9C];
	int m_120E0;
	int m_120E4;
};

bool Rva000AFA92::rva000AFA92(int a, int b, int c, int d, int e)
{
	int idx = (m_120E4 + b) * m_8 + m_120E0 + a;
	if (idx < m_20)
	{
		unsigned short *t = m_98;
		if (t)
		{
			unsigned short w = t[idx];
			return rva000AE490(idx, w, c, d, e);
		}
	}
	return false;
}
