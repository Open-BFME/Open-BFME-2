// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?drawAndRelease@W3DVolumetricShadowManagerV2@@QAEXH@Z @0x00107865 252B via BFME1 BfmeVolumetricShadowBufferDraw donor
// Evidence: frees vertex/index WriteLocks at +0xc/+0x10 via rowed dtors plus operator delete; 30000 compares at +0x14/+0x18 with div; rowed Record_DX8_Polys plus CurrentCaps+0x90 check plus rowed Set_DX8_Render_State plus D3DDevice Draw slot 82; BFME1 donor BfmeVolumetricShadowBufferDraw.cpp names drawAndRelease.
#include "../../../../../Libraries/Source/WWVegas/WW3D2/VertexBufferClass.h"

#include "../../../../../Libraries/Source/WWVegas/WW3D2/IndexBufferClass.h"

#include <new>

// Zero Hour shader.h's SHADE_CNST field packing (SHIFT_DEPTHCOMPARE 0, DEPTHMASK 3, COLORMASK 4,
// DSTBLEND 5, FOG 8, PRIGRADIENT 10, SECGRADIENT 13, SRCBLEND 14, TEXTURING 16, ALPHATEST 18,
// CULLMODE 19, POSTDETAILCOLORFUNC 20, POSTDETAILALPHAFUNC 24).
#define BFME_SHADE_CNST(depth_compare, depth_mask, color_mask, src_blend, dst_blend, fog, pri_grad, sec_grad, texture, alpha_test, cullmode, post_det_color, post_det_alpha) \
	(	(depth_compare) << 0 | (depth_mask) << 3 | (color_mask) << 4 | (dst_blend) << 5 | (fog) << 8 | \
		(pri_grad) << 10 | (sec_grad) << 13 | (src_blend) << 14 | (texture) << 16 | \
		(alpha_test) << 18 | (cullmode) << 19 | (post_det_color) << 20 | (post_det_alpha) << 24)

#include "../../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"

// The shader drawAndRelease reports to Debug_Statistics: this unit's initialised .data word at
// VA 0x00DB5E98 (retail 0x00101823 = LEQUAL, no depth/colour writes, dst ONE, primary gradient 6,
// post-detail colour 1). It follows this unit's copies of the header-static name tables
// (NONE/HOLD/KILL/SPAWN, NONE/CATAPULT_ROCK/TREBUCHET_ROCK, NONE/FRONT_DESTROYED..).
// Structural name, not a retail spelling.
ShaderClass BfmeShadowVolumeStatsShader(BFME_SHADE_CNST(3, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 1, 0));

namespace Debug_Statistics
{
	void __cdecl Record_DX8_Polys_And_Vertices(int polys, int verts, const ShaderClass &shader);
}

class DX8Caps
{
public:
	char m_pad[0x90];
	unsigned int m_caps;
};

struct IDirect3DDevice8;
class W3DVolumetricShadowManagerV2;

// Zero Hour vertmaterial.h's RefCountClass-derived material: Delete_This in
// vtable slot 0, the reference count at +4.
class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_NODIFFUSE = 0 };
	static VertexMaterialClass *__cdecl Get_Preset(PresetType type);
	virtual void Delete_This();
	__forceinline void Add_Ref() { NumRefs++; }
	__forceinline void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
	int NumRefs;
};

#include "../../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"

class VertexMaterialClass;
class DX8Wrapper
{
	friend class W3DVolumetricShadowManagerV2;
public:
	enum ChangedStates { WORLD_CHANGED = 1 << 0, MATERIAL_CHANGED = 1 << 14, WORLD_IDENTITY = 1 << 18 };
	static void __cdecl Set_DX8_Render_State(unsigned long state, unsigned int value);
	static void __cdecl Set_Shader(const ShaderClass &shader);
	static void __cdecl Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void __cdecl Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void __cdecl Apply_Render_State_Changes();
	static __forceinline void Set_Material(VertexMaterialClass *material)
	{
		if (material) material->Add_Ref();
		// Same global the other Set_Material emitters name (DX8Wrapper::render_state.material), so
		// this COMDAT copy is identical to theirs.
		if (DX8Wrapper::render_state.material) DX8Wrapper::render_state.material->Release_Ref();
		DX8Wrapper::render_state.material = material;
		render_state_changed |= MATERIAL_CHANGED;
	}
	static __forceinline void Set_World_Identity()
	{
		if (render_state_changed & WORLD_IDENTITY)
			return;
		render_state.world[0][0] = 1.0f; render_state.world[0][1] = 0.0f; render_state.world[0][2] = 0.0f; render_state.world[0][3] = 0.0f;
		render_state.world[1][0] = 0.0f; render_state.world[1][1] = 1.0f; render_state.world[1][2] = 0.0f; render_state.world[1][3] = 0.0f;
		render_state.world[2][0] = 0.0f; render_state.world[2][1] = 0.0f; render_state.world[2][2] = 1.0f; render_state.world[2][3] = 0.0f;
		render_state.world[3][0] = 0.0f; render_state.world[3][1] = 0.0f; render_state.world[3][2] = 0.0f; render_state.world[3][3] = 1.0f;
		render_state_changed |= WORLD_CHANGED | WORLD_IDENTITY;
	}
protected:
	// dx8wrapper.cpp defines both protected (CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A and
	// D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A).
	static DX8Caps *CurrentCaps;
	static IDirect3DDevice8 *D3DDevice;
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
};
extern unsigned number_of_DX8_calls;

#include "../../../../Include/W3DDevice/GameClient/W3DShadowManager.h"
extern W3DShadowManager *TheW3DShadowManager;

typedef long (__stdcall *BfmeDeviceSetDword)(IDirect3DDevice8 *, unsigned);
typedef long (__stdcall *BfmeDrawIndexedPrimitive)(IDirect3DDevice8 *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);

class W3DVolumetricShadowManagerV2
{
	VertexBufferClass *m_vertexBuffer;
	IndexBufferClass *m_indexBuffer;
	unsigned int m_unreconstructed008;
	VertexBufferClass::WriteLockClass *m_vertexLock;
	IndexBufferClass::WriteLockClass *m_indexLock;
	unsigned int m_vertexCapacity;
	unsigned int m_indexCapacity;

public:
	void rva001076F6();
	void drawAndRelease(int frontFace);
};

void W3DVolumetricShadowManagerV2::drawAndRelease(int frontFace)
{
	VertexBufferClass::WriteLockClass *vertexLock = m_vertexLock;
	if (vertexLock != 0) {
		vertexLock->~WriteLockClass();
		operator delete(vertexLock);
	}
	IndexBufferClass::WriteLockClass *indexLock = m_indexLock;
	m_vertexLock = 0;
	if (indexLock != 0) {
		indexLock->~WriteLockClass();
		operator delete(indexLock);
	}
	m_indexLock = 0;
	if (m_vertexCapacity == 30000)
		return;
	unsigned int polygonCount = (30000 - m_indexCapacity) / 3;
	int vertexCount = 30000 - m_vertexCapacity;
	Debug_Statistics::Record_DX8_Polys_And_Vertices(polygonCount * 2, vertexCount * 2, BfmeShadowVolumeStatsShader);
	IDirect3DDevice8 *device = DX8Wrapper::D3DDevice;
	if (!(DX8Wrapper::CurrentCaps->m_caps & 0x100)) {
		if (!frontFace) {
			DX8Wrapper::Set_DX8_Render_State(0x16, 2);
			DX8Wrapper::Set_DX8_Render_State(0x37, 7);
		} else {
			DX8Wrapper::Set_DX8_Render_State(0x16, 2);
			DX8Wrapper::Set_DX8_Render_State(0x36, 7);
		}
	}
	(*(BfmeDrawIndexedPrimitive **)device)[82](device, 4, 0, 0, vertexCount, 0, polygonCount);
	if (!(DX8Wrapper::CurrentCaps->m_caps & 0x100)) {
		if (!frontFace) {
			DX8Wrapper::Set_DX8_Render_State(0x16, 3);
			DX8Wrapper::Set_DX8_Render_State(0x37, 8);
		} else {
			DX8Wrapper::Set_DX8_Render_State(0x16, 3);
			DX8Wrapper::Set_DX8_Render_State(0x36, 8);
		}
		(*(BfmeDrawIndexedPrimitive **)device)[82](device, 4, 0, 0, vertexCount, 0, polygonCount);
	}
}


// ?rva001076EE@Rva001076EE@@QAE_NXZ @0x001076EE 8B: the W3DShadowManager
// re-acquire helper (callee of rva0009A254, pinned) re-acquires the projected
// shadow manager it sits on with the same this and always succeeds.
class W3DProjectedShadowManager { public: bool ReAcquireResources(); };
class Rva001076EE { public: bool rva001076EE(); };
bool Rva001076EE::rva001076EE()
{
	((W3DProjectedShadowManager *)this)->ReAcquireResources();
	return true;
}

// 0x001076F6 (367 B): the V2 manager's one-time stencil setup that
// W3DVolumetricShadowManagerV2Render.cpp calls before drawAndRelease. Shape
// carried from Zero Hour's W3DVolumetricShadowManager::renderStencilShadows
// preamble (preset material via Set_Material/REF_PTR_RELEASE, shader, buffers,
// Set_World_Identity, Apply_Render_State_Changes, stencil render states,
// DX8CALL counters); target facts: every callee is a rowed DX8Wrapper/
// VertexMaterialClass body, the globals are dx8wrapper.cpp's render_state
// (+4 material, +0x1EC world), render_state_changed and number_of_DX8_calls,
// and TheW3DShadowManager's +8 mask. Original method name unknown.
void W3DVolumetricShadowManagerV2::rva001076F6()
{
	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_NODIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	if (vmat) vmat->Release_Ref();
	DX8Wrapper::Set_Shader(BfmeShadowVolumeStatsShader);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffer, 0);
	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);
	DX8Wrapper::Set_World_Identity();
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Render_State(0x34, 1);
	DX8Wrapper::Set_DX8_Render_State(0x38, 8);
	unsigned int writeMask = ~TheW3DShadowManager->getStencilShadowMask();
	DX8Wrapper::Set_DX8_Render_State(0x3A, 0xFFFFFFFF);
	DX8Wrapper::Set_DX8_Render_State(0x3B, writeMask);
	(*(BfmeDeviceSetDword **)DX8Wrapper::D3DDevice)[92](DX8Wrapper::D3DDevice, 0);
	number_of_DX8_calls++;
	(*(BfmeDeviceSetDword **)DX8Wrapper::D3DDevice)[89](DX8Wrapper::D3DDevice, 2);
	number_of_DX8_calls++;
}
