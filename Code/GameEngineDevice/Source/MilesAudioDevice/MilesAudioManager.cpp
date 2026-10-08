// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <set>
#include <vector>
#include "ascii_string.h"

class Xfer;
enum INILoadType
{
    INI_LOAD_INVALID,
    INI_LOAD_OVERWRITE,
    INI_LOAD_CREATE_OVERRIDES,
    INI_LOAD_MULTIFILE
};

class Rva00601BBCHelper
{
public:
    Rva00601BBCHelper();
    virtual ~Rva00601BBCHelper();

private:
    char m_body[0x30];
};

// INI object view copied from INI_ctor.cpp so this local has the measured
// 0x888-byte extent. Offset +8 is kept address-derived: 0x54120 reads it and
// passes it as the load type, but its semantic field name is not settled here.
class INI
{
public:
    INI();
    ~INI();
    unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);

private:
    void *m_file;
    AsciiString m_filename;

public:
    unsigned int m_at08;

private:
    unsigned int m_readBufferUsed;
    unsigned int m_lineNum;
    char m_buffer[0x418 - 0x14];
    const char *m_seps;
    const char *m_sepsPercent;
    const char *m_sepsColon;
    const char *m_sepsQuote;
    const char *m_blockEndToken;
    const char *m_endScriptToken;
    unsigned char m_endOfFile;
    char m_curBlockStart[0x838 - 0x431];
    Rva00601BBCHelper m_helper;
    AsciiString m_str86C;
    _STL::vector<AsciiString> m_vec870;
};

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
    OpaqueRefElement4() : referent(0) {}
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};

typedef _STL::deque<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> > MusicStack;

enum MusicSystem { MUSIC_SYSTEM_0, MUSIC_SYSTEM_1 };
inline MusicSystem &operator--(MusicSystem &ms, int) { ms = (MusicSystem)(ms - 1); return ms; }

enum ObjectID
{
    ObjectID_Zero = 0
};

// AudioEventInfo view: +0x44 is the priority the lowest-priority scan ranks by.
struct AudioEventInfo {
    char at00[0x08];
    AsciiString m_audioName;                 // +0x08
    char at0C[0x44 - 0x0C];
    int m_priority;                          // +0x44
    unsigned int m_type;                     // +0x48
};

class AudioEventRTS {
public:
    bool isPositionalAudio(void) const;
    ObjectID getObjectID(void);
    unsigned int getSoundClass(void) const;
    bool hasMoreLoops(void) const;
    void rva002D9ADC(void);
    void advanceNextPlayPortion(void);
    char at00[0x08];
    AudioEventInfo *m_info;  // +0x08 (owning ref in WB)
    char at0C[0x30 - 0x0C];
    int m_viewType;          // +0x30
    char at34[0x4B - 0x34];
    bool m_at4B;             // +0x4B
    char at4C[0x78 - 0x4C];
    MusicSystem m_musicSystem; // +0x78
};

// Owning AudioEventRTS reference (its refcount base sits at event +0x88);
// the ledger's established name, assignment rowed at 0x00051971.
struct BfmePoolHolder88;

class BfmePoolRef10 {
public:
    AudioEventRTS *operator->(void) const { return m_ptr; }
    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
    void rva00053D26(BfmePoolHolder88 *p);  // assign from a raw event (0x00053D26)
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
    char at24[0x4B - 0x24];
    bool m_at4B;                         // +0x4B, set by 0x000535A6
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
    unsigned int m_at08;                  // +0x08 (target stores one argument)
    char at0C[0x10 - 0x0C];
    bool m_at10;                             // +0x10
    bool m_at11;
    bool m_at12;
    bool m_at13;
    bool m_at14;
    char at15[0x18 - 0x15];
};

typedef _STL::list<Rva00051107AudioRequest *> Rva00051107AudioRequestList;

// 0x90-byte refcounted audio event built by the music requests below; its
// (reference, value) constructor is rowed at 0x00051D22.
class Rva0051D93 {
public:
    Rva0051D93(const OpaqueRefElement4 &reference, int value30);
private:
    char opaque[0x90];
};

// Event field setters rowed by address: 0x002D94CE stores the view type at
// +0x30 and the ICF-folded Weapon::setLeechRangeActive (0x002D95FE) a flag.
class Rva002D94CE { public: void rva002D94CE(int value); };
class Weapon { public: void setLeechRangeActive(bool value); };
class Rva002D9BDC { public: void rva002D9BDC(float lo, float hi); };
extern float g_00DBA4FC;
extern float g_Va00BBDA30;

struct Rva0005A084Element { int m_value; };
typedef _STL::vector<Rva0005A084Element> Rva0005A084Vector;

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
    ~Rva00056CF8();
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

// Owning AudioEventInfo reference returned by the slot-75 lookup.
class AudioEventInfoRef {
public:
    ~AudioEventInfoRef() { if (m_ptr) m_ptr->Release_Ref(); }
    AudioEventInfo *get(void) const { return (AudioEventInfo *)m_ptr; }
private:
    OpaqueRefCounted *m_ptr;
};

class Rva002D9508 {
public:
    void rva002D9508(const void *value);
};

class Rva002D9576 {
public:
    int rva002D9576(void);
};

// hash map of event infos by name at +0xBC; its operator[] is 0x00059FBB.
class Rva00059FBBMap {
public:
    AudioEventInfo *&rva00059FBB(const AsciiString &name);
private:
    char opaque[0x14];
};

// Target view for Ghidra FUN_004a8b04: thiscall receiver with two float args.
// The receiver's original class and operation name remain unresolved.
class Rva000A8B04 {
public:
    void rva000A8B04(float first, float second);
};

// Address-derived callee view for the tree lookup used at 0x0005B1C2.
class Rva001F8437 {
public:
    void *rva001F8437(const AsciiString &key);
};

// Existing donor-derived alias of the rowed STLport tree increment worker.
struct BfmeNode1105;
BfmeNode1105 *__cdecl bfmeNext1105(BfmeNode1105 *node);

class MilesAudioManager {
public:
    // Virtual slots 0..74 are not named here; slot 75 (+0x12C) looks an
    // event info up by name.
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
    virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
    virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
    virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
    virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
    virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
    virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64();
    virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
    virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74();
    virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &name) const;
    bool rva00055FCA(int key, void **result, int flags);
    bool rva0005623E(int key, void **result, int flags);
    bool rva00054899(ObjectID objectID, int otherID);
    bool rva00056670(ObjectID objectID);
    bool rva00055426(int objectID);
    float getGlobalReverbMultiplier(void);
    void rva00053AFA(void *pendingSlot);
    void rva000562CF(int key);
    void rva000562A2(int key, const void *value);
    void rva0005A92A(int key, Rva0005A084Vector *output);
    void rva0005B137(void);
    AsciiString rva0005B19E(const AsciiString &key);
    AsciiString rva0005B1FA(const AsciiString &key);
    // These audio INI calls use the manager receiver and an explicit INI*.
    // The receiver type is supported by 0x61BD2's +0x9D4 mutex access; names
    // for 0x5407E/0x540A7 remain address-derived, with helper identity open.
    void rva000541DB(void);
    void rva0005407E(INI *ini);
    void rva000540A7(INI *ini);
    unsigned char rva00054120(INI *ini);
    void rva00057297(Rva00051107AudioRequest &request);
    bool rva000570C8(AudioEventRTS *event);
    void addUnownedAudioEventInfo(AudioEventInfo *eventInfo);
    AudioEventRTS *findLowestPrioritySound(AudioEventRTS *event);
    float rva0005A9F8(void *ref, int a, int b);
    float rva00059AD0(void *event, int a);
    void rva000578B3(int key);
    void rva00057948(const void *input);
    // Ledger rows name it (refreshAll/rva00052048 share its this).
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
    void rva0005774F(int viewType, int musicSystem, int arg);
    void rva0005876E(int viewType, int musicSystem, int arg, int resume);
    bool addAudioEventMusic(BfmePoolRef10 &event, int requestType, int append);
    void rva00055A58(int viewType, int musicSystem, int arg, int flag);
    void rva00055B40(int viewType, int musicSystem, int arg);
    void rva000567F4(int viewType, int musicSystem, int arg);
    void rva000568CE(int viewType, int musicSystem, int arg);
    void rva000569A8(int viewType, int musicSystem, int arg, int flag);
    Rva00051107AudioRequest *rva00051107(void);
    void onPlayingAudioDeleted(PlayingAudio &playingAudioBeingDeleted);
    void releaseMilesHandles(PlayingAudio &playing);
    void moveUpMusicSystems(int newMusicSystem, int viewType, int arg);
    void rva0005AC61(int viewType, int newMusicSystem, int arg);
    bool startNextLoop(PlayingAudioRef &looping);
    void getAppropriateSampleHandleForPlayingAudio(PlayingAudioRef &playing, void **sample, void **sample3D);

    void *get3DSampleHandleForPlayingAudio(PlayingAudioRef &playing);
    void rva000535A6(PlayingAudioRef &playing);

    void putPlayingMusicOnStack(int viewType, int arg);
    void rva00059CE6(PlayingAudioRef &looping);
    void rva0005AA72(PlayingAudioRef &playing);

private:
    char at04[0x98 - 0x04];
    Rva00051107AudioRequestList m_audioRequests;    // +0x98
    char at9C[0xBC - 0x9C];
    Rva00059FBBMap m_allAudioEventInfo;  // +0xBC
    char atD0[0x678 - 0xD0];
    int m_at678;                         // +0x678, compared with event view types
    char at67C[0x69C - 0x67C];
    unsigned short m_maxAmbientStreams;  // +0x69C
    char at69E[0x6A4 - 0x69E];
    bool m_at6A4;                        // +0x6A4
    char at6A5[0x6A7 - 0x6A5];
    bool m_at6A7;                        // +0x6A7, read by 0x52F4C and 0x53AFA
    char at6A8[0x6B4 - 0x6A8];
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

unsigned char MilesAudioManager::rva00054120(INI *ini)
{
    INILoadType type = static_cast<INILoadType>(ini->m_at08);
    unsigned char loaded = ini->loadFile(AsciiString("Data\\INI\\Music.ini"), type, 0);
    loaded |= ini->loadFile(AsciiString("Data\\INI\\SoundEffects.ini"), type, 0);
    loaded |= ini->loadFile(AsciiString("Data\\INI\\Speech.ini"), type, 0);
    loaded |= ini->loadFile(AsciiString("Data\\INI\\Voice.ini"), type, 0);
    loaded |= ini->loadFile(AsciiString("Data\\INI\\AmbientStream.ini"), type, 0);
    loaded |= ini->loadFile(AsciiString("Data\\INI\\MiscAudio.ini"), type, 0);
    return loaded;
}

// Target evidence: exact 0x888-byte INI local, ctor/dtor calls, and three
// thiscall helpers with the same INI* at 0x5407E, 0x540A7 and 0x54120.
// Audio subsystem context supports MilesAudioManager as the receiver class;
// that class association remains a structural inference.
void MilesAudioManager::rva000541DB(void)
{
    INI ini;
    rva0005407E(&ini);
    rva000540A7(&ini);
    rva00054120(&ini);
}

// Address-derived pending-slot adjustment. Target evidence: the +0x6A7 flag
// gates a reverb-scaled pair of floats; 0x52F4C is the matched room multiplier
// and 0xA8B04 is an address-derived two-float receiver view. Original slot and
// helper semantics remain open.
void MilesAudioManager::rva00053AFA(void *pendingSlot)
{
    void * volatile *slot = reinterpret_cast<void * volatile *>(pendingSlot);
    if (m_at6A7) {
        char *middle = *reinterpret_cast<char **>(
            reinterpret_cast<char *>(*slot) + 0x1C);
        char *settings = *reinterpret_cast<char **>(middle + 8);
        float base = *reinterpret_cast<float *>(settings + 0xA8);
        float scaled = getGlobalReverbMultiplier() * base;
        void *device = *slot;
        middle = *reinterpret_cast<char **>(
            reinterpret_cast<char *>(device) + 0x1C);
        settings = *reinterpret_cast<char **>(middle + 8);
        float level = *reinterpret_cast<float *>(settings + 0xAC);
        reinterpret_cast<Rva000A8B04 *>(reinterpret_cast<char *>(device) + 0x0C)
            ->rva000A8B04(level, scaled);
    } else {
        reinterpret_cast<Rva000A8B04 *>(reinterpret_cast<char *>(*slot) + 0x0C)
            ->rva000A8B04(1.0f, 0.0f);
    }
}

void MilesAudioManager::moveUpMusicSystems(int newMusicSystem, int viewType, int arg)
{
    putPlayingMusicOnStack(viewType, arg);
    m_activeMusicSystem[viewType] = (MusicSystem)newMusicSystem;
}

// Address-derived Manager method. The target passes the lookup output to the
// manager helper and increments the returned object's +0x80 reference count.
// The helper's address is read directly from the call at 0x000562E0.
void MilesAudioManager::rva000562CF(int key)
{
    void *result = 0;
    if (rva00055FCA(key, &result, 0) && result)
        ++*reinterpret_cast<int *>(reinterpret_cast<char *>(result) + 0x80);
}

// The neighboring target uses the same helper; its returned object receives
// the existing 0x002D9508 setter call with the second argument.
void MilesAudioManager::rva000562A2(int key, const void *value)
{
    void *result = 0;
    if (rva00055FCA(key, &result, 0) && result)
        reinterpret_cast<Rva002D9508 *>(result)->rva002D9508(value);
}

// Address-derived lookup wrapper; target appends the found record's +8 dword
// to the caller's four-byte vector using the already matched push_back body.
void MilesAudioManager::rva0005A92A(int key, Rva0005A084Vector *output)
{
    void *result = 0;
    if (rva0005623E(key, &result, 0) && result)
        output->push_back(*reinterpret_cast<const Rva0005A084Element *>(reinterpret_cast<char *>(result) + 8));
}

// Target evidence: the 92B body tests the byte at this+0x6A4, searches a
// tree at this+0xB0 by AsciiString key, advances the found node, wraps to the
// header's left node, and copy-returns the node string at +0x10 (or the empty
// string at 0x00DE0878). MilesAudioManager receiver identity is a structural
// inference from these fields and the surrounding audio methods.
AsciiString MilesAudioManager::rva0005B19E(const AsciiString &key)
{
    if (!m_at6A4)
        rva0005B137();

    Rva001F8437 *tree = reinterpret_cast<Rva001F8437 *>(
        reinterpret_cast<char *>(this) + 0xB0);
    void *next = tree->rva001F8437(key);
    if (next != *reinterpret_cast<void **>(tree))
        next = bfmeNext1105(reinterpret_cast<BfmeNode1105 *>(next));

    void *header = *reinterpret_cast<void **>(tree);
    if (next == header) {
        next = *reinterpret_cast<void **>(reinterpret_cast<char *>(header) + 8);
        if (next == header)
            return AsciiString::TheEmptyString;
    }

    return *reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(next) + 0x10);
}

// Target evidence: the 92B body shares the +0x6A4 initialization gate and
// +0xB0 string tree with 0x5B19E. It returns the empty string for a zero
// count; otherwise it finds the key, maps the leftmost node to the header,
// decrements once, and copies the node string at +0x10. The manager identity
// remains a structural inference from the surrounding audio methods.
AsciiString MilesAudioManager::rva0005B1FA(const AsciiString &key)
{
    if (!m_at6A4)
        rva0005B137();

    if (*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 0xB4) == 0)
        return AsciiString::TheEmptyString;

    Rva001F8437 *tree = reinterpret_cast<Rva001F8437 *>(
        reinterpret_cast<char *>(this) + 0xB0);
    void *node = tree->rva001F8437(key);
    void *header = *reinterpret_cast<void **>(tree);
    if (node == *reinterpret_cast<void **>(reinterpret_cast<char *>(header) + 8))
        node = header;

    node = _STL::_Rb_global<bool>::_M_decrement(
        reinterpret_cast<_STL::_Rb_tree_node_base *>(node));
    return *reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(node) + 0x10);
}

// Retail @ 0x0005AC61 gates the move-up helper on the per-view active system.
// Its direct caller supplies the view, requested system, and playback flag.
void MilesAudioManager::rva0005AC61(int viewType, int newMusicSystem, int arg)
{
    if (newMusicSystem > m_activeMusicSystem[viewType])
        moveUpMusicSystems(newMusicSystem, viewType, arg);
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

void MilesAudioManager::rva0005AA72(PlayingAudioRef &playing)
{
    playing->m_event->rva002D9ADC();
    if (playing->m_event->hasMoreLoops()) {
        playing->m_event->advanceNextPlayPortion();
        ((Rva002D9BDC *)playing->m_event.operator->())->rva002D9BDC(g_00DBA4FC + 1.0f, g_Va00BBDA30);
        playing->m_event->m_at4B = true;
        rva00059CE6(playing);
    }
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

// Vtable slots 34 and 35 (0x007C5638/0x007C563C): queue request 4 or 2 for
// a fresh event carrying the view type, music system and flags. WorldBuilder
// 0x788B70 has the same order; the request names stay address-derived.
void MilesAudioManager::rva00055A58(int viewType, int musicSystem, int arg, int flag)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva00051107AudioRequest *request = rva00051107();
    request->m_request = 4;
    request->m_at10 = arg == 0;
    request->m_pendingEvent.rva00053D26(
        reinterpret_cast<BfmePoolHolder88 *>(new Rva0051D93(OpaqueRefElement4(), 0)));
    ((Weapon *)request->m_pendingEvent.operator->())->setLeechRangeActive(flag == 0);
    ((Rva002D94CE *)request->m_pendingEvent.operator->())->rva002D94CE(viewType);
    request->m_pendingEvent->m_musicSystem = (MusicSystem)musicSystem;
    m_audioRequests.push_back(request);
}

void MilesAudioManager::rva00055B40(int viewType, int musicSystem, int arg)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva00051107AudioRequest *request = rva00051107();
    request->m_request = 2;
    request->m_at10 = arg == 0;
    request->m_pendingEvent.rva00053D26(
        reinterpret_cast<BfmePoolHolder88 *>(new Rva0051D93(OpaqueRefElement4(), 0)));
    ((Rva002D94CE *)request->m_pendingEvent.operator->())->rva002D94CE(viewType);
    request->m_pendingEvent->m_musicSystem = (MusicSystem)musicSystem;
    m_audioRequests.push_back(request);
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

void MilesAudioManager::rva0005774F(int viewType, int musicSystem, int arg)
{
    if (m_activeMusicSystem[viewType] == musicSystem)
        removeCurrentlyPlayingMusic(viewType, arg);
    m_musicStack[viewType][musicSystem].clear();
}

// Retail dispatches a nonzero active system through the preceding empty stack
// entries before moving down; otherwise it clears the requested system directly.
// Identity: same manager fields and callees as adjacent music-system handlers.
void MilesAudioManager::rva0005876E(int viewType, int musicSystem, int arg, int resume)
{
    if (m_activeMusicSystem[viewType] == musicSystem && musicSystem != 0) {
        int previous = musicSystem - 1;
        while (previous > 0 && m_musicStack[viewType][previous].empty())
            --previous;
        moveDownMusicSystems(viewType, (MusicSystem)previous, arg, resume);
    } else {
        rva0005774F(viewType, musicSystem, arg);
    }
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

void MilesAudioManager::rva00057297(Rva00051107AudioRequest &request)
{
    AudioEventRTS *event = request.m_pendingEvent.operator->();
    int viewType = event->m_viewType;
    MusicSystem musicSystem = event->m_musicSystem;
    if (m_activeMusicSystem[viewType] == musicSystem) {
        removeCurrentlyPlayingMusic(viewType, !request.m_at10);
    } else {
        MusicStack &stack = m_musicStack[viewType][musicSystem];
        if (!stack.empty())
            stack.pop_back();
    }
}

bool MilesAudioManager::rva000570C8(AudioEventRTS *event)
{
    if (event->m_info->m_type & 0x10)
        return rva00056670(event->getObjectID()) || rva00055426(
            static_cast<ObjectID>(reinterpret_cast<Rva002D9576 *>(event)->rva002D9576()));
    return false;
}

void MilesAudioManager::rva00057948(const void *input)
{
    MilesMutexGuard guard(&m_mutex, 0);
    rva000578B3(*reinterpret_cast<const int *>(
        reinterpret_cast<const char *>(input) + 0x0C));
}

bool __cdecl Rva000515E4Less(const Rva000515E4Key *x, const Rva000515E4Key *y)
{
    if (x->a < y->a)
        return true;
    if (x->a > y->a)
        return false;
    return y->b > x->b;
}

void MilesAudioManager::addUnownedAudioEventInfo(AudioEventInfo *eventInfo)
{
    MilesMutexGuard guard(&m_mutex, 0);
    AudioEventInfoRef existing = findAudioEventInfo(eventInfo->m_audioName);
    if (existing.get() == 0) {
        m_allAudioEventInfo.rva00059FBB(eventInfo->m_audioName) = eventInfo;
        m_at6A4 = false;
    }
}

class Rva00059068Tree
{
public:
    ~Rva00059068Tree();
};

// ?Rva00059068Tree::~Rva00059068Tree present-unmatched
Rva00059068Tree::~Rva00059068Tree()
{
    ((_STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > *)this)->~_Rb_tree();
}

class Rva0005906D
{
public:
    void rva0005906D();
};

void Rva0005906D::rva0005906D()
{
    ((Rva00056CF8 *)this)->~Rva00056CF8();
}

// Target 0x000567F4: all calls, offsets, EH states and branches agree
// with the matched request-2 member at 0x00055B40; request opcode is 7.
// Opcode purpose remains unnamed. Same three arguments and mutex scope.
void MilesAudioManager::rva000567F4(int viewType, int musicSystem, int arg)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva00051107AudioRequest *request = rva00051107();
    request->m_request = 7;
    request->m_at10 = arg == 0;
    request->m_pendingEvent.rva00053D26(
        reinterpret_cast<BfmePoolHolder88 *>(new Rva0051D93(OpaqueRefElement4(), 0)));
    ((Rva002D94CE *)request->m_pendingEvent.operator->())->rva002D94CE(viewType);
    request->m_pendingEvent->m_musicSystem = (MusicSystem)musicSystem;
    m_audioRequests.push_back(request);
}

// Target 0x000568CE: request-5 twin of the matched request-2 member.
// Retail preserves the same calls, member offsets, argument ABI and EH states.
void MilesAudioManager::rva000568CE(int viewType, int musicSystem, int arg)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva00051107AudioRequest *request = rva00051107();
    request->m_request = 5;
    request->m_at10 = arg == 0;
    request->m_pendingEvent.rva00053D26(
        reinterpret_cast<BfmePoolHolder88 *>(new Rva0051D93(OpaqueRefElement4(), 0)));
    ((Rva002D94CE *)request->m_pendingEvent.operator->())->rva002D94CE(viewType);
    request->m_pendingEvent->m_musicSystem = (MusicSystem)musicSystem;
    m_audioRequests.push_back(request);
}

// Target 0x000569A8: request-6 sibling of the verified request-4 wrapper.
// Native order sets the view before the fourth-argument flag; all other
// calls, member offsets, ABI and EH states agree. Opcode purpose stays open.
void MilesAudioManager::rva000569A8(int viewType, int musicSystem, int arg, int flag)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva00051107AudioRequest *request = rva00051107();
    request->m_request = 6;
    request->m_at10 = arg == 0;
    request->m_pendingEvent.rva00053D26(
        reinterpret_cast<BfmePoolHolder88 *>(new Rva0051D93(OpaqueRefElement4(), 0)));
    ((Rva002D94CE *)request->m_pendingEvent.operator->())->rva002D94CE(viewType);
    ((Weapon *)request->m_pendingEvent.operator->())->setLeechRangeActive(flag == 0);
    request->m_pendingEvent->m_musicSystem = (MusicSystem)musicSystem;
    m_audioRequests.push_back(request);
}

// Target 0x000540A7: four default audio files loaded in native order.
// The +8 INI value supplies every load type, as in 0x00054120; the manager
// receiver remains inferred from the matched orchestration at 0x000541DB.
void MilesAudioManager::rva000540A7(INI *ini)
{
    INILoadType type = static_cast<INILoadType>(ini->m_at08);
    ini->loadFile(AsciiString("Data\\INI\\Default\\Music.ini"), type, 0);
    ini->loadFile(AsciiString("Data\\INI\\Default\\Speech.ini"), type, 0);
    ini->loadFile(AsciiString("Data\\INI\\Default\\SoundEffects.ini"), type, 0);
    ini->loadFile(AsciiString("Data\\INI\\Default\\AmbientStream.ini"), type, 0);
}

// Same orchestration receiver and INI +8 load type as 0x000540A7.
// The native single-file wrapper uses the audio settings filename.
void MilesAudioManager::rva0005407E(INI *ini)
{
    INILoadType type = static_cast<INILoadType>(ini->m_at08);
    ini->loadFile(AsciiString("Data\\INI\\AudioSettings.ini"), type, 0);
}

void *MilesAudioManager::get3DSampleHandleForPlayingAudio(PlayingAudioRef &playing)
{
    switch (playing->m_type) {
    case 2:
        return (void *)playing->m_handle;
    case 3:
        if (m_loopBuffers[playing->m_handle].m_is3D)
            return m_loopBuffers[playing->m_handle].m_3DSample;
        return 0;
    case 5:
        return 0;
    }
    return 0;
}

// WorldBuilder 0x7A13D0 (unnamed, aligned by score 5.0): flags the playing
// audio's +0x4B byte unless its event view type is 2 or matches +0x678.
void MilesAudioManager::rva000535A6(PlayingAudioRef &playing)
{
    int viewType = playing->m_event->m_viewType;
    if (viewType != 2 && viewType != m_at678)
        playing->m_at4B = true;
    else
        playing->m_at4B = false;
}
