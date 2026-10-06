// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?computeExtents@W3DDisplayString@@IAEXXZ, 0x001065D9, 138B: W3DDisplayString::computeExtents (leaf). Evidence: vtable slots getTextLength+0xC getText+0x8, m_font+0x8, renderer+0x14, m_size+0x1DC/0x1E0 from Dtor TU layout, Get_Formatted_Text_Extents row 0x00159FF0, releaseBuffer row 0x00036E70.
#include "unicode_string.h"

class GameFont;

class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual int getTextLength();
	virtual void notifyTextChanged();
	virtual void reset();
protected:
	UnicodeString m_textString;
	GameFont *m_font;
	DisplayString *m_next;
	DisplayString *m_prev;
};

class Vector2
{
public:
	float X;
	float Y;
};

class Render2DSentenceClass
{
public:
	~Render2DSentenceClass();
	virtual void Reset();
	Vector2 Get_Formatted_Text_Extents(const unsigned short *text);
private:
	char m_pad04[0xC0];
};

class W3DDisplayString : public DisplayString
{
public:
	virtual ~W3DDisplayString();
	virtual void reset();
protected:
	void computeExtents();
private:
	Render2DSentenceClass m_textRenderer;
	Render2DSentenceClass m_textRendererHotKey;
	UnicodeString m_hotkey;
	bool m_textChanged;
	bool m_fontChanged;
	bool m_bfmeFlag1EC;
	bool m_bfmeFlag20C;
	int m_hotKeyPosX;
	int m_hotKeyPosY;
	int m_textPosX;
	int m_textPosY;
	int m_hotKeyColor;
	int m_currTextColor;
	int m_currDropColor;
	int m_bfmeResetFields[6];
	bool m_useHotKey;
	char m_pad1D9[3];
	int m_sizeX;
	int m_sizeY;
	int m_clipLoX;
	int m_clipLoY;
	int m_clipHiX;
	int m_clipHiY;
	int m_lastResourceFrame;
};

void W3DDisplayString::computeExtents()
{
	unsigned int len = getTextLength();
	if (len == 0 || m_font == 0) {
		m_sizeX = 0;
		m_sizeY = 0;
	} else {
		Vector2 extents = m_textRenderer.Get_Formatted_Text_Extents(getText().str());
		m_sizeX = extents.X;
		m_sizeY = extents.Y;
	}
}
