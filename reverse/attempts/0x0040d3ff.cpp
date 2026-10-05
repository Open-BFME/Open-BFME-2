// ?rva0040D3FF@Rva0040D3FF@@QAEPAXXZ
// partial score=0.94 date=2026-10-05
// cl: /O1 /MD
// ?rva0040D3FF@Rva0040D3FF@@QAEPAXXZ @0x0040D3FF 64B: chain from bfmeFind1038 0x0040D008 loops int array at +0x14/+0x18 returning +0x1c entry whose +0x14 byte is set. Evidence: calls rowed 0x0040D008; single caller jmp at 0x0023D0BD; prev/next in Common.
class BfmeY1038
{
public:
	char m_pad0[0x14];
	unsigned char m_14;
	char m_pad15[0x7];
	void *m_1c;
	char m_pad20[0xc];
	int m_2c;
};
class Rva0040D3FF
{
public:
	char m_pad0[0x14];
	int *m_begin;
	int *m_end;
	BfmeY1038 *rva0040D008(int v);
	void *rva0040D3FF();
};
// ?rva0040D3FF@Rva0040D3FF@@QAEPAXXZ present-unmatched
void *Rva0040D3FF::rva0040D3FF()
{
	for (unsigned int i = 0; i < (unsigned int)(m_end - m_begin); ++i)
	{
		BfmeY1038 *y = rva0040D008(m_begin[i]);
		if (y != 0 && y->m_14 != 0)
			return y->m_1c;
	}
	return 0;
}
