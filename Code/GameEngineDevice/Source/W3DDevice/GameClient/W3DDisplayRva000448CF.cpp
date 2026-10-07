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

struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; };
bool ClipLine2D(ICoord2D *start,ICoord2D *end,ICoord2D *returnStart,ICoord2D *returnEnd,IRegion2D *region);

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
	// Native00042C80..00042EBD RET14 independently consumes two 2-float
	// references, float width and two unsigned colours. It normalizes the
	// perpendicular endpoint delta, allocates4 vertices/6 indices and assigns
	// distinct colours to each endpoint pair: donor Add_Line(a,b,width,c0,c1).
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, uint32 color0, uint32 color1);
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
	void rva00044928(float x1, float y1, float x2, float y2, float width, uint32 color0, uint32 color1);
private:
	char m_pad14[0x164];
	Render2DClass *m_render2D;
	IRegion2D m_clipRegion; // native +0x16C
	bool m_isClippedEnabled; // native +0x17C
};

void W3DDisplay::rva000448CF(float x1, float y1, float x2, float y2, float width, uint32 color)
{
	Render2DClass *rdClear = m_render2D;
	rdClear->m_flag48 = 0;
	Render2DClass *rd = m_render2D;
	rd->Add_Line(Vector2(x1, y1), Vector2(x2, y2), width, color);
}

// Native00044928..00044A1A RET1C: same measured receiver and +0x168
// renderer as the preceding 89-byte wrapper, but optionally clips through
// rowed ClipLine2D00025F406 and forwards two endpoint colours. Semantic lead
// is BFME1/ZH W3DDisplay::drawLine (two colours) plus drawOpenRect's clipping
// pattern, at BFME1 ba7ddda7e8. Target coordinates are floats, unlike the
// donor's integer overload, and the original overload name remains unknown.
void W3DDisplay::rva00044928(float x1, float y1, float x2, float y2, float width, uint32 color0, uint32 color1)
{
    m_render2D->m_flag48 = 0;
    if (m_isClippedEnabled) {
        ICoord2D start,end,returnStart,returnEnd;
        start.x=(int)x1; start.y=(int)y1;
        end.x=(int)x2; end.y=(int)y2;
        if (ClipLine2D(&start,&end,&returnStart,&returnEnd,&m_clipRegion))
            m_render2D->Add_Line(Vector2((float)returnStart.x,(float)returnStart.y),
                                Vector2((float)returnEnd.x,(float)returnEnd.y),
                                width,color0,color1);
    } else {
        m_render2D->Add_Line(Vector2(x1,y1),Vector2(x2,y2),width,color0,color1);
    }
}
