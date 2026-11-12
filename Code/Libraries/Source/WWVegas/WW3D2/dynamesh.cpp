// cl: /Ireference/shims/dynamesh_material /Ireference/shims/bfmestages /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Bind the UV accessor to the separately matched native D1F40 owner.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#define BFME_MESHMATDESC_UV_ARRAY_EXTERNAL
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// stlport
// Use the verified out-of-line material getter; the ordinary /O2 header copy
// differs from retail and otherwise wins COMDAT selection for new consumers.
// readable body of ?Set_Material@DX8Wrapper@@SAXPBVVertexMaterialClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
// Link view: Matrix4(Vector4 x4), Transpose and the Matrix3D overloads stay inline without emitting
// non-/O1 copies that lose to retail's owners (0x0006A34E, 0x0006A3D1).
#include "../../../../../reference/shims/bfme_matrix4_rows_link/matrix4_zh_rows_link.h"
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

/*************************************************************************** 
 ***    C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S     *** 
 *************************************************************************** 
 *                                                                         * 
 *                 Project Name : Commando                                 * 
 *                                                                         * 
 *                     $Archive:: /Commando/Code/ww3d2/dynamesh.cpp       $* 
 *                                                                         * 
 *                      $Author:: Greg_h                                  $* 
 *                                                                         * 
 *                     $Modtime:: 12/03/01 4:50p                          $* 
 *                                                                         * 
 *                    $Revision:: 25                                      $* 
 *                                                                         * 
 *-------------------------------------------------------------------------* 
 * Functions:                                                              * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// ZH meshgeometry.h's Get_Flag and Set_Flag use Flags at +0x14; BFME2's MeshGeometryClass keeps it at
// +0x18 (retail 0x000D1AA1, 0x001494B0). Every use here is inlined, so
// TU-local names keep this unit's copies, first in link order, from displacing retail's.
#define Get_Flag Get_Flag_Zh
#define Set_Flag Set_Flag_Zh
#include "matinfo.h" // load the declaration-only TU shim before sibling includes
#include "dx8wrapper.h" // the bfmestages shim has to win the include guard over the ZH sibling
// Keep the native shader accessor at 0x00143370: its Shader array is
// +0x98, whereas this legacy donor view places it at +0x94.
#define BFME_MESHMATDESC_SINGLE_SHADER_EXTERNAL
// Preserve this TU's ZH layout while binding color-array calls to the native owner.
#include "../../../../../reference/shims/dynamesh_color_link/meshmatdesc.h"
// Only the four ledger-owned leaves remain in this unit. The old Zero Hour
// renderer and constructors were unrowed; their only outside consumer was
// the unrowed shatter code removed in the same change.
// Preserve the existing getter identity and the native E4/E8 accesses without
// constructing the donor RenderObj/DynamicMesh hierarchy or its vtables.
class DynamicMeshClass
{
public:
    virtual int Get_Num_Polys() const;
    virtual int Get_Num_Vertices() const;
private:
    char m_unmodelled04[0xE0];
    int PolyCount;
    int VertCount;
};

int DynamicMeshClass::Get_Num_Polys() const
{
    // Retain this unit's existing inline material leaf by ordinary address
    // use, as ProductionPrerequisite.cpp retains its push_back emission.
    int (MaterialInfoClass::*addMaterial)(VertexMaterialClass *) =
        &MaterialInfoClass::Add_Vertex_Material;
    (void)addMaterial;
    return PolyCount;
}

int DynamicMeshClass::Get_Num_Vertices() const
{
    VertexMaterialClass *(MeshMatDescClass::*peekMaterial)(int) const =
        &MeshMatDescClass::Peek_Single_Material;
    (void)peekMaterial;
    return VertCount;
}
