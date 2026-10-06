// cl: /DNDEBUG /MD
// ?rva002864E6@Rva00285DC5@@QAEXPAMMHHHH_N@Z @ 0x002864E6 310B
// Circle/disc paint delegating to Rva00285DC5 row-range paint: converts world pos
// via 0.1f/0.5 floor/ceil through IAT floor/ceil, then midpoint loop calling
// 0x00285DC5 twice per row range. Evidence: same Rva00285DC5 this, same
// 0.1f 0x007C2424/0.5 0x007C26F8 immediates, callers at 0x00395DEC/0x0050BE94.
// x87 fistp via inline asm (retail uses fld/fistp, SSE cvttss2si differs); SSE for comiss.
// The scale and rounding bias are the 0.1f and 0.5 literals; the banked
// attempt read them through float/double globals, which hoisted the scale
// load ahead of the coordinate and shifted every fmul operand.
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

__forceinline long FloatToLong(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Rva00285DC5
{
public:
	void rva00285DC5(int r0, int r1, int col, int add, int f12, int f10, int f8, bool flag);
	void rva002864E6(float *p, float w, int add, int f12, int f10, int f8, bool flag);
};

void Rva00285DC5::rva002864E6(float *p, float w, int add, int f12, int f10, int f8, bool flag)
{
	if (w <= 0.0f)
		return;
	if (add == 0)
		return;
	float fx = (float)floor(p[0] * 0.1f + 0.5);
	int cx = FloatToLong(fx);
	float fy = (float)floor(p[1] * 0.1f + 0.5);
	int cy = FloatToLong(fy);
	float fr = (float)ceil(w * 0.1f);
	int rad = FloatToLong(fr);
	int y = rad;
	int d = 0;
	int err = 2 - 2 * rad;
	int bot = cx;
	int top = cx;
	while (true) {
		if (err + y > 0) {
			if (y == 0) {
				if (rad == 1) {
					d++;
					bot++;
					top--;
				}
			}
			rva00285DC5(top, bot, cy + y, add, f12, f10, f8, flag);
			if (y == 0)
				break;
			rva00285DC5(top, bot, cy - y, add, f12, f10, f8, flag);
			y--;
			err += 1 - 2 * y;
		}
		if (d <= err)
			continue;
		d++;
		bot++;
		top--;
		err += 2 * d + 1;
	}
}
