// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// SimpleDynVecClass<Vector3>::Delete (0x00100306): retail holds one size-optimised (/O1) out-of-line copy of the template body.
// The pointer constants or anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#include "../../../../../reference/shims/bfmesegline/rendobj.h" // scoped retail collision slots
#include "segline.h"
#include "ww3d.h"
#include "rinfo.h"
#include "predlod.h"
#include "v3_rnd.h"
#include "texture.h"
#include "coltest.h"
#include "w3d_file.h"
#include "texture.h"
#include "dx8wrapper.h"
#include "vp.h"
#include "vector3i.h"
#include "sortingrenderer.h"

// This TU is a client of the Vector3 Shrink specialization: the kept /O2 copy
// lives in decalmsh.cpp, so do not emit the /O1 copy here.
template <> bool SimpleDynVecClass<Vector3>::Shrink(void);

extern bool (SimpleDynVecClass<Vector3>::*const g_bfmeDynVecV3DeleteAnchor)(int, bool);
bool (SimpleDynVecClass<Vector3>::*const g_bfmeDynVecV3DeleteAnchor)(int, bool) = &SimpleDynVecClass<Vector3>::Delete;
