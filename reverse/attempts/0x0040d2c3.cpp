// ?rva0040D2C3@Rva0040D2C3@@QAEXXZ
// partial score=0.93 date=2026-10-05
// cl: /O1 /MD
// ?rva0040D2C3@Rva0040D2C3@@QAEXXZ @0x0040D2C3 58B: chain from bfmeFind1038 0x0040D008 loops int array at +0x14/+0x18 setting +0x2c to 1. Evidence: calls rowed 0x0040D008; single caller jmp at 0x0023D044; prev/next in Common.
class BfmeY1038
{
public:
	char m_pad0[0x2c];
	int m_2c;
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
class Rva0040D2C3
{
public:
	char m_pad0[0x14];
	int *m_begin;
	int *m_end;
	BfmeY1038 *rva0040D008(int v);
	void rva0040D2C3();
};
// ?rva0040D2C3@Rva0040D2C3@@QAEXXZ present-unmatched
void Rva0040D2C3::rva0040D2C3()
{
	for (unsigned int i = 0; i < (unsigned int)(m_end - m_begin); ++i)
	{
		BfmeY1038 *y = rva0040D008(m_begin[i]);
		if (y != 0)
			y->m_2c = 1;
	}
}
