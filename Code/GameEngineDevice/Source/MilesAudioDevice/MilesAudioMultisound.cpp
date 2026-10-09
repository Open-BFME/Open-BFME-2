// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
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
 char pad50[0x3c]; unsigned m_totalSubsoundWeight;
 const _STL::vector<BfmeStringTailRecord156>&getSubsoundVector()const;
};
class AudioEventRTS { public:
 char pad0[8];AudioEventInfo *m_info;unsigned m_playingHandle;AudioEventRTS*m_multiSoundParent;int m_eventsBeforeReplay;char pad18[0x18];int m_viewType;
 const AudioEventInfo*getAudioEventInfo()const{return m_info;}
};
inline AudioEventRTS *multisoundTarget(const BfmePoolRef10& ref) {
 return *reinterpret_cast<AudioEventRTS*const*>(&ref);
}
class GameMessageList;
class GameMessage {public:void friend_setList(GameMessageList*);};
union Rva006AD590Slot {int m_asInt;float m_asFloat;};
class Rva006AD590Entry {public:Rva006AD590Slot*find(int);char opaque[0x1c4];};
class Rva003EF5DA {public:void rva003EF5DA(float);};
class View {public:virtual void setAngle(float);};
class MilesAudioManager {public:
 int addResumeOrPushMultisound(AudioEventRTS*,int,int,int,int,int);
 BfmePoolRef10 rva0005286A(AudioEventRTS*,int);
 int pushMusicEventInternal(AudioEventRTS*,int,int,int);
 unsigned addOrResumeAudioEvent(AudioEventRTS*,int,int,int,int);
 void mapLogicalHandleToPhysicalHandle(unsigned,unsigned);
 unsigned rva0005933D(AudioEventRTS*,int);
 void rva000592B8(AudioEventRTS*);
 unsigned allocateNewHandle(){return m_nextHandle++;}
 char pad0[0xd0];unsigned m_nextHandle;char padD4[0xc];_STL::vector<BfmePod144> m_queued[3];char pad104[0x28];Rva006AD590Entry m_priority[3];
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
