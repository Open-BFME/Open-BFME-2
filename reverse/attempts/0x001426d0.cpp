// ?Visibility_Check@SimpleSceneClass@@UAEXPAVCameraClass@@@Z
// partial score=0.924 date=2026-10-09
// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /O2 /G7 /arch:SSE
// Native SimpleScene constructor142960 stores vftableBD33D0; slot27 points
// at this523B body. ZH Visibility_Check supplies the force-visible/cull role;
// BFME2 adds changed-object spatial updates and a visible owning list.
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
#include "camera.h"
struct Gen_00943CF0_Node { Gen_00943CF0_Node *m_next; void *m_value; };
class Rva0006EFC8 {
public:
 bool rva0006EFC8(int arena,int size);
 int m_00; void *m_04; void *m_head;
 void *(__cdecl *m_alloc)(int,int);
 void (__cdecl *m_free)(void*,int); int m_14;
};
extern Rva0006EFC8 g_Rva0006EFC8Pool00DB424C;
struct Rva00943FF0List {
 Gen_00943CF0_Node *head;
 // ?Rva00943FF0List::~Rva00943FF0List present-unmatched
 ~Rva00943FF0List() {
  Gen_00943CF0_Node *current=head;
  while(current) { Gen_00943CF0_Node *old=current; current=current->m_next;
   old->m_next=(Gen_00943CF0_Node*)g_Rva0006EFC8Pool00DB424C.m_head;
   g_Rva0006EFC8Pool00DB424C.m_head=old;
  }
 }
};
class Gen_00943CF0 {
 friend class SimpleSceneClass;
 void first(void*,int*,int*,int*);
};
class BfmeSceneVector { public: void rva00142410(Gen_00943CF0_Node **out,CameraClass *camera,const float *margin); };
// Native camera extends the 129-slot RenderObj/Camera prefix by sphere culling.
// Only this target call contract is asserted; original extension name unknown.
class SceneVisibilityCamera : public CameraClass {
public: virtual bool rva001426D0Cull(const SphereClass &sphere)=0;
};
typedef char SceneVisibilityCameraSize[(sizeof(SceneVisibilityCamera)==sizeof(CameraClass))?1:-1];
void SimpleSceneClass::Visibility_Check(CameraClass *camera)
{
 MultiListIterator<RenderObjClass> changed(&_bfme_changed_objects);
 for(;!changed.Is_Done();changed.Next()) {
  RenderObjClass *obj=changed.Peek_Obj();
  volatile int outY,outX,outLevel;
  ((Gen_00943CF0*)&_bfme_spatial_index)->first(obj,(int*)&outY,(int*)&outX,(int*)&outLevel);
  int level=outLevel;
  int x=outX;
  int y=outY;
  int token=SceneClass::_bfme_spatial_token(obj);
  if(token<0) _bfme_spatial_index.Insert(obj,y,x,level);
  else if(token!=(((y<<10)|x)<<10|level)) {
   _bfme_spatial_index.Remove(obj);
   _bfme_spatial_index.Insert(obj,y,x,level);
  }
 }
 MultiListClass<RenderObjClass> *dirty=&_bfme_changed_objects;
 while(dirty->Peek_Head()!=0) dirty->Remove_Head();
 ++_bfme_visibility_token;
 RefMultiListClass<RenderObjClass> *visible=&_bfme_visible_objects;
 visible->Reset_List();
 Rva00943FF0List objects={0};
 ((BfmeSceneVector*)&_bfme_spatial_index)->rva00142410(&objects.head,camera,0);
 for(Gen_00943CF0_Node *node=objects.head;node;node=node->m_next) {
  RenderObjClass *obj=(RenderObjClass*)node->m_value;
  if(obj->Is_Force_Visible() || !((SceneVisibilityCamera*)camera)->rva001426D0Cull(obj->Get_Bounding_Sphere())) {
   visible->Add(obj);
   obj->Set_Visible((int)this,_bfme_visibility_token);
  }
 }
 MultiListIterator<RenderObjClass> forced(&_bfme_forced_objects);
 for(;!forced.Is_Done();forced.Next()) visible->Add(forced.Peek_Obj());
}
