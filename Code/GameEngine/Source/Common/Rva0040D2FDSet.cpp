// cl: /DNDEBUG /MD /Oy-
// ?Rva0040D2FDSet@@YGXHHPAURva0040D2FDVec@@@Z @0x0040D2FD 79B: chain from bfmeFind1038 0x0040D008 clears +0x2c scales int arg by g_00DBA4F4 to +0x30 copies vec pair to +0x58/+0x5c. Evidence: calls rowed 0x0040D008; single caller jmp at 0x0023D05A; prev/next in Common.
class BfmeY1038
{
public:
	char m_pad0[0x2c];
	int m_2c;
	int m_30;
	char m_pad34[0x24];
	int m_58;
	int m_5c;
};
struct Rva0040D2FDVec
{
	float x;
	float y;
};
extern float g_00DBA4F4;
extern BfmeY1038 *__stdcall bfmeFind1038(int a);
void __stdcall Rva0040D2FDSet(int a, int b, Rva0040D2FDVec *v)
{
	float f[2];
	BfmeY1038 *y = bfmeFind1038(a);
	if (y == 0)
		return;
	y->m_2c &= 0;
	y->m_30 = (int)((float)b * g_00DBA4F4);
	f[0] = v->x;
	f[1] = v->y;
	y->m_58 = *(int *)&f[0];
	y->m_5c = *(int *)&f[1];
}
