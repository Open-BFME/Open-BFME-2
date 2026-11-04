// cl: /DNDEBUG /MD /EHsc
// ?setWidth@W3DDisplay@@UAEXI@Z, retail 0x000433AC, 108 bytes: Zero Hour's and
// BFME1's W3DDisplay::setWidth (BFME1 0x006E80A0, same callees in order).
// Resolution apply: Display::setWidth(arg), then floatconverted unsigned height (slot 17)
// and width (slot 16) build RectClass(0,0,w,h) for the +0x168 Render2D member's
// Set_Coordinate_Range.
// Evidence: same-this setWidth 0x0025C391; vtable slots 0x40/0x44 with fild
// unsigned fixup via const 0x007C26EC; rowed Set_Coordinate_Range 0x001188C0.
#include "../../../../Libraries/Source/WWVegas/WWMath/RectClass.h"

class TextureClass;
template<class T> class RefCountPtr;

class Rva000425CB
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual bool slot6();
	virtual void slot7();
	virtual void slot8();
	virtual const RefCountPtr<TextureClass> *texture();
	float rva000425CB();
	float rva00042605();
	char m_pad04[0x18 - 4];
	unsigned int m_textureHeight18;
};

class Rva000465CEBuffer : public Rva000425CB
{
public:
	char m_pad1C[4];
	float m_alpha20;
};

class Rva000456C9
{
public:
	void Set_Texture(const RefCountPtr<TextureClass> *tex);
};

class Render2DClass
{
public:
	void Set_Coordinate_Range(const RectClass &range);
	void Add_Quad(const RectClass &screen, const RectClass &uv, unsigned long c0, unsigned long c1, unsigned long c2, unsigned long c3);
	char m_pad00[0x48];
	bool m_texturing48;
};

#include "../../../../GameEngine/Include/GameClient/Display.h"

class W3DDisplay : public Display
{
public:
	virtual void setWidth(unsigned int width);
	virtual void setHeight(unsigned int height);
	void queueImage(Rva000465CEBuffer *buffer, float startX, float startY, float endX, float endY, int color);
private:
	char m_pad144[0x168 - 0x144];
	Render2DClass *m_render2D;
};

void W3DDisplay::setWidth(unsigned int width)
{
	Display::setWidth(width);
	float displayHeight = (float)getHeight();
	float displayWidth = (float)getWidth();
	RectClass rc(0.0f, 0.0f, displayWidth, displayHeight);
	m_render2D->Set_Coordinate_Range(rc);
}

// ?setHeight@W3DDisplay@@UAEXI@Z, retail 0x00043340, 108 bytes: the same body
// over Display::setHeight, which is Zero Hour's W3DDisplay::setHeight beside its
// setWidth (BFME1 0x006E8140). Only the extended Display call differs.
void W3DDisplay::setHeight(unsigned int height)
{
	Display::setHeight(height);
	float screenHeight = (float)getHeight();
	float screenWidth = (float)getWidth();
	RectClass rc(0.0f, 0.0f, screenWidth, screenHeight);
	m_render2D->Set_Coordinate_Range(rc);
}

// ?queueImage@W3DDisplay@@QAEXPAVRva000465CEBuffer@@MMMMH@Z, retail 0x000465CE,
// 235 bytes (vtable 0x00BC3C80 slot 29). Video-buffer quad draw: computes a
// half-texel UV inset from buffer +0x18, enables texturing on +0x168 Render2D,
// binds the buffer's texture via 0x000456C9, queries maxU/maxV via 0x000425CB /
// 0x00042605, scales the input alpha byte by buffer +0x20, and submits Add_Quad.
void W3DDisplay::queueImage(Rva000465CEBuffer *buffer, float startX, float startY, float endX, float endY, int color)
{
	float inset = (1.0f / (float)buffer->m_textureHeight18) * 0.5f;
	m_render2D->m_texturing48 = true;
	((Rva000456C9 *)m_render2D)->Set_Texture(buffer->texture());
	float maxV = buffer->rva00042605() - inset;
	RectClass uv;
	uv.Left = inset;
	uv.Top = inset;
	uv.Right = buffer->rva000425CB() - inset;
	uv.Bottom = maxV;

	float scale = buffer->m_alpha20;
	unsigned int &alpha = *(unsigned int *)&buffer;
	alpha = (color >> 24);
	color = (color & 0xffffff) | ((unsigned int)((alpha & 0xff) * scale) << 24);
	m_render2D->Add_Quad(RectClass(startX, startY, endX, endY), uv, color, color, color, color);
}

