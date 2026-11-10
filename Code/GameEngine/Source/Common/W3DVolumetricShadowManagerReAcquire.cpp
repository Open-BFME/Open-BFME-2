// cl: /MD /EHsc
// dxsdk
// platformsdk
// ?ReAcquireResources@W3DVolumetricShadowManager@@QAE_NXZ @0x000F09E1 148B: reacquire IB plus VB via D3DDevice then manager reacquire under DX8 lock. Evidence: LINK BONUS names this mangling plus donor ZH ReAcquireResources plus chain callee 0x000F0972 row plus callers 0x0009A270 0x0009A390.
#include <d3d9.h>

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
// The device keeps its D3D8 type name but is a Direct3D 9 device
// (CreateVertexBuffer slot 26, CreateIndexBuffer slot 27).
struct IDirect3DDevice8;
// D3DDevice is protected in dx8wrapper.h; read it through WW3D2's accessor.
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
// g_00DEBCE0: matched references place it at VA 0xdebce0 (retail .data initial value 0).
struct IDirect3DIndexBuffer8; extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;
// g_00DEBCDC: matched references place it at VA 0xdebcdc (retail .data initial value 0).
struct IDirect3DVertexBuffer8; extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DBufferManagerClass.h"
extern class W3DBufferManager *TheW3DBufferManager;
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadowManager.h"
struct Rva000F09E1LockGuard
{
	Rva000F09E1LockGuard() { BFME_DX8_Thread_Lock(); }
	~Rva000F09E1LockGuard() { BFME_DX8_Thread_Assert(); }
};
bool W3DVolumetricShadowManager::ReAcquireResources()
{
	Rva000F09E1LockGuard guard;
	ReleaseResources();
	IDirect3DDevice9 *dev = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
	if (FAILED(dev->CreateIndexBuffer(0x8000, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFMT_INDEX16,
			D3DPOOL_DEFAULT, reinterpret_cast<IDirect3DIndexBuffer9 **>(&shadowIndexBufferD3D), 0)))
		return false;
	if (shadowVertexBufferD3D == 0)
	{
		if (FAILED(dev->CreateVertexBuffer(0x18000, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0,
				D3DPOOL_DEFAULT, reinterpret_cast<IDirect3DVertexBuffer9 **>(&shadowVertexBufferD3D), 0)))
			return false;
	}
	W3DBufferManager *mgr = TheW3DBufferManager;
	if (mgr != 0)
	{
		if (!mgr->ReAcquireResources())
			return false;
	}
	return true;
}

