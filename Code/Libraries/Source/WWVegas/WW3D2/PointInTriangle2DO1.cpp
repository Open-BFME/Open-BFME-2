// cl: /Ireference/shims/meshgeom /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// Point_In_Triangle_2D (0x0027EAFC): retail holds one size-optimised (/O1) out-of-line copy of the header body.
// The pointer constants or anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "meshgeometry.h"
#include "always.h"
#pragma push_macro("W3DMPO_GLUE")
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "aabtree.h"
#pragma pop_macro("W3DMPO_GLUE")
#include "chunkio.h"
#include "aabox.h"
#include "obbox.h"
#include "sphere.h"
#include "plane.h"
#include "wwdebug.h"
#include "wwmemlog.h"
#include "w3d_file.h"
#include "vp.h"
#include "htree.h"
#include "matrix4.h"
#include "rinfo.h"
#include "camera.h"
#if (OPTIMIZE_PLANEEQ_RAM)
#endif
#if (OPTIMIZE_VNORM_RAM)
#endif

extern bool (*const g_bfmePointInTriangle2DAnchor)(const Vector3 &, const Vector3 &, const Vector3 &, const Vector3 &, int, int, unsigned char &);
bool (*const g_bfmePointInTriangle2DAnchor)(const Vector3 &, const Vector3 &, const Vector3 &, const Vector3 &, int, int, unsigned char &) = &Point_In_Triangle_2D;
