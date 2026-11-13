// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Donor: BFME1 WW3D2/dx8renderer.cpp, container-first constructor.
// Matched Insert_To_Texture_Category calls target144A00 with this argument order.
// Target fields: pass8, texturesC/10, shader14, material18, list1C, container34.
// Texture references use a 16-bit count at+4; material references use 32 bits.

class MultiListObjectClass;
class GenericMultiListClass;

#include "../WWLib/GenericMultiListClass.h"

#include "../WWLib/MultiListObjectClass.h"

// Only the derived member list is constructed; retail stores its vptr.

class TextureClass
{
public:
	virtual void Delete_This() = 0;
	// Preserve inline increments without emitting a competing external copy.
	__declspec(dllimport) __forceinline void Add_Ref() { ++NumRefs; }
	unsigned short NumRefs;
	void Release_Ref();
};

template <class T> class RefCountPtr
{
public:
	RefCountPtr(); // The array callback uses the rowed six-byte constructor.
	~RefCountPtr();
	T *Referent;
};

// Native array initialization uses the same six-byte callback as the
// material/texture migration units (326BE6).
#pragma optimize("t", off)
template<> inline RefCountPtr<TextureClass>::RefCountPtr() : Referent(0) {}
#pragma optimize("", on)

#include "VertexMaterialClass.h"

class DX8PolygonRendererClass;
class DX8FVFCategoryContainer;
#include "ShaderClass.h"

// Member +1C installs table BD34E0 and unwinds to 144690; use that
// existing opaque provider without asserting the list's original type name.
#include "../../../../GameEngine/Include/Common/Rva00144690.h"

class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	DX8TextureCategoryClass(DX8FVFCategoryContainer *container_, TextureClass **textures_,
		ShaderClass shader_, VertexMaterialClass *material_, int pass_);
	virtual ~DX8TextureCategoryClass();
private:
	int pass;
	RefCountPtr<TextureClass> textures[2];
	ShaderClass shader;
	VertexMaterialClass *material;
	Rva00144690 PolygonRendererList;
	DX8FVFCategoryContainer *container;
	void *render_task_head;
};

// Target container-first call order. The 16-bit Add_Ref and old-texture release
// branch follow target code; RefCountPtr here models its 4-byte texture slots.
DX8TextureCategoryClass::DX8TextureCategoryClass(DX8FVFCategoryContainer *container_, TextureClass **textures_,
	ShaderClass shader_, VertexMaterialClass *material_, int pass_)
	: pass(pass_), shader(shader_), material(material_), container(container_), render_task_head(0)
{
	for (int index = 0; index < 2; ++index) {
		if (textures_[index] != 0)
			textures_[index]->Add_Ref();
		if (textures[index].Referent != 0)
			textures[index].Referent->Release_Ref();
		textures[index].Referent = textures_[index];
	}
	if (material != 0)
		material->Add_Ref();
}
