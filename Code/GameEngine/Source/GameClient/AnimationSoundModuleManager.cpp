// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/Libraries/Include/Lib
// Native433025..4330EE RET0; WB12BDFC0 names the source file, with
// no original method name. Keep the method address-derived.
// BF1@575ba2b game/GameEngine/Source/GameClient/Drawable/Behavior/
// AnimationSoundClientBehaviorGlobal_unregister.cpp supplies the intrusive
// two-list registry semantics; target offsets and dispatch come from retail.
// This receiver view has ends0C/10/14/18 and cached position20; it is not
// asserted to share the BF1 registry ABI. The node's next/previous14/18,
// audio virtual slot+0x120 and threshold setting are independently measured in native.
// Coord3D is canonical. Inline copy/subtract/length are ordinary vector
// algebra, with z/y/x evaluation order matching retail's scalar SSE.
#include "Coord3D.h"
class AnimationSoundClientBehavior {public:
 void updateAnimationSounds();
 char prefix[0x14];AnimationSoundClientBehavior *next,*previous;
};
struct AnimationSoundClientBehaviorGlobalSetting {float m_minMicrophoneDistanceToDirty;};
extern AnimationSoundClientBehaviorGlobalSetting TheAnimationSoundClientBehaviorGlobalSetting;
class AudioManager;extern AudioManager *TheAudio;
template<int N>class AnimationListenerSlots:public AnimationListenerSlots<N-1>{public:virtual void gap(char(*)[N]);};
template<>class AnimationListenerSlots<1>{public:virtual void gap(char(*)[1]);};
class AnimationListenerCalls:public AnimationListenerSlots<72>{public:virtual const Coord3D*listener();};
static __forceinline void animationSubtract(Coord3D &a,const Coord3D &b){a.x-=b.x;a.y-=b.y;a.z-=b.z;}
class AnimationSoundModuleManager {public:
 void rva00433025();
 char prefix[0x0c];AnimationSoundClientBehavior *cleanHead,*cleanTail,*dirtyHead,*dirtyTail;
 int count;Coord3D listenerPosition;
};
static __forceinline float animationSoundLengthSquared(const Coord3D&p){return p.z*p.z+p.y*p.y+p.x*p.x;}
void AnimationSoundModuleManager::rva00433025(){
 const Coord3D *listener=((AnimationListenerCalls*)TheAudio)->listener();
 Coord3D delta;delta.x=listener->x;delta.y=listener->y;delta.z=listener->z;
 animationSubtract(delta,listenerPosition);
 if(animationSoundLengthSquared(delta)>TheAnimationSoundClientBehaviorGlobalSetting.m_minMicrophoneDistanceToDirty*TheAnimationSoundClientBehaviorGlobalSetting.m_minMicrophoneDistanceToDirty && dirtyTail){
  if(cleanHead){dirtyTail->next=cleanHead;cleanHead->previous=dirtyTail;}
  cleanHead=dirtyHead;
  if(!cleanTail)cleanTail=dirtyTail;
  dirtyHead=0;dirtyTail=0;
 }
 if(!dirtyHead)listenerPosition=*((AnimationListenerCalls*)TheAudio)->listener();
 for(AnimationSoundClientBehavior *b=cleanHead;b;){
  AnimationSoundClientBehavior *next=b->next;
  b->updateAnimationSounds();b=next;
 }
}
