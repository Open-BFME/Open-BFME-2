// cl: /EHsc /MD /arch:SSE /G7
class DX8Wrapper {
 protected:
 static unsigned short BFME2IndexBase;
 static unsigned render_state_changed;
 public:
 static void Set_Index_Buffer_Index_Offset(unsigned offset) {
  if (BFME2IndexBase == offset) return;
  BFME2IndexBase = (unsigned short)offset;
  render_state_changed |= 1 << 17;
 }
 static void Draw_Strip(unsigned,unsigned,unsigned,unsigned);
 static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned);
};
#include <string.h>
// Retail143630..143761:305-byte RET4 body, including render-event lifetime.
// Sparse renderer fields follow the donor polygon batch layout. BFME2 draw
// arguments remain32-bit; the BFME1 ushort declarations truncate them.
// BFME2IndexBase is a descriptive alias for the16-bit cache atDEE864;
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
void DX8PolygonRendererClass::Render(int base_vertex_offset) {
 char label[256];
 strcpy(label,"Rendering mesh\tDX8Render\t");
 strcat(label,Model && Model->Get_Name() ? Model->Get_Name() : "(unnamed)");
 BFME2ScopedRenderEvent event(label,"MeshDX8Render",0);
 DX8Wrapper::Set_Index_Buffer_Index_Offset(base_vertex_offset);
 if (Strip) DX8Wrapper::Draw_Strip(IndexOffset,IndexCount-2,MinVertex,VertexRange);
 else DX8Wrapper::Draw_Triangles(IndexOffset,IndexCount/3,MinVertex,VertexRange);
}
