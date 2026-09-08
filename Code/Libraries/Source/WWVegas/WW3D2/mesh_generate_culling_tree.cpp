// cl: /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "rendobj.h"
#include "vector3i.h"
#include "sharebuf.h"
#include "wwmemlog.h"

typedef Vector3i16 TriIndex;

class AABTreeClass;

// BFME2's mesh layout places the culling inputs at +0x24..+0x30 and the
// resulting tree at +0x88.  Keep the unneeded prefix/gap opaque so this
// recovery states only offsets exercised by the body.
class MeshGeometryClass
{
public:
	typedef void (MeshGeometryClass::*GenerateCullingTreeFn)();
	static GenerateCullingTreeFn emit_generate_culling_tree()
	{
		return &MeshGeometryClass::Generate_Culling_Tree;
	}

protected:
	void Generate_Culling_Tree(void);

private:
	unsigned char m_prefix[0x24];
	int PolyCount;
	int VertexCount;
	ShareBufferClass<TriIndex> *Poly;
	ShareBufferClass<Vector3> *Vertex;
	unsigned char m_before_cull_tree[0x54];
	AABTreeClass *CullTree;
};

// aabtree.h normally reaches the vendored BFME1 MeshGeometryClass through
// aabtreebuilder.h; the local declaration above supplies the BFME2 offsets.
#define MESHGEOMETRY_H
// Retail uses the global scalar operator new at 0x2FDA0 for this object.  The
// shared AABTree header's pool glue would add a getClassMemoryPool call, so
// suppress that optional member operator in this layout-only declaration.
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "aabtree.h"

MeshGeometryClass::GenerateCullingTreeFn kGenerateCullingTree =
	MeshGeometryClass::emit_generate_culling_tree();

void MeshGeometryClass::Generate_Culling_Tree(void)
{
	WWMEMLOG(MEM_CULLINGDATA);
	{
		AABTreeBuilderClass builder;
		builder.Build_AABTree(PolyCount,Poly->Get_Array(),VertexCount,Vertex->Get_Array());
		CullTree = W3DNEW AABTreeClass(&builder);
		CullTree->Set_Mesh(this);
	}
}
