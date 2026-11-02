// Target facts: ctor RVA 0x0013EDD0 stores NumRefs +4 = 1 and vptr VA 0x00BD330C, constructs eight owning four-byte texture entries at +8 with callbacks RVA 0x00326BE6/0x0017098D, and initializes dwords +0x28/+0x2C/+0x34 and bool +0x30. RVA 0x0006F58D allocates 0x38 before the ctor call at 0x0006F5B2. RefCountClass is the eight-byte primary base: its ctor RVA 0x00072882 stores VA 0x00BC650C and count +4; MaterialPassClass's dtor RVA 0x0013EE40 restores VA 0x00BD330C, destroys the eight entries, then restores the base table VA 0x00BC650C at RVA 0x0013EE9E.
// Target facts: MaterialPassClass has four virtual slots at VA 0x00BD330C: inherited Delete_This RVA 0x0006CE57, deleting dtor RVA 0x0013EF80, Install_Materials RVA 0x0013EFA0 and the empty const UnInstall_Materials RVA 0x0069E440. VA 0x00BD331C starts the MaterialPassClass string and bounds the table. The base table has Delete_This and deleting dtor RVA 0x00072899; the destructor's final table is the base's, not a competing MaterialPassClass table. Derived W3DShroudMaterialPassClass's VA 0x00BC6244 overrides slots 2/3 with rowed Install_Materials/UnInstall_Materials at RVA 0x00072EEB/0x000729EB.
// Target facts: rowed Set_Shader RVA 0x0013EEF0 writes the ShaderClass word at +0x28; Set_Material RVA 0x0030D3AD and rva0013EF70 RVA 0x0013EF70 own the pointer at +0x2C; Peek_Texture RVA 0x002C7469 reads +8+stage*4; Set_Cull_Volume RVA 0x003B23A5 writes +0x34. Install_Materials reads +0x2C at RVA 0x0013EFBC and +0x28 at RVA 0x0013EFF6; MeshClass::Render tests bool +0x30 at RVA 0x0014BF98. Ctor/dtor and rowed accessors are declared out of line. Ledger spellings name the rowed methods. Zero Hour GeneralsMD WW3D2/matpass.h supplies Peek_Material, Peek_Shader, Is_Enabled_On_Translucent_Meshes and the field names Shader, Material, EnableOnTranslucentMeshes and CullVolume; opaque field08 retains BFME2's handle storage without asserting Zero Hour's raw-pointer ownership.
#pragma once
#ifndef BFME2_WW3D2_MATERIALPASSCLASS_H
#define BFME2_WW3D2_MATERIALPASSCLASS_H

#include "../WWLib/RefCountData.h"
#include "ShaderClass.h"

class TextureClass;
class VertexMaterialClass;
class OBBoxClass;

class MaterialPassClass : public RefCountClass
{
public:
    MaterialPassClass();
    virtual ~MaterialPassClass();

    virtual void Install_Materials() const;
    virtual void UnInstall_Materials() const {}

    void Set_Shader(ShaderClass shader);
    void Set_Material(VertexMaterialClass *material);
    TextureClass *Peek_Texture(int stage = 0) const;
    RefCountClass *rva0013EF70() const;
    VertexMaterialClass *Peek_Material() const { return Material; }
    ShaderClass Peek_Shader() const { return Shader; }
    bool Is_Enabled_On_Translucent_Meshes() { return EnableOnTranslucentMeshes; }
    void Set_Cull_Volume(OBBoxClass *volume);

    void *field08[8];
    ShaderClass Shader;
    VertexMaterialClass *Material;
    bool EnableOnTranslucentMeshes;
    OBBoxClass *CullVolume;
};

#endif
