// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ?rva000448CF@W3DDisplay@@QAEXMMMMMK@Z @0x000448CF 89B.
// Render2D line wrapper reusing the target-proven W3DDisplay +0x168
// Render2D view (same as rowed rva000433AC): clears the +0x48 byte in the
// Render2D member, then forwards two Vector2 temps plus width/color to the
// pinned Add_Line 0x00042A4D. Push order (color, width via fld/fstp dummy,
// two Vector2 temps) and movss temps prove the (x1,y1,x2,y2,width,color)
// shape; ret 0x18 proves six stack args. Address-derived name; offsets are
// target facts, Render2D +0x48 flag label descriptive. No header edits.
typedef unsigned long uint32;

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

class Render2DClass
{
public:
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, uint32 color);
	char m_pad48[0x48];
	unsigned char m_flag48;
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
	void rva000448CF(float x1, float y1, float x2, float y2, float width, uint32 color);
private:
	char m_pad14[0x164];
	Render2DClass *m_render2D;
};

void W3DDisplay::rva000448CF(float x1, float y1, float x2, float y2, float width, uint32 color)
{
	Render2DClass *rdClear = m_render2D;
	rdClear->m_flag48 = 0;
	Render2DClass *rd = m_render2D;
	rd->Add_Line(Vector2(x1, y1), Vector2(x2, y2), width, color);
}
