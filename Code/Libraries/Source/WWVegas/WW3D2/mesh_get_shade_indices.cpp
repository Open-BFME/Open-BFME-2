// cl: /Ireference/shims/bfmerendobj /arch:SSE2 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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

// Retail's RefCountClass inline copies (Release_Ref 0x005D1A7D, scalar deleting
// dtor 0x00072899) are the size form: compile refcount.h for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
// Keep the reference base's proven inline destructor and its size-optimized
// deleting wrapper; the canonical geometry layout uses this same 8-byte base.
#define BFME2_WWLIB_REFCOUNTDATA_H
#pragma optimize("", on)
#include "MeshGeometryClass.h"
#include "sharebuf.h"

// This specialization is rowed in its canonical defining unit. Keep this TU
// a client so it does not emit a conflicting inline destructor copy.
template <> ShareBufferClass<unsigned long>::~ShareBufferClass(void);

// Keep the existing emission anchor while using the canonical geometry layout.
struct BfmeMeshShadeIndicesAccessor : MeshGeometryClass
{
	typedef uint32 *(MeshGeometryClass::*GetShadeIndicesFn)(bool);
	static GetShadeIndicesFn emit_get_shade_indices()
	{
		return &BfmeMeshShadeIndicesAccessor::get_shade_indices;
	}
};

BfmeMeshShadeIndicesAccessor::GetShadeIndicesFn kGetShadeIndices = BfmeMeshShadeIndicesAccessor::emit_get_shade_indices();

inline uint32 *MeshGeometryClass::get_shade_indices(bool create)
{
	if (create && !VertexShadeIdx) {
		VertexShadeIdx = NEW_REF(ShareBufferClass<uint32>,(VertexCount, "MeshGeometryClass::VertexShadeIdx"));
	}
	if (VertexShadeIdx) {
		return VertexShadeIdx->Get_Array();
	}
	return NULL;
}

// get_shade_indices is a header inline elsewhere: another unit emits a
// select-any copy, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
struct BfmeMeshShadeIndicesEmitter : MeshGeometryClass
{
	static void emit(BfmeMeshShadeIndicesEmitter *p);
};
#pragma inline_depth(0)
// ?emit@BfmeMeshShadeIndicesEmitter@@SAXPAU1@@Z present-unmatched
void BfmeMeshShadeIndicesEmitter::emit(BfmeMeshShadeIndicesEmitter *p)
{
	p->MeshGeometryClass::get_shade_indices(false);
}
#pragma inline_depth()
