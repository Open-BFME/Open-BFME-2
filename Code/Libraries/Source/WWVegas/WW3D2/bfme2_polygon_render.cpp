// cl: /EHsc /MD
// DX8Wrapper::render_state (VA 0x00DEE5D8, dx8wrapper.cpp): Zero Hour's
// RenderStateStruct (bfmestages/dx8wrapper.h); index_base_offset, the 16-bit
// cache at 0x00DEE864, is its last field (+0x28C).
struct RenderStateStruct { unsigned char m_pad00[0x28C]; unsigned short index_base_offset; };
class DX8Wrapper {
 protected:
 static RenderStateStruct render_state;
 static unsigned render_state_changed;
 public:
 static void Set_Index_Buffer_Index_Offset(unsigned offset) {
  if (render_state.index_base_offset == offset) return;
  render_state.index_base_offset = (unsigned short)offset;
  render_state_changed |= 1 << 17;
 }
 static void Draw_Strip(unsigned,unsigned,unsigned,unsigned);
 static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned);
};
#include <string.h>
// Retail143630..143761:305-byte RET4 body, including render-event lifetime.
// Sparse renderer fields follow the donor polygon batch layout. BFME2 draw
// arguments remain32-bit; the BFME1 ushort declarations truncate them.
// The 16-bit index base cache at DEE864 is render_state.index_base_offset;
// the scope and its two buffers are independently decoded, not SDK spelling.
class MeshGeometryClass { public: const char *Get_Name() const; };
// Descriptive role; original profiler class spelling has not been recovered.
class BFME2ScopedRenderEvent {
 char Label[256]; char Group[64];
 public: BFME2ScopedRenderEvent(const char*,const char*,unsigned); ~BFME2ScopedRenderEvent();
};
class DX8PolygonRendererClass {
 void *Vtable; void *ListNode; MeshGeometryClass *Model; void *Category;
 unsigned IndexOffset,VertexOffset,IndexCount,MinVertex,VertexRange,MinVertex2,VertexRange2;
 bool Strip; unsigned Pass;
 public: void Render(int base_vertex_offset);
};
inline void DX8PolygonRendererClass::Render(int base_vertex_offset) {
 char label[256];
 strcpy(label,"Rendering mesh\tDX8Render\t");
 strcat(label,Model && Model->Get_Name() ? Model->Get_Name() : "(unnamed)");
 BFME2ScopedRenderEvent event(label,"MeshDX8Render",0);
 DX8Wrapper::Set_Index_Buffer_Index_Offset(base_vertex_offset);
 if (Strip) DX8Wrapper::Draw_Strip(IndexOffset,IndexCount-2,MinVertex,VertexRange);
 else DX8Wrapper::Draw_Triangles(IndexOffset,IndexCount/3,MinVertex,VertexRange);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (DX8PolygonRendererClass::*_bfmeInlineAnchor_bfme2_polygon_render_0)(int base_vertex_offset) = &DX8PolygonRendererClass::Render;
