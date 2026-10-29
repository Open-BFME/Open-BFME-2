// cl: /FIshader.h /Ireference/shims/bfmeshader /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
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

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "dx8caps.h" // BFME2 DX8Caps layout (MaxTexturesPerPass at +0x2B0) has to win the include guard over the ZH sibling
#include "sortingrenderer.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8wrapper.h"
#include "vertmaterial.h"
#include "texture.h"
#include "d3d8.h"
#include "D3dx8math.h"
#include "statistics.h"
#include <wwprofile.h>
#include <algorithm>

#ifdef _INTERNAL
// for occasional debugging...
// #pragma optimize("", off)
// #pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

bool SortingRendererClass::_EnableTriangleDraw=true;
// One external owner for the state shared with SortingRendererBFME1.cpp.
extern "C" {
unsigned DEFAULT_SORTING_POLY_COUNT = 16384;
unsigned DEFAULT_SORTING_VERTEX_COUNT = 32768;
}

// ?SetMinVertexBufferSize@SortingRendererClass@@SAXI@Z
void SortingRendererClass::SetMinVertexBufferSize( unsigned val )
{
	DEFAULT_SORTING_VERTEX_COUNT = val;
	DEFAULT_SORTING_POLY_COUNT = val/2;	//typically have 2:1 vertex:triangle ratio.
}

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

bool operator <(const TempIndexStruct &l, const TempIndexStruct &r);
bool operator <=(const TempIndexStruct &l, const TempIndexStruct &r);
bool operator >(const TempIndexStruct &l, const TempIndexStruct &r);
bool operator >=(const TempIndexStruct &l, const TempIndexStruct &r);
bool operator ==(const TempIndexStruct &l, const TempIndexStruct &r);
// ----------------------------------------------------------------------------
static
void InsertionSort(TempIndexStruct *begin, TempIndexStruct *end)
{
	for (TempIndexStruct *iter = begin + 1; iter < end; ++iter) {
		TempIndexStruct val = iter[0];
		TempIndexStruct *insert = iter;
		while (insert != begin && insert[-1] > val) {
			insert[0] = insert[-1];
			insert -= 1;
		}
		insert[0] = val;
	}
}

// ----------------------------------------------------------------------------
// Sort (0x0012DCF0) and the comparison operators are defined in
// SortingRendererBFME1.cpp, retail's unit for Flush_Sorting_Pool: it keeps
// overlapping_polygon_count in a register across the Sort call, which VC7 does
// only when Sort and its callees are compiled in the same unit.
void Sort(TempIndexStruct *begin, TempIndexStruct *end);

// ----------------------------------------------------------------------------

class SortingNodeStruct : public DLNodeClass<SortingNodeStruct>
{
	// BFME: global operator new/delete (retail Deinit @0x93BD60 calls 0x881EB0),
	// not W3DMPO pool free — drop W3DMPO_GLUE (same as MatBuffer/TexBuffer).

public:
	RenderStateStruct sorting_state;

	SphereClass bounding_sphere;

	Vector3 transformed_center;
	unsigned short start_index;			// First index used in the ib
	unsigned short polygon_count;			// Polygon count to process (3 indices = one polygon)
	unsigned short min_vertex_index;		// First index used in the vb
	unsigned short vertex_count;			// Number of vertices used in vb
public:
	SortingNodeStruct();
public:
	~SortingNodeStruct();
};

static DLListClass<SortingNodeStruct> sorted_list;
static DLListClass<SortingNodeStruct> clean_list;
extern "C" { unsigned total_sorting_vertices; }

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

extern "C" {
TempIndexStruct* temp_index_array;
unsigned temp_index_array_count;
}

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

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/SortingRendererInsertTrianglesThunk.cpp

// ----------------------------------------------------------------------------
//
// Insert triangles to the sorting system, with no bounding information.
//
// ----------------------------------------------------------------------------

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/SortingRendererInsertTrianglesThunk.cpp

// ----------------------------------------------------------------------------
//
// Flush all sorting polygons.
//
// ----------------------------------------------------------------------------

// Release_Refs: defined in SortingRendererBFME1.cpp (its row's unit).
void Release_Refs(SortingNodeStruct* state);

static unsigned overlapping_node_count;
static unsigned overlapping_polygon_count;
static unsigned overlapping_vertex_count;
static const unsigned MAX_OVERLAPPING_NODES=4096;
static SortingNodeStruct* overlapping_nodes[MAX_OVERLAPPING_NODES];

// ----------------------------------------------------------------------------

// SortingRendererClass::Insert_To_Sorting_Pool: defined in SortingRendererBFME1.cpp (its row's unit).

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

// Flush_Sorting_Pool (0x0012E8C0) and the helpers it emits are defined only in
// SortingRendererBFME1.cpp, retail's unit for it; a second strong copy here made both units fail to link.

// ----------------------------------------------------------------------------

// ?Flush@SortingRendererClass@@SAXXZ
// Body in sortingrenderer_Flush.asm (exact 2531B retail).

// ----------------------------------------------------------------------------

// ?Deinit@SortingRendererClass@@SAXXZ
void SortingRendererClass::Deinit()
{
	SortingNodeStruct *head = NULL;

	//
	//	Flush the sorted list
	//
	while ((head = sorted_list.Head ()) != NULL) {
		sorted_list.Remove_Head ();
		delete head;
	}

	//
	//	Flush the clean list
	//
	while ((head = clean_list.Head ()) != NULL) {
		clean_list.Remove_Head ();
		delete head;
	}

	delete[] temp_index_array;
	temp_index_array=NULL;
	temp_index_array_count=0;
}


// ----------------------------------------------------------------------------
//
// Insert a VolumeParticle triangle into the sorting system.
//
// ----------------------------------------------------------------------------

// Insert_VolumeParticle uses unsigned ranges and is defined in SortingRendererBFME1.cpp.

template void DLListClass<SortingNodeStruct>::Add_Head(DLNodeClass<SortingNodeStruct> *);
template void DLListClass<SortingNodeStruct>::Add_Tail(DLNodeClass<SortingNodeStruct> *);
template void DLNodeClass<SortingNodeStruct>::Insert_After(DLNodeClass<SortingNodeStruct> *);
template void DLNodeClass<SortingNodeStruct>::Insert_Before(DLNodeClass<SortingNodeStruct> *);

// ?bfmeEmitIsSortingEnabled absent-from-retail
bool bfmeEmitIsSortingEnabled()
{
    return WW3D::Is_Sorting_Enabled();
}
