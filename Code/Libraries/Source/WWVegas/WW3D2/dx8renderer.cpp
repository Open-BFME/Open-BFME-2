// cl: /Ireference/shims/bfmeshader /FIshader.h /Ireference/shims/meshgeom /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/bfmestages /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Bind the UV accessor to the separately matched native D1F40 owner.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define BFME_MESHMATDESC_UV_ARRAY_EXTERNAL
// Keep native color-array calls bound to the separately matched D1FBD owner.
#define BFME_MESHMATDESC_COLOR_ARRAY_EXTERNAL
// Link view first: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
// multilist.h's inline members are retail's size-optimised bodies: compile
// them for size (as hlod.cpp/decalsys.cpp do) so this unit's copies match.
#pragma optimize("s", on)
#include "multilist.h"
#pragma optimize("", on)
#include "refcount.h"
#pragma optimize("", on)
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp); this unit had no counterpart under Code/.

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#include "Vector.H"
#include "vector3.h"
// Retail keeps one VectorClass<Vector3>::Resize (0x000F0BF1); this unit calls it.
template <> bool VectorClass<Vector3>::Resize(int newsize, Vector3 const * array);
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "dx8wrapper.h"	// first, so the bfmestages copy (sixteen texture stages) wins
				// DX8_WRAPPER_H before a vendored header's quoted include does
// Reuse the verified BFME2 base layout so emitted MeshModelClass
// helpers read CurMatDesc at +0x94, as their retail providers do.
#include "../../../../../reference/shims/meshgeom/meshgeometry.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "../../../../../reference/shims/meshmatdesclayout/meshmatdesc.h"	// BFME2 MeshMatDescClass layout wins the include guard (TextureArray +0xC8)
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/dx8renderer.cpp                        $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/27/02 1:27p                                              $*
 *                                                                                             *
 *                    $Revision:: 111                                                         $*
 *                                                                                             *
 * 06/27/02 KM Changes to max texture stage caps																*
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//#define ENABLE_CATEGORY_LOG
//#define ENABLE_STRIPING

#include "dx8renderer.h"
#include "dx8wrapper.h"
// Zero Hour's dx8polygonrenderer.h class, with Render and Render_Sorted
// declared instead of carrying Zero Hour's inline bodies. BFME 2's bodies are
// different: each opens a render-event scope (BFME2ScopedRenderEvent around a
// "Rendering mesh"/"Rendering sorted mesh" label) and passes 32-bit draw
// ranges; retail keeps them out of line at 0x00143630 (bfme2_polygon_render.cpp)
// and 0x00143770 (bfme2_polygon_render_sorted.cpp), and the texture-category
// render at 0x00147xxx calls both. This unit only calls them, so it must not
// emit Zero Hour's copies (the link kept this unit's Render ahead of retail's).
#include "meshgeometry.h"	// the meshgeom shim (retail sizeof(MeshGeometryClass) 0x8C) has to win the include guard before meshmdl.h, or MeshModelClass's CurMatDesc lands at +0x98 instead of +0x94
#include "meshmdl.h"
#include "dx8list.h"
#include "sortingrenderer.h"
#include "mesh.h"
#define DX8_POLYGON_RENDERER_H
class DX8PolygonRendererClass;
class DX8TextureCategoryClass;
class DX8PolygonRendererClass : public MultiListObjectClass
{
	MeshModelClass *				mmc;
	DX8TextureCategoryClass *	texture_category;
	unsigned							index_offset;				// absolute index of index 0 for our parent mesh
	unsigned							vertex_offset;				// absolute index of vertex 0 for our parent mesh
	unsigned							index_count;				// number of indices
	unsigned							min_vertex_index;			// relative index of the first vertex our polys reference
	unsigned							vertex_index_range;		// range to the last vertex our polys reference
	bool								strip;						// is this a strip?
	unsigned							pass;					// rendering pass

public:
	DX8PolygonRendererClass(
		unsigned index_count,
		MeshModelClass* mmc_,
		DX8TextureCategoryClass* tex_cat,
		unsigned vertex_offset,
		unsigned index_offset,
		bool strip,
		unsigned pass);
	DX8PolygonRendererClass(const DX8PolygonRendererClass& src,MeshModelClass* mmc_);
	~DX8PolygonRendererClass();

	void								Render(/*const Matrix3D & tm,*/int base_vertex_offset);
	void								Render_Sorted(/*const Matrix3D & tm,*/int base_vertex_offset,const SphereClass & bounding_sphere);
	void								Set_Vertex_Index_Range(unsigned min_vertex_index_,unsigned vertex_index_range_)
	{
		min_vertex_index=min_vertex_index_;
		vertex_index_range=vertex_index_range_;
	}

	unsigned							Get_Vertex_Offset(void)	{ return vertex_offset; }
	unsigned							Get_Index_Offset(void)	{ return index_offset; }
	inline unsigned						Get_Pass(void)	{ return pass; }

	MeshModelClass*				Get_Mesh_Model_Class() { return mmc; }
	DX8TextureCategoryClass*	Get_Texture_Category() { return texture_category; }
	void								Set_Texture_Category(DX8TextureCategoryClass* tc) { texture_category=tc; }

	void Log();
};
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8fvf.h"
#include "dx8caps.h"
#include "dx8rendererdebugger.h"
#include "wwdebug.h"
#include "wwprofile.h"
#include "wwmemlog.h"
#include "rinfo.h"
#include "statistics.h"
#include "meshmdl.h"
#include "vp.h"
#include "decalmsh.h"
#include "matpass.h"
#include "camera.h"
#include "stripoptimizer.h"
#include "meshgeometry.h"
// bfme link decl-only begin
template <> VectorClass<Vector3>::VectorClass(int, Vector3 const *);
// bfme link decl-only end

/*
** Global Instance of the DX8MeshRender
*/
DX8MeshRendererClass TheDX8MeshRenderer;
bool DX8TextureCategoryClass::m_gForceMultiply = false; // Forces opaque materials to use the multiply blend - pseudo transparent effect.  jba.
// ----------------------------------------------------------------------------

static DynamicVectorClass<Vector3>				_TempVertexBuffer;
static DynamicVectorClass<Vector3>				_TempNormalBuffer;

static MultiListClass<MeshModelClass>			_RegisteredMeshList;
static TextureCategoryList							texture_category_delete_list;
static FVFCategoryList								fvf_category_container_delete_list;

// helper data structure
class PolyRemover : public MultiListObjectClass
{
public:
	DX8TextureCategoryClass *	src;
	DX8TextureCategoryClass *	dest;
	DX8PolygonRendererClass *  pr;
};

typedef MultiListClass<PolyRemover>			PolyRemoverList;
typedef MultiListIterator<PolyRemover>		PolyRemoverListIterator;

#define VERTEX_BUFFER_OVERFLOW	0xffff		//'Generals' flag to signal when a mesh didn't fit in streaming vertex buffer.

/**
** PolyRenderTaskClass
** This is a record of a polyrendere that needs to be rendered
** for this frame.  Since MeshClass instances can share meshmodels
** (and therefore their dx8 polygon renderers) this record contains
** a pointer to the polygon renderer and the MeshClass instance that
** it is being rendered for. 
*/
class PolyRenderTaskClass : public AutoPoolClass<PolyRenderTaskClass, 256>
{
public:
	PolyRenderTaskClass(DX8PolygonRendererClass * p_renderer,MeshClass * p_mesh) :
		Renderer(p_renderer),
		Mesh(p_mesh),
		NextVisible(NULL)
	{
		WWASSERT(Renderer != NULL);
		WWASSERT(Mesh != NULL);
		Mesh->Add_Ref();
	}

	~PolyRenderTaskClass(void)
	{
		Mesh->Release_Ref();
	}

	DX8PolygonRendererClass *	Peek_Polygon_Renderer(void)							{ return Renderer; }
	MeshClass *						Peek_Mesh(void)											{ return Mesh; }

	PolyRenderTaskClass *		Get_Next_Visible(void)									{ return NextVisible; }
	void								Set_Next_Visible(PolyRenderTaskClass * prtc)		{ NextVisible = prtc; }

protected:

	DX8PolygonRendererClass *	Renderer;
	MeshClass *						Mesh;
	PolyRenderTaskClass *		NextVisible;

};

DEFINE_AUTO_POOL(PolyRenderTaskClass, 256);

// The pool's allocator body is MatPassTaskPoolAllocateObjectMemory.cpp's row (0x001440C0).
// Instantiated here under this unit's /O2 it emitted a different external copy that,
// first in link order, won the link; declared only, this unit calls the row's body.
template<> PolyRenderTaskClass *ObjectPoolClass<PolyRenderTaskClass, 256>::Allocate_Object_Memory(void);

/**
** MatPassTaskClass
** This is the record of a material pass that needs to be rendered on
** a particular mesh.  These are linked into the FVF container which
** contains the mesh model.  They are also pooled to remove memory 
** allocation overhead.
*/
class MatPassTaskClass : public AutoPoolClass<MatPassTaskClass, 256>
{
public:
	MatPassTaskClass(MaterialPassClass * pass,MeshClass * mesh) :
		MaterialPass(pass),
		Mesh(mesh),
		NextVisible(NULL)
	{
		WWASSERT(MaterialPass != NULL);
		WWASSERT(Mesh != NULL);
		MaterialPass->Add_Ref();
		Mesh->Add_Ref();
	}

	~MatPassTaskClass(void)
	{
		MaterialPass->Release_Ref();
		Mesh->Release_Ref();
	}
	
	MaterialPassClass *	Peek_Material_Pass(void)							{ return MaterialPass; }
	MeshClass *				Peek_Mesh(void)										{ return Mesh; }
	
	MatPassTaskClass *	Get_Next_Visible(void)								{ return NextVisible; }
	void						Set_Next_Visible(MatPassTaskClass * mpr)		{ NextVisible = mpr; }

private:

	MaterialPassClass *	MaterialPass;
	MeshClass *				Mesh;
	MatPassTaskClass *	NextVisible;
};

DEFINE_AUTO_POOL(MatPassTaskClass, 256);


// ----------------------------------------------------------------------------


inline static bool Equal_Material(const VertexMaterialClass* mat1,const VertexMaterialClass* mat2)
{
	int crc0 = mat1 ? mat1->Get_CRC() : 0;
	int crc1 = mat2 ? mat2->Get_CRC() : 0;
	return (crc0 == crc1);
}


// DX8TextureCategoryClass constructor: BFME 2's body is the row 0x00144A00 in DX8TextureCategoryCtor.cpp;
// Zero Hour's copy here duplicated it.

// DX8TextureCategoryClass destructor: BFME 2's body is the row 0x00144AF0 in
// DX8TextureCategoryDtor.cpp; Zero Hour's copy here duplicated it.

void DX8TextureCategoryClass::Add_Render_Task(DX8PolygonRendererClass * p_renderer,MeshClass * p_mesh)
{
	PolyRenderTaskClass * new_prt = new PolyRenderTaskClass(p_renderer,p_mesh);
	new_prt->Set_Next_Visible(render_task_head);
	render_task_head = new_prt;

	container->Add_Visible_Texture_Category(this,pass);
}

inline void DX8TextureCategoryClass::Add_Polygon_Renderer(DX8PolygonRendererClass* p_renderer,DX8PolygonRendererClass* add_after_this)
{
	WWASSERT(p_renderer!=NULL);
	WWASSERT(!PolygonRendererList.Contains(p_renderer));

	if (add_after_this != NULL) {
		bool res = PolygonRendererList.Add_After(p_renderer,add_after_this,false);
		WWASSERT(res != NULL);
	} else {
		PolygonRendererList.Add(p_renderer);
	}

	p_renderer->Set_Texture_Category(this);
}

// DX8TextureCategoryClass::Remove_Polygon_Renderer: BFME 2's body is the row 0x001460E0 in DX8TextureCategoryRemovePolygonRenderer.cpp;
// Zero Hour's copy here duplicated it.


// Retail queues via the renderer pointer at 0x00DF363C (+0x34 list),
// null-checked, where ZH uses the file-static list below.
struct RendererFVFDeleteListView
{
	unsigned char pad[0x34];
	FVFCategoryList list;
};
extern RendererFVFDeleteListView *RendererPtr00DF363C;
void DX8FVFCategoryContainer::Remove_Texture_Category(DX8TextureCategoryClass* tex_category)
{
	for (unsigned pass=0;pass<passes;++pass) {
		texture_category_list[pass].Remove(tex_category);
	}
	for (pass=0; pass<passes; pass++) {
		// If any of the texture category lists has anything in it, no need to delete this container
		if (texture_category_list[pass].Peek_Head() != NULL) return;
	}
	RendererFVFDeleteListView *renderer = RendererPtr00DF363C;
	if (renderer)
		renderer->list.Add_Tail(this);
}

// DX8FVFCategoryContainer::Add_Visible_Material_Pass: BFME 2's body is the row 0x00144CB0 in DX8RigidDelayedMaterialPass.cpp;
// Zero Hour's copy here duplicated it.


// Owned by DX8RigidDelayedMaterialPass.cpp.

void DX8RigidFVFCategoryContainer::Render_Delayed_Procedural_Material_Passes(void)
{
	if (!Any_Delayed_Passes_To_Render()) return;
	AnyDelayedPassesToRender=false;

	DX8Wrapper::Set_Vertex_Buffer(vertex_buffer);
	DX8Wrapper::Set_Index_Buffer(index_buffer,0);

	SNAPSHOT_SAY(("DX8RigidFVFCategoryContainer::Render_Delayed_Procedural_Material_Passes()\n"));

	// additional passes
	MatPassTaskClass * mpr = delayed_matpass_head;
	while (mpr != NULL) {
	
		mpr->Peek_Mesh()->Render_Material_Pass(mpr->Peek_Material_Pass(),index_buffer);
		MatPassTaskClass * next_mpr = mpr->Get_Next_Visible();
		
		delete mpr;
		mpr = next_mpr;
	}

	delayed_matpass_head = delayed_matpass_tail = NULL;
}


// ?Log@DX8TextureCategoryClass@@ present-unmatched
void DX8TextureCategoryClass::Log(bool only_visible)
{
#ifdef ENABLE_CATEGORY_LOG
	StringClass work(255,true);
	work.Format("	DX8TextureCategoryClass\n");
	WWDEBUG_SAY((work));

	StringClass work2(255,true);
	for (int stage=0;stage<MeshMatDescClass::MAX_TEX_STAGES;++stage) {
		work2.Format("	texture[%d]: %x (%s)\n", stage, textures[stage], textures[stage] ? textures[stage]->Get_Name() : "-");
		work+=work2;
	}
	work2.Format("	material: %x (%s)\n	shader: %x\n", material, material ? material->Get_Name() : "-", shader);
	work+=work2;
	WWDEBUG_SAY((work));

	work.Format("	%8s %8s %6s %6s %6s %5s %s\n",
		"idx_cnt",
		"poly_cnt",
		"i_offs",
		"min_vi",
		"vi_rng",
		"ident",
		"name");
	WWDEBUG_SAY((work));

	DX8PolygonRendererListIterator it(&PolygonRendererList);
	while (!it.Is_Done()) {
	
		DX8PolygonRendererClass* p_renderer = it.Peek_Obj();

		PolyRenderTaskClass * prtc=render_task_head;
		while (prtc) {
			if (prtc->Peek_Polygon_Renderer()==p_renderer) break;
			prtc = prtc->Get_Next_Visible();
		}

		if (prtc != NULL) {
			WWDEBUG_SAY(("+"));
			p_renderer->Log();
		} else {
			if (!only_visible) {
				WWDEBUG_SAY(("-"));
				p_renderer->Log();
			}
		}
		it.Next();
	}
#endif
}

// ----------------------------------------------------------------------------

DX8FVFCategoryContainer::DX8FVFCategoryContainer(unsigned FVF_,bool sorting_)
	:
	FVF(FVF_),
	sorting(sorting_),
	visible_matpass_head(NULL),
	visible_matpass_tail(NULL),
	index_buffer(0),
	used_indices(0),
	passes(MAX_PASSES),
	uv_coordinate_channels(0),
	AnythingToRender(false),
	AnyDelayedPassesToRender(false)
{
	if ((FVF&D3DFVF_TEX1)==D3DFVF_TEX1) uv_coordinate_channels=1;
	if ((FVF&D3DFVF_TEX2)==D3DFVF_TEX2) uv_coordinate_channels=2;
	if ((FVF&D3DFVF_TEX3)==D3DFVF_TEX3) uv_coordinate_channels=3;
	if ((FVF&D3DFVF_TEX4)==D3DFVF_TEX4) uv_coordinate_channels=4;
	if ((FVF&D3DFVF_TEX5)==D3DFVF_TEX5) uv_coordinate_channels=5;
	if ((FVF&D3DFVF_TEX6)==D3DFVF_TEX6) uv_coordinate_channels=6;
	if ((FVF&D3DFVF_TEX7)==D3DFVF_TEX7) uv_coordinate_channels=7;
	if ((FVF&D3DFVF_TEX8)==D3DFVF_TEX8) uv_coordinate_channels=8;
}

// ----------------------------------------------------------------------------

// Target vtable slot-0 view. Retail calls the scalar deleting destructor with
// flags=0, then calls operator delete on its returned pointer; this declaration
// models only that call-site ABI, not a separate class identity.
class Rva00145000ScalarDtorSlotView
{
public:
	virtual void *scalarDelete(unsigned int flags);
};

// Target-backed destructor for DX8FVFCategoryContainer.
DX8FVFCategoryContainer::~DX8FVFCategoryContainer()
{
	// REF_PTR_RELEASE has the same refcount/delete semantics, but VC7.1 sinks
	// its null store past the loop test. The volatile lvalue keeps the
	// target-witnessed this+0xD0 clear inside the non-null branch.
	if (index_buffer) {
		index_buffer->Release_Ref();
		*reinterpret_cast<void * volatile *>(&index_buffer) = NULL;
	}

	for (unsigned p=0;p<passes;++p) {
		while (DX8TextureCategoryClass * tex = texture_category_list[p].Remove_Head()) {
			::operator delete(reinterpret_cast<Rva00145000ScalarDtorSlotView *>(tex)->scalarDelete(0));
		}
	}
}

// ----------------------------------------------------------------------------

// ?Find_Matching_Texture_Category@DX8FVFCategoryContainer@@ present-unmatched
DX8TextureCategoryClass* DX8FVFCategoryContainer::Find_Matching_Texture_Category(
	TextureClass* texture,
	unsigned pass,
	unsigned stage,
	DX8TextureCategoryClass* ref_category)
{
	// Find texture category which matches ref_category's properties but has 'texture' on given pass and stage.
	DX8TextureCategoryClass* dest_tex_category=NULL;
	TextureCategoryListIterator dest_it(&texture_category_list[pass]);
	while (!dest_it.Is_Done()) {
		if (dest_it.Peek_Obj()->Peek_Texture(stage)==texture) {
			// Compare all stage's textures
			dest_tex_category=dest_it.Peek_Obj();
			bool all_textures_same = true;
			for (unsigned int s = 0; s < MeshMatDescClass::MAX_TEX_STAGES; s++) {
				if (stage!=s) {
					all_textures_same = all_textures_same && (dest_tex_category->Peek_Texture(s) == ref_category->Peek_Texture(s));
				}
			}
			if (all_textures_same &&
				Equal_Material(dest_tex_category->Peek_Material(),ref_category->Peek_Material()) &&
				dest_tex_category->Get_Shader()==ref_category->Get_Shader()) {
				return dest_tex_category;
			}
		}
		dest_it.Next();
	}
	return NULL;
}

// Owned by DX8FVFCategoryFindMatchingMaterialBFME.cpp.

// ?Change_Polygon_Renderer_Texture@DX8FVFCategoryContainer@@ present-unmatched
void DX8FVFCategoryContainer::Change_Polygon_Renderer_Texture(
	DX8PolygonRendererList& polygon_renderer_list,
	TextureClass* texture,
	TextureClass* new_texture,
	unsigned pass,
	unsigned stage)
{
	WWASSERT(pass<passes);

	PolyRemoverList prl;

	bool foundtexture=false;

	if (texture==new_texture) return;

	// Find source texture category, then find all polygon renderers who belong to that category
	// and move them to destination category.
	TextureCategoryListIterator src_it(&texture_category_list[pass]);
	while (!src_it.Is_Done()) {
		DX8TextureCategoryClass* src_tex_category=src_it.Peek_Obj();		
		if (src_tex_category->Peek_Texture(stage)==texture) {
			foundtexture=true;
			DX8PolygonRendererListIterator poly_it(&polygon_renderer_list);
			while (!poly_it.Is_Done()) {
				// If source texture category contains polygon renderer, move to destination category
				DX8PolygonRendererClass* polygon_renderer=poly_it.Peek_Obj();
				DX8TextureCategoryClass *prc=polygon_renderer->Get_Texture_Category();

				if (prc==src_tex_category) {					
					DX8TextureCategoryClass* dest_tex_category=Find_Matching_Texture_Category(new_texture,pass,stage,src_tex_category);

					if (!dest_tex_category) {
						TextureClass * tmp_textures[MeshMatDescClass::MAX_TEX_STAGES];
						for (int s=0;s<MeshMatDescClass::MAX_TEX_STAGES;++s) {
							tmp_textures[s]=src_tex_category->Peek_Texture(s);
						}
						tmp_textures[stage]=new_texture;

						DX8TextureCategoryClass * new_tex_category=W3DNEW DX8TextureCategoryClass(
							this,
							tmp_textures,
							src_tex_category->Get_Shader(),
							const_cast<VertexMaterialClass*>(src_tex_category->Peek_Material()),
							pass);
		
						/*
						** Add the texture category object into the list, immediately after any existing
						** texture category object which uses the same texture.  This will result in
						** the list always having matching texture categories next to each other.
						*/
						bool found_similar_category = false;
						TextureCategoryListIterator tex_it(&texture_category_list[pass]);
						while (!tex_it.Is_Done()) {
							// Categorize according to first stage's texture for now
							if (tex_it.Peek_Obj()->Peek_Texture(0) == tmp_textures[0]) {
								texture_category_list[pass].Add_After(new_tex_category,tex_it.Peek_Obj());
								found_similar_category = true;
								break;
							}
							tex_it.Next();
						}

						if (!found_similar_category) {
							texture_category_list[pass].Add_Tail(new_tex_category);
						}
						dest_tex_category=new_tex_category;
					}
					PolyRemover *rem=W3DNEW PolyRemover;
					rem->src=src_tex_category;
					rem->dest=dest_tex_category;
					rem->pr=polygon_renderer;
					prl.Add(rem);					
				}
				poly_it.Next();
			} // while			
		} //if src_texture==texture
		else
			// quit loop if we've got a texture change
			if (foundtexture) break;
		src_it.Next();
	} // while

	PolyRemoverListIterator prli(&prl);

	while (!prli.Is_Done())
	{
		PolyRemover *rem=prli.Peek_Obj();
		rem->src->Remove_Polygon_Renderer(rem->pr);
		rem->dest->Add_Polygon_Renderer(rem->pr);		
		prli.Remove_Current_Object();
		delete rem;
	}
}

// DX8FVFCategoryContainer::Change_Polygon_Renderer_Material: BFME 2's body is the row 0x001465C0 in DX8FVFCategoryMigrateBFME2.cpp;
// Zero Hour's copy here duplicated it.

// ----------------------------------------------------------------------------

// Retail MeshModel/MeshMatDesc ABI views: the SORT flag word sits at mmc+0x18
// with SortLevel at +0x1c, CurMatDesc at mmc+0x94, and the UV pointer array at
// matdesc+0x10. This TU builds against ZH headers that place
// MeshGeometryClass::Flags at +0x14, CurMatDesc at +0x98, and drop
// MeshMatDesc's W3DMPO base so UV lands at +0x0c (retail keeps the base).
// BFME1 pinned the same model-side layout in its TU-local
// dx8renderer_Add_Rigid_Mesh_To_Container.cpp. TU-local views, so the placed
// bodies in this TU keep their layout.
struct RetailMeshModelFlagView { char _pad[0x18]; int Flags; char SortLevel; };
struct RetailMeshMatDescView { char _pad[0x10]; void * UV[8]; };
struct RetailMeshModelLayoutView { char _pad[0x94]; RetailMeshMatDescView * CurMatDesc; };
static int RetailMeshModel_Get_Flag(const MeshModelClass * mmc,int flag)
{ return ((const RetailMeshModelFlagView *)mmc)->Flags & flag; }
static int RetailMeshModel_Get_UV_Array_Count(const MeshModelClass * mmc)
{
	// Same count as the header inline, but with the bound evaluated first:
	// that is the condition order retail compiles (bound check at loop top,
	// null check as the loop-back test).
	const RetailMeshMatDescView * matdesc = ((const RetailMeshModelLayoutView *)mmc)->CurMatDesc;
	int count = 0;
	if (matdesc->UV[0] != NULL) {
		while (count < MeshMatDescClass::MAX_UV_ARRAYS) {
			count++;
			if (matdesc->UV[count] != NULL) {
				continue;
			}
			break;
		}
	}
	return count;
}
static unsigned * RetailMeshModel_Get_Color_Array(MeshModelClass * mmc,int array_index,bool create)
{ return ((MeshMatDescClass *)((const RetailMeshModelLayoutView *)mmc)->CurMatDesc)->Get_Color_Array(array_index,create); }

unsigned DX8FVFCategoryContainer::Define_FVF(MeshModelClass* mmc,bool enable_lighting)
{
	if ((!!RetailMeshModel_Get_Flag(mmc,MeshGeometryClass::SORT)) && WW3D::Is_Sorting_Enabled()) {
		return dynamic_fvf_type;
	}

	unsigned fvf=D3DFVF_XYZ;

	int tex_coord_count=RetailMeshModel_Get_UV_Array_Count(mmc);

	if (RetailMeshModel_Get_Color_Array(mmc,0,false)) {
		fvf|=D3DFVF_DIFFUSE;
	}
	if (RetailMeshModel_Get_Color_Array(mmc,1,false)) {
		fvf|=D3DFVF_SPECULAR;
	}
	
	switch (tex_coord_count) {
	default:
	case 0:
		break;
	case 1: fvf|=D3DFVF_TEX1; break;
	case 2: fvf|=D3DFVF_TEX2; break;
	case 3: fvf|=D3DFVF_TEX3; break;
	case 4: fvf|=D3DFVF_TEX4; break;
	case 5: fvf|=D3DFVF_TEX5; break;
	case 6: fvf|=D3DFVF_TEX6; break;
	case 7: fvf|=D3DFVF_TEX7; break;
	case 8: fvf|=D3DFVF_TEX8; break;
	}

	if (mmc->Needs_Vertex_Normals()) {
		fvf|=D3DFVF_NORMAL;	// Realtime-lit
	}
	return fvf;
}

// ----------------------------------------------------------------------------

DX8RigidFVFCategoryContainer::DX8RigidFVFCategoryContainer(unsigned FVF,bool sorting_)
	:
	DX8FVFCategoryContainer(FVF,sorting_),
	vertex_buffer(0),
	used_vertices(0),
	delayed_matpass_head(NULL),
	delayed_matpass_tail(NULL)
{
}

// ----------------------------------------------------------------------------

DX8RigidFVFCategoryContainer::~DX8RigidFVFCategoryContainer()
{
	if (vertex_buffer) {
		vertex_buffer->Release_Ref();
		*reinterpret_cast<void * volatile *>(&vertex_buffer) = NULL;
	}
}

// ----------------------------------------------------------------------------

// ?Log@DX8RigidFVFCategoryContainer@@ present-unmatched
void DX8RigidFVFCategoryContainer::Log(bool only_visible)
{
#ifdef ENABLE_CATEGORY_LOG
	StringClass work(255,true);
	work.Format("DX8RigidFVFCategoryContainer --------------\n");
	WWDEBUG_SAY((work));
	if (vertex_buffer) {
		StringClass fvfname(255,true);
		vertex_buffer->FVF_Info().Get_FVF_Name(fvfname);
		work.Format("VB size (used/total): %d/%d FVF: %s\n",used_vertices,vertex_buffer->Get_Vertex_Count(),fvfname);
		WWDEBUG_SAY((work));
	}
	else {
		WWDEBUG_SAY(("EMPTY VB\n"));
	}
	if (index_buffer) {
		work.Format("IB size (used/total): %d/%d\n",used_indices,index_buffer->Get_Index_Count());
		WWDEBUG_SAY((work));
	}
	else {
		WWDEBUG_SAY(("EMPTY IB\n"));
	}

	for (unsigned p=0;p<passes;++p) {
		WWDEBUG_SAY(("Pass: %d\n",p));

		TextureCategoryListIterator it(&texture_category_list[p]);
		while (!it.Is_Done()) {
			it.Peek_Obj()->Log(only_visible);
			it.Next();
		}
	}
#endif
}

// ----------------------------------------------------------------------------
//
// Generic render function for rigid meshes
//
// ----------------------------------------------------------------------------

void DX8RigidFVFCategoryContainer::Render(void)
{
	if (!Anything_To_Render()) return;
	AnythingToRender=false;

	DX8Wrapper::Set_Vertex_Buffer(vertex_buffer);

	DX8Wrapper::Set_Index_Buffer(index_buffer,0);

	SNAPSHOT_SAY(("DX8RigidFVFCategoryContainer::Render()\n"));
	// The Z-biasing was causing more problems than they solved.
	// Disabling it for now HY.
	//int zbias=0;
	//DX8Wrapper::Set_DX8_ZBias(zbias);
	for (unsigned p=0;p<passes;++p) {
		SNAPSHOT_SAY(("Pass: %d\n",p));
		while (DX8TextureCategoryClass * tex = visible_texture_category_list[p].Remove_Head()) {
			tex->Render();
		}
		//zbias++;
		//if (zbias>15) zbias=15;
		//DX8Wrapper::Set_DX8_ZBias(zbias);
	}

	Render_Procedural_Material_Passes();

	//DX8Wrapper::Set_DX8_ZBias(0);
}

// ----------------------------------------------------------------------------

// DX8RigidFVFCategoryContainer::Check_If_Mesh_Fits: BFME 2's body is the row 0x00143A20 in DX8RigidCheckIfMeshFits.cpp;
// Zero Hour's copy here duplicated it.

// ----------------------------------------------------------------------------

class Vertex_Split_Table
{
	MeshModelClass* mmc;
	bool npatch_enable;
	unsigned polygon_count;
	TriIndex* polygon_array;

	bool allocated_polygon_array;

public:
	// BFME 2's constructor is the row 0x001454D0 in VertexSplitTableConstructorBFME.cpp.
	Vertex_Split_Table(MeshModelClass* mmc_);

	~Vertex_Split_Table()
	{
		if (allocated_polygon_array) {
			delete[] polygon_array;
		}
	}

	const Vector3* Get_Vertex_Array() const
	{
		return mmc->Get_Vertex_Array();
	}

	const Vector3* Get_Vertex_Normal_Array() const
	{
		return mmc->Get_Vertex_Normal_Array();
	}

	const unsigned* Get_Color_Array(unsigned index) const
	{
		return mmc->Get_Color_Array(index,false);
	}

	const Vector2* Get_UV_Array(unsigned uv_array_index) const
	{
		return mmc->Get_UV_Array_By_Index(uv_array_index);
	}

	unsigned Get_Vertex_Count() const
	{
		return mmc->Get_Vertex_Count();
	}

	unsigned Get_Polygon_Count() const
	{
		return polygon_count;
	}

	unsigned Get_Pass_Count() const
	{
		return mmc->Get_Pass_Count();
	}

	TextureClass* Peek_Texture(unsigned idx,unsigned pass,unsigned stage)
	{
		if (mmc->Has_Texture_Array(pass,stage)) {
			if (idx>=unsigned(mmc->Get_Polygon_Count())) {
				WWASSERT(mmc->Get_Gap_Filler());
				return mmc->Get_Gap_Filler()->Get_Texture_Array(pass,stage)[idx-mmc->Get_Polygon_Count()];
			}
			return mmc->Peek_Texture(idx,pass,stage);
		}
		return mmc->Peek_Single_Texture(pass,stage);
	}

	VertexMaterialClass* Peek_Material(unsigned idx,unsigned pass)
	{
		if (mmc->Has_Material_Array(pass)) {
			if (idx>=unsigned(mmc->Get_Polygon_Count())) {
				WWASSERT(mmc->Get_Gap_Filler());
				return mmc->Get_Gap_Filler()->Get_Material_Array(pass)[idx-mmc->Get_Polygon_Count()];
			}
			return mmc->Peek_Material(mmc->Get_Polygon_Array()[idx][0],pass);
		}
		return mmc->Peek_Single_Material(pass);
	}

	ShaderClass Peek_Shader(unsigned idx,unsigned pass)
	{
		if (mmc->Has_Shader_Array(pass)) {
			ShaderClass shader;
			
			if (idx>=unsigned(mmc->Get_Polygon_Count())) {
				WWASSERT(mmc->Get_Gap_Filler());
				shader=mmc->Get_Gap_Filler()->Get_Shader_Array(pass)[idx-mmc->Get_Polygon_Count()];
			}
			else shader=mmc->Get_Shader(idx,pass);

			if (npatch_enable) {
				shader.Set_NPatch_Enable(ShaderClass::NPATCH_ENABLE);
			}

			return shader;
		}
		if (!npatch_enable) return mmc->Get_Single_Shader(pass);
		ShaderClass shader=mmc->Get_Single_Shader(pass);
		shader.Set_NPatch_Enable(ShaderClass::NPATCH_ENABLE);
		return shader;

	}

	MeshModelClass* Get_Mesh_Model_Class()
	{
		return mmc;
	}

	unsigned short* Get_Polygon_Array(unsigned pass)
	{
		return (unsigned short*)polygon_array;
	}
};

// ----------------------------------------------------------------------------

// ?Add_Mesh@DX8RigidFVFCategoryContainer@@ present-unmatched
void DX8RigidFVFCategoryContainer::Add_Mesh(MeshModelClass* mmc_)
{
	WWASSERT(Check_If_Mesh_Fits(mmc_));

	Vertex_Split_Table split_table(mmc_);
	int needed_vertices=split_table.Get_Vertex_Count();

	/*
	** This FVFCategoryContainer doesn't have a vertex buffer yet so allocate one big
	** enough to contain this mesh.
	*/
	if (!vertex_buffer) {
		int vb_size=4000;
		if (vb_size<needed_vertices) vb_size=needed_vertices;
		if (sorting) {
			vertex_buffer=NEW_REF(SortingVertexBufferClass,(vb_size));
			WWASSERT(vertex_buffer->FVF_Info().Get_FVF()==FVF);	// Only one sorting FVF type!
		}
		else {
			vertex_buffer=NEW_REF(DX8VertexBufferClass,(
				FVF,
				vb_size,
				(DX8Wrapper::Get_Current_Caps()->Support_NPatches() && WW3D::Get_NPatches_Level()>1) ? DX8VertexBufferClass::USAGE_NPATCHES : DX8VertexBufferClass::USAGE_DEFAULT));
		}
	}

	/*
	** Append this mesh's vertices to the vertex buffer.
	*/

	VertexBufferClass::AppendLockClass l(vertex_buffer,used_vertices,split_table.Get_Vertex_Count());
	const FVFInfoClass fi=vertex_buffer->FVF_Info();
	unsigned char *vb=(unsigned char*) l.Get_Vertex_Array();
	unsigned int i;
	const Vector3 *locs=split_table.Get_Vertex_Array();
	const Vector3 *norms=split_table.Get_Vertex_Normal_Array();
	const unsigned *diffuse=split_table.Get_Color_Array(0);
	const unsigned *specular=split_table.Get_Color_Array(1);
	for (i=0; i<split_table.Get_Vertex_Count(); i++)
	{
		*(Vector3*)(vb+fi.Get_Location_Offset())=locs[i];
		
		if ((FVF&D3DFVF_NORMAL)==D3DFVF_NORMAL && norms) {
			*(Vector3*)(vb+fi.Get_Normal_Offset())=norms[i];
		}

		if ((FVF&D3DFVF_DIFFUSE)==D3DFVF_DIFFUSE) {
			if (diffuse) {
				*(unsigned int*)(vb+fi.Get_Diffuse_Offset())=diffuse[i];
			} else {
				*(unsigned int*)(vb+fi.Get_Diffuse_Offset()) = 0xFFFFFFFF;
			}
		}
		
		if ((FVF&D3DFVF_SPECULAR)==D3DFVF_SPECULAR) {
			if (specular) {
				*(unsigned int*)(vb+fi.Get_Specular_Offset())=specular[i];
			} else {
				*(unsigned int*)(vb+fi.Get_Specular_Offset()) = 0xFFFFFFFF;
			}
		}

		vb+=fi.Get_FVF_Size();
	}
	

	/*
	** Append the UV coordinates to the vertex buffer
	*/
	int uvcount = 0;
	if ((FVF&D3DFVF_TEX1) == D3DFVF_TEX1) {
		uvcount = 1;
	}
	if ((FVF&D3DFVF_TEX2) == D3DFVF_TEX2) {
		uvcount = 2;
	}
	if ((FVF&D3DFVF_TEX3) == D3DFVF_TEX3) {
		uvcount = 3;
	}
	if ((FVF&D3DFVF_TEX4) == D3DFVF_TEX4) {
		uvcount = 4;
	}
	if ((FVF&D3DFVF_TEX5) == D3DFVF_TEX5) {
		uvcount = 5;
	}
	if ((FVF&D3DFVF_TEX6) == D3DFVF_TEX6) {
		uvcount = 6;
	}
	if ((FVF&D3DFVF_TEX7) == D3DFVF_TEX7) {
		uvcount = 7;
	}
	if ((FVF&D3DFVF_TEX8) == D3DFVF_TEX8) {
		uvcount = 8;
	}
	
	for (int j=0; j<uvcount; j++) {
		unsigned char *vb=(unsigned char*) l.Get_Vertex_Array();
		const Vector2*uvs=split_table.Get_UV_Array(j);
		if (uvs) {
			for (i=0; i<split_table.Get_Vertex_Count(); i++)
			{
				*(Vector2*)(vb+fi.Get_Tex_Offset(j))=uvs[i];
				vb+=fi.Get_FVF_Size();
			}		
		}
	}

	Generate_Texture_Categories(split_table,used_vertices);

	used_vertices+=needed_vertices;//vertex_count;
}


const unsigned MAX_ADDED_TYPE_COUNT=64;
struct Textures_Material_And_Shader_Booking_Struct
{
	TextureClass* added_textures[MeshMatDescClass::MAX_TEX_STAGES][MAX_ADDED_TYPE_COUNT];
	VertexMaterialClass* added_materials[MAX_ADDED_TYPE_COUNT];
	ShaderClass added_shaders[MAX_ADDED_TYPE_COUNT];
	unsigned added_type_count;

	__declspec(dllimport) __forceinline Textures_Material_And_Shader_Booking_Struct() : added_type_count(0) {}

	bool Add_Textures_Material_And_Shader(TextureClass** texs, VertexMaterialClass* mat, ShaderClass shd)
	{
		for (unsigned a=0;a<added_type_count;++a) {
			// Compare textures
			bool all_textures_same = true;
			for (unsigned int stage = 0; stage < MeshMatDescClass::MAX_TEX_STAGES; stage++) {
				all_textures_same = all_textures_same && (texs[stage] == added_textures[stage][a]);
			}
			if (all_textures_same && Equal_Material(mat,added_materials[a]) && shd==added_shaders[a]) {
				return false;
			}
		}
		WWASSERT(added_type_count<MAX_ADDED_TYPE_COUNT);
		for (unsigned int stage = 0; stage < MeshMatDescClass::MAX_TEX_STAGES; stage++) {
			added_textures[stage][added_type_count]=texs[stage];
		}
		added_materials[added_type_count]=mat;
		added_shaders[added_type_count]=shd;
		added_type_count++;
		return true;
	}
};

// ?Generate_Texture_Categories@DX8FVFCategoryContainer@@ present-unmatched
void DX8FVFCategoryContainer::Generate_Texture_Categories(Vertex_Split_Table& split_table,unsigned vertex_offset)
{
	int polygon_count=split_table.Get_Polygon_Count();
	int index_count=polygon_count*3*split_table.Get_Pass_Count(); 

	/*
	** If we don't have an index buffer yet, allocate one.  Make it hold at least 12000 entries,
	** more if the mesh requires it.  
	*/
	if (!index_buffer) {
		int ib_size=12000;  
		if (ib_size<index_count) ib_size=index_count;
		if (sorting) {
			index_buffer=NEW_REF(SortingIndexBufferClass,(ib_size));
		}
		else {
			index_buffer=NEW_REF(DX8IndexBufferClass,(
				ib_size,
				(DX8Wrapper::Get_Current_Caps()->Support_NPatches() && WW3D::Get_NPatches_Level()>1) ? DX8IndexBufferClass::USAGE_NPATCHES : DX8IndexBufferClass::USAGE_DEFAULT));
		}
	}

	for (unsigned pass=0;pass<split_table.Get_Pass_Count();++pass) {
		Textures_Material_And_Shader_Booking_Struct textures_material_and_shader_booking;

		unsigned old_used_indices=used_indices;

		for (int i=0;i<polygon_count;++i) {
			TextureClass* textures[MeshMatDescClass::MAX_TEX_STAGES];
			// disabled this assert as MAX_TEXTURE_STAGES is now 8, but legacy MeshMat::MAX_TEX_STAGES is still 2
	//		WWASSERT(MAX_TEXTURE_STAGES==MeshMatDescClass::MAX_TEX_STAGES);
			for (int stage=0;stage<MeshMatDescClass::MAX_TEX_STAGES;stage++) 
			{
				textures[stage]=split_table.Peek_Texture(i,pass,stage);
			}
			VertexMaterialClass* mat=split_table.Peek_Material(i,pass);
			ShaderClass shader=split_table.Peek_Shader(i,pass);
			if (!textures_material_and_shader_booking.Add_Textures_Material_And_Shader(textures,mat,shader)) continue;

			Insert_To_Texture_Category(split_table,textures,mat,shader,pass,vertex_offset);
		}

		int new_inds=used_indices-old_used_indices;
		WWASSERT(new_inds<=polygon_count*3);
	}
}

// ----------------------------------------------------------------------------

// ??0DX8SkinFVFCategoryContainer@@ present-unmatched
DX8SkinFVFCategoryContainer::DX8SkinFVFCategoryContainer(bool sorting)
	:
	DX8FVFCategoryContainer(DX8_FVF_XYZNUV1,sorting),
	VisibleVertexCount(0),
	VisibleSkinHead(NULL),
	VisibleSkinTail(NULL)
{
}

// ----------------------------------------------------------------------------

// ??1DX8SkinFVFCategoryContainer@@ present-unmatched
DX8SkinFVFCategoryContainer::~DX8SkinFVFCategoryContainer()
{
}

// ----------------------------------------------------------------------------

// ?Log@DX8SkinFVFCategoryContainer@@ present-unmatched
void DX8SkinFVFCategoryContainer::Log(bool only_visible)
{
#ifdef ENABLE_CATEGORY_LOG
	StringClass work(255,true);
	work.Format("DX8SkinFVFCategoryContainer --------------\n");
	WWDEBUG_SAY((work));

	if (index_buffer) {
		work.Format("IB size (used/total): %d/%d\n",used_indices,index_buffer->Get_Index_Count());
		WWDEBUG_SAY((work));
	}
	else {
		WWDEBUG_SAY(("EMPTY IB\n"));
	}

	for (unsigned pass=0;pass<passes;++pass) {
		TextureCategoryListIterator it(&texture_category_list[pass]);
		while (!it.Is_Done()) {
			it.Peek_Obj()->Log(only_visible);
			it.Next();
		}
	}
#endif
}

// ----------------------------------------------------------------------------

// ?Render@DX8SkinFVFCategoryContainer@@ present-unmatched
void DX8SkinFVFCategoryContainer::Render(void)
{
	SNAPSHOT_SAY(("DX8SkinFVFCategoryContainer::Render()\n"));
	if (!Anything_To_Render()) {
		SNAPSHOT_SAY(("Nothing to render\n"));
		return;
	}
	AnythingToRender=false;

	DX8Wrapper::Set_Vertex_Buffer(NULL);	// Free up the reference to the current vertex buffer
														// (in case it is the dynamic, which may have to be resized)

	//'Generals' customization to allow more than 65535 vertices
	unsigned int maxVertexCount=VisibleVertexCount;
	if (maxVertexCount > 65535)
	{	//clamp vertex count to maximum size that can be indexed by 16-bit index
		maxVertexCount = 65535;
	}

	DynamicVBAccessClass vb(
		sorting ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8,
		dynamic_fvf_type,
		maxVertexCount);
	SNAPSHOT_SAY(("DynamicVBAccess - %s - %d vertices\n",sorting ? "sorting" : "non-sorting",VisibleVertexCount));

	unsigned int renderedVertexCount=0;

	MeshClass * mesh = VisibleSkinHead;
	MeshClass * remainingMesh = VisibleSkinHead;
	while (renderedVertexCount < VisibleVertexCount)
	{	mesh = remainingMesh;
		{	DynamicVBAccessClass::WriteLockClass l(&vb);
			VertexFormatXYZNDUV2 * dest_verts = l.Get_Formatted_Vertex_Array();
			unsigned vertex_offset=0;
			remainingMesh = NULL;

			while (mesh != NULL) {

				MeshModelClass * mmc = mesh->Peek_Model();
				int mesh_vertex_count=mmc->Get_Vertex_Count();
				//'Generals' mod to deal with cases where not all meshes fit in VB.
				if (vertex_offset+mesh_vertex_count > maxVertexCount || remainingMesh)
				{	//flag mesh so we know it didn't fit in the vertex buffer
					mesh->Set_Base_Vertex_Offset(VERTEX_BUFFER_OVERFLOW);
					if (remainingMesh == NULL)
						remainingMesh = mesh;	//start of meshes that didn't fit in buffer
					mesh = mesh->Peek_Next_Visible_Skin();	//skip rendering this mesh
					continue;
				}


		// If this assert hits, a skinned mesh has probably been added to the scene more than once.
		// Example: A skinned mesh was added to the scene then it was attached to a bone without being removed from the scene.
		WWASSERT((vertex_offset+mesh_vertex_count)<=VisibleVertexCount);
			DX8_RECORD_SKIN_RENDER(mesh->Get_Num_Polys(),mesh_vertex_count);

				if (_TempVertexBuffer.Length() < mesh_vertex_count) _TempVertexBuffer.Resize(mesh_vertex_count); 
				if (_TempNormalBuffer.Length() < mesh_vertex_count) _TempNormalBuffer.Resize(mesh_vertex_count);

				Vector3* loc=&(_TempVertexBuffer[0]);
				Vector3* norm=&(_TempNormalBuffer[0]);
				const Vector2* uv0=mmc->Get_UV_Array_By_Index(0);
				const Vector2* uv1=mmc->Get_UV_Array_By_Index(1);
				const unsigned* diffuse=mmc->Get_Color_Array(0,false);

				VertexFormatXYZNDUV2* verts=dest_verts+vertex_offset;

				mesh->Get_Deformed_Vertices(loc,norm);

				for (int v=0;v<mesh_vertex_count;++v) {
					verts[v].x=(*loc)[0];
					verts[v].y=(*loc)[1];
					verts[v].z=(*loc)[2];
					verts[v].nx=(*norm)[0];
					verts[v].ny=(*norm)[1];
					verts[v].nz=(*norm)[2];
					if (diffuse) {
						verts[v].diffuse=*diffuse++;
					}
					else {
						verts[v].diffuse=0;
					}
					if (uv0) {
						verts[v].u1=(*uv0)[0];
						verts[v].v1=(*uv0)[1];
						uv0++;
					}
					else {
						verts[v].u1=0.0f;
						verts[v].v1=0.0f;
					}
					if (uv1) {
						verts[v].u2=(*uv1)[0];
						verts[v].v2=(*uv1)[1];
						uv1++;
					}
					else {
						verts[v].u2=0.0f;
						verts[v].v2=0.0f;
					}

					loc++;
					norm++;
				}

				mesh->Set_Base_Vertex_Offset(vertex_offset);
				vertex_offset+=mesh_vertex_count;
				renderedVertexCount += mesh_vertex_count;
				
				mesh = mesh->Peek_Next_Visible_Skin();
			}	//while
		}//lock

		SNAPSHOT_SAY(("Set vb: %x ib: %x\n",vb,index_buffer));

		DX8Wrapper::Set_Vertex_Buffer(vb);
		DX8Wrapper::Set_Index_Buffer(index_buffer,0);

		//Flush the meshes which fit in the vertex buffer, applying all texture variations
		for (unsigned pass=0;pass<passes;++pass) {
			SNAPSHOT_SAY(("Pass: %d\n",pass));

			TextureCategoryListIterator it(&visible_texture_category_list[pass]);
			while (!it.Is_Done()) {
				it.Peek_Obj()->Render();
				it.Next();
			}
		}

		Render_Procedural_Material_Passes();
	}//while

	//remove all the rendered data from queues
	for (unsigned pass=0;pass<passes;++pass) {
		while (DX8TextureCategoryClass * tex = visible_texture_category_list[pass].Remove_Head()) {
		}
	}

	WWASSERT(renderedVertexCount==VisibleVertexCount);


	clearVisibleSkinList();
}

// DX8SkinFVFCategoryContainer::Check_If_Mesh_Fits: BFME 2's body is the row 0x00143C20 in DX8SkinClearVisibleList.cpp;
// Zero Hour's copy here duplicated it.

// DX8SkinFVFCategoryContainer::clearVisibleSkinList: BFME 2's body is the row 0x00143C60 in DX8SkinClearVisibleList.cpp;
// Zero Hour's copy here duplicated it.
// DX8SkinFVFCategoryContainer::Add_Visible_Skin: BFME 2's body is the row 0x00143CB0 in DX8SkinClearVisibleList.cpp;
// Zero Hour's copy here duplicated it.


// ----------------------------------------------------------------------------

void DX8SkinFVFCategoryContainer::Reset()
{
	clearVisibleSkinList();
	
	for (unsigned pass=0;pass<passes;++pass) {
		while (DX8TextureCategoryClass* texture_category=texture_category_list[pass].Peek_Head()) {
			::delete texture_category;
		}
	}

	if (index_buffer) {
		index_buffer->Release_Ref();
		index_buffer = NULL;
	}
	used_indices=0;
}

// ----------------------------------------------------------------------------

// DX8SkinFVFCategoryContainer::Add_Mesh: BFME 2's body is the row 0x00766460 in 00146EE0;
// Zero Hour's copy here duplicated it.

// ----------------------------------------------------------------------------

// BFME2 Add_Mesh is defined in DX8TextureCategoryAddMesh.cpp.


// ----------------------------------------------------------------------------

// BFME 2 DX8TextureCategoryClass::Render reads the mesh through these retail
// vtable slots and fields (native 0x00146F50..0x00147F5A): Validate_Transform
// +0x50, alpha +0x64, bounding sphere +0x104, two state queries +0x1A8/+0x1D8.
struct TCRModelView
{
	char pad[0x18];
	volatile unsigned char FlagBytes[4];	// +0x18 MeshGeometryClass flags, tested a byte at a time
	int Get_Flag(int f) const { return f < 0x100 ? (FlagBytes[0] & f) : (FlagBytes[1] & (f >> 8)); }
};
class TCRMeshView
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void Validate_Transform(void) const;	// +0x50
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual float Get_Alpha_Override(void);	// +0x64
	virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual const SphereClass &Get_Bounding_Sphere(void) const;	// +0x104
	virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84();
	virtual void v85(); virtual void v86(); virtual void v87(); virtual void v88(); virtual void v89();
	virtual void v90(); virtual void v91(); virtual void v92(); virtual void v93(); virtual void v94();
	virtual void v95(); virtual void v96(); virtual void v97(); virtual void v98(); virtual void v99();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103(); virtual void v104();
	virtual void v105();
	virtual int Is_Depth_Sorted_Alpha(void);	// +0x1A8
	virtual void v107(); virtual void v108(); virtual void v109();
	virtual void v110(); virtual void v111(); virtual void v112(); virtual void v113(); virtual void v114();
	virtual void v115(); virtual void v116(); virtual void v117();
	virtual int Is_Additive(void);	// +0x1D8

	const Matrix3D &Get_Transform(void) const { Validate_Transform(); return Transform; }
	bool Is_Transform_Identity(void) const { Validate_Transform(); return IsTransformIdentity; }

	char m_pad04[0x14];
	Matrix3D Transform;	// +0x18
	float ObjectScale;	// +0x48
	char m_pad4C[0x74 - 0x4C];
	bool IsTransformIdentity;	// +0x74
	char m_pad75[0xBD - 0x75];
	bool HardwareFog;	// +0xBD
	char m_padBE[0xC4 - 0xBE];
	MeshModelClass *Model;	// +0xC4
	LightEnvironmentClass *LightEnvironment;	// +0xC8
	char m_padCC[0x300 - 0xCC];
	int BaseVertexOffset;	// +0x300
	char m_pad304[0x310 - 0x304];
	RenderObjClass **SkinContainer;	// +0x310
};

class BFME2RenderObjInheritedDataView
{
public:
	void *Get_Inherited_Render_Data(void);
};
extern int G00DEDA78;

struct BFME2TextureResource { unsigned Vtable; unsigned short Refs; void Release_Ref(); };
struct BFME2TextureRef
{
	BFME2TextureResource *Ptr;
	~BFME2TextureRef() { if (Ptr) Ptr->Release_Ref(); }
};
class BFME2TextureCategory
{
public:
	BFME2TextureRef Get_Texture(int stage);
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

// BFME 2 drives a D3D9 device: SetTextureStageState is vtable slot 67.
class TCRStageStates : public DX8Wrapper
{
public:
	static unsigned Get(unsigned stage, unsigned state) { return TextureStageStates[stage][state]; }
	static WWINLINE void Set(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value)
	{
		typedef HRESULT (__stdcall *SetTextureStageStateFn)(IDirect3DDevice8 *, DWORD, DWORD, DWORD);
		if (TextureStageStates[stage][(unsigned int)state]==value) return;
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0,true);
			Get_DX8_Texture_Stage_State_Value_Name(value_name,state,value);
			SNAPSHOT_SAY(("DX8 - SetTextureStageState(stage: %d, state: %s, value: %s)\n",
				stage,
				Get_DX8_Texture_Stage_State_Name(state),
				value_name));
		}
#endif
		TextureStageStates[stage][(unsigned int)state]=value;
		IDirect3DDevice8 *device = _Get_D3D_Device8();
		(*(SetTextureStageStateFn **)device)[67](device, stage, state, value);
		number_of_DX8_calls++;
		DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE();
	}
};

// Matrix storage the transform paths fill completely (no element constructors).
struct TCRMatrixStorage { float m[12]; };

// matrix3d.h's Matrix3D::Get_Translation(Vector3*), inlined into Render below. Called as
// the Matrix3D member, this /O2 unit also emitted an unreferenced external COMDAT copy
// (integer moves) that differs from retail's one x87 body (0x0009314A, ICF-shared with
// Matrix4D::GetTranslationVector) and, first in link order, won the link for the units
// whose copies are retail's. The body is unchanged; only the out-of-line name is local.
class TCRTranslationView : public Matrix3D
{
public:
	WWINLINE void Get_Translation(Vector3 * set) const { set->X = Row[0][3]; set->Y = Row[1][3]; set->Z = Row[2][3]; }
};

// dx8wrapper.h's Set_DX8_Render_State / Set_Material / Set_Shader, inlined into Render below.
// They live in this derived helper rather than as DX8Wrapper:: definitions: an inline
// definition of the header's out-of-line declaration made this /O2 unit emit external
// COMDAT copies that differ from the one retail body of each (0x0006615F, 0x000662B1,
// 0x000662E5) and win the link for every caller. Render_Decal_Meshes keeps calling
// DX8Wrapper::Set_DX8_Render_State out of line. ShaderClass base: ShaderDirty is protected.
class TCRRenderStates : public DX8Wrapper, public ShaderClass
{
public:
	static WWINLINE void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
	{
		if (RenderStates[state]==value) return;
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0,true);
			Get_DX8_Render_State_Value_Name(value_name,state,value);
			SNAPSHOT_SAY(("DX8 - SetRenderState(state: %s, value: %s)\n",
				Get_DX8_Render_State_Name(state),
				value_name));
		}
#endif
		RenderStates[state]=value;
		DX8CALL(SetRenderState( state, value ));
		DX8_RECORD_RENDER_STATE_CHANGE();
	}

	static WWINLINE void Set_Material(const VertexMaterialClass* material)
	{
		REF_PTR_SET(render_state.material,const_cast<VertexMaterialClass*>(material));
		render_state_changed|=0x4000;	// DX8Wrapper::MATERIAL_CHANGED (private enumerator)
		SNAPSHOT_SAY(("DX8Wrapper::Set_Material(%s)\n",material ? material->Get_Name() : "NULL"));
	}

	static WWINLINE void Set_Shader(const ShaderClass& shader)
	{
		if (!ShaderClass::ShaderDirty && ((unsigned&)shader==(unsigned&)render_state.shader)) {
			return;
		}
		render_state.shader=shader;
		render_state_changed|=0x8000;	// DX8Wrapper::SHADER_CHANGED (private enumerator)
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
		StringClass str;
#endif
		SNAPSHOT_SAY(("DX8Wrapper::Set_Shader(%s)\n",shader.Get_Description(str)));
	}
};

void DX8TextureCategoryClass::Render(void)
{
	for (unsigned i=0;i<2;++i)
	{
		BFME2Set_Texture(i,((BFME2TextureCategory *)this)->Get_Texture(i));
	}

	VertexMaterialClass *vmaterial=(VertexMaterialClass *)Peek_Material();
	TCRRenderStates::Set_Material(vmaterial);

	ShaderClass theShader = Get_Shader();
	TCRRenderStates::Set_Shader(theShader);

	if (m_gForceMultiply && theShader.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ZERO) {
		theShader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_SRC_COLOR);
		theShader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_ZERO);
		TCRRenderStates::Set_Shader(theShader);
		DX8Wrapper::Apply_Render_State_Changes();
		TCRRenderStates::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_DESTCOLOR);
	}

	bool renderTasksRemaining=false;

	PolyRenderTaskClass * prt = render_task_head;
	PolyRenderTaskClass * last_prt = NULL;

	while (prt) {

		DX8PolygonRendererClass * renderer = prt->Peek_Polygon_Renderer();
		TCRMeshView * mesh = (TCRMeshView *)prt->Peek_Mesh();

		if (mesh->BaseVertexOffset == VERTEX_BUFFER_OVERFLOW)
		{
			last_prt = prt;
			prt = prt->Get_Next_Visible();
			renderTasksRemaining = true;
			continue;
		}

		if (DX8Wrapper::Get_Fog_Enable()) {
			if (mesh->HardwareFog) {
				if (theShader.Get_Fog_Func() == ShaderClass::FOG_DISABLE) {
					theShader.Enable_Fog("HardwareFog");
					TCRRenderStates::Set_Shader(theShader);
				}
			} else if (theShader.Get_Fog_Func() != ShaderClass::FOG_DISABLE) {
				theShader.Set_Fog_Func(ShaderClass::FOG_DISABLE);
				TCRRenderStates::Set_Shader(theShader);
			}
		}

		LightEnvironmentClass * lenv = mesh->LightEnvironment;
		if (lenv != NULL) {
			DX8Wrapper::Set_Light_Environment(lenv);
		}

		const Matrix3D* world_transform = &mesh->Get_Transform();
		bool identity=mesh->Is_Transform_Identity();
		TCRMatrixStorage tmp_storage;
		Matrix3D &tmp_world = *(Matrix3D *)&tmp_storage;

		if (((TCRModelView *)mesh->Model)->Get_Flag(MeshModelClass::ALIGNED)) {
			Vector3 mesh_position;
			Vector3 camera_z_vector;

			((DX8MeshRendererClass *)RendererPtr00DF363C)->Peek_Camera()->Get_Transform().Get_Z_Vector(&camera_z_vector);
			const Matrix3D & mesh_tm = mesh->Get_Transform();
			((const TCRTranslationView &)mesh_tm).Get_Translation(&mesh_position);

			tmp_world.Obj_Look_At(mesh_position,mesh_position + camera_z_vector,0.0f);
			world_transform = &tmp_world;

		} else if (((TCRModelView *)mesh->Model)->Get_Flag(MeshModelClass::ORIENTED)) {
			Vector3 mesh_position;
			Vector3 camera_position;

			const Matrix3D & camera_tm = ((DX8MeshRendererClass *)RendererPtr00DF363C)->Peek_Camera()->Get_Transform();
			camera_position.X = camera_tm[0][3];
			camera_position.Y = camera_tm[1][3];
			camera_position.Z = camera_tm[2][3];
			const Matrix3D & mesh_tm = mesh->Get_Transform();
			mesh_position.X = mesh_tm[0][3];
			mesh_position.Y = mesh_tm[1][3];
			mesh_position.Z = mesh_tm[2][3];

			tmp_world.Obj_Look_At(mesh_position,camera_position,0.0f);
			world_transform = &tmp_world;

		} else if (((TCRModelView *)mesh->Model)->Get_Flag(MeshModelClass::SKIN)) {
			if (mesh->SkinContainer && *mesh->SkinContainer) {
				RenderObjClass *container = *mesh->SkinContainer;
				TCRMatrixStorage inverse_storage;
				Matrix3D &inverse = *(Matrix3D *)&inverse_storage;
				container->Get_Transform().Get_Inverse(inverse);
				Matrix3D::Multiply(mesh->Get_Transform(),inverse,&tmp_world);
				world_transform = &tmp_world;
				identity=false;
			} else {
				identity=true;
			}
		}

		if (identity) {
			DX8Wrapper::Set_World_Identity();
		}
		else {
			DX8Wrapper::Set_Transform(D3DTS_WORLD,*world_transform);
		}

		if (mesh->ObjectScale != 1.0f)
			TCRRenderStates::Set_DX8_Render_State(D3DRS_NORMALIZENORMALS, TRUE);

		int oldInherited = G00DEDA78;
		G00DEDA78 = (int)((BFME2RenderObjInheritedDataView *)mesh)->Get_Inherited_Render_Data();

		if ((!!((TCRModelView *)mesh->Model)->Get_Flag(MeshGeometryClass::SORT)) && WW3D::Is_Sorting_Enabled()) {
			int base_vertex_offset=mesh->BaseVertexOffset;
			renderer->Render_Sorted(base_vertex_offset,mesh->Get_Bounding_Sphere());
		} else {
			if (mesh->Get_Alpha_Override() < 1.0f)
			{
				ShaderClass theAlphaShader = theShader;
				theAlphaShader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_SRC_ALPHA);
				theAlphaShader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA);
				if (mesh->Is_Additive())
					theAlphaShader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);
				bool sortedAlpha = mesh->Is_Depth_Sorted_Alpha() != 0;
				float alpha = mesh->Get_Alpha_Override();
				if (sortedAlpha && alpha < 0.5f)
					theAlphaShader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
				TCRRenderStates::Set_Shader(theAlphaShader);
				DX8Wrapper::Apply_Render_State_Changes();

				bool stageModulates = TCRStageStates::Get(1,D3DTSS_ALPHAOP) == D3DTOP_MODULATE;
				if (stageModulates) {
					TCRStageStates::Set(0,D3DTSS_ALPHAARG1,D3DTA_TFACTOR);
					TCRStageStates::Set(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
				} else {
					TCRStageStates::Set(1,D3DTSS_ALPHAARG1,D3DTA_CURRENT);
					TCRStageStates::Set(1,D3DTSS_ALPHAARG2,D3DTA_TFACTOR);
					TCRStageStates::Set(1,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
					if (TCRStageStates::Get(1,D3DTSS_COLOROP) == D3DTOP_DISABLE) {
						TCRStageStates::Set(1,D3DTSS_COLORARG1,D3DTA_CURRENT);
						TCRStageStates::Set(1,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
					}
				}
				TCRRenderStates::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR,((int)(alpha*255.0f))<<24);
				TCRRenderStates::Set_DX8_Render_State(D3DRS_ALPHAREF,(int)((float)0x60*alpha));
				{
					int offset = mesh->BaseVertexOffset;
					renderer->Render(offset);
				}
				TCRRenderStates::Set_DX8_Render_State(D3DRS_ALPHAREF,0x60);
				TCRRenderStates::Set_Shader(theShader);
				ShaderClass::Invalidate();
				TCRRenderStates::Set_Material(NULL);
				TCRRenderStates::Set_Material(vmaterial);
			}
			else {
				int offset = mesh->BaseVertexOffset;
				renderer->Render(offset);
			}
		}

		G00DEDA78 = oldInherited;

		if (mesh->ObjectScale != 1.0f)
			TCRRenderStates::Set_DX8_Render_State(D3DRS_NORMALIZENORMALS, FALSE);

		PolyRenderTaskClass * next_prt = prt->Get_Next_Visible();

		if (last_prt == NULL) {
		   render_task_head = next_prt;
		} else {
		  last_prt->Set_Next_Visible(next_prt);
		}

		delete prt;
		prt = next_prt;
	}

	if (!renderTasksRemaining)
	{
		Clear_Render_List();
	}
}


// BFME 2's Render inlines the header accessors Zero Hour's Render reached out
// of line. Their rows (placed from this unit's COMDAT copies) keep the copies
// through this source-only anchor.
// ?DX8TextureCategoryClass_AccessorAnchor absent-from-retail
void DX8TextureCategoryClass_AccessorAnchor(
	const float (RenderObjClass::*&object_scale)(void) const,
	int (MeshClass::*&base_vertex_offset)(void),
	LightEnvironmentClass *(MeshClass::*&lighting)(void),
	TextureMapperClass *(VertexMaterialClass::*&mapper)(int),
	void (LinearOffsetTextureMapperClass::*&uv_offset)(const Vector2 &))
{
	object_scale = &RenderObjClass::Get_ObjectScale;
	base_vertex_offset = &MeshClass::Get_Base_Vertex_Offset;
	lighting = &MeshClass::Get_Lighting_Environment;
	mapper = &VertexMaterialClass::Peek_Mapper;
	uv_offset = &LinearOffsetTextureMapperClass::Set_Current_UV_Offset;
}

// DX8MeshRendererClass constructor: BFME 2's body is the row 0x00145AA0 in DX8MeshRendererCtor.cpp;
// Zero Hour's copy here duplicated it.

// Owned by DX8MeshRendererClassDtor.cpp.

void DX8MeshRendererClass::Init(void)
{
	// DMS - Only allocate one if we havent already (leak fix)
	if(!texture_category_container_list_skin)
		texture_category_container_list_skin = W3DNEW FVFCategoryList;
}

// Owned by DX8MeshRendererClearPendingDeleteLists.cpp.

// ----------------------------------------------------------------------------

// Owned by DX8MeshRendererClearPendingDeleteLists.cpp.

// ----------------------------------------------------------------------------

// External: Register_Mesh_Type (DX8MeshRendererRegisterMeshTypeBFME2.cpp) calls it.
void Add_Rigid_Mesh_To_Container(FVFCategoryList* container_list,unsigned fvf,MeshModelClass* mmc)
{
	WWASSERT(container_list);
	DX8FVFCategoryContainer * container = NULL;
	bool sorting=((!!RetailMeshModel_Get_Flag(mmc,MeshModelClass::SORT)) && WW3D::Is_Sorting_Enabled() && (mmc->Get_Sort_Level() == SORT_LEVEL_NONE));

	FVFCategoryListIterator it(container_list);
	while (!it.Is_Done()) {
		container = it.Peek_Obj();
		if (sorting==container->Is_Sorting() && container->Check_If_Mesh_Fits(mmc)) {
			container->Add_Mesh(mmc);
			return;
		}
		it.Next();
	}

	container=W3DNEW DX8RigidFVFCategoryContainer(fvf,sorting);
	container_list->Add_Tail(container);
	container->Add_Mesh(mmc);
}

// ----------------------------------------------------------------------------

// DX8MeshRendererClass::Unregister_Mesh_Type: BFME 2's body is the row 0x001445E0 in DX8MeshRendererUnregisterMeshType.cpp;
// Zero Hour's copy here duplicated it.


// DX8MeshRendererClass::Register_Mesh_Type: BFME 2's body is the row 0x00145C30 in
// DX8MeshRendererRegisterMeshTypeBFME2.cpp, which calls Add_Rigid_Mesh_To_Container
// above; Zero Hour's copy here duplicated it.

static unsigned statistics_requested=0;

void DX8MeshRendererClass::Request_Log_Statistics()
{
	statistics_requested=WW3D::Get_Frame_Count();
}


// ---------------------------------------------------------------------------
//
// Render all meshes that are added to visible lists
//
// ---------------------------------------------------------------------------

static void Render_FVF_Category_Container_List(FVFCategoryList& list)
{
	FVFCategoryListIterator it(&list);
	while (!it.Is_Done()) {
		it.Peek_Obj()->Render();
		it.Next();
	}
}

static void Render_FVF_Category_Container_List_Delayed_Passes(FVFCategoryList& list)
{
	FVFCategoryListIterator it(&list);
	while (!it.Is_Done()) {
		it.Peek_Obj()->Render_Delayed_Procedural_Material_Passes();
		it.Next();
	}
}

// BFME 2's Flush (0x00148030): the rigid and skin lists, then the delayed
// passes, with no decal pass; the two list walks inline, and the cached-state
// reset calls replace Zero Hour's buffer-only reset.
void DX8MeshRendererClass::Flush(void)
{
	int i;

	if (!camera) return;
	Log_Statistics_String(true);

	for (i=0;i<texture_category_container_lists_rigid.Count();++i) {
		Render_FVF_Category_Container_List(*texture_category_container_lists_rigid[i]);
	}

	Render_FVF_Category_Container_List(*texture_category_container_list_skin);

	for (i=0;i<texture_category_container_lists_rigid.Count();++i) {
		Render_FVF_Category_Container_List_Delayed_Passes(*texture_category_container_lists_rigid[i]);
	}

	DX8Wrapper::Set_Vertex_Buffer(NULL,0);
	DX8Wrapper::Set_Index_Buffer(NULL,0);
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Invalidate_Cached_Render_States();
	DX8Wrapper::Apply_Default_State();
}


// ?Add_To_Render_List@DX8MeshRendererClass@@ present-unmatched
void DX8MeshRendererClass::Add_To_Render_List(DecalMeshClass * decalmesh)
{
	WWASSERT(decalmesh != NULL);
	decalmesh->Set_Next_Visible(visible_decal_meshes);
	visible_decal_meshes = decalmesh;
}

// ?Render_Decal_Meshes@DX8MeshRendererClass@@ present-unmatched
void DX8MeshRendererClass::Render_Decal_Meshes(void)
{
	DecalMeshClass * decal_mesh = visible_decal_meshes;
	if (!decal_mesh) return;

	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZBIAS,8);
	
	while (decal_mesh != NULL) {
		decal_mesh->Render();
		decal_mesh = decal_mesh->Peek_Next_Visible();
	}
	visible_decal_meshes = NULL;

	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZBIAS,0);
}

// ----------------------------------------------------------------------------

static void Log_Container_List(FVFCategoryList& container_list,bool only_visible)
{
	FVFCategoryListIterator it(&container_list);
	while (!it.Is_Done()) {
		it.Peek_Obj()->Log(only_visible);
		it.Next();
	}
}

void DX8MeshRendererClass::Log_Statistics_String(bool only_visible)
{
	if (statistics_requested!=WW3D::Get_Frame_Count()) return;

	for (int i=0;i<texture_category_container_lists_rigid.Count();++i) {
		Log_Container_List(*texture_category_container_lists_rigid[i],only_visible);
	}
	Log_Container_List(*texture_category_container_list_skin,only_visible);

}

// Retail 0x00144620 (40B, RET 0) is this file-static helper on its own: the list
// arrives in ESI, the private convention cl 7.1 picks for a file-static noinline
// function, and each container is destroyed through slot 0 with the no-free flag
// and its result freed by the global operator delete, which is what `::delete`
// emits for a class with a virtual destructor (the same idiom the inlined copies
// in DX8MeshRendererClass_Invalidate_Thunk.cpp show). The only retail calls are
// inlined into Invalidate, so a source-only caller emits this copy.
static __declspec(noinline) void Invalidate_FVF_Category_Container_List(FVFCategoryList& list)
{
	while (DX8FVFCategoryContainer* fvf_category=list.Remove_Head()) {
		::delete fvf_category;
	}
}

// ?Invalidate_FVF_Category_Container_ListCaller absent-from-retail
void Invalidate_FVF_Category_Container_ListCaller(FVFCategoryList& list)
{
	Invalidate_FVF_Category_Container_List(list);
}

// DX8MeshRendererClass::Invalidate: the byte-exact BFME2 definition is in
// DX8MeshRendererClass_Invalidate_Thunk.cpp. The ZH definition formerly here
// reset RegisteredMeshList, which retail omits, and duplicated that provider.
// ?RendererPtr00DF363C@@3PAURendererFVFDeleteListView@@A: the global at VA 0xdf363c is ?TheDX8MeshRenderer@@3PAVDX8MeshRendererClass@@A.
#pragma comment(linker, "/alternatename:?RendererPtr00DF363C@@3PAURendererFVFDeleteListView@@A=?TheDX8MeshRenderer@@3PAVDX8MeshRendererClass@@A")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00145000@@UAE@XZ=??1DX8FVFCategoryContainer@@UAE@XZ")

// ?Rva00143970Find@@YAPAVRva00143970Node@@PAV1@PAX@Z @0x00143970 155B
// Free recursive search between Equal_Material and PolyRemover; slots 0xC/0x14/0x70/0x78
// on a RefCount view with key at +0xC4; self-recursive, releases child ref.
class Rva00143970Node : public RefCountClass
{
public:
	virtual void d08();
	virtual int Has_Something();
	virtual void d10();
	virtual Rva00143970Node *Get_Model();
	virtual void d18();
	virtual void d1C();
	virtual void d20();
	virtual void d24();
	virtual void d28();
	virtual void d2C();
	virtual void d30();
	virtual void d34();
	virtual void d38();
	virtual void d3C();
	virtual void d40();
	virtual void d44();
	virtual void d48();
	virtual void d4C();
	virtual void d50();
	virtual void d54();
	virtual void d58();
	virtual void d5C();
	virtual void d60();
	virtual void d64();
	virtual void d68();
	virtual void d6C();
	virtual int Get_Count();
	virtual void d74();
	virtual Rva00143970Node *Get_At(int index);
	char m_pad[0xC4 - 8];
	void *m_key;
};

Rva00143970Node *__cdecl Rva00143970Find(Rva00143970Node *node, void *key)
{
	if (!node || !key)
		return 0;
	if (!node->Has_Something()) {
		Rva00143970Node *m = node->Get_Model();
		if (m->m_key == key)
			return m;
	}
	for (int i = 0; i < node->Get_Count(); i++) {
		Rva00143970Node *child = node->Get_At(i);
		Rva00143970Node *res = Rva00143970Find(child, key);
		if (child)
			child->Release_Ref();
		if (res)
			return res;
	}
	return 0;
}
