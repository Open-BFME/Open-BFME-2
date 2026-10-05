// cl: /O1 /MD
// ?Rva0040D396Set@@YGXH@Z @0x0040D396 32B: chain from bfmeFind1038 0x0040D008 then Rva0040C985::rva0040C985 0x0040C985 with TheGameLogic frame does nothing when null. Evidence: calls rowed 0x0040D008 0x0040C985; TheGameLogic at VA 0x009FE78C; single caller jmp at 0x0023D086; prev 0x0040D380 next 0x0040D3B6 in Common.
class BfmeY1038
{
public:
	char m_pad0[0x34];
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
class Rva00DFE78C
{
public:
	char m_pad[0x40];
	int m_40;
};
class GameLogic;
extern GameLogic *TheGameLogic;
class Rva0040C985
{
public:
	void rva0040C985(int x);
};
void __stdcall Rva0040D396Set(int v)
{
	BfmeY1038 *y = bfmeFind1038(v);
	if (y == 0)
		return;
	((Rva0040C985 *)y)->rva0040C985(((Rva00DFE78C *)TheGameLogic)->m_40);
}
