// ?Apply_Default_State@DX8Wrapper@@SAXXZ
// partial score=0.9984782609 date=2026-10-06
// Fragment for dx8wrapper.cpp at 6c063da4fc; NOT a standalone TU.
// Replace old Apply_Default_State block through Get_DX8_Render_State_Name comment
// with this fragment; remove the later duplicate Render_State_Value_Name body.
// Mark the existing Texture_Stage_State_Value_Name definition __declspec(noinline).
// Give existing BfmeResetResource::Add_Ref an inline body incrementing the
// unsigned short refcount at byte +4. Reuse existing credited BfmeApplyDevice9.
// Canonical TextureStageStates and render_state.Textures own all cached data.
// No header modifications. Full extent4600, seven byte differences at +0x462.
// Existing source retains its EA GPL and Wine interface attribution notices.
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

struct BfmeDefaultState : DX8Wrapper {
 static __forceinline BfmeApplyDevice9 *Device() { return reinterpret_cast<BfmeApplyDevice9 *>(_Get_D3D_Device8()); }
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
  if (reinterpret_cast<unsigned *>(TextureStageStates)[row+(unsigned)state-D3DTSS_COLORARG1]==value) return;
  if (WW3D::Is_Snapshot_Activated()) {
   StringClass value_name(0,true);
   Get_DX8_Texture_Stage_State_Value_Name(value_name,state,value);
  }
  reinterpret_cast<unsigned *>(TextureStageStates)[row+(unsigned)state-D3DTSS_COLORARG1]=value;
  Device()->SetTextureStageState(stage,state,value);number_of_DX8_calls++;
  DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE();
 }
 static __forceinline void Sampler(unsigned stage,unsigned state,unsigned value) {
  Device()->SetSamplerState(stage,state,value);number_of_DX8_calls++;
  DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE();
 }
 static __forceinline void Texture(unsigned stage,const RefCountPtr<BfmeResetResource> &texture) {
  RefCountPtr<BfmeResetResource>& current = reinterpret_cast<RefCountPtr<BfmeResetResource>&>(render_state.Textures[stage]);
  if (texture.Peek()==*reinterpret_cast<BfmeResetResource *volatile *>(&render_state.Textures[stage])) return;
  current=texture;
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
