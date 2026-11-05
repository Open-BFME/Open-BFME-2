// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// auto_inline(off) keeps that /O1 iterator out of line: otherwise the /O2
// ShareBufferClass<Vector3> constructor inlines it and drops the Vector3
// construction loop that retail's copy (0x00169780) still calls ??_H for.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
#pragma auto_inline(off)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma auto_inline(on)
#pragma optimize("", on)

#include <string.h>
// Retail's out-of-line RefCountClass deleting-dtor copy is the /O1 form
// (pop ecx after the delete call); this TU builds /G7 which emits add esp,4
// instead. Compile just the base class for size so our COMDAT matches the
// first copy in link order. Code this TU's rows inline keeps this TU's flags.
#pragma optimize("s", on)
#include "refcount.h"
// Keep the reference base's proven inline destructor and its size-optimized
// deleting wrapper; the canonical geometry layout uses this same 8-byte base.
#define BFME2_WWLIB_REFCOUNTDATA_H
#pragma optimize("", on)
#include "MeshGeometryClass.h"
#include "sharebuf.h"
#include "vector3.h"

// Their byte-matched specializations live in MeshGeometryShareBufferInstantiations.cpp.
// Do not implicitly re-emit their virtual destructors in this TU.
template <> ShareBufferClass<Vector3>::~ShareBufferClass();

// MeshGeometryClass::get_vert_normals(bool), retail 0x0016AAE0, 170 bytes.
// VertexCount is at +0x28, VertexNorm at +0x38, slot3C at +0x3C.
struct BfmeMeshVertNormalsAccessor : MeshGeometryClass
{
	typedef Vector3 *(MeshGeometryClass::*GetVertNormalsFn)(bool);
	static GetVertNormalsFn emit_get_vert_normals()
	{
		return &BfmeMeshVertNormalsAccessor::get_vert_normals;
	}
};

BfmeMeshVertNormalsAccessor::GetVertNormalsFn kGetVertNormals = BfmeMeshVertNormalsAccessor::emit_get_vert_normals();

Vector3 *MeshGeometryClass::get_vert_normals(bool alternate_format)
{
	if (alternate_format) {
		if (!slot3C) {
			slot3C = new ShareBufferClass<Vector3>(VertexCount, "MeshGeometryClass::VertexNorm", 0);
			slot3C->Clear();
		}
		return slot3C->Get_Array();
	}
	return VertexNorm->Get_Array();
}
