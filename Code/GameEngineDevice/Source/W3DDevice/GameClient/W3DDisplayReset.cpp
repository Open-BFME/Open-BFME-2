// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// dxsdk
// platformsdk
// ?reset@W3DDisplay@@UAEXXZ, retail 0x00043418..0x00043511 (249 bytes), W3DDisplay vtable
// 0x007C3C80 slot 9 (WB 0x00966600). Zero Hour's W3DDisplay::reset spine: the base display
// reset (rowed 0x0025D9E3), then every render object leaves m_3DScene through a scene
// iterator; BFME 2 also clears the global +0xBBD flag and +0x98 value, the clip flag at
// +0x17C and two display globals, and under the DX8 thread lock evicts managed resources,
// clears the texture cache (rowed 0x0012641F) and re-inits the streak renderer.
#include <d3d9.h>

typedef bool Bool;
typedef float Real;

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
#include "../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

void Log_DX8_ErrorCode(unsigned int error);
void Rva0012641FClear();

#include "../../../Include/W3DDevice/GameClient/SimpleStreakRendererClass.h"

// The device keeps its D3D8 type name but is a Direct3D 9 device
// (EvictManagedResources, vtable slot 5).
struct IDirect3DDevice8;

#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

extern int g_bfmeDisplayAnimationSyncClock;
extern int g_Va00DB3BDC;

class RenderObjClass
{
public:
	virtual void Delete_This();
	void Add_Ref() { NumRefs++; }
	void Release_Ref() { if (--NumRefs == 0) Delete_This(); }
	int NumRefs;
};

class SceneIterator
{
public:
	virtual void s00();
	virtual void First();
	virtual void Next();
	virtual Bool Is_Done();
	virtual RenderObjClass *Current_Item();
};

#include "../../../Include/W3DDevice/GameClient/RTS3DScene.h"

class Display
{
public:
	void reset();
};

class W3DDisplay
{
public:
	virtual ~W3DDisplay();
	virtual void init();
	virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05();
	virtual void s06(); virtual void s07(); virtual void s08();
	virtual void reset();

	static RTS3DScene *m_3DScene;

private:
	unsigned char m_pad04[0x17C - 4];
	Bool m_isClippedEnabled;		// +0x17C
};

void W3DDisplay::reset()
{
	((Display *)this)->reset();
	TheWritableGlobalData->field0BBD = false;

	SceneIterator *sceneIter = m_3DScene->Create_Iterator();
	sceneIter->First();
	while (!sceneIter->Is_Done()) {
		RenderObjClass *robj = sceneIter->Current_Item();
		if (robj) {
			robj->Add_Ref();
			m_3DScene->Remove_Render_Object(robj);
			robj->Release_Ref();
		}
		sceneIter->Next();
	}
	m_3DScene->Destroy_Iterator(sceneIter);

	m_isClippedEnabled = false;
	if (TheWritableGlobalData)
		TheWritableGlobalData->field0098 = 0.0f;
	g_bfmeDisplayAnimationSyncClock = 0;
	g_Va00DB3BDC = -1;

	BFMEDX8DeviceLock lock;
	HRESULT hr = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->EvictManagedResources();
	if (hr)
		Log_DX8_ErrorCode(hr);
	Rva0012641FClear();
	SimpleStreakRendererClass::Init(TheWritableGlobalData->m_useShadowMapping);
}
