// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// dxsdk
// platformsdk
// ?RenderMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z @0x000F200A 505B.
//
// W3DVolumetricShadow::RenderMeshVolume: draws one static shadow volume
// from its vertex/index buffer slots. Target evidence: retail
// 0x000F200A..0x000F2203 (plain frame, ret 0xC), called from RenderVolume
// (0x000F49D0). The stencil sub-mask ((this+0x34 >> 7) & 7) << 4 is
// replicated into D3DRS_STENCILMASK/STENCILREF through the out-of-line
// DX8Wrapper::Set_DX8_Render_State (0x0006615F) and restored afterwards
// from TheW3DShadowManager's mask; the volume's active counts sit at
// Geometry+0x10/+0x14, the slots at this+0x300/+0x580 with 160 meshes per
// light, the last bound buffer at 0x00DEBCF4, and the draw is gated on the
// triangle-draw flag 0x00DB5FCD and counted through
// Debug_Statistics::Record_DX8_Polys_And_Vertices (0x00129540) with
// ShaderClass::_PresetOpaqueShader. Device calls are the IDirect3DDevice9
// slots SetTransform (+0xB0), SetStreamSource (+0x190), SetIndices
// (+0x1A0) and DrawIndexedPrimitive (+0x148).
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp RenderMeshVolume (the ZH
// body plus the BFME stencil sub-mask). BFME 2 deltas read from retail:
// render states go through DX8Wrapper rather than the raw device. The last
// bound buffer stays the ZH file-static: retail keeps the slot chain live
// across its store, which only a non-escaping static allows.

#include <d3d9.h>
typedef float Real;
typedef int Int;


struct IDirect3DDevice8;
struct IDirect3DVertexBuffer8;
struct IDirect3DIndexBuffer8;
// The device and buffers keep their D3D8 type names (the decorations of
// DX8Wrapper::D3DDevice, the shadow buffers and the WW3D buffer classes) but
// are Direct3D 9 objects: SetTransform 44, DrawIndexedPrimitive 82,
// SetStreamSource 100, SetIndices 104; buffer Lock / Unlock 11 / 12.
#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix4Data.h"
typedef Matrix4 Matrix4x4;

#include "../../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"

namespace Debug_Statistics
{
	void Record_DX8_Polys_And_Vertices(int polys, int vertices, const ShaderClass &shader);
}

#include "../../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

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

class FVFInfoClass
{
public:
	__declspec(dllimport) __forceinline unsigned Get_FVF_Size(void) const { return fvf_size; }
private:
	char m_pad[0xc];
	unsigned fvf_size;
};

class DX8VertexBufferClass
{
public:
	const FVFInfoClass &FVF_Info(void) const { return *fvf_info; }
	__declspec(dllimport) __forceinline IDirect3DVertexBuffer8 *Get_DX8_Vertex_Buffer(void) { return VertexBuffer; }
private:
	char m_pad[0x14];
	FVFInfoClass *fvf_info;
	char m_pad18[4];
	IDirect3DVertexBuffer8 *VertexBuffer;
};

#include "../../../../../Libraries/Source/WWVegas/WW3D2/DX8IndexBufferClass.h"

#include "../../../../Include/W3DDevice/GameClient/W3DBufferManagerClass.h"

class Geometry
{
public:
	Int GetNumActivePolygon(void) const { return m_numActivePolygon; }
	Int GetNumActiveVertex(void) const { return m_numActiveVertex; }
private:
	char m_pad[0x10];
	Int m_numActivePolygon;
	Int m_numActiveVertex;
};

#define MAX_SHADOW_LIGHTS		1
#define MAX_SHADOW_CASTER_MESHES	160

class W3DVolumetricShadow
{
protected:
	void RenderMeshVolume(Int meshIndex, Int lightIndex, const Matrix3D *meshXform);
	void *m_vtable;
	char m_pad4[0x30];
	Int m_stencilFlags;
	char m_pad38[0x48];
	Geometry *m_shadowVolume[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DVertexBufferSlot *m_shadowVolumeVB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DIndexBufferSlot *m_shadowVolumeIB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
};

static IDirect3DVertexBuffer8 *lastActiveVertexBuffer = 0;

void W3DVolumetricShadow::RenderMeshVolume(Int meshIndex, Int lightIndex, const Matrix3D *meshXform)
{
	IDirect3DDevice9 *m_pDev = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
	if (!m_pDev)
		return;

	Int stencilIndex = (m_stencilFlags >> 7) & 7;
	if (stencilIndex)
	{
		unsigned stencilRef = stencilIndex << 4;
		unsigned stencilMask = stencilRef;
		stencilMask = (stencilMask << 8) | stencilRef;
		stencilMask = (stencilMask << 8) | stencilRef;
		stencilMask = (stencilMask << 8) | TheW3DShadowManager->getStencilShadowMask();
		stencilMask |= stencilRef;
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, stencilMask);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, stencilRef);
	}

	Geometry *geometry = m_shadowVolume[lightIndex][meshIndex];
	Int numVerts = geometry->GetNumActiveVertex();
	Int numPolys = geometry->GetNumActivePolygon();
	if (!numVerts || !numPolys)
		return;

	Matrix4x4 mWorld(*meshXform);
	m_pDev->SetTransform(D3DTS_WORLD, (D3DMATRIX *)&mWorld.Transpose());

	W3DBufferManager::W3DVertexBufferSlot *vbSlot = m_shadowVolumeVB[lightIndex][meshIndex];
	if (!vbSlot)
		return;
	if (vbSlot->m_VB->m_DX8VertexBuffer->Get_DX8_Vertex_Buffer() != lastActiveVertexBuffer)
	{
		lastActiveVertexBuffer = vbSlot->m_VB->m_DX8VertexBuffer->Get_DX8_Vertex_Buffer();
		m_pDev->SetStreamSource(0, reinterpret_cast<IDirect3DVertexBuffer9 *>(lastActiveVertexBuffer), 0,
			vbSlot->m_VB->m_DX8VertexBuffer->FVF_Info().Get_FVF_Size());
	}

	W3DBufferManager::W3DIndexBufferSlot *ibSlot = m_shadowVolumeIB[lightIndex][meshIndex];
	if (!ibSlot)
		return;
	m_pDev->SetIndices(reinterpret_cast<IDirect3DIndexBuffer9 *>(ibSlot->m_IB->m_DX8IndexBuffer->Get_DX8_Index_Buffer()));

	if (DX8Wrapper::_Is_Triangle_Draw_Enabled())
	{
		Debug_Statistics::Record_DX8_Polys_And_Vertices(numPolys, numVerts, ShaderClass::_PresetOpaqueShader);
		m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, vbSlot->m_start, 0, numVerts, ibSlot->m_start, numPolys);
	}

	if (stencilIndex)
	{
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, TheW3DShadowManager->getStencilShadowMask());
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 0x80808080);
	}
}
