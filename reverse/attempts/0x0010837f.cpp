// ?add@Rva0010837FManager@@QAEPAVW3DVolumetricShadowV2@@PAVRenderObjClass@@PAUShadowAngleView@@PAUShadowDrawableView@@@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0010837F..00108430, 177B; WB 8E1980 calls the named
// W3DVolumetricShadowV2 constructor and SetShadowAngleLimit. Their native
// targets are 0010811E (ret8) and the rowed 00106F82 (ret4).
// Retail proves allocation160, geometry-manager storage address +8,
// ShadowTypeInfo angle +1C and extrusion padding +8C. The manager entry's
// original name and the constructor's first parameter type remain unknown.
// Existing BFME2 W3DVolumetricShadowManagerAddShadow supplies the stencil /
// global gate and kind-bit interpretation; this V2 path does not use its
// larger volumetric-shadow layout or geometry-cache flow.
class RenderObjClass;
class W3DVolumetricShadowV2
{
public:
    W3DVolumetricShadowV2(void *managerStorage, RenderObjClass *renderObject);
    void SetShadowAngleLimit(float);
    unsigned char prefix[0x8c];
    float extrusionPadding;
    unsigned char tail[0x10];
};
class DX8Wrapper
{
public:
    static bool Has_Stencil();
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct ShadowGlobalView
{
    unsigned char prefix[0x60];
    bool useShadowVolumes;
};
struct ShadowAngleView
{
    unsigned char prefix[0x1c];
    float angle;
};
struct ShadowKindView
{
    unsigned char prefix[0x108];
    unsigned char kindBits;
};
struct ShadowDrawableView
{
    void *vptr;
    ShadowKindView *objectTemplate;
};
class Rva0010837FManager
{
public:
    W3DVolumetricShadowV2 *add(RenderObjClass *, ShadowAngleView *, ShadowDrawableView *);
private:
    unsigned char prefix[8];
    unsigned storage[2];
};
W3DVolumetricShadowV2 *Rva0010837FManager::add(RenderObjClass *renderObject,
                                             ShadowAngleView *info,
                                             ShadowDrawableView *drawable)
{
    if (!DX8Wrapper::Has_Stencil() || !renderObject ||
        !reinterpret_cast<ShadowGlobalView *>(TheWritableGlobalData)->useShadowVolumes)
        return 0;
    W3DVolumetricShadowV2 *shadow = new W3DVolumetricShadowV2(storage, renderObject);
    if (info->angle != 0.0f)
        shadow->SetShadowAngleLimit(info->angle);
    if (!drawable || !(drawable->objectTemplate->kindBits & 4))
        shadow->extrusionPadding = 0.1f;
    return shadow;
}
