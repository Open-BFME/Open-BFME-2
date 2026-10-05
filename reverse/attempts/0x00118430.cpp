// ?Render@WW3D@@SA?AW4WW3DErrorType@@AAVRenderObjClass@@AAVRenderInfoClass@@@Z
// partial score=0.97 date=2026-10-05
// cl: /O2 /G7 /DNDEBUG /MD /EHsc

// Semantic donor: BFME1 6583b3c1 WW3DRenderObjectBfme.cpp.
// Target118430..1184CC Ghidra156 returns bool; RenderInfo light pointer+28,
// camera vslot13, object vslot12 and mesh camera+4 are target facts.
// All instructions match except unresolved SortingRendererClass::Flush call
// at+88 to12F190 (Ghidra2824). Additional cache reset174BA6 (113) is pinned
// opaque but still unrowed. Neither dependency is claimed recovered here.
// WW3D/class spellings are donor-carried; cache-reset identity is unknown.

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
	CameraClass *Camera;
	char m_padding04[0x24];
	void *light_environment;
};

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
};

class DX8MeshRendererClass
{
public:
	void Set_Camera(CameraClass *camera) { m_camera = camera; }
	void Flush(void);
	void Clear_Pending_Delete_Lists(void);

private:
	char m_padding00[4];
	CameraClass *m_camera;
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class Rva00DF6F94GapFillerContext { public: void rva174ba6(); };
extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

class SortingRendererClass
{
public:
	static void Flush(void);
};

class StaticSortListClass
{
public:
	virtual ~StaticSortListClass(void);
	virtual void Add_To_List(RenderObjClass *obj, unsigned sort_level);
	virtual void Render_And_Clear(RenderInfoClass &rinfo);
};

class WW3D
{
public:
	static bool Render(RenderObjClass &obj, RenderInfoClass &rinfo);

	static bool IsInitted;
	static bool AreStaticSortListsEnabled;
	static StaticSortListClass *CurrentStaticSortLists;
};

// ?Render@WW3D@@SA_NAAVRenderObjClass@@AAVRenderInfoClass@@@Z
bool WW3D::Render(RenderObjClass &obj, RenderInfoClass &rinfo)
{
	if (!IsInitted)
		return true;

	rinfo.Camera->On_Frame_Update();
	rinfo.Camera->Apply();
	DX8Wrapper::Set_DX8_Render_State(8, 3);
	if (rinfo.light_environment != 0)
		DX8Wrapper::Set_Light_Environment(
			reinterpret_cast<LightEnvironmentClass *>(rinfo.light_environment));

	TheDX8MeshRenderer->Set_Camera(rinfo.Camera);
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
