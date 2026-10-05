// cl: /O1 /DNDEBUG /MD
//
// 0x0007F92A (26B): guard wrapper tail-jumping to 0x0007F87C. Returns
// unless TheTerrainRenderObject (VA 0x00DE1EAC) and its +0x37C0 subobject
// are both present, then tail-jumps to the rowed body with the arguments
// and this intact. Address names.

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject; // VA 0x00DE1EAC

struct Rva0007F92AGlobalView
{
	char m_pad[0x37C0];
	void *m_sub; // +0x37C0
};

class Rva0007F92AHost
{
public:
	void rva0007F92A(int a, int b);
	void rva0007F87C(int a, int b);
};

void Rva0007F92AHost::rva0007F92A(int a, int b)
{
	Rva0007F92AGlobalView *g = (Rva0007F92AGlobalView *)TheTerrainRenderObject;
	if (g == 0)
		return;
	if (g->m_sub == 0)
		return;
	return rva0007F87C(a, b);
}
