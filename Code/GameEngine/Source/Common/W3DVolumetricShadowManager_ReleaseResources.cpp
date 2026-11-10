// cl: /MD /EHsc
// ?ReleaseResources@W3DVolumetricShadowManager@@QAEXXZ @0x000F0972 111B (ZH W3DVolumetricShadowManager::ReleaseResources shape): release two globals plus buffer manager then clear 160-slot list under DX8 lock. Evidence: chain callee 0x000F0912 row plus LINK BONUS via 0x000F09E1 plus callers 0x0009A3E8 0x000F09FD.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
class Rva000F0972Releasable
{
public:
	virtual void f0();
	virtual void f1();
	virtual void __stdcall f2();
};
struct IDirect3DIndexBuffer8; extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;
struct IDirect3DVertexBuffer8; extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DBufferManagerClass.h"
extern class W3DBufferManager *TheW3DBufferManager;
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadowManager.h"
struct Rva000F0972LockGuard
{
	Rva000F0972LockGuard() { BFME_DX8_Thread_Lock(); }
	~Rva000F0972LockGuard() { BFME_DX8_Thread_Assert(); }
};
void W3DVolumetricShadowManager::ReleaseResources()
{
	Rva000F0972LockGuard guard;
	if ((*(Rva000F0972Releasable * *)&shadowIndexBufferD3D) != 0)
		(*(Rva000F0972Releasable * *)&shadowIndexBufferD3D)->f2();
	if ((*(Rva000F0972Releasable * *)&shadowVertexBufferD3D) != 0)
		(*(Rva000F0972Releasable * *)&shadowVertexBufferD3D)->f2();
	W3DBufferManager *mgr = TheW3DBufferManager;
	(*(Rva000F0972Releasable * *)&shadowIndexBufferD3D) = 0;
	(*(Rva000F0972Releasable * *)&shadowVertexBufferD3D) = 0;
	if (mgr != 0)
	{
		mgr->ReleaseResources();
		invalidateCachedLightPositions();
	}
}
