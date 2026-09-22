// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /arch:SSE /G7
// ?preRender@ScreenMotionBlurFilter@@UAE_NAA_NAAW4CustomScenePassModes@@@Z retail 0x000FD4CE (19B).
// Ported from Open-BFME-1 Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// (BFME1 0x007D8790, donor-verbatim): copies m_skipRender into skipRender,
// calls startRenderToTexture and returns true. Only the placed body is defined
// here.

enum CustomScenePassModes
{
	CUSTOM_SCENE_PASS_DUMMY = 0
};

struct IDirect3DSurface8;
struct IDirect3DTexture8;
struct IDirect3DDevice8;

struct IDirect3DDevice8Vtbl
{
	void *m_reserved[69];
	long (__stdcall *m_setSamplerState)(IDirect3DDevice8 *device, unsigned stage, unsigned type, unsigned value);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *m_vtable;
};

class W3DShaderManager
{
public:
	static void startRenderToTexture();
	static IDirect3DTexture8 *endRenderToTexture();

	static bool m_renderingToTexture;
	static IDirect3DSurface8 *m_oldRenderSurface;
	static IDirect3DTexture8 *m_renderTexture;
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *target, bool useDefaultDepth);

private:
	static IDirect3DDevice8 *D3DDevice;
};

extern unsigned g_numberOfDX8Calls;
extern unsigned g_d3dCallCount;

class ScreenMotionBlurFilter
{
public:
	virtual bool preRender(bool &skipRender, CustomScenePassModes &scenePassMode);

	char m_pad[0x09];
	bool m_skipRender;
};

bool ScreenMotionBlurFilter::preRender(bool &skipRender, CustomScenePassModes &scenePassMode)
{
	skipRender = m_skipRender;
	W3DShaderManager::startRenderToTexture();
	return true;
}

// ?endRenderToTexture@W3DShaderManager@@SAPAUIDirect3DTexture8@@XZ retail 0x00075D52 (228B).
// Ported from Open-BFME-1 Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// (BFME1 donor): BFME2 restores through DX8Wrapper::Set_Render_Target and
// programs the stage states with direct device SetSamplerState calls plus the
// two DX8 call counters. Only the placed body is defined here.

IDirect3DTexture8 *W3DShaderManager::endRenderToTexture()
{
	if (!m_renderingToTexture)
		return 0;
	DX8Wrapper::Set_Render_Target(m_oldRenderSurface, true);
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 1, 3);
	++g_numberOfDX8Calls;
	++g_d3dCallCount;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 2, 3);
	++g_numberOfDX8Calls;
	++g_d3dCallCount;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 3, 3);
	++g_numberOfDX8Calls;
	++g_d3dCallCount;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 5, 2);
	++g_numberOfDX8Calls;
	++g_d3dCallCount;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 6, 2);
	++g_numberOfDX8Calls;
	++g_d3dCallCount;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 7, 0);
	++g_numberOfDX8Calls;
	++g_d3dCallCount;
	m_renderingToTexture = false;
	return m_renderTexture;
}
