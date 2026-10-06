// cl: /Ireference/shims/meshgeom /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// Size-optimised (/O1) emission of the MeshModelClass::Get_Shader header inline.
//
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
#define MESH_SINGLE_MATERIAL_HACK		0		// (gth) forces all multi-material meshes to use their first material only. (NOT RECOMMENDED, TESTING ONLY!)
#define MESH_FORCE_STATIC_SORT_HACK	0		// (gth) forces all sorting meshes to use static sort level 1 instead.

extern ShaderClass (MeshModelClass::*const g_bfmeMeshModelGetShaderAnchor)(int, int) const;
ShaderClass (MeshModelClass::*const g_bfmeMeshModelGetShaderAnchor)(int, int) const = &MeshModelClass::Get_Shader;
