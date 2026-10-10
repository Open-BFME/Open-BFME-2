// cl: /DNDEBUG /MD /EHsc
// ?rva000433AC@W3DDisplay@@QAEXI@Z, retail 0x000433AC, 108 bytes.
// Resolution apply: setWidth(arg), then floatconverted unsigned height (slot 17)
// and width (slot 16) build RectClass(0,0,w,h) for the +0x168 Render2D member's
// Set_Coordinate_Range.
// Evidence: same-this setWidth 0x0025C391; vtable slots 0x40/0x44 with fild
// unsigned fixup via const 0x007C26EC; rowed Set_Coordinate_Range 0x001188C0.
class RectClass
{
public:
	RectClass() {}
	RectClass(float x, float y, float w, float h) : X(x), Y(y), Width(w), Height(h) {}
	float X;
	float Y;
	float Width;
	float Height;
};

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
	void rva000456C9(const RefCountPtr<TextureClass> *tex);
};

class Render2DClass
{
public:
	void Set_Coordinate_Range(const RectClass &range);
	void Add_Quad(const RectClass &screen, const RectClass &uv, unsigned long c0, unsigned long c1, unsigned long c2, unsigned long c3);
	char m_pad00[0x48];
	bool m_texturing48;
};

class Display
{
public:
	virtual void setHeight(unsigned int height);
	virtual void setWidth(unsigned int width);
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
};

class W3DDisplay : public Display
{
public:
	void rva000433AC(unsigned int width);
	void rva00043340(unsigned int height);
	void rva000465CE(Rva000465CEBuffer *buffer, float x0, float y0, float x1, float y1, int color);
private:
	char m_pad14[0x164];
	Render2DClass *m_render2D;
};

void W3DDisplay::rva000433AC(unsigned int width)
{
	Display::setWidth(width);
	float h = (float)getHeight();
	float w = (float)getWidth();
	RectClass rc(0.0f, 0.0f, w, h);
	m_render2D->Set_Coordinate_Range(rc);
}

// ?rva00043340@W3DDisplay@@QAEXI@Z, retail 0x00043340, 108 bytes: the same body
// over Display::setHeight, which is Zero Hour's W3DDisplay::setHeight beside its
// setWidth. Only the extended Display call differs from rva000433AC.
void W3DDisplay::rva00043340(unsigned int height)
{
	Display::setHeight(height);
	float h = (float)getHeight();
	float w = (float)getWidth();
	RectClass rc(0.0f, 0.0f, w, h);
	m_render2D->Set_Coordinate_Range(rc);
}

// ?rva000465CE@W3DDisplay@@QAEXPAVRva000465CEBuffer@@MMMMH@Z, retail 0x000465CE,
// 235 bytes (vtable 0x00BC3C80 slot 29). Video-buffer quad draw: computes a
// half-texel UV inset from buffer +0x18, enables texturing on +0x168 Render2D,
// binds the buffer's texture via 0x000456C9, queries maxU/maxV via 0x000425CB /
// 0x00042605, scales the input alpha byte by buffer +0x20, and submits Add_Quad.
void W3DDisplay::rva000465CE(Rva000465CEBuffer *buffer, float x0, float y0, float x1, float y1, int color)
{
	float inset = (1.0f / (float)buffer->m_textureHeight18) * 0.5f;
	m_render2D->m_texturing48 = true;
	((Rva000456C9 *)m_render2D)->rva000456C9(buffer->texture());
	float maxV = buffer->rva00042605() - inset;
	RectClass uv;
	uv.X = inset;
	uv.Y = inset;
	uv.Width = buffer->rva000425CB() - inset;
	uv.Height = maxV;

	float scale = buffer->m_alpha20;
	unsigned int &alpha = *(unsigned int *)&buffer;
	alpha = (color >> 24);
	color = (color & 0xffffff) | ((unsigned int)((alpha & 0xff) * scale) << 24);
	m_render2D->Add_Quad(RectClass(x0, y0, x1, y1), uv, color, color, color, color);
}

