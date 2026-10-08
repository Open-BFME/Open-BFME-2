// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0W3DDisplayString@@QAE@XZ, 0x00106088, 203B: W3DDisplayString::W3DDisplayString (named).
// Evidence: pin plus BFME1 donor game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayString.cpp
// plus BFME2 layout of W3DDisplayStringDtor.cpp and W3DDisplayStringComputeExtents.cpp
// (renderers +0x14/+0xD8 size 0xC4 and reset twin 0x001061BE) plus caller 0x00090619.
#include "unicode_string.h"

class GameFont;

class DisplayString
{
public:
	DisplayString();
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
	Render2DSentenceClass();
	~Render2DSentenceClass();
	virtual void Reset();
	Vector2 Get_Formatted_Text_Extents(const unsigned short *text);
private:
	char m_pad04[0xC0];
};

class W3DDisplayString : public DisplayString
{
public:
	W3DDisplayString();
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
	int m_bfmeField1D8;
	int m_sizeX;
	int m_sizeY;
	int m_clipLoX;
	int m_clipLoY;
	int m_clipHiX;
	int m_clipHiY;
	int m_lastResourceFrame;
};

W3DDisplayString::W3DDisplayString()
{
	m_textChanged = false;
	m_textPosX = 0;
	m_textPosY = 0;
	for (int i = 0; i < 4; ++i) {
		(&m_currTextColor)[i] = 0;
		(&m_currTextColor)[i + 4] = 0;
	}
	m_hotKeyColor = -1;
	m_sizeX = 0;
	m_sizeY = 0;
	m_fontChanged = false;
	m_clipLoX = 0;
	m_clipLoY = 0;
	m_clipHiX = 0;
	m_clipHiY = 0;
	m_lastResourceFrame = 0;
	m_bfmeFlag20C = false;
	m_hotKeyPosX = 0;
	m_hotKeyPosY = 0;
	m_bfmeField1D8 = 0;
	m_bfmeFlag1EC = true;
}
