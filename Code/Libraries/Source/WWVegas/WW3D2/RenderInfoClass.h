// Target facts (BFME 2 1.06; code addresses are RVAs):
// Constructor 0x00142EE0 stores the CameraClass reference at +0, not a vptr;
// neither it nor destructor 0x00142FE0 installs a table or calls a base.
// RenderInfoClass has no base, virtual functions, virtual slots or virtual
// destructor. Indirect calls at 0x00143037 and 0x00142E6E release pointed-to
// material passes and rendering methods, respectively, not RenderInfoClass.
// WW3D::Render 0x00118660 reserves exactly 0x148 bytes at 0x00118675 for
// the object passed to the constructor at 0x001186A8 and destructor at
// 0x001186DE. The constructor's final member word is +0x144: sizeof 0x148.
// The constructor clears float words +0x04..+0x18 and initializes the
// three overrides +0x1C/+0x20/+0x24 to 1.0 at 0x00142F19..0x00142F23;
// it clears pointers +0x28/+0x2C, 32 pass pointers +0x30..+0xAC, counts
// +0xB0/+0xB4, override level +0x138 and vector words +0x13C/+0x140/+0x144.
// Get_Fog_Color 0x001494D0 copies three words +0x08/+0x0C/+0x10 to a
// returned Vector3. MeshClass::Render 0x0014BB90 uses the overrides and
// light environment. Zero Hour's WW3D2/rinfo.h names Camera, the overrides,
// light_environment, Texture_Projector, pass members and override members;
// its fog-float names do not establish BFME 2's +0x04/+0x14/+0x18 meanings.
// Push_Material_Pass 0x00142BA0 bounds the count at +0xB0 against 31 and
// indexes +0x30 by four; Pop_Material_Pass 0x00142BE0 uses rejected +0xB4.
// Additional_Pass_Count 0x00142C20 reads +0xB0; Peek_Additional_Pass
// 0x00142C30 indexes +0x30. Push_Override_Flags 0x00142C50,
// Pop_Override_Flags 0x00142C70 and Current_Override_Flags 0x00142C80
// use level +0x138 and four-byte flags at +0xB8 (32 entries fit the extent).
// The ledger's Get_Rendering_Method_Stack 0x00142C40 returns the STLport
// vector<RefCountPtr<FXShader::RenderingMethod> > at +0x13C. Push_Rendering_Method
// 0x001431B0 and Pop_Rendering_Method 0x00142DF0 operate on four-byte entries;
// the destructor calls that vector's destructor 0x00142E30 at 0x00143057.
// All rowed methods remain out-of-line declarations, including Get_Fog_Color.
// Donor facts: Zero Hour's WW3D2/rinfo.h supplies the nonvirtual method and
// flag names and values; the rendering-method names and types are ledger facts.

#pragma once

#ifndef BFME2_RENDERINFOCLASS_H
#define BFME2_RENDERINFOCLASS_H

#include "../WWMath/Vector3Data.h"
#include <vector>

class CameraClass;
class LightEnvironmentClass;
class MaterialPassClass;
class TexProjectClass;
namespace FXShader { class RenderingMethod; }
template <class T> class RefCountPtr;

typedef _STL::vector<RefCountPtr<FXShader::RenderingMethod>,
    _STL::allocator<RefCountPtr<FXShader::RenderingMethod> > > RenderingMethodStackType;

class RenderInfoClass
{
public:
    RenderInfoClass(CameraClass &camera);
    ~RenderInfoClass();

    enum RINFO_OVERRIDE_FLAGS
    {
        RINFO_OVERRIDE_DEFAULT = 0x0000,
        RINFO_OVERRIDE_FORCE_TWO_SIDED = 0x0001,
        RINFO_OVERRIDE_FORCE_SORTING = 0x0002,
        RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY = 0x0004,
        RINFO_OVERRIDE_SHADOW_RENDERING = 0x0008
    };

    void Push_Material_Pass(MaterialPassClass *pass);
    void Pop_Material_Pass();
    int Additional_Pass_Count();
    MaterialPassClass *Peek_Additional_Pass(int index);
    void Push_Override_Flags(RINFO_OVERRIDE_FLAGS flags);
    void Pop_Override_Flags();
    RINFO_OVERRIDE_FLAGS &Current_Override_Flags();
    void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
    void Pop_Rendering_Method();
    const RenderingMethodStackType &Get_Rendering_Method_Stack() const;
    Vector3 Get_Fog_Color() const;

    CameraClass &Camera;                         // +0x00
    float field04;                               // +0x04
    Vector3 FogColor;                             // +0x08
    float field14;                               // +0x14
    float field18;                               // +0x18
    float alphaOverride;                         // +0x1C
    float materialPassAlphaOverride;             // +0x20
    float materialPassEmissiveOverride;          // +0x24
    LightEnvironmentClass *light_environment;     // +0x28
    TexProjectClass *Texture_Projector;           // +0x2C

protected:
    MaterialPassClass *AdditionalMaterialPassArray[32]; // +0x30
    unsigned int AdditionalMaterialPassCount;     // +0xB0
    unsigned int RejectedMaterialPasses;          // +0xB4
    RINFO_OVERRIDE_FLAGS OverrideFlag[32];         // +0xB8
    unsigned int OverrideFlagLevel;               // +0x138
    RenderingMethodStackType RenderingMethodStack; // +0x13C
};

#endif
