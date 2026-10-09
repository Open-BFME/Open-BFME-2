// cl: /O2 /Ob2 /G7 /MD /DNDEBUG
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
class RenderObjClass { public:
virtual void Delete_This();
virtual ~RenderObjClass();
virtual RenderObjClass *Clone() const;
virtual int Class_ID() const;
virtual void slot4();
virtual MeshClass *Mesh_View();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual int Sub_Object_Count() const;
virtual void slot29();
virtual RenderObjClass *Get_Sub_Object(int) const;
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual MaterialInfoClass *Get_Material_Info();
void Release_Ref() { if(--m_refCount==0) Delete_This(); }
protected: int m_refCount; };
class MeshClass : public RenderObjClass { public: void Make_Unique(bool); };
class MaterialInfoClass { public: virtual void Delete_This();
 void Release_Ref() { if(--m_refCount==0) Delete_This(); }
 bool Has_Time_Variant_Texture_Mappers(); void Reset_Texture_Mappers();
private: int m_refCount; };
class Rva0010E4D4 { public: void rva0010E4D4(); };
void Reset_All_Texture_Mappers(RenderObjClass *robj, bool make_unique)
{
 if(robj->Class_ID()==0) {
  MeshClass *mesh=robj->Mesh_View();
  MaterialInfoClass *minfo=robj->Get_Material_Info();
  if(minfo && minfo->Has_Time_Variant_Texture_Mappers()) {
   if(make_unique) {
    mesh->Make_Unique(false);
    reinterpret_cast<Rva0010E4D4*>(minfo)->rva0010E4D4();
   }
   minfo->Reset_Texture_Mappers();
   minfo->Release_Ref();
  }
 } else {
  int num_obj=robj->Sub_Object_Count();
  for(int i=0; i<num_obj; ++i) {
   RenderObjClass *sub_obj=robj->Get_Sub_Object(i);
   if(sub_obj) {
    Reset_All_Texture_Mappers(sub_obj,make_unique);
    sub_obj->Release_Ref();
   }
  }
 }
}
