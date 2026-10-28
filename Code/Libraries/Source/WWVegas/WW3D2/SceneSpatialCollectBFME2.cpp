// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /O2 /G7 /arch:SSE
// Target [142330,142407) maps a floating rectangle to spatial cells and
// calls the recursive tree query at142170. Its node stride is 28 bytes.
// Original function names are unknown; no donor name is asserted.
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
// bfmeHeadersForSize: the headers' out-of-line inline copies that retail keeps are
// the size-optimised bodies (decalsys.cpp pattern); the rows below keep the unit's flags.
// PlaneClass::Compute_Intersection is inlined at its one use here, yet this /O2 unit still emits
// a 166-byte out-of-line copy that retail's /O1 owner at 0x00069168 (165 B, PlaneO1Inlines.cpp)
// disproves, and no pragma state reproduces /Os for it. A TU-local name keeps that copy from
// displacing retail's.
#define Compute_Intersection Compute_Intersection_O2
#pragma optimize("s", on)
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
#include "camera.h"
#include "plane.h"
#pragma optimize("", on)
struct Gen_00943CF0_Node { Gen_00943CF0_Node *m_next; void *m_value; };
struct SceneCollectCell { unsigned count; MultiListClass<RenderObjClass> objects; };
typedef char SceneCollectCellSize[(sizeof(SceneCollectCell)==28)?1:-1];
class Gen_009431F0 { public: int map_x(float); int map_y(float); };
struct SceneCollectPair { float X,Y; };
struct SceneCollectRect {
 SceneCollectPair min,max;
 __forceinline void Add_Point(const Vector2 &point)
 {
  if (point.X < min.X) min.X = point.X;
  else if (point.X > max.X) max.X = point.X;
  if (point.Y < min.Y) min.Y = point.Y;
  else if (point.Y > max.Y) max.Y = point.Y;
 }
};
class BfmeSceneVector {
public:
 void rva00142170(Gen_00943CF0_Node **out,SceneCollectCell *node,unsigned childStride,int xmin,int ymin,int xmax,int ymax,int ox,int oy,int extent);
 void rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin);
 void rva00142410(Gen_00943CF0_Node **out,CameraClass *camera,const float *margin);
 float bounds[6]; SceneCollectCell *vector; int vector_max; float scale; unsigned level_mask;
};
typedef char SceneCollectIndexMatches[(sizeof(BfmeSceneVector)==sizeof(BFME2SceneSpatialIndex))?1:-1];
typedef char SceneCollectCellMatches[(sizeof(SceneCollectCell)==sizeof(BFME2SceneSpatialNode))?1:-1];

// The 8-byte list-node pool (defined with its grow 0x0006EFC8 and pop 0x00141800
// in Rva0006EFC8Grow.cpp); rva00142170 inlines the pop.
class Rva0006EFC8
{
public:
	bool rva0006EFC8(int arena, int size);

	int m_00;
	void *m_04;
	void *m_head;
	void *(__cdecl *m_alloc)(int size, int arg);
	void (__cdecl *m_free)(void *ptr, int arg);
	int m_14;
};

extern Rva0006EFC8 g_BfmeSceneNodePool;

// Pops an 8-byte node, growing the pool until it has one; the operation of 0x00141800, inlined here.
inline void *bfmeSceneNodePoolPop()
{
	void *node;
retry:
	if (g_BfmeSceneNodePool.m_head) goto found;
	{
		int size = g_BfmeSceneNodePool.m_00 * 8 + 4;
		if (g_BfmeSceneNodePool.rva0006EFC8(0, size))
			goto retry;
	}
	return 0;
found:
	node = g_BfmeSceneNodePool.m_head;
	g_BfmeSceneNodePool.m_head = *(void **)node;
	return node;
}

// Layout view of a cell list's sentinel (GenericMultiListClass::Head is protected).
// The emptiness test reads it directly: GenericMultiListClass::Is_Empty() compiles
// to the same compare, but its inlined call leaves one more coalesced copy on
// c2's globreg free list and swaps the xmin/ymin reloads after the first
// quadrant call.
struct SceneCollectListView
{
	void *vtable;
	MultiListNodeClass Head;
};

// rva00142170, retail 0x00142170 (443 bytes, RET40): recursive 28-byte-stride
// quadrant-tree rectangle query. Drains each visited cell's object list into
// the pooled output list, then recurses into the overlapping quadrants; the
// last quadrant is a tail call. Shape of BFME 1's Rva009441D0Recurse (early
// return on an empty subtree, in-place halving, repeated midpoint sums). The
// sibling rva00142330 establishes the signature. Original names are unknown.
void BfmeSceneVector::rva00142170(Gen_00943CF0_Node **out, SceneCollectCell *node, unsigned childStride, int xmin, int ymin, int xmax, int ymax, int ox, int oy, int extent)
{
	if (((SceneCollectListView *)&node->objects)->Head.Next != &((SceneCollectListView *)&node->objects)->Head) {
		MultiListIterator<RenderObjClass> it(&node->objects);
		for (; !it.Is_Done(); it.Next()) {
			RenderObjClass *object = it.Peek_Obj();
			Gen_00943CF0_Node *item = (Gen_00943CF0_Node *)bfmeSceneNodePoolPop();
			void **valuePtr = (void **)((char *)item + 4);
			if (valuePtr) *valuePtr = object;
			item->m_next = 0;
			item->m_next = *out;
			*out = item;
		}
	}
	if (node->count == 0)
		return;
	extent /= 2;
	++node;
	if (ymin < oy + extent) {
		if (xmin < ox + extent) rva00142170(out, node, childStride >> 2, xmin, ymin, xmax, ymax, ox, oy, extent);
		if (xmax >= ox + extent) rva00142170(out, node + childStride, childStride >> 2, xmin, ymin, xmax, ymax, ox + extent, oy, extent);
	}
	if (ymax >= oy + extent) {
		if (xmin < ox + extent) rva00142170(out, node + 2 * childStride, childStride >> 2, xmin, ymin, xmax, ymax, ox, oy + extent, extent);
		if (xmax >= ox + extent) rva00142170(out, node + 3 * childStride, childStride >> 2, xmin, ymin, xmax, ymax, ox + extent, oy + extent, extent);
	}
}

void BfmeSceneVector::rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin)
{
 int minX=((Gen_009431F0*)this)->map_x(rect.min.X-(margin ? margin[0] : 0.0f));
 int maxX=((Gen_009431F0*)this)->map_x(rect.max.X+(margin ? margin[0] : 0.0f));
 int minY=((Gen_009431F0*)this)->map_y(rect.min.Y-(margin ? margin[1] : 0.0f));
 int maxY=((Gen_009431F0*)this)->map_y(rect.max.Y+(margin ? margin[1] : 0.0f));
 rva00142170(out,vector,(unsigned)vector_max>>2,minX,minY,maxX,maxY,0,0,level_mask);
}


// rva00142410, retail 0x00142410 (662 bytes, RET12; Ghidra's 655 truncates the
// epilogue): the camera-frustum collect. Frustum corners 0..3 (camera +0x190)
// seed an x/y rectangle; each of the four corner rays (i to i+4) is then cut
// by the z=0 plane (z=800 when the camera's Z-axis Z component, transform +0x40,
// is negative), the cut point (clamped to t=1) widens the rectangle, and the
// sibling rva00142330 maps it to cells. Shape from WWMath: PlaneClass default
// plane, Compute_Intersection and Vector3::Lerp; the unrolled corner updates are
// the rectangle's Add_Point. Original function names are unknown.
void BfmeSceneVector::rva00142410(Gen_00943CF0_Node **out, CameraClass *camera, const float *margin)
{
	const Vector3 *corners = camera->Get_Frustum_Corners();
	SceneCollectRect rect;
	rect.max.X = corners[0].X;
	rect.max.Y = corners[0].Y;
	rect.min = rect.max;
	if (corners[1].X < rect.min.X) rect.min.X = corners[1].X;
	else if (corners[1].X > rect.max.X) rect.max.X = corners[1].X;
	if (corners[1].Y < rect.min.Y) rect.min.Y = corners[1].Y;
	else if (corners[1].Y > rect.max.Y) rect.max.Y = corners[1].Y;
	if (corners[2].X < rect.min.X) rect.min.X = corners[2].X;
	else if (corners[2].X > rect.max.X) rect.max.X = corners[2].X;
	if (corners[2].Y < rect.min.Y) rect.min.Y = corners[2].Y;
	else if (corners[2].Y > rect.max.Y) rect.max.Y = corners[2].Y;
	if (corners[3].X < rect.min.X) rect.min.X = corners[3].X;
	else if (corners[3].X > rect.max.X) rect.max.X = corners[3].X;
	if (corners[3].Y < rect.min.Y) rect.min.Y = corners[3].Y;
	else if (corners[3].Y > rect.max.Y) rect.max.Y = corners[3].Y;
	PlaneClass plane;
	if (camera->Get_Transform()[2][2] < 0.0f) plane.D = 800.0f;
	for (int i = 0; i < 4; ++i) {
		float intersectionFraction;
		if (!plane.Compute_Intersection(corners[i], corners[i + 4], &intersectionFraction)) intersectionFraction = 1.0f;
		Vector3 point;
		Vector3::Lerp(corners[i], corners[i + 4], intersectionFraction, &point);
		rect.Add_Point(Vector2(point.X, point.Y));
	}
	rva00142330(out, rect, margin);
}
