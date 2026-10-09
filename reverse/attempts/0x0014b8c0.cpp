// ?Recolor_Prototype@MeshClass@@QAEXABVRva0013101E@@@Z
// partial score=0.85 date=2026-10-09
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// WB9CC180 identifies MeshClass::Recolor_Prototype. Native14B8C0..14BA3D.
// MeshClass table7D35A8 slot85=Get_Material_Info149980 and slot126=
// RecolorHouseColor14C470. BFME1 W3DAssetManager recolour-material traversal
// is the semantic guide; target selects HOUSECOLOR and reads options+4.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include "vector3.h"
class Rva0013101E{public:unsigned flags,color;};
class VertexMaterialClass{public:void Make_Unique();void Set_Ambient(const Vector3&);void Set_Diffuse(const Vector3&);__forceinline void Set_Ambient(float r,float g,float b){Set_Ambient(Vector3(r,g,b));}__forceinline void Set_Diffuse(float r,float g,float b){Set_Diffuse(Vector3(r,g,b));}};
class MeshModelClass{public:virtual void Delete_This();int refs;void Add_Ref(){++refs;}void Release_Ref(){--refs;if(refs==0)Delete_This();}};
class MaterialInfoClass{public:virtual void Delete_This();int refs;char gap08[4];VertexMaterialClass **materials;char gap10[8];int count;VertexMaterialClass *Peek_Vertex_Material(int i){return i<count?materials[i]:0;}void Release_Ref(){--refs;if(refs==0)Delete_This();}};
class MeshClass{public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual const char *Get_Name();
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
virtual void slot28();
virtual void slot29();
virtual void slot30();
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
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual void slot96();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual void slot111();
virtual void slot112();
virtual void slot113();
virtual void slot114();
virtual void slot115();
virtual void slot116();
virtual void slot117();
virtual void slot118();
virtual void slot119();
virtual void slot120();
virtual void slot121();
virtual void slot122();
virtual void slot123();
virtual void slot124();
virtual void slot125();
virtual void RecolorHouseColor(const Rva0013101E&,const char *);
char gap04[0xC0];MeshModelClass *model;
MeshModelClass *Get_Model()const{if(model)model->Add_Ref();return model;}
void Recolor_Prototype(const Rva0013101E&);
};
void MeshClass::Recolor_Prototype(const Rva0013101E &options)
{
 MeshModelClass *mesh=Get_Model();MaterialInfoClass *materials=Get_Material_Info();
 const char *name=Get_Name();if(!name)return;
 const char *part=strchr(name,'.');if(!(part&&*part++))part=name;
 if(_strnicmp(part,"HOUSECOLOR",10)==0){
  for(int i=0;i<materials->count;++i){
   VertexMaterialClass *material=materials->Peek_Vertex_Material(i);material->Make_Unique();
   Vector3 rgb,rgb2;
   rgb.X=(float)*reinterpret_cast<const unsigned short*>(reinterpret_cast<const char*>(&options)+6)*(1.0f/255.0f);
   rgb.Y=(float)(options.color>>8)*(1.0f/255.0f);
   rgb.Z=(float)options.color*(1.0f/255.0f);
   rgb2.X=rgb.X;rgb2.Y=rgb.Y;rgb2.Z=rgb.Z;
   material->Set_Ambient(rgb2);
   rgb2.X=rgb.X;rgb2.Y=rgb.Y;rgb2.Z=rgb.Z;
   material->Set_Diffuse(rgb2);
  }
 }
 RecolorHouseColor(options,0);
 if(materials)materials->Release_Ref();if(mesh)mesh->Release_Ref();
}
