// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?Rva0006297CClamp@@YGXPBM0PAM1@Z @0x0006297C 160B
// Evidence: vslot 17 of 0x007C57E0 class Rva00628FD; single callee
// Get_Render_Target_Resolution rowed; neighbours VslotSmallBodiesAJ/B.
class WW3D
{
public:
	static void Get_Render_Target_Resolution(int &a, int &b, int &c, bool &d);
};

void __stdcall Rva0006297CClamp(const float *a, const float *b, float *c, float *d)
{
	int w = 0;
	int h = 0;
	int w2 = 0;
	bool flag = false;
	WW3D::Get_Render_Target_Resolution(w, h, w2, flag);
	float x = 0.0f;
	if (!(0.0f >= a[0]))
		x = a[0];
	c[0] = x;
	float y;
	if (0.0f >= a[1])
		y = 0.0f;
	else
		y = a[1];
	c[1] = y;
	float wf = (float)w;
	float t = b[0] + c[0];
	if (t > wf)
		t = wf - c[0];
	else
		t = b[0];
	d[0] = t;
	float u = b[1] + c[1];
	if (u > wf)
		u = wf - c[1];
	else
		u = b[1];
	d[1] = u;
}
