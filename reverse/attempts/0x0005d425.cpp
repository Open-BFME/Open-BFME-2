// ?helper@Rva0005E13CHost@@QAE_NPBURva0005E13CInner1@@@Z
// partial score=0.97 date=2026-10-09
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <list>
#include <map>
#include <set>
#include <new>
#include "Common/BfmeAudioEventPrefix136.h"
// WorldBuilder786370 multisound identity; native5A451..5A7BE. Previous bank
// source guides control flow; canonical136B prefix and existing folded owners
// replace the previous bank's unlanded duplicate copy/setter names.
struct BfmePod144 { int a[36]; };
namespace _STL { template<> void vector<BfmePod144>::push_back(const BfmePod144&); }
struct Rva00050FA0 {
 Rva00050FA0(const BfmeAudioEventPrefix136&);
 __forceinline ~Rva00050FA0() {}
 __forceinline operator const BfmePod144&()const{return *reinterpret_cast<const BfmePod144*>(this);}
 BfmeAudioEventPrefix136 prefix;float zero88;unsigned char zero8C;char pad8D[3];
};
struct AudioEventInfo;
class Rva0036CA00Str { public:
 Rva0036CA00Str(const Rva0036CA00Str&);
 OpaqueRefCounted *m_ptr;
};
class AudioEventInfoRef : public Rva0036CA00Str { public:
 __forceinline AudioEventInfoRef(const AudioEventInfoRef &other) : Rva0036CA00Str(other) {}
 ~AudioEventInfoRef() { if(m_ptr) m_ptr->Release_Ref(); }
 AudioEventInfo *get()const{return reinterpret_cast<AudioEventInfo*>(m_ptr);}
};
struct OwnedAudioInfoCopy : Rva0036CA00Str {
 OwnedAudioInfoCopy(const Rva0036CA00Str &x):Rva0036CA00Str(x){}
 ~OwnedAudioInfoCopy(){m_ptr->Release_Ref();}
 OpaqueRefCounted*get()const{return m_ptr;}
};
class BfmeStringTailRecord156 {public: AudioEventInfoRef m_eventInfo;unsigned m_weight;};
struct AudioEventInfo { virtual ~AudioEventInfo();virtual int getNameKey()const;char pad04[0xc];float defaultPriority;char pad14[8];float defaultVolume;char pad20[0x20]; int m_lastSubsoundIndex; unsigned m_priority,m_type,m_control;
 char pad50[0x3c];unsigned m_totalSubsoundWeight;char pad90[8];float maxRange;char pad9C[0x14];int m_audioType;

 const _STL::vector<BfmeStringTailRecord156>&getSubsoundVector()const;
};
class AudioEventRTS { public:
 char pad0[8];AudioEventInfo *m_info;unsigned m_playingHandle;AudioEventRTS*m_multiSoundParent;int m_eventsBeforeReplay;
 char pad18[0x18];int m_viewType;char pad34[0x16];bool m_localOverride;
 bool m_loopRestart;char pad4C[3];bool m_startFlag;char pad50[2];bool m_immediate;char pad53[0x11];float m_delay;char pad68[0xc];int m_nextPlayPortion;
 const AudioEventInfo*getAudioEventInfo()const{return m_info;}
 unsigned getSoundClass()const;void advanceNextPlayPortion();bool hasMoreLoops()const;bool isPositionalAudio()const;
 __forceinline float getDelay()const{return m_delay;}void rva002D9ADC();
};
inline AudioEventRTS *multisoundTarget(const BfmePoolRef10& ref) {
 return *reinterpret_cast<AudioEventRTS*const*>(&ref);
}
class GameMessageList;
class GameMessage {public:void friend_setList(GameMessageList*);};
class MilesMutexGuard {public:MilesMutexGuard(void*,int);~MilesMutexGuard();bool rva00041055();bool rva00041037(int);void*mutex;bool held;};
class Rva001D9A00 {public:bool rva001D9A00();};
class Rva001D98BD {public:int rva001D9781();};
class AudioInfoNames {public:virtual ~AudioInfoNames();virtual const AsciiString&getAudioName()const;};
class Weapon {public:void setLeechRangeActive(bool);};
class FileStatus {public:virtual bool check(int);};
struct PendingAudioFile {char pad0[0x44];FileStatus ready;char pad48[4];FileStatus failed;};
class Rva00691110Handle {public:Rva00691110Handle(const Rva00691110Handle&);PendingAudioFile*target;};
class Rva00691040Handle {public:Rva00691040Handle&operator=(const Rva00691040Handle&);private:void*target;};
class Rva00690FF0Handle:public Rva00691110Handle {public:
 __forceinline Rva00690FF0Handle(const Rva00690FF0Handle&x):Rva00691110Handle(x){}
 ~Rva00690FF0Handle();
 __forceinline operator const Rva00691040Handle&()const{return *reinterpret_cast<const Rva00691040Handle*>(this);}
 bool isReady()const{return target ? target->ready.check(0):false;}
 bool hasFailed()const{return target ? target->failed.check(0):false;}
};
struct Rva00051107AudioRequest {int kind;BfmePoolRef10 event;unsigned field08;Rva00690FF0Handle file;bool flag10,flag11,flag12,flag13,flag14;char pad15[3];};
class Image;
typedef _STL::map<unsigned,Image*> ResumeHandles;
union Rva006AD590Slot {int m_asInt;float m_asFloat;};
class Rva006AD590Entry {public:Rva006AD590Slot*find(int);char opaque[0x1c4];};
class Rva003EF5DA {public:void rva003EF5DA(float);};
class View {public:virtual void setAngle(float);};
struct Rva0005E13CInner1;
class Rva0005E13CHost {public:bool helper(const Rva0005E13CInner1*);};
class Rva002D9BDC {public:void rva002D9BDC(float,float);};
class AudioFileCache {public:Rva00690FF0Handle requestFile(const BfmePoolRef10&,int);};
struct AudioSettings {char pad0[0x74];int globalRange;char pad78[0x3c];int cacheThreshold;};
extern float g_00DBA4FC;extern float g_Va00BBDA30;
class MilesAudioManager {public:
 virtual ~MilesAudioManager();
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
 virtual bool slot56(unsigned soundClass);
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
 virtual const BfmeEventPositionView*slot72();
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
 virtual void slot85();
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
 virtual bool slot108(AudioEventRTS*);
 int addResumeOrPushMultisound(AudioEventRTS*,int,int,int,int,int);
 BfmePoolRef10 rva0005286A(AudioEventRTS*,int);
 int pushMusicEventInternal(AudioEventRTS*,int,int,int);
 unsigned addOrResumeAudioEvent(AudioEventRTS*,int,int,int,int);
 void mapLogicalHandleToPhysicalHandle(unsigned,unsigned);
 unsigned allocateNewHandle(){return m_nextHandle++;}
 unsigned rva0005933D(AudioEventRTS*,int);
 void rva000592B8(AudioEventRTS*);
 bool shouldPlayLocally(const AudioEventRTS*);
 int rva00052F1E(void*);bool rva000570C8(AudioEventRTS*);bool rva000575CE(AudioEventRTS*);bool isPlayingLowerPriority(AudioEventRTS*);bool rva00054839(AudioEventRTS*);
 bool addAudioEventMusic(BfmePoolRef10&,int,int);
 bool addAudioEventSound(BfmePoolRef10&,int,int);
 void processRequest(Rva00051107AudioRequest*,bool*);
 void deleteAudioRequest(void*);
 Rva00051107AudioRequest*rva00051107();
 char pad04[0xc];AudioSettings*settings;char pad14[0x98-0x14];_STL::list<Rva00051107AudioRequest*>requests;
 char pad9C[0xd0-0x9c];unsigned m_nextHandle;
 char padD4[0xc];_STL::vector<BfmePod144> m_queued[3];char pad104[0x28];Rva006AD590Entry m_priority[3];char pad678[4];unsigned sampleLimit2D,sampleLimit3D,sampleCount2D,sampleCount3D;char pad68C[0xc];unsigned activeViews;
 char pad69C[0x18];unsigned flags6B4[3],flags6C0[3];char pad6CC[0x9d4-0x6cc];void*mutex;
 char pad9D8[0xa14-0x9d8];_STL::set<AsciiString>mutedNames[3];
 char padA38[0xb6c-0xa38];ResumeHandles resumeHandles;char padB78[0x14];AudioFileCache*fileCache;
};
class Rva002D9C2F {public:OpaqueRefElement4&rva002D9C2F(const OpaqueRefElement4&);};
class Rva002D9AD4 {public:BfmePoolRef10&rva002D9AD4(const BfmePoolRef10&);};
int GetGameAudioRandomValue(int,int,char*,int);
#define MILES_AUDIO_MANAGER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\MilesAudioDevice\\MilesAudioManager.cpp"

int MilesAudioManager::addResumeOrPushMultisound(AudioEventRTS *event, int requestType, int arg2, int arg3, int allocateHandle, int arg5)
{
    OwnedAudioInfoCopy infoRef(*reinterpret_cast<const Rva0036CA00Str *>(&event->m_info));
    AudioEventInfo *info = reinterpret_cast<AudioEventInfo *>(infoRef.get());
    BfmePoolRef10 multiSound;
    if (info->m_control & 1)
        multiSound = rva0005286A(event, allocateHandle);
    if (reinterpret_cast<AudioEventInfo *>(infoRef.get())->m_control & 0x80) {
        const _STL::vector<BfmeStringTailRecord156> &subs = reinterpret_cast<AudioEventInfo *>(infoRef.get())->getSubsoundVector();
        int index;
        if (subs.size() <= 1) {
            index = 0;
        } else {
            do {
                unsigned int pick = GetGameAudioRandomValue(0, reinterpret_cast<AudioEventInfo *>(infoRef.get())->m_totalSubsoundWeight - 1, MILES_AUDIO_MANAGER_FILE, 3761);
                _STL::vector<BfmeStringTailRecord156>::const_iterator it = subs.begin();
                _STL::vector<BfmeStringTailRecord156>::const_iterator end = subs.end();
                while (it != end && pick >= it->m_weight) {
                    pick -= it->m_weight;
                    ++it;
                }
                if (it == end)
                    return 0;
                index = it - subs.begin();
            } while (index == event->getAudioEventInfo()->m_lastSubsoundIndex);
        }
        reinterpret_cast<AudioEventInfo *>(infoRef.get())->m_lastSubsoundIndex = index;
        if (index < 0 || (unsigned int)index >= subs.size())
            return 1;
        AudioEventInfoRef sub(subs[index].m_eventInfo);
        if (sub.get() == 0)
            return 1;
        BfmeAudioEventPrefix136 copy(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(event));
        ((Rva002D9C2F *)&copy)->rva002D9C2F(*reinterpret_cast<const OpaqueRefElement4 *>(&sub));
        if (multisoundTarget(multiSound)) {
            ((Rva002D9AD4 *)&copy)->rva002D9AD4(multiSound);
            multisoundTarget(multiSound)->m_eventsBeforeReplay++;
            copy.m_int7C = 1;
        }
        unsigned int result;
        if (requestType == 2)
            result = pushMusicEventInternal(reinterpret_cast<AudioEventRTS *>(&copy), arg3, allocateHandle, arg5);
        else
            result = addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>(&copy), requestType, arg2, allocateHandle, arg5);
        if (multisoundTarget(multiSound) && result >= 5)
            reinterpret_cast<GameMessage *>(multisoundTarget(multiSound))->friend_setList(reinterpret_cast<GameMessageList *>(result));
        return result;
    } else {
        unsigned int handle;
        if (multisoundTarget(multiSound))
            handle = multisoundTarget(multiSound)->m_playingHandle;
        else if (allocateHandle == 1)
            handle = event->m_playingHandle;
        else
            handle = allocateNewHandle();
        if (!multisoundTarget(multiSound)) {
            AudioEventRTS *parent = event->m_multiSoundParent;
            if (parent)
                parent->m_eventsBeforeReplay--;
        }
        const _STL::vector<BfmeStringTailRecord156> &subs = event->getAudioEventInfo()->getSubsoundVector();
        _STL::vector<BfmeStringTailRecord156>::const_iterator it = subs.begin();
        _STL::vector<BfmeStringTailRecord156>::const_iterator end = subs.end();
        bool played = false;
        unsigned int result = 1;
        for (; it != end; ++it) {
            if (it->m_eventInfo.get() == 0)
                continue;
            BfmeAudioEventPrefix136 copy(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(event));
            ((Rva002D9C2F *)&copy)->rva002D9C2F(*reinterpret_cast<const OpaqueRefElement4 *>(&it->m_eventInfo));
            if (multisoundTarget(multiSound))
                ((Rva002D9AD4 *)&copy)->rva002D9AD4(multiSound);
            if (multisoundTarget(copy.m_pool10))
                copy.m_int7C = 1;
            unsigned int r;
            if (requestType == 2)
                r = pushMusicEventInternal(reinterpret_cast<AudioEventRTS *>(&copy), arg3, 0, arg5);
            else
                r = addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>(&copy), requestType, 1, 0, arg5);
            if (r >= 5) {
                if (multisoundTarget(copy.m_pool10))
                    multisoundTarget(copy.m_pool10)->m_eventsBeforeReplay++;
                played = true;
                mapLogicalHandleToPhysicalHandle(handle, r);
            } else {
                result = r;
            }
        }
        if (played)
            return handle;
        return result;
    }
}

// Native5933D..593CD; WB785B80 queues a copied event wrapper as an ambient
// stream marker. Original method name remains unknown.
unsigned MilesAudioManager::rva0005933D(AudioEventRTS *event,int allocateHandle)
{
 int view=event->m_viewType;
 m_queued[view].push_back(Rva00050FA0(*reinterpret_cast<const BfmeAudioEventPrefix136*>(event)));
 AudioEventRTS *queued=reinterpret_cast<AudioEventRTS*>(&m_queued[view].back());
 rva000592B8(queued);
 if(allocateHandle==0)
  reinterpret_cast<GameMessage*>(queued)->friend_setList(reinterpret_cast<GameMessageList*>(allocateNewHandle()));
 return queued->m_playingHandle;
}

// Native592B8..5933D RET4; WB785A70 priority/volume override lookup. The
// BFME1 AudioManagerAdjustPriorityAndVolume donor establishes the subsystem;
// native view30, table12C and info defaults10/1C establish BFME2 offsets.
void MilesAudioManager::rva000592B8(AudioEventRTS*event)
{
 int view=event->m_viewType;
 int key=event->m_info->getNameKey();
 Rva006AD590Slot *slot=m_priority[view].find(key);
 if(slot) {
  reinterpret_cast<Rva003EF5DA*>(event)->rva003EF5DA(slot->m_asFloat);
  AudioEventInfo *info=event->m_info;
  float priority=info->defaultPriority;
  if(priority>0.0f) {
   float ratio=slot->m_asFloat/priority;
   float volume=ratio*info->defaultVolume;
   reinterpret_cast<View*>(event)->View::setAngle(volume);
  }
 }else {
  reinterpret_cast<Rva003EF5DA*>(event)->rva003EF5DA(event->m_info->defaultPriority);
  reinterpret_cast<View*>(event)->View::setAngle(event->m_info->defaultVolume);
 }
}

// WB785260 names addAudioEventSound; native5D57B..5D734 RET12. Target
// request layout and loops/delay/cache flows extend the ZH audio-request lead.
bool MilesAudioManager::addAudioEventSound(BfmePoolRef10&event,int requestType,int append)
{
 if(requestType==2)return false;
 bool available=reinterpret_cast<Rva0005E13CHost*>(this)->helper(reinterpret_cast<const Rva0005E13CInner1*>(multisoundTarget(event)));
 if(!available) {
  float firstDelay=multisoundTarget(event)->getDelay();
  if(firstDelay<g_00DBA4FC && multisoundTarget(event)->hasMoreLoops()) {
   multisoundTarget(event)->rva002D9ADC();
   if(multisoundTarget(event)->hasMoreLoops()) {
    multisoundTarget(event)->advanceNextPlayPortion();
    multisoundTarget(event)->m_loopRestart=true;
    reinterpret_cast<Rva002D9BDC*>(multisoundTarget(event))->rva002D9BDC(g_00DBA4FC+1.0f,g_Va00BBDA30);
   }
  }
  float secondDelay=multisoundTarget(event)->getDelay();
  if(!(secondDelay>=g_00DBA4FC) && !multisoundTarget(event)->hasMoreLoops())return false;
 }
 Rva00051107AudioRequest*request=rva00051107();
 request->event=event;
 request->kind=0;
 if(requestType==1) {
  multisoundTarget(request->event)->m_startFlag=false;
  request->flag14=true;
 }
 unsigned affect=multisoundTarget(event)->getSoundClass();
 if(flags6B4[multisoundTarget(event)->m_viewType]&affect)request->flag12=true;
 if(flags6C0[multisoundTarget(event)->m_viewType]&affect)request->flag13=true;
 if(multisoundTarget(event)->m_info->m_audioType==2 && available) {
  if(multisoundTarget(event)->getDelay()<settings->cacheThreshold) {
  int priority=!(multisoundTarget(event)->getDelay()>=g_00DBA4FC);
  if(multisoundTarget(event)->m_immediate && multisoundTarget(event)->getDelay()<g_00DBA4FC)priority=2;
  reinterpret_cast<Rva00691040Handle*>(&request->file)->operator=(fileCache->requestFile(event,priority));
 }
 }
 if(!append)requests.push_front(request);else requests.push_back(request);
 return true;
}

// Native5D425..5D57B RET4 and WB7849D0 implement the audio event admission
// helper already called by the rowed5E13C request gate. Original name unknown.
bool Rva0005E13CHost::helper(const Rva0005E13CInner1*input)
{
 MilesAudioManager *manager=reinterpret_cast<MilesAudioManager*>(this);
 AudioEventRTS*event=reinterpret_cast<AudioEventRTS*>(const_cast<Rva0005E13CInner1*>(input));
 if(event->isPositionalAudio() && !(unsigned char)manager->rva00052F1E(event)) {
  bool valid;
  BfmeEventPositionView position=reinterpret_cast<BfmeAudioEventPrefix136*>(event)->rva002DA1CC(valid);
  BfmeEventPositionView distance=*manager->slot72();
  if(!valid)return false;
  distance.x-=position.x;distance.y-=position.y;distance.z-=position.z;
  float range;
  if(event->m_info->m_type&8)range=(float)manager->settings->globalRange;
  else range=event->m_info->maxRange;
  if(distance.x*distance.x+distance.y*distance.y+distance.z*distance.z>=range*range)return false;
  if(manager->slot108(event)){event->m_startFlag=true;return false;}
 }
 if(manager->rva000570C8(event))return (static_cast<unsigned char>(event->m_info->m_control>>3)&1)!=0;
 if(manager->rva000575CE(event))return false;
 if(!(event->m_info->m_control&8) && event->m_info->m_audioType==2) {
  if(event->isPositionalAudio()) {
   if(manager->sampleCount3D<manager->sampleLimit3D)return true;
  }else {
   if(manager->sampleCount2D<manager->sampleLimit2D)return true;
  }
  if(!manager->isPlayingLowerPriority(event)) {
   if(event->m_info->m_control&8)return manager->rva00054839(event)?true:false;
   return false;
  }
 }
 return true;
}
