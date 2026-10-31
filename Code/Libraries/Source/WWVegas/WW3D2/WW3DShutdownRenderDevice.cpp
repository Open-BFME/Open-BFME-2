// cl: /DNDEBUG /MD /EHsc
// platformsdk
// BFME1 6583b3c1 WW3D_Shutdown_Bfme.cpp and ZH ww3d.cpp semantic donors.
// Native1180E0..118166 returns bool and holds the rowed DX8 device lock
// only around DX8Wrapper::Shutdown125DC0. Movie cleanup117A10 is rowed.
// WW3D::Shutdown: BFME 2 returns bool (as its Init does); callers are
// W3DDisplay's destructor after W3DShaderManager::shutdown and
// W3DDisplay::init's failed-device path, as in ZH. Class/global
// spellings follow the donor while capture/Lite/init slots and cleanup
// behavior are independently established from target calls and accesses.
#include <new>
#include <windows.h>

class FrameGrabClass
{
public:
	long *GetBuffer();
	virtual ~FrameGrabClass();
};
class RenderObjClass;
class RenderInfoClass;
class StaticSortListClass
{
public:
	virtual ~StaticSortListClass();
	virtual void Add_To_List(RenderObjClass *obj, unsigned sort_level);
	virtual void Render_And_Clear(RenderInfoClass &rinfo);
};
class RvaWW3DDestroySlot0 { public: virtual void *release(int); };
// ww3d.cpp defines WW3D's statics private (?IsCapturing@WW3D@@0_NA, ...); spell them so.
// Lite lives in ww3d.cpp's g_WW3D_Lite (VA 0x00DEC411), which the init path writes;
// the default sort list is WW3D::DefaultStaticSortLists (0x00DEC3F0).
class WW3D {
public:
    static bool Shutdown();
    static void Stop_Movie_Capture();
private:
    static bool IsCapturing; static bool IsInitted;
    static StaticSortListClass *DefaultStaticSortLists; };
extern unsigned char g_WW3D_Lite;
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct BfmeDeviceGuard { BfmeDeviceGuard() { BFME_DX8_Thread_Lock(); }
    ~BfmeDeviceGuard() { BFME_DX8_Thread_Assert(); } };
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
bool WW3D::Shutdown()
{
    if (IsCapturing) Stop_Movie_Capture();
    timeEndPeriod(1);
    if (!g_WW3D_Lite) { BfmeDeviceGuard guard; DX8Wrapper::Shutdown(); }
    ::delete DefaultStaticSortLists;
    IsInitted=false;
    return true;
}
