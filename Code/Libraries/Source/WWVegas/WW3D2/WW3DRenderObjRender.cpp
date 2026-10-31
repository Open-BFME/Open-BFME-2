// ?Render@WW3D@@SA_NAAVRenderObjClass@@AAVRenderInfoClass@@@Z
// cl: /DNDEBUG /MD /EHsc
//
// WW3D::Render 0x00118430, 156 bytes, retail boundary 0x118430..0x1184CC.
// Semantic donor: BFME1 6583b3c1 WW3DRenderObjectBfme.cpp. Target facts read off
// retail: the return is a bool AL (b0 01 / c3), RenderInfoClass's light
// environment sits at +0x28 (not the donor's +0x1C), the camera vcall is
// slot 0x34 and the object vcall slot 0x30, and the mesh flush goes through
// TheDX8MeshRenderer (0x00DF363C) at +4 as the camera.
// Dependencies: 0x00135A70 (camera Apply), 0x0006615F (Set_DX8_Render_State),
// 0x000122EA0 (Set_Light_Environment), 0x00148030 (mesh Flush),
// 0x000174BA6 (gap-filler cache reset) and 0x00144580 (Clear_Pending_Delete_Lists)
// are all unrowed; they are declared here and called through the addresses the
// REL32s in retail name, and none is claimed recovered by this body. The +0x87
// static flush is the pinned ?rva0012F190@@YAXXZ. WW3D/RenderObjClass/StaticSortList
// spellings are donor-carried; the static-sort enable byte is 0x00DEC3D9 and the
// init flag 0x00DEC3D4.

class CameraClass;
class RenderInfoClass;
class LightEnvironmentClass;

class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void Render(RenderInfoClass &rinfo);
};

class CameraClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void On_Frame_Update(void);
	void Apply(void);
};

class RenderInfoClass
{
public:
	CameraClass &Camera;
	char m_padding04[0x24];
	LightEnvironmentClass *light_environment;
};

class WW3D;
struct IDirect3DDevice8;
class IDirect3DSurface9;
struct _D3DVIEWPORT8;
class Vector3;
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

class DX8MeshRendererClass
{
public:
	void Invalidate( bool shutdown );
	void Flush();
	void Set_Camera(CameraClass *camera) { m_camera = camera; }
	void Clear_Pending_Delete_Lists(void);
	char m_pad00[0x4];
private:
	CameraClass *m_camera; // +0x04
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class Rva00DF6F94GapFillerContext { public: void rva174ba6(); };
extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

// The +0x87 static flush: the callee reads only the global 0x00DEC4F4 and an
// SSE constant, so it takes no this and is __cdecl. Rowed as the static
// SortingRendererClass::Flush.
class SortingRendererClass
{
public:
	static void Flush(void);
};

class StaticSortListClass
{
public:
	virtual ~StaticSortListClass();
	virtual void Add_To_List(RenderObjClass *obj, unsigned sort_level);
	virtual void Render_And_Clear(RenderInfoClass &rinfo);
};

class WW3D
{
public:
	static bool Render(RenderObjClass &obj, RenderInfoClass &rinfo);

private:
	// ww3d.cpp defines these private (?IsInitted@WW3D@@0_NA, ...).
	static bool IsInitted;
	static bool AreStaticSortListsEnabled;
	static StaticSortListClass *CurrentStaticSortLists;
};

// ?Render@WW3D@@SA_NAAVRenderObjClass@@AAVRenderInfoClass@@@Z
bool WW3D::Render(RenderObjClass &obj, RenderInfoClass &rinfo)
{
	if (!IsInitted)
		return true;

	rinfo.Camera.On_Frame_Update();
	rinfo.Camera.Apply();
	DX8Wrapper::Set_DX8_Render_State(8, 3);
	if (rinfo.light_environment != 0)
		DX8Wrapper::Set_Light_Environment(rinfo.light_environment);

	TheDX8MeshRenderer->Set_Camera(&rinfo.Camera);
	obj.Render(rinfo);
	TheDX8MeshRenderer->Flush();
	TheMeshGapFillerContext->rva174ba6();

	bool old_enable = AreStaticSortListsEnabled;
	AreStaticSortListsEnabled = false;
	CurrentStaticSortLists->Render_And_Clear(rinfo);
	AreStaticSortListsEnabled = old_enable;

	SortingRendererClass::Flush();
	TheDX8MeshRenderer->Clear_Pending_Delete_Lists();
	return true;
}
