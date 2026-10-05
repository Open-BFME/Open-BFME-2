// cl: /O1 /DNDEBUG /MD
//
// ?openKeyboard@DirectInputKeyboard@@IAEXXZ, retail 0x00098BD4, 188 bytes
// (formerly rowed as rva00098BD4; Zero Hour's openKeyboard, called by
// DirectInputKeyboard::init in Win32DIKeyboard.cpp).
// DirectInput creator for the 0xE28-byte keyboard input class: creates
// the DirectInput8 object plus the SysKeyboard device into +0xE20/+0xE24,
// then SetDataFormat/SetCooperativeLevel/SetProperty(BUFFER)/Acquire, with
// closeKeyboard (0x00098A6F) teardown on every FAILED path. Evidence: donor BFME1
// Win32DIKeyboard.cpp openKeyboard (same 5 FAILED checks, same DIPROPDWORD
// 0x14/0x10/0/0/0x100, same tail Acquire); neighbours 0x98B55 ctor (CapsLock)
// 0x98B8B dtor and 0x98A6F closeKeyboard; W3DGameClient DirectInputKeyboard
// shape (Keyboard plus 8 tail bytes, BFME2 +4 to 0xE28).

extern void *ApplicationHInstance;
extern void *ApplicationHWnd;
// Matched DIR32 witness (w=1) in openKeyboard places this 16-byte GUID-sized
// value at VA 0x00CDF7E8 (.rdata); extent ends before the adjacent value at
// VA 0x00CDF7F8. Bytes are retail's initial value.
extern const unsigned char g_00CDF7E8[16] = {
	0x30, 0x80, 0x79, 0xBF, 0x3A, 0x48, 0xA2, 0x4D,
	0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00,
};
// Matched DIR32 witness (w=1) in openKeyboard places this 16-byte GUID-sized
// value at VA 0x00CDF678 (.rdata); extent ends before the adjacent value at
// VA 0x00CDF688. The call site passes it as CreateDevice's GUID argument.
extern const unsigned char g_00CDF678[16] = {
	0x61, 0x2B, 0x1D, 0x6F, 0xA0, 0xD5, 0xCF, 0x11,
	0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00,
};
// Matched DIR32 witness (w=1) in openKeyboard places the 24-byte DIDATAFORMAT
// value at VA 0x00C7C9A4 (.rdata), with dwSize=0x18 bounding the initializer.
// Its pointer bytes retain retail VA 0x00A29F20 (.text); no corresponding
// tracked C++ object exists here, so those bytes reproduce the target pointer,
// not a source-level object identity. Retail text follows at VA 0x00C7C9BC.
extern const unsigned char g_00C7C9A4[24] = {
	0x18, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x20, 0x9F, 0xA2, 0x00,
};

long __stdcall ji_0062af20(void *hinst, unsigned long ver, const void *riid, void **ppv, void *punk);
#pragma comment(linker, "/alternatename:?ji_0062af20@@YGJPAXKPBXPAPAX0@Z=?ji_0062af20@@YAXXZ")

struct DI8Obj;
struct DI8Table
{
	void *slot0;
	void *slot1;
	void *slot2;
	long (__stdcall *createDevice)(DI8Obj *self, const void *rguid, void **device, void *outer);
};

struct DI8Obj
{
	DI8Table *m_table;
};

struct DIDevObj;
struct DIDevTable
{
	void *slot0;
	void *slot1;
	void *slot2;
	void *slot3;
	void *slot4;
	void *slot5;
	long (__stdcall *setProperty)(DIDevObj *self, const void *rguid, const void *prop);
	long (__stdcall *acquire)(DIDevObj *self);
	void *slot8;
	void *slot9;
	void *slot10;
	long (__stdcall *setDataFormat)(DIDevObj *self, const void *format);
	void *slot12;
	long (__stdcall *setCooperativeLevel)(DIDevObj *self, void *hwnd, unsigned long flags);
};

struct DIDevObj
{
	DIDevTable *m_table;
};

struct DIPROPHEADER
{
	unsigned long dwSize;
	unsigned long dwHeaderSize;
	unsigned long dwObj;
	unsigned long dwHow;
};

struct DIPROPDWORD
{
	DIPROPHEADER diph;
	unsigned long dwData;
};

class DirectInputKeyboard
{
protected:
	void openKeyboard();
	void closeKeyboard();

private:
	unsigned char m_pad[0xE20];
	DI8Obj *m_pDirectInput;
	DIDevObj *m_pKeyboardDevice;
};

void DirectInputKeyboard::openKeyboard()
{
	long hr;
	hr = ji_0062af20(ApplicationHInstance, 0x800, g_00CDF7E8, (void **)&m_pDirectInput, 0);
	if (hr < 0)
	{
		closeKeyboard();
		return;
	}
	hr = m_pDirectInput->m_table->createDevice(m_pDirectInput, g_00CDF678, (void **)&m_pKeyboardDevice, 0);
	if (hr < 0)
	{
		closeKeyboard();
		return;
	}
	hr = m_pKeyboardDevice->m_table->setDataFormat(m_pKeyboardDevice, g_00C7C9A4);
	if (hr < 0)
	{
		closeKeyboard();
		return;
	}
	hr = m_pKeyboardDevice->m_table->setCooperativeLevel(m_pKeyboardDevice, ApplicationHWnd, 6);
	if (hr < 0)
	{
		closeKeyboard();
		return;
	}
	DIPROPDWORD prop;
	prop.diph.dwSize = 20;
	prop.diph.dwHeaderSize = 16;
	prop.diph.dwObj = 0;
	prop.diph.dwHow = 0;
	prop.dwData = 256;
	hr = m_pKeyboardDevice->m_table->setProperty(m_pKeyboardDevice, (const void *)1, &prop.diph);
	if (hr < 0)
	{
		closeKeyboard();
		return;
	}
	m_pKeyboardDevice->m_table->acquire(m_pKeyboardDevice);
}
