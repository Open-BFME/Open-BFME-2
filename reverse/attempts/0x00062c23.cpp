// ?rva00062C23@Rva00062C23Host@@QAEMMM@Z
// partial score=0.7 date=2026-10-05
// cl: /O1 /Oy- /DNDEBUG /MD /arch:SSE
//
// 0x00062C23 (34B): null-guard tail-jump. Returns 0.0f unless
// TheTerrainRenderObject is present, in which case it tail-jumps to the
// (blocked, pinned) 0x00066E69 with the global in ecx and the arguments
// intact. Address names.

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject; // VA 0x00DE1EAC

struct Rva00062C23GlobalView
{
	char m_pad[0x37C0];
	void *m_sub; // +0x37C0
};

class Rva00062C23Host
{
public:
	float rva00062C23(float a, float b);
	float rva00066E69(float a, float b);
};

float Rva00062C23Host::rva00062C23(float a, float b)
{
	(void)a;
	Rva00062C23GlobalView *g = (Rva00062C23GlobalView *)TheTerrainRenderObject;
	if (g == 0)
		goto zero;
	return ((Rva00062C23Host *)g)->rva00066E69(a, b);
zero:
	b = 0.0f;
	return b;
}
