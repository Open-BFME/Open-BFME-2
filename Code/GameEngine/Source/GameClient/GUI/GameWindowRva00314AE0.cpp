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

void __stdcall Rva00314AE0(Image *image, int startX, int startY, int endX, int endY, int color)
{
	((W3DDisplay *)TheDisplay)->rva0004D6B3(image, (float)startX, (float)startY, (float)endX, (float)endY, color, 2);
}

void __stdcall Rva00314BC9(int a0, float a1, int startX, int startY, int endX, int endY)
{
	((W3DDisplay *)TheDisplay)->rva0004D664((float)startX, (float)startY, (float)endX, (float)endY, a1, a0);
}

void __stdcall Rva00314B28(int color, int a1, int startX, int startY, int endX, int endY)
{
	((Rva0004263F *)TheDisplay)->rva0004263F((float)startX, (float)startY, (float)(endX - startX), (float)(endY - startY), color);
}

void __stdcall Rva00314B75(int lineColor, float lineWidth, int startX, int startY, int endX, int endY)
{
	((W3DDisplay *)TheDisplay)->rva0008EEF0((float)startX, (float)startY, (float)(endX - startX), (float)(endY - startY), lineWidth, lineColor);
}
