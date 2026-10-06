// flags: region default (reverse/retail_inventory/flag_regions.csv)
// The DX8Wrapper enum-to-string helpers from WW3D2/dx8wrapper.cpp, taken
// verbatim from the reference tree. Each is a switch over a D3D enum
// returning a string literal, so the only thing that has to come out right
// is the shape of the switch.
//
// /G7 is what makes them match. It tunes for the Pentium 4, where `dec`
// carries a partial-flag stall, so the bounds check ahead of each switch
// normalises the value with an add of -1 instead. Without it every one of
// these bodies diverges at that single instruction, and the sizes then
// shift far enough that nothing downstream lines up either.
//
// The D3D constants are spelled as their numeric values because this tree
// carries no d3d8.h; the values come from the DX8.1 SDK header in the
// toolchain and are listed here so the switch labels stay readable.

#define D3DBLENDOP_ADD 1
#define D3DBLENDOP_MAX 5
#define D3DBLENDOP_MIN 4
#define D3DBLENDOP_REVSUBTRACT 3
#define D3DBLENDOP_SUBTRACT 2
#define D3DBLEND_BOTHINVSRCALPHA 13
#define D3DBLEND_BOTHSRCALPHA 12
#define D3DBLEND_DESTALPHA 7
#define D3DBLEND_DESTCOLOR 9
#define D3DBLEND_INVDESTALPHA 8
#define D3DBLEND_INVDESTCOLOR 10
#define D3DBLEND_INVSRCALPHA 6
#define D3DBLEND_INVSRCCOLOR 4
#define D3DBLEND_ONE 2
#define D3DBLEND_SRCALPHA 5
#define D3DBLEND_SRCALPHASAT 11
#define D3DBLEND_SRCCOLOR 3
#define D3DBLEND_ZERO 1
#define D3DCMP_ALWAYS 8
#define D3DCMP_EQUAL 3
#define D3DCMP_GREATER 5
#define D3DCMP_GREATEREQUAL 7
#define D3DCMP_LESS 2
#define D3DCMP_LESSEQUAL 4
#define D3DCMP_NEVER 1
#define D3DCMP_NOTEQUAL 6
#define D3DCULL_CCW 3
#define D3DCULL_CW 2
#define D3DCULL_NONE 1
#define D3DDMT_DISABLE 1
#define D3DDMT_ENABLE 0
#define D3DFILL_POINT 1
#define D3DFILL_SOLID 3
#define D3DFILL_WIREFRAME 2
#define D3DFOG_EXP 1
#define D3DFOG_EXP2 2
#define D3DFOG_LINEAR 3
#define D3DFOG_NONE 0
#define D3DMCS_COLOR1 1
#define D3DMCS_COLOR2 2
#define D3DMCS_MATERIAL 0
#define D3DPATCHEDGE_CONTINUOUS 1
#define D3DPATCHEDGE_DISCRETE 0
#define D3DRS_ALPHAFUNC 25
#define D3DRS_ALPHABLENDENABLE 27
#define D3DRS_ALPHAREF 24
#define D3DRS_ALPHATESTENABLE 15
#define D3DRS_AMBIENT 139
#define D3DRS_AMBIENTMATERIALSOURCE 147
#define D3DRS_BLENDOP 171
#define D3DRS_CLIPPLANEENABLE 152
#define D3DRS_CLIPPING 136
#define D3DRS_COLORVERTEX 141
#define D3DRS_COLORWRITEENABLE 168
#define D3DRS_CULLMODE 22
#define D3DRS_DEBUGMONITORTOKEN 165
#define D3DRS_DESTBLEND 20
#define D3DRS_DIFFUSEMATERIALSOURCE 145
#define D3DRS_DITHERENABLE 26
#define D3DRS_EMISSIVEMATERIALSOURCE 148
#define D3DRS_FILLMODE 8
#define D3DRS_FOGCOLOR 34
#define D3DRS_FOGDENSITY 38
#define D3DRS_FOGENABLE 28
#define D3DRS_FOGEND 37
#define D3DRS_FOGSTART 36
#define D3DRS_FOGTABLEMODE 35
#define D3DRS_FOGVERTEXMODE 140
#define D3DRS_INDEXEDVERTEXBLENDENABLE 167
#define D3DRS_LASTPIXEL 16
#define D3DRS_LIGHTING 137
#define D3DRS_LOCALVIEWER 142
#define D3DRS_MULTISAMPLEANTIALIAS 161
#define D3DRS_MULTISAMPLEMASK 162
#define D3DRS_NORMALIZENORMALS 143
#define D3DRS_PATCHEDGESTYLE 163
#define D3DRS_POINTSCALE_A 158
#define D3DRS_POINTSCALE_B 159
#define D3DRS_POINTSCALE_C 160
#define D3DRS_POINTSCALEENABLE 157
#define D3DRS_POINTSIZE 154
#define D3DRS_POINTSIZE_MAX 166
#define D3DRS_POINTSIZE_MIN 155
#define D3DRS_POINTSPRITEENABLE 156
#define D3DRS_RANGEFOGENABLE 48
#define D3DRS_SHADEMODE 9
#define D3DRS_SPECULARENABLE 29
#define D3DRS_SPECULARMATERIALSOURCE 146
#define D3DRS_SRCBLEND 19
#define D3DRS_STENCILENABLE 52
#define D3DRS_STENCILFAIL 53
#define D3DRS_STENCILFUNC 56
#define D3DRS_STENCILMASK 58
#define D3DRS_STENCILPASS 55
#define D3DRS_STENCILREF 57
#define D3DRS_STENCILWRITEMASK 59
#define D3DRS_STENCILZFAIL 54
#define D3DRS_TEXTUREFACTOR 60
#define D3DRS_TWEENFACTOR 170
#define D3DRS_VERTEXBLEND 151
#define D3DRS_WRAP0 128
#define D3DRS_WRAP1 129
#define D3DRS_WRAP2 130
#define D3DRS_WRAP3 131
#define D3DRS_WRAP4 132
#define D3DRS_WRAP5 133
#define D3DRS_WRAP6 134
#define D3DRS_WRAP7 135
#define D3DRS_ZENABLE 7
#define D3DRS_ZFUNC 23
#define D3DRS_ZWRITEENABLE 14
#define D3DSHADE_FLAT 1
#define D3DSHADE_GOURAUD 2
#define D3DSHADE_PHONG 3
#define D3DSTENCILOP_DECR 8
#define D3DSTENCILOP_DECRSAT 5
#define D3DSTENCILOP_INCR 7
#define D3DSTENCILOP_INCRSAT 4
#define D3DSTENCILOP_INVERT 6
#define D3DSTENCILOP_KEEP 1
#define D3DSTENCILOP_REPLACE 3
#define D3DSTENCILOP_ZERO 2
#define D3DTADDRESS_BORDER 4
#define D3DTADDRESS_CLAMP 3
#define D3DTADDRESS_MIRROR 2
#define D3DTADDRESS_MIRRORONCE 5
#define D3DTADDRESS_WRAP 1
#define D3DTA_ALPHAREPLICATE 0x00000020
#define D3DTA_COMPLEMENT 0x00000010
#define D3DTA_CURRENT 0x00000001
#define D3DTA_DIFFUSE 0x00000000
#define D3DTA_SELECTMASK 0x0000000f
#define D3DTA_SPECULAR 0x00000004
#define D3DTA_TEMP 0x00000005
#define D3DTA_TEXTURE 0x00000002
#define D3DTA_TFACTOR 0x00000003
#define D3DTEXF_ANISOTROPIC 3
#define D3DTEXF_LINEAR 2
#define D3DTEXF_NONE 0
#define D3DTEXF_POINT 1
#define D3DTOP_ADD 7
#define D3DTOP_ADDSIGNED 8
#define D3DTOP_ADDSIGNED2X 9
#define D3DTOP_ADDSMOOTH 11
#define D3DTOP_BLENDCURRENTALPHA 16
#define D3DTOP_BLENDDIFFUSEALPHA 12
#define D3DTOP_BLENDFACTORALPHA 14
#define D3DTOP_BLENDTEXTUREALPHA 13
#define D3DTOP_BLENDTEXTUREALPHAPM 15
#define D3DTOP_BUMPENVMAP 22
#define D3DTOP_BUMPENVMAPLUMINANCE 23
#define D3DTOP_DISABLE 1
#define D3DTOP_DOTPRODUCT3 24
#define D3DTOP_LERP 26
#define D3DTOP_MODULATE 4
#define D3DTOP_MODULATE2X 5
#define D3DTOP_MODULATE4X 6
#define D3DTOP_MODULATEALPHA_ADDCOLOR 18
#define D3DTOP_MODULATECOLOR_ADDALPHA 19
#define D3DTOP_MODULATEINVALPHA_ADDCOLOR 20
#define D3DTOP_MODULATEINVCOLOR_ADDALPHA 21
#define D3DTOP_MULTIPLYADD 25
#define D3DTOP_PREMODULATE 17
#define D3DTOP_SELECTARG1 2
#define D3DTOP_SELECTARG2 3
#define D3DTOP_SUBTRACT 10
#define D3DTSS_ALPHAARG0 27
#define D3DTSS_ALPHAARG1 5
#define D3DTSS_ALPHAARG2 6
#define D3DTSS_ALPHAOP 4
#define D3DTSS_BUMPENVMAT00 7
#define D3DTSS_BUMPENVMAT01 8
#define D3DTSS_BUMPENVMAT10 9
#define D3DTSS_BUMPENVMAT11 10
#define D3DTSS_BUMPENVLSCALE 22
#define D3DTSS_BUMPENVLOFFSET 23
#define D3DTSS_COLORARG0 26
#define D3DTSS_COLORARG1 2
#define D3DTSS_COLORARG2 3
#define D3DTSS_COLOROP 1
#define D3DTSS_RESULTARG 28
#define D3DTSS_TEXCOORDINDEX 11
#define D3DTSS_TEXTURETRANSFORMFLAGS 24
#define D3DTTFF_COUNT1 1
#define D3DTTFF_COUNT2 2
#define D3DTTFF_COUNT3 3
#define D3DTTFF_COUNT4 4
#define D3DTTFF_DISABLE 0
#define D3DTTFF_PROJECTED 256
#define D3DVBF_0WEIGHTS 256
#define D3DVBF_1WEIGHTS 1
#define D3DVBF_2WEIGHTS 2
#define D3DVBF_3WEIGHTS 3
#define D3DVBF_DISABLE 0
#define D3DVBF_TWEENING 255
#define D3DZB_FALSE 0
#define D3DZB_TRUE 1
#define D3DZB_USEW 2

// BFME's headers type render states as unsigned long (KI mangling on the
// landed Value_Name rows); the 195 arm below keeps BFME1's honest
// (D3DRENDERSTATETYPE)195 DEPTHBIAS spelling through this alias.
typedef unsigned long D3DRENDERSTATETYPE;

class DX8Wrapper
{
public:
    static const char *Get_DX8_Blend_Name(unsigned value);
    static const char *Get_DX8_Blend_Op_Name(unsigned value);
    static const char *Get_DX8_Cmp_Func_Name(unsigned value);
    static const char *Get_DX8_Cull_Mode_Name(unsigned value);
    static const char *Get_DX8_Debug_Monitor_Token_Name(unsigned value);
    static const char *Get_DX8_Fill_Mode_Name(unsigned value);
    static const char *Get_DX8_Fog_Mode_Name(unsigned value);
    static const char *Get_DX8_Material_Source_Name(unsigned value);
    static const char *Get_DX8_Patch_Edge_Style_Name(unsigned value);
    static const char *Get_DX8_Render_State_Name(unsigned long state);
    static const char *Get_DX8_Shade_Mode_Name(unsigned value);
    static const char *Get_DX8_Stencil_Op_Name(unsigned value);
    static const char *Get_DX8_Texture_Address_Name(unsigned value);
    static const char *Get_DX8_Texture_Arg_Name(unsigned value);
    static const char *Get_DX8_Texture_Filter_Name(unsigned value);
    static const char *Get_DX8_Texture_Op_Name(unsigned value);
    static const char *Get_DX8_Texture_Stage_State_Name(unsigned long state);
    static const char *Get_DX8_Texture_Transform_Flag_Name(unsigned value);
    static const char *Get_DX8_Vertex_Blend_Flag_Name(unsigned value);
    static const char *Get_DX8_ZBuffer_Type_Name(unsigned value);
};

const char* DX8Wrapper::Get_DX8_Texture_Op_Name(unsigned value)
{
	switch (value) {
	case D3DTOP_DISABLE                      : return "D3DTOP_DISABLE";
	case D3DTOP_SELECTARG1                   : return "D3DTOP_SELECTARG1";
	case D3DTOP_SELECTARG2                   : return "D3DTOP_SELECTARG2";
	case D3DTOP_MODULATE                     : return "D3DTOP_MODULATE";
	case D3DTOP_MODULATE2X                   : return "D3DTOP_MODULATE2X";
	case D3DTOP_MODULATE4X                   : return "D3DTOP_MODULATE4X";
	case D3DTOP_ADD                          : return "D3DTOP_ADD";
	case D3DTOP_ADDSIGNED                    : return "D3DTOP_ADDSIGNED";
	case D3DTOP_ADDSIGNED2X                  : return "D3DTOP_ADDSIGNED2X";
	case D3DTOP_SUBTRACT                     : return "D3DTOP_SUBTRACT";
	case D3DTOP_ADDSMOOTH                    : return "D3DTOP_ADDSMOOTH";
	case D3DTOP_BLENDDIFFUSEALPHA            : return "D3DTOP_BLENDDIFFUSEALPHA";
	case D3DTOP_BLENDTEXTUREALPHA            : return "D3DTOP_BLENDTEXTUREALPHA";
	case D3DTOP_BLENDFACTORALPHA             : return "D3DTOP_BLENDFACTORALPHA";
	case D3DTOP_BLENDTEXTUREALPHAPM          : return "D3DTOP_BLENDTEXTUREALPHAPM";
	case D3DTOP_BLENDCURRENTALPHA            : return "D3DTOP_BLENDCURRENTALPHA";
	case D3DTOP_PREMODULATE                  : return "D3DTOP_PREMODULATE";
	case D3DTOP_MODULATEALPHA_ADDCOLOR       : return "D3DTOP_MODULATEALPHA_ADDCOLOR";
	case D3DTOP_MODULATECOLOR_ADDALPHA       : return "D3DTOP_MODULATECOLOR_ADDALPHA";
	case D3DTOP_MODULATEINVALPHA_ADDCOLOR    : return "D3DTOP_MODULATEINVALPHA_ADDCOLOR";
	case D3DTOP_MODULATEINVCOLOR_ADDALPHA    : return "D3DTOP_MODULATEINVCOLOR_ADDALPHA";
	case D3DTOP_BUMPENVMAP                   : return "D3DTOP_BUMPENVMAP";
	case D3DTOP_BUMPENVMAPLUMINANCE          : return "D3DTOP_BUMPENVMAPLUMINANCE";
	case D3DTOP_DOTPRODUCT3                  : return "D3DTOP_DOTPRODUCT3";
	case D3DTOP_MULTIPLYADD                  : return "D3DTOP_MULTIPLYADD";
	case D3DTOP_LERP                         : return "D3DTOP_LERP";
	default										     : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Texture_Arg_Name(unsigned value)
{
	switch (value) {
	case D3DTA_CURRENT			: return "D3DTA_CURRENT";
	case D3DTA_DIFFUSE			: return "D3DTA_DIFFUSE";
	case D3DTA_SELECTMASK		: return "D3DTA_SELECTMASK";
	case D3DTA_SPECULAR			: return "D3DTA_SPECULAR";
	case D3DTA_TEMP				: return "D3DTA_TEMP";
	case D3DTA_TEXTURE			: return "D3DTA_TEXTURE";
	case D3DTA_TFACTOR			: return "D3DTA_TFACTOR";
	case D3DTA_ALPHAREPLICATE	: return "D3DTA_ALPHAREPLICATE";
	case D3DTA_COMPLEMENT		: return "D3DTA_COMPLEMENT";
	default					      : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Texture_Filter_Name(unsigned value)
{
	switch (value) {
	case D3DTEXF_NONE				: return "D3DTEXF_NONE";
	case D3DTEXF_POINT			: return "D3DTEXF_POINT";
	case D3DTEXF_LINEAR			: return "D3DTEXF_LINEAR";
	case D3DTEXF_ANISOTROPIC	: return "D3DTEXF_ANISOTROPIC";
	default					      : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Texture_Address_Name(unsigned value)
{
	switch (value) {
	case D3DTADDRESS_WRAP		: return "D3DTADDRESS_WRAP";
	case D3DTADDRESS_MIRROR		: return "D3DTADDRESS_MIRROR";
	case D3DTADDRESS_CLAMP		: return "D3DTADDRESS_CLAMP";
	case D3DTADDRESS_BORDER		: return "D3DTADDRESS_BORDER";
	case D3DTADDRESS_MIRRORONCE: return "D3DTADDRESS_MIRRORONCE";
	default					      : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Texture_Transform_Flag_Name(unsigned value)
{
	switch (value) {
	case D3DTTFF_DISABLE			: return "D3DTTFF_DISABLE";
	case D3DTTFF_COUNT1			: return "D3DTTFF_COUNT1";
	case D3DTTFF_COUNT2			: return "D3DTTFF_COUNT2";
	case D3DTTFF_COUNT3			: return "D3DTTFF_COUNT3";
	case D3DTTFF_COUNT4			: return "D3DTTFF_COUNT4";
	case D3DTTFF_PROJECTED		: return "D3DTTFF_PROJECTED";
	default					      : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_ZBuffer_Type_Name(unsigned value)
{
	switch (value) {
	case D3DZB_FALSE				: return "D3DZB_FALSE";
	case D3DZB_TRUE				: return "D3DZB_TRUE";
	case D3DZB_USEW				: return "D3DZB_USEW";
	default					      : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Fill_Mode_Name(unsigned value)
{
	switch (value) {
	case D3DFILL_POINT			: return "D3DFILL_POINT";
	case D3DFILL_WIREFRAME		: return "D3DFILL_WIREFRAME";
	case D3DFILL_SOLID			: return "D3DFILL_SOLID";
	default					      : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Shade_Mode_Name(unsigned value)
{
	switch (value) {
	case D3DSHADE_FLAT			: return "D3DSHADE_FLAT";
	case D3DSHADE_GOURAUD		: return "D3DSHADE_GOURAUD";
	case D3DSHADE_PHONG			: return "D3DSHADE_PHONG";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Blend_Name(unsigned value)
{
	switch (value) {
	case D3DBLEND_ZERO                : return "D3DBLEND_ZERO";
	case D3DBLEND_ONE                 : return "D3DBLEND_ONE";
	case D3DBLEND_SRCCOLOR            : return "D3DBLEND_SRCCOLOR";
	case D3DBLEND_INVSRCCOLOR         : return "D3DBLEND_INVSRCCOLOR";
	case D3DBLEND_SRCALPHA            : return "D3DBLEND_SRCALPHA";
	case D3DBLEND_INVSRCALPHA         : return "D3DBLEND_INVSRCALPHA";
	case D3DBLEND_DESTALPHA           : return "D3DBLEND_DESTALPHA";
	case D3DBLEND_INVDESTALPHA        : return "D3DBLEND_INVDESTALPHA";
	case D3DBLEND_DESTCOLOR           : return "D3DBLEND_DESTCOLOR";
	case D3DBLEND_INVDESTCOLOR        : return "D3DBLEND_INVDESTCOLOR";
	case D3DBLEND_SRCALPHASAT         : return "D3DBLEND_SRCALPHASAT";
	case D3DBLEND_BOTHSRCALPHA        : return "D3DBLEND_BOTHSRCALPHA";
	case D3DBLEND_BOTHINVSRCALPHA     : return "D3DBLEND_BOTHINVSRCALPHA";
	default									 : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Cull_Mode_Name(unsigned value)
{
	switch (value) {
	case D3DCULL_NONE				: return "D3DCULL_NONE";
	case D3DCULL_CW				: return "D3DCULL_CW";
	case D3DCULL_CCW				: return "D3DCULL_CCW";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Cmp_Func_Name(unsigned value)
{
	switch (value) {
	case D3DCMP_NEVER          : return "D3DCMP_NEVER";
	case D3DCMP_LESS           : return "D3DCMP_LESS";
	case D3DCMP_EQUAL          : return "D3DCMP_EQUAL";
	case D3DCMP_LESSEQUAL      : return "D3DCMP_LESSEQUAL";
	case D3DCMP_GREATER        : return "D3DCMP_GREATER";
	case D3DCMP_NOTEQUAL       : return "D3DCMP_NOTEQUAL";
	case D3DCMP_GREATEREQUAL   : return "D3DCMP_GREATEREQUAL";
	case D3DCMP_ALWAYS         : return "D3DCMP_ALWAYS";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Fog_Mode_Name(unsigned value)
{
	switch (value) {
	case D3DFOG_NONE				: return "D3DFOG_NONE";
	case D3DFOG_EXP				: return "D3DFOG_EXP";
	case D3DFOG_EXP2				: return "D3DFOG_EXP2";
	case D3DFOG_LINEAR			: return "D3DFOG_LINEAR";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Stencil_Op_Name(unsigned value)
{
	switch (value) {
	case D3DSTENCILOP_KEEP		: return "D3DSTENCILOP_KEEP";
	case D3DSTENCILOP_ZERO		: return "D3DSTENCILOP_ZERO";
	case D3DSTENCILOP_REPLACE	: return "D3DSTENCILOP_REPLACE";
	case D3DSTENCILOP_INCRSAT	: return "D3DSTENCILOP_INCRSAT";
	case D3DSTENCILOP_DECRSAT	: return "D3DSTENCILOP_DECRSAT";
	case D3DSTENCILOP_INVERT	: return "D3DSTENCILOP_INVERT";
	case D3DSTENCILOP_INCR		: return "D3DSTENCILOP_INCR";
	case D3DSTENCILOP_DECR		: return "D3DSTENCILOP_DECR";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Material_Source_Name(unsigned value)
{
	switch (value) {
	case D3DMCS_MATERIAL			: return "D3DMCS_MATERIAL";
	case D3DMCS_COLOR1			: return "D3DMCS_COLOR1";
	case D3DMCS_COLOR2			: return "D3DMCS_COLOR2";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Vertex_Blend_Flag_Name(unsigned value)
{
	switch (value) {
	case D3DVBF_DISABLE			: return "D3DVBF_DISABLE";
	case D3DVBF_1WEIGHTS			: return "D3DVBF_1WEIGHTS";
	case D3DVBF_2WEIGHTS			: return "D3DVBF_2WEIGHTS";
	case D3DVBF_3WEIGHTS			: return "D3DVBF_3WEIGHTS";
	case D3DVBF_TWEENING			: return "D3DVBF_TWEENING";
	case D3DVBF_0WEIGHTS			: return "D3DVBF_0WEIGHTS";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Patch_Edge_Style_Name(unsigned value)
{
	switch (value) {
	case D3DPATCHEDGE_DISCRETE	: return "D3DPATCHEDGE_DISCRETE";
   case D3DPATCHEDGE_CONTINUOUS:return "D3DPATCHEDGE_CONTINUOUS";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Debug_Monitor_Token_Name(unsigned value)
{
	switch (value) {
	case D3DDMT_ENABLE			: return "D3DDMT_ENABLE";
	case D3DDMT_DISABLE			: return "D3DDMT_DISABLE";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Blend_Op_Name(unsigned value)
{
	switch (value) {
	case D3DBLENDOP_ADD			: return "D3DBLENDOP_ADD";
	case D3DBLENDOP_SUBTRACT	: return "D3DBLENDOP_SUBTRACT";
	case D3DBLENDOP_REVSUBTRACT: return "D3DBLENDOP_REVSUBTRACT";
	case D3DBLENDOP_MIN			: return "D3DBLENDOP_MIN";
	case D3DBLENDOP_MAX			: return "D3DBLENDOP_MAX";
	default							: return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Texture_Stage_State_Name(unsigned long state)
{
	switch (state) {
	case D3DTSS_COLOROP                   : return "D3DTSS_COLOROP";
	case D3DTSS_COLORARG1                 : return "D3DTSS_COLORARG1";
	case D3DTSS_COLORARG2                 : return "D3DTSS_COLORARG2";
	case D3DTSS_ALPHAOP                   : return "D3DTSS_ALPHAOP";
	case D3DTSS_ALPHAARG1                 : return "D3DTSS_ALPHAARG1";
	case D3DTSS_ALPHAARG2                 : return "D3DTSS_ALPHAARG2";
	case D3DTSS_BUMPENVMAT00              : return "D3DTSS_BUMPENVMAT00";
	case D3DTSS_BUMPENVMAT01              : return "D3DTSS_BUMPENVMAT01";
	case D3DTSS_BUMPENVMAT10              : return "D3DTSS_BUMPENVMAT10";
	case D3DTSS_BUMPENVMAT11              : return "D3DTSS_BUMPENVMAT11";
	case D3DTSS_TEXCOORDINDEX             : return "D3DTSS_TEXCOORDINDEX";
	case D3DTSS_BUMPENVLSCALE             : return "D3DTSS_BUMPENVLSCALE";
	case D3DTSS_BUMPENVLOFFSET            : return "D3DTSS_BUMPENVLOFFSET";
	case D3DTSS_TEXTURETRANSFORMFLAGS     : return "D3DTSS_TEXTURETRANSFORMFLAGS";
	case D3DTSS_COLORARG0                 : return "D3DTSS_COLORARG0";
	case D3DTSS_ALPHAARG0                 : return "D3DTSS_ALPHAARG0";
	case D3DTSS_RESULTARG                 : return "D3DTSS_RESULTARG";
	default										  : return "UNKNOWN";
	}
}

const char* DX8Wrapper::Get_DX8_Render_State_Name(unsigned long state)
{
	switch (state) {
	case D3DRS_ZENABLE                       : return "D3DRS_ZENABLE";
	case D3DRS_FILLMODE                      : return "D3DRS_FILLMODE";
	case D3DRS_SHADEMODE                     : return "D3DRS_SHADEMODE";
	case D3DRS_ZWRITEENABLE                  : return "D3DRS_ZWRITEENABLE";
	case D3DRS_ALPHATESTENABLE               : return "D3DRS_ALPHATESTENABLE";
	case D3DRS_LASTPIXEL                     : return "D3DRS_LASTPIXEL";
	case D3DRS_SRCBLEND                      : return "D3DRS_SRCBLEND";
	case D3DRS_DESTBLEND                     : return "D3DRS_DESTBLEND";
	case D3DRS_CULLMODE                      : return "D3DRS_CULLMODE";
	case D3DRS_ZFUNC                         : return "D3DRS_ZFUNC";
	case D3DRS_ALPHAREF                      : return "D3DRS_ALPHAREF";
	case D3DRS_ALPHAFUNC                     : return "D3DRS_ALPHAFUNC";
	case D3DRS_DITHERENABLE                  : return "D3DRS_DITHERENABLE";
	case D3DRS_ALPHABLENDENABLE              : return "D3DRS_ALPHABLENDENABLE";
	case D3DRS_FOGENABLE                     : return "D3DRS_FOGENABLE";
	case D3DRS_SPECULARENABLE                : return "D3DRS_SPECULARENABLE";
	case D3DRS_FOGCOLOR                      : return "D3DRS_FOGCOLOR";
	case D3DRS_FOGTABLEMODE                  : return "D3DRS_FOGTABLEMODE";
	case D3DRS_FOGSTART                      : return "D3DRS_FOGSTART";
	case D3DRS_FOGEND                        : return "D3DRS_FOGEND";
	case D3DRS_FOGDENSITY                   : return "D3DRS_FOGDENSITY";
	// BFME's Direct3D 9 headers call this state D3DRS_DEPTHBIAS (195).
	case (D3DRENDERSTATETYPE)195             : return "D3DRS_DEPTHBIAS";
	case D3DRS_RANGEFOGENABLE                : return "D3DRS_RANGEFOGENABLE";
	case D3DRS_STENCILENABLE                 : return "D3DRS_STENCILENABLE";
	case D3DRS_STENCILFAIL                   : return "D3DRS_STENCILFAIL";
	case D3DRS_STENCILZFAIL                  : return "D3DRS_STENCILZFAIL";
	case D3DRS_STENCILPASS                   : return "D3DRS_STENCILPASS";
	case D3DRS_STENCILFUNC                   : return "D3DRS_STENCILFUNC";
	case D3DRS_STENCILREF                    : return "D3DRS_STENCILREF";
	case D3DRS_STENCILMASK                   : return "D3DRS_STENCILMASK";
	case D3DRS_STENCILWRITEMASK              : return "D3DRS_STENCILWRITEMASK";
	case D3DRS_TEXTUREFACTOR                 : return "D3DRS_TEXTUREFACTOR";
	case D3DRS_WRAP0                         : return "D3DRS_WRAP0";
	case D3DRS_WRAP1                         : return "D3DRS_WRAP1";
	case D3DRS_WRAP2                         : return "D3DRS_WRAP2";
	case D3DRS_WRAP3                         : return "D3DRS_WRAP3";
	case D3DRS_WRAP4                         : return "D3DRS_WRAP4";
	case D3DRS_WRAP5                         : return "D3DRS_WRAP5";
	case D3DRS_WRAP6                         : return "D3DRS_WRAP6";
	case D3DRS_WRAP7                         : return "D3DRS_WRAP7";
	case D3DRS_CLIPPING                      : return "D3DRS_CLIPPING";
	case D3DRS_LIGHTING                      : return "D3DRS_LIGHTING";
	case D3DRS_AMBIENT                       : return "D3DRS_AMBIENT";
	case D3DRS_FOGVERTEXMODE                 : return "D3DRS_FOGVERTEXMODE";
	case D3DRS_COLORVERTEX                   : return "D3DRS_COLORVERTEX";
	case D3DRS_LOCALVIEWER                   : return "D3DRS_LOCALVIEWER";
	case D3DRS_NORMALIZENORMALS              : return "D3DRS_NORMALIZENORMALS";
	case D3DRS_DIFFUSEMATERIALSOURCE         : return "D3DRS_DIFFUSEMATERIALSOURCE";
	case D3DRS_SPECULARMATERIALSOURCE        : return "D3DRS_SPECULARMATERIALSOURCE";
	case D3DRS_AMBIENTMATERIALSOURCE         : return "D3DRS_AMBIENTMATERIALSOURCE";
	case D3DRS_EMISSIVEMATERIALSOURCE        : return "D3DRS_EMISSIVEMATERIALSOURCE";
	case D3DRS_VERTEXBLEND                   : return "D3DRS_VERTEXBLEND";
	case D3DRS_CLIPPLANEENABLE               : return "D3DRS_CLIPPLANEENABLE";
	case D3DRS_POINTSIZE                     : return "D3DRS_POINTSIZE";
	case D3DRS_POINTSIZE_MIN                 : return "D3DRS_POINTSIZE_MIN";
	case D3DRS_POINTSPRITEENABLE             : return "D3DRS_POINTSPRITEENABLE";
	case D3DRS_POINTSCALEENABLE              : return "D3DRS_POINTSCALEENABLE";
	case D3DRS_POINTSCALE_A                  : return "D3DRS_POINTSCALE_A";
	case D3DRS_POINTSCALE_B                  : return "D3DRS_POINTSCALE_B";
	case D3DRS_POINTSCALE_C                  : return "D3DRS_POINTSCALE_C";
	case D3DRS_MULTISAMPLEANTIALIAS          : return "D3DRS_MULTISAMPLEANTIALIAS";
	case D3DRS_MULTISAMPLEMASK               : return "D3DRS_MULTISAMPLEMASK";
	case D3DRS_PATCHEDGESTYLE                : return "D3DRS_PATCHEDGESTYLE";
	case D3DRS_DEBUGMONITORTOKEN             : return "D3DRS_DEBUGMONITORTOKEN";
	case D3DRS_POINTSIZE_MAX                 : return "D3DRS_POINTSIZE_MAX";
	case D3DRS_INDEXEDVERTEXBLENDENABLE      : return "D3DRS_INDEXEDVERTEXBLENDENABLE";
	case D3DRS_COLORWRITEENABLE              : return "D3DRS_COLORWRITEENABLE";
	case D3DRS_TWEENFACTOR                   : return "D3DRS_TWEENFACTOR";
	case D3DRS_BLENDOP                       : return "D3DRS_BLENDOP";
	default											  : return "UNKNOWN";
	}
}
