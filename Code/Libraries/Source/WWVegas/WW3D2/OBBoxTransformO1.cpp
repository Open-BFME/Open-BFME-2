// cl: /Ireference/shims/bfme_lineseg_math_link /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// OBBoxClass::Transform (0x000B2A4C) from obbox.h: retail holds one size-optimised (/O1)
// out-of-line copy.
// The pointer constants and anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#define Matrix4x4 Matrix4
// Keep the transform algorithm inline in the /O1 OBBox body without emitting
// an unused competing Matrix3D helper. The scoped view preserves its layout
// and complete inline definitions; it adds no imported call or address.
#pragma optimize("ty", on)
#include "matrix3d.h"
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
