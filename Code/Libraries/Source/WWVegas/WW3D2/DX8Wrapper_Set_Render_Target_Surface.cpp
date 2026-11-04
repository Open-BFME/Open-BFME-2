// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// dxsdk
// platformsdk
// BFME's Direct3D device keeps the D3D8 type name but is a Direct3D 9 device:
// the calls below use IDirect3DDevice9's render-target slots (37..40) and
// IDirect3DSurface9's AddRef/Release from the vendored SDK, casting the
// DX8-spelled members at each call.
#include <d3d9.h>

struct IDirect3DSurface8;
struct IDirect3DDevice8;

#define DEVICE9 (reinterpret_cast<IDirect3DDevice9 *>(D3DDevice))
#define SURFACE9(surface) (reinterpret_cast<IDirect3DSurface9 *>(surface))
#define SURFACE9_OUT(slot) (reinterpret_cast<IDirect3DSurface9 **>(slot))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
#include "DX8WrapperClass.h"

// The DX8 call counter at 0x9EDA98 (the ledger's ?number_of_DX8_calls@@3IA).
extern unsigned number_of_DX8_calls;

// ?Set_Render_Target@DX8Wrapper@@SAXPAUIDirect3DSurface8@@_N@Z
void DX8Wrapper::Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer)
{
	if (renderTarget == 0 || renderTarget == DefaultRenderTarget) {
		if (DefaultRenderTarget != 0) {
			DEVICE9->SetRenderTarget(0, SURFACE9(DefaultRenderTarget));
			++number_of_DX8_calls;
			DEVICE9->SetDepthStencilSurface(SURFACE9(DefaultDepthBuffer));
			++number_of_DX8_calls;
			SURFACE9(DefaultRenderTarget)->Release();
			DefaultRenderTarget = 0;
			if (DefaultDepthBuffer != 0) {
				SURFACE9(DefaultDepthBuffer)->Release();
				DefaultDepthBuffer = 0;
			}
		}

		if (CurrentRenderTarget != 0) {
			SURFACE9(CurrentRenderTarget)->Release();
			CurrentRenderTarget = 0;
		}
		if (CurrentDepthBuffer != 0) {
			SURFACE9(CurrentDepthBuffer)->Release();
			CurrentDepthBuffer = 0;
		}
	} else if (renderTarget != CurrentRenderTarget) {
		if (DefaultDepthBuffer == 0) {
			DEVICE9->GetDepthStencilSurface(SURFACE9_OUT(&DefaultDepthBuffer));
			++number_of_DX8_calls;
		}
		if (DefaultRenderTarget == 0) {
			DEVICE9->GetRenderTarget(0, SURFACE9_OUT(&DefaultRenderTarget));
			++number_of_DX8_calls;
		}

		if (CurrentRenderTarget != 0) {
			SURFACE9(CurrentRenderTarget)->Release();
			CurrentRenderTarget = 0;
		}
		if (CurrentDepthBuffer != 0) {
			SURFACE9(CurrentDepthBuffer)->Release();
			CurrentDepthBuffer = 0;
		}

		CurrentRenderTarget = renderTarget;
		SURFACE9(CurrentRenderTarget)->AddRef();
		if (useDefaultDepthBuffer) {
			DEVICE9->SetRenderTarget(0, SURFACE9(CurrentRenderTarget));
			++number_of_DX8_calls;
			DEVICE9->SetDepthStencilSurface(SURFACE9(DefaultDepthBuffer));
			++number_of_DX8_calls;
		} else {
			DEVICE9->SetRenderTarget(0, SURFACE9(CurrentRenderTarget));
			++number_of_DX8_calls;
		}
	}

	IsRenderToTexture = false;
}
