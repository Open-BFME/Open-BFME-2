// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// OBBoxClass::Transform (0x000B2A4C) from obbox.h: retail holds one size-optimised (/O1)
// out-of-line copy.
// The pointer constants and anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#define Matrix4x4 Matrix4
// LINK-COMDAT: Matrix3D::Transform_Vector is __forceinline in matrix3d.h, so
// this TU emits a COMDAT copy that must match the kept (frameless, /O2-style)
// copy from camera.cpp. Our /O1 row inlines it, so it cannot be declared;
// compile the header inline with the kept flags while OBBoxClass::Transform
// (from obbox.h below) keeps /O1.
#pragma optimize("ty", on)
#include "matrix3d.h"
#pragma optimize("", on)
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#include "mesh.h"
#include <assert.h>
#include <string.h>
#include "w3d_file.h"
#include "assetmgr.h"
#include "w3derr.h"
#include "wwdebug.h"
#include "vertmaterial.h"
#include "shader.h"
#include "matinfo.h"
#include "htree.h"
#include "meshbuild.h"
#include "tri.h"
#include "aaplane.h"
#include "aabtree.h"
#include "chunkio.h"
#include "w3d_util.h"
#include "meshmdl.h"
#include "meshgeometry.h"
#include "ww3d.h"
#include "camera.h"
#include "texture.h"
#include "rinfo.h"
#include "coltest.h"
#include "inttest.h"
#include "decalmsh.h"
#include "decalsys.h"
#include "dx8polygonrenderer.h"
#include "dx8indexbuffer.h"
#include "dx8renderer.h"
#include "visrasterizer.h"
#include "wwmemlog.h"
#include "dx8rendererdebugger.h"
#include <stdio.h>
#include "wwprofile.h"
#if (OPTIMIZE_PLANEEQ_RAM)
#define COMPUTE_NORMALS
#endif

extern void (*const g_bfmeOBBoxTransformAnchor)(const Matrix3D &, const OBBoxClass &, OBBoxClass *);
void (*const g_bfmeOBBoxTransformAnchor)(const Matrix3D &, const OBBoxClass &, OBBoxClass *) = &OBBoxClass::Transform;
