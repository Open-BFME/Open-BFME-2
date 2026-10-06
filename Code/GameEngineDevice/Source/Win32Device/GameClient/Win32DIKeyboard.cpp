// cl: /DNDEBUG /MD /EHsc
//
// DirectInputKeyboard (vtable 0x00BC8688), Zero Hour's
// GameEngineDevice/Source/Win32Device/GameClient/Win32DIKeyboard.cpp. The
// constructor, destructor and closeKeyboard were rowed as AISkirmishPlayer's
// and an address-named input class's until the tables were identified: the
// base table 0x00BE81F0 is Keyboard's (Keyboard.cpp, KeyboardInitUpdate.cpp)
// and this one fills its pure getCapsState/getKey slots. W3DGameClient's
// keyboard factory 0x0004C6D4 news this class (0xE28 bytes).
//
//   0x00098A6F  closeKeyboard: Unacquire and Release the device (+0xE24),
//               then Release the DirectInput8 object (+0xE20). Also called
//               on openKeyboard's failure paths.
//   0x00098AAC  slot 16 getKey: one buffered DirectInput record into a
//               KeyboardIO.
//   0x00098B55  constructor: Keyboard() (0x00232920), clear both interface
//               pointers, then KEY_STATE_CAPSLOCK (0x0200) in m_modifiers
//               (+0x0C) from GetKeyState(VK_CAPITAL).
//   0x00098B8B  destructor: closeKeyboard, then ~Keyboard (0x00232976).
//   0x00098BC3  slot 10 update: only extends Keyboard::update (0x00232BC7),
//               a lone tail jump.
//   0x00098BC8  slot 14 getCapsState: GetKeyState(VK_CAPITAL) bit 0.
//   0x00098BD4  openKeyboard (DirectInputKeyboardOpen.cpp).
//   0x00098C90  scalar deleting destructor, emitted here.
//   0x00098CAC  slot 1 init: Keyboard::init (0x0023260F), then openKeyboard.
//
// Names are Zero Hour's, matched by body shape and slot position.

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

// The DirectInput 8 interface, as far as closeKeyboard calls it.
struct IDirectInput8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

#define VK_CAPITAL 0x14
#define KEY_STATE_CAPSLOCK 0x0200

class Keyboard
{
public:
	Keyboard();									///< matched 0x00232920
	virtual ~Keyboard();						///< matched 0x00232976
	virtual void init();						///< matched 0x0023260F
	virtual void update();						///< matched 0x00232BC7
	virtual Bool getCapsState() = 0;

protected:
	virtual void getKey(KeyboardIO *key) = 0;

	unsigned char m_unmodelled_04[0x0C - 0x04];
	UnsignedShort m_modifiers;					// +0x0C
	unsigned char m_unmodelled_0E[0xE20 - 0x0E];
};

class DirectInputKeyboard : public Keyboard
{
public:
	DirectInputKeyboard();
	virtual ~DirectInputKeyboard();

	virtual void init();
	virtual void update();
	virtual Bool getCapsState();

protected:
	virtual void getKey(KeyboardIO *key);

	void openKeyboard();						///< matched 0x00098BD4
	void closeKeyboard();

	IDirectInput8 *m_pDirectInput;				// +0xE20
	IDirectInputDevice8 *m_pKeyboardDevice;		// +0xE24
};

void DirectInputKeyboard::closeKeyboard()
{
	if (m_pKeyboardDevice)
	{
		m_pKeyboardDevice->Unacquire();
		m_pKeyboardDevice->Release();
		m_pKeyboardDevice = 0;
	}
	if (m_pDirectInput)
	{
		m_pDirectInput->Release();
		m_pDirectInput = 0;
	}
}

DirectInputKeyboard::DirectInputKeyboard()
{
	m_pDirectInput = 0;
	m_pKeyboardDevice = 0;

	if (GetKeyState(VK_CAPITAL) & 0x01)
		m_modifiers |= KEY_STATE_CAPSLOCK;
	else
		m_modifiers &= ~KEY_STATE_CAPSLOCK;
}

DirectInputKeyboard::~DirectInputKeyboard()
{
	// close keyboard and release all resource
	closeKeyboard();
}

void DirectInputKeyboard::init()
{
	Keyboard::init();
	openKeyboard();
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
