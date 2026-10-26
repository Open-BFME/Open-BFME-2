// cl: /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/build/toolchains/dx81/include
// ?Collect_Materials@MaterialCollectorClass@@QAEXPAVMeshModelClass@@@Z, retail 0x001703D0, 1238 B.
// Built from the banked reconstruction (reverse/attempts history). The texture-site
// DynamicVectorClass<RefCountPtr<TextureClass> >::Add is specialized here so its growth
// sum reads GrowthStep into a local first: retail adds into the Length() register
// (add ecx,eax / push ecx), which the shared vector.h spelling compiles the other way.
// Reconstruction of MaterialCollectorClass::Collect_Materials, 0x1703D0, 1238 bytes.
// Donor: Open-BFME-1 1281192f68 game/.../WW3D2/matinfo.cpp; BFME2 owning
// texture operations from MaterialCollectorAddTexture.cpp. Target offsets
// and the complete loops are independently read from retail. Four bytes
// differ: two Resize sums use EAX instead of ECX. Original and reversed sum
// order, and an explicit newSize temporary all emitted the same residue.
// Visible noinline Get_Single_Texture + Peek_Single_Texture are necessary:
// declaration-only versions caused extra alias reloads in the single path.
#include <new>
// The toolchain header supplies allocation declarations and placement bodies;
// suppress the older copies in the donor's always.h for this TU.
#define _OPERATOR_NEW_DEFINED_
#include "shader.h"
#include "vector.h"
// Reset accesses the target's RefCountClass prefix only.
class VertexMaterialClass {
public:
    virtual void Delete_This();
    void Add_Ref() { ++m_refs; }
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

template<class T> class RefCountPtr {
public:
    T *p;
    RefCountPtr() : p(0) {}
    __declspec(dllimport) __forceinline RefCountPtr(const RefCountPtr &other) : p(other.p) {
        if (p) p->Add_Ref();
    }
    ~RefCountPtr() {
        if (p) p->Release_Ref();
    }
    RefCountPtr &operator=(const RefCountPtr &other) {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p = other.p;
        return *this;
    }
    bool operator==(const RefCountPtr &other) const { return p == other.p; }
    bool operator!=(const RefCountPtr &other) const { return p != other.p; }
};
// Inlined everywhere here; dllimport keeps this TU's /O2 copy out of the object so
// the link uses the retail-proven out-of-line copy.
template <> __declspec(dllimport) __forceinline
RefCountPtr<TextureClass>::RefCountPtr(const RefCountPtr<TextureClass> &other) : p(other.p) {
    if (p) p->Add_Ref();
}


class MeshMatDescClass {
public:
    int PassCount;
    char padToTexture[0x74];
    RefCountPtr<TextureClass> Texture[4][2];
    ShaderClass Shader[4];
    VertexMaterialClass *Material[4];
    char padToTextureArray[0x10];
    void *TextureArray[4][2];
    void *MaterialArray[4];
    void *ShaderArray[4];
    VertexMaterialClass *Peek_Material(int index, int pass) const;
    ShaderClass Get_Shader(int index, int pass) const;
    __declspec(noinline) RefCountPtr<TextureClass> Get_Single_Texture(int pass,int stage) const { return Texture[pass][stage]; }
    VertexMaterialClass *Get_Single_Material(int pass) const {
        if (Material[pass]) Material[pass]->Add_Ref();
        return Material[pass];
    }
};
class MeshModelClass {
    char padToPolyCount[0x24];
    int PolyCount, VertexCount;
    char padToDesc[0x68];
    MeshMatDescClass *CurMatDesc;
public:
    int Get_Pass_Count() const { return CurMatDesc->PassCount; }
    int Get_Vertex_Count() const { return VertexCount; }
    int Get_Polygon_Count() const { return PolyCount; }
    bool Has_Material_Array(int pass) const { return CurMatDesc->MaterialArray[pass] != 0; }
    bool Has_Shader_Array(int pass) const { return CurMatDesc->ShaderArray[pass] != 0; }
    bool Has_Texture_Array(int pass,int stage) const { return CurMatDesc->TextureArray[pass][stage] != 0; }
    VertexMaterialClass *Peek_Material(int index,int pass) const { return CurMatDesc->Peek_Material(index,pass); }
    VertexMaterialClass *Get_Single_Material(int pass) const {
        return CurMatDesc->Get_Single_Material(pass);
    }
    // This view is inlined; keep the standalone retail helper with its owner.
    __declspec(dllimport) __forceinline ShaderClass Get_Shader(int index,int pass) const { return CurMatDesc->Get_Shader(index,pass); }
    ShaderClass Get_Single_Shader(int pass) const { return CurMatDesc->Shader[pass]; }
    RefCountPtr<TextureClass> Peek_Texture(int index,int pass,int stage) const;
    __declspec(noinline) RefCountPtr<TextureClass> Peek_Single_Texture(int pass,int stage) const { return CurMatDesc->Get_Single_Texture(pass,stage); }
};
template<> inline bool DynamicVectorClass<RefCountPtr<TextureClass> >::Add(RefCountPtr<TextureClass> const & object)
{
	if (ActiveCount >= Length()) {
		if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
			int growth = GrowthStep;
			if (!Resize(Length() + growth)) {
				return(false);
			}
		} else {
			return(false);
		}
	}
	(*this)[ActiveCount++] = object;
	return(true);
}
class MaterialCollectorClass {
public:
    void Collect_Materials(MeshModelClass *);
    void Add_Texture(const RefCountPtr<TextureClass> &texture) {
        if (!texture.p || texture.p == LastTexture.p) return;
        if (Find_Texture(texture.p) != -1) return;
        Textures.Add(texture);
        LastTexture = texture;
    }
    int Find_Texture(TextureClass *texture) const {
        for (int i=0; i<Textures.Count(); ++i) if (Textures[i].p == texture) return i;
        return -1;
    }
    void Add_Vertex_Material(VertexMaterialClass *vmat) {
        if (!vmat || vmat == LastMaterial) return;
        if (Find_Vertex_Material(vmat) != -1) return;
        VertexMaterials.Add(vmat);
        vmat->Add_Ref();
        LastMaterial = vmat;
    }
    int Find_Vertex_Material(VertexMaterialClass *vmat) {
        for (int i=0; i<VertexMaterials.Count(); ++i) if (VertexMaterials[i] == vmat) return i;
        return -1;
    }
    void Add_Shader(ShaderClass shader) {
        if (shader == LastShader) return;
        if (Find_Shader(shader) != -1) return;
        Shaders.Add(shader);
        LastShader = shader;
    }
    int Find_Shader(const ShaderClass &shader) {
        for (int i=0; i<Shaders.Count(); ++i) if (Shaders[i] == shader) return i;
        return -1;
    }
private:
    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    DynamicVectorClass<RefCountPtr<TextureClass> > Textures;
    ShaderClass LastShader;
    VertexMaterialClass *LastMaterial;
    RefCountPtr<TextureClass> LastTexture;
};
void MaterialCollectorClass::Collect_Materials(MeshModelClass * mesh)
{
	for (int pass = 0;pass < mesh->Get_Pass_Count(); pass++) {

		// Vertex materials (either single or per vertex)
		if (mesh->Has_Material_Array(pass)) {

			for (int vert_index = 0;vert_index < mesh->Get_Vertex_Count(); vert_index++) {
				VertexMaterialClass * mat = mesh->Peek_Material(vert_index,pass);
				Add_Vertex_Material(mat);
			}

		} else {
			VertexMaterialClass * mat = mesh->Get_Single_Material(pass);
			Add_Vertex_Material(mat);
			if (mat) { mat->Release_Ref(); mat = 0; }
		}


		// Shaders (single or per poly...)
		if (mesh->Has_Shader_Array(pass)) {
			for (int poly_index=0; poly_index < mesh->Get_Polygon_Count(); poly_index++) {
				Add_Shader(mesh->Get_Shader(poly_index,pass));
			}
		} else {
			ShaderClass sh = mesh->Get_Single_Shader(pass);
			Add_Shader(sh);
		}


		// Textures per pass, per stage (either array or single...)
		for (int stage = 0; stage < 2; stage++) {

			if (mesh->Has_Texture_Array(pass,stage)) {

				for (int poly_index = 0;poly_index < mesh->Get_Polygon_Count(); poly_index++) {
					RefCountPtr<TextureClass> tex = mesh->Peek_Texture(poly_index,pass,stage);
					Add_Texture(tex);
				}

			} else {

				RefCountPtr<TextureClass> tex = mesh->Peek_Single_Texture(pass,stage);
				Add_Texture(tex);

			}
		}
	}
}
