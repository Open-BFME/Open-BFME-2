// ?Rva0040D2FDSet@@YGXHHPAURva0040D2FDVec@@@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE /Oy-
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
class Rva002BA8F1Logic;
struct Rva002B488EResult;
class BfmeY1038;
extern "C" BfmeY1038 * __stdcall bfmeFind1038(int a);
// ?Rva0040D2FDSet@@YGXHHPAURva0040D2FDVec@@@Z present-unmatched
void __stdcall Rva0040D2FDSet(int a, int b, Rva0040D2FDVec *v)
{
	float x;
	float yy;
	BfmeY1038 *y = bfmeFind1038(a);
	if (y == 0)
		return;
	y->m_2c &= 0;
	y->m_30 = (int)((float)b * g_00DBA4F4);
	x = v->x;
	yy = v->y;
	y->m_58 = *(int *)&x;
	y->m_5c = *(int *)&yy;
}
