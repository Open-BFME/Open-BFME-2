// cl: /DNDEBUG /MD /EHsc
// platformsdk
// ?Reset_D3D_Device@@YAX_N@Z, retail 0x0004312A, 278 bytes.
// Ported from Open-BFME-1
// (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayResetD3DDevice.cpp,
// their matched 311B row): ZH twin GeneralsMD W3DDisplay.cpp Reset_D3D_Device.
// BFME2 adaptations (all retail-measured): DX8-mutex guard (Lock/Assert pair,
// both matched rows in BfmeDX8ThreadLock.cpp) instead of the radar guard;
// Display vtable carries getWidth/getHeight/getBitDepth/getWindowed at
// +0x40/+0x44/+0x4C/+0x54; getBitDepth is byte-wide (movzx at both call sites);
// restore_assets passed explicitly (8-arg Set call, add esp,0x20).
// Human-readable names; the Win9x branch reloads textures through
// WW3D::_Invalidate_Textures (0x1171B0), as in ZH.

#include <windows.h>

void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);
void __cdecl clipCursorToClient(void);

#include "../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

// BFME2 Display carries three more virtuals ahead of getWidth than ZH's, so
// getWidth/getHeight/getBitDepth/getWindowed land at +0x40/+0x44/+0x4C/+0x54
// (all four call sites retail-measured; +0x48/+0x50 uncalled).
#include "../../../../GameEngine/Include/GameClient/Display.h"

// Matched DIR32 sites establish TheDisplay at VA 0x00DFE9D8. This is in the
// PE .data zero-fill tail, so the retail startup value is null.
Display *TheDisplay = 0;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/w3derr.h
enum WW3DErrorType
{
	WW3D_ERROR_OK = 0,
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

// ?Reset_D3D_Device@@YAX_N@Z
void Reset_D3D_Device(bool active)
{
	if (TheDisplay && WW3D::Is_Initted() && !TheDisplay->getWindowed())
	{
		BFMEDX8DeviceLock lock;

		if (active)
		{
			// switch back to desired mode when user alt-tabs back into game
			if (WW3D_ERROR_OK != WW3D::Set_Render_Device(WW3D::Get_Render_Device(), TheDisplay->getWidth(), TheDisplay->getHeight(), TheDisplay->getBitDepth(), TheDisplay->getWindowed(), true, true, true))
			{
				OSVERSIONINFOA osvi;
				osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
				if (GetVersionExA(&osvi))
				{
					// check if we're running Win9x variant since they have buggy alt-tab
					// that requires reloading all textures.
					if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
					{
						WW3D::_Invalidate_Textures();
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
