// cl: /MD
// ?rva000EFDBB@Rva000EFDBB@@QAEXHGG@Z @0x000EFDBB 59B: Append two words to ptrs[idx] at plus4180 using lens[idx] at plus4400 as index with double inc. Evidence: unlock lane sibling Rva000F26DCAlloc same plus4180 plus4400 layout plus 2 callers plus lea-movsx-word-store shape.
class Rva000EFDBB {
public:
	void rva000EFDBB(int idx, unsigned short a, unsigned short b);
private:
	char _pad0[0x4180];
	unsigned short *m_ptrs[160];
	short m_lens[160];
	unsigned short m_counts[160];
};
void Rva000EFDBB::rva000EFDBB(int idx, unsigned short a, unsigned short b)
{
	short cur = m_lens[idx];
	m_ptrs[idx][cur] = a;
	++m_lens[idx];
	short nxt = m_lens[idx];
	m_ptrs[idx][nxt] = b;
	++m_lens[idx];
}
