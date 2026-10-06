// cl: /DNDEBUG /MD /EHsc
// ?rva00273755@Drawable@@QAEXXZ @0x00273755 179B: Drawable anim draw with scale g_Va007C26F0 via rowed getter 0x00270BA8 and Anim2D width/height plus draw 0x002D7127; tail to 0x002736A8 on stale frame.
// Evidence: offsets +0x354/+0x2C/+0x64 match Rva00270025 layout, TheGameLogic+0x40 frame check, m_460/m_468/m_46C rect math, callers 0x00279734, neighbours Drawable_rva00273648.
class GameLogic
{
public:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;
extern float g_Va007C26F0;

class Anim2D
{
public:
	unsigned int getCurrentFrameWidth() const;
	unsigned int getCurrentFrameHeight() const;
};

class Rva002D7127 : public Anim2D
{
public:
	void rva002D7127(int x, int y, int width, int height);
};

class Rva00270025
{
public:
	virtual ~Rva00270025();
	Rva002D7127 *m_items[14];
	unsigned int m_vals[14];
};

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
private:
	unsigned char m_pad[0x354];
	Rva00270025 *m_354;
};

class Drawable
{
public:
	void rva00273755();
	void rva002736A8();
private:
	unsigned char m_pad0[0x354];
	Rva00270025 *m_354;
	unsigned char m_pad1[0x460 - 0x358];
	int m_460;
	int m_464;
	int m_468;
	int m_46c;
};

void Drawable::rva00273755()
{
	if (m_354 == 0)
		return;
	if (((Rva00270BA8 *)this)->rva00270BA8()->m_items[10] == 0)
		return;
	unsigned int cur = TheGameLogic->m_frame;
	unsigned int v = ((Rva00270BA8 *)this)->rva00270BA8()->m_vals[10];
	if (v >= cur) {
		int dw = m_468 - m_460;
		int w = ((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->getCurrentFrameWidth();
		int h = ((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->getCurrentFrameHeight();
		int y = m_46c - h;
		int x = (int)((float)dw * g_Va007C26F0 + (float)m_460 - (float)w * g_Va007C26F0);
		((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->rva002D7127(x, y, w, h);
	} else {
		rva002736A8();
	}
}
