// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include
// AnimationSoundClientBehavior::updateAnimationSounds. Retail 0x004CA328..0x004CA653.
// WB 0x012700F0, AnimationSoundClientBehavior.cpp:391..424; retail adds parent-distance test.
// The committed BFME1 same-name file contains an unrelated ghost-object worker.
// Native +0x44A gates sound participation; +0xFC provides the parent position.
// ModuleData tree+8 / key payload+0x10 / 168-byte key / 136-byte audio event
// agree with the already verified constructor, tree, mask and event siblings.
// Module slots are reread across loop iterations as native does. Inline key
// construction preserves the native compare encoding; its emitted 55 bytes
// are independently verified at 0x004C9E5D and resolve to the rowed provider.
#include "Lib/Coord3D.h"
#include "Common/BfmeAudioEventPrefix136.h"
enum DrawableID { INVALID_DRAWABLE_ID=0 };
__forceinline const float& rangeMax(const float&a,const float&b){return a>b?a:b;}
__forceinline const float& rangeMin(const float&a,const float&b){return a<b?a:b;}
// ?Range::Range present-unmatched
struct Range { float first,second; Range():first(0.0f),second(0.0f){} };
class Rva0042526Member { public: Rva0042526Member(); unsigned int words[19]; };
// ?AnimationSoundNullRef::AnimationSoundNullRef present-unmatched
struct AnimationSoundNullRef : OpaqueRefElement4 { __forceinline AnimationSoundNullRef(){referent=0;} };
class Rva004C9E5D { public:
 Rva004C9E5D(const int*,float);
 // ?Rva004C9E5D::~Rva004C9E5D present-unmatched
 __forceinline ~Rva004C9E5D(){if(sound.referent)sound.referent->Release_Ref();}
 int id; AnimationSoundNullRef sound; float frame;
 Rva0042526Member required,prohibited; unsigned char conditional;
};
inline Rva004C9E5D::Rva004C9E5D(const int*p,float f):id(*p),sound(),frame(f),required(),prohibited(),conditional(0){}
typedef char EntryExtent[(sizeof(Rva004C9E5D)==168)?1:-1];
namespace _STL {
struct _Rb_tree_node_base { bool color; _Rb_tree_node_base *parent,*left,*right; };
template<class D> class _Rb_global { public: static _Rb_tree_node_base* __cdecl _M_increment(_Rb_tree_node_base*); };
}
struct AnimationSoundTreeNode { int color; AnimationSoundTreeNode *parent,*left,*right; Rva004C9E5D payload; };
class AnimationSoundTree { public: AnimationSoundTreeNode *rva004C9FE0(const void*); AnimationSoundTreeNode*header; unsigned int count; char comparator; };
struct ModuleData { void*vptr; int unknown04; AnimationSoundTree tree; float cap; };
class Rva001DFE56 { public: bool rva001DFE56(const void*,const void*) const; };
class Rva00432F23Node;
class Rva00432F23 { public: void rva00432EC0(Rva00432F23Node*); };
extern Rva00432F23 *g_004C9DC9Container;
class ObjectDrawInterface { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual int getAnimationCount()=0;
 virtual void slot10()=0;
 virtual int getAnimationKey(int)=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void getPlayingRange(int,Range*,Range*)=0;
};
class DrawModule { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void slot21()=0;
 virtual void slot22()=0;
 virtual void slot23()=0;
 virtual void slot24()=0;
 virtual void slot25()=0;
 virtual void slot26()=0;
 virtual void slot27()=0;
 virtual void slot28()=0;
 virtual void slot29()=0;
 virtual void slot30()=0;
 virtual void slot31()=0;
 virtual void slot32()=0;
 virtual void slot33()=0;
 virtual void slot34()=0;
 virtual void slot35()=0;
 virtual void slot36()=0;
 virtual void slot37()=0;
 virtual void slot38()=0;
 virtual void slot39()=0;
 virtual void slot40()=0;
 virtual ObjectDrawInterface *getDrawInterface()=0;
};
class AudioManager { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void slot21()=0;
 virtual void slot22()=0;
 virtual void slot23()=0;
 virtual void slot24()=0;
 virtual int addAudioEvent(const BfmeAudioEventPrefix136*)=0;
 virtual void slot26()=0;
 virtual void slot27()=0;
 virtual void slot28()=0;
 virtual void slot29()=0;
 virtual void slot30()=0;
 virtual void slot31()=0;
 virtual void slot32()=0;
 virtual void slot33()=0;
 virtual void slot34()=0;
 virtual void slot35()=0;
 virtual void slot36()=0;
 virtual void slot37()=0;
 virtual void slot38()=0;
 virtual void slot39()=0;
 virtual void slot40()=0;
 virtual void slot41()=0;
 virtual void slot42()=0;
 virtual void slot43()=0;
 virtual void slot44()=0;
 virtual void slot45()=0;
 virtual void slot46()=0;
 virtual void slot47()=0;
 virtual void slot48()=0;
 virtual void slot49()=0;
 virtual void slot50()=0;
 virtual void slot51()=0;
 virtual void slot52()=0;
 virtual void slot53()=0;
 virtual void slot54()=0;
 virtual void slot55()=0;
 virtual void slot56()=0;
 virtual void slot57()=0;
 virtual void slot58()=0;
 virtual void slot59()=0;
 virtual void slot60()=0;
 virtual void slot61()=0;
 virtual void slot62()=0;
 virtual void slot63()=0;
 virtual void slot64()=0;
 virtual void slot65()=0;
 virtual void slot66()=0;
 virtual void slot67()=0;
 virtual void slot68()=0;
 virtual void slot69()=0;
 virtual void slot70()=0;
 virtual void slot71()=0;
 virtual const Coord3D* getListenerPosition()=0;
};
extern AudioManager *TheAudio;
struct ObjectPositionView { char unknown[0x38]; Coord3D position; };
class Drawable { public:
 const Coord3D* getPosition() const; DrawableID getID() const; DrawModule**getDrawModules();
 char unknown00[0xFC]; ObjectPositionView *parent; char unknown100[0x34A]; bool enabled;
};
class AnimationSoundClientBehavior { public:
 void updateAnimationSounds(); void*vptr; const ModuleData*data; Drawable*drawable;
 void*secondary; float rangeSquared; void*next; void*prev;
};
void AnimationSoundClientBehavior::updateAnimationSounds()
{
 Drawable*d=drawable;
 if(!d)return;
 if(!d->enabled){if(g_004C9DC9Container)g_004C9DC9Container->rva00432EC0((Rva00432F23Node*)this);return;}
 if(!TheAudio)return;
 const Coord3D*microphone=TheAudio->getListenerPosition();
 Coord3D relative={microphone->x,microphone->y,microphone->z};
 const Coord3D*position=d->getPosition();
 relative.x-=position->x;relative.y-=position->y;relative.z-=position->z;
 if(relative.z*relative.z+relative.y*relative.y+relative.x*relative.x>rangeSquared){
  if(d->parent){relative=*microphone;position=&d->parent->position;
   relative.x-=position->x;relative.y-=position->y;relative.z-=position->z;
   if(rangeSquared>=relative.z*relative.z+relative.y*relative.y+relative.x*relative.x)return;
  }
  if(g_004C9DC9Container)g_004C9DC9Container->rva00432EC0((Rva00432F23Node*)this);
  return;
 }
 AnimationSoundTree*tree=(AnimationSoundTree*)&data->tree;
 DrawModule**moduleList=d->getDrawModules();if(!moduleList)return;
 DrawModule* volatile*modules=moduleList;
 for(;*modules;++modules){
  ObjectDrawInterface*draw=(*modules)->getDrawInterface();if(!draw)continue;
  int count=draw->getAnimationCount();
  for(int index=0;index<count;++index){
   int key=draw->getAnimationKey(index);Range ranges[2];
   draw->getPlayingRange(index,&ranges[0],&ranges[1]);
   for(unsigned int r=0;r<2;++r){
    if(ranges[r].first==ranges[r].second)continue;
    float maximum=rangeMax(ranges[r].first,ranges[r].second);
    Rva004C9E5D query(&key,rangeMin(ranges[r].first,ranges[r].second));
    AnimationSoundTreeNode*iter=tree->rva004C9FE0(&query);
    AnimationSoundTreeNode*end=tree->header;
    while(iter!=end && iter->payload.id==key && maximum>=iter->payload.frame){
     Rva004C9E5D*entry=&iter->payload;
     iter=(AnimationSoundTreeNode*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)iter);
     if(entry->frame==ranges[r].first)continue;
     if(entry->conditional && !((Rva001DFE56*)((char*)d+0x258))->rva001DFE56(&entry->required,&entry->prohibited))continue;
     BfmeAudioEventPrefix136 event(entry->sound,d->getID());
     TheAudio->addAudioEvent(&event);
    }
   }
  }
 }
}
