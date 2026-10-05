// cl: /O1 /arch:SSE /MD
// ?bfmeDoBOE@BfmeSinkBOE@@QAEXPAX0@Z @0x005B7454 600B
// BFME2 port of Open-BFME-1 game/GameEngine/Source/Common/BfmeSinkBOE_bfmeDoBOE.cpp: same DisplayString slots plus GameGetColorComponents plus clamp plus color assembly plus style switch.
// Evidence: retail cvttss2si dimensions into +0x40 +0x44 then list walk at +0x14 then heightChunk /3 push 3 idiv then perc branches with movss 1.0 plus GameGetColorComponents 0x002D2A9F plus clamp 0-255 plus GameMakeColor shl-or plus style switch with setColor +0x28 draw +0x38 getSize +0x3C; pin names BfmeSinkBOE::bfmeDoBOE; caller 0x00514CFD bfmeGoBOE; BFME2 outer pad 0x14 vs donor 0x10 for list at +0x14 widths at +0x40.
typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef int Color;
template <typename T>
inline T BfmeSinkBOEClamp(T low, T value, T high)
{
	if (value < low)
		return low;
	else if (value > high)
		return high;
	return value;
}
inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}
extern void GameGetColorComponents(Color color, UnsignedByte *red, UnsignedByte *green, UnsignedByte *blue, UnsignedByte *alpha);
class BfmeSinkBOEDisplayString
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void setColor(Color color, Color dropColor) = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void draw(Int x, Int y, Int scaleX, Int scaleY) = 0;
	virtual void getSize(Int *width, Int *height) = 0;
};
struct BfmeSinkBOELine
{
	Int m_style;
	unsigned char m_pad0004[0xc];
	BfmeSinkBOEDisplayString *m_displayString;
	BfmeSinkBOEDisplayString *m_secondDisplayString;
	Int m_posX;
	Int m_posY;
	unsigned char m_pad0020[4];
	Color m_color;
};
struct BfmeSinkBOENode
{
	BfmeSinkBOENode *m_next;
	BfmeSinkBOENode *m_prev;
	BfmeSinkBOELine *m_line;
};
struct BfmeSinkBOESize
{
	Int m_width;
	Int m_height;
};
class BfmeSinkBOE
{
public:
	void bfmeDoBOE(void *one, void *two);
private:
	unsigned char m_pad0000[0x14];
	BfmeSinkBOENode *m_displayedLineList;
	unsigned char m_pad0018[0x28];
	Int m_displayWidth;
	Int m_displayHeight;
};
void BfmeSinkBOE::bfmeDoBOE(void *one, void *two)
{
	const Real *display = reinterpret_cast<const Real *>(one);
	const Real *dimensions = reinterpret_cast<const Real *>(two);
	m_displayWidth = (Int)dimensions[0];
	m_displayHeight = (Int)dimensions[1];
	BfmeSinkBOENode *drawIt = m_displayedLineList->m_next;
	while (drawIt != m_displayedLineList)
	{
		BfmeSinkBOELine *cLine = drawIt->m_line;
		Int heightChunk = m_displayHeight / 3;
		Real perc = 0.0f;
		if (cLine->m_posY < heightChunk || cLine->m_posY > heightChunk * 2)
		{
			if (cLine->m_posY < 0 || cLine->m_posY > m_displayHeight)
				perc = 0.0f;
			else if (cLine->m_posY < heightChunk)
				perc = (Real)cLine->m_posY / heightChunk;
			else
				perc = 1.0f - (Real)(cLine->m_posY - 2 * heightChunk) / heightChunk;
		}
		else
			perc = 1.0f;
		UnsignedByte r, g, b, a;
		GameGetColorComponents(cLine->m_color, &r, &g, &b, &a);
		Int color = GameMakeColor(r, g, b, (UnsignedByte)BfmeSinkBOEClamp(0, (Int)(a * perc), 255));
		Int bColor = GameMakeColor(0, 0, 0, (UnsignedByte)BfmeSinkBOEClamp(0, (Int)(a * perc), 255));
		switch (cLine->m_style)
		{
		case 0:
		case 1:
		case 2:
			if (cLine->m_displayString != 0)
			{
				cLine->m_displayString->setColor(color, bColor);
				cLine->m_displayString->draw((Int)((Real)cLine->m_posX + display[0]), (Int)((Real)cLine->m_posY + display[1]), 1, 1);
			}
			break;
		case 3:
			{
				Int chunk = m_displayWidth / 3;
				BfmeSinkBOESize size;
				if (cLine->m_displayString != 0)
				{
					cLine->m_displayString->getSize(&size.m_width, &size.m_height);
					cLine->m_displayString->setColor(color, bColor);
					cLine->m_displayString->draw((Int)(display[0] + chunk - (size.m_width / 2)), (Int)((Real)cLine->m_posY + display[1]), 1, 1);
				}
				if (cLine->m_secondDisplayString != 0)
				{
					cLine->m_secondDisplayString->getSize(&size.m_width, &size.m_height);
					cLine->m_secondDisplayString->setColor(color, bColor);
					cLine->m_secondDisplayString->draw((Int)(display[0] + 2 * chunk - (size.m_width / 2)), (Int)((Real)cLine->m_posY + display[1]), 1, 1);
				}
			}
			break;
		}
		drawIt = drawIt->m_next;
	}
}
