// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// MeshGeometryClass::read_chunks @0x0016D340 (255B through ret4 at 0x16D43E).
// Target facts (retail disassembly): bool thiscall, frameless, saves
// ebx/esi/edi; while (Open_Chunk 0x614F50) { bl=1; id=Cur_Chunk_ID 0x615020;
// id-=2; ja default; indexed jump table at 0x16D444 + byte map at 0x16D464 }.
// Arms: 0x02 read_vertices(cload,false) 0x16AE70; 0x03/0x04 bulk normals
// (get_vert_normals(false) 0x16AAE0 + Read 0x6151A0 count*12, sete);
// 0x0C read_user_text 0x16B0E0; 0x0E read_vertex_influences 0x16B1A0;
// 0x20 read_triangles 0x16B020; 0x22 bulk shade indices
// (get_shade_indices(true) 0x16A010 + Read count*4, sete);
// 0x90 read_aabtree 0x1693A0 with its return ignored (bl stays 1).
// Close_Chunk 0x614FC0; cmp bl,1 / jne returns bl; else loops; true at end.
// Donor facts (ZH GeneralsMD meshgeometry.cpp read_chunks): same 7-arm
// switch with the same chunk IDs; ZH returns WW3DErrorType and calls the
// separate read_vertex_normals / read_vertex_shade_indices helpers, while
// BFME2 (like its matched 50B read_vertex_normals 0x16AF40 wrapper) reads
// both bulks inline, and BFME2 returns bool.
// SURRENDER_NORMALS=0x04 is from w3d_obsolete.h (BFME1 tree); the main
// w3d_file.h only names the others.
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "vector3.h"
#include "w3d_file.h"
#include "w3d_obsolete.h"
#include "sharebuf.h"
#include "chunkio.h"

class MeshGeometryClass
{
protected:
	bool read_chunks(ChunkLoadClass &cload);
	bool read_vertices(ChunkLoadClass &cload, bool use_secondary);
	Vector3 *get_vert_normals(bool alternate_format);
	bool read_triangles(ChunkLoadClass &cload);
	bool read_user_text(ChunkLoadClass &cload);
	bool read_vertex_influences(ChunkLoadClass &cload);
	uint32 *get_shade_indices(bool create);
	bool read_aabtree(ChunkLoadClass &cload);
	int Get_Vertex_Count() const { return VertexCount; }

private:
	char m_prefix[0x28];
	int VertexCount;			// retail VertexCount is at +0x28
};

// ?read_chunks@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_chunks(ChunkLoadClass &cload)
{
	while (cload.Open_Chunk()) {
		bool error = true;

		switch (cload.Cur_Chunk_ID()) {
		case W3D_CHUNK_VERTICES:
			error = read_vertices(cload, false);
			break;

		case W3D_CHUNK_VERTEX_NORMALS:
		case W3D_CHUNK_SURRENDER_NORMALS:
		{
			Vector3 *normals = get_vert_normals(false);
			error = cload.Read(normals, Get_Vertex_Count() * sizeof(Vector3))
				== Get_Vertex_Count() * sizeof(Vector3);
			break;
		}

		case W3D_CHUNK_TRIANGLES:
			error = read_triangles(cload);
			break;

		case W3D_CHUNK_MESH_USER_TEXT:
			error = read_user_text(cload);
			break;

		case W3D_CHUNK_VERTEX_INFLUENCES:
			error = read_vertex_influences(cload);
			break;

		case W3D_CHUNK_VERTEX_SHADE_INDICES:
		{
			uint32 *indices = get_shade_indices(true);
			error = cload.Read(indices, Get_Vertex_Count() * sizeof(uint32))
				== Get_Vertex_Count() * sizeof(uint32);
			break;
		}

		case W3D_CHUNK_AABTREE:
			read_aabtree(cload);
			break;

		default:
			break;
		}

		cload.Close_Chunk();

		if (error != true) {
			return error;
		}
	}

	return true;
}
