// ?Apply_Default_State@DX8Wrapper@@SAXXZ
// partial score=0.9984782609 date=2026-09-07
// Reconstruction fragment for Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp.
// Baseline original commit9869fa55c34614ab2ae3f0f1800f6719115420e9.
// Use the translation unit's existing first-line compiler flags and includes.
// Replace its entire Apply_Default_State block with this fragment. Remove the
// old Get_DX8_Render_State_Value_Name definition (its forceinline version is
// included below). Mark the existing Get_DX8_Texture_Stage_State_Value_Name
// definition __declspec(noinline). Add this ordinary source member to the
// existing opaque BfmeResetResource view, without claiming further layout:
// void Add_Ref() { ++reinterpret_cast<unsigned short *>(this)[2]; }
// The actual reference ref_ptr.h supplies the nullable ownership semantics.
// Current public depth-bias commit67430ed8 now independently supplies the
// float callee380 bytes; avoid duplicating its Device9 forward declarations.
// Emitted Apply_Default_State is4600 bytes versus complete retail4600.
// Relocation-masked aligned score4593/4600; one unresolved diagnostic StringClass
// initializer scheduling site at body+0x462 exchanges ECX/EDX and CL/DL.
// This is NOT a verified claim; dependencies/literals/EH remain to be audited.
// Explicit cache-row cursor is anchored to COLORARG1; it expresses the retail
// induction variable (offset8, stride128, bound0x808) with named state enums.
// Ordinary i-only source is also semantically correct but compiles4495 bytes.

/*
 * Copyright (C) 2002-2003 Jason Edmeades
 *                         Raphael Junqueira
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

// Device9 method prefix through SetNPatchMode, in Wine/SDK order.
// https://github.com/wine-mirror/wine/blob/master/include/d3d9.h
struct IDirect3D9;
struct D3DCAPS9;
struct IDirect3DSurface9;
struct IDirect3DSwapChain9;
struct IDirect3DTexture9;
struct IDirect3DVolumeTexture9;
struct IDirect3DCubeTexture9;
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct IDirect3DBaseTexture9;
struct D3DVIEWPORT9;
struct D3DMATERIAL9;
struct D3DLIGHT9;
struct IDirect3DStateBlock9;
struct D3DCLIPSTATUS9;
typedef DWORD D3DTEXTUREFILTERTYPE;
typedef DWORD D3DBACKBUFFER_TYPE;
typedef DWORD D3DMULTISAMPLE_TYPE;
typedef DWORD D3DSTATEBLOCKTYPE;
typedef DWORD D3DSAMPLERSTATETYPE;
struct RGNDATA;
struct IDirect3DVertexDeclaration9;
struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct D3DVERTEXELEMENT9;
struct BfmeDefaultDevice9 {
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject)=0;
    virtual ULONG __stdcall AddRef()=0;
    virtual ULONG __stdcall Release()=0;
    virtual HRESULT __stdcall TestCooperativeLevel()=0;
    virtual UINT __stdcall GetAvailableTextureMem()=0;
    virtual HRESULT __stdcall EvictManagedResources()=0;
    virtual HRESULT __stdcall GetDirect3D(IDirect3D9** ppD3D9)=0;
    virtual HRESULT __stdcall GetDeviceCaps(D3DCAPS9* pCaps)=0;
    virtual HRESULT __stdcall GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)=0;
    virtual HRESULT __stdcall GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)=0;
    virtual HRESULT __stdcall SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)=0;
    virtual void __stdcall SetCursorPosition(int X,int Y, DWORD Flags)=0;
    virtual BOOL __stdcall ShowCursor(BOOL bShow)=0;
    virtual HRESULT __stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)=0;
    virtual HRESULT __stdcall GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)=0;
    virtual UINT __stdcall GetNumberOfSwapChains()=0;
    virtual HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)=0;
    virtual HRESULT __stdcall Present(const RECT *src_rect, const RECT *dst_rect, HWND dst_window_override, const RGNDATA *dirty_region)=0;
    virtual HRESULT __stdcall GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)=0;
    virtual HRESULT __stdcall GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)=0;
    virtual HRESULT __stdcall SetDialogBoxMode(BOOL bEnableDialogs)=0;
    virtual void __stdcall SetGammaRamp(UINT swapchain_idx, DWORD flags, const D3DGAMMARAMP *ramp)=0;
    virtual void __stdcall GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)=0;
    virtual HRESULT __stdcall CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall UpdateSurface(IDirect3DSurface9 *src_surface, const RECT *src_rect, IDirect3DSurface9 *dst_surface, const POINT *dst_point)=0;
    virtual HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)=0;
    virtual HRESULT __stdcall GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)=0;
    virtual HRESULT __stdcall GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)=0;
    virtual HRESULT __stdcall StretchRect(IDirect3DSurface9 *src_surface, const RECT *src_rect, IDirect3DSurface9 *dst_surface, const RECT *dst_rect, D3DTEXTUREFILTERTYPE filter)=0;
    virtual HRESULT __stdcall ColorFill(IDirect3DSurface9 *surface, const RECT *rect, D3DCOLOR color)=0;
    virtual HRESULT __stdcall CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)=0;
    virtual HRESULT __stdcall SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)=0;
    virtual HRESULT __stdcall GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)=0;
    virtual HRESULT __stdcall SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)=0;
    virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)=0;
    virtual HRESULT __stdcall BeginScene()=0;
    virtual HRESULT __stdcall EndScene()=0;
    virtual HRESULT __stdcall Clear(DWORD rect_count, const D3DRECT *rects, DWORD flags, D3DCOLOR color, float z, DWORD stencil)=0;
    virtual HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix)=0;
    virtual HRESULT __stdcall GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)=0;
    virtual HRESULT __stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix)=0;
    virtual HRESULT __stdcall SetViewport(const D3DVIEWPORT9 *viewport)=0;
    virtual HRESULT __stdcall GetViewport(D3DVIEWPORT9* pViewport)=0;
    virtual HRESULT __stdcall SetMaterial(const D3DMATERIAL9 *material)=0;
    virtual HRESULT __stdcall GetMaterial(D3DMATERIAL9* pMaterial)=0;
    virtual HRESULT __stdcall SetLight(DWORD index, const D3DLIGHT9 *light)=0;
    virtual HRESULT __stdcall GetLight(DWORD Index, D3DLIGHT9*)=0;
    virtual HRESULT __stdcall LightEnable(DWORD Index, BOOL Enable)=0;
    virtual HRESULT __stdcall GetLightEnable(DWORD Index, BOOL* pEnable)=0;
    virtual HRESULT __stdcall SetClipPlane(DWORD index, const float *plane)=0;
    virtual HRESULT __stdcall GetClipPlane(DWORD Index, float* pPlane)=0;
    virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)=0;
    virtual HRESULT __stdcall GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)=0;
    virtual HRESULT __stdcall CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)=0;
    virtual HRESULT __stdcall BeginStateBlock()=0;
    virtual HRESULT __stdcall EndStateBlock(IDirect3DStateBlock9** ppSB)=0;
    virtual HRESULT __stdcall SetClipStatus(const D3DCLIPSTATUS9 *clip_status)=0;
    virtual HRESULT __stdcall GetClipStatus(D3DCLIPSTATUS9* pClipStatus)=0;
    virtual HRESULT __stdcall GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)=0;
    virtual HRESULT __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)=0;
    virtual HRESULT __stdcall GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)=0;
    virtual HRESULT __stdcall SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)=0;
    virtual HRESULT __stdcall GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)=0;
    virtual HRESULT __stdcall SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)=0;
    virtual HRESULT __stdcall ValidateDevice(DWORD* pNumPasses)=0;
    virtual HRESULT __stdcall SetPaletteEntries(UINT palette_idx, const PALETTEENTRY *entries)=0;
    virtual HRESULT __stdcall GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries)=0;
    virtual HRESULT __stdcall SetCurrentTexturePalette(UINT PaletteNumber)=0;
    virtual HRESULT __stdcall GetCurrentTexturePalette(UINT *PaletteNumber)=0;
    virtual HRESULT __stdcall SetScissorRect(const RECT *rect)=0;
    virtual HRESULT __stdcall GetScissorRect(RECT* pRect)=0;
    virtual HRESULT __stdcall SetSoftwareVertexProcessing(BOOL bSoftware)=0;
    virtual BOOL __stdcall GetSoftwareVertexProcessing()=0;
    virtual HRESULT __stdcall SetNPatchMode(float nSegments)=0;
    virtual float __stdcall GetNPatchMode()=0;
    virtual HRESULT __stdcall DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)=0;
    virtual HRESULT __stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)=0;
    virtual HRESULT __stdcall DrawPrimitiveUP(D3DPRIMITIVETYPE primitive_type, UINT primitive_count, const void *data, UINT stride)=0;
    virtual HRESULT __stdcall DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE primitive_type, UINT min_vertex_idx, UINT vertex_count, UINT primitive_count, const void *index_data, D3DFORMAT index_format, const void *data, UINT stride)=0;
    virtual HRESULT __stdcall ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)=0;
    virtual HRESULT __stdcall CreateVertexDeclaration(const D3DVERTEXELEMENT9 *elements, IDirect3DVertexDeclaration9 **declaration)=0;
    virtual HRESULT __stdcall SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)=0;
    virtual HRESULT __stdcall GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)=0;
    virtual HRESULT __stdcall SetFVF(DWORD FVF)=0;
    virtual HRESULT __stdcall GetFVF(DWORD* pFVF)=0;
    virtual HRESULT __stdcall CreateVertexShader(const DWORD *byte_code, IDirect3DVertexShader9 **shader)=0;
    virtual HRESULT __stdcall SetVertexShader(IDirect3DVertexShader9* pShader)=0;
    virtual HRESULT __stdcall GetVertexShader(IDirect3DVertexShader9** ppShader)=0;
    virtual HRESULT __stdcall SetVertexShaderConstantF(UINT reg_idx, const float *data, UINT count)=0;
    virtual HRESULT __stdcall GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)=0;
    virtual HRESULT __stdcall SetVertexShaderConstantI(UINT reg_idx, const int *data, UINT count)=0;
    virtual HRESULT __stdcall GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)=0;
    virtual HRESULT __stdcall SetVertexShaderConstantB(UINT reg_idx, const BOOL *data, UINT count)=0;
    virtual HRESULT __stdcall GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)=0;
    virtual HRESULT __stdcall SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)=0;
    virtual HRESULT __stdcall GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* OffsetInBytes, UINT* pStride)=0;
    virtual HRESULT __stdcall SetStreamSourceFreq(UINT StreamNumber, UINT Divider)=0;
    virtual HRESULT __stdcall GetStreamSourceFreq(UINT StreamNumber, UINT* Divider)=0;
    virtual HRESULT __stdcall SetIndices(IDirect3DIndexBuffer9* pIndexData)=0;
    virtual HRESULT __stdcall GetIndices(IDirect3DIndexBuffer9** ppIndexData)=0;
    virtual HRESULT __stdcall CreatePixelShader(const DWORD *byte_code, IDirect3DPixelShader9 **shader)=0;
    virtual HRESULT __stdcall SetPixelShader(IDirect3DPixelShader9* pShader)=0;
    virtual HRESULT __stdcall GetPixelShader(IDirect3DPixelShader9** ppShader)=0;
    virtual HRESULT __stdcall SetPixelShaderConstantF(UINT reg_idx, const float *data, UINT count)=0;
};
// ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@ present-unmatched
__forceinline void DX8Wrapper::Get_DX8_Render_State_Value_Name(StringClass& name, D3DRENDERSTATETYPE state, unsigned value)
{
	switch (state) {
	case D3DRS_ZENABLE:
		name=Get_DX8_ZBuffer_Type_Name(value);
		break;

	case D3DRS_FILLMODE:
		name=Get_DX8_Fill_Mode_Name(value);
		break;

	case D3DRS_SHADEMODE:
		name=Get_DX8_Shade_Mode_Name(value);
		break;

	case D3DRS_LINEPATTERN:
	case D3DRS_FOGCOLOR:
	case D3DRS_ALPHAREF:
	case D3DRS_STENCILMASK:
	case D3DRS_STENCILWRITEMASK:
	case D3DRS_TEXTUREFACTOR:
	case D3DRS_AMBIENT:
	case D3DRS_CLIPPLANEENABLE:
	case D3DRS_MULTISAMPLEMASK:
		name.Format("0x%x",value);
		break;

	case D3DRS_ZWRITEENABLE:
	case D3DRS_ALPHATESTENABLE:
	case D3DRS_LASTPIXEL:
	case D3DRS_DITHERENABLE:
	case D3DRS_ALPHABLENDENABLE:
	case D3DRS_FOGENABLE:
	case D3DRS_SPECULARENABLE:
	case D3DRS_STENCILENABLE:
	case D3DRS_RANGEFOGENABLE:
	case D3DRS_EDGEANTIALIAS:
	case D3DRS_CLIPPING:
	case D3DRS_LIGHTING:
	case D3DRS_COLORVERTEX:
	case D3DRS_LOCALVIEWER:
	case D3DRS_NORMALIZENORMALS:
	case D3DRS_SOFTWAREVERTEXPROCESSING:
	case D3DRS_POINTSPRITEENABLE:
	case D3DRS_POINTSCALEENABLE:
	case D3DRS_MULTISAMPLEANTIALIAS:
	case D3DRS_INDEXEDVERTEXBLENDENABLE:
		name=value ? "TRUE" : "FALSE";
		break;

	case D3DRS_SRCBLEND:
	case D3DRS_DESTBLEND:
		name=Get_DX8_Blend_Name(value);
		break;

	case D3DRS_CULLMODE:
		name=Get_DX8_Cull_Mode_Name(value);
		break;

	case D3DRS_ZFUNC:
	case D3DRS_ALPHAFUNC:
	case D3DRS_STENCILFUNC:
		name=Get_DX8_Cmp_Func_Name(value);
		break;

	case D3DRS_ZVISIBLE:
		name="NOTSUPPORTED";
		break;

	case D3DRS_FOGTABLEMODE:
	case D3DRS_FOGVERTEXMODE:
		name=Get_DX8_Fog_Mode_Name(value);
		break;

	case D3DRS_FOGSTART:
	case D3DRS_FOGEND:
	case D3DRS_FOGDENSITY:
	case D3DRS_POINTSIZE:
	case D3DRS_POINTSIZE_MIN:
	case D3DRS_POINTSCALE_A:
	case D3DRS_POINTSCALE_B:
	case D3DRS_POINTSCALE_C:
	case D3DRS_PATCHSEGMENTS:
	case D3DRS_POINTSIZE_MAX:
	case D3DRS_TWEENFACTOR:
		name.Format("%f",*(float*)&value);
		break;

	case D3DRS_ZBIAS:
	case D3DRS_STENCILREF:
		name.Format("%d",value);
		break;

	case D3DRS_STENCILFAIL:
	case D3DRS_STENCILZFAIL:
	case D3DRS_STENCILPASS:
		name=Get_DX8_Stencil_Op_Name(value);
		break;

	case D3DRS_WRAP0:
	case D3DRS_WRAP1:
	case D3DRS_WRAP2:
	case D3DRS_WRAP3:
	case D3DRS_WRAP4:
	case D3DRS_WRAP5:
	case D3DRS_WRAP6:
	case D3DRS_WRAP7:
		name="0";
		if (value&D3DWRAP_U) name+="|D3DWRAP_U";
		if (value&D3DWRAP_V) name+="|D3DWRAP_V";
		if (value&D3DWRAP_W) name+="|D3DWRAP_W";
		break;

	case D3DRS_DIFFUSEMATERIALSOURCE:
	case D3DRS_SPECULARMATERIALSOURCE:
	case D3DRS_AMBIENTMATERIALSOURCE:
	case D3DRS_EMISSIVEMATERIALSOURCE:
		name=Get_DX8_Material_Source_Name(value);
		break;

	case D3DRS_VERTEXBLEND:
		name=Get_DX8_Vertex_Blend_Flag_Name(value);
		break;

	case D3DRS_PATCHEDGESTYLE:
		name=Get_DX8_Patch_Edge_Style_Name(value);
		break;

	case D3DRS_DEBUGMONITORTOKEN:
		name=Get_DX8_Debug_Monitor_Token_Name(value);
		break;

	case D3DRS_COLORWRITEENABLE:
		name="0";
		if (value&D3DCOLORWRITEENABLE_RED) name+="|D3DCOLORWRITEENABLE_RED";
		if (value&D3DCOLORWRITEENABLE_GREEN) name+="|D3DCOLORWRITEENABLE_GREEN";
		if (value&D3DCOLORWRITEENABLE_BLUE) name+="|D3DCOLORWRITEENABLE_BLUE";
		if (value&D3DCOLORWRITEENABLE_ALPHA) name+="|D3DCOLORWRITEENABLE_ALPHA";
		break;
	case D3DRS_BLENDOP:
		name=Get_DX8_Blend_Op_Name(value);
		break;
	default:
		name.Format("UNKNOWN (%d)",value);
		break;
	}
}


#include "ref_ptr.h"
void bfmeSetProjectionDepthBias(float);
extern RefCountPtr<BfmeResetResource> bfmeDefaultTextures[16];

struct BfmeDefaultState : DX8Wrapper {
 static unsigned States[16][32];
 static __forceinline BfmeDefaultDevice9 *Device() { return reinterpret_cast<BfmeDefaultDevice9 *>(_Get_D3D_Device8()); }
 static __forceinline void Render(D3DRENDERSTATETYPE state,unsigned value) {
  if (RenderStates[state]==value) return;
  if (WW3D::Is_Snapshot_Activated()) {
   StringClass value_name(0,true);
   Get_DX8_Render_State_Value_Name(value_name,state,value);
  }
  RenderStates[state]=value;
  Device()->SetRenderState(state,value);number_of_DX8_calls++;
  DX8_RECORD_RENDER_STATE_CHANGE();
 }
 static __forceinline void Stage(unsigned stage,unsigned row,D3DTEXTURESTAGESTATETYPE state,unsigned value) {
  if (row>=16*32+D3DTSS_COLORARG1) { Device()->SetTextureStageState(stage,state,value);number_of_DX8_calls++;return; }
  if (reinterpret_cast<unsigned *>(States)[row+(unsigned)state-D3DTSS_COLORARG1]==value) return;
  if (WW3D::Is_Snapshot_Activated()) {
   StringClass value_name(0,true);
   Get_DX8_Texture_Stage_State_Value_Name(value_name,state,value);
  }
  reinterpret_cast<unsigned *>(States)[row+(unsigned)state-D3DTSS_COLORARG1]=value;
  Device()->SetTextureStageState(stage,state,value);number_of_DX8_calls++;
  DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE();
 }
 static __forceinline void Sampler(unsigned stage,unsigned state,unsigned value) {
  Device()->SetSamplerState(stage,state,value);number_of_DX8_calls++;
  DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE();
 }
 static __forceinline void Texture(unsigned stage,const RefCountPtr<BfmeResetResource> &texture) {
  if (texture==bfmeDefaultTextures[stage]) return;
  bfmeDefaultTextures[stage]=texture;
  render_state_changed|=(0x40u<<stage);
 }
 static __forceinline void Light(unsigned index) {
  if (CurrentDX8LightEnables[index]) {
   DX8_RECORD_LIGHT_CHANGE();CurrentDX8LightEnables[index]=false;
   Device()->LightEnable(index,FALSE);number_of_DX8_calls++;
  }
 }
 static __forceinline void VertexConstants(unsigned reg,const Vector4 *data,unsigned count) {
  if (memcmp(data,Vertex_Shader_Constants+reg,sizeof(Vector4)*count)==0) return;
  memcpy(Vertex_Shader_Constants+reg,data,sizeof(Vector4)*count);
  Device()->SetVertexShaderConstantF(reg,reinterpret_cast<const float *>(data),count);number_of_DX8_calls++;
 }
 static __forceinline void PixelConstants(unsigned reg,const Vector4 *data,unsigned count) {
  if (memcmp(data,Pixel_Shader_Constants+reg,sizeof(Vector4)*count)==0) return;
  memcpy(Pixel_Shader_Constants+reg,data,sizeof(Vector4)*count);
  Device()->SetPixelShaderConstantF(reg,reinterpret_cast<const float *>(data),count);number_of_DX8_calls++;
 }
};
unsigned BfmeDefaultState::States[16][32];
// ?Apply_Default_State@DX8Wrapper@@ present-unmatched
void DX8Wrapper::Apply_Default_State()
{
	SNAPSHOT_SAY(("DX8Wrapper::Apply_Default_State()\n"));
	
	// only set states used in game
	BfmeDefaultState::Render(D3DRS_ZENABLE, TRUE);
//	BfmeDefaultState::Render(D3DRS_FILLMODE, D3DFILL_SOLID);
	BfmeDefaultState::Render(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//BfmeDefaultState::Render(D3DRS_LINEPATTERN, 0);
	BfmeDefaultState::Render(D3DRS_ZWRITEENABLE, TRUE);
	BfmeDefaultState::Render(D3DRS_ALPHATESTENABLE, FALSE);
	//BfmeDefaultState::Render(D3DRS_LASTPIXEL, FALSE);
	BfmeDefaultState::Render(D3DRS_SRCBLEND, D3DBLEND_ONE);
	BfmeDefaultState::Render(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	BfmeDefaultState::Render(D3DRS_CULLMODE, D3DCULL_CW);
	BfmeDefaultState::Render(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	BfmeDefaultState::Render(D3DRS_ALPHAREF, 0);
	BfmeDefaultState::Render(D3DRS_ALPHAFUNC, D3DCMP_LESSEQUAL);
	BfmeDefaultState::Render(D3DRS_DITHERENABLE, FALSE);
	BfmeDefaultState::Render(D3DRS_ALPHABLENDENABLE, FALSE);
	BfmeDefaultState::Render(D3DRS_FOGENABLE, FALSE);
	BfmeDefaultState::Render(D3DRS_SPECULARENABLE, FALSE);
//	BfmeDefaultState::Render(D3DRS_ZVISIBLE, FALSE);
//	BfmeDefaultState::Render(D3DRS_FOGCOLOR, 0);
//	BfmeDefaultState::Render(D3DRS_FOGTABLEMODE, D3DFOG_NONE);
//	BfmeDefaultState::Render(D3DRS_FOGSTART, 0);

//	BfmeDefaultState::Render(D3DRS_FOGEND, WWMath::Float_As_Int(1.0f));
//	BfmeDefaultState::Render(D3DRS_FOGDENSITY, WWMath::Float_As_Int(1.0f));

	//BfmeDefaultState::Render(D3DRS_EDGEANTIALIAS, FALSE);
	bfmeSetProjectionDepthBias(0.0f);
//	BfmeDefaultState::Render(D3DRS_RANGEFOGENABLE, FALSE);








	BfmeDefaultState::Render(D3DRS_TEXTUREFACTOR, 0);
/*	BfmeDefaultState::Render(D3DRS_WRAP0, D3DWRAP_U| D3DWRAP_V);
	BfmeDefaultState::Render(D3DRS_WRAP1, D3DWRAP_U| D3DWRAP_V);
	BfmeDefaultState::Render(D3DRS_WRAP2, D3DWRAP_U| D3DWRAP_V);
	BfmeDefaultState::Render(D3DRS_WRAP3, D3DWRAP_U| D3DWRAP_V);
	BfmeDefaultState::Render(D3DRS_WRAP4, D3DWRAP_U| D3DWRAP_V);
	BfmeDefaultState::Render(D3DRS_WRAP5, D3DWRAP_U| D3DWRAP_V);
	BfmeDefaultState::Render(D3DRS_WRAP6, D3DWRAP_U| D3DWRAP_V);
	BfmeDefaultState::Render(D3DRS_WRAP7, D3DWRAP_U| D3DWRAP_V);*/
	BfmeDefaultState::Render(D3DRS_CLIPPING, TRUE);
	BfmeDefaultState::Render(D3DRS_LIGHTING, FALSE);
	//BfmeDefaultState::Render(D3DRS_AMBIENT, 0);
//	BfmeDefaultState::Render(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	BfmeDefaultState::Render(D3DRS_COLORVERTEX, TRUE);
/*	BfmeDefaultState::Render(D3DRS_LOCALVIEWER, TRUE);
	BfmeDefaultState::Render(D3DRS_NORMALIZENORMALS, FALSE);
	BfmeDefaultState::Render(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	BfmeDefaultState::Render(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2);
	BfmeDefaultState::Render(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	BfmeDefaultState::Render(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
	BfmeDefaultState::Render(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);*/
	//BfmeDefaultState::Render(D3DRS_CLIPPLANEENABLE, 0);
	
	//BfmeDefaultState::Render(D3DRS_POINTSIZE, 0x3f800000);
	//BfmeDefaultState::Render(D3DRS_POINTSIZE_MIN, 0);
	//BfmeDefaultState::Render(D3DRS_POINTSPRITEENABLE, FALSE);
	//BfmeDefaultState::Render(D3DRS_POINTSCALEENABLE, FALSE);
	//BfmeDefaultState::Render(D3DRS_POINTSCALE_A, 0);
	//BfmeDefaultState::Render(D3DRS_POINTSCALE_B, 0);
	//BfmeDefaultState::Render(D3DRS_POINTSCALE_C, 0);
	//BfmeDefaultState::Render(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	//BfmeDefaultState::Render(D3DRS_MULTISAMPLEMASK, 0xffffffff);
	//BfmeDefaultState::Render(D3DRS_PATCHEDGESTYLE, D3DPATCHEDGE_DISCRETE);
	//BfmeDefaultState::Render(D3DRS_PATCHSEGMENTS, 0x3f800000);
	//BfmeDefaultState::Render(D3DRS_DEBUGMONITORTOKEN, D3DDMT_ENABLE);
	//BfmeDefaultState::Render(D3DRS_POINTSIZE_MAX, Float_At_Int(64.0f));
	//BfmeDefaultState::Render(D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE);
	BfmeDefaultState::Render(D3DRS_COLORWRITEENABLE, 0x00000007);
	//BfmeDefaultState::Render(D3DRS_TWEENFACTOR, 0);
	BfmeDefaultState::Render(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//BfmeDefaultState::Render(D3DRS_POSITIONORDER, D3DORDER_CUBIC);
	//BfmeDefaultState::Render(D3DRS_NORMALORDER, D3DORDER_LINEAR);

	// disable TSS stages
	int i;
	unsigned row=D3DTSS_COLORARG1;
 for (i=0; i<reinterpret_cast<BfmeEnumerationCaps *>(CurrentCaps)->MaxTexturesPerPass; i++,row+=32)
	{
		BfmeDefaultState::Stage(i,row, D3DTSS_COLOROP, D3DTOP_DISABLE);
		BfmeDefaultState::Stage(i,row, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		BfmeDefaultState::Stage(i,row, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		BfmeDefaultState::Stage(i,row, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		BfmeDefaultState::Stage(i,row, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		BfmeDefaultState::Stage(i,row, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
		/*BfmeDefaultState::Stage(i,row, D3DTSS_BUMPENVMAT00, 0);
		BfmeDefaultState::Stage(i,row, D3DTSS_BUMPENVMAT01, 0);
		BfmeDefaultState::Stage(i,row, D3DTSS_BUMPENVMAT10, 0);
		BfmeDefaultState::Stage(i,row, D3DTSS_BUMPENVMAT11, 0);
		BfmeDefaultState::Stage(i,row, D3DTSS_BUMPENVLSCALE, 0);
		BfmeDefaultState::Stage(i,row, D3DTSS_BUMPENVLOFFSET, 0);*/

		BfmeDefaultState::Stage(i,row, D3DTSS_TEXCOORDINDEX, i);
		

		BfmeDefaultState::Sampler(i,1,D3DTADDRESS_WRAP);
		BfmeDefaultState::Sampler(i,2,D3DTADDRESS_WRAP);
		BfmeDefaultState::Sampler(i,4,1);
//		BfmeDefaultState::Stage(i,row, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
//		BfmeDefaultState::Stage(i,row, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
//		BfmeDefaultState::Stage(i,row, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
//		BfmeDefaultState::Stage(i,row, D3DTSS_MIPMAPLODBIAS, 0);
//		BfmeDefaultState::Stage(i,row, D3DTSS_MAXMIPLEVEL, 0);
//		BfmeDefaultState::Stage(i,row, D3DTSS_MAXANISOTROPY, 1);
		//BfmeDefaultState::Stage(i,row, D3DTSS_ADDRESSW, D3DTADDRESS_WRAP);
		//BfmeDefaultState::Stage(i,row, D3DTSS_COLORARG0, D3DTA_CURRENT);
		//BfmeDefaultState::Stage(i,row, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
		//BfmeDefaultState::Stage(i,row, D3DTSS_RESULTARG, D3DTA_CURRENT);

		BfmeDefaultState::Stage(i,row, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
		BfmeDefaultState::Texture(i,RefCountPtr<BfmeResetResource>());
	}

//	DX8Wrapper::Set_Material(NULL);
	VertexMaterialClass::Apply_Null();

	for (unsigned index=0;index<4;++index) {
		SNAPSHOT_SAY(("Clearing light %d to NULL\n",index));
		BfmeDefaultState::Light(index);
	}

	// set up simple default TSS 
	Vector4 vconst[MAX_VERTEX_SHADER_CONSTANTS];
	memset(vconst,0,sizeof(Vector4)*MAX_VERTEX_SHADER_CONSTANTS);
	BfmeDefaultState::VertexConstants(0, vconst, MAX_VERTEX_SHADER_CONSTANTS);

	Vector4 pconst[MAX_PIXEL_SHADER_CONSTANTS];
	memset(pconst,0,sizeof(Vector4)*MAX_PIXEL_SHADER_CONSTANTS);
	BfmeDefaultState::PixelConstants(0, pconst, MAX_PIXEL_SHADER_CONSTANTS);

	BfmeDefaultState::Device()->SetVertexShader(NULL);number_of_DX8_calls++;
 BfmeDefaultState::Device()->SetFVF(DX8_FVF_XYZNDUV2);number_of_DX8_calls++;
	BfmeDefaultState::Device()->SetPixelShader(NULL);number_of_DX8_calls++;

	ShaderClass::Invalidate();
}

