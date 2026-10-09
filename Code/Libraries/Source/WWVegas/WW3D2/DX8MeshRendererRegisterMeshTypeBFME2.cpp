// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /O2 /G7 /arch:SSE
// ZH dx8renderer.cpp Register_Mesh_Type semantic source. Native145C30..145E88
// proves flag18, skin-links50, polygon list9C, renderer vector8 and skin-list18.
// BFME2 omits ZH registered-mesh global bookkeeping. The native skin constructor
// adds opaque E8 and F8 state around the visible count/list; no semantics guessed.
#include "multilist.h"
#include "simplevec.h"
class DX8PolygonRendererClass;
class MeshModelClass {
public:
 char pad0[0x18]; unsigned Flags; char SortLevel; char pad1[0x33]; void *VertexBoneLink;
 char pad2[0x48]; MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
};
class MaterialPassClass;
class MeshClass;
class DX8FVFCategoryContainer: public MultiListObjectClass {
public:
 DX8FVFCategoryContainer(unsigned,bool);
 virtual ~DX8FVFCategoryContainer();
 virtual void Render()=0;
 virtual void Add_Mesh(MeshModelClass*)=0;
 virtual void Log(bool)=0;
 virtual bool Check_If_Mesh_Fits(MeshModelClass*)=0;
 virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass*,MeshClass*)=0;
 virtual void Render_Delayed_Procedural_Material_Passes()=0;
 static unsigned Define_FVF(MeshModelClass*,bool);
 bool Is_Sorting()const{return sorting;}
 unsigned Get_FVF()const{return FVF;}
private:
 char pad[0xD0]; unsigned FVF; char tail[8]; bool sorting; char align[3];
};
class DX8SkinFVFCategoryContainer:public DX8FVFCategoryContainer {
public:
 __forceinline DX8SkinFVFCategoryContainer(bool sorting):DX8FVFCategoryContainer(0x112,sorting),rva_e8(0),VisibleVertexCount(0),VisibleSkinHead(0),VisibleSkinTail(0),rva_f8(false){}
 virtual ~DX8SkinFVFCategoryContainer();
 virtual void Render();
 virtual void Add_Mesh(MeshModelClass*);
 virtual void Log(bool);
 virtual bool Check_If_Mesh_Fits(MeshModelClass*);
 virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass*,MeshClass*);
 virtual void Render_Delayed_Procedural_Material_Passes();
private:
 void *rva_e8; unsigned VisibleVertexCount; MeshClass *VisibleSkinHead,*VisibleSkinTail; bool rva_f8;
};
typedef MultiListClass<DX8FVFCategoryContainer> FVFCategoryList;
typedef MultiListIterator<DX8FVFCategoryContainer> FVFCategoryListIterator;
void Add_Rigid_Mesh_To_Container(FVFCategoryList*,unsigned,MeshModelClass*);
class WW3D {public:static bool Is_Sorting_Enabled(){return _IsSortingEnabled;} static bool _IsSortingEnabled;};
class DX8MeshRendererClass {
public:
 void Register_Mesh_Type(MeshModelClass*);
private:
 bool enable_lighting; void *camera;
 SimpleDynVecClass<FVFCategoryList*> texture_category_container_lists_rigid;
 FVFCategoryList *texture_category_container_list_skin;
};
typedef char ModelListOffset[(sizeof(MeshModelClass)==0xB4)?1:-1];
typedef char SkinSize[(sizeof(DX8SkinFVFCategoryContainer)==0xFC)?1:-1];
void DX8MeshRendererClass::Register_Mesh_Type(MeshModelClass* mmc)
{
 bool skin=(mmc->Flags&0x400) && mmc->VertexBoneLink;
 bool sorting=(mmc->Flags&0x10) && WW3D::Is_Sorting_Enabled() && mmc->SortLevel==0;
 if(skin){
  FVFCategoryListIterator it(texture_category_container_list_skin);
  while(!it.Is_Done()) {
   DX8FVFCategoryContainer *container=it.Peek_Obj();
   if(sorting==container->Is_Sorting() && container->Check_If_Mesh_Fits(mmc)) {
    container->Add_Mesh(mmc);return;
   }
   it.Next();
  }
  DX8FVFCategoryContainer *new_container=new DX8SkinFVFCategoryContainer(sorting);
  texture_category_container_list_skin->Add_Tail(new_container);
  new_container->Add_Mesh(mmc);
 }else if(mmc->PolygonRendererList.Is_Empty()) {
  unsigned fvf=DX8FVFCategoryContainer::Define_FVF(mmc,enable_lighting);
  for(int i=0;i<texture_category_container_lists_rigid.Count();++i){
   FVFCategoryList *list=texture_category_container_lists_rigid[i];
   DX8FVFCategoryContainer *container=list->Peek_Head();
   if(container && container->Get_FVF()!=fvf)continue;
   Add_Rigid_Mesh_To_Container(list,fvf,mmc);break;
  }
  if(i==texture_category_container_lists_rigid.Count()) {
   FVFCategoryList *new_fvf_category=new FVFCategoryList();
   texture_category_container_lists_rigid.Add(new_fvf_category);
   Add_Rigid_Mesh_To_Container(new_fvf_category,fvf,mmc);
  }
 }
}
