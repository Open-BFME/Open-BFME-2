// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// dxsdk
// platformsdk
// Ghidra 00174BA6..00174C17, 113B, RET0. The existing caller 001173F0
// establishes the DF6F94 receiver identity and its address-derived method.
// Retail compares three pointer ranges at +0/+4, +C/+10, +18/+1C, calls
// each range worker, then invalidates textures and clears both D3D shaders.
// Range-worker original names and element types are not established.
#include <d3d9.h>

struct IDirect3DDevice8;
class Rva00DF6F94GapFillerContext;
#include "DX8WrapperClass.h"
struct DX8WrapperStageHelper
{
    static void Rva0011CC60InvalidateTextureStages();
};
void Rva00125430(bool enable);
extern unsigned int number_of_DX8_calls;
class Rva00174A57
{
public:
    void rva00174A57();
};
class Rva001748B3 { public: void rva001748B3(); };
// 0x001748E8 is rowed as FXShaderRenderer::FlushSoftwareSkinnedRenderingTasks
// (FXShaderRendererSkin.cpp); this context is that renderer.
#include "FXShaderRenderer.h"
class Rva00DF6F94GapFillerContext
{
public:
    void rva174ba6();
    /* the rowed Rva001748B3::rva001748B3 */ __declspec(dllimport) __forceinline void rva001748B3() { ((Rva001748B3 *)this)->rva001748B3(); }
private:
    void *first0, *last0, *limit0;
    void *first1, *last1, *limit1;
    void *first2, *last2, *limit2;
};
void Rva00DF6F94GapFillerContext::rva174ba6()
{
    if (first0 != last0 || first1 != last1 || first2 != last2)
    {
        Rva00125430(true);
        rva001748B3();
        reinterpret_cast<FXShaderRenderer *>(this)->FlushSoftwareSkinnedRenderingTasks();
        reinterpret_cast<Rva00174A57 *>(this)->rva00174A57();
        Rva00125430(false);
        DX8WrapperStageHelper::Rva0011CC60InvalidateTextureStages();
        // The device is a Direct3D 9 device: SetVertexShader is slot 92 (+0x170),
        // SetPixelShader slot 107 (+0x1AC).
        reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetVertexShader(0);
        ++number_of_DX8_calls;
        reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(0);
        ++number_of_DX8_calls;
    }
}
