// cl: /O2 /arch:SSE /G7 /MD /EHs
// Native Ghidra 00118660..001186FB, 155B, cdecl RET0. Existing
// callback 0006EE46 supplies owner and camera pointers. The native result
// is bool (AL), correcting the earlier void-only caller declaration.
// Rowed rinfo.cpp constructor/destructor establish RenderInfoClass size
// 148 and CameraClass-reference ABI. Native 001182A0..0011842F, 399B,
// consumes owner and RenderInfo pointers and returns true in AL. The
// wrapper forwards that result after releasing its local RenderInfo.
// Original wrapper and inner render API names remain unknown; the ZH
// WW3D::Render source supplies the RenderInfo lifetime as a semantic lead.
class CameraClass;
class RenderInfoClass
{
public:
    RenderInfoClass(CameraClass &camera);
    ~RenderInfoClass();
private:
    char storage[0x148];
};
// Canonical global identity is established by WW3DEndRender.cpp at DEC3D4.
class WW3D
{
    friend bool Rva00118660Call(void *owner, void *camera);
    static bool IsInitted;
};
bool Rva001182A0(void *owner, RenderInfoClass &info);

bool Rva00118660Call(void *owner, void *camera)
{
    if (!WW3D::IsInitted)
        return true;
    RenderInfoClass info(*static_cast<CameraClass *>(camera));
    return Rva001182A0(owner, info);
}
