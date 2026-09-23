// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Donor: BFME1 WW3D2/meshgeometry.cpp and MeshGeometryClass_Load_W3D.cpp.
// Target Load_W3D slot returns bool (AL1 success); MeshClass caller149D36
// tests AL after the corresponding MeshModel virtual call. Full body643B
// ends at ret4 at16DA92. Header loaders16D810/18BA10 establish MeshName+10;
// chunk0x0C reader16B0E0 establishes UserText+14. Target Reset_Geometry
// takes a third skin flag; read_chunks retains its donor enum declaration.

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "sphere.h"
#include "multilist.h"
#include "w3derr.h"
#include "w3d_file.h"
#include "chunkio.h"
#include "wwdebug.h"
#include <string.h>

class AABTreeClass;

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual bool Load_W3D(ChunkLoadClass & cload);

	void Reset_Geometry(int polycount, int vertcount, bool bfme_header);
	void Set_Name(const char * newname);

	void Set_Flag(int flag, bool onoff) { if (onoff) { Flags |= flag; } else { Flags &= ~flag; } }
	int Get_Flag(int flag) { return Flags & flag; }
	int Get_Vertex_Count(void) { return VertexCount; }

protected:
	WW3DErrorType read_chunks(ChunkLoadClass & cload);
	uint16 * get_bone_links(bool create = true);
	void Generate_Culling_Tree(void);

	void * MeshName;
	void * UserText;
	int Flags;
	char SortLevel;
	uint32 W3dAttributes;
	int PolyCount;
	int VertexCount;
	void * Poly;
	void * Vertex;
	void * Slot34;
	void * Slot38;
	void * Slot3c;
	void * Slot40;
	void * Slot44;
	void * Slot48;
	void * Slot4c;
	void * Slot50;
	void * Slot54;
	void * Slot58;
	void * Slot5c;
	Vector3 BoundBoxMin;
	Vector3 BoundBoxMax;
	Vector3 BoundSphereCenter;
	float BoundSphereRadius;
	AABTreeClass * CullTree;
};

bool MeshGeometryClass::Load_W3D(ChunkLoadClass & cload)
{
	cload.Open_Chunk();
	if (cload.Cur_Chunk_ID() != W3D_CHUNK_MESH_HEADER3) {
		WWDEBUG_SAY(("Old format mesh mesh, no longer supported.\n"));
		goto Error;
	}

	W3dMeshHeader3Struct header;
	if (cload.Read(&header, sizeof(W3dMeshHeader3Struct)) != sizeof(W3dMeshHeader3Struct)) {
		goto Error;
	}
	cload.Close_Chunk();

	char * tmpname;
	int namelen;

	Reset_Geometry(header.NumTris, header.NumVertices,
		(header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK) == W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN);

	namelen = strlen(header.ContainerName);
	namelen += strlen(header.MeshName);
	namelen += 2;
	W3dAttributes = header.Attributes;
	SortLevel = header.SortLevel;
	tmpname = W3DNEWARRAY char[namelen];
	memset(tmpname, 0, namelen);

	if (strlen(header.ContainerName) > 0) {
		strcpy(tmpname, header.ContainerName);
		strcat(tmpname, ".");
	}
	strcat(tmpname, header.MeshName);

	Set_Name(tmpname);
	delete[] tmpname;
	tmpname = NULL;

	BoundBoxMin.Set(header.Min.X, header.Min.Y, header.Min.Z);
	BoundBoxMax.Set(header.Max.X, header.Max.Y, header.Max.Z);
	BoundSphereCenter.Set(header.SphCenter.X, header.SphCenter.Y, header.SphCenter.Z);
	BoundSphereRadius = header.SphRadius;

	if (header.Version >= W3D_MAKE_VERSION(4, 1)) {
		int geometry_type = header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK;
		switch (geometry_type) {
			case W3D_MESH_FLAG_GEOMETRY_TYPE_NORMAL:
				break;
			case W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ALIGNED:
				Set_Flag(0x200, true);
				break;
			case W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ORIENTED:
				Set_Flag(0x800, true);
				break;
			case W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN:
				Set_Flag(0x400, true);
				break;
		}
	}

	if (header.Attributes & W3D_MESH_FLAG_TWO_SIDED) {
		Set_Flag(0x100, true);
	}
	if (header.Attributes & W3D_MESH_FLAG_CAST_SHADOW) {
		Set_Flag(0x1000, true);
	}

	read_chunks(cload);

	if ((header.Version < W3D_MAKE_VERSION(3, 0)) && (Get_Flag(0x400))) {
		uint16 * links = get_bone_links();
		WWASSERT(links);
		for (int bi = 0; bi < Get_Vertex_Count(); bi++) {
			links[bi] += 1;
		}
	}

	if ((((W3dAttributes & W3D_MESH_FLAG_COLLISION_TYPE_MASK) >> W3D_MESH_FLAG_COLLISION_TYPE_SHIFT) != 0) &&
		(CullTree == NULL)) {
		Generate_Culling_Tree();
	}

	return true;

Error:
	return false;
}

