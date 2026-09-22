// cl: /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/shims/sweep
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

// BFME1 converted donor: Find_Matching_Texture_Category texture overload.
// Retail boundary 0x1450E0/419 is called by the pinned texture migration
// routine at 0x146200. That routine also calls the matched owning texture
// getter at 0x143400. The getter establishes texture slots at category +0x0C
// and a WORD resource refcount at +4; the matched shader getter at 0x143440
// supports shader access at category +0x14. Handle and class labels below
// remain donor-model inferences.

#include "multilist.h"

class TextureClass
{
public:
	void Release_Ref();
};

class BfmeHandleCX
{
public:
	TextureClass *p;

	~BfmeHandleCX(void)
	{
		if (p)
			p->Release_Ref();
	}
	bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
};

inline bool operator==(TextureClass *left, const BfmeHandleCX &right)
{
	return left == right.p;
}

struct BFME2TextureResource { unsigned Vtable; unsigned short Refs; void Release_Ref(); };
struct BFME2TextureRef {
 BFME2TextureResource* Ptr;
 BFME2TextureRef(BFME2TextureResource* p):Ptr(p) { if(Ptr) ++Ptr->Refs; }
 BFME2TextureRef(const BFME2TextureRef& p):Ptr(p.Ptr) { if(Ptr) ++Ptr->Refs; }
 ~BFME2TextureRef() { if(Ptr) Ptr->Release_Ref(); }
};

class BFME2TextureCategory
{
public:
    // The matched getter only loads a pointer and increments its reference count.
    BFME2TextureRef Get_Texture(int stage) throw();
};

inline bool operator==(const BFME2TextureRef &left, const BfmeHandleCX &right)
{
    return reinterpret_cast<TextureClass *>(left.Ptr) == right.p;
}

inline bool operator==(const BFME2TextureRef &left, const BFME2TextureRef &right)
{
    return left.Ptr == right.Ptr;
}

class VertexMaterialClass
{
	unsigned char pad[0x64];
	mutable unsigned long CRC;
	mutable bool CRCDirty;
	unsigned long Compute_CRC() const;

public:
	unsigned long Get_CRC() const
	{
		if (CRCDirty) {
			CRC = Compute_CRC();
			CRCDirty = false;
		}
		return CRC;
	}
};

class ShaderClass
{
public:
	unsigned int ShaderBits;
};

class DX8PolygonRendererClass;
class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	const VertexMaterialClass *Peek_Material() const { return material; }
	unsigned int Get_Shader_Bits() const { return shader.ShaderBits; }

private:
	int pass;
	TextureClass *textures[2];
	ShaderClass shader;
	VertexMaterialClass *material;
	MultiListClass<DX8PolygonRendererClass> polygon_renderer_list;
};

typedef MultiListClass<DX8TextureCategoryClass> TextureCategoryList;
typedef MultiListIterator<DX8TextureCategoryClass> TextureCategoryListIterator;

class DX8FVFCategoryContainer : public MultiListObjectClass
{
protected:
	DX8TextureCategoryClass *Find_Matching_Texture_Category(
		const BfmeHandleCX &texture,
		unsigned pass,
		unsigned stage,
		DX8TextureCategoryClass *ref_category);

private:
	TextureCategoryList texture_category_list[4];
};

inline static bool Equal_Material(const VertexMaterialClass *mat1,
	const VertexMaterialClass *mat2)
{
	unsigned int crc0 = mat1 ? mat1->Get_CRC() : 0;
	unsigned int crc1 = mat2 ? mat2->Get_CRC() : 0;
	return crc0 == crc1;
}

DX8TextureCategoryClass *DX8FVFCategoryContainer::Find_Matching_Texture_Category(
	const BfmeHandleCX &texture,
	unsigned pass,
	unsigned stage,
	DX8TextureCategoryClass *ref_category)
{
	DX8TextureCategoryClass *dest_tex_category = NULL;
	TextureCategoryListIterator dest_it(&texture_category_list[pass]);
	while (!dest_it.Is_Done()) {
		if (reinterpret_cast<BFME2TextureCategory *>(dest_it.Peek_Obj())->Get_Texture(stage) == texture) {
			dest_tex_category = dest_it.Peek_Obj();
			bool all_textures_same = true;
			for (unsigned int s = 0; s < 2; ++s) {
				if (stage != s) {
					all_textures_same = all_textures_same &&
						(reinterpret_cast<BFME2TextureCategory *>(dest_tex_category)->Get_Texture(s) ==
						 reinterpret_cast<BFME2TextureCategory *>(ref_category)->Get_Texture(s));
				}
			}
			if (all_textures_same &&
				Equal_Material(dest_tex_category->Peek_Material(), ref_category->Peek_Material()) &&
				dest_tex_category->Get_Shader_Bits() == ref_category->Get_Shader_Bits())
				return dest_tex_category;
		}
		dest_it.Next();
	}
	return NULL;
}
