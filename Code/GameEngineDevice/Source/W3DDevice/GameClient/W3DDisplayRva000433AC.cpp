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
	RectClass(float x, float y, float w, float h) : X(x), Y(y), Width(w), Height(h) {}
	float X;
	float Y;
	float Width;
	float Height;
};

class Render2DClass
{
public:
	void Set_Coordinate_Range(const RectClass &range);
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
