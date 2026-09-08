// cl: /O2 /G7 /EHsc /MD /DNDEBUG
// Reconstructed from retail RVA 143400 and caller 146F50.
// Descriptive BFME2 type names: the original smart-reference spelling is unknown.
// Category texture pointers begin at +0C; resources use a WORD refcount at +4.
// Returning the owning reference reproduces all 35 bytes including RET8.
// Release is observed in the caller at A1ED10; this getter contains no relocations.
struct BFME2TextureResource { unsigned Vtable; unsigned short Refs; void Release_Ref(); };
struct BFME2TextureRef {
 BFME2TextureResource* Ptr;
 BFME2TextureRef(BFME2TextureResource* p):Ptr(p) { if(Ptr) ++Ptr->Refs; }
 BFME2TextureRef(const BFME2TextureRef& p):Ptr(p.Ptr) { if(Ptr) ++Ptr->Refs; }
 ~BFME2TextureRef() { if(Ptr) Ptr->Release_Ref(); }
};
class BFME2TextureCategory {
 unsigned Prefix[3]; BFME2TextureResource* Textures[2];
 public: BFME2TextureRef Get_Texture(int stage);
};
BFME2TextureRef BFME2TextureCategory::Get_Texture(int stage) { return BFME2TextureRef(Textures[stage]); }
