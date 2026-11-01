// cl: /DNDEBUG /MD /EHsc
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

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock(void)
	{
		BFME_DX8_Thread_Lock();
	}

	~BFMEDX8DeviceLock(void)
	{
		BFME_DX8_Thread_Assert();
	}
};

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

class BaseHeightMapRenderObjClass
{
public:
	void loadRoadsAndBridges(W3DTerrainLogic *pTerrainLogic, Bool saveGame);

private:
	unsigned char m_pad0000[0x386C];
	W3DRoadBuffer *m_roadBuffer;      // +0x386C
	W3DBridgeBuffer *m_bridgeBuffer;  // +0x3870
};

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
