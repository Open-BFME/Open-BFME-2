// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?drawRectClock@W3DDisplay@@UAEXMMMMMI@Z, retail 0x00045B45..0x000463B5 (2160 bytes)
// thiscall RET 0x18.
//
// Identity: W3DDisplay vtable slot +0xEC (absolute reference at 0x007C3D6C),
// next to the rowed drawOpenRect (+0xE0, 0x00044A1A) and the fill-rect slot
// (+0xE4, 0x00044C9A); +0xF0 (0x000463B5) is drawRemainingRectClock. Body is
// Zero Hour's W3DDisplay::drawRectClock (GeneralsMD W3DDisplay.cpp) with BFME
// 2's float coordinates and percent, the +0x168 Render2D's rowed
// Add_Quad(rect, color) 0x000428C7 for Add_Rect and the pinned Add_Tri
// 0x00045708; as in drawOpenRect the Reset/Render calls are gone. WB twin
// 0x00971AF0 (vtable evidence) is unnamed.
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Int;

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

class RectClass
{
public:
	RectClass(float left, float top, float right, float bottom) : Left(left), Top(top), Right(right), Bottom(bottom) {}
	float Left;
	float Top;
	float Right;
	float Bottom;
};

class Render2DClass
{
public:
	void Enable_Texturing(bool onoff) { m_texturing = onoff; }
	void Add_Quad(const RectClass &rect, unsigned long color);
	void Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2, const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2, unsigned long color);

private:
	char m_pad00[0x48];
	bool m_texturing;					// +0x48
};

#define W3DDISPLAY_SLOT(n) virtual void slot##n();

class W3DDisplay
{
public:
	W3DDISPLAY_SLOT(00) W3DDISPLAY_SLOT(01) W3DDISPLAY_SLOT(02) W3DDISPLAY_SLOT(03)
	W3DDISPLAY_SLOT(04) W3DDISPLAY_SLOT(05) W3DDISPLAY_SLOT(06) W3DDISPLAY_SLOT(07)
	W3DDISPLAY_SLOT(08) W3DDISPLAY_SLOT(09) W3DDISPLAY_SLOT(10) W3DDISPLAY_SLOT(11)
	W3DDISPLAY_SLOT(12) W3DDISPLAY_SLOT(13) W3DDISPLAY_SLOT(14) W3DDISPLAY_SLOT(15)
	W3DDISPLAY_SLOT(16) W3DDISPLAY_SLOT(17) W3DDISPLAY_SLOT(18) W3DDISPLAY_SLOT(19)
	W3DDISPLAY_SLOT(20) W3DDISPLAY_SLOT(21) W3DDISPLAY_SLOT(22) W3DDISPLAY_SLOT(23)
	W3DDISPLAY_SLOT(24) W3DDISPLAY_SLOT(25) W3DDISPLAY_SLOT(26) W3DDISPLAY_SLOT(27)
	W3DDISPLAY_SLOT(28) W3DDISPLAY_SLOT(29) W3DDISPLAY_SLOT(30) W3DDISPLAY_SLOT(31)
	W3DDISPLAY_SLOT(32) W3DDISPLAY_SLOT(33) W3DDISPLAY_SLOT(34) W3DDISPLAY_SLOT(35)
	W3DDISPLAY_SLOT(36) W3DDISPLAY_SLOT(37) W3DDISPLAY_SLOT(38) W3DDISPLAY_SLOT(39)
	W3DDISPLAY_SLOT(40) W3DDISPLAY_SLOT(41) W3DDISPLAY_SLOT(42) W3DDISPLAY_SLOT(43)
	W3DDISPLAY_SLOT(44) W3DDISPLAY_SLOT(45) W3DDISPLAY_SLOT(46) W3DDISPLAY_SLOT(47)
	W3DDISPLAY_SLOT(48) W3DDISPLAY_SLOT(49) W3DDISPLAY_SLOT(50) W3DDISPLAY_SLOT(51)
	W3DDISPLAY_SLOT(52) W3DDISPLAY_SLOT(53) W3DDISPLAY_SLOT(54) W3DDISPLAY_SLOT(55)
	W3DDISPLAY_SLOT(56) W3DDISPLAY_SLOT(57) W3DDISPLAY_SLOT(58)
	// +0xEC (retail 0x00045B45).
	virtual void drawRectClock(Real startX, Real startY, Real width, Real height, Real percent, UnsignedInt color);

private:
	char m_pad004[0x168 - 0x004];
	Render2DClass *m_2DRender;			// +0x168
};

void W3DDisplay::drawRectClock(Real startX, Real startY, Real width, Real height, Real percent, UnsignedInt color)
{
	// sanity
	if(percent < 1 || percent > 100)
		return;

	m_2DRender->Enable_Texturing( false );

// The rectanges are numberd as follows
//(x,y)	|---------|
//			| 4  | 1  |
//			|----+----|
//			| 3  | 2  |
//			|---------| (x + width, y + width)
//	
	// we're done, lets just draw one rectangle for it all.
	if(percent == 100)
	{
		m_2DRender->Add_Quad(RectClass( startX, startY, 
																		startX + width, startY + height), color);
	}
	else if( percent> 75)
	{
		//rectangle #1 & 2
		m_2DRender->Add_Quad(RectClass( startX + width/2, startY, 
																		startX + width, startY + height), color);
		// rectangle #3
		m_2DRender->Add_Quad(RectClass( startX, startY + height/2, 
																		startX + width/2, startY + height), color);
		// draw the part of rectangle 4
		Real remain = percent - 75;
		if(remain > 12)
		{
			//draw the full triangle
			m_2DRender->Add_Tri(Vector2(startX, startY), 
													Vector2(startX, startY + height/2),
													Vector2(startX + width/2, startY + height/2),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
			
			// draw the part of triangle
			Real percentDraw = (remain - 12)/ 13;
			m_2DRender->Add_Tri(Vector2(startX, startY), 
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + (width/2 * percentDraw), startY),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
		else
		{
			// draw the part of triangle
			Real percentDraw = (remain)/ 12;
			m_2DRender->Add_Tri(Vector2(startX, startY + height/2 - (height/2 * percentDraw)), 
													Vector2(startX, startY + height/2),
													Vector2(startX + width/2, startY + height/2),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}

	}
	else if( percent > 50)
	{
		//rectangle #1 & 2
		m_2DRender->Add_Quad(RectClass( startX + width/2, startY, 
																		startX + width, startY + height), color);
		// draw the part of rectangle 3
		Real remain = percent - 50;
		if(remain > 12)
		{
			//draw the full triangle
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY + height/2), 
													Vector2(startX, startY + height),
													Vector2(startX + width/2, startY + height),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
			
			// draw the part of triangle
			Real percentDraw = (remain - 12)/ 13;
			m_2DRender->Add_Tri(Vector2(startX, startY + height - (height/2 * percentDraw)), 
													Vector2(startX, startY + height),
													Vector2(startX + width/2, startY + height/2),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
		else
		{
			// draw the part of triangle
			Real percentDraw = (remain)/ 12;
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY + height),  
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + width/2 - ( width/2 * percentDraw), startY + height),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
	}
	else if(percent > 25)
	{
		// rectangel #1
		m_2DRender->Add_Quad(RectClass( startX + width/2, startY, 
																		startX + width, startY + height/2), color);
		// draw the part of rectangle 2
		Real remain = percent - 25;
		if(remain > 12)
		{
			//draw the full triangle
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY + height/2), 
													Vector2(startX + width, startY + height),
													Vector2(startX + width, startY + height/2),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
			
			// draw the part of triangle
			Real percentDraw = (remain - 12)/ 13;
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY + height/2), 
													Vector2(startX + width - (width/2 * percentDraw), startY + height),
													Vector2(startX + width, startY + height),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
		else
		{
			// draw the part of triangle
			Real percentDraw = (remain)/ 12;
			m_2DRender->Add_Tri(Vector2(startX + width, startY + height/2),  
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + width, startY + height/2 + ( height/2 * percentDraw)),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
	}
	else
	{
				// draw the part of rectangle 1
		
		if(percent > 12)
		{
			//draw the full triangle
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY), 
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + width, startY),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
			
			// draw the part of triangle
			Real percentDraw = (percent - 12)/ 13;
			m_2DRender->Add_Tri(Vector2(startX + width, startY),
													Vector2(startX + width/2, startY + height/2), 
													Vector2(startX + width, startY + (height/2 * percentDraw)),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
		else
		{
			// draw the part of triangle
			Real percentDraw = (percent)/ 12;
			m_2DRender->Add_Tri(Vector2(startX + width/2, startY),  
													Vector2(startX + width/2, startY + height/2),
													Vector2(startX + width/2 + (width/2 * percentDraw), startY ),
													Vector2(0,0),Vector2(0,0),Vector2(0,0),color);
		}
	}
}
