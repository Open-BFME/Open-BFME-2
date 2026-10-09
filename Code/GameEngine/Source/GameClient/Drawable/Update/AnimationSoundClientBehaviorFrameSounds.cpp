// Ghidra004C9E5D+55, called by animation-sound processing004CA328.
// Clean BF1 9cbfb551fe20 AnimationSoundInfoCtor.cpp establishes key/reference/frame
// and required/excluded-condition semantics. Target key is an integer identifier;
// masks are19 words each (76B), versus BF1 ten; offsets0/4/8/C/58/A4 are target facts.
// The prefix shares the independently verified Rva002390CB cleanup (owner+4 release).
// Inheritance is a C++ prefix/lifetime view, not a claim about the original class.
// Default intrusive-reference construction after key initialization preserves native store order.
// Original record owner remains unknown; keep its constructor address-derived.
// ?rva004CA328@AnimationSoundClientBehavior@@QAEXXZ
// Target 4CA328..4CA653: WB12700F0 identifies updateAnimationSounds.
// BF1 AnimationSoundInfoCtor9cbfb551 supplies record semantics; target
// masks and drawable fields are independently established in native accesses.
// Iterator and key read views preserve the native reload/compare order.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include/Lib
#include "Common/BfmeAudioEventPrefix136.h"
#include "Coord3D.h"
enum DrawableID { INVALID_DRAWABLE_ID=0 };
struct Rva0042526Member {unsigned words[19];Rva0042526Member() throw();};
struct AudioKeyRef {void*p;__forceinline AudioKeyRef():p(0){} __forceinline ~AudioKeyRef(){if(p)((OpaqueRefCounted*)p)->Release_Ref();}};
class Rva002390CB {public:
 __forceinline Rva002390CB(const int *p):key(*p),audio(){}
 int key;AudioKeyRef audio;
};
class Rva004C9E5D:public Rva002390CB
{
public:
 Rva004C9E5D(const int*,float);
 float frame;
 Rva0042526Member required,excluded;
 bool anyConditions;
};
Rva004C9E5D::Rva004C9E5D(const int*p,float f):Rva002390CB(p),frame(f),anyConditions(false) {}
struct AnimationSoundTreeNode {int color;AnimationSoundTreeNode*parent,*left,*right;Rva004C9E5D value;};
class AnimationSoundTree {public:AnimationSoundTreeNode*header;int count;AnimationSoundTreeNode*rva004C9FE0(const void*);};
namespace _STL {struct _Rb_tree_node_base;template<class T>class _Rb_global {public:static _Rb_tree_node_base*__cdecl _M_increment(_Rb_tree_node_base*);};}
class DrawModule;
class Drawable {public:const Coord3D *getPosition() const;DrawModule**getDrawModules();DrawableID getID() const;};
struct DrawableFrameSoundView {char pad00[0xfc];void*parent;char pad100[0x158];char conditionFlags[76];char pad2a4[0x1a6];bool active;};
struct ObjectSoundPositionView {char pad00[0x38];Coord3D position;};
class Rva001DFE56 {public:bool rva001DFE56(const void*,const void*) const;};
class AnimationSoundClientBehavior;
class Rva00432F23Node;
class Rva00432F23 {public:void rva00432EC0(Rva00432F23Node*);};extern Rva00432F23*g_004C9DC9Container;
class AudioManager;extern AudioManager*TheAudio;
template<int N>class FrameSoundSlots:public FrameSoundSlots<N-1> {public:virtual void gap(char(*)[N]);};
template<>class FrameSoundSlots<1> {public:virtual void gap(char(*)[1]);};
class AudioFrameSoundCalls:public FrameSoundSlots<25>{public:virtual void add(const BfmeAudioEventPrefix136*);virtual void pad1a();virtual void pad1b();virtual void pad1c();virtual void pad1d();virtual void pad1e();virtual void pad1f();virtual void pad20();virtual void pad21();virtual void pad22();virtual void pad23();virtual void pad24();virtual void pad25();virtual void pad26();virtual void pad27();virtual void pad28();virtual void pad29();virtual void pad2a();virtual void pad2b();virtual void pad2c();virtual void pad2d();virtual void pad2e();virtual void pad2f();virtual void pad30();virtual void pad31();virtual void pad32();virtual void pad33();virtual void pad34();virtual void pad35();virtual void pad36();virtual void pad37();virtual void pad38();virtual void pad39();virtual void pad3a();virtual void pad3b();virtual void pad3c();virtual void pad3d();virtual void pad3e();virtual void pad3f();virtual void pad40();virtual void pad41();virtual void pad42();virtual void pad43();virtual void pad44();virtual void pad45();virtual void pad46();virtual void pad47();virtual const Coord3D*listener();};
struct FrameRange {float previous,current;__forceinline FrameRange():previous(0.0f),current(0.0f){}};
class DrawFrameSoundCalls:public FrameSoundSlots<41> {public:virtual void*animations();};
class AnimationFrameSoundCalls:public FrameSoundSlots<9>{public:virtual int count();virtual void pad28();virtual int key(int);virtual void pad30();virtual void pad34();virtual void pad38();virtual void ranges(int,FrameRange*,FrameRange*);};
class AnimationSoundClientBehavior {public:void rva004CA328();void*head;void*data;Drawable*drawable;void*iface;float maxDistanceSq;};
static __forceinline float squareLength(const Coord3D&p){return p.z*p.z+p.y*p.y+p.x*p.x;}
static __forceinline const float&soundMin(const float&a,const float&b){return b>a?a:b;}
static __forceinline const float&soundMax(const float&a,const float&b){return a>b?a:b;}
void AnimationSoundClientBehavior::rva004CA328() {
 Drawable *d=drawable;if(!d)return;
 DrawableFrameSoundView *view=(DrawableFrameSoundView*)d;
 if(!view->active){if(g_004C9DC9Container)g_004C9DC9Container->rva00432EC0((Rva00432F23Node*)this);return;}
 if(!TheAudio)return;
 const Coord3D*listener=((AudioFrameSoundCalls*)TheAudio)->listener();
 Coord3D delta;delta.x=listener->x;delta.y=listener->y;delta.z=listener->z;
 const Coord3D*position=d->getPosition();delta.x-=position->x;delta.y-=position->y;delta.z-=position->z;
 if(squareLength(delta)>maxDistanceSq) {
  if(view->parent){delta=*listener;const Coord3D&p=((ObjectSoundPositionView*)view->parent)->position;delta.x-=p.x;delta.y-=p.y;delta.z-=p.z;if(squareLength(delta)<=maxDistanceSq)return;}
  if(g_004C9DC9Container)g_004C9DC9Container->rva00432EC0((Rva00432F23Node*)this);return;
 }
 AnimationSoundTree *tree=(AnimationSoundTree*)((char*)data+8);
 DrawModule **raw=d->getDrawModules();if(!raw)return;DrawModule**mods=raw;
 for(;*mods;++reinterpret_cast<DrawModule **volatile&>(mods)) {
  AnimationFrameSoundCalls*animations=(AnimationFrameSoundCalls*)((DrawFrameSoundCalls*)*reinterpret_cast<DrawModule **const volatile&>(mods))->animations();if(!animations)continue;
  int count=animations->count();
  for(int i=0;i<count;++i) {
   int key=animations->key(i);FrameRange range[2];animations->ranges(i,&range[0],&range[1]);
   for(int k=0;k<2;++k) {
    float &first=range[k].previous,&last=range[k].current;
    if(first==last)continue;
    float maximum=soundMax(first,last);
    Rva004C9E5D search(&key,soundMin(first,last));
    AnimationSoundTreeNode*it=tree->rva004C9FE0(&search);AnimationSoundTreeNode*end=tree->header;
    while(it!=end && it->value.key==reinterpret_cast<const volatile int&>(key) && it->value.frame<=maximum) {
     Rva004C9E5D*info=&it->value;
     it=(AnimationSoundTreeNode*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)it);
     if(info->frame!=first) {
      if(!info->anyConditions||((Rva001DFE56*)view->conditionFlags)->rva001DFE56(&info->required,&info->excluded)) {
       BfmeAudioEventPrefix136 event(*(OpaqueRefElement4*)&info->audio,d->getID());
       ((AudioFrameSoundCalls*)TheAudio)->add(&event);
      }
     }
    }
   }
  }
 }
}
