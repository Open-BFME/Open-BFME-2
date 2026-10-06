// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1W3DDisplayString@@UAE@XZ, retail 0x00106162, 92 bytes (pinned; rowed
// deleting wrapper 0x0010625B). The Zero Hour destructor is empty; what
// retail runs is member and base teardown. Retail's unwind map destroys
// the DisplayString base (rowed dtor 0x00358994) in state 0 and two
// Render2DSentenceClass members at +0x14 and +0xD8 in states 1 and 2
// (m_textRenderer, m_textRendererHotKey), whose destructor is 0x00157C70.
// The UnicodeString released first at +0x19C directly follows them, so
// Render2DSentenceClass is 0xC4 bytes here. 0x00157C70 restores vtable
// 0x007D3C80, whose only slot is the rowed Render2DSentenceClass::Reset, so
// it is that class's non-virtual destructor, pinned from these calls.
// Supersedes the blocked BFME1 transfer, which had those members at
// +0xE0/+0x1B0.
#include "unicode_string.h"


class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText(UnicodeString text);
	virtual void pad02();
	virtual void pad03();
	virtual void notifyTextChanged();
	virtual void reset();
private:
	char m_pad04[0x10];
};

class Render2DSentenceClass
{
public:
	~Render2DSentenceClass();
	virtual void Reset();
private:
	char m_pad04[0xC0];
};

class W3DDisplayString : public DisplayString
{
public:
	virtual ~W3DDisplayString();
	virtual void reset();
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

W3DDisplayString::~W3DDisplayString()
{
}

void W3DDisplayString::reset()
{
	DisplayString::reset();
	(&m_textRenderer)->Reset();
	(&m_textRendererHotKey)->Reset();
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
	m_bfmeFlag1EC = true;
	m_hotkey.clear();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?pad02@DisplayString@@UAEXXZ=?rva0022C4DF@Rva0022C4DF@@QBE?AVUnicodeString@@XZ")
