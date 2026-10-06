// flags: region default (reverse/retail_inventory/flag_regions.csv)
// DX8Wrapper::Get_DX8_Render_State_Value_Name (retail 0x00121A10, 651 bytes):
// switch over the D3D render state formatting the value into a StringClass.
// BFME1 dx8wrapper.cpp verbatim: retail's switch map (states 7..195) sends
// LINEPATTERN, EDGEANTIALIAS, SOFTWAREVERTEXPROCESSING, PATCHSEGMENTS and
// ZVISIBLE to the UNKNOWN default, keeps RANGEFOGENABLE in the TRUE/FALSE
// group, and pairs (D3DRENDERSTATETYPE)195 (BFME's D3D9 DEPTHBIAS) with
// STENCILREF for "%d" — all exactly as BFME1 spells it. Static member with
// unsigned long state (KI mangling per BFME1's matched row); every callee
// stays out-of-line via declared-only decls and resolves to its matched row.
// /G7 for the add-of--7 switch bounds check (dx8wrapper_names.cpp rule).

class StringClass
{
public:
	const StringClass &operator=(const char *string);
	const StringClass &operator+=(const char *string);
	int _cdecl Format(const char *format, ...);
};

typedef unsigned long D3DRENDERSTATETYPE;

#define D3DRS_ZENABLE 7
#define D3DRS_FILLMODE 8
#define D3DRS_SHADEMODE 9
#define D3DRS_ZWRITEENABLE 14
#define D3DRS_ALPHATESTENABLE 15
#define D3DRS_LASTPIXEL 16
#define D3DRS_SRCBLEND 19
#define D3DRS_DESTBLEND 20
#define D3DRS_CULLMODE 22
#define D3DRS_ZFUNC 23
#define D3DRS_ALPHAREF 24
#define D3DRS_ALPHAFUNC 25
#define D3DRS_DITHERENABLE 26
#define D3DRS_ALPHABLENDENABLE 27
#define D3DRS_FOGENABLE 28
#define D3DRS_SPECULARENABLE 29
#define D3DRS_FOGCOLOR 34
#define D3DRS_FOGTABLEMODE 35
#define D3DRS_FOGSTART 36
#define D3DRS_FOGEND 37
#define D3DRS_FOGDENSITY 38
#define D3DRS_RANGEFOGENABLE 48
#define D3DRS_STENCILENABLE 52
#define D3DRS_STENCILFAIL 53
#define D3DRS_STENCILZFAIL 54
#define D3DRS_STENCILPASS 55
#define D3DRS_STENCILFUNC 56
#define D3DRS_STENCILREF 57
#define D3DRS_STENCILMASK 58
#define D3DRS_STENCILWRITEMASK 59
#define D3DRS_TEXTUREFACTOR 60
#define D3DRS_WRAP0 128
#define D3DRS_WRAP1 129
#define D3DRS_WRAP2 130
#define D3DRS_WRAP3 131
#define D3DRS_WRAP4 132
#define D3DRS_WRAP5 133
#define D3DRS_WRAP6 134
#define D3DRS_WRAP7 135
#define D3DRS_CLIPPING 136
#define D3DRS_LIGHTING 137
#define D3DRS_AMBIENT 139
#define D3DRS_FOGVERTEXMODE 140
#define D3DRS_COLORVERTEX 141
#define D3DRS_LOCALVIEWER 142
#define D3DRS_NORMALIZENORMALS 143
#define D3DRS_DIFFUSEMATERIALSOURCE 145
#define D3DRS_SPECULARMATERIALSOURCE 146
#define D3DRS_AMBIENTMATERIALSOURCE 147
#define D3DRS_EMISSIVEMATERIALSOURCE 148
#define D3DRS_VERTEXBLEND 151
#define D3DRS_CLIPPLANEENABLE 152
#define D3DRS_POINTSIZE 154
#define D3DRS_POINTSIZE_MIN 155
#define D3DRS_POINTSPRITEENABLE 156
#define D3DRS_POINTSCALEENABLE 157
#define D3DRS_POINTSCALE_A 158
#define D3DRS_POINTSCALE_B 159
#define D3DRS_POINTSCALE_C 160
#define D3DRS_MULTISAMPLEANTIALIAS 161
#define D3DRS_MULTISAMPLEMASK 162
#define D3DRS_PATCHEDGESTYLE 163
#define D3DRS_DEBUGMONITORTOKEN 165
#define D3DRS_POINTSIZE_MAX 166
#define D3DRS_INDEXEDVERTEXBLENDENABLE 167
#define D3DRS_COLORWRITEENABLE 168
#define D3DRS_TWEENFACTOR 170
#define D3DRS_BLENDOP 171

#define D3DWRAP_U 1
#define D3DWRAP_V 2
#define D3DWRAP_W 4

#define D3DCOLORWRITEENABLE_RED 1
#define D3DCOLORWRITEENABLE_GREEN 2
#define D3DCOLORWRITEENABLE_BLUE 4
#define D3DCOLORWRITEENABLE_ALPHA 8

class DX8Wrapper
{
public:
	static const char *Get_DX8_ZBuffer_Type_Name(unsigned value);
	static const char *Get_DX8_Fill_Mode_Name(unsigned value);
	static const char *Get_DX8_Shade_Mode_Name(unsigned value);
	static const char *Get_DX8_Blend_Name(unsigned value);
	static const char *Get_DX8_Cull_Mode_Name(unsigned value);
	static const char *Get_DX8_Cmp_Func_Name(unsigned value);
	static const char *Get_DX8_Fog_Mode_Name(unsigned value);
	static const char *Get_DX8_Stencil_Op_Name(unsigned value);
	static const char *Get_DX8_Material_Source_Name(unsigned value);
	static const char *Get_DX8_Vertex_Blend_Flag_Name(unsigned value);
	static const char *Get_DX8_Patch_Edge_Style_Name(unsigned value);
	static const char *Get_DX8_Debug_Monitor_Token_Name(unsigned value);
	static const char *Get_DX8_Blend_Op_Name(unsigned value);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
};

void DX8Wrapper::Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned value)
{
	switch (state) {
	case D3DRS_ZENABLE:
		name = Get_DX8_ZBuffer_Type_Name(value);
		break;

	case D3DRS_FILLMODE:
		name = Get_DX8_Fill_Mode_Name(value);
		break;

	case D3DRS_SHADEMODE:
		name = Get_DX8_Shade_Mode_Name(value);
		break;

	case D3DRS_FOGCOLOR:
	case D3DRS_ALPHAREF:
	case D3DRS_STENCILMASK:
	case D3DRS_STENCILWRITEMASK:
	case D3DRS_TEXTUREFACTOR:
	case D3DRS_AMBIENT:
	case D3DRS_CLIPPLANEENABLE:
	case D3DRS_MULTISAMPLEMASK:
		name.Format("0x%x", value);
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
	case D3DRS_CLIPPING:
	case D3DRS_LIGHTING:
	case D3DRS_COLORVERTEX:
	case D3DRS_LOCALVIEWER:
	case D3DRS_NORMALIZENORMALS:
	case D3DRS_POINTSPRITEENABLE:
	case D3DRS_POINTSCALEENABLE:
	case D3DRS_MULTISAMPLEANTIALIAS:
	case D3DRS_INDEXEDVERTEXBLENDENABLE:
		name = value ? "TRUE" : "FALSE";
		break;

	case D3DRS_SRCBLEND:
	case D3DRS_DESTBLEND:
		name = Get_DX8_Blend_Name(value);
		break;

	case D3DRS_CULLMODE:
		name = Get_DX8_Cull_Mode_Name(value);
		break;

	case D3DRS_ZFUNC:
	case D3DRS_ALPHAFUNC:
	case D3DRS_STENCILFUNC:
		name = Get_DX8_Cmp_Func_Name(value);
		break;

	case D3DRS_FOGTABLEMODE:
	case D3DRS_FOGVERTEXMODE:
		name = Get_DX8_Fog_Mode_Name(value);
		break;

	case D3DRS_FOGSTART:
	case D3DRS_FOGEND:
	case D3DRS_FOGDENSITY:
	case D3DRS_POINTSIZE:
	case D3DRS_POINTSIZE_MIN:
	case D3DRS_POINTSCALE_A:
	case D3DRS_POINTSCALE_B:
	case D3DRS_POINTSCALE_C:
	case D3DRS_POINTSIZE_MAX:
	case D3DRS_TWEENFACTOR:
		name.Format("%f", *(float *)&value);
		break;

	// BFME's Direct3D 9 headers call this state D3DRS_DEPTHBIAS (195).
	case (D3DRENDERSTATETYPE)195:
	case D3DRS_STENCILREF:
		name.Format("%d", value);
		break;

	case D3DRS_STENCILFAIL:
	case D3DRS_STENCILZFAIL:
	case D3DRS_STENCILPASS:
		name = Get_DX8_Stencil_Op_Name(value);
		break;

	case D3DRS_WRAP0:
	case D3DRS_WRAP1:
	case D3DRS_WRAP2:
	case D3DRS_WRAP3:
	case D3DRS_WRAP4:
	case D3DRS_WRAP5:
	case D3DRS_WRAP6:
	case D3DRS_WRAP7:
		name = "0";
		if (value & D3DWRAP_U) name += "|D3DWRAP_U";
		if (value & D3DWRAP_V) name += "|D3DWRAP_V";
		if (value & D3DWRAP_W) name += "|D3DWRAP_W";
		break;

	case D3DRS_DIFFUSEMATERIALSOURCE:
	case D3DRS_SPECULARMATERIALSOURCE:
	case D3DRS_AMBIENTMATERIALSOURCE:
	case D3DRS_EMISSIVEMATERIALSOURCE:
		name = Get_DX8_Material_Source_Name(value);
		break;

	case D3DRS_VERTEXBLEND:
		name = Get_DX8_Vertex_Blend_Flag_Name(value);
		break;

	case D3DRS_PATCHEDGESTYLE:
		name = Get_DX8_Patch_Edge_Style_Name(value);
		break;

	case D3DRS_DEBUGMONITORTOKEN:
		name = Get_DX8_Debug_Monitor_Token_Name(value);
		break;

	case D3DRS_COLORWRITEENABLE:
		name = "0";
		if (value & D3DCOLORWRITEENABLE_RED) name += "|D3DCOLORWRITEENABLE_RED";
		if (value & D3DCOLORWRITEENABLE_GREEN) name += "|D3DCOLORWRITEENABLE_GREEN";
		if (value & D3DCOLORWRITEENABLE_BLUE) name += "|D3DCOLORWRITEENABLE_BLUE";
		if (value & D3DCOLORWRITEENABLE_ALPHA) name += "|D3DCOLORWRITEENABLE_ALPHA";
		break;
	case D3DRS_BLENDOP:
		name = Get_DX8_Blend_Op_Name(value);
		break;
	default:
		name.Format("UNKNOWN (%d)", value);
		break;
	}
}
