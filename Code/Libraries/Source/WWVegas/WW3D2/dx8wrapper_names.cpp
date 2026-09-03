// cl: /G7
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
    static const char *Get_DX8_Shade_Mode_Name(unsigned value);
    static const char *Get_DX8_Stencil_Op_Name(unsigned value);
    static const char *Get_DX8_Texture_Address_Name(unsigned value);
    static const char *Get_DX8_Texture_Arg_Name(unsigned value);
    static const char *Get_DX8_Texture_Filter_Name(unsigned value);
    static const char *Get_DX8_Texture_Op_Name(unsigned value);
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
