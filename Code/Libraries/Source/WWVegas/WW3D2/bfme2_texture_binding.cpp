// cl: /O2 /G7 /EHsc /MD /DNDEBUG
// Descriptive recovered BFME2 texture-reference and cache names.
// Retail caller546F9A passes stage and owning reference; stage pointers at DEE5E0.
// 16 slots agree with the already recovered BFME2 Apply_Render_State layout.
// WORD refcounts at resource+4; cached release reaches A1ED10.
struct BFME2TextureResource { unsigned Vtable; unsigned short Refs; void Release_Ref(); };
struct BFME2TextureRef {
 BFME2TextureResource* Ptr;
 BFME2TextureRef(BFME2TextureResource* p):Ptr(p) { if(Ptr) ++Ptr->Refs; }
 BFME2TextureRef(const BFME2TextureRef& p):Ptr(p.Ptr) { if(Ptr) ++Ptr->Refs; }
 ~BFME2TextureRef() { if(Ptr) Ptr->Release_Ref(); }
};

extern BFME2TextureResource* BFME2CurrentTextures[16];
extern unsigned BFME2RenderStateChanged;
void BFME2Set_Texture(unsigned stage,const BFME2TextureRef& texture) {
 if(texture.Ptr==BFME2CurrentTextures[stage]) return;
 if(texture.Ptr) ++texture.Ptr->Refs;
 if(BFME2CurrentTextures[stage]) BFME2CurrentTextures[stage]->Release_Ref();
 BFME2CurrentTextures[stage]=texture.Ptr;
 BFME2RenderStateChanged|=0x40<<stage;
}
