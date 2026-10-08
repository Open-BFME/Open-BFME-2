// cl: /DNDEBUG /MD /O1 /GX /G7 /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME1 34f59164 BfmeShadowBufferManagerCreate.cpp is the semantic lead.
// Native 0x10837F..0x108430 returns a 0xA0-byte owner with RET12.
// Target-only deltas: GlobalData flag60, ShadowTypeInfo angle1C,
// Drawable kind-bit block4/108, SetShadowAngleLimit106F82, padding8C.
// Constructor10811E accepts prev-link then RenderObj; WB named lead and
// target m_renderObj74 agree with W3DVolumetricShadowV2. Factory method's
// original name remains unknown; its entry-point name is address-derived.
// Retail's vector allocator frees through the game-memory free wrapper at
// 0x00030830. Use that C entry point rather than a CRT DLL-import declaration.
#define _CRTIMP
#include <vector>
class MeshClass;
// Target1080B4 calls virtual slots 3, 5, 28 and 30 and releases refs at +4.
// Mesh CLASSID=0 and child enumeration are semantic leads from rendobj.h;
// slot 5's precise method name remains unknown. Do not import BFME1's slots.
class RenderObjClass {
public:
    virtual void Delete_This();
    virtual void v01();
    virtual void v02();
    virtual int Class_ID() const;
    virtual void v04();
    virtual MeshClass *v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual int v28() const;
    virtual void v29();
    virtual RenderObjClass *v30(int index) const;
    int m_numRefs;
};
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
    void rva001080B4(_STL::vector<MeshClass *> *meshes, RenderObjClass *resource);
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

void W3DVolumetricShadowV2::rva001080B4(
    _STL::vector<MeshClass *> *meshes, RenderObjClass *resource)
{
    if (resource->Class_ID() == 0) {
        MeshClass *mesh = resource->v05();
        meshes->push_back(mesh);
    } else {
        int count = resource->v28();
        while (count > 0) {
            RenderObjClass *child = resource->v30(--count);
            if (child) {
                rva001080B4(meshes, child);
                if (--child->m_numRefs == 0)
                    child->Delete_This();
            }
        }
    }
}
