// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// MeshGeometryClass vertex shade-index chunk reader at 0x0016B3C0 (47B).
// Evidence: calls the rowed Rowed get_shade_indices(bool) at 0x0016A010 with
// create=true, then reads VertexCount*4 bytes straight into the array and
// returns whether Read() returned the full size.  The caller is the
// MeshModelClass read_chunks dispatch at 0x0018B85A.  BFME2 collapsed the
// reference per-index read loop into one bulk Read, so the donor name
// read_vertex_shade_indices is retained but the body follows retail.

#include "chunkio.h"
#include "sharebuf.h"

// Keep the reference RefCountClass inline definitions and the canonical list base.
#define BFME2_WWLIB_REFCOUNTDATA_H
#include "../WWLib/MultiListObjectClass.h"
#define MULTILIST_H
#include "MeshGeometryClass.h"

// ?read_vertex_shade_indices@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_vertex_shade_indices(ChunkLoadClass & cload)
{
	uint32 *indices = get_shade_indices(true);
	bool matched = cload.Read(indices, Get_Vertex_Count() * 4) == Get_Vertex_Count() * 4;
	return matched;
}
