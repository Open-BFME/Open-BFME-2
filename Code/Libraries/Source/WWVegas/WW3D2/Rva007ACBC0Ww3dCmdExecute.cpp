// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD
// dxsdk
// platformsdk
// ?Execute@Rva007ACBC0CmdInterface@@..., retail 0x00117DC0 (330 B, RET 0x14): the "ww3d"
// debug command group's Execute (class table 0x00BCFBF0, registered by Rva007ACBC0Ww3dCmdGroup.cpp;
// WB 0x009C02D0 by its strings). "help" lists or explains sceneanalyst and pixmarker through
// the Debug slot 0x38 writer; "sceneanalyst <frames> <filter>" arms the frame count
// (0x00DEC414, frames + 1) and copies the 128-byte filter (0x00DEC418, terminated at +127);
// "pixmarker <name>" forwards to the rowed 0x0011F3D0. Both settings are file-scope statics of
// the WW3D unit (their only other reader is 0x001172B0 in the same range); retail schedules the
// frame store past the strncpy pushes, which needs the no-alias knowledge a static gives.
// WW3D::Prepare_Render_New_Frame, retail 0x001172B0 (317 B; WB 0x009BDFD0, ww3d.cpp): device
// lost/not-reset handling, Begin_Statistics, then the scene analyst countdown that switches
// the debug log groups through theDebug's command slot 0x8C.
#include <string.h>
#include <stdlib.h>
#include <d3d9.h>
class Debug;

class DebugCmdInterface
{
protected:
	virtual ~DebugCmdInterface() {}

public:
	__declspec(dllimport) __forceinline DebugCmdInterface() {}

	enum CommandMode
	{
		Normal,
		Structured,
		MAX
	};

	virtual bool Execute( Debug &dbg, const char *cmd, CommandMode cmdmode, unsigned argn, const char *const *argv ) = 0;
	virtual void Delete() = 0;
};

class Rva007ACBC0CmdInterface : public DebugCmdInterface
{
public:
	virtual bool Execute( Debug &dbg, const char *cmd, CommandMode cmdmode, unsigned argn, const char *const *argv );
	virtual void Delete();
};

// Placeholder slots up to AddCommands at 0x84; DebugPostStaticInit.cpp
// carries the named view.
class Debug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual bool AddCommands( const char *cmdgroup, DebugCmdInterface *cmdif ); // slot 0x84
	virtual void slot88();
	virtual void slot8C(const char *command);
};


static int g_rva00DEC414SceneAnalystFrames;
static char g_rva00DEC418SceneAnalystFilter[128];
void Rva0011F3D0Convert(const char *name, void *value);

bool Rva007ACBC0CmdInterface::Execute( Debug &dbg, const char *cmd, CommandMode cmdmode, unsigned argn, const char *const *argv )
{
	if (!strcmp(cmd, "help"))
	{
		if (cmdmode != Normal)
			return true;
		if (!argn)
		{
			dbg.slot38("ww3d group help:\n  sceneanalyst\n  pixmarker\n");
			return true;
		}
		if (!strcmp(argv[0], "sceneanalyst"))
		{
			dbg.slot38("sceneanalyst <number of frames> (*|Mesh*|MeshFXShader|MeshDX8Render|Skinning|DrawCall)\n\nDump rendering order (mesh names, draw calls) for a given number of (client) frames\n");
			return true;
		}
		if (!strcmp(argv[0], "pixmarker"))
		{
			dbg.slot38("pixmarker <markername>\n\nExecute a \"user marker\" for PIX allowing to trigger PIX actions\n");
			return true;
		}
		return false;
	}
	if (!strcmp(cmd, "sceneanalyst"))
	{
		if (argn < 2)
		{
			dbg.slot38("see help for parameters");
			return true;
		}
		g_rva00DEC414SceneAnalystFrames = atoi(argv[0]) + 1;
		strncpy(g_rva00DEC418SceneAnalystFilter, argv[1], 128);
		g_rva00DEC418SceneAnalystFilter[127] = 0;
		return true;
	}
	if (!strcmp(cmd, "pixmarker"))
	{
		if (argn < 1)
		{
			dbg.slot38("see help for parameters");
			return true;
		}
		Rva0011F3D0Convert(argv[0], 0);
		return true;
	}
	return false;
}

// The device keeps its D3D8 type name but is a Direct3D 9 device
// (TestCooperativeLevel, vtable slot 3).
struct IDirect3DDevice8;

class IDirect3DSurface9;
struct _D3DVIEWPORT8;
class Vector3;
class LightEnvironmentClass;
class DX8Wrapper
{
private:
	friend class WW3D;
protected:
	static IDirect3DDevice8 *D3DDevice;
	// dx8wrapper.cpp's protected static at VA 0x00DEDC70.
	static Vector3 Ambient_Color;
public:
	static bool Reset_Device(bool reload_assets);
	static IDirect3DSurface9 *_Get_DX8_Front_Buffer();
	static void Shutdown();
private:
	static void Get_Render_Target_Resolution(int &,int &,int &,bool &);
public:
	static void Set_Viewport(const _D3DVIEWPORT8 *viewport);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
	static void Begin_Scene_Inner(void);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	// dllimport: inlined at every use, so no out-of-line copy competes with retail's
	// Convert_Color (0x0006E1C0) or Set_Ambient (0x00117F50, DX8SetAmbient.cpp).
	__declspec(dllimport) static unsigned Convert_Color(const Vector3 &color, float alpha);
	__declspec(dllimport) static void Set_Ambient(const Vector3 &color);
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
};

namespace Debug_Statistics
{
	void Begin_Statistics();
}

extern Debug *theDebug;

class WW3D
{
public:
	static bool Prepare_Render_New_Frame();
};

bool WW3D::Prepare_Render_New_Frame()
{
	if (DX8Wrapper::D3DDevice)
	{
		HRESULT hr = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::D3DDevice)->TestCooperativeLevel();
		if (hr != D3D_OK)
		{
			if (hr != D3DERR_DEVICELOST && hr == D3DERR_DEVICENOTRESET)
				DX8Wrapper::Reset_Device(true);
			return false;
		}
	}
	Debug_Statistics::Begin_Statistics();
	if (g_rva00DEC414SceneAnalystFrames > 0)
	{
		char command[192];
		if (--g_rva00DEC414SceneAnalystFrames <= 0)
		{
			theDebug->slot8C("debug.add l - SceneAnalystFrame");
			strcpy(command, "debug.add l - SceneAnalyst");
			strcat(command, g_rva00DEC418SceneAnalystFilter);
			theDebug->slot8C(command);
		}
		else
		{
			strcpy(command, "debug.add l + SceneAnalyst");
			strcat(command, g_rva00DEC418SceneAnalystFilter);
			theDebug->slot8C(command);
			theDebug->slot8C("debug.add l + SceneAnalystFrame");
		}
	}
	return true;
}

// Retail 0x00117F10 (28 bytes), the class table's Delete slot (0x007CFBF8): the command
// interface destroys itself through its virtual destructor and the global operator delete.
void Rva007ACBC0CmdInterface::Delete()
{
	::delete this;
}
