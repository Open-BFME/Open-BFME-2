// cl: /Ireference/shims/meshgeom /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// Semantic donor: Generals Zero Hour meshmdlio.cpp, retained in this repo.
// The method name follows that donor; target shader tests and material accesses
// establish the corresponding fog behavior and layout.
class TextureClass { public: void Add_Ref(); void Release_Ref(); };
template<class T>
class RefCountPtr {
public:
    RefCountPtr() : Ptr(0) {}
    RefCountPtr(const RefCountPtr& other) : Ptr(other.Ptr) { if (Ptr) Ptr->Add_Ref(); }
    ~RefCountPtr() { if (Ptr) Ptr->Release_Ref(); }
    const RefCountPtr& operator=(const RefCountPtr& other);
    operator T*() const { return Ptr; }
protected:
    T *Ptr;
};

// Target-local one-pointer wrapper view. It forwards assignment through the
// donor RefCountPtr<TextureClass> owning-copy body while retaining the target
// non-const wrapper return ABI; original target wrapper name is unresolved.
class BfmeTextureHandle {
public:
    RefCountPtr<TextureClass> Handle;
    BfmeTextureHandle& operator=(const BfmeTextureHandle& other);
};

class MeshMatDescClass;
class MeshModelClass;
#include "meshgeometry.h"
#include "shader.h"
#include "vertmaterial.h"
#include "refcount.h"
#include "sharebuf.h"

class TexBufferClass {
public:
    // Target allocation passes 0x18 to operator new; opaque base semantics.
    unsigned char targetOpaqueLayout[0x18];
    TexBufferClass(int, const char*);
    RefCountPtr<TextureClass> Get_Element(int);
    void Set_Element(int, const RefCountPtr<TextureClass>&);
};
class MatBufferClass {
public:
    VertexMaterialClass *Peek_Element(int);
};

// Retail BFME2 descriptor ABI view, bounded to fields used by this method.
// Retail accesses anchor Texture at +0x78, Shader at +0x98, Material at
// +0xA8, TextureArray at +0xC8, MaterialArray at +0xE8, ShaderArray at +0xF8.
class MeshMatDescClass {
public:
    enum { MAX_PASSES = 4, MAX_TEX_STAGES = 2 };
    int PassCount;
    unsigned char opaque04[0x74];
    BfmeTextureHandle Texture[MAX_PASSES][MAX_TEX_STAGES];
    ShaderClass Shader[MAX_PASSES];
    VertexMaterialClass *Material[MAX_PASSES];
    RefCountClass *OpaquePassBuffers[MAX_PASSES];
    TexBufferClass *TextureArray[MAX_PASSES][MAX_TEX_STAGES];
    MatBufferClass *MaterialArray[MAX_PASSES];
    ShareBufferClass<ShaderClass> *ShaderArray[MAX_PASSES];
    RefCountClass *OpaqueTailBuffers[MAX_PASSES];
    int Get_Pass_Count() const { return PassCount; }
};
typedef char VerifyBfmeTextureHandleSize[(sizeof(BfmeTextureHandle) == 4) ? 1 : -1];
typedef char VerifyTexBufferSize[(sizeof(TexBufferClass) == 0x18) ? 1 : -1];
typedef char VerifyMeshMatDescSize[(sizeof(MeshMatDescClass) == 0x118) ? 1 : -1];

// Minimal source-owner views: field offsets are target disassembly anchors.
class MeshModelClass : public MeshGeometryClass {
public:
    MeshMatDescClass *DefMatDesc;
protected:
    void post_process_fog(void);
};

void MeshModelClass::post_process_fog(void)
{
	// If two pass...
	if (DefMatDesc->Get_Pass_Count() == 2) {

		// If single shader on both passes...
		if (!DefMatDesc->ShaderArray[0] && !DefMatDesc->ShaderArray[1]) {

			ShaderClass &shader0 = DefMatDesc->Shader [0];
			ShaderClass &shader1 = DefMatDesc->Shader [1];

			// Analyze the mesh to determine if it is the emissive map effect and if it is, fix it up appropriately.
			bool emissive_map_effect = DefMatDesc->PassCount == 2 &&
												shader0.Get_Texturing() == ShaderClass::TEXTURING_DISABLE &&
												shader0.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
												shader0.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ZERO &&
												shader0.Get_Primary_Gradient() == ShaderClass::GRADIENT_MODULATE &&
												shader0.Get_Secondary_Gradient() == ShaderClass::SECONDARY_GRADIENT_DISABLE &&
												shader1.Get_Texturing() == ShaderClass::TEXTURING_ENABLE &&
												shader1.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_SRC_ALPHA &&
												shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_SRC_COLOR;

			if (emissive_map_effect) {

				// Change the shader/texture setting into an equivalent one which will enable setting fog
				// correctly: Note that we are setting up pass 0 to have a texture now.
				shader0.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
				shader1.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);
				shader0.Set_Fog_Func(ShaderClass::FOG_ENABLE);
				shader1.Set_Fog_Func(ShaderClass::FOG_SCALE_FRAGMENT);

				// Copy pass 1 texture/texture array to pass 0.
				DefMatDesc->Texture[0][0] = DefMatDesc->Texture[1][0];
				if (DefMatDesc->TextureArray [1][0]) {
					if (!DefMatDesc->TextureArray [0][0]) {
						DefMatDesc->TextureArray [0][0] = NEW_REF (TexBufferClass, (PolyCount, "MeshModelClass::DefMatDesc::TextureArray"));
						for (int i = 0; i < PolyCount; i++) {
							DefMatDesc->TextureArray [0][0]->Set_Element (i, DefMatDesc->TextureArray [1][0]->Get_Element (i));
						}
					}
				}

				// Make pass 0 point to the same UV array as pass 1. If pass 1 has a vertex material
				// array, we only take the first one for determining UV source. The UV source is
				// used to set the UV source of all the vertex materials in pass 0.
				int uv_source = 0;
				if (DefMatDesc->MaterialArray[1]) {
					uv_source = DefMatDesc->MaterialArray[1]->Peek_Element(0)->Get_UV_Source(0);
				} else {
					// Retail donor calls this accessor but discards its return value.
					// Retail donor calls this accessor but discards its return value.
					DefMatDesc->Material[1]->Get_UV_Source(0);
				}
				if (DefMatDesc->MaterialArray[0]) {
					for (int i = 0; i < VertexCount; i++) {
						DefMatDesc->MaterialArray[0]->Peek_Element(i)->Set_UV_Source(0, uv_source);
					}
				} else {
					DefMatDesc->Material[0]->Set_UV_Source(0, uv_source);
				}

				return;
			}

			// Analyze the mesh to determine if it is the shiny mask effect and if it is, fix it up appropriately.
			bool shiny_mask_effect = shader0.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
											 shader0.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ZERO &&
											 shader1.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
											(shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_SRC_ALPHA ||
											 shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA);

			if (shiny_mask_effect) {
				shader0.Set_Fog_Func(ShaderClass::FOG_SCALE_FRAGMENT);
				shader1.Set_Fog_Func(ShaderClass::FOG_ENABLE);
				return;
			}
		}
	}

	// Mesh is not one of the special two-pass combinations. Apply a per-pass generic fix-up.
	for (int pass = 0; pass < DefMatDesc->PassCount; pass++) {
		DefMatDesc->Shader [pass].Enable_Fog (Get_Name());
		if (DefMatDesc->ShaderArray [pass]) {
			for (int tri = 0; tri < DefMatDesc->ShaderArray [pass]->Get_Count(); tri++) {
				DefMatDesc->ShaderArray [pass]->Get_Element (tri).Enable_Fog (Get_Name());
			}
		}
	}
}
