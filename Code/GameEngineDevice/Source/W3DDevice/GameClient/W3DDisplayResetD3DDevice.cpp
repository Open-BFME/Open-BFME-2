// cl: /DNDEBUG /MD /EHsc
// ?Reset_D3D_Device@@YAX_N@Z, retail 0x0004312A, 278 bytes.
// Ported from Open-BFME-1
// (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayResetD3DDevice.cpp,
// their matched 311B row): ZH twin GeneralsMD W3DDisplay.cpp Reset_D3D_Device.
// BFME2 adaptations (all retail-measured): DX8-mutex guard (Lock/Assert pair,
// both matched rows in BfmeDX8ThreadLock.cpp) instead of the radar guard;
// Display vtable carries getWidth/getHeight/getBitDepth/getWindowed at
// +0x40/+0x44/+0x4C/+0x54; getBitDepth is byte-wide (movzx at both call sites);
// restore_assets passed explicitly (8-arg Set call, add esp,0x20).
// Human-readable names; the Win9x texture worker (0x1171B0) keeps an opaque
// address-derived pin (target proven by REL32, semantic identity unproven).

void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);
void __cdecl Rva001171B0(void);
void __cdecl clipCursorToClient(void);

class DX8DeviceGuard
{
public:
	DX8DeviceGuard(void)
	{
		BFME_DX8_Thread_Lock();
	}

	~DX8DeviceGuard(void)
	{
		BFME_DX8_Thread_Assert();
	}
};

// BFME2 Display carries three more virtuals ahead of getWidth than ZH's, so
// getWidth/getHeight/getBitDepth/getWindowed land at +0x40/+0x44/+0x4C/+0x54
// (all four call sites retail-measured; +0x48/+0x50 uncalled).
class Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual int getWidth();
	virtual int getHeight();
	virtual void slot48();
	virtual unsigned int getBitDepth();
	virtual void slot50();
	virtual bool getWindowed();
};

// Matched DIR32 sites establish TheDisplay at VA 0x00DFE9D8. This is in the
// PE .data zero-fill tail, so the retail startup value is null.
Display *TheDisplay = 0;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/w3derr.h
enum WW3DErrorType
{
	WW3D_ERROR_OK = 0,
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static bool Is_Initted(void) { return IsInitted; }
	static int Get_Render_Device(void);
	static WW3DErrorType Set_Render_Device(int dev = -1, int resx = -1, int resy = -1, int bits = -1, int windowed = -1, bool resize_window = false, bool reset_device = false, bool restore_assets = true);

private:
	static bool IsInitted;
};

// GetVersionExA: KERNEL32 import, same idiom as the neighbouring
// W3DDisplayClipCursor.cpp (no manual IAT pin needed for a standard import).
struct BfmeOsVersionInfo
{
	unsigned long dwOSVersionInfoSize;
	unsigned long dwMajorVersion;
	unsigned long dwMinorVersion;
	unsigned long dwBuildNumber;
	unsigned long dwPlatformId;
	char szCSDVersion[128];
};

#define BFME_VER_PLATFORM_WIN32_WINDOWS 1

extern "C" __declspec(dllimport) int __stdcall GetVersionExA(BfmeOsVersionInfo *lpVersionInformation);

// ?Reset_D3D_Device@@YAX_N@Z
void Reset_D3D_Device(bool active)
{
	if (TheDisplay && WW3D::Is_Initted() && !TheDisplay->getWindowed())
	{
		DX8DeviceGuard lock;

		if (active)
		{
			// switch back to desired mode when user alt-tabs back into game
			if (WW3D_ERROR_OK != (char)WW3D::Set_Render_Device(WW3D::Get_Render_Device(), TheDisplay->getWidth(), TheDisplay->getHeight(), TheDisplay->getBitDepth(), TheDisplay->getWindowed(), true, true, true))
			{
				BfmeOsVersionInfo osvi;
				osvi.dwOSVersionInfoSize = sizeof(BfmeOsVersionInfo);
				if (GetVersionExA(&osvi))
				{
					// check if we're running Win9x variant since they have buggy alt-tab
					// that requires reloading all textures.
					if (osvi.dwPlatformId == BFME_VER_PLATFORM_WIN32_WINDOWS)
					{
						Rva001171B0();
					}
				}

				clipCursorToClient();
			}
		}
		else
		{
			// switch to windowed mode whenever the user alt-tabs out of game.
			// Don't restore assets after reset since we'll do it when returning.
			WW3D::Set_Render_Device(WW3D::Get_Render_Device(), TheDisplay->getWidth(), TheDisplay->getHeight(), TheDisplay->getBitDepth(), TheDisplay->getWindowed(), true, true, false);
		}
	}
}
