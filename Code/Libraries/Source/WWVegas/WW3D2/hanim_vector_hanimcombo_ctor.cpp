// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// VectorClass<HAnimComboDataClass*>::~VectorClass() at 0x00196B50, split out
// of the hanim.cpp instantiation chain (built /G7 like hanim_vector_float_ctor.cpp).
// HAnimComboClass ctors 0x196B80/0x197650 install DynamicVectorClass vtable
// 0xBD5E88; its deleting dtor 0x197470 calls this body, which restores the
// VectorClass base vtable 0xBD5E58. The (int, T const *) ctor this TU once
// claimed at 0x001A36D0 installs 0xBD6C0C and belongs to the AggregateDefClass
// subobject list (VectorClass<W3dAggregateSubobjectStruct*>, agg_def.cpp).
// Headers copied from hanim.cpp.
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
#define Matrix4x4 Matrix4
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#include "hanim.h"
#include "assetmgr.h"
#include "htree.h"
#include "motchan.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"

template VectorClass<HAnimComboDataClass*>::~VectorClass();

// ??_G?$DynamicVectorClass@PAVHAnimComboDataClass@@@@UAEPAXI@Z at 0x00197470 (30B):
// slot 0 of DynamicVectorClass vtable 0x7D5E88 installed by HAnimComboClass
// ctors 0x196B80/0x197650; calls rowed ??1 VectorClass 0x196B50 then delete.
template class DynamicVectorClass<HAnimComboDataClass *>;
