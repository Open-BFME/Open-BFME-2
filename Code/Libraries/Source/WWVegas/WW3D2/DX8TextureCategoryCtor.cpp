// cl: /G7 /DNDEBUG /MD /EHsc
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

class MultiListNodeClass
{
public:
	MultiListNodeClass()
	{
		Prev = Next = NextList = 0;
		Object = 0;
		List = 0;
	}
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
	GenericMultiListClass *List;
};

class MultiListObjectClass
{
public:
	MultiListObjectClass() : ListNode(0) {}
	virtual ~MultiListObjectClass();
private:
	MultiListNodeClass *ListNode;
};

class GenericMultiListClass
{
public:
	GenericMultiListClass()
	{
		Head.Next = Head.Prev = &Head;
		Head.Object = 0;
		Head.NextList = 0;
	}
	virtual ~GenericMultiListClass();
private:
	MultiListNodeClass Head;
};

template <class T> class MultiListClass : public GenericMultiListClass
{
public:
	MultiListClass() {}
	virtual ~MultiListClass();
};

class TextureClass
{
public:
	virtual void Delete_This() = 0;
	void Add_Ref() { ++NumRefs; }
	unsigned short NumRefs;
	void Release_Ref();
};

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0) {
			Referent->Release_Ref();
			Referent = 0;
		}
	}
	T *Referent;
};

class VertexMaterialClass
{
public:
	virtual void Delete_This() = 0;
	void Add_Ref() { ++NumRefs; }
	int NumRefs;
};

class DX8PolygonRendererClass;
class DX8FVFCategoryContainer;
class ShaderClass { public: unsigned ShaderBits; };

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
	MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
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
