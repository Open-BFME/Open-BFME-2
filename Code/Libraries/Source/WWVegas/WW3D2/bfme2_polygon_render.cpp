// cl: /EHsc /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// DX8Wrapper::render_state (VA 0x00DEE5D8, dx8wrapper.cpp): Zero Hour's
// RenderStateStruct (bfmestages/dx8wrapper.h); index_base_offset, the 16-bit
// cache at 0x00DEE864, is its last field (+0x28C).
#include "RenderStateStruct.h"
#include "DX8WrapperClass.h"
inline void DX8Wrapper::Set_Index_Buffer_Index_Offset(unsigned offset) {
 if (render_state.index_base_offset == offset) return;
 render_state.index_base_offset = (unsigned short)offset;
 render_state_changed |= 1 << 17;
}
#include <string.h>
// Retail143630..143761:305-byte RET4 body, including render-event lifetime.
// Sparse renderer fields follow the donor polygon batch layout. BFME2 draw
// arguments remain32-bit; the BFME1 ushort declarations truncate them.
// The 16-bit index base cache at DEE864 is render_state.index_base_offset;
// the scope and its two buffers are independently decoded, not SDK spelling.
#include "MeshGeometryClass.h"
// Descriptive role; original profiler class spelling has not been recovered.
class BFME2ScopedRenderEvent {
 char Label[256]; char Group[64];
 public: BFME2ScopedRenderEvent(const char*,const char*,unsigned); ~BFME2ScopedRenderEvent();
};
#include "dx8polygonrendererClass.h"
#include "MeshModelClass.h"
inline void DX8PolygonRendererClass::Render(int base_vertex_offset) {
 char label[256];
 strcpy(label,"Rendering mesh\tDX8Render\t");
 strcat(label,mmc && mmc->Get_Name() ? mmc->Get_Name() : "(unnamed)");
 BFME2ScopedRenderEvent event(label,"MeshDX8Render",0);
 DX8Wrapper::Set_Index_Buffer_Index_Offset(base_vertex_offset);
 if (strip) DX8Wrapper::Draw_Strip(index_offset,index_count-2,min_vertex_index,vertex_index_range);
 else DX8Wrapper::Draw_Triangles(index_offset,index_count/3,min_vertex_index,vertex_index_range);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (DX8PolygonRendererClass::*_bfmeInlineAnchor_bfme2_polygon_render_0)(int base_vertex_offset) = &DX8PolygonRendererClass::Render;
