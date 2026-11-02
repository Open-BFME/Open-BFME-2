// Target facts: constructors RVA 0x0013D420 and 0x0013DAE0 store VA 0x00BD32A0 at +0 (stores RVA 0x0013D448 and 0x0013DB12); destructor RVA 0x0013C990 restores it at 0x0013C9AF, then RefCountClass's VA 0x00BC650C at 0x0013CA00. VA 0x00BD32A0 has inherited slot 0 = RVA 0x0006CE57 (Delete_This), slot 1 = RVA 0x0013D550 (deleting destructor calling 0x0013C990); GridClassicEnvironmentMapperClass constructor RVA 0x0013D2F0 owns the next table at VA 0x00BD32A8. The class is polymorphic with no new slots; RefCountClass occupies +0..+7, with int NumRefs = 1 stored by both constructors.
// Target facts: Init RVA 0x0013D9B0 allocates 0x6C at 0x0013D9D0 before calling the constructor at 0x0013D9E8. Constructor 0x0013D420 initializes pointer +8 (a separately allocated 0x44-byte material), uints +0xC/+0x10/+0x14/+0x18, StringClass +0x1C, eight mapper pointers +0x20..+0x3C and eight UV sources +0x40..+0x5C, UniqueID +0x60, CRCDirty byte +0x68 and UseLighting byte +0x69. Get_CRC RVA 0x001432B0 reads/writes CRC at +0x64. Set_Name RVA 0x0013D3F0 forwards +0x1C to StringClass assignment; copy constructor 0x0013DAE0, assignment 0x0013DC00 and destructor 0x0013C990 manage that string and the mappers out of line. Zero Hour GeneralsMD WW3D2/vertmaterial.h supplies field and enum names; retail Init sets COLOR1 on preset 0 and initializes preset 1 separately.
// Target facts: out-of-line ledger declarations: flags/mapper 0x0013C780/0x0013C7B0; Make_Unique 0x0013C970; Compute_CRC 0x0013CA20; color accessors 0x0013CAB0..0x0013CD11; shininess 0x0013CD20/0x0013CD30; opacity 0x0013CD50/0x0013CD60; color sources 0x0013CD80..0x0013CE6C; UV sources 0x0013CE70/0x0013CE90; lighting 0x0006E18D/0x0012D2B0; Peek_Mapper 0x000633CA; normals 0x0015A010; Reset_Mappers/time variance 0x001820C0/0x001820F0; Clone 0x0016EAF0; Apply/Apply_Null 0x0013D570/0x0013D180; Init/Shutdown/Get_Preset 0x0013D9B0/0x0013D200/0x0013D230; RAM size 0x0013D250; material conversion 0x0013CEA0/0x0013D030/0x0013DD10; Load_W3D 0x0013E8B0 returns bool. Get_CRC uses the retail cache expression (also inlined at RVA 0x00143B15..0x00143B48). Compute_CRC, Apply, Apply_Null and Presets retain their private ledger spellings. Get_Name, Get_Flag and the DX8Wrapper friendship follow Zero Hour's declarations.

#ifndef VERTMATERIAL_H
#define VERTMATERIAL_H

#include "../WWLib/RefCountData.h"
#include "../WWLib/wwstring.h"

class ChunkLoadClass;
class DX8Wrapper;
class DynD3DMATERIAL8;
class RefCountClass;
class StringClass;
class TextureMapperClass;
class Vector3;
struct W3dMaterial3Struct;
struct W3dVertexMaterialStruct;

#define DYN_MAT8

class VertexMaterialClass : public RefCountClass
{
    friend class DX8Wrapper;

public:
    enum FlagsType { DEPTH_CUE = 0, DEPTH_CUE_TO_ALPHA, COPY_SPECULAR_TO_DIFFUSE };
    enum ColorSourceType { MATERIAL = 0, COLOR1, COLOR2 };
    enum PresetType { PRELIT_DIFFUSE = 0, PRELIT_NODIFFUSE, PRESET_COUNT };

    VertexMaterialClass();
    VertexMaterialClass(const VertexMaterialClass &src);
    virtual ~VertexMaterialClass();
    VertexMaterialClass &operator=(const VertexMaterialClass &src);
    VertexMaterialClass *Clone();

    void Set_Name(const char *name);
    const char *Get_Name() const { return Name; }
    void Set_Flag(FlagsType flag, bool onoff);
    int Get_Flag(FlagsType flag) { return (Flags >> flag) & 1; }
    float Get_Shininess() const;
    void Set_Shininess(float shin);
    float Get_Opacity() const;
    void Set_Opacity(float opacity);
    void Get_Ambient(Vector3 *color) const;
    void Set_Ambient(const Vector3 &color);
    void Set_Ambient(float r, float g, float b);
    void Get_Diffuse(Vector3 *color) const;
    void Set_Diffuse(const Vector3 &color);
    void Set_Diffuse(float r, float g, float b);
    void Get_Specular(Vector3 *color) const;
    void Set_Specular(const Vector3 &color);
    void Set_Specular(float r, float g, float b);
    void Get_Emissive(Vector3 *color) const;
    void Set_Emissive(const Vector3 &color);
    void Set_Emissive(float r, float g, float b);
    void Set_Lighting(bool lighting);
    bool Get_Lighting() const;
    void Set_Ambient_Color_Source(ColorSourceType src);
    ColorSourceType Get_Ambient_Color_Source();
    void Set_Emissive_Color_Source(ColorSourceType src);
    ColorSourceType Get_Emissive_Color_Source();
    void Set_Diffuse_Color_Source(ColorSourceType src);
    ColorSourceType Get_Diffuse_Color_Source();
    void Set_UV_Source(int stage, int array_index);
    int Get_UV_Source(int stage);
    void Set_Mapper(TextureMapperClass *mapper, int stage = 0);
    TextureMapperClass *Peek_Mapper(int stage = 0);
    void Reset_Mappers();
    bool Do_Mappers_Need_Normals() const;
    bool Are_Mappers_Time_Variant() const;
    bool Load_W3D(ChunkLoadClass &cload);
    void Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct &vmat);
    void Parse_Mapping_Args(const W3dVertexMaterialStruct &vmat, char *mapping0, char *mapping1);
    void Init_From_Material3(const W3dMaterial3Struct &mat3);
    unsigned long Get_CRC() const
    {
        if (CRCDirty) {
            CRC = Compute_CRC();
            CRCDirty = false;
        }
        return CRC;
    }
    void Make_Unique();
    int rva0013D250() const;
    static void Init();
    static void Shutdown();
    static VertexMaterialClass *Get_Preset(PresetType type);

    DynD3DMATERIAL8 *MaterialDyn;
    unsigned int Flags;
    unsigned int AmbientColorSource;
    unsigned int EmissiveColorSource;
    unsigned int DiffuseColorSource;
    StringClass Name;
    TextureMapperClass *Mapper[8];
    unsigned int UVSource[8];
    unsigned int UniqueID;
    mutable unsigned long CRC;
    mutable bool CRCDirty;
    bool UseLighting;

private:
    unsigned long Compute_CRC() const;
    void Apply() const;
    static void Apply_Null();
    static VertexMaterialClass *Presets[PRESET_COUNT];
};

typedef char VertexMaterialClassSizeCheck[sizeof(VertexMaterialClass) == 0x6C ? 1 : -1];

#endif
