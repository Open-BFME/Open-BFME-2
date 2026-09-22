// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Include /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME1 MeshGeometryLoading.cpp culling-tree reader, adapted to BFME2.
// Target read_chunks dispatches chunk 0x90 via call 0x16D411 to this body.
// Target CullTree is at +0x88 and scalar new allocates 0x1C bytes.
// Full body: RVA 0x1693A0, 150B through ret 4 at 0x169433..0x169435.
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "vector3.h"
#include "sphere.h"
#include "multilist.h"
#include "chunkio.h"
#include "sharebuf.h"
#include "vector4.h"
#include "vector3i.h"
#include "w3d_file.h"

typedef Vector3i16 TriIndex;

class MeshGeometryClass;

class AABTreeClass : public W3DMPO, public RefCountClass
{
public:
    AABTreeClass(void);
    void Load_W3D(ChunkLoadClass &cload);
    void Set_Mesh(MeshGeometryClass *mesh);
private:
    char _storage[0x14]; // target operand proves sizeof AABTreeClass is 0x1c
};

class MeshGeometryClass
{
protected:
    bool read_aabtree(ChunkLoadClass &cload);

    char BeforeCullTree[0x88];
    AABTreeClass *CullTree;
};

// ?read_aabtree@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_aabtree(ChunkLoadClass &cload)
{
    REF_PTR_RELEASE(CullTree);
    CullTree = new AABTreeClass;
    CullTree->Load_W3D(cload);
    CullTree->Set_Mesh(this);
    return true;
}
