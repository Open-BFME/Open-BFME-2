// cl: /O1 /DNDEBUG /MD /EHsc
// ?gogoMessageBox@GameWindowManager@@UAEPAVGameWindow@@HHHHGVUnicodeString@@0P6AXXZ111@Z @0x002C187D 137B
// GameWindowManager::gogoMessageBox 11-arg forwarder to 12-arg with FALSE; BFME1 donor GameWindowManagerMessageBox.cpp; vtable 0x7C7C90 slot 18 calls slot 17 (+0x44); UnicodeString by-value via StringBase<G> pins 0x37050/0x36E70.

typedef int Int;
typedef unsigned short wchar_t;
typedef unsigned short UnsignedShort;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class UnicodeString;

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

class GameWindow;

typedef void (*GameWinMsgBoxFunc)(void);

class GameWindowManager
{
public:
	virtual void pad0() = 0;
	virtual void pad1() = 0;
	virtual void pad2() = 0;
	virtual void pad3() = 0;
	virtual void pad4() = 0;
	virtual void pad5() = 0;
	virtual void pad6() = 0;
	virtual void pad7() = 0;
	virtual void pad8() = 0;
	virtual void pad9() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
	virtual void pad14() = 0;
	virtual void pad15() = 0;
	virtual void pad16() = 0;
	virtual GameWindow *gogoMessageBox(Int x, Int y, Int width, Int height, UnsignedShort buttonFlags, UnicodeString titleString, UnicodeString bodyString, GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback);
	virtual GameWindow *gogoMessageBox(Int x, Int y, Int width, Int height, UnsignedShort buttonFlags, UnicodeString titleString, UnicodeString bodyString, GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback, Bool useLogo);
	virtual void pad19() = 0;
	virtual void pad20() = 0;
	virtual void pad21() = 0;
	virtual void pad22() = 0;
};

GameWindow *GameWindowManager::gogoMessageBox(Int x, Int y, Int width, Int height, UnsignedShort buttonFlags, UnicodeString titleString, UnicodeString bodyString, GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback)
{
	return gogoMessageBox(x, y, width, height, buttonFlags, titleString, bodyString, yesCallback, noCallback, okCallback, cancelCallback, false);
}
