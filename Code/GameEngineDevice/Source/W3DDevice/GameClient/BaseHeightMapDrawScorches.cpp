// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// dxsdk
// platformsdk
// Target 0x000693AE..0x000694A3, RET 0 (245 bytes). Zero Hour's
// BaseHeightMapRenderObjClass::drawScorches (BaseHeightMap.cpp) in its BFME2
// form: updateScorches (0x000678BB, pinned) first, then nothing when no
// scorch index is staged; otherwise the alpha shader (with hardware fog when
// the wrapper's fog flag is on), the scorch index/vertex buffers and texture,
// a depth bias of 1, the render-state flush and two direct sampler-0 writes
// (IDirect3DDevice9::SetSamplerState, slot 69: ADDRESSU / ADDRESSV clamp,
// counted as texture-stage changes) before the draw, and the bias back to 0.
// RenderObjClass::Is_Hidden is vtable slot 100 (+0x190); the draw is skipped while hidden.

#include <d3d9.h>

class IndexBufferClass;
class VertexBufferClass;
class TextureBaseClass;

// The device keeps its D3D8 type name but is a Direct3D 9 device.
struct IDirect3DDevice8;

extern unsigned number_of_DX8_calls;

class DX8Wrapper;
#include "../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"

class DX8Wrapper
{
	friend class BaseHeightMapRenderObjClass;
public:
	static void Set_Shader(const ShaderClass &shader);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Apply_Render_State_Changes();
	static void Draw_Triangles(unsigned buffer_type, unsigned start_index, unsigned min_vertex_index, unsigned vertex_count);
protected:
	static bool FogEnable;
	static IDirect3DDevice8 *D3DDevice;
	static unsigned texture_stage_state_changes;
};

struct BFME2TextureRef
{
public:
	TextureBaseClass *p; // +0x00
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);
void bfmeSetProjectionDepthBias(float bias);

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H
// d3d9.h already brought in the Platform SDK persist.h, whose guard hides
// WWSaveLoad's; rendobj.h only needs these names declared.
class PersistFactoryClass;
class ChunkSaveClass;
class ChunkLoadClass;

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// The header keeps the scorch texture holder at +0xD4 as an opaque word.
static __forceinline const BFME2TextureRef &scorchTexture(const BaseHeightMapRenderObjClass *self)
{
	return *reinterpret_cast<const BFME2TextureRef *>(&self->field00D4);
}

void BaseHeightMapRenderObjClass::drawScorches()
{
	updateScorches();
	if (m_curNumScorchIndices == 0)
		return;
	if (Is_Hidden() != 0)
		return;

	ShaderClass shader = ShaderClass::_PresetAlphaShader;
	if (DX8Wrapper::FogEnable)
		shader.Enable_Fog("HardwareFog");
	DX8Wrapper::Set_Shader(shader);
	DX8Wrapper::Set_Index_Buffer(m_indexScorch, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexScorch, 0);
	BFME2Set_Texture(0, scorchTexture(this));
	bfmeSetProjectionDepthBias(1.0f);
	DX8Wrapper::Apply_Render_State_Changes();
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::D3DDevice)->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	++number_of_DX8_calls;
	++DX8Wrapper::texture_stage_state_changes;
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::D3DDevice)->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	++number_of_DX8_calls;
	++DX8Wrapper::texture_stage_state_changes;
	DX8Wrapper::Draw_Triangles(0, m_curNumScorchIndices / 3, 0, m_curNumScorchVertices);
	bfmeSetProjectionDepthBias(0.0f);
}
