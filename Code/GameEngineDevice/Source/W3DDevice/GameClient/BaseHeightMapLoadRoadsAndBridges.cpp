// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?loadRoadsAndBridges@BaseHeightMapRenderObjClass@@QAEXPAVW3DTerrainLogic@@_N@Z
// retail 0x00067800, 102 bytes. Zero Hour BaseHeightMap.cpp verbatim (with
// DO_ROADS) inside BFME 2's DX8 device-mutex guard (the Lock/Assert pair
// rowed in BfmeDX8ThreadLock.cpp, as in W3DDisplayResetD3DDevice.cpp): skip
// when DX8Wrapper's device (0x00DEDA34) fails TestCooperativeLevel, else the
// road buffer (+0x386C, rowed W3DRoadBuffer::loadRoads) and the bridge
// buffer (+0x3870, W3DBridgeBuffer::loadBridges 0x000DFB3C).

typedef bool Bool;
typedef long HRESULT;
#define D3D_OK 0

void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);

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

struct IDirect3DDevice8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppvObj) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
	virtual HRESULT __stdcall TestCooperativeLevel() = 0;
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

protected:
	static IDirect3DDevice8 *D3DDevice;
};

class W3DTerrainLogic;

class W3DRoadBuffer
{
public:
	void loadRoads(void);
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
	DX8DeviceGuard guard;

	if (DX8Wrapper::_Get_D3D_Device8() && (DX8Wrapper::_Get_D3D_Device8()->TestCooperativeLevel()) != D3D_OK)
		return;	//device not ready to render anything

	if (m_roadBuffer) {
		m_roadBuffer->loadRoads();
	}
	if (m_bridgeBuffer) {
		m_bridgeBuffer->loadBridges(pTerrainLogic, saveGame);
	}
}
