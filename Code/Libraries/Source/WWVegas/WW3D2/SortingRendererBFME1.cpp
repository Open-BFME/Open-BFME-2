// cl: /DBFME_SORTING_DWORD_DRAW /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /G7 /arch:SSE /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// No /O1 vector-constructor-iterator anchor here: Flush (0x0012F190) is the
// first function to need ??_H, and retail calls it out of line for Flush's
// last Set_Transform. With the /O1 body first, VC7 inlines that call too and
// reallocates Flush's zero register, so this unit emits the /O2 ??_H copy
// that retail's linker discarded for the /O1 one at 0x00001423.
#define Matrix4x4 Matrix4  // BFME renamed it
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
 *                     $Archive:: /Commando/Code/ww3d2/sortingrenderer.cpp                    $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/27/02 1:27p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 * 06/27/02 KM Changes to max texture stage caps																*
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// BFME2's SortingRendererClass takes its index ranges as unsigned ints: both
// sphere inserts reject a value above 65535 before narrowing it into the
// node. This unit declares the class itself in place of the Zero Hour header.
#include "always.h"
#define SORTING_RENDERER_H
class SortingNodeStruct;
class SphereClass;
class SortingRendererClass
{
	static bool _EnableTriangleDraw;

	static void Flush_Sorting_Pool();
	static void Insert_To_Sorting_Pool(SortingNodeStruct* state);

public:
	static void Insert_Triangles(
		const SphereClass& bounding_sphere,
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);

	static void Insert_Triangles(
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);

	static void Insert_VolumeParticle(
		const SphereClass& bounding_sphere,
		unsigned start_index,
		unsigned polygon_count,
		unsigned min_vertex_index,
		unsigned vertex_count,
		unsigned layerCount);

	static void Flush();
	static void Deinit();

	static void SetMinVertexBufferSize( unsigned val );

	static void _Enable_Triangle_Draw(bool enable) { _EnableTriangleDraw=enable; }
	static bool _Is_Triangle_Draw_Enabled() { return _EnableTriangleDraw; }
};
#include "sortingrenderer.h"
// The Zero Hour DynamicVBAccessClass is not BFME2's: retail Flush_Sorting_Pool
// builds the 24-byte record of bfmedynamicvertexbuffer.cpp (format record,
// type, format index, declaration, count, offset, buffer) with its four-argument
// constructor (0x0013B040) and nested WriteLock (0x0013AA00 / 0x0013AB00).
#define DynamicVBAccessClass ZHDynamicVBAccessClass
#include "dx8vertexbuffer.h"
#undef DynamicVBAccessClass
class DynamicVBAccessClass
{
public:
	const void *format;
	unsigned type, formatIndex, declaration;
	unsigned short vertexCount, vertexOffset;
	VertexBufferClass *buffer;
	DynamicVBAccessClass(unsigned type, unsigned format_index, unsigned short vertex_count, unsigned declaration);
	~DynamicVBAccessClass();
	static void _Reset(bool frame_changed);
	static unsigned short Get_Default_Vertex_Count(void);
	struct WriteLock {
		DynamicVBAccessClass *owner;
		VertexFormatXYZNDUV2 *data;
		unsigned char guard;	// the empty BFMEDX8DeviceLock member
		WriteLock(DynamicVBAccessClass *vb_access);
		~WriteLock();
	};
};
// BFME2's index write lock holds the DX8 device mutex as a third member
// (DynamicIBAccessWriteLock.cpp), so the Zero Hour header's two-member lock
// is too small for retail's frame.
#define DynamicIBAccessClass ZHDynamicIBAccessClass
#include "dx8indexbuffer.h"
#undef DynamicIBAccessClass
class DynamicIBAccessClass
{
	unsigned Type;
	unsigned short IndexCount;
	unsigned short IndexBufferOffset;
	IndexBufferClass *IndexBuffer;

public:
	DynamicIBAccessClass(unsigned short type, unsigned short index_count);
	~DynamicIBAccessClass();
	static void _Reset(bool frame_changed);
	static unsigned short Get_Default_Index_Count(void);

	class WriteLockClass
	{
		DynamicIBAccessClass *DynamicIBAccess;
		unsigned short *Indices;
		unsigned char device_lock;	// the empty BFMEDX8DeviceLock member

	public:
		WriteLockClass(DynamicIBAccessClass *ib_access);
		~WriteLockClass();
		unsigned short *Get_Index_Array() { return Indices; }
	};
};
// BFME's REF_PTR_RELEASE clears the pointer inside its test, where the Zero
// Hour macro stores NULL unconditionally; DX8Wrapper::Release_Render_State
// (0x0011C500) is emitted from this unit with that shape.
#include "refcount.h"
#undef REF_PTR_RELEASE
#define REF_PTR_RELEASE(x)		{ if (x) { x->Release_Ref(); x = NULL; } }
#include "dx8wrapper.h"
#include "vertmaterial.h"
#include "texture.h"
#include "ref_ptr.h"
#include "d3d8.h"
#include "D3dx8math.h"
#include "statistics.h"
#include <wwprofile.h>
#include <algorithm>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern unsigned char *BfmeCurrentCaps;

// BFME stores the eight texture references in RenderStateStruct as owning
// handles.  The Zero Hour header exposes them as raw pointers, which has the
// same layout but makes VC7 emit a hand-written release loop instead of the
// retail eh-vector-destructor call.  Keep the correction local to this TU:
// SortingNodeStruct is the only owner whose destructor is claimed here.
struct BfmeSortingShaderState
{
	unsigned int bits;

	BfmeSortingShaderState() : bits(0x0010441B) {}
};

struct BfmeSortingRenderStateStruct
{
	BfmeSortingShaderState shader;
	VertexMaterialClass *material;
	RefCountPtr<TextureClass> Textures[MAX_TEXTURE_STAGES];
	D3DLIGHT8 Lights[4];
	bool LightEnable[4];
	Matrix4x4 world;
	Matrix4x4 view;
	unsigned vertex_buffer_types[MAX_VERTEX_STREAMS];
	unsigned index_buffer_type;
	unsigned short vba_offset;
	unsigned short vba_count;
	unsigned short iba_offset;
	VertexBufferClass *vertex_buffers[MAX_VERTEX_STREAMS];
	IndexBufferClass *index_buffer;
	unsigned short index_base_offset;

	BfmeSortingRenderStateStruct()
		: shader(), material(0), index_buffer(0)
	{
		vertex_buffers[0] = 0;
		vertex_buffers[1] = 0;
	}

	__forceinline ~BfmeSortingRenderStateStruct()
	{
		if (material) {
			material->Release_Ref();
			*reinterpret_cast<VertexMaterialClass * volatile *>(&material) = 0;
		}
		for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i) {
			if (vertex_buffers[i]) {
				vertex_buffers[i]->Release_Ref();
				*reinterpret_cast<VertexBufferClass * volatile *>(&vertex_buffers[i]) = 0;
			}
		}
		if (index_buffer) {
			index_buffer->Release_Ref();
			*reinterpret_cast<IndexBufferClass * volatile *>(&index_buffer) = 0;
		}
	}
};

#ifdef _INTERNAL
// for occasional debugging...
// #pragma optimize("", off)
// #pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

bool SortingRendererClass::_EnableTriangleDraw=true;
static unsigned DEFAULT_SORTING_POLY_COUNT = 16384;	// (count * 3) must be less than 65536
static unsigned DEFAULT_SORTING_VERTEX_COUNT = 32768;	// count must be less than 65536

// SortingRendererClass::SetMinVertexBufferSize: defined in sortingrenderer.cpp (its row's unit).

struct ShortVectorIStruct
{
	unsigned short i;
	unsigned short j;
	unsigned short k;
};

struct TempIndexStruct
{
	ShortVectorIStruct tri;
	unsigned short idx;
	float z;
};

// Sort and its comparison operators belong to this unit: retail's
// Flush_Sorting_Pool keeps overlapping_polygon_count in ESI across the Sort
// call, which VC7 does only when Sort and everything it calls are compiled
// here (an external Sort forces a reload of the static).
bool operator <(const TempIndexStruct &l, const TempIndexStruct &r) { return l.z < r.z; }
bool operator <=(const TempIndexStruct &l, const TempIndexStruct &r) { return l.z <= r.z; }
bool operator >(const TempIndexStruct &l, const TempIndexStruct &r) { return l.z > r.z; }
bool operator >=(const TempIndexStruct &l, const TempIndexStruct &r) { return l.z >= r.z; }
bool operator ==(const TempIndexStruct &l, const TempIndexStruct &r) { return l.z == r.z; }
// ----------------------------------------------------------------------------
// ?Sort@@YAXPAUTempIndexStruct@@0@Z
void Sort(TempIndexStruct *begin, TempIndexStruct *end)
{
	if (begin >= end)
		return;

	TempIndexStruct *ranges[64];
	TempIndexStruct **next_range = ranges;
	for (;;) {
		const int diff = end - begin;
		if (diff <= 16) {
			for (TempIndexStruct *iter = begin + 1; iter < end; ++iter) {
				TempIndexStruct val = iter[0];
				TempIndexStruct *insert = iter;
				while (insert != begin && insert[-1] > val) {
					insert[0] = insert[-1];
					insert -= 1;
				}
				insert[0] = val;
			}

			if (next_range == ranges)
				return;
			begin = *(--next_range);
			end = *(--next_range);
			continue;
		}

		// Choose the median of begin, mid, and (end - 1) as the partitioning element.
		// Rearrange so that *(begin + 1) <= *begin <= *(end - 1).  These will be guard
		// elements.
		TempIndexStruct *mid = begin + diff/2;
		std::swap(mid[0], begin[1]);
		if (begin[1] > end[-1]) {
			std::swap(begin[1], end[-1]);
		}
		if (begin[0] > end[-1]) {
			std::swap(begin[0], end[-1]);
		}																// end[-1] has the largest element
		if (begin[1] > begin[0]) {
			std::swap(begin[1], begin[0]);
		}																// begin[0] has the middle element and begin[1] has the smallest element

		// *begin is now the partitioning element
		TempIndexStruct *begin1 = begin + 1;	// TODO: Temp fix until I find out who is passing me NaN
		TempIndexStruct *end1 = end - 1;			// TODO: Temp fix until I find out who is passing me NaN
		TempIndexStruct *left = begin + 1;
		TempIndexStruct *right = end - 1;
		for (;;) {
#if 0		// TODO: Temp fix until I find out who is passing me NaN.
			do ++left; while (left[0] < begin[0]);		// Scan up to find element >= than partition
			do --right; while (right[0] > begin[0]);	// Scan down to find element <= than partition
#else
			do ++left; while (left < end1 && left[0] < begin[0]);		// Scan up to find element >= than partition
			do --right; while (right > begin1 && right[0] > begin[0]);	// Scan down to find element <= than partition
#endif
			if (right < left) break;									// Pointers crossed.  Partitioning completed.
// ?swap@std@@ present-unmatched
			std::swap(left[0], right[0]);							// Exchange elements.
		}
// ?swap@std@@ present-unmatched
		std::swap(begin[0], right[0]);							// Insert partition element

		// Sort the smaller subarray first then the larger
		if (right - begin > end - (right + 1)) {
			*next_range++ = right;
			*next_range++ = begin;
			begin = right + 1;
		} else {
			*next_range++ = end;
			*next_range++ = right + 1;
			end = right;
		}
	}
}

// ----------------------------------------------------------------------------

class SortingNodeStruct : public DLNodeClass<SortingNodeStruct>
{
	// BFME: global operator new/delete (retail Deinit @0x93BD60 calls 0x881EB0),
	// not W3DMPO pool free — drop W3DMPO_GLUE (same as MatBuffer/TexBuffer).

public:
	BfmeSortingRenderStateStruct sorting_state;

	float transformed_center;
	unsigned short start_index;			// First index used in the ib
	unsigned short polygon_count;			// Polygon count to process (3 indices = one polygon)
	unsigned short min_vertex_index;		// First index used in the vb
	unsigned short vertex_count;			// Number of vertices used in vb
};

static DLListClass<SortingNodeStruct> sorted_list;
static DLListClass<SortingNodeStruct> clean_list;
static unsigned total_sorting_vertices;

static SortingNodeStruct* Get_Sorting_Struct()
{

	SortingNodeStruct* state=clean_list.Head();
	if (state) {
		state->Remove();
		return state;
	}
	state=W3DNEW SortingNodeStruct();
	return state;
}

// ----------------------------------------------------------------------------
//
// Temporary arrays for the sorting system
//
// ----------------------------------------------------------------------------

static TempIndexStruct* temp_index_array;
static unsigned temp_index_array_count;

static TempIndexStruct* Get_Temp_Index_Array(unsigned count)
{
	if (count < DEFAULT_SORTING_POLY_COUNT)
		count = DEFAULT_SORTING_POLY_COUNT;
	if (count>temp_index_array_count) {
		delete[] temp_index_array;
		temp_index_array=W3DNEWARRAY TempIndexStruct[count];
		temp_index_array_count=count;
	}
	return temp_index_array;
}

// ----------------------------------------------------------------------------
//
// Insert triangles to the sorting system.
//
// ----------------------------------------------------------------------------

// ?Insert_Triangles@SortingRendererClass@@ present-unmatched
void SortingRendererClass::Insert_Triangles(
	const SphereClass& bounding_sphere,
	unsigned short start_index, 
	unsigned short polygon_count,
	unsigned short min_vertex_index,
	unsigned short vertex_count)
{
	if (!WW3D::Is_Sorting_Enabled()) {
		DX8Wrapper::Draw_Triangles(start_index,polygon_count,min_vertex_index,vertex_count);
		return;
	}

	SNAPSHOT_SAY(("SortingRenderer::Insert(start_i: %d, polygons : %d, min_vi: %d, vertex_count: %d)\n",
		start_index,polygon_count,min_vertex_index,vertex_count));


	DX8_RECORD_SORTING_RENDER(polygon_count,vertex_count);

	SortingNodeStruct* state=Get_Sorting_Struct();

	DX8Wrapper::Get_Render_State(reinterpret_cast<RenderStateStruct &>(state->sorting_state));

 	WWASSERT(
		((state->sorting_state.index_buffer_type==BUFFER_TYPE_SORTING || state->sorting_state.index_buffer_type==BUFFER_TYPE_DYNAMIC_SORTING) &&
		(state->sorting_state.vertex_buffer_types[0]==BUFFER_TYPE_SORTING || state->sorting_state.vertex_buffer_types[0]==BUFFER_TYPE_DYNAMIC_SORTING)));


	state->start_index=start_index;
	state->polygon_count=polygon_count;
	state->min_vertex_index=min_vertex_index;
	state->vertex_count=vertex_count;

	SortingVertexBufferClass* vertex_buffer=static_cast<SortingVertexBufferClass*>(state->sorting_state.vertex_buffers[0]);
	WWASSERT(vertex_buffer);
	WWASSERT(state->vertex_count<=vertex_buffer->Get_Vertex_Count());

	D3DXMATRIX mtx=(D3DXMATRIX&)state->sorting_state.world*(D3DXMATRIX&)state->sorting_state.view;
	D3DXVECTOR3 vec=(D3DXVECTOR3&)bounding_sphere.Center;
	D3DXVECTOR4 transformed_vec;
	D3DXVec3Transform(
		&transformed_vec,
		&vec,
		&mtx); 
	state->transformed_center=transformed_vec[2];

	
	/// @todo lorenzen sez use a bucket sort here... and stop copying so much data so many times

	SortingNodeStruct* node=sorted_list.Head();
	while (node) {
		if (state->transformed_center>node->transformed_center) {
			if (sorted_list.Head()==sorted_list.Tail())
				sorted_list.Add_Head(state);
			else
				state->Insert_Before(node);
			break;
		}
		node=node->Succ();
	}
	if (!node) sorted_list.Add_Tail(state);

#ifdef WWDEBUG
	unsigned short* indices=NULL;
	SortingIndexBufferClass* index_buffer=static_cast<SortingIndexBufferClass*>(state->sorting_state.index_buffer);
	WWASSERT(index_buffer);
	indices=index_buffer->index_buffer;
	WWASSERT(indices);
	indices+=state->start_index;
	indices+=state->sorting_state.iba_offset;

	for (int i=0;i<state->polygon_count;++i) {
		unsigned short idx1=indices[i*3]-state->min_vertex_index;
		unsigned short idx2=indices[i*3+1]-state->min_vertex_index;
		unsigned short idx3=indices[i*3+2]-state->min_vertex_index;
		WWASSERT(idx1<state->vertex_count);
		WWASSERT(idx2<state->vertex_count);
		WWASSERT(idx3<state->vertex_count);
	}
#endif // WWDEBUG
}

// ----------------------------------------------------------------------------
//
// Insert triangles to the sorting system, with no bounding information.
//
// ----------------------------------------------------------------------------

// ?Insert_Triangles@SortingRendererClass@@SAXGGGG@Z
#if 0
void SortingRendererClass::Insert_Triangles(
	unsigned short start_index, 
	unsigned short polygon_count,
	unsigned short min_vertex_index,
	unsigned short vertex_count)
{
	SphereClass sphere(Vector3(0.0f,0.0f,0.0f),0.0f);
	Insert_Triangles(sphere,start_index,polygon_count,min_vertex_index,vertex_count);
}
#endif

// ----------------------------------------------------------------------------
//
// Flush all sorting polygons.
//
// ----------------------------------------------------------------------------

#define BFME_RELEASE_REFS(x) { if (x) { x->Release_Ref(); x = 0; } }

void Release_Refs(SortingNodeStruct* state)
{
	int i;
	for (i=0;i<MAX_VERTEX_STREAMS;++i) {
		BFME_RELEASE_REFS(state->sorting_state.vertex_buffers[i]);
	}
	BFME_RELEASE_REFS(state->sorting_state.index_buffer);
	BFME_RELEASE_REFS(state->sorting_state.material);
	for (i=0;i<*(const int *)(BfmeCurrentCaps+0x2b0);++i)
	{
		state->sorting_state.Textures[i].Clear();
	}
}

static unsigned overlapping_node_count;
static unsigned overlapping_polygon_count;
static unsigned overlapping_vertex_count;
static const unsigned MAX_OVERLAPPING_NODES=4096;
static SortingNodeStruct* overlapping_nodes[MAX_OVERLAPPING_NODES];

// ----------------------------------------------------------------------------

// ?Insert_To_Sorting_Pool@SortingRendererClass@@CAXPAVSortingNodeStruct@@@Z
void SortingRendererClass::Insert_To_Sorting_Pool(SortingNodeStruct* state)
{
	if (overlapping_node_count>=MAX_OVERLAPPING_NODES) {
		Release_Refs(state);
		WWASSERT(0);
		return;
	}

	overlapping_nodes[overlapping_node_count]=state;
	overlapping_vertex_count+=state->vertex_count;
	overlapping_polygon_count+=state->polygon_count;
	overlapping_node_count++;
}

// ----------------------------------------------------------------------------
//static unsigned prevLight = 0xffffffff;

static void Apply_Render_State(RenderStateStruct& render_state)
{



	DX8Wrapper::Set_Shader(render_state.shader);

	DX8Wrapper::Set_Material(render_state.material);

	for (int i=0;i<DX8Wrapper::Get_Current_Caps()->Get_Max_Textures_Per_Pass();++i) 
	{
		DX8Wrapper::Set_Texture(i,render_state.Textures[i]);
	}

	DX8Wrapper::_Set_DX8_Transform(D3DTS_WORLD,render_state.world);
	DX8Wrapper::_Set_DX8_Transform(D3DTS_VIEW,render_state.view);



  if (!render_state.material->Get_Lighting())
    return;
  //prevLight = render_state.lightsHash;

	if (render_state.LightEnable[0]) 
  {
    
    DX8Wrapper::Set_DX8_Light(0,&render_state.Lights[0]);
		if (render_state.LightEnable[1]) 
    {
			DX8Wrapper::Set_DX8_Light(1,&render_state.Lights[1]);
			if (render_state.LightEnable[2]) 
      {
				DX8Wrapper::Set_DX8_Light(2,&render_state.Lights[2]);
				if (render_state.LightEnable[3]) 
					DX8Wrapper::Set_DX8_Light(3,&render_state.Lights[3]);
				else 
					DX8Wrapper::Set_DX8_Light(3,NULL);
			}
			else 
				DX8Wrapper::Set_DX8_Light(2,NULL);
		}
		else 
			DX8Wrapper::Set_DX8_Light(1,NULL);
	}
	else 
		DX8Wrapper::Set_DX8_Light(0,NULL);


}

// ----------------------------------------------------------------------------
// ?Rva0012D4D0Apply@@YAXAAURenderStateStruct@@@Z @0x0012D4D0 387B. BFME2
// owning-handle apply: Set_Shader, manual material REF_PTR_SET with
// TheBoxTextureDirtyMask, BFME2Set_Texture loop over BfmeCurrentCaps+0x2b0,
// looped Set_DX8_Light with break, direct world/view SetTransform.
// Evidence: rowed Set_Shader 0x000662E5, rowed BFME2Set_Texture 0x0011F4B0,
// BFME1 donor sortingrenderer.cpp Rva009391B0::apply loop+break shape.
struct BFME2TextureRef { void *Ptr; };
void BFME2Set_Texture(unsigned stage, const struct BFME2TextureRef &texture);
extern unsigned TheBoxTextureDirtyMask;
// ?g_00DEE5DC@@3PAVVertexMaterialClass@@A: the global at this VA is ?ScreenMaterial@@3PAVVertexMaterialClass@@A; this name is an alias for it.
extern class VertexMaterialClass *ScreenMaterial;
extern struct IDirect3DDevice8 *g_d3dDevice;
extern unsigned g_00DEDA4C;
// ?g_00DEDA4C@@3IA: the global at this VA is ?matrix_changes@DX8Wrapper@@1IA; this name is an alias for it.
extern unsigned int g_00DEDA4C;
#pragma comment(linker, "/alternatename:?g_00DEDA4C@@3IA=?matrix_changes@DX8Wrapper@@1IA")
extern unsigned g_00DEDA98;

void Rva0012D4D0Apply(RenderStateStruct &render_state)
{
	DX8Wrapper::Set_Shader(render_state.shader);
	VertexMaterialClass *mat = render_state.material;
	if (mat)
		mat->Add_Ref();
	if (ScreenMaterial)
		ScreenMaterial->Release_Ref();
	TheBoxTextureDirtyMask |= 0x4000;
	ScreenMaterial = mat;
	for (int i = 0; i < *(const int *)((const unsigned char *)DX8Wrapper::Get_Current_Caps() + 0x2b0); ++i)
		BFME2Set_Texture(i, reinterpret_cast<const struct BFME2TextureRef &>(render_state.Textures[i]));
	if (render_state.material->Get_Lighting()) {
		for (int i = 0; i < 4; ++i) {
			if (!render_state.LightEnable[i]) {
				DX8Wrapper::Set_DX8_Light(i, NULL);
				break;
			}
			DX8Wrapper::Set_DX8_Light(i, &render_state.Lights[i]);
		}
	}
	++g_00DEDA4C;
	g_d3dDevice->SetTransform(D3DTS_WORLD, reinterpret_cast<const D3DMATRIX *>(&render_state.world));
	++g_00DEDA98;
	++g_00DEDA4C;
	g_d3dDevice->SetTransform(D3DTS_VIEW, reinterpret_cast<const D3DMATRIX *>(&render_state.view));
	++g_00DEDA98;
}

// ----------------------------------------------------------------------------

// BFME-only, no Zero Hour twin.  Flush_Sorting_Pool (0x00939FC0) inlines this
// test before each Apply_Render_State, and retail also keeps out-of-line copies
// of it.  This body byte-matches the copy at 0x0012D660, 181 bytes, under
// MSVC's private static convention (b in EAX, a on the stack), so the name
// carries that address.  The copy at 0x00939370 uses the same convention but
// does NOT reproduce from this TU -- its first byte is 0x19 where this body has
// the 0x55 prologue -- so it is left to the caller that owns its register state.
// The constant read at the top of the texture loop is BfmeCurrentCaps+0x2b0;
// the 0x278 in the first version of this body was the one byte the drift report
// still scored as different.
static __forceinline bool RenderStatesDifferRva0012D660(RenderStateStruct& a, RenderStateStruct& b)
{
	if (a.shader != b.shader) return true;
	if (a.material != b.material) return true;
	for (int i=0;i<*(const int *)(BfmeCurrentCaps+0x2b0);++i) {
		if (a.Textures[i] != b.Textures[i]) return true;
	}
	if (a.material->Get_Lighting()) {
		for (int i=0;i<4;++i) {
			if (a.LightEnable[i] != b.LightEnable[i]) return true;
		}
	}
	if (a.world != b.world) return true;
	if (a.view != b.view) return true;
	return false;
}

void SortingRendererClass::Flush_Sorting_Pool()
{
	if (!overlapping_node_count) return;

	SNAPSHOT_SAY(("SortingSystem - Flush \n"));

	// Fill dynamic index buffer with sorting index buffer vertices
	TempIndexStruct* tis=Get_Temp_Index_Array(overlapping_polygon_count);

	unsigned vertexAllocCount = overlapping_vertex_count;
	if (DynamicVBAccessClass::Get_Default_Vertex_Count() < DEFAULT_SORTING_VERTEX_COUNT)
		vertexAllocCount = DEFAULT_SORTING_VERTEX_COUNT;	//make sure that we force the DX8 dynamic vertex buffer to maximum size
	if (overlapping_vertex_count > vertexAllocCount)
		vertexAllocCount = overlapping_vertex_count;
	WWASSERT(DEFAULT_SORTING_VERTEX_COUNT == 1 || vertexAllocCount <= DEFAULT_SORTING_VERTEX_COUNT);
	DynamicVBAccessClass dyn_vb_access(BUFFER_TYPE_DYNAMIC_DX8,5,vertexAllocCount,0);
	unsigned vertex_array_offset=0;
	{
		DynamicVBAccessClass::WriteLock lock(&dyn_vb_access);
		VertexFormatXYZNDUV2* dest_verts=lock.data;

		unsigned polygon_array_offset=0;
		for (unsigned node_id=0;node_id<overlapping_node_count;++node_id) {
			SortingNodeStruct* state=overlapping_nodes[node_id];
			VertexFormatXYZNDUV2* src_verts=NULL;
			SortingVertexBufferClass* vertex_buffer=static_cast<SortingVertexBufferClass*>(state->sorting_state.vertex_buffers[0]);
			WWASSERT(vertex_buffer);
			src_verts=vertex_buffer->VertexBuffer;
			WWASSERT(src_verts);
			src_verts+=state->sorting_state.vba_offset;
			src_verts+=state->sorting_state.index_base_offset;
			src_verts+=state->min_vertex_index;

			// If you have a crash in here and "dest_verts" points to illegal memory area,
			// it is because D3D is in illegal state, and the only known cure is rebooting.
			// This illegal state is usually caused by Quake3-engine powered games such as MOHAA.
			memcpy(dest_verts, src_verts, sizeof(VertexFormatXYZNDUV2)*state->vertex_count);
			dest_verts += state->vertex_count;

			// Each term reads the node's matrices directly: through a Matrix4x4
			// reference, world[0][0] is a bare dereference and VC7 orders it after
			// world[0][3], where retail sums it before.
			float mtx02 = state->sorting_state.world[0][2]*state->sorting_state.view[2][2] + state->sorting_state.world[0][1]*state->sorting_state.view[1][2] + state->sorting_state.world[0][0]*state->sorting_state.view[0][2] + state->sorting_state.world[0][3]*state->sorting_state.view[3][2];
			float mtx12 = state->sorting_state.world[1][2]*state->sorting_state.view[2][2] + state->sorting_state.world[1][1]*state->sorting_state.view[1][2] + state->sorting_state.world[1][0]*state->sorting_state.view[0][2] + state->sorting_state.world[1][3]*state->sorting_state.view[3][2];
			float mtx22 = state->sorting_state.world[2][2]*state->sorting_state.view[2][2] + state->sorting_state.world[2][1]*state->sorting_state.view[1][2] + state->sorting_state.world[2][0]*state->sorting_state.view[0][2] + state->sorting_state.world[2][3]*state->sorting_state.view[3][2];
			float mtx32 = state->sorting_state.world[3][2]*state->sorting_state.view[2][2] + state->sorting_state.world[3][1]*state->sorting_state.view[1][2] + state->sorting_state.world[3][0]*state->sorting_state.view[0][2] + state->sorting_state.world[3][3]*state->sorting_state.view[3][2];

			unsigned short* indices=NULL;
			SortingIndexBufferClass* index_buffer=static_cast<SortingIndexBufferClass*>(state->sorting_state.index_buffer);
			WWASSERT(index_buffer);
			indices=index_buffer->index_buffer;
			WWASSERT(indices);
			indices+=state->start_index;
			indices+=state->sorting_state.iba_offset;

			if (mtx02 == 0.0f && mtx12 == 0.0f && mtx32 == 0.0f && mtx22 == 1.0f) {
				// The common case for particle systems.
				for (int i=0;i<state->polygon_count;++i) {
					unsigned short idx1=indices[i*3]-state->min_vertex_index;
					unsigned short idx2=indices[i*3+1]-state->min_vertex_index;
					unsigned short idx3=indices[i*3+2]-state->min_vertex_index;
					WWASSERT(idx1<state->vertex_count);
					WWASSERT(idx2<state->vertex_count);
					WWASSERT(idx3<state->vertex_count);
					const VertexFormatXYZNDUV2 *v1 = src_verts + idx1;
					const VertexFormatXYZNDUV2 *v2 = src_verts + idx2;
					const VertexFormatXYZNDUV2 *v3 = src_verts + idx3;
					unsigned array_index=i+polygon_array_offset;
					WWASSERT(array_index<overlapping_polygon_count);
					TempIndexStruct *tis_ptr = tis + array_index;
					tis_ptr->tri.i = idx1 + vertex_array_offset;
					tis_ptr->tri.j = idx2 + vertex_array_offset;
					tis_ptr->tri.k = idx3 + vertex_array_offset;
					tis_ptr->idx = node_id;
					tis_ptr->z = (v1->z + v2->z + v3->z)/3.0f;
					DEBUG_ASSERTCRASH((! _isnan(tis_ptr->z) && _finite(tis_ptr->z)), ("Triangle has invalid center"));
				}
			} else {
				for (int i=0;i<state->polygon_count;++i) {
					unsigned short idx1=indices[i*3]-state->min_vertex_index;
					unsigned short idx2=indices[i*3+1]-state->min_vertex_index;
					unsigned short idx3=indices[i*3+2]-state->min_vertex_index;
					WWASSERT(idx1<state->vertex_count);
					WWASSERT(idx2<state->vertex_count);
					WWASSERT(idx3<state->vertex_count);
					const VertexFormatXYZNDUV2 *v1 = src_verts + idx1;
					const VertexFormatXYZNDUV2 *v2 = src_verts + idx2;
					const VertexFormatXYZNDUV2 *v3 = src_verts + idx3;
					unsigned array_index=i+polygon_array_offset;
					WWASSERT(array_index<overlapping_polygon_count);
					TempIndexStruct *tis_ptr = tis + array_index;
					tis_ptr->tri.i = idx1 + vertex_array_offset;
					tis_ptr->tri.j = idx2 + vertex_array_offset;
					tis_ptr->tri.k = idx3 + vertex_array_offset;
					tis_ptr->idx = node_id;
					tis_ptr->z = (mtx02*(v1->x + v2->x + v3->x) +
												mtx12*(v1->y + v2->y + v3->y) +
												mtx22*(v1->z + v2->z + v3->z))/3.0f + mtx32;
					DEBUG_ASSERTCRASH((! _isnan(tis_ptr->z) && _finite(tis_ptr->z)), ("Triangle has invalid center"));
				}
			}

			state->min_vertex_index=vertex_array_offset;

			polygon_array_offset+=state->polygon_count;
			vertex_array_offset+=state->vertex_count;
		}
	}

	TempIndexStruct* end = tis + overlapping_polygon_count;
	Sort(tis, end);

	int total_overlapping_polygon_count = overlapping_polygon_count;

	while (total_overlapping_polygon_count > 0)
	{
		if ((total_overlapping_polygon_count*3) > 65535)
		{	//overflowed the index buffer, must break into multiple batches
			overlapping_polygon_count = 65535/3;
		}
		else
			overlapping_polygon_count = total_overlapping_polygon_count;

	unsigned polygonAllocCount = overlapping_polygon_count;
	if ((unsigned)(DynamicIBAccessClass::Get_Default_Index_Count()/3) < DEFAULT_SORTING_POLY_COUNT)
		polygonAllocCount = DEFAULT_SORTING_POLY_COUNT;	//make sure that we force the DX8 index buffer to maximum size
	if (overlapping_polygon_count > polygonAllocCount)
		polygonAllocCount = overlapping_polygon_count;
	WWASSERT(DEFAULT_SORTING_POLY_COUNT <= 1 || polygonAllocCount <= DEFAULT_SORTING_POLY_COUNT);

	DynamicIBAccessClass dyn_ib_access(BUFFER_TYPE_DYNAMIC_DX8,polygonAllocCount*3);
	{
		DynamicIBAccessClass::WriteLockClass lock(&dyn_ib_access);
		ShortVectorIStruct* sorted_polygon_index_array=(ShortVectorIStruct*)lock.Get_Index_Array();

		for (unsigned a=0;a<overlapping_polygon_count;++a) {
			sorted_polygon_index_array[a]=tis[a].tri;
		}
	}

	// Set index buffer and render!

	DX8Wrapper::Set_Index_Buffer(dyn_ib_access,0); // Override with this buffer (do something to prevent need for this!)
	DX8Wrapper::Set_Vertex_Buffer(dyn_vb_access); // Override with this buffer (do something to prevent need for this!)

	DX8Wrapper::Apply_Render_State_Changes();

	unsigned count_to_render=1;
	unsigned start_index=0;
	unsigned node_id=tis[0].idx;
	for (unsigned i=1;i<overlapping_polygon_count;++i) {
		if (node_id!=tis[i].idx) {
			RenderStateStruct& b = reinterpret_cast<RenderStateStruct &>(overlapping_nodes[tis[i].idx]->sorting_state);
			RenderStateStruct& a = reinterpret_cast<RenderStateStruct &>(overlapping_nodes[node_id]->sorting_state);
			if (RenderStatesDifferRva0012D660(a,b)) {
				SortingNodeStruct* state=overlapping_nodes[node_id];
				Rva0012D4D0Apply(reinterpret_cast<RenderStateStruct &>(state->sorting_state));

				DX8Wrapper::Draw_Triangles(
					start_index*3,
					count_to_render,
					0u,
					vertex_array_offset);

				count_to_render=0;
				start_index=i;
			}
			node_id=tis[i].idx;
		}
		count_to_render++;	//keep track of number of polygons of same kind
	}

	// Render any remaining polygons...
	if (count_to_render) {
		SortingNodeStruct* state=overlapping_nodes[node_id];
		Rva0012D4D0Apply(reinterpret_cast<RenderStateStruct &>(state->sorting_state));

		DX8Wrapper::Draw_Triangles(
			start_index*3,
			count_to_render,
			0u,
			vertex_array_offset);
	}

	// Release all references and return nodes back to the clean list for the frame...
	for (unsigned node_id=0;node_id<overlapping_node_count;++node_id) {
		SortingNodeStruct* state=overlapping_nodes[node_id];
		Release_Refs(state);
		clean_list.Add_Head(state);
	}
	total_overlapping_polygon_count -= overlapping_polygon_count;
	overlapping_node_count=0;
	overlapping_polygon_count=0;
	overlapping_vertex_count=0;
	}

	SNAPSHOT_SAY(("SortingSystem - Done flushing\n"));

}

// ----------------------------------------------------------------------------

// Retail 0x0012F190..0x0012FC98, 2824 bytes: Open-BFME-1's Flush (its
// 0x0093A810) with the pooled-node cap read from DEFAULT_SORTING_POLY_COUNT
// (data ledger 0x009B61F8), BFME2's inline render-state copy and an inlined
// Insert_To_Sorting_Pool. Flush_Sorting_Pool (0x0012E8C0) is its only call
// into the pool.
// ?Flush@SortingRendererClass@@SAXXZ
void SortingRendererClass::Flush()
{
	Matrix4x4 old_view;
	Matrix4x4 old_world;
	DX8Wrapper::Get_Transform(D3DTS_VIEW,old_view);
	DX8Wrapper::Get_Transform(D3DTS_WORLD,old_world);

	while (SortingNodeStruct* state=sorted_list.Head()) {
		state->Remove();

		if ((state->sorting_state.index_buffer_type==BUFFER_TYPE_SORTING || state->sorting_state.index_buffer_type==BUFFER_TYPE_DYNAMIC_SORTING) &&
			(state->sorting_state.vertex_buffer_types[0]==BUFFER_TYPE_SORTING || state->sorting_state.vertex_buffer_types[0]==BUFFER_TYPE_DYNAMIC_SORTING)) {
			if (state->polygon_count + overlapping_polygon_count >= DEFAULT_SORTING_POLY_COUNT) continue;
			Insert_To_Sorting_Pool(state);
		}
		else {
			DX8Wrapper::Set_Render_State(reinterpret_cast<const RenderStateStruct &>(state->sorting_state));
			DX8Wrapper::Draw_Triangles((unsigned)state->start_index,(unsigned)state->polygon_count,(unsigned)state->min_vertex_index,(unsigned)state->vertex_count);
			DX8Wrapper::Release_Render_State();
			Release_Refs(state);
			clean_list.Add_Head(state);
		}
	}

	bool old_enable=DX8Wrapper::_Is_Triangle_Draw_Enabled();
	DX8Wrapper::_Enable_Triangle_Draw(_EnableTriangleDraw);
	Flush_Sorting_Pool();
	DX8Wrapper::_Enable_Triangle_Draw(old_enable);

	DX8Wrapper::Set_Index_Buffer(0,0);
	DX8Wrapper::Set_Vertex_Buffer(0,0);
	total_sorting_vertices=0;

	DynamicIBAccessClass::_Reset(false);
	DynamicVBAccessClass::_Reset(false);

	DX8Wrapper::Set_Transform(D3DTS_VIEW,old_view);
	DX8Wrapper::Set_Transform(D3DTS_WORLD,old_world);
}

// ----------------------------------------------------------------------------

// SortingRendererClass::Deinit: defined in sortingrenderer.cpp (its row's unit).


// ----------------------------------------------------------------------------
//
// Insert a VolumeParticle triangle into the sorting system.
//
// ----------------------------------------------------------------------------

// Retail 0x00130410..0x00130A1E, 1550 bytes. Target evidence: the body is
// the 0x0012FE00 insert (same range checks, inlined Get_Render_State, depth
// formula and sorted insertion) except that both recorded counts and the
// node's polygon and vertex counts are multiplied by a sixth argument, which
// is Zero Hour's Insert_VolumeParticle layerCount. Like that sibling, BFME2
// takes the ranges as unsigned ints and rejects any above 65535.
// ?Insert_VolumeParticle@SortingRendererClass@@SAXABVSphereClass@@IIIII@Z
void SortingRendererClass::Insert_VolumeParticle(
	const SphereClass& bounding_sphere,
	unsigned start_index,
	unsigned polygon_count,
	unsigned min_vertex_index,
	unsigned vertex_count,
	unsigned layerCount)
{
	if (!WW3D::Is_Sorting_Enabled()) {
		DX8Wrapper::Draw_Triangles(start_index,polygon_count,min_vertex_index,vertex_count);
		return;
	}
	if (polygon_count > 65535 || vertex_count > 65535 ||
		start_index > 65535 || min_vertex_index > 65535) return;

	//FOR VOLUME_PARTICLE LOGIC:
	// WE MUST MULTIPLY THE VERTCOUNT AND POLYCOUNT BY THE VOLUME_PARTICLE DEPTH
	DX8_RECORD_SORTING_RENDER( polygon_count * layerCount,vertex_count * layerCount);//THIS IS VOLUME_PARTICLE SPECIFIC

	SortingNodeStruct* state=Get_Sorting_Struct();
	DX8Wrapper::Get_Render_State(reinterpret_cast<RenderStateStruct &>(state->sorting_state));

	state->start_index=start_index;
	state->min_vertex_index=min_vertex_index;
	state->polygon_count=polygon_count * layerCount;//THIS IS VOLUME_PARTICLE SPECIFIC
	state->vertex_count=vertex_count * layerCount;//THIS IS VOLUME_PARTICLE SPECIFIC

	const Matrix4& a = state->sorting_state.world;
	const Matrix4& b = state->sorting_state.view;
	const Vector3& v = bounding_sphere.Center;
	state->transformed_center =
		(((float)(a[2][2]*b[2][2]) + (float)(a[2][1]*b[1][2]) + a[2][0]*b[0][2]) + a[2][3]*b[3][2])*v.Z +
		(((float)(a[1][2]*b[2][2]) + (float)(a[1][1]*b[1][2]) + a[1][0]*b[0][2]) + a[1][3]*b[3][2])*v.Y +
		(((float)(a[0][2]*b[2][2]) + (float)(a[0][1]*b[1][2]) + ((const volatile float&)a[0][0])*b[0][2]) + a[0][3]*b[3][2])*v.X +
		(((float)(a[3][2]*b[2][2]) + (float)(a[3][1]*b[1][2]) + a[3][0]*b[0][2]) + a[3][3]*b[3][2]);

	SortingNodeStruct* node=sorted_list.Head();
	while (node) {
		if (state->transformed_center>node->transformed_center) {
			if (sorted_list.Head()==sorted_list.Tail())
				sorted_list.Add_Head(state);
			else
				state->Insert_Before(node);
			break;
		}
		node=node->Succ();
	}
	if (!node) sorted_list.Add_Tail(state);
}

// ?TheBoxTextureDirtyMask@@3IA: the global at this VA is ?render_state_changed@DX8Wrapper@@1IA; this name is an alias for it.
extern unsigned int TheBoxTextureDirtyMask;
#pragma comment(linker, "/alternatename:?TheBoxTextureDirtyMask@@3IA=?render_state_changed@DX8Wrapper@@1IA")
#pragma comment(linker, "/alternatename:?BFME2RenderStateChanged@@3IA=?render_state_changed@DX8Wrapper@@1IA")
// ?g_00DEDA98@@3IA: the global at this VA is ?number_of_DX8_calls@@3IA; this name is an alias for it.
extern unsigned int g_00DEDA98;
#pragma comment(linker, "/alternatename:?g_00DEDA98@@3IA=?number_of_DX8_calls@@3IA")
#pragma comment(linker, "/alternatename:?g_bfmeCountTDB@@3HA=?number_of_DX8_calls@@3IA")
// ?g_d3dDevice@@3PAUIDirect3DDevice8@@A: the global at VA 0xdeda34 is ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A.
#pragma comment(linker, "/alternatename:?g_d3dDevice@@3PAUIDirect3DDevice8@@A=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")
// ?TheBoxTextureDirtyMask@@3IA: the global at VA 0xdec4f4 is ?render_state_changed@DX8Wrapper@@1IA.
#pragma comment(linker, "/alternatename:?TheBoxTextureDirtyMask@@3IA=?render_state_changed@DX8Wrapper@@1IA")
// ?BfmeCurrentCaps@@3PAEA: the global at VA 0xdeda7c is ?CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A.
#pragma comment(linker, "/alternatename:?BfmeCurrentCaps@@3PAEA=?CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A")
// ?g_00DEDA98@@3IA: the global at VA 0xdeda98 is ?number_of_DX8_calls@@3IA.
#pragma comment(linker, "/alternatename:?g_00DEDA98@@3IA=?number_of_DX8_calls@@3IA")

// Retail 0x0012FE00..0x001303F0, 1520 bytes, ending at RET (no padding).
// BFME1 sortingrenderer.cpp at d6db6bfa4fd3 provides the sorted-insertion
// algorithm. Target evidence: DX8DrawTrianglesDispatch's call at 0x00120613
// passes an xyz center (not a full SphereClass) and four DWORD ranges; this
// body checks every range before narrowing. Its node offsets agree with
// SortingNodeStructDtor.cpp: state +0x0C, depth +0x29C, ranges +0x2A0..+0x2A6.
// The original source name is not independently proved; retain the neutral
// ABI spelling already used by the verified dispatch and PointGroup bank.
struct TargetCenter3 {
	float x, y, z;
	TargetCenter3(float a, float b, float c) : x(a), y(b), z(c) {}
};
class BfmeSortingDispatchAt0012FE00 {
public:
	static void Insert(const TargetCenter3& center, unsigned start_index,
		unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);
};

void BfmeSortingDispatchAt0012FE00::Insert(const TargetCenter3& center,
	unsigned start_index, unsigned polygon_count, unsigned min_vertex_index,
	unsigned vertex_count)
{
	if (!WW3D::Is_Sorting_Enabled()) {
		DX8Wrapper::Draw_Triangles(start_index, polygon_count, min_vertex_index, vertex_count);
		return;
	}
	if (polygon_count > 65535 || vertex_count > 65535 ||
		start_index > 65535 || min_vertex_index > 65535) return;
	DX8_RECORD_SORTING_RENDER(polygon_count, vertex_count);
	SortingNodeStruct* state = Get_Sorting_Struct();
	DX8Wrapper::Get_Render_State(reinterpret_cast<RenderStateStruct&>(state->sorting_state));
	state->start_index = start_index;
	state->polygon_count = polygon_count;
	state->min_vertex_index = min_vertex_index;
	state->vertex_count = vertex_count;

	const Matrix4& a = state->sorting_state.world;
	const Matrix4& b = state->sorting_state.view;
	const TargetCenter3& v = center;
	// Only depth is consumed: project the center through world * view.
	// Float intermediates preserve retail's 2,1,0,3 dot-product addition
	// order. Plain expressions reassociate to 2,1,3,0 (16 operand bytes differ).
	// At 0x0013031E the world[0][0] read precedes view[0][2]; the ordered
	// read below preserves that last otherwise-commuted pair without spills.
	state->transformed_center =
		(((float)(a[2][2]*b[2][2]) + (float)(a[2][1]*b[1][2]) + a[2][0]*b[0][2]) + a[2][3]*b[3][2])*v.z +
		(((float)(a[1][2]*b[2][2]) + (float)(a[1][1]*b[1][2]) + a[1][0]*b[0][2]) + a[1][3]*b[3][2])*v.y +
		(((float)(a[0][2]*b[2][2]) + (float)(a[0][1]*b[1][2]) + ((const volatile float&)a[0][0])*b[0][2]) + a[0][3]*b[3][2])*v.x +
		(((float)(a[3][2]*b[2][2]) + (float)(a[3][1]*b[1][2]) + a[3][0]*b[0][2]) + a[3][3]*b[3][2]);

	SortingNodeStruct* node = sorted_list.Head();
	while (node) {
		if (state->transformed_center > node->transformed_center) {
			if (sorted_list.Head() == sorted_list.Tail()) sorted_list.Add_Head(state);
			else state->Insert_Before(node);
			break;
		}
		node = node->Succ();
	}
	if (!node) sorted_list.Add_Tail(state);
}
