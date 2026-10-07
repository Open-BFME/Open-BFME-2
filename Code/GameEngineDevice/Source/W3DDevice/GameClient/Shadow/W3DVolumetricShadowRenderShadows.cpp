// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?renderShadows@W3DVolumetricShadowManager@@QAEXAAVRenderInfoClass@@@Z @0x000F4AB7 4116B.
//
// W3DVolumetricShadowManager::renderShadows: the stencil shadow-volume pass.
// Target evidence: retail 0x000F4AB7..0x000F5ACB (__EH_prolog frame, ret 4),
// sole caller 0x0009A377. It copies the camera frustum (Update_Frustum,
// FrustumClass::operator=), fits the visible box through
// getMaximumVisibleBox, runs the shadow helper manager's own pass
// (0x00107F8B), then sets up W3D/D3D state through the inlined DX8Wrapper
// cache (RenderStates 0x00DED5F8, TextureStageStates 0x00DECA38, Textures
// 0x00DEC4B0, snapshot flag 0x00DEC3FD feeding the out-of-line
// Get_DX8_*_Value_Name callees), queues each enabled shadow through
// W3DVolumetricShadow::Update (0x000F4017) and RenderVolume (0x000F49D0),
// walks the XYZ vertex buffers twice (stencil incr/decr), clears the task
// lists, calls renderStencilShadows (0x000F0842) and invalidates the cache.
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp renderShadows (0x007BFB90,
// game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow), itself the ZH
// W3DVolumetricShadow.cpp body. BFME 2 deltas read from retail: a
// RenderInfoClass& argument replaces forceStencilFill (and its else branch),
// every state goes through DX8Wrapper::Set_DX8_* rather than the raw device,
// colour writes are disabled unconditionally (no caps probe) and restored to
// 0xF, the first getNextVertexBuffer(NULL, ...) of each walk is inlined.
// Names of the BFME 2 callees without a ZH counterpart are descriptive.

typedef unsigned long DWORD;
typedef long HRESULT;
typedef unsigned int UINT;
typedef DWORD D3DRENDERSTATETYPE;
typedef DWORD D3DTEXTURESTAGESTATETYPE;

// BFME 2 renders through Direct3D 9 behind the dx8* names: retail dispatches
// SetRenderState +0xE4, SetTexture +0x104, SetTextureStageState +0x10C,
// SetFVF +0x164 and SetVertexShader +0x170, the IDirect3DDevice9 order.
struct IDirect3DBaseTexture8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual DWORD __stdcall AddRef(void) = 0;
	virtual DWORD __stdcall Release(void) = 0;
};

struct IDirect3DDevice8
{
	virtual HRESULT __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual DWORD __stdcall AddRef(void) = 0;
	virtual DWORD __stdcall Release(void) = 0;
	virtual HRESULT __stdcall TestCooperativeLevel(void) = 0;
	virtual UINT __stdcall GetAvailableTextureMem(void) = 0;
	virtual HRESULT __stdcall EvictManagedResources(void) = 0;
	virtual HRESULT __stdcall GetDirect3D(void **ppD3D9) = 0;
	virtual HRESULT __stdcall GetDeviceCaps(void *pCaps) = 0;
	virtual HRESULT __stdcall GetDisplayMode(UINT iSwapChain, void *pMode) = 0;
	virtual HRESULT __stdcall GetCreationParameters(void *pParameters) = 0;
	virtual HRESULT __stdcall SetCursorProperties(UINT x, UINT y, void *pCursorBitmap) = 0;
	virtual void __stdcall SetCursorPosition(int x, int y, DWORD flags) = 0;
	virtual int __stdcall ShowCursor(int bShow) = 0;
	virtual HRESULT __stdcall CreateAdditionalSwapChain(void *pPresentationParameters, void **pSwapChain) = 0;
	virtual HRESULT __stdcall GetSwapChain(UINT iSwapChain, void **pSwapChain) = 0;
	virtual UINT __stdcall GetNumberOfSwapChains(void) = 0;
	virtual HRESULT __stdcall Reset(void *pPresentationParameters) = 0;
	virtual HRESULT __stdcall Present(const void *pSourceRect, const void *pDestRect, void *hDestWindowOverride, const void *pDirtyRegion) = 0;
	virtual HRESULT __stdcall GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, DWORD type, void **ppBackBuffer) = 0;
	virtual HRESULT __stdcall GetRasterStatus(UINT iSwapChain, void *pRasterStatus) = 0;
	virtual HRESULT __stdcall SetDialogBoxMode(int bEnableDialogs) = 0;
	virtual void __stdcall SetGammaRamp(UINT iSwapChain, DWORD flags, const void *pRamp) = 0;
	virtual void __stdcall GetGammaRamp(UINT iSwapChain, void *pRamp) = 0;
	virtual HRESULT __stdcall CreateTexture(void) = 0;
	virtual HRESULT __stdcall CreateVolumeTexture(void) = 0;
	virtual HRESULT __stdcall CreateCubeTexture(void) = 0;
	virtual HRESULT __stdcall CreateVertexBuffer(void) = 0;
	virtual HRESULT __stdcall CreateIndexBuffer(void) = 0;
	virtual HRESULT __stdcall CreateRenderTarget(void) = 0;
	virtual HRESULT __stdcall CreateDepthStencilSurface(void) = 0;
	virtual HRESULT __stdcall UpdateSurface(void) = 0;
	virtual HRESULT __stdcall UpdateTexture(void) = 0;
	virtual HRESULT __stdcall GetRenderTargetData(void) = 0;
	virtual HRESULT __stdcall GetFrontBufferData(void) = 0;
	virtual HRESULT __stdcall StretchRect(void) = 0;
	virtual HRESULT __stdcall ColorFill(void) = 0;
	virtual HRESULT __stdcall CreateOffscreenPlainSurface(void) = 0;
	virtual HRESULT __stdcall SetRenderTarget(void) = 0;
	virtual HRESULT __stdcall GetRenderTarget(void) = 0;
	virtual HRESULT __stdcall SetDepthStencilSurface(void) = 0;
	virtual HRESULT __stdcall GetDepthStencilSurface(void) = 0;
	virtual HRESULT __stdcall BeginScene(void) = 0;
	virtual HRESULT __stdcall EndScene(void) = 0;
	virtual HRESULT __stdcall Clear(void) = 0;
	virtual HRESULT __stdcall SetTransform(void) = 0;
	virtual HRESULT __stdcall GetTransform(void) = 0;
	virtual HRESULT __stdcall MultiplyTransform(void) = 0;
	virtual HRESULT __stdcall SetViewport(void) = 0;
	virtual HRESULT __stdcall GetViewport(void) = 0;
	virtual HRESULT __stdcall SetMaterial(void) = 0;
	virtual HRESULT __stdcall GetMaterial(void) = 0;
	virtual HRESULT __stdcall SetLight(void) = 0;
	virtual HRESULT __stdcall GetLight(void) = 0;
	virtual HRESULT __stdcall LightEnable(void) = 0;
	virtual HRESULT __stdcall GetLightEnable(void) = 0;
	virtual HRESULT __stdcall SetClipPlane(void) = 0;
	virtual HRESULT __stdcall GetClipPlane(void) = 0;
	virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE state, DWORD value) = 0;
	virtual HRESULT __stdcall GetRenderState(D3DRENDERSTATETYPE state, DWORD *pValue) = 0;
	virtual HRESULT __stdcall CreateStateBlock(void) = 0;
	virtual HRESULT __stdcall BeginStateBlock(void) = 0;
	virtual HRESULT __stdcall EndStateBlock(void) = 0;
	virtual HRESULT __stdcall SetClipStatus(void) = 0;
	virtual HRESULT __stdcall GetClipStatus(void) = 0;
	virtual HRESULT __stdcall GetTexture(DWORD stage, IDirect3DBaseTexture8 **ppTexture) = 0;
	virtual HRESULT __stdcall SetTexture(DWORD stage, IDirect3DBaseTexture8 *pTexture) = 0;
	virtual HRESULT __stdcall GetTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD *pValue) = 0;
	virtual HRESULT __stdcall SetTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value) = 0;
	virtual HRESULT __stdcall GetSamplerState(void) = 0;
	virtual HRESULT __stdcall SetSamplerState(void) = 0;
	virtual HRESULT __stdcall ValidateDevice(void) = 0;
	virtual HRESULT __stdcall SetPaletteEntries(void) = 0;
	virtual HRESULT __stdcall GetPaletteEntries(void) = 0;
	virtual HRESULT __stdcall SetCurrentTexturePalette(void) = 0;
	virtual HRESULT __stdcall GetCurrentTexturePalette(void) = 0;
	virtual HRESULT __stdcall SetScissorRect(void) = 0;
	virtual HRESULT __stdcall GetScissorRect(void) = 0;
	virtual HRESULT __stdcall SetSoftwareVertexProcessing(void) = 0;
	virtual int __stdcall GetSoftwareVertexProcessing(void) = 0;
	virtual HRESULT __stdcall SetNPatchMode(void) = 0;
	virtual float __stdcall GetNPatchMode(void) = 0;
	virtual HRESULT __stdcall DrawPrimitive(void) = 0;
	virtual HRESULT __stdcall DrawIndexedPrimitive(void) = 0;
	virtual HRESULT __stdcall DrawPrimitiveUP(void) = 0;
	virtual HRESULT __stdcall DrawIndexedPrimitiveUP(void) = 0;
	virtual HRESULT __stdcall ProcessVertices(void) = 0;
	virtual HRESULT __stdcall CreateVertexDeclaration(void) = 0;
	virtual HRESULT __stdcall SetVertexDeclaration(void) = 0;
	virtual HRESULT __stdcall GetVertexDeclaration(void) = 0;
	virtual HRESULT __stdcall SetFVF(DWORD fvf) = 0;
	virtual HRESULT __stdcall GetFVF(DWORD *pFVF) = 0;
	virtual HRESULT __stdcall CreateVertexShader(void) = 0;
	virtual HRESULT __stdcall SetVertexShader(void *pShader) = 0;
};

#define TRUE	1
#define FALSE	0

#define D3DRS_ZENABLE			7
#define D3DRS_SHADEMODE			9
#define D3DRS_ZWRITEENABLE		14
#define D3DRS_ALPHATESTENABLE	15
#define D3DRS_CULLMODE			22
#define D3DRS_ZFUNC				23
#define D3DRS_ALPHABLENDENABLE	27
#define D3DRS_FOGENABLE			28
#define D3DRS_STENCILENABLE		52
#define D3DRS_STENCILFAIL		53
#define D3DRS_STENCILZFAIL		54
#define D3DRS_STENCILPASS		55
#define D3DRS_STENCILFUNC		56
#define D3DRS_STENCILREF		57
#define D3DRS_STENCILMASK		58
#define D3DRS_STENCILWRITEMASK	59
#define D3DRS_LIGHTING			137
#define D3DRS_COLORWRITEENABLE	168

#define D3DSHADE_FLAT			1
#define D3DSHADE_GOURAUD		2
#define D3DCULL_CW				2
#define D3DCULL_CCW				3
#define D3DCMP_LESSEQUAL		4
#define D3DCMP_GREATER			5
#define D3DCMP_GREATEREQUAL		7
#define D3DSTENCILOP_KEEP		1
#define D3DSTENCILOP_DECRSAT	5
#define D3DSTENCILOP_INCR		7

#define D3DTSS_COLOROP			1
#define D3DTSS_COLORARG1		2
#define D3DTSS_COLORARG2		3
#define D3DTSS_ALPHAOP			4
#define D3DTSS_TEXCOORDINDEX	11
#define D3DTA_DIFFUSE			0
#define D3DTA_TEXTURE			2
#define D3DTOP_DISABLE			1
#define D3DTOP_SELECTARG2		3

#define D3DFVF_XYZ				0x002

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned char UnsignedByte;

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	~StringClass() { Free_String(); }
private:
	char *m_Buffer;
private:
	void Free_String();
};

class Vector3 { public: Real X, Y, Z; };

class AABoxClass
{
public:
	AABoxClass(void) {}
	Vector3 Center;
	Vector3 Extent;
};

class FrustumClass
{
public:
	FrustumClass &operator=(const FrustumClass &that);
private:
	char m_data[264];
};

class CameraClass
{
public:
	const FrustumClass &Get_Frustum(void) const { Update_Frustum(); return Frustum; }
protected:
	void Update_Frustum(void) const;
	char m_pad[0x100];
	FrustumClass Frustum;
};

class RenderInfoClass
{
public:
	CameraClass &Camera;
};

class BaseHeightMapRenderObjClass
{
public:
	Bool getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, Bool ignoreMaxHeight);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class GlobalData
{
public:
	char m_pad[0x60];
	Bool m_useShadowVolumes;
};
extern GlobalData *TheWritableGlobalData;

class W3DShadowManager
{
public:
	unsigned getStencilShadowMask(void) { return m_stencilShadowMask; }
private:
	void *m_vtable;
	unsigned m_shadowColor;
	unsigned m_stencilShadowMask;
};
extern W3DShadowManager *TheW3DShadowManager;

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType type);
	virtual void Delete_This(void);
	void Add_Ref(void) { ++NumRefs; }
	void Release_Ref(void) { if (--NumRefs == 0) Delete_This(); }
private:
	int NumRefs;
};

class ShaderClass
{
public:
	static ShaderClass _PresetOpaqueShader;
	static bool ShaderDirty;
	unsigned ShaderBits;
};

struct BFME2TextureResource { void Release_Ref(void); };
struct BFME2TextureRef
{
	BFME2TextureResource *Ptr;
	BFME2TextureRef(BFME2TextureResource *p) : Ptr(p) {}
	~BFME2TextureRef() { if (Ptr) Ptr->Release_Ref(); }
};
void BFME2Set_Texture(unsigned int stage, const BFME2TextureRef &texture);

extern unsigned number_of_DX8_calls;

class WW3D
{
public:
	static bool Is_Snapshot_Activated(void) { return SnapshotActivated; }
private:
	static bool SnapshotActivated;
};

class DX8Wrapper
{
public:
	enum ChangedStates { MATERIAL_CHANGED = 1 << 14, SHADER_CHANGED = 1 << 15 };
	struct RenderStateStruct
	{
		ShaderClass shader;
		VertexMaterialClass *material;
	};

	static IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }
	static void Apply_Render_State_Changes(void);
	static void Invalidate_Cached_Render_States(void);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, D3DRENDERSTATETYPE state, unsigned value);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, D3DTEXTURESTAGESTATETYPE state, unsigned value);

	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		VertexMaterialClass *m = const_cast<VertexMaterialClass *>(material);
		if (m) m->Add_Ref();
		if (render_state.material) render_state.material->Release_Ref();
		render_state.material = m;
		render_state_changed |= MATERIAL_CHANGED;
	}

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && shader.ShaderBits == render_state.shader.ShaderBits)
			return;
		render_state.shader = shader;
		render_state_changed |= SHADER_CHANGED;
		StringClass str;
	}

	static __forceinline void Set_Texture(unsigned stage, const BFME2TextureRef &texture) { BFME2Set_Texture(stage, texture); }

	static __forceinline void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		D3DDevice->SetRenderState(state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}

	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value)
	{
		if (TextureStageStates[stage][state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Texture_Stage_State_Value_Name(value_name, state, value);
		}
		TextureStageStates[stage][state] = value;
		D3DDevice->SetTextureStageState(stage, state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}

	static __forceinline void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
	{
		if (Textures[stage] == texture) return;
		if (Textures[stage]) Textures[stage]->Release();
		Textures[stage] = texture;
		if (Textures[stage]) Textures[stage]->AddRef();
		D3DDevice->SetTexture(stage, texture);
		number_of_DX8_calls++;
		texture_changes++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned RenderStates[256];
	static unsigned TextureStageStates[16][32];
	static IDirect3DBaseTexture8 *Textures[16];
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
	static unsigned render_state_changes;
	static unsigned texture_stage_state_changes;
	static unsigned texture_changes;
};

#define DX8CALL(x) DX8Wrapper::_Get_D3D_Device8()->x; number_of_DX8_calls++;

class W3DVolumetricShadow;

class W3DBufferManager
{
public:
	enum VBM_FVF_TYPES { VBM_FVF_XYZ, MAX_FVF = 9 };
	struct W3DRenderTask
	{
		W3DRenderTask *m_nextTask;
	};
	struct W3DVertexBuffer
	{
		char m_pad[0x10];
		W3DVertexBuffer *m_NextVB;
		char m_pad14[4];
		W3DRenderTask *m_renderTaskList;
	};
	static Int getDX8Format(VBM_FVF_TYPES format);
	W3DVertexBuffer *getNextVertexBuffer(W3DVertexBuffer *pVb, VBM_FVF_TYPES type)
	{
		if (pVb == 0) return m_W3DVertexBuffers[type];
		return pVb->m_NextVB;
	}
private:
	char m_pad[0x9000];
	W3DVertexBuffer *m_W3DVertexBuffers[MAX_FVF];
};
extern W3DBufferManager *TheW3DBufferManager;

struct W3DVolumetricShadowRenderTask : public W3DBufferManager::W3DRenderTask
{
	W3DVolumetricShadow *m_parentShadow;
	UnsignedByte m_meshIndex;
	UnsignedByte m_lightIndex;
};

class W3DVolumetricShadow
{
	friend class W3DVolumetricShadowManager;
public:
	void Update(Bool forceUpdate);
protected:
	void RenderVolume(Int meshIndex, Int lightIndex);
	void *m_vtable;
	Bool m_isEnabled;
	Bool m_isInvisibleEnabled;
	char m_pad6[0x62];
	W3DVolumetricShadow *m_next;
};

class W3DVolumetricShadowManagerV2
{
public:
	void renderShadows(RenderInfoClass &rinfo);
};
extern W3DVolumetricShadowManagerV2 *TheW3DShadowHelperManager;

class W3DVolumetricShadowManager
{
public:
	void renderShadows(RenderInfoClass &rinfo);
protected:
	void renderStencilShadows(void);
	W3DVolumetricShadow *m_shadowList;
	W3DVolumetricShadowRenderTask *m_dynamicShadowVolumesToRender;
};

#define SHADOW_DYNAMIC_VOLUME_FVF D3DFVF_XYZ

extern FrustumClass shadowCameraFrustum;
extern Real bcX, bcY, bcZ, beX, beY, beZ;
extern Int nShadowVertsInBuf;
extern Int nShadowIndicesInBuf;
extern W3DBufferManager::W3DVertexBuffer *lastActiveVertexBuffer;

void W3DVolumetricShadowManager::renderShadows(RenderInfoClass &rinfo)
{
	W3DVolumetricShadow *shadow;

	AABoxClass bbox;

	shadowCameraFrustum = rinfo.Camera.Get_Frustum();

	//Get a bounding box around our visible universe.  Bounded by terrain and the sky
	//so much tighter fitting volume than what's actually visible.  This will cull
	//particles falling under the ground.
	TheTerrainRenderObject->getMaximumVisibleBox(shadowCameraFrustum, &bbox, TRUE);

	bcX = bbox.Center.X;
	bcY = bbox.Center.Y;
	bcZ = bbox.Center.Z;
	beX = bbox.Extent.X;
	beY = bbox.Extent.Y;
	beZ = bbox.Extent.Z;

	if (TheW3DShadowHelperManager)
		TheW3DShadowHelperManager->renderShadows(rinfo);

	if (m_shadowList && TheWritableGlobalData->m_useShadowVolumes)
	{
		if (!DX8Wrapper::_Get_D3D_Device8())
			return;	//need device to render anything.

		//According to Nvidia there's a D3D bug that happens if you don't start with a
		//new dynamic VB each frame - so we force a DISCARD by overflowing the counter.
		nShadowIndicesInBuf = 0xffff;
		nShadowVertsInBuf = 0xffff;

		//Set W3D to some known state
		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		if (vmat) { vmat->Release_Ref(); vmat = 0; }

		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
		DX8Wrapper::Set_Texture(0,0);	//turn off textures
		DX8Wrapper::Set_Texture(1,0);	//turn off textures
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		// turn off z writing
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, TRUE);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE, FALSE);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHATESTENABLE, FALSE);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_FOGENABLE, FALSE);

		// setup the TMU to default
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_LIGHTING, FALSE);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_TEXCOORDINDEX, 0);

		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_TEXCOORDINDEX, 1);
		DX8Wrapper::Set_DX8_Texture(0, 0);
		DX8Wrapper::Set_DX8_Texture(1, 0);

		//disable writes to color buffer
		DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE, 0);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, TRUE);

		//Any pixels with stencil already set to 128 contains a potential occluder.  If this pixels also has any of the player
		//color stencil bits also set, it means that it's an occluded player color and we need to NOT render shadows here.  We
		//do this determination by comparing the value in the combined bits against a value containing only a potential occluder.
		//If the value of just the potential occluder bit is >= than the combined bits, then we know none of the player color
		//bits were set and it's okay to render shadow.
		if (TheW3DShadowManager->getStencilShadowMask() == 0x80808080)
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_GREATER);	//in this mode, MSB indicates occluded player pixels.
		else
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);	//in this mode, multiple bits indicate occluded player pixels.
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0x80808080);	//isolate MSB, it's used to indicate pixels containing potential occluders.
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, TheW3DShadowManager->getStencilShadowMask());	//isolate upper bits containing PotentialOccluderBit|PlayerColorBits
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK, 0xffffffff);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

		DX8CALL(SetVertexShader(0));
		DX8CALL(SetFVF(SHADOW_DYNAMIC_VOLUME_FVF));

		DX8Wrapper::Set_DX8_Render_State(D3DRS_CULLMODE, D3DCULL_CW);

		m_dynamicShadowVolumesToRender=0;	//clear list of pending dynamic shadows

		W3DVolumetricShadowRenderTask *shadowDynamicTasksStart,*shadowDynamicTask;

		// step through each of our shadows and render
		shadow = m_shadowList;
		lastActiveVertexBuffer=0;	//reset
		for( ; shadow; shadow = shadow->m_next )
		{
			if (shadow->m_isEnabled && !shadow->m_isInvisibleEnabled)
			{
				//Record last added task
				shadowDynamicTasksStart=m_dynamicShadowVolumesToRender;
				shadow->Update(false);
				shadowDynamicTask=m_dynamicShadowVolumesToRender;
				while (shadowDynamicTask != shadowDynamicTasksStart)
				{	//update() added a dynamic shadow
					//dynamic shadow columes don't need to wait in queue since they
					//all use the same vertex buffer.  Flush them ASAP.
					shadow->RenderVolume(shadowDynamicTask->m_meshIndex,shadowDynamicTask->m_lightIndex);
					//move to next dynamic task
					shadowDynamicTask=(W3DVolumetricShadowRenderTask *)shadowDynamicTask->m_nextTask;
				}
			}
		}  // end for

		// Set vertex format to that used by static shadow volumes
		Int staticFVF = W3DBufferManager::getDX8Format(W3DBufferManager::VBM_FVF_XYZ);
		DX8CALL(SetFVF(staticFVF));

		//Empty queue of static shadow volumes to render.
		W3DBufferManager::W3DVertexBuffer *nextVb;
		W3DVolumetricShadowRenderTask *nextTask;
		for (nextVb=TheW3DBufferManager->getNextVertexBuffer(0,W3DBufferManager::VBM_FVF_XYZ); nextVb != 0; nextVb=TheW3DBufferManager->getNextVertexBuffer(nextVb,W3DBufferManager::VBM_FVF_XYZ))
		{
			nextTask=(W3DVolumetricShadowRenderTask *)nextVb->m_renderTaskList;
			while (nextTask)
			{
				nextTask->m_parentShadow->RenderVolume(nextTask->m_meshIndex,nextTask->m_lightIndex);
				nextTask=(W3DVolumetricShadowRenderTask *)nextTask->m_nextTask;
			}
		}

		// change the stencil op to decrement
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_DECRSAT);

		//
		// invert normals of shadow volumes so we can decrement in the
		// stencil buffer and render
		//
		DX8Wrapper::Set_DX8_Render_State(D3DRS_CULLMODE, D3DCULL_CCW);

		for (nextVb=TheW3DBufferManager->getNextVertexBuffer(0,W3DBufferManager::VBM_FVF_XYZ); nextVb != 0; nextVb=TheW3DBufferManager->getNextVertexBuffer(nextVb,W3DBufferManager::VBM_FVF_XYZ))
		{
			nextTask=(W3DVolumetricShadowRenderTask *)nextVb->m_renderTaskList;
			while (nextTask)
			{
				nextTask->m_parentShadow->RenderVolume(nextTask->m_meshIndex,nextTask->m_lightIndex);
				nextTask=(W3DVolumetricShadowRenderTask *)nextTask->m_nextTask;
			}
		}

		DX8CALL(SetFVF(SHADOW_DYNAMIC_VOLUME_FVF));
		//flush any dynamic shadow volumes
		shadowDynamicTask=m_dynamicShadowVolumesToRender;
		while (shadowDynamicTask)
		{	//dynamic shadow columes don't need to wait in queue since they
			//all use the same vertex buffer.  Flush them ASAP.
			shadowDynamicTask->m_parentShadow->RenderVolume(shadowDynamicTask->m_meshIndex,shadowDynamicTask->m_lightIndex);
			shadowDynamicTask=(W3DVolumetricShadowRenderTask *)shadowDynamicTask->m_nextTask;
		}

		//Reset all render tasks for next frame.
		for (nextVb=TheW3DBufferManager->getNextVertexBuffer(0,W3DBufferManager::VBM_FVF_XYZ); nextVb != 0; nextVb=TheW3DBufferManager->getNextVertexBuffer(nextVb,W3DBufferManager::VBM_FVF_XYZ))
		{
			nextVb->m_renderTaskList=0;
		}

		DX8Wrapper::Set_DX8_Render_State(D3DRS_CULLMODE, D3DCULL_CW);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE, 0x0f);

		//
		// render the big transparent square of shadows in the stencil buffer
		// to the screen
		//
		renderStencilShadows();

		DX8Wrapper::Set_DX8_Render_State(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, FALSE);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_LIGHTING, FALSE);

		DX8Wrapper::Invalidate_Cached_Render_States();
	}
}  // end RenderShadows
