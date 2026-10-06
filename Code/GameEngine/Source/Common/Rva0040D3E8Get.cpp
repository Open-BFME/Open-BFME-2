// cl: /MD
// ?Rva0040D3E8Get@@YGHH@Z @0x0040D3E8 23B: chain from bfmeFind1038 0x0040D008 then Rva0040C985::rva0040C9F4 0x0040C9F4 returns 0 when null. Evidence: calls rowed 0x0040D008 0x0040C9F4; single caller jmp at 0x0023D0B2; prev 0x0040D380 in Common.
class BfmeY1038
{
public:
	char m_pad0[0x34];
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
class Rva0040C985
{
public:
	int rva0040C9F4();
};
int __stdcall Rva0040D3E8Get(int v)
{
	BfmeY1038 *y = bfmeFind1038(v);
	if (y == 0)
		return 0;
	return ((Rva0040C985 *)y)->rva0040C9F4();
}
