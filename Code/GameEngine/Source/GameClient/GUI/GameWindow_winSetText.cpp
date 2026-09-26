// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?winSetText@GameWindow@@UAEHVUnicodeString@@@Z, retail 0x0031484A, 88 bytes.
//
// GameWindow caption setter: copies the by-value text into the instance data,
// then notifies the window callback (slot 0x0C) with the parameter address.
// Ported from Open-BFME-1
// Code/GameEngine/Source/GameClient/GUI/GameWindowTextAndHitTest.cpp
// (BFME1 0x00479660, 114B; BFME2 trims to 88B under /O1).
// BFME2 facts (all retail-measured):
// - WinInstanceData lives at +0x30 (same TU family as
//   WinInstanceDataDisplayStrings.cpp); its setText is the rowed 0x3223B3.
// - The callback sits at +0x04; onTextChanged is its slot 0x0C.
// - The by-value UnicodeString parameter is copied once (StringBase copy
//   0x37050 into a stack temp for the setText argument) and destroyed here
//   at the end (releaseBuffer 0x36E70 on [ebp+8]); the callback borrows
//   [ebp+8] by address, so no second copy exists.

typedef int Int;
typedef unsigned short wchar_t;

#ifndef NULL
#define NULL 0
#endif

template <typename T>
class StringBase
{
	friend class UnicodeString;

	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	StringBase() { m_data = NULL; }
	~StringBase() { releaseBuffer(); }

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class UnicodeString
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &that) : m_data(that.m_data) {}
	~UnicodeString() {}

private:
	StringBase<wchar_t> m_data;
};

class DisplayString;

class WinInstanceData
{
public:
	void setText(UnicodeString text);

private:
	char m_pad[0x19C];
	DisplayString *m_text;
	DisplayString *m_tooltip;
};

class GameWindowCallback
{
public:
	virtual void callbackSlot0();
	virtual void callbackSlot1();
	virtual void callbackSlot2();
	virtual void onTextChanged(UnicodeString *text);
};

class GameWindow
{
public:
	virtual int winSetText(UnicodeString text);

	GameWindowCallback *m_callback; // this+0x04
	unsigned int m_status; // this+0x08
	unsigned char m_pad[0x30 - 0x0C];
	WinInstanceData m_instData; // this+0x30
};

// ?winSetText@GameWindow@@UAEHVUnicodeString@@@Z
int GameWindow::winSetText(UnicodeString text)
{
	m_instData.setText(text);

	if (m_callback != NULL)
		m_callback->onTextChanged(&text);

	return 0;
}
