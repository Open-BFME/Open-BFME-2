// cl: /MD
// ?Rva0040D3B6Get@@YGMH@Z @0x0040D3B6 31B: chain from bfmeFind1038 0x0040D008 then Rva0040C985::rva0040C9A4 0x0040C9A4 returns BfmeZeroRange when null. Evidence: calls rowed 0x0040D008 0x0040C9A4; BfmeZeroRange at VA 0x00BBAEAC; single caller jmp at 0x0023D09C; prev 0x0040D380 next 0x0040D3E8 in Common.
class BfmeY1038
{
public:
	char m_pad0[0x34];
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
class Rva0040C985
{
public:
	float rva0040C9A4();
};
extern const float BfmeZeroRange;
float __stdcall Rva0040D3B6Get(int v)
{
	BfmeY1038 *y = bfmeFind1038(v);
	if (y == 0)
		return BfmeZeroRange;
	return ((Rva0040C985 *)y)->rva0040C9A4();
}
