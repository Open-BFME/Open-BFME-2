// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// dxsdk
// platformsdk
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

#include <d3d9.h>

// BFME 2 renders through Direct3D 9 behind the dx8* names (the vendored SDK's
// IDirect3DDevice9 / IDirect3DBaseTexture9 here): retail dispatches
// SetRenderState +0xE4, SetTexture +0x104, SetTextureStageState +0x10C,
// SetFVF +0x164 and SetVertexShader +0x170, the IDirect3DDevice9 order.
struct IDirect3DBaseTexture8;

struct IDirect3DDevice8;


typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned char UnsignedByte;

#include "../../../../../Libraries/Source/WWVegas/WW3D2/VertexMaterialClass.h"

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../../Libraries/Source/WWVegas/WWMath/AABoxClass.h"

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

#include "../../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"

class BaseHeightMapRenderObjClass
{
public:
	Bool getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, Bool ignoreMaxHeight);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#include "../../../../../GameEngine/Include/Common/GlobalData.h"
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


#include "../../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"

#include "../../../../../GameEngine/Include/Common/BFME2TextureResource.h"
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

// DX8Wrapper::render_state (dx8wrapper.cpp ?render_state@DX8Wrapper@@1URenderStateStruct@@A):
// Zero Hour's RenderStateStruct starts with the shader and the material.
#include "../../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"

class DX8Wrapper
{
public:
	enum ChangedStates { MATERIAL_CHANGED = 1 << 14, SHADER_CHANGED = 1 << 15 };

	static IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }
	static void Apply_Render_State_Changes(void);
	static void Invalidate_Cached_Render_States(void);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned long state, unsigned value);

	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		VertexMaterialClass *vertexMaterial = const_cast<VertexMaterialClass *>(material);
		if (vertexMaterial) vertexMaterial->Add_Ref();
		if (render_state.material) render_state.material->Release_Ref();
		render_state.material = vertexMaterial;
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

	static __forceinline void Set_DX8_Render_State(unsigned long state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetRenderState((D3DRENDERSTATETYPE)state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}

	// This renderer only uses stages 0 and 1. Keep these restricted inline
	// paths here; the callable owners at 661DD and 75412 also handle stage>=16.
	static __declspec(dllimport) __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value)
	{
		if (TextureStageStates[stage][state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Texture_Stage_State_Value_Name(value_name, state, value);
		}
		TextureStageStates[stage][state] = value;
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}

	static __declspec(dllimport) __forceinline void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
	{
		if (Textures[stage] == texture) return;
		if (Textures[stage]) reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->Release();
		Textures[stage] = texture;
		if (Textures[stage]) reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->AddRef();
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
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

#define DX8CALL(x) reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->x; number_of_DX8_calls++;

class W3DVolumetricShadow;

#include "../../../../Include/W3DDevice/GameClient/W3DBufferManagerClass.h"
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
// TheW3DShadowHelperManager is only an alias of the owned global TheW3DProjectedShadowManager (ledger names column); this unit reads the owner through its own view type.
extern class W3DProjectedShadowManager *TheW3DProjectedShadowManager;
#define TheW3DShadowHelperManager (*(W3DVolumetricShadowManagerV2 * *)&TheW3DProjectedShadowManager)

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
// Owned here: the camera frustum renderShadows copies each frame; retail
// .data leaves its 264 bytes zero (VA 0x009EBD00).
FrustumClass shadowCameraFrustum;
extern Real bcX, bcY, bcZ, beX, beY, beZ;
extern Int nShadowVertsInBuf;
extern Int nShadowIndicesInBuf;
extern W3DBufferManager::W3DVertexBuffer *lastActiveVertexBuffer;
// Owned here: reset below after each batch; retail .data starts it at 0
// (VA 0x009EBCF4).
W3DBufferManager::W3DVertexBuffer *lastActiveVertexBuffer = 0;

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
		//turn off textures
		DX8Wrapper::Set_Texture(0,0);
		DX8Wrapper::Set_Texture(1,0);
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
