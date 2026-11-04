// Target facts: ShaderClass is a plain class with no bases or virtual functions.
// RVA 0x00068FE6 stores only the dword 0x0010441B at +0; 0x0015CF75 allocates
// count*4 and 0x0015CF95 passes this constructor and stride 4 to the array iterator.
// There is no ShaderClass destructor row or vtable store. RVA 0x0010852B copies
// one dword. RVA 0x00129544 tests byte +2, bit 1, inside that same ShaderBits word;
// 0x001374E0 reads byte +2, bit 0. field02 exposes that byte of the word.
// Rowed getters at 0x00137470/480/490, 0x00125FC7, 0x001374C0, 0x000D1A91,
// 0x001374D0, 0x00125FD0, 0x001374E0 and 0x00129430 prove shifts 0,3,4,5,8,
// 10,13,14,16,17. Alpha test uses two bits at shift 18 (0x00125FBE);
// cull uses bit 20 (0x001374B0), detail color bits 21..24 (0x000D1A88),
// and detail alpha bits 25..27 (0x001374A0). Reset is rowed at 0x00066073.
// RVA 0x00138110 writes ShaderDirty at VA 0x00DB621C; Apply (0x00137590)
// reads/writes CurrentShader at VA 0x00DF29C0 (0x001375C1 and 0x001375DE).
// The rowed BfmeB1137::Install_Materials and ShroudTextureShader::rva000F5AD4
// write the same ShaderDirty byte at 0x0009585A and 0x000F5ADE; they retain access.
// Rva0006614F::rva0006E153 writes it at 0x0006E153; Rva007D6B70::set and
// Rva007D85C0::set read it at 0x000F81C3 and 0x000FA68E; they also retain access.
// Other rowed entries: Init_From_Material3 0x00137550, Guess_Sort_Level
// 0x001381B0, Get_SS_Category 0x00138130, Enable_Fog 0x00138200,
// Get_Description 0x00138280, Is_Backface_Culling_Inverted 0x001381F0,
// operator== 0x00143240, operator!= 0x001541B0. The setters from Set_Depth_Compare
// to Set_NPatch_Enable, in declaration order and skipping Set_Depth_Mask, are rowed at
// 0x00065F66, 0x00065F85, 0x00065F97, 0x00065FAC, 0x00065FC1, 0x00065FD6, 0x00065FEB,
// 0x00065FFD, 0x00066010, 0x00066023, 0x00066036, 0x00066049 and 0x0006605E. No setter,
// getter, Reset or default constructor row has a retail caller, direct or through a thunk
// (testHardwareSupport inlines Set_Depth_Compare: `or al, 7` at 0x000A651E), so they are
// inline with Zero Hour's bodies and their rows are the copies units emit. Set_Depth_Mask
// has no row; as an import-inline it is always inlined and never emitted. Enum, field,
// preset and inline names follow Zero Hour's GeneralsMD WW3D2/shader.h; its one-bit
// alpha-test layout is not used here.

#pragma once
// WW3D2's shader.h guard: a unit that includes the reference shader.h first keeps its
// ShaderClass (same layout and decorated names), and this header then adds nothing.

#ifndef SHADER_H
#define SHADER_H
enum ShaderShiftConstants {
    SHIFT_DEPTHCOMPARE = 0,
    SHIFT_DEPTHMASK = 3,
    SHIFT_COLORMASK = 4,
    SHIFT_DSTBLEND = 5,
    SHIFT_FOG = 8,
    SHIFT_PRIGRADIENT = 10,
    SHIFT_SECGRADIENT = 13,
    SHIFT_SRCBLEND = 14,
    SHIFT_TEXTURING = 16,
    SHIFT_NPATCHENABLE = 17,
    SHIFT_ALPHATEST = 18,
    SHIFT_CULLMODE = 20,
    SHIFT_POSTDETAILCOLORFUNC = 21,
    SHIFT_POSTDETAILALPHAFUNC = 25
};

#define SHADE_CNST(depth_compare, depth_mask, color_mask, src_blend, dst_blend, fog, pri_grad, sec_grad, texture, alpha_test, cullmode, post_det_color, post_det_alpha) \
    ((depth_compare) << SHIFT_DEPTHCOMPARE | (depth_mask) << SHIFT_DEPTHMASK | \
     (color_mask) << SHIFT_COLORMASK | (dst_blend) << SHIFT_DSTBLEND | (fog) << SHIFT_FOG | \
     (pri_grad) << SHIFT_PRIGRADIENT | (sec_grad) << SHIFT_SECGRADIENT | \
     (src_blend) << SHIFT_SRCBLEND | (texture) << SHIFT_TEXTURING | \
     (alpha_test) << SHIFT_ALPHATEST | (cullmode) << SHIFT_CULLMODE | \
     (post_det_color) << SHIFT_POSTDETAILCOLORFUNC | \
     (post_det_alpha) << SHIFT_POSTDETAILALPHAFUNC)


class DX8Wrapper;
class BfmeB1137;
class ShroudTextureShader;
class Rva0006614F;
class Rva007D6B70;
class Rva007D85C0;
class StringClass;
struct W3dMaterial3Struct;

class ShaderClass
{
    friend class DX8Wrapper;
    friend class BfmeB1137;
    friend class ShroudTextureShader;
    friend class Rva0006614F;
    friend class Rva007D6B70;
    friend class Rva007D85C0;
    void Apply();

public:
    enum AlphaTestType
    	{
    		ALPHATEST_DISABLE= 0,
    		ALPHATEST_ENABLE,
    		ALPHATEST_MAX
    	};

    enum DepthCompareType
    	{
    		PASS_NEVER=0,
    		PASS_LESS,
    		PASS_EQUAL,
    		PASS_LEQUAL,
    		PASS_GREATER,
    		PASS_NOTEQUAL,
    		PASS_GEQUAL,
    		PASS_ALWAYS,
    		PASS_MAX
    	};

    enum DepthMaskType
    	{
    		DEPTH_WRITE_DISABLE=0,
    		DEPTH_WRITE_ENABLE,
    		DEPTH_WRITE_MAX
    	};

    enum ColorMaskType
    	{
    		COLOR_WRITE_DISABLE=0,
    		COLOR_WRITE_ENABLE,
    		COLOR_WRITE_MAX
    	};

    enum DetailAlphaFuncType
     	{
    		DETAILALPHA_DISABLE=0,
    		DETAILALPHA_DETAIL,
    		DETAILALPHA_SCALE,
    		DETAILALPHA_INVSCALE,
    		DETAILALPHA_MAX
    	};

    enum DetailColorFuncType
     	{
     		DETAILCOLOR_DISABLE=0,
    		DETAILCOLOR_DETAIL,
    		DETAILCOLOR_SCALE,
    		DETAILCOLOR_INVSCALE,
    		DETAILCOLOR_ADD,
    		DETAILCOLOR_SUB,
    		DETAILCOLOR_SUBR,
    		DETAILCOLOR_BLEND,
    		DETAILCOLOR_DETAILBLEND,
    		DETAILCOLOR_ADDSIGNED,
    		DETAILCOLOR_ADDSIGNED2X,
    		DETAILCOLOR_SCALE2X,
    		DETAILCOLOR_MODALPHAADDCOLOR,
    		DETAILCOLOR_MAX
    	};

    enum CullModeType
    	{
    		CULL_MODE_DISABLE=0,
    		CULL_MODE_ENABLE,
    		CULL_MODE_MAX
    	};

    enum NPatchEnableType
    	{
    		NPATCH_DISABLE=0,
    		NPATCH_ENABLE,
    		NPATCH_TYPE_MAX
    	};

    enum DstBlendFuncType
      	{
      		DSTBLEND_ZERO=0,
      		DSTBLEND_ONE,
     		DSTBLEND_SRC_COLOR,
     		DSTBLEND_ONE_MINUS_SRC_COLOR,
     		DSTBLEND_SRC_ALPHA,
     		DSTBLEND_ONE_MINUS_SRC_ALPHA,
    		DSTBLEND_MAX
      	};

    enum FogFuncType
     	{
     		FOG_DISABLE=0,
     		FOG_ENABLE,
     		FOG_SCALE_FRAGMENT,
     		FOG_WHITE,
    		FOG_MAX
     	};

    enum PriGradientType
     	{
     		GRADIENT_DISABLE=0,
    		GRADIENT_MODULATE,
    		GRADIENT_ADD,
    		GRADIENT_BUMPENVMAP,
    		GRADIENT_BUMPENVMAPLUMINANCE,
    		GRADIENT_MODULATE2X,
    		GRADIENT_MAX
     	};

    enum SecGradientType
    	{
    		SECONDARY_GRADIENT_DISABLE=0,
    		SECONDARY_GRADIENT_ENABLE,
    		SECONDARY_GRADIENT_MAX
    	};

    enum SrcBlendFuncType
      	{
      		SRCBLEND_ZERO=0,
      		SRCBLEND_ONE,
     		SRCBLEND_SRC_ALPHA,
     		SRCBLEND_ONE_MINUS_SRC_ALPHA,
    		SRCBLEND_MAX
      	};

    enum TexturingType
    	{
    		TEXTURING_DISABLE=0,
    		TEXTURING_ENABLE,
    		TEXTURING_MAX
    	};

    enum StaticSortCategoryType
    	{
    		SSCAT_OPAQUE=0,
    		SSCAT_ALPHA_TEST,
    		SSCAT_ADDITIVE,
    		SSCAT_SCREEN,
    		SSCAT_OTHER
    	};

    enum {
        MASK_DEPTHCOMPARE = 7,
        MASK_DEPTHMASK = 1 << 3,
        MASK_COLORMASK = 1 << 4,
        MASK_DSTBLEND = 7 << 5,
        MASK_FOG = 3 << 8,
        MASK_PRIGRADIENT = 7 << 10,
        MASK_SECGRADIENT = 1 << 13,
        MASK_SRCBLEND = 3 << 14,
        MASK_TEXTURING = 1 << 16,
        MASK_NPATCHENABLE = 1 << 17,
        MASK_ALPHATEST = 3 << 18,
        MASK_CULLMODE = 1 << 20,
        MASK_POSTDETAILCOLORFUNC = 15 << 21,
        MASK_POSTDETAILALPHAFUNC = 7 << 25
    };

    ShaderClass() { Reset(); }
    ShaderClass(const ShaderClass &shader) : ShaderBits(shader.ShaderBits) {}
    ShaderClass(unsigned int bits) : ShaderBits(bits) {}
    // Inline, as retail's are: VectorClass<ShaderClass>::operator== and ::ID fold into the
    // four-byte-element bodies 0x00196920 and 0x001964F0 (the compare is inlined), and the rowed
    // 0x00143240/0x001541B0 are the COMDAT copies units emit where a call is not inlined.
    // Declared out of line, a unit calls them where retail inlines (LINK-177).
    bool operator==(const ShaderClass &shader) { return ShaderBits == shader.ShaderBits; }
    bool operator!=(const ShaderClass &shader) { return ShaderBits != shader.ShaderBits; }

    unsigned int Get_Bits() const { return ShaderBits; }
    inline void Reset();
    DepthCompareType Get_Depth_Compare() const { return (DepthCompareType)(ShaderBits&MASK_DEPTHCOMPARE>>SHIFT_DEPTHCOMPARE); }
    DepthMaskType Get_Depth_Mask() const { return (DepthMaskType)((ShaderBits&MASK_DEPTHMASK)>>SHIFT_DEPTHMASK); }
    ColorMaskType Get_Color_Mask() const { return (ColorMaskType)((ShaderBits&MASK_COLORMASK)>>SHIFT_COLORMASK); }
    DetailAlphaFuncType Get_Post_Detail_Alpha_Func() const { return (DetailAlphaFuncType)((ShaderBits&MASK_POSTDETAILALPHAFUNC)>>SHIFT_POSTDETAILALPHAFUNC); }
    DetailColorFuncType Get_Post_Detail_Color_Func() const { return (DetailColorFuncType)((ShaderBits&MASK_POSTDETAILCOLORFUNC)>>SHIFT_POSTDETAILCOLORFUNC); }
    AlphaTestType Get_Alpha_Test() const { return (AlphaTestType)((ShaderBits&MASK_ALPHATEST)>>SHIFT_ALPHATEST); }
    CullModeType Get_Cull_Mode() const { return (CullModeType)((ShaderBits&MASK_CULLMODE)>>SHIFT_CULLMODE); }
    DstBlendFuncType Get_Dst_Blend_Func() const { return (DstBlendFuncType)((ShaderBits&MASK_DSTBLEND)>>SHIFT_DSTBLEND); }
    FogFuncType Get_Fog_Func() const { return (FogFuncType)((ShaderBits&MASK_FOG)>>SHIFT_FOG); }
    PriGradientType Get_Primary_Gradient() const { return (PriGradientType)((ShaderBits&MASK_PRIGRADIENT)>>SHIFT_PRIGRADIENT); }
    SecGradientType Get_Secondary_Gradient() const { return (SecGradientType)((ShaderBits&MASK_SECGRADIENT)>>SHIFT_SECGRADIENT); }
    SrcBlendFuncType Get_Src_Blend_Func() const { return (SrcBlendFuncType)((ShaderBits&MASK_SRCBLEND)>>SHIFT_SRCBLEND); }
    TexturingType Get_Texturing() const { return (TexturingType)((ShaderBits&MASK_TEXTURING)>>SHIFT_TEXTURING); }
    NPatchEnableType Get_NPatch_Enable() const { return (NPatchEnableType)((ShaderBits&MASK_NPATCHENABLE)>>SHIFT_NPATCHENABLE); }

    int Uses_Alpha() const
    {
        if (Get_Alpha_Test() != ALPHATEST_DISABLE) return true;
        DstBlendFuncType dst = Get_Dst_Blend_Func();
        if (dst == DSTBLEND_SRC_ALPHA || dst == DSTBLEND_ONE_MINUS_SRC_ALPHA) return true;
        SrcBlendFuncType src = Get_Src_Blend_Func();
        return src == SRCBLEND_SRC_ALPHA || src == SRCBLEND_ONE_MINUS_SRC_ALPHA;
    }
    int Uses_Fog() const { return Get_Fog_Func() != FOG_DISABLE; }
    int Uses_Primary_Gradient() const { return Get_Primary_Gradient() != GRADIENT_DISABLE; }
    int Uses_Secondary_Gradient() const { return Get_Secondary_Gradient() != SECONDARY_GRADIENT_DISABLE; }
    int Uses_Texture() const { return Get_Texturing() != TEXTURING_DISABLE; }
    int Uses_Post_Detail_Texture() const
    {
        if (Get_Texturing() == TEXTURING_DISABLE) return false;
        return Get_Post_Detail_Color_Func() != DETAILCOLOR_DISABLE || Get_Post_Detail_Alpha_Func() != DETAILALPHA_DISABLE;
    }

    void Set_Depth_Compare(DepthCompareType x) { ShaderBits &= ~MASK_DEPTHCOMPARE; ShaderBits |= (x << SHIFT_DEPTHCOMPARE); }
    __declspec(dllimport) __forceinline void Set_Depth_Mask(DepthMaskType value) { ShaderBits = (ShaderBits & ~MASK_DEPTHMASK) | (value << 3); }
    void Set_Color_Mask(ColorMaskType x) { ShaderBits &= ~MASK_COLORMASK; ShaderBits |= (x << SHIFT_COLORMASK); }
    void Set_Post_Detail_Alpha_Func(DetailAlphaFuncType x) { ShaderBits &= ~MASK_POSTDETAILALPHAFUNC; ShaderBits |= (x << SHIFT_POSTDETAILALPHAFUNC); }
    void Set_Post_Detail_Color_Func(DetailColorFuncType x) { ShaderBits &= ~MASK_POSTDETAILCOLORFUNC; ShaderBits |= (x << SHIFT_POSTDETAILCOLORFUNC); }
    void Set_Alpha_Test(AlphaTestType x) { ShaderBits &= ~MASK_ALPHATEST; ShaderBits |= (x << SHIFT_ALPHATEST); }
    void Set_Cull_Mode(CullModeType x) { ShaderBits &= ~MASK_CULLMODE; ShaderBits |= (x << SHIFT_CULLMODE); }
    void Set_Dst_Blend_Func(DstBlendFuncType x) { ShaderBits &= ~MASK_DSTBLEND; ShaderBits |= (x << SHIFT_DSTBLEND); }
    void Set_Fog_Func(FogFuncType x) { ShaderBits &= ~MASK_FOG; ShaderBits |= (x << SHIFT_FOG); }
    void Set_Primary_Gradient(PriGradientType x) { ShaderBits &= ~MASK_PRIGRADIENT; ShaderBits |= (x << SHIFT_PRIGRADIENT); }
    void Set_Secondary_Gradient(SecGradientType x) { ShaderBits &= ~MASK_SECGRADIENT; ShaderBits |= (x << SHIFT_SECGRADIENT); }
    void Set_Src_Blend_Func(SrcBlendFuncType x) { ShaderBits &= ~MASK_SRCBLEND; ShaderBits |= (x << SHIFT_SRCBLEND); }
    void Set_Texturing(TexturingType x) { ShaderBits &= ~MASK_TEXTURING; ShaderBits |= (x << SHIFT_TEXTURING); }
    void Set_NPatch_Enable(NPatchEnableType x) { ShaderBits &= ~MASK_NPATCHENABLE; ShaderBits |= (x << SHIFT_NPATCHENABLE); }

    void Init_From_Material3(const W3dMaterial3Struct &material);
    void Enable_Fog(const char *source);
    StaticSortCategoryType Get_SS_Category() const;
    int Guess_Sort_Level() const;
    const StringClass &Get_Description(StringClass &str) const;
    static void Invalidate() { ShaderDirty = true; }
    static void Invert_Backface_Culling(bool onoff);
    static bool Is_Backface_Culling_Inverted();

    union {
        unsigned int ShaderBits;
        struct {
            unsigned char pad00[2];
            unsigned char field02;
        };
    };

    static ShaderClass _PresetOpaqueShader;
    static ShaderClass _PresetAdditiveShader;
    static ShaderClass _PresetBumpenvmapShader;
    static ShaderClass _PresetAlphaShader;
    static ShaderClass _PresetMultiplicativeShader;
    static ShaderClass _PresetOpaque2DShader;
    static ShaderClass _PresetOpaqueSpriteShader;
    static ShaderClass _PresetAdditive2DShader;
    static ShaderClass _PresetAlpha2DShader;
    static ShaderClass _PresetAdditiveSpriteShader;
    static ShaderClass _PresetAlphaSpriteShader;
    static ShaderClass _PresetOpaqueSolidShader;
    static ShaderClass _PresetAdditiveSolidShader;
    static ShaderClass _PresetAlphaSolidShader;
    static ShaderClass _PresetATest2DShader;
    static ShaderClass _PresetATestSpriteShader;
    static ShaderClass _PresetATestBlend2DShader;
    static ShaderClass _PresetATestBlendSpriteShader;
    static ShaderClass _PresetScreen2DShader;
    static ShaderClass _PresetScreenSpriteShader;
    static ShaderClass _PresetMultiplicative2DShader;
    static ShaderClass _PresetMultiplicativeSpriteShader;

protected:
    void Report_Unable_To_Fog(const char *source);
    static bool ShaderDirty;
    static unsigned long CurrentShader;
};

inline void ShaderClass::Reset()
{
    ShaderBits = 0;
    Set_Depth_Compare(PASS_LEQUAL);
    Set_Depth_Mask(DEPTH_WRITE_ENABLE);
    Set_Color_Mask(COLOR_WRITE_ENABLE);
    Set_Dst_Blend_Func(DSTBLEND_ZERO);
    Set_Fog_Func(FOG_DISABLE);
    Set_Primary_Gradient(GRADIENT_MODULATE);
    Set_Secondary_Gradient(SECONDARY_GRADIENT_DISABLE);
    Set_Src_Blend_Func(SRCBLEND_ONE);
    Set_Texturing(TEXTURING_DISABLE);
    Set_Alpha_Test(ALPHATEST_DISABLE);
    Set_Cull_Mode(CULL_MODE_ENABLE);
    Set_Post_Detail_Color_Func(DETAILCOLOR_DISABLE);
    Set_Post_Detail_Alpha_Func(DETAILALPHA_DISABLE);
    Set_NPatch_Enable(NPATCH_DISABLE);
}

#endif // SHADER_H
