// cl: /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ibuild/toolchains/dx81/include
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
// BFME MaterialCollectorClass destructor: RVA 0x00931120, full 216 bytes.
// The matched constructor at 0x00931070 establishes the three vectors at
// 0/18/30 and LastShader/LastMaterial/LastTexture at 48/4C/50. The original
// GeneralsMD destructor calls Reset; BFME then destroys its owning last
// texture and member vectors in reverse order. Actual vector.h types emit
// the retail vtable transitions and array cleanup without manual stores.
// The array element destructor route 0x00030652 -> 0x0005CC00 was checked:
// it releases a nonempty owning texture handle. Array delete is nonthrowing,
// as in the verified neighboring material destructors and retail EH states.
// RET at 0x009311F7 ends before INT3 padding at 0x009311F8.
// The former claim at 0x00C5C6A8 was retracted: it joined an array-deallocation
// unwind funclet and a separate C++ exception handler, neither this body.
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

class MaterialCollectorClass {
public:
    ~MaterialCollectorClass();
    void Reset();
private:
    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    DynamicVectorClass<BfmeHandleCX> Textures;
    ShaderClass LastShader;
    VertexMaterialClass *LastMaterial;
    BfmeHandleCX LastTexture;
};
MaterialCollectorClass::~MaterialCollectorClass() { Reset(); }

// Reference matinfo.cpp Reset adapted for BFME2's owning texture-handle vector.
// Target Reset at 0x16F460 releases raw vertex-material references explicitly,
// then clears texture, vertex-material, and shader vectors.
void MaterialCollectorClass::Reset()
{
    for (int i = 0; i < VertexMaterials.Count(); ++i) {
        if (VertexMaterials[i]) {
            VertexMaterials[i]->Release_Ref();
            VertexMaterials[i] = 0;
        }
    }
    Textures.Clear();
    VertexMaterials.Clear();
    Shaders.Clear();
}

// Emit the Resize overrides selected by the collector's target vtables.
template class DynamicVectorClass<BfmeHandleCX>;
template class DynamicVectorClass<ShaderClass>;
