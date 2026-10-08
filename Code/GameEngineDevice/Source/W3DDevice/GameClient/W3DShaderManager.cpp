// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
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
struct Rva00077D0FVertexElement;

struct IDirect3DDevice8Vtbl
{
	void *m_reserved[69];
	long (__stdcall *m_setSamplerState)(IDirect3DDevice8 *device, unsigned stage, unsigned type, unsigned value);
	void *m_reserved70[16];
	long (__stdcall *m_createVertexShader)(IDirect3DDevice8 *device, const Rva00077D0FVertexElement *declaration, unsigned long *shader);
	void *m_reserved87[4];
	long (__stdcall *m_createShaderA)(IDirect3DDevice8 *device, const unsigned long *shaderData, unsigned long *shader);
	void *m_reserved92[14];
	long (__stdcall *m_createShaderB)(IDirect3DDevice8 *device, const unsigned long *shaderData, unsigned long *shader);
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

protected:
	static IDirect3DDevice8 *D3DDevice;
};

extern unsigned number_of_DX8_calls;
extern unsigned ScreenTextureStageStateChanges;

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
	++number_of_DX8_calls;
	++ScreenTextureStageStateChanges;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 2, 3);
	++number_of_DX8_calls;
	++ScreenTextureStageStateChanges;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 3, 3);
	++number_of_DX8_calls;
	++ScreenTextureStageStateChanges;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 5, 2);
	++number_of_DX8_calls;
	++ScreenTextureStageStateChanges;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 6, 2);
	++number_of_DX8_calls;
	++ScreenTextureStageStateChanges;
	DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_setSamplerState(DX8Wrapper::_Get_D3D_Device8(), 0, 7, 0);
	++number_of_DX8_calls;
	++ScreenTextureStageStateChanges;
	m_renderingToTexture = false;
	return m_renderTexture;
}

struct FileInfo
{
	long sizeHigh;
	long sizeLow;
	long timestampHigh;
	long timestampLow;
};

class File
{
public:
	enum { READ = 0x01, BINARY = 0x40 };
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int flags);
	bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const;
};

extern FileSystem *TheFileSystem;

class Rva00077D0FFileView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void close();
	virtual int read(void *buffer, int bytes);
};

struct Rva00077D0FVertexElement
{
	unsigned short stream;
	unsigned short offset;
	unsigned char type;
	unsigned char method;
	unsigned char usage;
	unsigned char usageIndex;
};

extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *heap, unsigned long flags, unsigned long bytes);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *heap, unsigned long flags, void *memory);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *text);

// Target 0x00077C19: paired file/heap/error flow with the matched loader below;
// this variant calls device slot 91. Keep its address-derived identity: neither
// the device interface spelling nor a donor loader name is a target fact.
// The separately rowed 0x00077CFE catch is emitted and tail-verified here too.
long __cdecl Rva00077C19Load(const char *strFilePath, unsigned int *pHandle)
{
	try
	{
		{
		File *file = TheFileSystem->openFile(strFilePath, File::READ | File::BINARY, 0);
		if (file == 0) {
			// The retail shared error call receives each string as an immediate
			// stack argument. MSVC folds a C++ message phi through EAX instead.
			__asm { push 0x00BC66EC }
			goto reportFailure;
		}

		FileInfo fileInfo;
		{
			AsciiString filename(strFilePath);
			TheFileSystem->getFileInfo(filename, &fileInfo);
		}
		unsigned long fileSize = fileInfo.sizeLow;

		unsigned long *shader = (unsigned long *)HeapAlloc(GetProcessHeap(), 8, fileSize);
		if (shader == 0) {
			__asm { push 0x00BC66C0 }
			goto reportFailure;
		}

		((Rva00077D0FFileView *)file)->read(shader, fileSize);
		((Rva00077D0FFileView *)file)->close();

		long hr = DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_createShaderA(
			DX8Wrapper::_Get_D3D_Device8(), shader, (unsigned long *)pHandle);
		HeapFree(GetProcessHeap(), 0, shader);
		if (hr < 0) {
			__asm { push 0x00BC66A4 }
			goto reportFailure;
		}
		}
		return 0;

	reportFailure:
		((void (__stdcall *)(void))OutputDebugStringA)();
		return (long)0x80004005L;
	}
	catch (...)
	{
		OutputDebugStringA("Error opening file \n");
		return (long)0x80004005L;
	}

	return 0;
}

long __cdecl Rva00077D0FLoad(const char *strFilePath, unsigned long *pHandle)
{
	try
	{
		{
		File *file = TheFileSystem->openFile(strFilePath, File::READ | File::BINARY, 0);
		if (file == 0) {
			// The retail shared error call receives each string as an immediate
			// stack argument. MSVC folds a C++ message phi through EAX instead.
			__asm { push 0x00BC66EC }
			goto reportFailure;
		}

		FileInfo fileInfo;
		{
			AsciiString filename(strFilePath);
			TheFileSystem->getFileInfo(filename, &fileInfo);
		}
		unsigned long fileSize = fileInfo.sizeLow;

		unsigned long *shader = (unsigned long *)HeapAlloc(GetProcessHeap(), 8, fileSize);
		if (shader == 0) {
			__asm { push 0x00BC66C0 }
			goto reportFailure;
		}

		((Rva00077D0FFileView *)file)->read(shader, fileSize);
		((Rva00077D0FFileView *)file)->close();

		long hr = DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_createShaderB(
			DX8Wrapper::_Get_D3D_Device8(), shader, pHandle);
		HeapFree(GetProcessHeap(), 0, shader);
		if (hr < 0) {
			__asm { push 0x00BC66A4 }
			goto reportFailure;
		}
		}
		return 0;

	reportFailure:
		((void (__stdcall *)(void))OutputDebugStringA)();
		return (long)0x80004005L;
	}
	catch (...)
	{
		OutputDebugStringA("Error opening file \n");
		return (long)0x80004005L;
	}

	return 0;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?D3DDevice@DX8Wrapper@@0PAUIDirect3DDevice8@@A=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")
#pragma comment(linker, "/alternatename:?m_oldRenderSurface@W3DShaderManager@@2PAUIDirect3DSurface8@@A=?g_Va009E1F64@@3IA")
#pragma comment(linker, "/alternatename:?m_renderTexture@W3DShaderManager@@2PAUIDirect3DTexture8@@A=?g_Va001FDE68@@3HA")
