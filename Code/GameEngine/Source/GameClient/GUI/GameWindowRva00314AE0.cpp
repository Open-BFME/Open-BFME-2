// cl: /Oy- /DNDEBUG /MD /EHsc /Oi-
// ?Rva00314AE0@@YGXPAVImage@@HHHHH@Z, retail 0x00314AE0, 72 bytes.
// Int-coordinate drawImage wrapper that forwards to the float W3DDisplay
// helper 0x0004D6B3 with mode=2 (alpha). Evidence: chain lane (calls the
// just-landed ?rva0004D6B3@W3DDisplay@@QAEXPAVImage@@MMMMHH@Z); this=TheDisplay
// global 0x00DFE9D8 for the callee; four int args converted via cvtsi2ss to
// floats; vtable slot 66 of 0x007C7C90 in the packet.
// ?Rva00314BC9@@YGXHMHHHH@Z, retail 0x00314BC9, 74 bytes.
// Chain of 0x0004D664 (5-float + int core at DC): (int, float, int*4) forwarded
// with int-to-float conversions; same TheDisplay global; vtable slot 69 of
// 0x007C7C90.

class Image;
class Display;
extern Display *TheDisplay;

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
	void rva0004D664(float x0, float y0, float x1, float y1, float w, int color);
	void rva0008EEF0(float x0, float y0, float w, float h, float a1, int a0);
};

class Rva0004263F
{
public:
	void rva0004263F(float x0, float y0, float w, float h, int color);
};

void __stdcall Rva00314AE0(Image *image, int x0, int y0, int x1, int y1, int color)
{
	((W3DDisplay *)TheDisplay)->rva0004D6B3(image, (float)x0, (float)y0, (float)x1, (float)y1, color, 2);
}

void __stdcall Rva00314BC9(int a0, float a1, int a2, int a3, int a4, int a5)
{
	((W3DDisplay *)TheDisplay)->rva0004D664((float)a2, (float)a3, (float)a4, (float)a5, a1, a0);
}

void __stdcall Rva00314B28(int a0, int a1, int x0, int y0, int x1, int y1)
{
	((Rva0004263F *)TheDisplay)->rva0004263F((float)x0, (float)y0, (float)(x1 - x0), (float)(y1 - y0), a0);
}

void __stdcall Rva00314B75(int a0, float a1, int x0, int y0, int x1, int y1)
{
	((W3DDisplay *)TheDisplay)->rva0008EEF0((float)x0, (float)y0, (float)(x1 - x0), (float)(y1 - y0), a1, a0);
}
