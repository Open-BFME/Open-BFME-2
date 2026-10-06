// cl: /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// RenderObjClass::Set_Sub_Object_Transforms_Dirty (0x0006334D): retail holds one size-optimised (/O1) out-of-line copy of the header body.
// The pointer constants or anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#define Matrix4x4 Matrix4
#define strdup __bfme_strdup_dllimport
#include <sweep/winbase_shim.h>
#include <string.h>
#define _CRTIMP
#include "rendobj.h"	// the scoped BFME2 RenderObj layout and slots must win the include guard
#include "winbase_shim.h"
#undef strdup

extern void (RenderObjClass::*const g_bfmeSetSubObjDirtyAnchor)(bool);
void (RenderObjClass::*const g_bfmeSetSubObjDirtyAnchor)(bool) = &RenderObjClass::Set_Sub_Object_Transforms_Dirty;
