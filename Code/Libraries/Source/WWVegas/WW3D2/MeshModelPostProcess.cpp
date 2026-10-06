// cl: /Ireference/shims/meshgeom /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// MeshModelClass::post_process, retail 0x00189C60 (102 bytes). Dedicated TU:
// the marker-less meshmdlio.cpp port cannot take another row without a full
// marker sweep, so the BFME2 shape lives here with the same headers and flags
// as that TU. BFME1 base minus the ZH fog activation block
// (Get_Instance/Get_Activate_Fog_On_Load/post_process_fog) and the overbright
// rewrite block, both absent from retail: its only REL32 sites are the two
// Disable_Backface_Culling calls to 0x00188670 (pinned in symbols.csv), then
// the SORT check tail-jumps to compute_static_sort_levels.
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

#include "meshgeometry.h"	// the meshgeom shim has to win the include guard before meshmdl.h reaches the reference copy
#include "meshmdl.h"
#include "aabtree.h"
#include "matinfo.h"
#include "vertmaterial.h"
#include "shader.h"
#include "texture.h"
#include "chunkio.h"
#include "w3derr.h"
#include "w3d_file.h"
#include "w3d_util.h"
#include "assetmgr.h"
#include "simplevec.h"
#include "realcrc.h"
#include "dx8wrapper.h"

#include <stdio.h>

#ifdef _UNIX
#include "osdep/osdep.h"
#endif

void MeshModelClass::post_process()
{
	// skinned meshes should not have cull trees
	if (Get_Flag(MeshGeometryClass::SKIN)) {
		if (CullTree) {
			REF_PTR_RELEASE(CullTree);
		}
	}

	// turn off backface culling if the mesh is supposed to be two-sided
	if (Get_Flag(MeshGeometryClass::TWO_SIDED)) {

		DefMatDesc->Disable_Backface_Culling();
		if (AlternateMatDesc != NULL) {
			AlternateMatDesc->Disable_Backface_Culling();
		}

	}

	// if the mesh is sorting, pick an appropriate static sort level
	// if default isn't set
	if (Get_Flag(SORT) && SortLevel==SORT_LEVEL_NONE && WW3D::Is_Munge_Sort_On_Load_Enabled()) {
		compute_static_sort_levels();
	}
}
