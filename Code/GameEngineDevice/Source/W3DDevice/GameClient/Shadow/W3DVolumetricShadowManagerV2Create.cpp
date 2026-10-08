// cl: /DNDEBUG /MD /O1 /EHsc /G7 /arch:SSE
// BFME1 34f59164 BfmeShadowBufferManagerCreate.cpp is the semantic lead.
// Native 0x10837F..0x108430 returns a 0xA0-byte owner with RET12.
// Target-only deltas: GlobalData flag60, ShadowTypeInfo angle1C,
// Drawable kind-bit block4/108, SetShadowAngleLimit106F82, padding8C.
// Constructor10811E accepts prev-link then RenderObj; WB named lead and
// target m_renderObj74 agree with W3DVolumetricShadowV2. Factory method's
// original name remains unknown; its entry-point name is address-derived.
class RenderObjClass;
class Drawable;
class Shadow {
public:
    struct ShadowTypeInfo {
        char opaque00[0x1C];
        float m_sizeX;
    };
};
class W3DVolumetricShadowV2 {
public:
    W3DVolumetricShadowV2(W3DVolumetricShadowV2 **prevLink, RenderObjClass *resource);
    // The matched 35-byte setter only calls the CRT tan routine; retail's
    // factory retains its allocation unwind state across this nonthrowing call.
    void SetShadowAngleLimit(float angle) throw();
    char opaque00[0x8C];
    float m_extraExtrusionPadding;
    char opaque90[0x10];
};
class DX8Wrapper {
public:
    static bool Has_Stencil();
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct ShadowManagerGlobalDataView {
    char opaque00[0x60];
    bool m_useShadowVolumes;
};
struct DrawableKindBits {
    char opaque00[0x108];
    unsigned char m_bits;
};
struct DrawableKindView {
    void *opaque00;
    DrawableKindBits *m_bits;
};
class W3DVolumetricShadowManagerV2 {
public:
    W3DVolumetricShadowV2 *rva0010837F(RenderObjClass *, Shadow::ShadowTypeInfo *, Drawable *);
private:
    char opaque00[8];
    W3DVolumetricShadowV2 *m_firstShadow;
};
W3DVolumetricShadowV2 *W3DVolumetricShadowManagerV2::rva0010837F(
    RenderObjClass *resource, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw)
{
    if (!DX8Wrapper::Has_Stencil() || !resource ||
        !((ShadowManagerGlobalDataView *)TheWritableGlobalData)->m_useShadowVolumes)
        return 0;
    W3DVolumetricShadowV2 *shadow = new W3DVolumetricShadowV2(&m_firstShadow, resource);
    if (shadowInfo->m_sizeX != 0.0f)
        shadow->SetShadowAngleLimit(shadowInfo->m_sizeX);
    if (!draw || !(((DrawableKindView *)draw)->m_bits->m_bits & 4))
        shadow->m_extraExtrusionPadding = 0.1f;
    return shadow;
}
