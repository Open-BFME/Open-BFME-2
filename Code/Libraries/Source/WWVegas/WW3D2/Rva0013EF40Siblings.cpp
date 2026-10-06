// cl: /EHsc /MD /DNDEBUG
// Recovered from the ?Get_Texture@BFME2TextureCategory@@QAE?AUBFME2TextureRef@@H@Z
// recipe at 0x00143400 (35 bytes). Same operand-masked shape: form a smart
// reference to Textures[stage], bumping the resource's WORD refcount at +4 and
// returning through the hidden return pointer; RET8. Only the array base
// differs: retail's category has its texture pointers at +8 (two prefix dwords)
// where the template's sits at +0x0C (three). No relocations in either body, so
// the offset is the whole difference. Identity of the owning type is unknown;
// the name is address-derived while the shared BFME2 resource/ref spelling is
// kept, as in the template.
struct BFME2TextureResource { unsigned Vtable; unsigned short Refs; void Release_Ref(); };
struct BFME2TextureRef {
 BFME2TextureResource* Ptr;
 BFME2TextureRef(BFME2TextureResource* p):Ptr(p) { if(Ptr) ++Ptr->Refs; }
 BFME2TextureRef(const BFME2TextureRef& p):Ptr(p.Ptr) { if(Ptr) ++Ptr->Refs; }
 ~BFME2TextureRef() { if(Ptr) Ptr->Release_Ref(); }
};
class Rva0013EF40Category {
 unsigned Prefix[2]; BFME2TextureResource* Textures[2];
 public: BFME2TextureRef Get_Texture(int stage);
};
BFME2TextureRef Rva0013EF40Category::Get_Texture(int stage) { return BFME2TextureRef(Textures[stage]); }
