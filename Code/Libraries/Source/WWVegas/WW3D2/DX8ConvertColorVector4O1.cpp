// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
//
// DX8Wrapper::Convert_Color(unsigned) (0x000EDF46): retail holds one size-optimised (/O1) out-of-line copy of the header body.
// The pointer constants or anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#include "dx8wrapper.h"
#include "w3d_file.h"
#include "simplevec.h"
#include "vector2.h"
#include "vector3i.h"
#pragma intrinsic(_ReadWriteBarrier)

#include "dx8wrapper.h"
extern Vector4 (*const g_bfmeConvertColorU32Anchor)(unsigned);
Vector4 (*const g_bfmeConvertColorU32Anchor)(unsigned) = &DX8Wrapper::Convert_Color;
