// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB
// stlport
// Whole native 0x00740BCD..0x00740E76 RET12, 683B.
// WB 0x017EDEB0 asserts W3DAptComponentView3D::AddRenderObj.
// This is target reconstruction; BFME1 same-path donor only implements the
// separate animation binding operation, not this method.
// The first stack word is unused: its original source type remains unknown.
// Every view field and used virtual slot is based on this retail body; these
// view names do not establish original class names or undocumented slots.
#include <stdlib.h>
#include "ascii_string.h"
// The 12-byte empty-set constructor is the folded 0x000D3A71, rowed as
// set<AsciiString>::set() (the NetworkGetCommandsFromCommandList view); the
// name is the link spelling, not an identity claim for the asset keys.
namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class K, class C, class A> class set
{
public:
	set();
private:
	unsigned storage[3];
};
}
typedef _STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva002EE9B7;
void j_00015d7a();
// The registry already uses this 20-byte lifetime view and the same verified
// member-call projection of the tree destructor; no new template is emitted.
struct Q1ReceiverLocalSet {
 // The parent inlines these field stores; suppress the unused constructor
 // COMDAT, whose relocation spelling would compete with the registry copy.
 __declspec(dllimport) __forceinline Q1ReceiverLocalSet() : pad(0),changed(true) {}
 ~Q1ReceiverLocalSet() {
  typedef void (Rva002EE9B7::*TreeDestructor)();
  union { void (*raw)(); TreeDestructor member; } destroy;
  destroy.raw=j_00015d7a;
  (keys.*destroy.member)();
 }
 Rva002EE9B7 keys;
 unsigned pad;
 bool changed;
};
typedef char AptAssetHolderExtent[(sizeof(Q1ReceiverLocalSet)==20)?1:-1];
class AssetList { public: AssetList &operator<<(const AsciiString &); };
void bfmeMergeReceiverKeys(int);
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
// Retail VA0x00E1F2B4 is a zero-initialized unsigned call counter.
// This descriptive name is reconstructed; the original identifier is unknown.
unsigned AptViewAddRenderObjCounter = 0;
struct AptVector { float x,y,z; void set(float a,float b,float c) {x=a;y=b;z=c;} };
struct AptSphere { AptVector center; float radius; };
struct AptMatrix {
 float m[3][4];
 AptMatrix() {
  m[0][0]=1.0f;m[0][1]=0.0f;m[0][2]=0.0f;m[0][3]=0.0f;
  m[1][0]=0.0f;m[1][1]=1.0f;m[1][2]=0.0f;m[1][3]=0.0f;
  m[2][0]=0.0f;m[2][1]=0.0f;m[2][2]=1.0f;m[2][3]=0.0f;
 }
};
#include "../../../../../../reference/shims/wwmath/Vector2.h"
// CameraClass slots 0x40/0x44 in retail are getWidth/getHeight on the display;
// this method's camera view supplies Set_Viewport/Set_Aspect_Ratio (nonvirtual
// rowed members) and slot 0x54. Slot names are ABI placeholders.
class CameraClass {
public:
	inline void Set_Viewport(const Vector2 &min, const Vector2 &max);
	void Set_Aspect_Ratio(float);
	virtual void cam00();
	virtual void cam01();
	virtual void cam02();
	virtual void cam03();
	virtual void cam04();
	virtual void cam05();
	virtual void cam06();
	virtual void cam07();
	virtual void cam08();
	virtual void cam09();
	virtual void cam10();
	virtual void cam11();
	virtual void cam12();
	virtual void cam13();
	virtual void cam14();
	virtual void cam15();
	virtual void cam16();
	virtual void cam17();
	virtual void cam18();
	virtual void cam19();
	virtual void cam20();
	virtual void cam21(const AptMatrix &);
};
// CameraClass::Set_Viewport (rowed 0x0007E6A6, CameraSetViewportO1.cpp) is
// visible here: its ViewportMin/ViewportMax (+0xC8/+0xD0) stores and
// FrustumValid clear (+0xFC) let cl pack Render's dead display extents into
// the viewport locals, as retail's frame does.
struct CameraViewportFields { char pad[0xC8]; Vector2 ViewportMin; Vector2 ViewportMax; char padD8[0xFC - 0xD8]; bool FrustumValid; };
inline void CameraClass::Set_Viewport(const Vector2 &min, const Vector2 &max)
{
	CameraViewportFields *cameraViewportFields = (CameraViewportFields *)this;
	cameraViewportFields->ViewportMin = min;
	cameraViewportFields->ViewportMax = max;
	cameraViewportFields->FrustumValid = false;
}
// Display vtable slots 0x40/0x44 return the unsigned viewport extents.
class Display
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual unsigned getWidth();
	virtual unsigned getHeight();
};
extern Display *TheDisplay;
bool Rva00118660Call(void *, void *);
class LightClass;
class AptRenderView {
public:
	virtual void release();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
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
	virtual void setTransform(const AptMatrix &);
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
	virtual void attachBone(LightClass *,int,int);
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual int boneCount();
	virtual const char *boneName(int);
	virtual void slot50();
	virtual AptMatrix slot51(int);
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
	virtual const AptSphere &bounds();
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
	virtual void setVisible(int);
 int refCount;
};
class RenderObjClass;
RenderObjClass *Create_Render_Obj(const char *);
class LightClass {
public:
 enum LightType { POINT=0,DIRECTIONAL,SPOT };
 LightClass(LightType);
 char prefix[0xC4];
 int type;
 unsigned flags;
 bool shadows;
 float intensity;
 AptVector ambient,diffuse,specular;
 float nearStart,nearEnd,farStart,farEnd;
 float spotAngle,spotAngleCos,spotExponent;
 AptVector direction;
};
// ABI-only projection of LightClass into its existing render-object prefix.
typedef char AptLightExtent[(sizeof(LightClass)==0x120)?1:-1];

class AptSceneView {
public:
	virtual void slot0();
	virtual void slot1();
	virtual void addRenderObj(AptRenderView *);
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void addLight(LightClass *,int);
};
class Rva00740AB4RefTarget;
class HTreeClass;
int Rva00740A60Get(const StringBase<char> &);
class W3DAptComponentView3D {
public:
 class AnimInfo {
 public:
  bool Init(const AsciiString &,Rva00740AB4RefTarget *,int);
  Rva00740AB4RefTarget *owner;
  HTreeClass *animation;
  int second,first;
 };
 void AddRenderObj(unsigned unused,const AsciiString &name,const StringBase<char> &mode);
 void Render(int x, int y, int width, int height);
 char unknown00[0xC];
 AptSceneView *scene;
 CameraClass *camera;
 bool aspect;
 char pad15[3];
 AptRenderView *cameraObj;
 int cameraBone;
 AnimInfo anim;
};
void W3DAptComponentView3D::AddRenderObj(unsigned unused,const AsciiString &name,const StringBase<char> &mode) {
 ++AptViewAddRenderObjCounter;
 if (!scene) return;
 if (Rva0134FAA0) {
  Q1ReceiverLocalSet assets;
  *(AssetList *)&assets << name;
  bfmeMergeReceiverKeys((int)&assets);
 }
 AptRenderView *obj=(AptRenderView *)Create_Render_Obj(name.str());
 if (!obj) return;
 int count=obj->boneCount();
 for(int i=0;i<count;++i) {
  const char *bone=obj->boneName(i);
  if (!bone || !*bone) continue;
  if (!cameraObj && !_strcmpi(bone,"CAMERA")) {
   ++obj->refCount;
   AptRenderView *old=cameraObj;
   if (old && --old->refCount==0) old->release();
   cameraObj=obj;cameraBone=i;
  } else if (strstr(bone,"LIGHT")) {
   const char *suffix=strchr(bone,'_');
   if (suffix && *suffix) {
    float factor=(float)(atoi(suffix+1)*0.01);
    if (factor>0.0f) {
     LightClass *light=new LightClass(LightClass::POINT);
     light->diffuse.set(0.5f,0.5f,0.5f);
     light->ambient.set(0.5f,0.5f,0.5f);
     light->specular.set(0.5f,0.5f,0.5f);
     light->shadows=true;
     const AptSphere &aptSphere=obj->bounds();
     double end=2.0*aptSphere.radius;
     double start=aptSphere.radius;
     light->farStart=(float)start;
     light->farEnd=(float)end;
     scene->addLight(light,1);
     obj->attachBone(light,i,0);
     AptRenderView *ref=(AptRenderView *)light;
     if (--ref->refCount==0) ref->release();
    }
   }
  }
 }
 AptMatrix identity;
 obj->setTransform(identity);
 obj->setVisible(0);
 scene->addRenderObj(obj);
 int modeIndex=Rva00740A60Get(mode);
 anim.Init(name,(Rva00740AB4RefTarget *)obj,modeIndex);
 if (--obj->refCount==0) obj->release();
}
// Native 0x007405A9..0x007406E1 RET16. W3DAptComponentView3D::Render view:
// normalized viewport from the int rect against the unsigned display extents,
// camera viewport/aspect, the camera bone transform and the WW3D scene render.
// Shape follows the BFME 1 donor Rva00789900ViewportRender.cpp, with the
// display extents read as one Vector2 (getHeight evaluated first).
void W3DAptComponentView3D::Render(int x, int y, int width, int height) {
 float w = (float)width;
 float h = (float)height;
 Vector2 screen((float)TheDisplay->getWidth(), (float)TheDisplay->getHeight());
 float invw = 1.0f / screen.X;
 Vector2 vMin;
 vMin.X = x * invw;
 float invh = 1.0f / screen.Y;
 vMin.Y = y * invh;
 Vector2 vMax(vMin.X + w * invw, vMin.Y + h * invh);
 if (vMin.X < 0.0f) vMin.X = 0.0f;
 if (vMin.Y < 0.0f) vMin.Y = 0.0f;
 if (vMax.X > 1.0f) vMax.X = 1.0f;
 if (vMax.Y > 1.0f) vMax.Y = 1.0f;
 camera->Set_Viewport(vMin, vMax);

 if (aspect)
  camera->Set_Aspect_Ratio(w / h);
 if (cameraObj) {
  AptMatrix xf = cameraObj->slot51(cameraBone);
  camera->cam21(xf);
 }
 Rva00118660Call(scene, camera);
}
