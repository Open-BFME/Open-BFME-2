// cl: /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep
//
// ?updatePoolSizes@Rva00914860Sizer@@QAEXHHPAH@Z, retail 0x0017F150, 86 bytes.
// PointGroupClass vertex-array sizing prologue, the out-of-line copy of the
// body the matched renderer at 0x0017F1B0 keeps inline (see
// PointGroupClassRender.cpp rva00914860). Evidence: the matched caller at
// 0x0017F3A0 casts its receiver to Rva00914860Sizer and calls this method;
// the three VectorClass globals are the target's own DIR32 operands
// (VertexLoc 0x00DF708C vtable 0x00BCEFAC VectorClass<Vector3>,
// VertexUV 0x00DF94C0, VertexDiffuse 0x00DFC4E0), and Length() reads the
// target's +8 member (0x00DF7094). /G7 is required: without it MSVC emits
// `dec eax` where retail has `sub eax,1`. The VectorClass<Vector3>::Resize
// callee is ICF-shared with the rowed VectorClass<TCBClass> body at 0x000F0BF1.

#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

class Rva00914860Sizer
{
public:
	void updatePoolSizes(int active_points, int total_points, int *vnum);
};

// Defined by the matched pointgr.cpp at the target's own addresses
// (VertexLoc 0x00DF708C, VertexUV 0x00DF94C0, VertexDiffuse 0x00DFC4E0).
extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector2> VertexUV;
extern VectorClass<Vector4> VertexDiffuse;

void Rva00914860Sizer::updatePoolSizes(int active_points, int total_points, int *vnum)
{
	int verts_per_point = *(int *)((char *)this + 0x2C) == 1 ? 4 : 3;
	int total_vnum = verts_per_point * total_points;
	*vnum = verts_per_point * active_points;
	if (VertexLoc.Length() < total_vnum) {
		int count = total_vnum * 2;
		VertexLoc.VectorClass<Vector3>::Resize(count, 0);
		VertexUV.VectorClass<Vector2>::Resize(count, 0);
		VertexDiffuse.VectorClass<Vector4>::Resize(count, 0);
	}
}
