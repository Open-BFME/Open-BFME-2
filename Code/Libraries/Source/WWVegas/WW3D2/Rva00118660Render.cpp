// cl: /O2 /arch:SSE /G7 /MD /EHs /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
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
#include "RenderInfoClass.h"
// Canonical global identity is established by ww3d.cpp (WW3D::End_Render) at DEC3D4.
#include "../WWMath/Vector3Data.h"
class CameraClass
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30();
    virtual void On_Frame_Update(void);
    void Apply(void);
};
class SceneClass;
// Zero Hour layer.h LayerClass on its GenericNode list base: vtable, NextNode
// +4, PrevNode +8 (Is_Valid tests both), Clear +0xC, ClearZ +0xD, ClearColor
// +0x10, Scene +0x1C, Camera +0x20. Offsets from the two bodies below.
class LayerClass
{
public:
    bool Is_Valid(void) const { return this != 0 && NextNode != 0 && PrevNode != 0; }
    LayerClass *Prev(void) const { return PrevNode; }
    void *vtable;
    LayerClass *NextNode;
    LayerClass *PrevNode;
    bool Clear;
    bool ClearZ;
    Vector3 ClearColor;
    SceneClass *Scene;
    CameraClass *Camera;
};
// LayerListClass::Last() is the list tail sentinel's PrevNode at +0x18.
class LayerListClass
{
public:
    LayerClass *Last(void) const { return LastNodePrev; }
    char pad[0x18];
    LayerClass *LastNodePrev;
};
class WW3D;
struct IDirect3DDevice8;
class IDirect3DSurface9;
struct _D3DVIEWPORT8;
class LightEnvironmentClass;
#include "DX8WrapperClass.h"
bool Rva00118660Call(void *owner, void *camera);
#include "WW3DClass.h"
bool Rva001182A0(void *owner, RenderInfoClass &info);

bool Rva00118660Call(void *owner, void *camera)
{
    if (!WW3D::IsInitted)
        return true;
    RenderInfoClass info(*static_cast<CameraClass *>(camera));
    return Rva001182A0(owner, info);
}

// Retail 0x00118700 (96 B) and 0x00118760 (135 B), right after this unit's
// 0x00118660: Zero Hour ww3d.cpp WW3D::Render(const LayerClass &) and
// WW3D::Render(const LayerListClass &). BFME2 returns bool (true = OK, as the
// matched WW3D::Render 0x00118430) and folds the scene/camera/clear overload
// in: it reads the layer's fields directly, skips the camera update, Apply
// and the three-bool DX8Wrapper::Clear when the layer has no camera, then
// renders the scene through 0x00118660. The list overload walks from the
// last layer through Prev() while Is_Valid(), inlining the layer overload and
// stopping on the first non-true result. Neither has a direct caller.
bool WW3D::Render(const LayerClass &layer)
{
    if (!IsInitted)
        return true;
    if (layer.Camera) {
        layer.Camera->On_Frame_Update();
        layer.Camera->Apply();
        if (layer.Clear || layer.ClearZ)
            DX8Wrapper::Clear(layer.Clear, layer.ClearZ, layer.ClearZ, layer.ClearColor, 0.0f, 1.0f, 0);
    }
    return Rva00118660Call(layer.Scene, layer.Camera);
}

bool WW3D::Render(const LayerListClass &layer_list)
{
    if (!IsInitted)
        return true;
    LayerClass *layer = layer_list.Last();
    while (layer->Is_Valid()) {
        bool result = Render(*layer);
        if (result != true)
            return result;
        layer = layer->Prev();
    }
    return true;
}
