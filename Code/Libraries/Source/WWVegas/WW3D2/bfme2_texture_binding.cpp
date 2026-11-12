// cl: /EHsc /MD /DNDEBUG
// Descriptive recovered BFME2 texture-reference and cache names.
// Retail caller546F9A passes stage and owning reference; stage pointers at DEE5E0.
// 16 slots agree with the already recovered BFME2 Apply_Render_State layout.
// WORD refcounts at resource+4; cached release reaches A1ED10.
// The screen-filter, Line3D and BfmeConv1137 callers spell this body as the
// BFME 1 donor's BoxSetTexture(unsigned, TextureBaseClass *&), pinned to this
// address: same cdecl stage plus by-reference handle. Bind that spelling here.
#pragma comment(linker, "/alternatename:?BoxSetTexture@@YAXIAAPAVTextureBaseClass@@@Z=?BFME2Set_Texture@@YAXIABUBFME2TextureRef@@@Z")
#include "../../../../GameEngine/Include/Common/BFME2TextureResource.h"
struct BFME2TextureRef {
 BFME2TextureResource* Ptr;
 BFME2TextureRef(BFME2TextureResource* p):Ptr(p) { if(Ptr) ++Ptr->Refs; }
 BFME2TextureRef(const BFME2TextureRef& p):Ptr(p.Ptr) { if(Ptr) ++Ptr->Refs; }
 ~BFME2TextureRef() { if(Ptr) Ptr->Release_Ref(); }
};

#include "RenderStateStruct.h"
struct BFME2TextureRef;
void BFME2Set_Texture(unsigned stage,const BFME2TextureRef& texture);
// The stage pointers at VA 0x00DEE5E0 are render_state's, read by Apply_Render_State_Changes, and the
// dirty mask at 0x00DEC4F4 is render_state_changed: both are DX8Wrapper's protected statics, defined
// in dx8wrapper.cpp. This view lets the setter reach them.
class DX8Wrapper {
 friend void BFME2Set_Texture(unsigned stage,const BFME2TextureRef& texture);
protected:
 static unsigned render_state_changed;
 static RenderStateStruct render_state;
};
void BFME2Set_Texture(unsigned stage,const BFME2TextureRef& texture) {
 BFME2TextureResource *&current=reinterpret_cast<BFME2TextureResource *&>(DX8Wrapper::render_state.Textures[stage]);
 if(texture.Ptr==current) return;
 if(texture.Ptr) ++texture.Ptr->Refs;
 if(current) current->Release_Ref();
 current=texture.Ptr;
 DX8Wrapper::render_state_changed|=0x40<<stage;
}
