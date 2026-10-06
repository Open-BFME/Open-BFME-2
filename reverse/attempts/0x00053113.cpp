// ?pauseResumeSound@MilesAudioManager@@QAEXAAVPlayingAudioRef@@@Z
// partial score=0.6 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// MilesAudioManager members recovered from WorldBuilder leads.
// Identity: WorldBuilder's debug build names each body (its assert text and
// line numbers sit in MilesAudioManager.cpp) and its call graph maps onto
// these retail addresses (score/evidence in each row's notes). Zero Hour's
// MilesAudioManager.cpp has no music-system stack; BFME 2's is new code.
// Target-measured layout (retail immediates, cross-checked by WB asserts):
// music stacks: deque[viewType][musicSystem] at +0xA4C (0x28 each, 2 per
// view type), m_activeMusicSystem[viewType] at +0xB3C (WB assert names it).
// PlayingAudio (owning ref, refcount object): type +0x14, file holder +0x20,
// event +0x1C. Field names other than WB-asserted ones are descriptive.
// Callees still under address-derived ledger names are reached through
// alias pins in reverse/symbols.csv.
#include <deque>
#include <list>
#include <set>
#include <vector>
#include "ascii_string.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) unsigned int __stdcall AIL_sample_status(void *sample);
extern "C" __declspec(dllimport) unsigned int __stdcall AIL_3D_sample_status(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_3D_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_resume_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_resume_3D_sample(void *sample);

class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    void Add_Ref() { InterlockedIncrement(&refs); }
    void Release_Ref();
private:
    long refs;
};

struct OpaqueRefElement4 {
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};

typedef _STL::deque<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> > MusicStack;

enum MusicSystem { MUSIC_SYSTEM_0, MUSIC_SYSTEM_1 };
inline MusicSystem &operator--(MusicSystem &ms, int) { ms = (MusicSystem)(ms - 1); return ms; }

// AudioEventInfo view: +0x44 is the priority the lowest-priority scan ranks by.
struct AudioEventInfo {
    char at00[0x44];
    int m_priority;                          // +0x44
};

class AudioEventRTS {
public:
    bool isPositionalAudio(void) const;
    unsigned int getSoundClass(void) const;
    bool hasMoreLoops(void) const;
    void rva002D9ADC(void);
    char at00[0x08];
    AudioEventInfo *m_info;  // +0x08 (owning ref in WB)
    char at0C[0x30 - 0x0C];
    int m_viewType;          // +0x30
    char at34[0x78 - 0x34];
    MusicSystem m_musicSystem; // +0x78
};

// Owning AudioEventRTS reference (its refcount base sits at event +0x88);
// the ledger's established name, assignment rowed at 0x00051971.
class BfmePoolRef10 {
public:
    AudioEventRTS *operator->(void) const { return m_ptr; }
    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
private:
    AudioEventRTS *m_ptr;
};

// Release-then-null holder at PlayingAudio +0x20 (ledger 0x000A8A6C).
class Rva000A8A6C {
public:
    void rva000A8A6C(void);
private:
    void *m_ptr;
};

// Stream holder at PlayingAudio +0x0C; its two forwards are rowed at
// 0x000A8AC0 and 0x000A8ACC.
class MilesStreamRef {
public:
    void rva000A8AC0(void);
    void rva000A8ACC(void);
private:
    void *m_object;
};

struct PlayingAudio {
    bool rva00050D6C(void) const;        // pause-request test (0x00050D6C)
    void *vfptr;
    long refs;
    int m_handle;                        // +0x08 loop-buffer / handle-state index
    MilesStreamRef m_stream;             // +0x0C
    char at10[0x14 - 0x10];
    int m_type;                          // +0x14
    int m_status;                        // +0x18
    BfmePoolRef10 m_event;               // +0x1C
    Rva000A8A6C m_file;                  // +0x20
    char at24[0x49 - 0x24];
    bool m_at49;
    bool m_at4A;
    bool m_at4B;
    bool m_at4C;
};

class PlayingAudioRef {
public:
    PlayingAudio *operator->(void) const { return m_ptr; }
private:
    PlayingAudio *m_ptr;
};

// 0x18-byte request record (operator new(0x18) in its allocator 0x00051107);
// Zero Hour's AudioRequest plays this role, the name stays address-derived.
struct Rva00051107AudioRequest {
    int m_request;
    BfmePoolRef10 m_pendingEvent;         // +0x04
    char at08[0x10 - 0x08];
    bool m_at10;                             // +0x10
    bool m_at11;
    bool m_at12;
    bool m_at13;
    bool m_at14;
    char at15[0x18 - 0x15];
};

typedef _STL::list<Rva00051107AudioRequest *> Rva00051107AudioRequestList;

class MilesMutexGuard {
public:
    MilesMutexGuard(void *mutex, int defer);
    ~MilesMutexGuard();
private:
    void *m_mutex;
    bool m_held;
};

// 72-byte retail record (WB's debug record is 84 bytes); +0x14 named by the
// WB assert in onPlayingAudioDeleted.
struct LoopBuffer {
    bool m_isValid;                      // +0x00 (WB assert name)
    bool m_at01;
    bool m_is3D;                         // +0x02 selects the handle below
    char at03;
    void *m_3DSample;                    // +0x04
    void *m_sample;                      // +0x08
    char at0C[0x14 - 0x0C];
    PlayingAudio *m_playingAudio;        // +0x14
    char at18[0x48 - 0x18];
};

// TheGameLODManager (0x00DFE144): +0x1770 audio LOD level, per-level
// 8-byte settings at +0x218 whose first word is the ambient stream cap.
struct AudioLODSettings {
    unsigned short m_maxAmbientStreams;
    char at02[6];
};

class GameLODManager {
public:
    char at0000[0x218];
    AudioLODSettings m_audioLODSettings[2];  // +0x218
    char at0228[0x1770 - 0x228];
    int m_audioLOD;                          // +0x1770
};

extern GameLODManager *TheGameLODManager;

// 8-byte vector element whose +4 is compared against the view focus.
struct BfmePod8 {
    int m_at00;
    int m_viewType;
};

// Tree-like member at GlobalVolumeData +0x1B8; its clear is rowed at
// 0x00057B74 under this address-derived name.
class Rva00056CF8 {
public:
    void rva00057B74(void);
private:
    char opaque[0x10];
};

// {priority, volume} ranking key and its free less (rowed at 0x000515E4).
struct Rva000515E4Key {
    int a;
    float b;
};

bool __cdecl Rva000515E4Less(const Rva000515E4Key *x, const Rva000515E4Key *y);

typedef _STL::list<PlayingAudioRef> PlayingAudioList;

class MilesAudioManager {
public:
    AudioEventRTS *findLowestPrioritySound(AudioEventRTS *event);
    float rva0005A9F8(void *ref, int a, int b);
    float rva00059AD0(void *event, int a);
    // Ledger class Rva00699180Owner (refreshAll/rva00052048 share its this).
    class GlobalVolumeData {
    public:
        void reset(void);
        void rva00052048(int index);
        void refreshAll(void);

        int m_myViewFocus;                         // +0x00 (WB assert name)
        float m_volumes[6][2];                     // +0x04
        float m_product[6];                        // +0x34
        _STL::vector<BfmePod8> m_requests[6];      // +0x4C
        float m_at94;                              // +0x94
        float m_at98;
        float m_at9C;                              // +0x9C
        _STL::set<AsciiString> m_names;            // +0xA0
        char atAC[0xC4 - 0xAC];
        bool m_atC4;                               // +0xC4
        char atC5[0x1B8 - 0xC5];
        Rva00056CF8 m_at1B8;                       // +0x1B8
    };

    void setMaxAmbientStreams(void);
    void removeCurrentlyPlayingMusic(int viewType, int arg);
    void rva00057151(int viewType, int musicSystem, int resume);
    void moveDownMusicSystems(int viewType, MusicSystem newMusicSystem, int arg, int resume);
    bool addAudioEventMusic(BfmePoolRef10 &event, int requestType, int append);
    Rva00051107AudioRequest *rva00051107(void);
    void onPlayingAudioDeleted(PlayingAudio &playingAudioBeingDeleted);
    void releaseMilesHandles(PlayingAudio &playing);
    void moveUpMusicSystems(int newMusicSystem, int viewType, int arg);
    bool startNextLoop(PlayingAudioRef &looping);
    void getAppropriateSampleHandleForPlayingAudio(PlayingAudioRef &playing, void **sample, void **sample3D);
    void pauseResumeSound(PlayingAudioRef &playing);

    void putPlayingMusicOnStack(int viewType, int arg);
    void rva00059CE6(PlayingAudioRef &looping);

private:
    char at00[0x98];
    Rva00051107AudioRequestList m_audioRequests;    // +0x98
    char at9C[0x69C - 0x9C];
    unsigned short m_maxAmbientStreams;  // +0x69C
    char at69E[0x6B4 - 0x69E];
    unsigned int m_at6B4[3];             // +0x6B4 per-view-type affect masks
    unsigned int m_at6C0[3];             // +0x6C0
    char at6CC[0x9D4 - 0x6CC];
    void *m_mutex;                       // +0x9D4
    char at9D8[0xA40 - 0x9D8];
    PlayingAudioList m_playingSounds;    // +0xA40
    PlayingAudioList m_playing3DSounds;  // +0xA44
    PlayingAudioList m_playingStreams;   // +0xA48
    MusicStack m_musicStack[3][2];       // +0xA4C
    MusicSystem m_activeMusicSystem[3];  // +0xB3C
    char atB48[0xBD4 - 0xB48];
    LoopBuffer *m_loopBuffers;           // +0xBD4 (WB assert name)
};

void MilesAudioManager::moveUpMusicSystems(int newMusicSystem, int viewType, int arg)
{
    putPlayingMusicOnStack(viewType, arg);
    m_activeMusicSystem[viewType] = (MusicSystem)newMusicSystem;
}

bool MilesAudioManager::startNextLoop(PlayingAudioRef &looping)
{
    if (looping->m_type == 3 || looping->m_type == 1)
        return false;
    looping->m_file.rva000A8A6C();
    if (looping->m_event->hasMoreLoops()) {
        looping->m_event->rva002D9ADC();
        rva00059CE6(looping);
        return true;
    }
    return false;
}

void MilesAudioManager::onPlayingAudioDeleted(PlayingAudio &playingAudioBeingDeleted)
{
    MilesMutexGuard guard(&m_mutex, 0);
    releaseMilesHandles(playingAudioBeingDeleted);
    if (playingAudioBeingDeleted.m_type == 3 || playingAudioBeingDeleted.m_type == 1) {
        LoopBuffer &buffer = m_loopBuffers[playingAudioBeingDeleted.m_handle];
        buffer.m_playingAudio = 0;
    }
}

bool MilesAudioManager::addAudioEventMusic(BfmePoolRef10 &event, int requestType, int append)
{
    if (requestType == 2)
        return false;
    Rva00051107AudioRequest *request = rva00051107();
    request->m_pendingEvent = event;
    request->m_request = 0;
    if (requestType == 1)
        request->m_at14 = true;
    unsigned int affect = event->getSoundClass();
    if (m_at6B4[event->m_viewType] & affect)
        request->m_at12 = true;
    if (m_at6C0[event->m_viewType] & affect)
        request->m_at13 = true;
    if (!append)
        m_audioRequests.push_front(request);
    else
        m_audioRequests.push_back(request);
    return true;
}

void MilesAudioManager::getAppropriateSampleHandleForPlayingAudio(PlayingAudioRef &playing, void **sample, void **sample3D)
{
    switch (playing->m_type) {
    case 0:
        *sample3D = 0;
        *sample = (void *)playing->m_handle;
        break;
    case 1:
        *sample3D = 0;
        if (!m_loopBuffers[playing->m_handle].m_is3D)
            *sample = m_loopBuffers[playing->m_handle].m_sample;
        else
            *sample = 0;
        break;
    case 2:
        *sample = 0;
        *sample3D = (void *)playing->m_handle;
        break;
    case 3:
        *sample = 0;
        if (m_loopBuffers[playing->m_handle].m_is3D)
            *sample3D = m_loopBuffers[playing->m_handle].m_3DSample;
        else
            *sample3D = 0;
        break;
    case 4:
        *sample3D = 0;
        *sample = 0;
        break;
    case 5:
        *sample3D = 0;
        *sample = 0;
        break;
    default:
        *sample3D = 0;
        *sample = 0;
        break;
    }
}

void MilesAudioManager::moveDownMusicSystems(int viewType, MusicSystem newMusicSystem, int arg, int resume)
{
    removeCurrentlyPlayingMusic(viewType, arg);
    while (newMusicSystem < m_activeMusicSystem[viewType]) {
        m_musicStack[viewType][m_activeMusicSystem[viewType]].clear();
        m_activeMusicSystem[viewType]--;
    }
    if (!m_musicStack[viewType][newMusicSystem].empty())
        rva00057151(viewType, newMusicSystem, resume);
}


void MilesAudioManager::setMaxAmbientStreams(void)
{
    if (TheGameLODManager == 0) {
        m_maxAmbientStreams = 2;
        return;
    }
    int audioLOD = TheGameLODManager->m_audioLOD;
    if (audioLOD < 0 || audioLOD >= 2) {
        m_maxAmbientStreams = 2;
    } else {
        m_maxAmbientStreams = TheGameLODManager->m_audioLODSettings[audioLOD].m_maxAmbientStreams;
        if (m_maxAmbientStreams > 2)
            m_maxAmbientStreams = 2;
    }
}

void MilesAudioManager::GlobalVolumeData::reset(void)
{
    m_at1B8.rva00057B74();
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 2; ++j)
            m_volumes[i][j] = 1.0f;
    m_at94 = 1.0f;
    m_at9C = 1.0f;
    m_atC4 = false;
    m_names.clear();
    for (int viewType = 0; viewType < 6; ++viewType) {
        bool removed = false;
        _STL::vector<BfmePod8>::iterator it = m_requests[viewType].begin();
        while (it != m_requests[viewType].end()) {
            if (it->m_viewType == m_myViewFocus) {
                it = m_requests[viewType].erase(it);
                removed = true;
            } else {
                ++it;
            }
        }
        if (removed)
            rva00052048(viewType);
    }
    refreshAll();
}

AudioEventRTS *MilesAudioManager::findLowestPrioritySound(AudioEventRTS *event)
{
    AudioEventRTS *lowestEvent = 0;
    Rva000515E4Key lowest = { event->m_info->m_priority, rva00059AD0(event, 1) };
    PlayingAudioList *list = event->isPositionalAudio() ? &m_playing3DSounds : &m_playingSounds;
    for (PlayingAudioList::iterator it = list->begin(); it != list->end(); ++it) {
        AudioEventRTS *playingEvent = (*it)->m_event.operator->();
        Rva000515E4Key key = { playingEvent->m_info->m_priority, rva0005A9F8(&*it, 1, 1) };
        if (Rva000515E4Less(&key, &lowest)) {
            lowestEvent = playingEvent;
            lowest = key;
        }
    }
    return lowestEvent;
}

bool __cdecl Rva000515E4Less(const Rva000515E4Key *x, const Rva000515E4Key *y)
{
    if (x->a < y->a)
        return true;
    if (x->a > y->a)
        return false;
    return y->b > x->b;
}

bool PlayingAudio::rva00050D6C(void) const
{
    return m_at49 || m_at4A || m_at4B || m_at4C;
}

void MilesAudioManager::pauseResumeSound(PlayingAudioRef &playing)
{
    if (playing->m_type == 4) {
        if (playing->rva00050D6C())
            playing->m_stream.rva000A8AC0();
        else
            playing->m_stream.rva000A8ACC();
        return;
    }
    void *sample2DHandle;
    void *sample3DHandle;
    getAppropriateSampleHandleForPlayingAudio(playing, &sample2DHandle, &sample3DHandle);
    if (sample2DHandle == 0 && sample3DHandle == 0)
        return;
    unsigned int status;
    if (sample2DHandle == 0)
        status = AIL_3D_sample_status(sample3DHandle);
    else
        status = AIL_sample_status(sample2DHandle);
    if (playing->rva00050D6C()) {
        if (status != 2) {
            if (sample2DHandle == 0)
                AIL_stop_3D_sample(sample3DHandle);
            else
                AIL_stop_sample(sample2DHandle);
        }
    } else if (status == 8) {
        if (playing->m_type == 3 || playing->m_type == 1) {
            LoopBuffer &buffer = m_loopBuffers[playing->m_handle];
            if (buffer.m_at01)
                return;
        }
        if (sample2DHandle == 0)
            AIL_resume_3D_sample(sample3DHandle);
        else
            AIL_resume_sample(sample2DHandle);
    }
}
