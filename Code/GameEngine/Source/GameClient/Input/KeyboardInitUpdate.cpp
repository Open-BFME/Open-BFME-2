// cl: /O1 /DNDEBUG /MD /EHsc
//
// Keyboard::init (retail 0x0023260F, 17B) and Keyboard::update (0x00232BC7,
// 22B), slots 1 and 10 of vtable 0x00BE81F0. That table is Keyboard's: its
// slots 14 and 16 are pure (Zero Hour's getCapsState and getKey), the
// DirectInputKeyboard table 0x00BC8688 fills them (0x00098BC8 is
// GetKeyState(VK_CAPITAL) & 1), and its own init (0x00098CAC) calls this
// init before openKeyboard (0x00098BD4). The ledger currently labels the two
// tables ??_7AIPlayer@@6B@ and ??_7AISkirmishPlayer@@6B@.
//
// Zero Hour's bodies (GameClient/Input/Keyboard.cpp): init names the keys
// (0x002306B8, Zero Hour's initKeyNames) and zeroes the input frame (+0xE1C);
// update bumps the input frame and refreshes the key data, which BFME2 does in
// two steps over its key vector (0x00232B7B, already pinned, then 0x00232A42)
// where Zero Hour calls updateKeys.

typedef int Int;

class Keyboard
{
public:
	virtual void init();
	virtual void update();

protected:
	void initKeyNames();						///< pinned 0x002306B8 (ZH name)

private:
	void rva00232B7B();							///< pinned 0x00232B7B
	void rva00232A42();

	unsigned char m_unmodelled_04[0xE1C - 0x04];
	Int m_inputFrame;							// +0xE1C (ZH name)
};

void Keyboard::init()
{
	initKeyNames();
	m_inputFrame = 0;
}

void Keyboard::update()
{
	m_inputFrame++;
	rva00232B7B();
	rva00232A42();
}
