// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/Compression
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
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// Donor implementation: BFME1 MeshLoadContextClass::Add_Legacy_Material in
// WW3D2/MeshLoadContextAddLegacyMaterial.cpp, derived from meshmdlio.cpp. Target identity
// is supported by the version-3 material reader at 0x18A750 calling this at
// 0x18AB73, and that reader's 0x15 chunk dispatch at 0x18B80A. The target
// body is 896 bytes, ending at RET 12 at 0x18A6ED (exclusive end 0x18A6F0).
// Target member accesses place DynamicVectorClass Textures at +0x10C, with
// data at +0x110 and count at +0x11C; the preceding context vectors remain
// at +0x94/+0xAC/+0xC4/+0xDC. The 0x18 gap before Textures is opaque.
// The donor BfmeHandleCX stores its pointer at +0. Target calls the existing
// BFME2ParticleTextureHandle name getter at 0x129D30 on this pointer-shaped
// view; its getter body null-checks the pointer, calls the texture name slot,
// and returns a StringClass. This view is ABI/behavioral evidence, not a claim
// that the two handle class identities are the same.
//
// MeshModelClass::read_v3_materials (0x18A750, 1336 bytes, RET 8 at +0x51B,
// cold failure tail to +0x538) follows Add_Legacy_Material in retail as in the
// BFME1 donor TU (BFME1 0x0096F5B0), whose body it ports. read_chunks reaches
// it through the 0x15 chunk dispatch. BFME2 loads map textures through
// BFME2LoadParticleTexture (0x132D89), assigns them with the owning wrapper at
// 0x42707 and drops the reference with the release-and-clear helper at
// 0x4D75B; the context Textures vector sits at +0x10C and the model's
// CurMatDesc at +0x94. Retail keeps the texture handle's pointer in EDI across
// the chunk loop and skips its cleanup on the early failures, which VC7.1 does
// only when it can see that the wrapper, the clear helper and
// Add_Legacy_Material (with the name getter it calls) never retain the
// handle's address: making any one of the three opaque reloads the pointer on
// every failure path. All three stay out of line, as in retail; the name
// getter compiles to retail's 176-byte body here, so its row lives in this TU.
#include "w3d_file.h"
#include "wwstring.h"
#include "shader.h"
#include "vector.h"
#include "vector3.h"
#include "chunkio.h"

class VertexMaterialClass {
public:
    VertexMaterialClass();
    virtual void Delete_This();
    void Add_Ref() { ++RefCount; }
    void Release_Ref() { RefCount--; if (RefCount == 0) Delete_This(); }
    void Init_From_Material3(const W3dMaterial3Struct &mat3);
    void Set_Name(const char *name) { Name = name; }
    void Set_Ambient(const Vector3 &color);
    void Get_Diffuse(Vector3 *set_color) const;
    void Set_Diffuse(const Vector3 &color);
    unsigned long Get_CRC() const {
        if (CRCDirty) {
            CRC = Compute_CRC();
            CRCDirty = false;
        }
        return CRC;
    }
private:
    int RefCount;
    unsigned char beforeName[0x1c - 8];
    StringClass Name;
    unsigned char beforeCRC[0x64 - 0x20];
    mutable unsigned long CRC;
    mutable bool CRCDirty;
    unsigned long Compute_CRC() const;
};

class TextureBaseClass {
public:
    virtual const char *Get_Name() const;
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

// Local view of the target getter at 0x129D30 (BFME1 donor
// BfmeHandleCX::Get_Texture_Name). Its pointer-at-zero shape is supported by
// the donor handle and target call sites; the name is virtual slot 0.
class BFME2ParticleTextureHandle {
public:
    TextureClass *Ptr;
    StringClass Get_Texture_Name() const {
        const char *name = Ptr ? Ptr->Get_Name() : 0;
        StringClass result(name);
        return result;
    }
    ~BFME2ParticleTextureHandle() {
        if (Ptr) Ptr->Release_Ref();
    }
};

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int, int);

template<class T> class RefCountPtr;

// Owning-assignment wrapper matched at 0x00042707 (TextureHandleAssignment.cpp).
// Defined here only so read_v3_materials can see it keeps no handle address.
class BfmeTextureHandle {
public:
    TextureClass *Ptr;
    BfmeTextureHandle &operator=(const BfmeTextureHandle &other) {
        if (other.Ptr) other.Ptr->Add_Ref();
        if (Ptr) Ptr->Release_Ref();
        Ptr = other.Ptr;
        return *this;
    }
};

// Release-and-clear helper matched at 0x0004D75B (BfmeResetTextureRefClear.cpp).
// Defined here only so read_v3_materials can see it keeps no handle address.
struct BfmeResetTextureRef {
    TextureClass *pointer;
    void clear() {
        if (pointer) {
            pointer->Release_Ref();
            pointer = 0;
        }
    }
};

class MeshLoadContextClass {
    struct LegacyMaterialClass {
        StringClass Name;
        int VertexMaterialIdx;
        int ShaderIdx;
        int TextureIdx;
        LegacyMaterialClass() : VertexMaterialIdx(0), ShaderIdx(0), TextureIdx(0) {}
    };
public:
    W3dMeshHeader3Struct Header;
private:
    unsigned char afterHeader[0x94 - sizeof(W3dMeshHeader3Struct)];
    DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    DynamicVectorClass<unsigned long> VertexMaterialCrcs;
    unsigned char opaqueTargetGapBeforeTextures[0x18];
    DynamicVectorClass<BfmeHandleCX> Textures;

    int Add_Shader(ShaderClass shader) {
        int index = Shaders.Count();
        Shaders.Add(shader);
        return index;
    }
    int Add_Vertex_Material(VertexMaterialClass *vmat) {
        vmat->Add_Ref();
        int index = VertexMaterials.Count();
        VertexMaterials.Add(vmat);
        return index;
    }
    int Add_Texture(const BfmeHandleCX &tex) {
        int index = Textures.Count();
        Textures.Add(tex);
        return index;
    }
    void Add_Legacy_Material(ShaderClass, VertexMaterialClass *, const BfmeHandleCX &);
    BfmeHandleCX Peek_Texture(int index);
    int Vertex_Material_Count() { return VertexMaterials.Count(); }
    int Texture_Count() { return Textures.Count(); }
    int Shader_Count() { return Shaders.Count(); }
    VertexMaterialClass *Peek_Vertex_Material(int index) { return VertexMaterials[index]; }
    ShaderClass Peek_Shader(int index) { return Shaders[index]; }
    friend class MeshModelClass;
};

class MeshMatDescClass {
public:
    void Set_Single_Material(VertexMaterialClass *vmat, int pass);
    void Set_Single_Shader(ShaderClass shader, int pass);
    void Set_Single_Texture(const RefCountPtr<TextureClass> &tex, int pass, int stage);
};

// Retail BFME2 accesses: Flags at +0x18 (SORT is 0x10), CurMatDesc at +0x94.
class MeshGeometryClass {
protected:
    void Set_Flag(int flag, bool onoff) { if (onoff) Flags |= flag; else Flags &= ~flag; }
    unsigned char beforeFlags[0x18];
    int Flags;
};

class MeshModelClass : public MeshGeometryClass {
public:
    enum { SORT = 0x10 };
protected:
    bool read_v3_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
    void Set_Single_Texture(const BfmeHandleCX &tex, int pass = 0, int stage = 0) { CurMatDesc->Set_Single_Texture(reinterpret_cast<const RefCountPtr<TextureClass> &>(tex), pass, stage); }
    void Set_Single_Material(VertexMaterialClass *vmat, int pass = 0) { CurMatDesc->Set_Single_Material(vmat, pass); }
    void Set_Single_Shader(ShaderClass shader, int pass = 0) { CurMatDesc->Set_Single_Shader(shader, pass); }
private:
    unsigned char beforeMatDesc[0x94 - 0x1c];
    MeshMatDescClass *CurMatDesc;
};

void MeshLoadContextClass::Add_Legacy_Material(ShaderClass shader,VertexMaterialClass * vmat,const BfmeHandleCX &tex)
{
	// create a new legacy material
	LegacyMaterialClass * mat = new LegacyMaterialClass;

	// add the shader if it is unique
	for (int si=0; si<Shaders.Count(); si++) {
		if (Shaders[si] == shader) break;
	}
	if (si == Shaders.Count()) {
		mat->ShaderIdx = Add_Shader(shader);
	} else {
		mat->ShaderIdx = si;
	}

	// add the vertex material if it is unique
	if (vmat == NULL) {
		mat->VertexMaterialIdx = -1;
	} else {
		unsigned long crc = vmat->Get_CRC();
		for (int vi=0; vi<VertexMaterialCrcs.Count(); vi++) {
			if (VertexMaterialCrcs[vi] == crc) break;
		}
		if (vi == VertexMaterials.Count()) {
			mat->VertexMaterialIdx = Add_Vertex_Material(vmat);
			VertexMaterialCrcs.Add(crc);
			WWASSERT(VertexMaterialCrcs.Count() == VertexMaterials.Count());
		} else {
			mat->VertexMaterialIdx = vi;
		}
	}

	// add the texture if it is unique
	if (tex.p == NULL) {
		mat->TextureIdx = -1;
	} else {
		for (int ti=0; ti<Textures.Count(); ti++) {
			if (Textures[ti] == tex) break;
			if (_strcmpi(
				reinterpret_cast<const BFME2ParticleTextureHandle &>(Textures[ti]).Get_Texture_Name(),
				reinterpret_cast<const BFME2ParticleTextureHandle &>(tex).Get_Texture_Name()) == 0) break;
		}
		if (ti == Textures.Count()) {
			mat->TextureIdx = Add_Texture(tex);
		} else {
			mat->TextureIdx = ti;
		}
	}

	LegacyMaterials.Add(mat);
}

bool MeshModelClass::read_v3_materials(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	for (unsigned int mi = 0; mi < context->Header.NumMaterials; ++mi) {
		if (!cload.Open_Chunk()) goto Error;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_MATERIAL3) goto Error;

		VertexMaterialClass *vmat = 0;
		ShaderClass shader(0x0010441b);
		BfmeHandleCX texture;
		char name[256];

		if (!cload.Open_Chunk()) goto Error;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_MATERIAL3_NAME) goto Error;
		cload.Read(name, cload.Cur_Chunk_Length());
		if (!cload.Close_Chunk()) goto Error;

		if (!cload.Open_Chunk()) goto Error;
		W3dMaterial3Struct material;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_MATERIAL3_INFO) goto Error;
		if (cload.Read(&material, sizeof(material)) != sizeof(material)) goto Error;
		vmat = new VertexMaterialClass;
		vmat->Init_From_Material3(material);
		vmat->Set_Name(name);
		shader.Init_From_Material3(material);
		if (shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO)
			Set_Flag(MeshModelClass::SORT, true);
		if (!cload.Close_Chunk()) goto Error;

		while (cload.Open_Chunk()) {
			if (cload.Cur_Chunk_ID() == W3D_CHUNK_MATERIAL3_DC_MAP) {
				char filename[0x200];
				if (!cload.Open_Chunk()) goto Error;
				if (cload.Cur_Chunk_ID() != W3D_CHUNK_MAP3_FILENAME) goto Error;
				if (cload.Cur_Chunk_Length() >= sizeof(filename)) goto Error;
				cload.Read(filename, cload.Cur_Chunk_Length());
				if (!cload.Close_Chunk()) goto Error;
				W3dMap3Struct mapinfo;
				if (!cload.Open_Chunk()) goto Error;
				if (cload.Cur_Chunk_ID() != W3D_CHUNK_MAP3_INFO) goto Error;
				if (cload.Read(&mapinfo, sizeof(mapinfo)) != sizeof(mapinfo)) goto Error;
				if (!cload.Close_Chunk()) goto Error;
				reinterpret_cast<BfmeTextureHandle &>(texture) = reinterpret_cast<const BfmeTextureHandle &>(BFME2LoadParticleTexture(filename, 0, 0));
				shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
			} else if (cload.Cur_Chunk_ID() == W3D_CHUNK_MATERIAL3_SI_MAP) {
				Vector3 diffuse;
				vmat->Get_Diffuse(&diffuse);
				if (diffuse == Vector3(0, 0, 0)) {
					char filename[0x200];
					if (!cload.Open_Chunk()) goto Error;
					if (cload.Cur_Chunk_ID() != W3D_CHUNK_MAP3_FILENAME) goto Error;
					if (cload.Cur_Chunk_Length() >= sizeof(filename)) goto Error;
					cload.Read(filename, cload.Cur_Chunk_Length());
					if (!cload.Close_Chunk()) goto Error;
					W3dMap3Struct mapinfo;
					if (!cload.Open_Chunk()) goto Error;
					if (cload.Cur_Chunk_ID() != W3D_CHUNK_MAP3_INFO) goto Error;
					if (cload.Read(&mapinfo, sizeof(mapinfo)) != sizeof(mapinfo)) goto Error;
					if (!cload.Close_Chunk()) goto Error;
					reinterpret_cast<BfmeTextureHandle &>(texture) = reinterpret_cast<const BfmeTextureHandle &>(BFME2LoadParticleTexture(filename, 0, 0));
					shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
					shader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);
					shader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_ONE);
					shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
				}
			}
			cload.Close_Chunk();
		}

		if (shader.Get_Texturing() == ShaderClass::TEXTURING_DISABLE) {
			Vector3 color;
			vmat->Get_Diffuse(&color);
			vmat->Set_Ambient(color);
			vmat->Set_Diffuse(Vector3(0, 0, 0));
		}
		context->Add_Legacy_Material(shader, vmat, texture);
		vmat->Release_Ref();
		reinterpret_cast<BfmeResetTextureRef &>(texture).clear();
		cload.Close_Chunk();
	}

	if (context->Vertex_Material_Count() >= 1)
		Set_Single_Material(context->Peek_Vertex_Material(0), 0);
	if (context->Texture_Count() >= 1) {
		Set_Single_Texture(context->Peek_Texture(0), 0, 0);
	}
	if (context->Shader_Count() >= 1)
		Set_Single_Shader(context->Peek_Shader(0), 0);
	return true;

Error:
	return false;
}
