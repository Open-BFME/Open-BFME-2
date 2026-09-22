// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/Compression
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
#include "w3d_file.h"
#include "wwstring.h"
#include "shader.h"
#include "vector.h"

class VertexMaterialClass {
public:
    virtual void Delete_This();
    void Add_Ref() { ++RefCount; }
    unsigned long Get_CRC() const {
        if (CRCDirty) {
            CRC = Compute_CRC();
            CRCDirty = false;
        }
        return CRC;
    }
private:
    int RefCount;
    unsigned char beforeCRC[0x64 - 8];
    mutable unsigned long CRC;
    mutable bool CRCDirty;
    unsigned long Compute_CRC() const;
};

class TextureClass {
public:
    void Add_Ref() {
        ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
    }
    void Release_Ref();
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

// Declaration-only local view of the already matched target getter. Its
// pointer-at-zero shape is supported by the donor handle and target call sites.
class BFME2ParticleTextureHandle {
public:
    TextureClass *Ptr;
    StringClass Get_Texture_Name() const;
};

class MeshLoadContextClass {
    struct LegacyMaterialClass {
        StringClass Name;
        int VertexMaterialIdx;
        int ShaderIdx;
        int TextureIdx;
        LegacyMaterialClass() : VertexMaterialIdx(0), ShaderIdx(0), TextureIdx(0) {}
    };
    unsigned char beforeLegacyMaterials[0x94];
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
