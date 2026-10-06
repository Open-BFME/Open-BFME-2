// cl: /MD
// ?Rva0040D380Get@@YGHH@Z @0x0040D380 22B: chain from bfmeFind1038 0x0040D008 returns +0x2c or 1 when null. Evidence: calls rowed 0x0040D008; single caller jmp at 0x0023D07B; prev/next in Common.
class BfmeY1038
{
public:
	char m_pad0[0x2c];
	int m_2c;
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
int __stdcall Rva0040D380Get(int v)
{
	BfmeY1038 *y = bfmeFind1038(v);
	if (y == 0)
		return 1;
	return y->m_2c;
}
