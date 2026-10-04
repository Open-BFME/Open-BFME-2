// cl: /O1 /DNDEBUG /MD /EHsc
//
// Three DirectInputKeyboard virtuals (vtable 0x00BC8688; the ledger labels
// it ??_7AISkirmishPlayer@@6B@), Zero Hour's bodies from
// GameEngineDevice/Source/Win32Device/GameClient/Win32DIKeyboard.cpp:
//
//   slot 1   0x00098CAC  init: Keyboard::init (0x0023260F), then
//                        openKeyboard (0x00098BD4, ledger rva00098BD4, the
//                        DirectInput8 device setup).
//   slot 10  0x00098BC3  update: only extends Keyboard::update (0x00232BC7),
//                        a lone tail jump.
//   slot 14  0x00098BC8  getCapsState: GetKeyState(VK_CAPITAL) bit 0.

typedef bool Bool;

extern "C" __declspec(dllimport) short __stdcall GetKeyState(int nVirtKey);

#define VK_CAPITAL 0x14

class Keyboard
{
public:
	virtual void init();						///< matched 0x0023260F
	virtual void update();						///< matched 0x00232BC7
	virtual Bool getCapsState() = 0;
};

class DirectInputKeyboard : public Keyboard
{
public:
	virtual void init();
	virtual void update();
	virtual Bool getCapsState();

	void rva00098BD4();							///< matched 0x00098BD4 (Zero Hour's openKeyboard)
};

void DirectInputKeyboard::init()
{
	Keyboard::init();
	rva00098BD4();
}

void DirectInputKeyboard::update()
{
	Keyboard::update();
}

Bool DirectInputKeyboard::getCapsState()
{
	return (GetKeyState(VK_CAPITAL) & 0x01) != 0;
}
