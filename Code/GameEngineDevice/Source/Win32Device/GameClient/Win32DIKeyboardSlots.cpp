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
//   slot 16  0x00098AAC  getKey: one buffered DirectInput record into a
//                        KeyboardIO; the device is at +0xE24 as the
//                        constructor 0x00098B55 and openKeyboard set it up.

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned long DWORD;
typedef long HRESULT;

#define DI_OK 0
#define S_FALSE 1
#define DIERR_INVALIDPARAM ((HRESULT)0x80070057L)
#define DIERR_NOTINITIALIZED ((HRESULT)0x80070015L)
#define DIERR_OTHERAPPHASPRIO ((HRESULT)0x80070005L)
#define DIERR_INPUTLOST ((HRESULT)0x8007001EL)
#define DIERR_NOTACQUIRED ((HRESULT)0x8007000CL)

struct DIDEVICEOBJECTDATA
{
	DWORD dwOfs;
	DWORD dwData;
	DWORD dwTimeStamp;
	DWORD dwSequence;
	DWORD uAppData;
};

// The DirectInput 8 device interface, as far as getKey calls it.
struct IDirectInputDevice8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
	virtual HRESULT __stdcall GetCapabilities(void *caps) = 0;
	virtual HRESULT __stdcall EnumObjects(void *callback, void *ref, DWORD flags) = 0;
	virtual HRESULT __stdcall GetProperty(const void *guid, void *header) = 0;
	virtual HRESULT __stdcall SetProperty(const void *guid, const void *header) = 0;
	virtual HRESULT __stdcall Acquire() = 0;
	virtual HRESULT __stdcall Unacquire() = 0;
	virtual HRESULT __stdcall GetDeviceState(DWORD size, void *data) = 0;
	virtual HRESULT __stdcall GetDeviceData(DWORD size, DIDEVICEOBJECTDATA *data, DWORD *inOut, DWORD flags) = 0;
};

enum
{
	KEY_NONE = 0x00,
	KEY_LOST = 0xFF
};

enum
{
	KEY_STATE_UP = 0x0001,
	KEY_STATE_DOWN = 0x0002
};

// upstream layout: GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
struct KeyboardIO
{
	enum StatusType
	{
		STATUS_UNUSED = 0x00,
		STATUS_USED = 0x01
	};

	UnsignedByte key;
	UnsignedByte status;
	UnsignedShort state;
	UnsignedInt sequence;
};

extern "C" __declspec(dllimport) short __stdcall GetKeyState(int nVirtKey);

#define VK_CAPITAL 0x14

class Keyboard
{
public:
	virtual void init();						///< matched 0x0023260F
	virtual void update();						///< matched 0x00232BC7
	virtual Bool getCapsState() = 0;

protected:
	virtual void getKey(KeyboardIO *key) = 0;
};

class DirectInputKeyboard : public Keyboard
{
public:
	virtual void init();
	virtual void update();
	virtual Bool getCapsState();

	void rva00098BD4();							///< matched 0x00098BD4 (Zero Hour's openKeyboard)

protected:
	virtual void getKey(KeyboardIO *key);

private:
	unsigned char m_unmodelled_04[0xE24 - 0x04];
	IDirectInputDevice8 *m_pKeyboardDevice;		// +0xE24
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

void DirectInputKeyboard::getKey(KeyboardIO *key)
{
	DIDEVICEOBJECTDATA kbdat;
	DWORD num = 0;
	HRESULT hr;

	key->sequence = 0;
	key->key = KEY_NONE;

	if (m_pKeyboardDevice)
	{
		// get 1 key, if available
		num = 1;
		hr = m_pKeyboardDevice->Acquire();
		if (hr == DI_OK || hr == S_FALSE)
			hr = m_pKeyboardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &kbdat, &num, 0);

		switch (hr)
		{
			case DI_OK:
				break;

			case DIERR_INPUTLOST:
			case DIERR_NOTACQUIRED:
				// if we lost focus, attempt to re-acquire
				hr = m_pKeyboardDevice->Acquire();
				switch (hr)
				{
					case DIERR_INVALIDPARAM:
					case DIERR_NOTINITIALIZED:
					case DIERR_OTHERAPPHASPRIO:
						break;

					case DI_OK:
					case S_FALSE:
						// this will tell the system to loop again
						key->key = KEY_LOST;
						break;
				}
				return;

			default:
				return;
		}

		// no keys returned
		if (num == 0)
			return;

		key->key = (UnsignedByte)(kbdat.dwOfs & 0xFF);
		key->sequence = kbdat.dwSequence;
		key->state = ((kbdat.dwData & 0x0080) ? KEY_STATE_DOWN : KEY_STATE_UP);
		key->status = KeyboardIO::STATUS_UNUSED;
	}
}
