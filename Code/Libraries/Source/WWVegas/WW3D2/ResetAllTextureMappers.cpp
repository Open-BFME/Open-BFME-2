// cl: /O2 /Ob2 /G7 /MD /DNDEBUG /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Direct Zero Hour mapper.cpp Reset_All_Texture_Mappers transfer (BFME 1
// reference 874e38488 inputs/reference/.../GeneralsMD/.../WW3D2/mapper.cpp).
// Retail 0x00186CF0..0x00186D95 proves this same recursive mapper reset:
// mesh Class_ID==0; MaterialInfo variant-test184060, reset184010; Make_Unique
// 149C10(false) and the already-rowed vertex-material uniqueness loop10E4D4.
// BFME 2 adaptations independently read from target: virtual mesh view at
// +0x14, material-info getter at +0x154, child count +0x70, child getter +0x78.
// The intervening virtual slots below are opaque declarations only. Both
// returned object kinds carry the counted reference at +4 and deletion slot0.
// The reference source releases material info only in its time-variant arm;
// retain that observed behavior exactly rather than adding a cleanup path.
class MeshClass; class MaterialInfoClass;
#include "rendobj.h"
class MeshClass : public RenderObjClass { public: void Make_Unique(bool); };
class MaterialInfoClass { public: virtual void Delete_This();
 void Release_Ref() { if(--m_refCount==0) Delete_This(); }
 // LINK: same reason as above, for MaterialInfoClass::Release_Ref.
 void bfme_release() { if(--m_refCount==0) Delete_This(); }
 bool Has_Time_Variant_Texture_Mappers(); void Reset_Texture_Mappers();
private: int m_refCount; };
class Rva0010E4D4 { public: void rva0010E4D4(); };
void Reset_All_Texture_Mappers(RenderObjClass *robj, bool make_unique)
{
 if(robj->Class_ID()==0) {
  MeshClass *mesh=reinterpret_cast<MeshClass *>(robj->_bfme_ro_v3());
  MaterialInfoClass *minfo=robj->Get_Material_Info();
  if(minfo && minfo->Has_Time_Variant_Texture_Mappers()) {
   if(make_unique) {
    mesh->Make_Unique(false);
    reinterpret_cast<Rva0010E4D4*>(minfo)->rva0010E4D4();
   }
   minfo->Reset_Texture_Mappers();
   minfo->bfme_release();
  }
 } else {
  int num_obj=robj->Get_Num_Sub_Objects();
  for(int i=0; i<num_obj; ++i) {
   RenderObjClass *sub_obj=robj->Get_Sub_Object(i);
   if(sub_obj) {
    Reset_All_Texture_Mappers(sub_obj,make_unique);
    sub_obj->Release_Ref();
   }
  }
 }
}
