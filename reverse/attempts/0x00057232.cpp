// ?processPopMusicRequest@MilesAudioManager@@QAEXAAURva00051107AudioRequest@@@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

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

class AudioEventRTS {
public:
    unsigned int getSoundClass(void) const;
    bool hasMoreLoops(void) const;
    void rva002D9ADC(void);
    char at00[0x30];
    int m_viewType;          // +0x30
    unsigned char rva000CB12F(void) const;
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

struct PlayingAudio {
    void *vfptr;
    long refs;
    int m_handle;                        // +0x08 loop-buffer / handle-state index
    char at0C[0x14 - 0x0C];
    int m_type;                          // +0x14
    int m_status;                        // +0x18
    BfmePoolRef10 m_event;            // +0x1C
    Rva000A8A6C m_file;                  // +0x20
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
    char at01;
    bool m_is3D;                         // +0x02 selects the handle below
    char at03;
    void *m_3DSample;                    // +0x04
    void *m_sample;                      // +0x08
    char at0C[0x14 - 0x0C];
    PlayingAudio *m_playingAudio;        // +0x14
    char at18[0x48 - 0x18];
};

class MilesAudioManager {
public:
    void removeCurrentlyPlayingMusic(int viewType, int arg);
    void rva00057151(int viewType, int musicSystem, int resume);
    void moveDownMusicSystems(int viewType, MusicSystem newMusicSystem, int arg, int resume);
    void processPopMusicRequest(Rva00051107AudioRequest &request);
    bool addAudioEventMusic(BfmePoolRef10 &event, int requestType, int append);
    Rva00051107AudioRequest *rva00051107(void);
    void onPlayingAudioDeleted(PlayingAudio &playingAudioBeingDeleted);
    void releaseMilesHandles(PlayingAudio &playing);
    void moveUpMusicSystems(int newMusicSystem, int viewType, int arg);
    bool startNextLoop(PlayingAudioRef &looping);
    void getAppropriateSampleHandleForPlayingAudio(PlayingAudioRef &playing, void **sample, void **sample3D);

    void putPlayingMusicOnStack(int viewType, int arg);
    void rva00059CE6(PlayingAudioRef &looping);

private:
    char at00[0x98];
    Rva00051107AudioRequestList m_audioRequests;    // +0x98
    char at9C[0x6B4 - 0x9C];
    unsigned int m_at6B4[3];             // +0x6B4 per-view-type affect masks
    unsigned int m_at6C0[3];             // +0x6C0
    char at6CC[0x9D4 - 0x6CC];
    void *m_mutex;                       // +0x9D4
    char at9D8[0xA4C - 0x9D8];
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

void MilesAudioManager::processPopMusicRequest(Rva00051107AudioRequest &request)
{
    int viewType = request.m_pendingEvent->m_viewType;
    MusicSystem musicSystem = request.m_pendingEvent->m_musicSystem;
    if (m_activeMusicSystem[viewType] == musicSystem) {
        removeCurrentlyPlayingMusic(viewType, !request.m_at10);
        rva00057151(viewType, musicSystem, !request.m_pendingEvent->rva000CB12F());
    } else if (!m_musicStack[viewType][musicSystem].empty()) {
        m_musicStack[viewType][musicSystem].pop_back();
    }
}
