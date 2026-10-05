// cl: /O1 /MD
// ?Rva0040D3D5Get@@YGHH@Z @0x0040D3D5 18B: chain from bfmeFind1038 0x0040D008 returns +0x30 dword or 0 when null. Evidence: calls rowed 0x0040D008; same TU family as rowed Rva0040D380Get 0x0040D380.
class BfmeY1038
{
public:
	char m_pad[0x30];
	int m_30;
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
int __stdcall Rva0040D3D5Get(int v)
{
	BfmeY1038 *y = bfmeFind1038(v);
	if (y == 0)
		return 0;
	return y->m_30;
}
