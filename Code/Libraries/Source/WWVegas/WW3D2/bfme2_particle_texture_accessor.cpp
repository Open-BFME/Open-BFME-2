// cl: /O2 /G7 /EHsc /MD /DNDEBUG
// Descriptive particle-renderer texture accessor shared by point/line callers.
// Retail getter1790E0..1790FE is30B: complete RET4 starts5790FB.
// Texture slot+24; one-pointer owning handle increments WORD refcount+4.
// Contracts independently traced in particle copy constructor1AD1B0 and
// setter1790A0; this view does not assert original C++ class spelling.
struct BFME2TextureResource { unsigned Vtable; unsigned short Refs; void Release_Ref(); };
struct BFME2TextureRef {
 BFME2TextureResource* Ptr;
 BFME2TextureRef(BFME2TextureResource* p):Ptr(p) { if(Ptr) ++Ptr->Refs; }
 BFME2TextureRef(const BFME2TextureRef& p):Ptr(p.Ptr) { if(Ptr) ++Ptr->Refs; }
 ~BFME2TextureRef() { if(Ptr) Ptr->Release_Ref(); }
};
class BFME2ParticleTextureAccessor {
 unsigned Prefix[9]; BFME2TextureResource* Texture;
 public: BFME2TextureRef Get_Texture() const;
 void Set_Texture(const BFME2TextureRef& value);
};
BFME2TextureRef BFME2ParticleTextureAccessor::Get_Texture() const { return BFME2TextureRef(Texture); }
