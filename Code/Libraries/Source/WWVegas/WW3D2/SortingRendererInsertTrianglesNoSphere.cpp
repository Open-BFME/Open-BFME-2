// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// SortingRendererClass::Insert_Triangles(start, count, minv, vert)
// retail 0x009037D0. Forwards a zeroed 12-byte sphere view plus four stack args.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
public:
	float X;
	float Y;
	float Z;
	SphereClass() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/sortingrenderer.h
#include "SortingRendererClass.h"

// The four-argument overload's own matched body at 0x0012FE00; retail's 0x009037D0
// forwards the zeroed sphere view to it by the rowed spelling.
struct TargetCenter3
{
public:
	float X;
	float Y;
	float Z;
	TargetCenter3() {}
};

#include "BfmeSortingDispatchAt0012FE00.h"

// ?Insert_Triangles@SortingRendererClass@@SAXGGGG@Z
void SortingRendererClass::Insert_Triangles(
	unsigned short start_index,
	unsigned short polygon_count,
	unsigned short min_vertex_index,
	unsigned short vertex_count)
{
	SphereClass sphere;
	sphere.X = 0.0f;
	sphere.Y = 0.0f;
	sphere.Z = 0.0f;
	BfmeSortingDispatchAt0012FE00::Insert(*(const TargetCenter3 *)&sphere,
		*(const unsigned int *)&start_index, *(const unsigned int *)&polygon_count,
		*(const unsigned int *)&min_vertex_index, *(const unsigned int *)&vertex_count);
}
