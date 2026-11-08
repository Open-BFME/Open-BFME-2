// cl: /D_OPERATOR_NEW_DEFINED_ /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// dxsdk
// platformsdk
//
// ?loadRoadsAndBridges@BaseHeightMapRenderObjClass@@QAEXPAVW3DTerrainLogic@@_N@Z
// retail 0x00067800, 102 bytes. Zero Hour BaseHeightMap.cpp verbatim (with
// DO_ROADS) inside BFME 2's DX8 device-mutex guard (the Lock/Assert pair
// rowed in BfmeDX8ThreadLock.cpp, as in W3DDisplayResetD3DDevice.cpp): skip
// when DX8Wrapper's device (0x00DEDA34) fails TestCooperativeLevel, else the
// road buffer (+0x386C, rowed W3DRoadBuffer::loadRoads) and the bridge
// buffer (+0x3870, W3DBridgeBuffer::loadBridges 0x000DFB3C).

#include <d3d9.h>

typedef bool Bool;

void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);

#include "../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

// The device keeps its D3D8 type name but is a Direct3D 9 device
// (TestCooperativeLevel, vtable slot 3).
struct IDirect3DDevice8;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

protected:
	static IDirect3DDevice8 *D3DDevice;
};

class W3DTerrainLogic;

class BaseHeightMapRenderObjClass;
class WorldHeightMap;
class W3DRoadBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void loadRoads();
protected:
	void freeRoadBuffers();
	void allocateRoadBuffers();
public:
	W3DRoadBuffer();
	~W3DRoadBuffer();
	void clearAllRoads();
	void setMap(WorldHeightMap*);
	char data[80]; // +0x00
};

class W3DBridgeBuffer
{
public:
	void loadBridges(W3DTerrainLogic *pTerrainLogic, Bool saveGame);
};

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
#define REFCOUNT_H
// d3d9.h already brought in the Platform SDK persist.h, whose guard hides
// WWSaveLoad's; declare the classes rendobj.h names.
class PersistFactoryClass;
class ChunkSaveClass;
class ChunkLoadClass;
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

void BaseHeightMapRenderObjClass::loadRoadsAndBridges(W3DTerrainLogic *pTerrainLogic, Bool saveGame)
{
	BFMEDX8DeviceLock guard;

	if (DX8Wrapper::_Get_D3D_Device8() && (reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->TestCooperativeLevel()) != D3D_OK)
		return;	//device not ready to render anything

	if (m_roadBuffer) {
		m_roadBuffer->loadRoads();
	}
	if (m_bridgeBuffer) {
		m_bridgeBuffer->loadBridges(pTerrainLogic, saveGame);
	}
}
