// ?addOrResumeAudioEvent@MilesAudioManager@@QAEIPAVAudioEventRTS@@HHHH@Z
// partial score=0.96 date=2026-10-09
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
struct AudioEventInfo { char pad0[0x40]; int m_lastSubsoundIndex; unsigned m_priority,m_type,m_control;
 char pad50[0x3c]; unsigned m_totalSubsoundWeight; char pad90[0x20];int m_audioType;
 const _STL::vector<BfmeStringTailRecord156>&getSubsoundVector()const;
};
class AudioEventRTS { public:
 char pad0[8];AudioEventInfo *m_info;unsigned m_playingHandle;AudioEventRTS*m_multiSoundParent;int m_eventsBeforeReplay;
 char pad18[0x18];int m_viewType;char pad34[0x16];bool m_localOverride;
 char pad4B[7];bool m_immediate;char pad53[0x21];int m_nextPlayPortion;
 const AudioEventInfo*getAudioEventInfo()const{return m_info;}
 unsigned getSoundClass()const;void advanceNextPlayPortion();
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
class Rva00690FF0Handle:public Rva00691110Handle {public:
 __forceinline Rva00690FF0Handle(const Rva00690FF0Handle&x):Rva00691110Handle(x){}
 ~Rva00690FF0Handle();
 bool isReady()const{return target ? target->ready.check(0):false;}
 bool hasFailed()const{return target ? target->failed.check(0):false;}
};
struct Rva00051107AudioRequest {int kind;BfmePoolRef10 event;unsigned field08;Rva00690FF0Handle file;char tail10[8];};
class Image;
typedef _STL::map<unsigned,Image*> ResumeHandles;
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
 int addResumeOrPushMultisound(AudioEventRTS*,int,int,int,int,int);
 BfmePoolRef10 rva0005286A(AudioEventRTS*,int);
 int pushMusicEventInternal(AudioEventRTS*,int,int,int);
 unsigned addOrResumeAudioEvent(AudioEventRTS*,int,int,int,int);
 void mapLogicalHandleToPhysicalHandle(unsigned,unsigned);
 unsigned allocateNewHandle(){return m_nextHandle++;}
 unsigned rva0005933D(AudioEventRTS*,int);
 void rva000592B8(AudioEventRTS*);
 bool shouldPlayLocally(const AudioEventRTS*);
 bool addAudioEventMusic(BfmePoolRef10&,int,int);
 bool addAudioEventSound(BfmePoolRef10&,int,int);
 void processRequest(Rva00051107AudioRequest*,bool*);
 void deleteAudioRequest(void*);
 char pad04[0x98-4];_STL::list<Rva00051107AudioRequest*>requests;
 char pad9C[0xd0-0x9c];unsigned m_nextHandle;
 char padD4[0x698-0xd4];unsigned activeViews;
 char pad69C[0x9d4-0x69c];void*mutex;
 char pad9D8[0xa14-0x9d8];_STL::set<AsciiString>mutedNames[3];
 char padA38[0xb6c-0xa38];ResumeHandles resumeHandles;
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

// Native5D734..5DABB RET20; WB786F40 names addOrResumeAudioEvent.
// The new BFME2 request/handle flow is taken from its native and WB evidence;
// ZH's simpler AudioManager request path establishes the audio-event roles.
unsigned MilesAudioManager::addOrResumeAudioEvent(AudioEventRTS *event,int requestType,int resumeHandle,int allocateHandle,int append)
{
 MilesMutexGuard guard(&mutex,0);
 if(requestType==2)return 0;
 if(requestType==1 && (unsigned)resumeHandle>=5) {
  ResumeHandles::iterator previous=resumeHandles.find(reinterpret_cast<const unsigned&>(resumeHandle));
  if(previous!=resumeHandles.end())return reinterpret_cast<unsigned>(previous->second);
 }
 if(!event->m_info)return 1;
 if(!reinterpret_cast<Rva001D9A00*>(event->m_info)->rva001D9A00())return 1;
 if(mutedNames[event->m_viewType].count(reinterpret_cast<AudioInfoNames*>(event->m_info)->getAudioName()))return 1;
 if(event->m_info->m_audioType==5)return addResumeOrPushMultisound(event,requestType,resumeHandle,1,allocateHandle,append);
 if(event->m_info->m_audioType==3)return rva0005933D(event,allocateHandle);
 if(!slot56(event->getSoundClass()))return 1;
 if(event->m_info->m_audioType==1 && (activeViews&(1<<event->m_viewType)))return 1;
 BfmePoolRef10 playing=rva0005286A(event,allocateHandle);
 if(requestType==1) {
  if(!(unsigned char)reinterpret_cast<Rva001D98BD*>(multisoundTarget(playing)->m_info)->rva001D9781())return 4;
  if(multisoundTarget(playing)->m_nextPlayPortion==0)multisoundTarget(playing)->advanceNextPlayPortion();
  if((unsigned)resumeHandle>=5) {
   _STL::pair<ResumeHandles::iterator,bool> inserted=resumeHandles.insert(
    ResumeHandles::value_type(reinterpret_cast<const unsigned&>(resumeHandle),reinterpret_cast<Image*>(multisoundTarget(playing)->m_playingHandle)));
   if(!inserted.second)return reinterpret_cast<unsigned>(inserted.first->second);
  }
 }
 rva000592B8(multisoundTarget(playing));
 if(!multisoundTarget(playing)->m_localOverride && !shouldPlayLocally(multisoundTarget(playing)))return 3;
 if(multisoundTarget(playing)->m_info->m_control&0x20)reinterpret_cast<Weapon*>(multisoundTarget(playing))->setLeechRangeActive(true);
 bool added;
 if(event->m_info->m_audioType==0)added=addAudioEventMusic(playing,requestType,append);
 else added=addAudioEventSound(playing,requestType,append);
 if(!added)return 1;
 unsigned handle=multisoundTarget(playing)->m_playingHandle;
 if(multisoundTarget(playing)->m_immediate) {
  for(;;) {
   _STL::list<Rva00051107AudioRequest*>::reverse_iterator it=requests.rbegin();
   for(;it!=requests.rend();++it)
    if((*it)->kind==0 && multisoundTarget((*it)->event)==multisoundTarget(playing))break;
   if(it==requests.rend())break;
   bool remove=true;
   if((*it)->file.target) {
    Rva00690FF0Handle file((*it)->file);
    guard.rva00041055();
    while(!file.isReady() && !file.hasFailed())Sleep(1);
    guard.rva00041037(-1);
    continue;
   }
   processRequest(*it,&remove);
   if(remove) {
    Rva00051107AudioRequest *request=*it;
    _STL::list<Rva00051107AudioRequest*>::iterator node=it.base();
    --node;
    requests.erase(node);
    deleteAudioRequest(request);
   }
   break;
  }
 }
 return handle;
}
