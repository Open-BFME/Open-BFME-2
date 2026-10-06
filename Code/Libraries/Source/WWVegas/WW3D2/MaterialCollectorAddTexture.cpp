// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/build/toolchains/dx81/include
// BFME MaterialCollectorClass::Add_Texture: RVA 0x0016FC70, 96 bytes, between
// the collector's VectorClass<ShaderClass> ctor (0x16FB40) and Add_Shader
// (0x16FCD0). Donor: BFME1 matinfo.cpp (Open-BFME-1 08718ef48), whose
// collector takes the owning texture handle by reference; placed by masked
// byte search of that body. Layout from the matched ctor/dtor (see
// MaterialCollectorDestructor.cpp); handle type name is a donor placeholder.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
void __cdecl operator delete[](void *) throw();
#include "shader.h"
#include "vector.h"
// Reset accesses the target's RefCountClass prefix only.
class VertexMaterialClass {
public:
    virtual void Delete_This();
    void Release_Ref() { --m_refs; if (m_refs == 0) Delete_This(); }
private:
    unsigned int m_refs;
};
class TextureBaseClass {
public:
    void Add_Ref() {
        ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
    }
    void Release_Ref();
};

class TextureClass : public TextureBaseClass {
};

class BfmeHandleCX {
public:
    TextureClass *p;
    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) {
        if (p) p->Add_Ref();
    }
    ~BfmeHandleCX() {
        if (p) p->Release_Ref();
    }
    BfmeHandleCX &operator=(const BfmeHandleCX &other) {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p = other.p;
        return *this;
    }
    bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
    bool operator!=(const BfmeHandleCX &other) const { return p != other.p; }
};

class MaterialCollectorClass {
public:
    void Add_Texture(const BfmeHandleCX &texture);
private:
    int Find_Texture(TextureClass *texture) const
    {
        for (int i = 0; i < Textures.Count(); ++i) {
            if (Textures[i].p == texture) return i;
        }
        return -1;
    }

    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    DynamicVectorClass<BfmeHandleCX> Textures;
    ShaderClass LastShader;
    VertexMaterialClass *LastMaterial;
    BfmeHandleCX LastTexture;
};

void MaterialCollectorClass::Add_Texture(const BfmeHandleCX &texture)
{
    if (texture.p == 0) return;
    if (texture.p == LastTexture.p) return;
    if (Find_Texture(texture.p) != -1) return;
    Textures.Add(texture);
    LastTexture = texture;
}
