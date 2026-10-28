// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
//
// ?UpdateShadowMap@W3DShadowMapManager@@QAEXPAVRTS3DScene@@@Z
// retail 0x0007DC01..0x0007DE26 (549 bytes EH RET 4).
// WorldBuilder twin 0x007EE110 names W3DShadowMapManager::UpdateShadowMap
// (W3DShadowMapManager.cpp assert line 276 "m_renderTarget.IsBound() &&
// m_depthBuffer") and supplies the statement order. Sole caller 0x0004A55F
// passes W3DDisplay::m_3DScene with ecx = the manager at 0x00DE1FF8.
// Body: bail unless GlobalData+0x62 enables shadow maps; when the +0x28
// reset flag is set or the bound +0x14 render target is no longer the
// configured ShadowMap MapSize (g_00DB447C first dword compared with the
// smaller of the two rowed texture extents) the device surfaces are
// released (rowed 0x0007BAD6) the queued device interfaces dropped
// (pinned 0x00133283) and the resources re-acquired (pinned 0x0007DA23).
// With both the render target and the +0x1C depth surface present the
// scene is rendered into the target through a RenderInfoClass of the +0x00
// camera with a fresh rendering method pushed (vtable 0x00BC6C24 stores
// refcount 1 then a null method pointer and a zero word) and the
// WW3D::IsCurrentlyRenderingShadowMap flag raised; a border is drawn
// unless the +0x18 post-process target takes over and then the post
// process pass draws into it. Every callee by its row or pin spelling.
// The rendering method's two bases are novtable views (retail stores only
// the final vptr); its vtable at 0x00BC6C24 is unledgered and only its
// slot 0 (Delete_This) is declared here. The ShadowMap MapSize compare is
// unsigned because retail tests the extents with jb.

class CameraClass;
class RTS3DScene;
struct IDirect3DSurface8;

class GlobalData
{
public:
	char m_pad00[0x62];
	bool m_useShadowMap;	// +0x62
};
extern GlobalData *TheWritableGlobalData;

struct Db12
{
	int v0;
	int v1;
	int v2;
};
extern Db12 g_shadowMapSettings;
extern unsigned char g_009E1FFC;

template <class T>
inline const T &ShadowMin(const T &a, const T &b)
{
	return b < a ? b : a;
}

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	const RefCountPtr &operator=(const RefCountPtr &that);
	RefCountPtr(T *referent) : Referent(referent) {}
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr(void)
	{
		if (Referent)
			Referent->Release_Ref();
	}

public:
	T *Referent;
};

class __declspec(novtable) RefCountClass
{
public:
	__declspec(dllimport) __forceinline RefCountClass() : NumRefs(1) {}
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

namespace FXShader {
class __declspec(novtable) RenderingMethod : public RefCountClass
{
public:
	RenderingMethod() : m_next(0) {}

private:
	RefCountPtr<RenderingMethod> m_next;	// +0x08
};
}

class Rva0007DC01ShadowMethod : public FXShader::RenderingMethod
{
public:
	Rva0007DC01ShadowMethod() : m_0c(0) {}

private:
	int m_0c;	// +0x0C
};

class RenderInfoClass
{
public:
	RenderInfoClass(CameraClass &cam);
	~RenderInfoClass(void);
	void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
	void Pop_Rendering_Method(void);

private:
	char m_data[0x148];
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

class WW3D
{
public:
	static bool Begin_Render(bool clear_target, bool clear_zbuffer, const Vector3 &color, float dest_alpha);
	static bool End_Render(bool flip_frame);
	static void Set_Rendering_Shadow_Map(bool on) { IsCurrentlyRenderingShadowMap = on; }

private:
	template<class T> friend struct DataRowPrivateProbe;
	static bool IsCurrentlyRenderingShadowMap;
};

bool Rva001182A0(void *scene, RenderInfoClass &rinfo);

// Both texture and FX handles own one pointer. Texture references use the
// rowed release worker; FX references use count +4 and Delete_This slot 0.
class TextureClass
{
public:
    void Add_Ref() { ++refs; }
    void Release_Ref();
    void *vtable;
    unsigned short refs;
};
class FXShaderSetup : public RefCountClass {};

// The existing ctor and dtor have different ledger view names. Their whole
// bodies establish the same 36-byte parameter storage. Delegate cleanup to
// the rowed dtor; no base relationship or new symbol alias is asserted.
struct Rva0007BB16Record
{
    ~Rva0007BB16Record();
    void *name;
    int type;
    void *texture;
    float vector[4];
    int integer;
    bool boolean;
};
struct BfmeAssignRecord36
{
    BfmeAssignRecord36(const char *name, int type);
    void *name;
    int type;
    void *texture;
    float vector[4];
    int integer;
    bool boolean;
};
namespace
{
struct ShadowColorParameter
{
    __forceinline ShadowColorParameter(const char *name, int type) : storage(name, type) {}
    __forceinline ~ShadowColorParameter()
    {
        ((Rva0007BB16Record *)&storage)->~Rva0007BB16Record();
    }
    BfmeAssignRecord36 storage;
};
}
typedef char ShadowParameterStorageSize[
    sizeof(BfmeAssignRecord36) == 36 && sizeof(Rva0007BB16Record) == 36 ? 1 : -1];
namespace _STL
{
    template <> void vector<Rva0007BB16Record>::push_back(const Rva0007BB16Record &);
    template <> vector<Rva0007BB16Record>::~vector();
}
RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char *shader,
    const char *technique, const _STL::vector<Rva0007BB16Record> *parameters, int lod);
class Rva00072A94
{
public:
    Rva00072A94 &operator=(const Rva00072A94 &);
    void *ptr;
};
enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
struct IDirect3DDevice8;
// Preserve DX8Wrapper's existing device spelling. Retail uses the D3D9
// depth-surface signature at slot 29, including quality and shared handle.
struct ShadowDepthDeviceTable
{
    void *pad[29];
    long (__stdcall *createDepth)(IDirect3DDevice8 *, unsigned width,
        unsigned height, unsigned format, unsigned multisample, unsigned quality,
        int discard, IDirect3DSurface8 **surface, void *sharedHandle);
};
struct IDirect3DDevice8 { ShadowDepthDeviceTable *vtable; };

class DX8Wrapper
{
public:
	static RefCountPtr<TextureClass> Create_Render_Target(int width, int height, WW3DFormat format);
	static void Set_Render_Target(IDirect3DSurface8 *render_target, IDirect3DSurface8 *depth_buffer);
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);
protected:
	static IDirect3DDevice8 *D3DDevice;
	friend class Rva0007DA23ResourceManager;
};

void bfmeReleaseQueuedDeviceInterfaces();

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
	IDirect3DSurface8 *Peek() const { return m_surface; }

	IDirect3DSurface8 *m_surface;
};

struct CursorTextureSlot
{
	void *Ptr;

	W3DRadarResetSurface Get_Surface_Level(void);
};

class TextureBaseClass
{
public:
	int rva0013275A() const;
	int rva00132784() const;
};

class Rva0007BAD6
{
public:
	void rva0007BAD6();
};

class Rva0007DA23ResourceManager
{
public:
    bool ReAcquireResources();
    char pad[0x14];
    RefCountPtr<TextureClass> target; // +0x14
    RefCountPtr<TextureClass> post;   // +0x18
    IDirect3DSurface8 *depth;         // +0x1C
    Rva00072A94 writeShader;          // +0x20
    Rva00072A94 postShader;           // +0x24
};

class W3DShadowMapManager
{
public:
	void UpdateShadowMap(RTS3DScene *scene);
	void RenderBorder();
	void RenderPostProcess();

private:
	CameraClass *m_camera;	// +0x00
	char m_pad04[0x10];
	CursorTextureSlot m_renderTarget;	// +0x14
	CursorTextureSlot m_postTarget;	// +0x18
	IDirect3DSurface8 *m_depthBuffer;	// +0x1C
	char m_pad20[8];
	bool m_needsReset;	// +0x28
};

void W3DShadowMapManager::UpdateShadowMap(RTS3DScene *scene)
{
	if (!TheWritableGlobalData->m_useShadowMap)
		return;

	if (m_needsReset || (m_renderTarget.Ptr != 0 &&
		g_shadowMapSettings.v0 != ShadowMin<unsigned int>(reinterpret_cast<const TextureBaseClass &>(m_renderTarget).rva0013275A(),
			reinterpret_cast<const TextureBaseClass &>(m_renderTarget).rva00132784())))
	{
		reinterpret_cast<Rva0007BAD6 *>(this)->rva0007BAD6();
		bfmeReleaseQueuedDeviceInterfaces();
		reinterpret_cast<Rva0007DA23ResourceManager *>(this)->ReAcquireResources();
		m_needsReset = false;
	}

	if (m_renderTarget.Ptr == 0 || m_depthBuffer == 0)
		return;

	RenderInfoClass rinfo(*m_camera);
	RefCountPtr<FXShader::RenderingMethod> method(new Rva0007DC01ShadowMethod);
	rinfo.Push_Rendering_Method(method);
	WW3D::Set_Rendering_Shadow_Map(true);
	DX8Wrapper::Set_Render_Target(m_renderTarget.Get_Surface_Level().Peek(), m_depthBuffer);
	if (WW3D::Begin_Render(true, true, Vector3(1.0f, 1.0f, 1.0f), 0.0f))
	{
		Rva001182A0(scene, rinfo);
		if (!g_009E1FFC || m_postTarget.Ptr == 0)
			RenderBorder();
		WW3D::End_Render(false);
	}
	if (g_009E1FFC && m_postTarget.Ptr != 0)
	{
		DX8Wrapper::Set_Render_Target(m_postTarget.Get_Surface_Level().Peek(), m_depthBuffer);
		if (WW3D::Begin_Render(false, false, Vector3(0.0f, 0.0f, 0.0f), 0.0f))
		{
			RenderPostProcess();
			RenderBorder();
			WW3D::End_Render(false);
		}
	}
	DX8Wrapper::Set_Render_Target((IDirect3DSurface8 *)0, false);
	WW3D::Set_Rendering_Shadow_Map(false);
	rinfo.Pop_Rendering_Method();
}

// WW3D shadow-map gate read by the render units and written only through
// Set_Rendering_Shadow_Map above. Retail .data starts it at 0.
bool WW3D::IsCurrentlyRenderingShadowMap = false;

// Full native7DA23..7DC01 RET0; WB7EDC60 independently names
// W3DShadowMapManager::ReAcquireResources. Keep the existing neutral
// receiver spelling while using measured owning texture and shader handles.
// This real parent's complete native EH graph also places the parameter-vector
// cleanup at0075F3B7: lea ecx,[ebp-28] and tail jump through the existing
// 0007C632 destructor thunk to0007C5D5. Its compiler-local label is only a
// locator; no synthetic parent or independently callable cleanup is introduced.
bool Rva0007DA23ResourceManager::ReAcquireResources()
{
    if (!TheWritableGlobalData->m_useShadowMap)
        return true;
    if (!target.Referent)
    {
        target = DX8Wrapper::Create_Render_Target(g_shadowMapSettings.v0,
            g_shadowMapSettings.v0, (WW3DFormat)0x72);
        g_shadowMapSettings.v0 = ShadowMin<unsigned int>(
            ((TextureBaseClass *)&target)->rva0013275A(),
            ((TextureBaseClass *)&target)->rva00132784());
    }
    if (!post.Referent && g_009E1FFC)
        post = DX8Wrapper::Create_Render_Target(g_shadowMapSettings.v0,
            g_shadowMapSettings.v0, (WW3DFormat)0x72);
    if (!depth)
    {
        IDirect3DDevice8 *device = DX8Wrapper::D3DDevice;
        device->vtable->createDepth(device, g_shadowMapSettings.v0, g_shadowMapSettings.v0,
            0x4b, 0, 0, 1, &depth, 0);
    }
    _STL::vector<Rva0007BB16Record> parameters;
    ShadowColorParameter color("ColorToWrite", 5);
    color.storage.vector[0] = 1000000.0f;
    color.storage.vector[1] = 0.0f;
    color.storage.vector[2] = 0.0f;
    color.storage.vector[3] = 0.0f;
    parameters.push_back((const Rva0007BB16Record &)color.storage);
    writeShader = (const Rva00072A94 &)Rva00152C47_CreateFXShaderSetup(
        "Shadow.fx", "_WriteColor", &parameters, 4);
    postShader = (const Rva00072A94 &)Rva00152C47_CreateFXShaderSetup(
        "Shadow.fx", "_ShadowMapPostProcess", 0, 4);
    return true;
}
