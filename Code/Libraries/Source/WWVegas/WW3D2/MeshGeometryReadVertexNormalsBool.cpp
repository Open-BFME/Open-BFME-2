// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ?read_vertex_normals@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@_N@Z @0x0016AF40 50B.
// Bulk normal-chunk reader for MeshModel::read_chunks 0x18B790 dispatch.
// Target facts (retail 0x16AF40, 50B, ret8 at 0x16AF6E, end 0x16AF72):
// - thiscall (cload&, bool), bool at [esp+8], this kept in ESI across getter.
// - calls get_vert_normals(bool) 0x16AAE0 (matched mesh_get_vert_normals.cpp)
//   with the same bool selector, then bulk ChunkLoadClass::Read 0x6151A0
//   (matched chunkio.cpp) of count*12 bytes into the returned buffer.
// - VertexCount at +0x28 (meshgeometry.h shim + matched bodies), size
//   computed twice via lea+add+add (count*12) once for the push and once
//   for cmp eax,edx / sete al tail. No null guards, no EH, frameless ret8.
// - Callers in 0x18B790: chunk 0x03 (VERTEX_NORMALS) with false at 0x18B7F1
//   via push-0 trampoline to 0x18B93A, and chunk 0xC01 with true at 0x18B938.
//   Chunk IDs from target jump tables (byte table 0x18B9A4 + jump 0x18B974)
//   and explicit compares, matching BFME1 MeshModelReadChunks dispatch for
//   0x03/0xC01 plus BFME2-new 0x60/0x61/0xC00 variants handled elsewhere.
// Donor facts (BFME1 6583b3c1, clean, reference-first):
// - game/.../WW3D2/MeshGeometryReadVertexNormals.cpp: bool
//   read_vertex_normals(ChunkLoadClass&, bool alternate_format) with
//   get_vert_normals(bool) selector + per-vertex Read loop + SKIN
//   de-interleave into +0x48/+0x4C buffers (203B at 0x009274C0).
// - game/.../WW3D2/MeshGeometryGetVertexNormals.cpp: get_vert_normals(bool)
//   selecting +0x40/+0x44 (BFME1) vs target +0x38/+0x3C via matched 0x16AAE0.
// - game/.../WW3D2/MeshModelReadChunks.cpp: bool read_chunks dispatch for
//   VERTICES 0x02 / VERTEX_NORMALS 0x03 with false and 0xC00/0xC01 with true,
//   bool ABI, prelit/AABTree ignored (same as target 0x18B790).
// - ZH GeneralsMD meshgeometry/read path preserves the same bool loop shape
//   (semantic guide only, never port source).
// Inferences (separate from facts):
// - 0x16AF40 is MeshGeometry::read_vertex_normals-with-selector: same ABI
//   as proven read_vertices 0x16AE70 (bool), same getter family, same
//   count*12 bulk shape as matched Rva0016AF80/16AFD0 siblings, same
//   dispatch positions. Opaque Rva name rejected in favor of donor-attested
//   mangling once target dispatch + callee + ABI converge.
// - Target bulk (no loop, no SKIN) is a BFME2 simplification of the donor
//   loop+SKIN: substantial repair removing donor loop/SKIN to match retail
//   bulk, allowed as same-function semantics (normals bulk read) with target
//   bytes as truth. Existing header field types (VertexCount int +0x28,
//   Vector3 12B) used, not donor char pads.
// - No new pins: callees are matched rows (16AAE0, 6151A0), resolved
//   automatically. No MeshLoadContext touch, no shared-header edit.
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "chunkio.h"

class Vector3
{
public:
	float x, y, z;
	Vector3() {}
};

class MeshGeometryClass
{
protected:
	Vector3 *get_vert_normals(bool alternate_format);
	bool read_vertex_normals(ChunkLoadClass &cload, bool alternate_format);
private:
	char m_pad00[0x28];
	int m_count28;
	int Get_Vertex_Count() const { return m_count28; }
};

// ?read_vertex_normals@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@_N@Z
bool MeshGeometryClass::read_vertex_normals(ChunkLoadClass &cload, bool alternate_format)
{
	Vector3 *buf = get_vert_normals(alternate_format);
	bool matched = cload.Read(buf, Get_Vertex_Count() * sizeof(Vector3))
		== Get_Vertex_Count() * sizeof(Vector3);
	return matched;
}
