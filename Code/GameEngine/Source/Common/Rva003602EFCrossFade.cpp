// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva003602EF@Rva003602EF@@QAEXXZ @0x003602EF 229B, a virtual (table entry at
// VA 0x00C16788): while the frame at +0x2C is non-negative, draw the image at
// +0x30 with alpha min(255, frame * rate(+0x28) * 255) and the image at +0x34
// with the complementary alpha over the rectangle at +0x18..+0x24, both in
// draw mode 2 through the rowed W3DDisplay wrapper 0x0004D6B3 on TheDisplay.
// The alpha clamp is cmovg and the float-to-int is cvttss2si, both from
// /arch:SSE. Names are address-derived.
class Image;
class Display;
extern Display *TheDisplay;
class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};
class Rva003602EF
{
public:
	void rva003602EF();
private:
	char m_pad00[0x18];
	int m_x;		// +0x18
	int m_y;		// +0x1C
	int m_width;		// +0x20
	int m_height;		// +0x24
	float m_rate;		// +0x28
	int m_frame;		// +0x2C
	Image *m_fadeIn;	// +0x30
	Image *m_fadeOut;	// +0x34
};
void Rva003602EF::rva003602EF()
{
	if (m_frame < 0)
		return;
	int alpha = (int)((float)m_frame * m_rate * 255.0f);
	if (alpha > 255)
		alpha = 255;
	((W3DDisplay *)TheDisplay)->rva0004D6B3(m_fadeIn, (float)m_x, (float)m_y, (float)(m_x + m_width), (float)(m_y + m_height), ((unsigned char)alpha << 24) | 0xFFFFFF, 2);
	((W3DDisplay *)TheDisplay)->rva0004D6B3(m_fadeOut, (float)m_x, (float)m_y, (float)(m_x + m_width), (float)(m_y + m_height), ((unsigned char)(255 - alpha) << 24) | 0xFFFFFF, 2);
}
