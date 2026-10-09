// ?setCameraTransform@W3DView@@AAEXXZ
// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Native8BE6B..8C224 953B; WB9886F0 independently names setCameraTransform.
// Clean BFME1 camera-transform donor at2f243e26d supplies the guide;
// native bytes establish the target layouts, counted-camera return ABI,
// terrain slot218, settings and all extra passes. Larger builder/constraints
// are independently recovered providers. Existing integer Vector_base ctor
// is used as a three-pointer storage ABI view, with the real owning63B dtor.
// Scoped volatile stores express the retail x-clamp then y-clamp write order.
// Private unmodified float far-scale retains native FMUL dword precision;
// literal double promotion otherwise emits FMUL qword. No new alias pins.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include "Coord3D.h"
struct CameraPoint:public Coord3D {__forceinline CameraPoint(const Coord3D&p){x=p.x;y=p.y;z=p.z;}};
static __forceinline float cameraClamp(float x,float low,float high){return low>x?low:(x>high?high:x);}
// Internal scale is initialized once and never modified or exposed.
static float CameraFarScale=1800.f;
class CameraClass {public:
 virtual void v000();
 virtual void v001();
 virtual void v002();
 virtual void v003();
 virtual void v004();
 virtual void v005();
 virtual void v006();
 virtual void v007();
 virtual void v008();
 virtual void v009();
 virtual void v010();
 virtual void v011();
 virtual void v012();
 virtual void v013();
 virtual void v014();
 virtual void v015();
 virtual void v016();
 virtual void v017();
 virtual void v018();
 virtual void v019();
 virtual void v020();
 virtual void Set_Transform(const Matrix3D&);
 int refs;void Add_Ref(){refs++;}void Release_Ref(){refs--;if(refs==0)v000();}
 void Set_Clip_Planes(float,float);void Set_View_Plane(float,float);
};
struct Rva0008B689Element {CameraClass *pointer; Rva0008B689Element():pointer(0){} __forceinline Rva0008B689Element(const Rva0008B689Element&p):pointer(p.pointer){if(pointer)pointer->Add_Ref();} ~Rva0008B689Element(){if(pointer)pointer->Release_Ref();}bool isNull()const{return pointer==0;}};
namespace _STL {template<> void vector<Rva0008B689Element>::push_back(const Rva0008B689Element&);}
class Rva0008B470:private _STL::_Vector_base<int,_STL::allocator<int> > {typedef _STL::_Vector_base<int,_STL::allocator<int> > Base;public:__forceinline Rva0008B470(const _STL::allocator<int>&a=_STL::allocator<int>()):Base(a){}~Rva0008B470();void push_back(const Rva0008B689Element&p){reinterpret_cast<std::vector<Rva0008B689Element>*>(this)->push_back(p);}};
Rva0008B689Element Rva000897C8(CameraClass*);
class Rva0007D9B5Host{public:void rva0007D9B5(int);};
class Rva0007BB79Owner{public:Rva0008B689Element rva0007BB79();};
class Rva0007FD57Owner{public:Rva0008B689Element rva0007FD57(CameraClass*);};
class Rva0007DA23ResourceManager;extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;
extern void *W3DGCData00DE2000;
class RenderObjClass;template<class T>class RefMultiListIterator;
class Rva0006ED29 {public:void rva0006ED29(void*);};
class RTS3DScene{public:RefMultiListIterator<RenderObjClass>*createLightsIterator();void destroyLightsIterator(RefMultiListIterator<RenderObjClass>*);};
class W3DDisplay{public:static RTS3DScene*m_3DScene;};
class BaseHeightMapRenderObjClass{public:
virtual void v000();
virtual void v001();
virtual void v002();
virtual void v003();
virtual void v004();
virtual void v005();
virtual void v006();
virtual void v007();
virtual void v008();
virtual void v009();
virtual void v010();
virtual void v011();
virtual void v012();
virtual void v013();
virtual void v014();
virtual void v015();
virtual void v016();
virtual void v017();
virtual void v018();
virtual void v019();
virtual void v020();
virtual void v021();
virtual void v022();
virtual void v023();
virtual void v024();
virtual void v025();
virtual void v026();
virtual void v027();
virtual void v028();
virtual void v029();
virtual void v030();
virtual void v031();
virtual void v032();
virtual void v033();
virtual void v034();
virtual void v035();
virtual void v036();
virtual void v037();
virtual void v038();
virtual void v039();
virtual void v040();
virtual void v041();
virtual void v042();
virtual void v043();
virtual void v044();
virtual void v045();
virtual void v046();
virtual void v047();
virtual void v048();
virtual void v049();
virtual void v050();
virtual void v051();
virtual void v052();
virtual void v053();
virtual void v054();
virtual void v055();
virtual void v056();
virtual void v057();
virtual void v058();
virtual void v059();
virtual void v060();
virtual void v061();
virtual void v062();
virtual void v063();
virtual void v064();
virtual void v065();
virtual void v066();
virtual void v067();
virtual void v068();
virtual void v069();
virtual void v070();
virtual void v071();
virtual void v072();
virtual void v073();
virtual void v074();
virtual void v075();
virtual void v076();
virtual void v077();
virtual void v078();
virtual void v079();
virtual void v080();
virtual void v081();
virtual void v082();
virtual void v083();
virtual void v084();
virtual void v085();
virtual void v086();
virtual void v087();
virtual void v088();
virtual void v089();
virtual void v090();
virtual void v091();
virtual void v092();
virtual void v093();
virtual void v094();
virtual void v095();
virtual void v096();
virtual void v097();
virtual void v098();
virtual void v099();
virtual void v100();
virtual void v101();
virtual void v102();
virtual void v103();
virtual void v104();
virtual void v105();
virtual void v106();
virtual void v107();
virtual void v108();
virtual void v109();
virtual void v110();
virtual void v111();
virtual void v112();
virtual void v113();
virtual void v114();
virtual void v115();
virtual void v116();
virtual void v117();
virtual void v118();
virtual void v119();
virtual void v120();
virtual void v121();
virtual void v122();
virtual void v123();
virtual void v124();
virtual void v125();
virtual void v126();
virtual void v127();
virtual void v128();
virtual void v129();
virtual void v130();
virtual void v131();
virtual void v132();
virtual void v133();
virtual void updateCenter(std::vector<Rva0008B689Element >&,RefMultiListIterator<RenderObjClass>*);};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class Rva00203B2BHost{public:void rva00203B2B();};class ScriptEngine;extern ScriptEngine *TheScriptEngine;
class AudioManager{public:
virtual void v000();
virtual void v001();
virtual void v002();
virtual void v003();
virtual void v004();
virtual void v005();
virtual void v006();
virtual void v007();
virtual void v008();
virtual void v009();
virtual void v010();
virtual void v011();
virtual void v012();
virtual void v013();
virtual void v014();
virtual void v015();
virtual void v016();
virtual void v017();
virtual void v018();
virtual void v019();
virtual void v020();
virtual void v021();
virtual void rva0008BE6BNotify();};extern AudioManager*TheAudio;
class GlobalData{public:char pad[0x950];float clipMultiplier;char pad954[0xea6-0x954];bool debug,unused;float debugFov,debugAngle;};extern GlobalData*TheWritableGlobalData;
class W3DView{void *vtable;char pad4[8];Coord3D position;char pad18[0x44-0x18];bool constrain;char pad45[0x6c-0x45];float fov;char pad70[0x104-0x70];CameraClass *camera;char pad108[0x2354-0x108];int mode;char pad2358[12];float modeFov;char pad2368[0x23d8-0x2368];bool moved;char pad23d9[0x240c-0x23d9];float loX,loY,hiX,hiY;bool valid;
 void buildCameraTransform(Matrix3D*);void calcCameraConstraints();void setCameraTransform();
};
void W3DView::setCameraTransform(){
 moved=true;Matrix3D transform(1);
 camera->Set_Clip_Planes(10.0f,(double)TheWritableGlobalData->clipMultiplier*CameraFarScale);
 if(!valid){buildCameraTransform(&transform);camera->Set_Transform(transform);calcCameraConstraints();}
 if(valid && constrain){CameraPoint pos(position);static_cast<volatile float&>(pos.x)=cameraClamp(pos.x,loX,hiX);static_cast<volatile float&>(pos.y)=cameraClamp(pos.y,loY,hiY);position=pos;}
 if(TheWritableGlobalData->debug)camera->Set_View_Plane(TheWritableGlobalData->debugFov,-1.0f);else camera->Set_View_Plane(fov,-1.0f);
 buildCameraTransform(&transform);
 if(mode==4)camera->Set_View_Plane(modeFov,-1.0f);
 if(TheWritableGlobalData->debug)transform.Rotate_Y(TheWritableGlobalData->debugAngle);
 camera->Set_Transform(transform);
 if(TheTerrainRenderObject){
  RefMultiListIterator<RenderObjClass>*it=W3DDisplay::m_3DScene->createLightsIterator();Rva0008B470 cameras;
  cameras.push_back(Rva000897C8(camera));
  if(Rva00DE1FF8Manager){reinterpret_cast<Rva0007D9B5Host*>(Rva00DE1FF8Manager)->rva0007D9B5((int)camera);Rva0008B689Element extra=reinterpret_cast<Rva0007BB79Owner*>(Rva00DE1FF8Manager)->rva0007BB79();if(!extra.isNull())cameras.push_back(extra);}
  if(W3DGCData00DE2000){Rva0008B689Element extra=reinterpret_cast<Rva0007FD57Owner*>(W3DGCData00DE2000)->rva0007FD57(camera);if(!extra.isNull())cameras.push_back(extra);}
  TheTerrainRenderObject->updateCenter(*reinterpret_cast<std::vector<Rva0008B689Element>*>(&cameras),it);if(it)reinterpret_cast<Rva0006ED29*>(W3DDisplay::m_3DScene)->rva0006ED29(it);
 }
 reinterpret_cast<Rva00203B2BHost*>(TheScriptEngine)->rva00203B2B();if(TheAudio)TheAudio->rva0008BE6BNotify();
}
