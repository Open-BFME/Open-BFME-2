// cl: /EHsc /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
/*
 * BFME2 DX8PolygonRendererClass::Render_Sorted.
 *
 * The retail body starts at RVA 0x00143770, returns at VA 0x00543885, and
 * occupies 280 bytes through the RET.  The four unsigned locals are written
 * in the compiler's right-to-left argument evaluation order.  Keeping the
 * range and minimum live across the triangle-count divide reproduces the
 * retail ECX/ESI/EBX allocation without ABI tricks.
 *
 * BFME2SortingRendererClass is the descriptive source view of the established
 * SortingRendererClass callee.  Its five arguments are DWORDs in BFME2: the
 * target callee at VA 0x0052FE00 reads all four as DWORDs, checks each against
 * 0xFFFF, and narrows internally.  The target's disabled-sorting path forwards
 * the same four DWORD arguments to VA 0x00520620.
 */
#include <string.h>

// DX8Wrapper::render_state (VA 0x00DEE5D8, dx8wrapper.cpp): Zero Hour's
// RenderStateStruct (bfmestages/dx8wrapper.h); index_base_offset, the 16-bit
// cache at 0x00DEE864, is its last field (+0x28C).
#include "RenderStateStruct.h"

class DX8Wrapper {
protected:
	static RenderStateStruct render_state;
	static unsigned render_state_changed;

public:
	static void Set_Index_Buffer_Index_Offset(unsigned offset)
	{
		if (render_state.index_base_offset == offset) return;
		render_state.index_base_offset = (unsigned short)offset;
		render_state_changed |= 1 << 17;
	}
};

#include "MeshGeometryClass.h"

// Descriptive event-scope view; ctor/dtor identities are independently pinned.
class BFME2ScopedRenderEvent {
	char Label[256];
	char Group[64];

public:
	BFME2ScopedRenderEvent(const char *,const char *,unsigned);
	~BFME2ScopedRenderEvent();
};

#include "../WWMath/SphereClass.h"

struct TargetCenter3 { float x, y, z; };
#include "BfmeSortingDispatchAt0012FE00.h"

#include "SortingRendererClass.h"

class DX8PolygonRendererClass {
	void *Vtable;
	void *ListNode;
	MeshGeometryClass *Model;
	void *Category;
	unsigned IndexOffset;
	unsigned VertexOffset;
	unsigned IndexCount;
	unsigned MinVertex;
	unsigned VertexRange;
	unsigned MinVertex2;
	unsigned VertexRange2;
	bool Strip;
	unsigned Pass;

public:
	void Render_Sorted(int base_vertex_offset,const SphereClass &bounding_sphere);
};

inline void DX8PolygonRendererClass::Render_Sorted(
	int base_vertex_offset,const SphereClass &bounding_sphere)
{
	char label[256];
	strcpy(label,"Rendering sorted mesh\tDX8Render\t");
	strcat(label,Model && Model->Get_Name() ? Model->Get_Name() : "(unnamed)");
	BFME2ScopedRenderEvent event(label,"MeshDX8Render",0);
	DX8Wrapper::Set_Index_Buffer_Index_Offset(base_vertex_offset);

	unsigned vertex_range=VertexRange;
	unsigned min_vertex=MinVertex;
	unsigned polygon_count=IndexCount/3;
	unsigned index_offset=IndexOffset;
	BfmeSortingDispatchAt0012FE00::
		Insert(
		reinterpret_cast<const TargetCenter3 &>(bounding_sphere),index_offset,polygon_count,min_vertex,vertex_range);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (DX8PolygonRendererClass::*_bfmeInlineAnchor_bfme2_polygon_render_sorted_0)(
	int base_vertex_offset,const SphereClass &bounding_sphere) = &DX8PolygonRendererClass::Render_Sorted;
