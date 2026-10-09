// ?processAmbientStreams@MilesAudioManager@@QAEXPAU?$_List_iterator@VPlayingAudioRef@@U?$_Nonconst_traits@VPlayingAudioRef@@@_STL@@@_STL@@@Z
// partial score=0.7623023179 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include <math.h>
// STLport frees through the game's C++-linkage free at 0x00030830 (pinned as
// ?free@_STL@@YAXPAX@Z): a callee that may throw is what keeps the unwind
// state reset retail stores before a local hash_set's destructor.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <deque>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <hash_map>
#include <hash_set>
#include <set>
#include <map>
#include <vector>
#undef free
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
#include "Common/Snapshot.h"

// Xfer view: slot 1 tells a load from a save; +0x78 and +0x90 xfer an
// unsigned int and a bool (0x0005B256).
class Xfer {
public:
    virtual ~Xfer();
    virtual bool isLoading();
    virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
    virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
    virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual Xfer &xferUnsignedInt(unsigned int *value);
    virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
    virtual void slot35();
    virtual Xfer &xferBool(bool *value);
};
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

#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

// (channel, volume) entry of AudioEventInfo +0xB8: 0x0005818B reads the
// channel index first (-1 skips) and the float second.
struct AudioEventChannelVolume {
    int m_channel;
    float m_volume;
};

// AudioEventInfo view: +0x44 is the priority the lowest-priority scan ranks by.
// prep3DSample passes +0x94 as AIL_set_3D_sample_distances' max distance and
// +0x98 (non-global sounds) as its min distance.
struct AudioEventInfo {
    char at00[0x08];
    AsciiString m_audioName;                 // +0x08
    char at0C[0x44 - 0x0C];
    int m_priority;                          // +0x44
    unsigned int m_type;                     // +0x48, bit 3 global
    unsigned int m_control;                  // +0x4C, Zero Hour's AudioControl bits (AC_LOOP = 1)
    char at50[0x90 - 0x50];
    float m_at90;                            // +0x90, occlusion factor when positive
    float m_maxDistance;                     // +0x94
    float m_minDistance;                     // +0x98
    char at9C[0xA4 - 0x9C];
    float m_atA4;                            // +0xA4, distance occlusion weight
    float m_reverbWetLevel;                  // +0xA8, wet level scaled by the global reverb multiplier (0x52FA0)
    float m_reverbDryLevel;                  // +0xAC, dry level passed with it (0x52FA0)
    int m_atB0;                              // +0xB0, processRequest preloads a file when 2
    char atB4[0xB8 - 0xB4];
    _STL::vector<AudioEventChannelVolume> m_channelVolumes;  // +0xB8
};

// Owning AudioEventRTS reference (its refcount base sits at event +0x88);
// the ledger's established name: copy constructor rowed at 0x00051950,
// destructor at 0x000519AB and assignment at 0x00051971.
class AudioEventRTS;
struct BfmePoolHolder88;

class BfmePoolRef10 {
public:
    BfmePoolRef10() : m_ptr(0) {}
    // Retail 0x00051950 (rowed in stlport_stringtailrecord144_dtor.cpp; same
    // bytes here). Out of line in retail but visible to this unit, so cl knows
    // the copy keeps no pointer to itself: checkForNaturalSoundCompletion then
    // holds the waiting event in esi and drops its release null test.
    __declspec(noinline) BfmePoolRef10(const BfmePoolRef10 &other) : m_ptr(other.m_ptr) { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(reinterpret_cast<char *>(m_ptr) + 0x88)->Add_Ref(); }
    ~BfmePoolRef10() { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(reinterpret_cast<char *>(m_ptr) + 0x88)->Release_Ref(); }
    AudioEventRTS *operator->(void) const { return m_ptr; }
    AudioEventRTS *get(void) const { return m_ptr; }
    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
    void rva00053D26(BfmePoolHolder88 *p);  // assign from a raw event (0x00053D26)
    void rva000519BD(void);                 // release then null (0x000519BD)
private:
    AudioEventRTS *m_ptr;
};

class AudioEventRTS {
public:
    bool isPositionalAudio(void) const;
    ObjectID getObjectID(void);
    unsigned int getSoundClass(void) const;
    bool hasMoreLoops(void) const;
    void generatePlayInfo(void);
    void rva002D9ADC(void);
    void advanceNextPlayPortion(void);
    // Inline in WorldBuilder too (its twin copies the read into a temp);
    // putFileIntoLoopBuffer's first reads go through it into a register.
    int getNextPlayPortion(void) const { return m_portionToPlayNext; }
    // Inline getter (WorldBuilder calls it on the +0x08 reference); the
    // loop-buffer refill's decay test reads through it.
    const AudioEventInfo *getAudioEventInfo(void) const { return m_info; }
    AsciiString getFilename(void);
    // WorldBuilder names; both are inline in retail.
    void decrementNumberOfEventsNeedingToBeDoneBeforeReplaying(void) { --m_at14; }
    void setNumberOfTimesToPlayMusicOrMultisound(int times) { m_loopCount = times; }
    // The +0x84 name checkForNaturalSoundCompletion tests.
    const AsciiString &getAt84(void) const { return *reinterpret_cast<const AsciiString *>(m_at84); }
    char at00[0x08];
    AudioEventInfo *m_info;  // +0x08 (owning ref in WB)
    int m_playingHandle;     // +0x0C, copied into a requeued loop's request
    AudioEventRTS *m_at10;   // +0x10, owning reference to the event waiting on this one (0x002D9AD4 sets it)
    int m_at14;              // +0x14, events still to finish before that one replays
    char at18[0x30 - 0x18];
    int m_viewType;          // +0x30
    char at34[0x38 - 0x34];
    int m_ownerType;         // +0x38, 2 when object-owned (getObjectID's test)
    char at3C[0x4B - 0x3C];
    bool m_at4B;             // +0x4B
    bool m_at4C;             // +0x4C, the loop-buffer thread's decay/loop test
    char at4D[0x50 - 0x4D];
    bool m_at50;             // +0x50, set once a sample starts playing
    char at51[0x64 - 0x51];
    float m_at64;            // +0x64, compared with AudioSettings +0xB4 and one frame
    char at68[0x74 - 0x68];
    int m_portionToPlayNext; // +0x74, the portion advanceNextPlayPortion steps
    MusicSystem m_musicSystem; // +0x78
    int m_loopCount;         // +0x7C, -12345 loops forever (0x00051E7D)
    int m_at80;              // +0x80, holds against a stop request (0x000562CF adds one)
    char m_at84[4];          // +0x84, an AsciiString (see getAt84)
};

// Open audio file the holder below points at. WorldBuilder names its getters
// (OpenAudioFile::getMilesSoundInfo, getFileImage): the file name sits at +0,
// Miles' AILSOUNDINFO at +0x08 (channels at +0x14) and the file image at +0x2C.
struct MilesSoundInfo {
    int m_format;                        // +0x00
    const void *m_dataPtr;               // +0x04, AILSOUNDINFO data_ptr
    unsigned int m_dataLen;              // +0x08, AILSOUNDINFO data_len
    unsigned int m_rate;                 // +0x0C
    unsigned int m_bits;                 // +0x10
    int m_channels;                      // +0x14
    char at18[0x24 - 0x18];
};
struct OpenAudioFile {
    AsciiString m_fileName;              // +0x00
    char at04[0x08 - 0x04];
    MilesSoundInfo m_soundInfo;          // +0x08
    void *m_fileImage;                   // +0x2C
    char at30[0x3C - 0x30];
    int m_at3C;                          // +0x3C, re-requested by name while below 2
};

// Release-then-null holder at PlayingAudio +0x20 (ledger 0x000A8A6C); its
// inline accessors fall back to null or the empty name when no file is open.
class Rva000A8A6C {
public:
    void rva000A8A6C(void);
    bool isOpen(void) const { return m_ptr != 0; }
    const AsciiString &getFileName(void) const { return m_ptr ? m_ptr->m_fileName : AsciiString::TheEmptyString; }
    const MilesSoundInfo *getMilesSoundInfo(void) const { return m_ptr ? &m_ptr->m_soundInfo : 0; }
    void *getFileImage(void) const { return m_ptr ? m_ptr->m_fileImage : 0; }
private:
    OpenAudioFile *m_ptr;
};

// Target view for Ghidra FUN_004a8b04: thiscall receiver with two float args.
// The receiver's original class and operation name remain unresolved.
class Rva000A8B04 {
public:
    void rva000A8B04(float first, float second);
};
// The same +0x0C receiver's loop-count setter and restart, rowed at
// 0x000A8B23 and 0x000A8AB4 under their own address-derived owners.
class Rva000A8B23 { public: void rva000A8B23(int loopCount); };
class Rva000A8AB4 { public: void rva000A8AB4(void); };
// Further +0x0C stream-holder forwarders (PinnedForwarders1830.cpp).
struct Rva0010FFA2Packet;
class Rva000A8B4B { public: void rva000A8B4B(int callback); };
class Rva000A8C6E { public: void rva000A8C6E(const Rva0010FFA2Packet *packet); };
class Rva000A8B31 { public: void rva000A8B31(float position, int arg); };
class Rva000A8ACC { public: void rva000A8ACC(void); };
class MilesStreamRef { public: void rva000A8AC0(void); };
class Rva000A8AD8 { public: void rva000A8AD8(float level); };
// Opens a stream file into the +0x0C holder (0x000A8D0B, operator new(0x28)).
class Rva000A8D0B { public: void rva000A8D0B(void *owner, const AsciiString &file, int arg); };

struct PlayingAudio {
    void *vfptr;
    long refs;
    int m_handle;                        // +0x08 loop-buffer / handle-state index
    Rva000A8B04 m_at0C;                  // +0x0C, type-4 receiver of the reverb level pair (0x52FA0)
    char at0D[0x14 - 0x0D];
    int m_type;                          // +0x14
    int m_status;                        // +0x18
    BfmePoolRef10 m_event;            // +0x1C
    Rva000A8A6C m_file;                  // +0x20
    Coord3D m_at24;                      // +0x24, last position 0x55C5D tested
    float m_at30;                        // +0x30, compared with settings +0x78 (0x59CE6)
    float m_at34;                        // +0x34, scales the 3D effects level (0x52FA0)
    int m_at38;                          // +0x38, area index 0x55C5D starts from
    float m_at3C;                        // +0x3C, extra volume handed to a requeued loop
    float m_at40;                        // +0x40, cleared once that volume is handed on
    bool m_at44;                         // +0x44, tested with +0x46 by checkForNaturalSoundCompletion
    bool m_at45;                         // +0x45, set when a pushed track resumes
    bool m_at46;                         // +0x46
    char at47;
    bool m_at48;                         // +0x48, overrides +0x44/+0x46 in that test
    bool m_at49;                         // +0x49
    bool m_at4A;                         // +0x4A
    bool m_at4B;                         // +0x4B, set by 0x000535A6
    char at4C[0x4D - 0x4C];
    bool m_at4D;                         // +0x4D, raise the event's script flag on release (0x5FDCA)
    bool m_at4E;                         // +0x4E, m_at24 holds a position
};

// Retain-and-replace setter rowed at 0x000A8CE5 under its address-derived owner.
class Rva000A8C9B {
public:
    void clear(void);
    void rva000A8CE5(OpaqueRefCounted *value);
private:
    OpaqueRefCounted *m_ptr;
};

class PlayingAudioRef {
public:
    PlayingAudioRef() : m_ptr(0) {}
    PlayingAudioRef(const PlayingAudioRef &other) : m_ptr(other.m_ptr) { if (m_ptr) asRefCounted()->Add_Ref(); }
    PlayingAudioRef(PlayingAudio *playing);
    ~PlayingAudioRef() { if (m_ptr) asRefCounted()->Release_Ref(); }
    // Folded at 0x00239099; defined here (cl still calls it out of line) so
    // the unit knows it neither keeps nor changes its argument, which is
    // what lets 0x00055FCA release its copy from the register it tested.
    PlayingAudioRef &operator=(const PlayingAudioRef &other)
    {
        if (this != &other) {
            if (other.m_ptr)
                other.asRefCounted()->Add_Ref();
            if (m_ptr)
                asRefCounted()->Release_Ref();
            m_ptr = other.m_ptr;
        }
        return *this;
    }
    PlayingAudio *operator->(void) const { return m_ptr; }
    PlayingAudio *get(void) const { return m_ptr; }
    void set(PlayingAudio *playing)
    {
        reinterpret_cast<Rva000A8C9B *>(this)->rva000A8CE5(reinterpret_cast<OpaqueRefCounted *>(playing));
    }
private:
    OpaqueRefCounted *asRefCounted(void) const { return reinterpret_cast<OpaqueRefCounted *>(m_ptr); }
    PlayingAudio *m_ptr;
};

// WorldBuilder's free comparison (inline in retail): same referent.
inline bool operator==(const PlayingAudioRef &left, const PlayingAudioRef &right)
{
    return left.get() == right.get();
}

// Assignment of the event's +0x10 reference, rowed at 0x002D9AD4 under an
// address-derived owner.
class Rva002D9AD4 {
public:
    BfmePoolRef10 &rva002D9AD4(const BfmePoolRef10 &other);
};

// Retail 0x00051914, which ICF shares with AudioEventInfoRef's constructor;
// the loop-buffer thread (0x0005EFE9) builds one from a buffer's playing audio.
PlayingAudioRef::PlayingAudioRef(PlayingAudio *playing) : m_ptr(playing)
{
    if (m_ptr)
        asRefCounted()->Add_Ref();
}

// 0x18-byte request record (operator new(0x18) in its allocator 0x00051107);
// Zero Hour's AudioRequest plays this role, the name stays address-derived.
struct Rva00051107AudioRequest {
    int m_request;
    BfmePoolRef10 m_pendingEvent;         // +0x04
    unsigned int m_at08;                  // +0x08 (target stores one argument)
    Rva000A8A6C m_file;                   // +0x0C, preloaded by processRequest
    bool m_at10;                             // +0x10
    bool m_at11;
    bool m_at12;
    bool m_at13;
    bool m_at14;
    char at15[0x18 - 0x15];
};

typedef _STL::list<Rva00051107AudioRequest *> Rva00051107AudioRequestList;

// Request set at +0x9C keyed by the +0x08 handle: retail's bucket helper
// 0x00051B89 inlines this hash and its erase calls the equality at
// 0x00050E1C out of line; both fall back to the pointer when it is null.
struct Rva00051B89Hash {
    unsigned int operator()(const Rva00051107AudioRequest *req) const
    {
        // Retail's pointer-key hash keeps zero from the null key itself.
        unsigned int handle = reinterpret_cast<unsigned int>(req);
        if (req)
            handle = req->m_at08;
        return handle;
    }
    // The same hash over the rowed Rva00051B89Keyed view (0x00056FD9).
    unsigned int operator()(const struct Rva00051B89Keyed *req) const
    {
        return (*this)(reinterpret_cast<const Rva00051107AudioRequest *>(req));
    }
};

struct Rva00050E1CEqualTo {
    bool operator()(const Rva00051107AudioRequest *left, const Rva00051107AudioRequest *right) const
    {
        if (left && right)
            return left->m_at08 == right->m_at08;
        return left == right;
    }
};

typedef _STL::hash_set<Rva00051107AudioRequest *, Rva00051B89Hash, Rva00050E1CEqualTo>
    Rva00051107AudioRequestSet;

// File handle AudioFileCache::requestFile returns (WorldBuilder name and
// MilesAudioCache.cpp asserts). The ledger rows its destructor (0x000A8A37)
// and assignment (0x000A8A43) under two BFME 1 donor class names.
class Rva00691040Handle {
public:
    Rva00691040Handle &operator=(const Rva00691040Handle &other);
private:
    void *m_target;
};
// A ready file the handle hands out (WorldBuilder: AudioFileContainer, its
// ctor asserting assertFileIsReady at 0x0077B650). It has its own ctor/dtor
// pair in WorldBuilder (0x008E4730/0x008E47B0); retail folds the destructor
// with the handle's (0x000A8A37).
class AudioFileContainer {
public:
    AudioFileContainer();
    ~AudioFileContainer();
    bool isValid(void) const { return m_target != 0; }
    operator const Rva00691040Handle &() const { return *reinterpret_cast<const Rva00691040Handle *>(this); }
    const AsciiString &getFileName(void) const { return m_target ? m_target->m_fileName : AsciiString::TheEmptyString; }
    const MilesSoundInfo *getMilesSoundInfo(void) const { return m_target ? &m_target->m_soundInfo : 0; }
    void *getFileImage(void) const { return m_target ? m_target->m_fileImage : 0; }
private:
    OpenAudioFile *m_target;
};
// Retail folds it with the other empty-pointer constructors at 0x00326BE6.
AudioFileContainer::AudioFileContainer() : m_target(0)
{
}
class Rva00690FF0Handle {
public:
    Rva00690FF0Handle();
    ~Rva00690FF0Handle();
    bool isValid(void) const { return m_target != 0; }
    operator const Rva00691040Handle &() const { return *reinterpret_cast<const Rva00691040Handle *>(this); }
    const AsciiString &getFileName(void) const { return m_target ? m_target->m_fileName : AsciiString::TheEmptyString; }
    const MilesSoundInfo *getMilesSoundInfo(void) const { return m_target ? &m_target->m_soundInfo : 0; }
    void *getFileImage(void) const { return m_target ? m_target->m_fileImage : 0; }
    int getAt3C(void) const { return m_target ? m_target->m_at3C : 0; }
    AudioFileContainer rva000A89E3(void) const;  // a new reference once ready (0x000A89E3)
private:
    OpenAudioFile *m_target;
};
// WorldBuilder names both overloads requestFile (MilesAudioCache.cpp); the
// by-name one (0x000A7EFA) clamps its priority argument to 0..2.
class AudioFileCache {
public:
    Rva00690FF0Handle requestFile(const BfmePoolRef10 &event, int shortSound);
    Rva00690FF0Handle requestFile(const AsciiString &fileName, int priority);
};
// The file handle's ready (+0x44) and failed (+0x4C) checks, rowed at
// 0x00050DBD and 0x00050DD0 under address-derived names.
class Rva00050DBD { public: bool rva00050DBD(); };
class Rva00050DD0 { public: bool rva00050DD0(); };
// Plain dword setter at +0x74 (0x002D94FE), i.e. the event's next play portion.
class Rva002D94FEDwordSlot { public: void set(int value); };

// Request gate rowed at 0x0005E13C under address-derived names.
struct Rva0005E13CArg;
class Rva0005E13CHost {
public:
    bool rva0005E13C(const Rva0005E13CArg *request);
};
class Rva000CB12FByteField {
public:
    unsigned char get(void) const;
};

// 0x90-byte refcounted audio event built by the music requests below; its
// (reference, value) constructor is rowed at 0x00051D22.
struct BfmeAudioEventPrefix136;
class Rva0051D93 {
public:
    Rva0051D93(const OpaqueRefElement4 &reference, int value30);
    Rva0051D93(const BfmeAudioEventPrefix136 &source);
private:
    char opaque[0x90];
};

// Event field setters rowed by address: 0x002D94CE stores the view type at
// +0x30 and the ICF-folded Weapon::setLeechRangeActive (0x002D95FE) a flag.
class Rva002D94CE { public: void rva002D94CE(int value); };
class Weapon { public: void setLeechRangeActive(bool value); };
class Rva002D9BDC { public: void rva002D9BDC(float lo, float hi); };
// WorldBuilder calls this AudioEventRTS::setExtraVolumeMultiplier; retail
// folded it to 0x00481FAF, rowed under this neutral float-slot name.
class Rva00481FAFFloatSlot { public: void store(float value); };
// Float-returning event query rowed at 0x002DA153; prep3DSample compares it
// with AudioSettings +0xB8 to treat a sound as global.
class Rva002DA153 { public: float rva002DA153(void); };
// Event pitch-shift multiplier (rowed 0x002D94DD, a const float product
// getter); initFilters3D scales the 3D playback rate by it when non-zero.
class Rva002D94E4 {public:float rva002D94E4(void) const;};
class Rva002D94DD { public: float rva002D94DD(void) const; };
// 8-byte record of the manager's +0xB54 vector: 0x55C5D passes +0x00 to
// Object::isInside(PolygonTrigger *) and keeps the lowest +0x04 level whose
// trigger holds the event. Names are descriptive.
class PolygonTrigger { public: bool rva002E3A39(const Coord3D &pos); };
class Object { public: bool isInside(PolygonTrigger *trigger); };
extern GameLogic *TheGameLogic;
inline float sqr(float value) { return value * value; }

// class-gate: allow Coord2D retail 0x53854 receives ClosestPointOnLineSegment's Coord2D through a hidden return pointer (exported user ctors and dtor make BFME 2's Coord2D non-POD); the canonical plain Coord2D returns in edx:eax
class Coord2D
{
public:
    Coord2D() {}
    Coord2D(const Coord3D &that) : x(that.x), y(that.y) {}
    Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}
    ~Coord2D() {}
    Coord2D &Sub(const Coord3D &that) { x -= that.x; y -= that.y; return *this; }
    float GetLengthSqrd() const { return x * x + sqr(y); }
    float x;
    float y;
};

// Exported 0x00004C06 (folded with Region2D's ctor) and 0x006B3100.
struct LineSegment2D {
    LineSegment2D(const Coord2D &start, const Coord2D &end);
    Coord2D m_start;
    Coord2D m_end;
};
Coord2D ClosestPointOnLineSegment(const LineSegment2D &segment, const Coord2D &point);

// Corner records at MilesAudioManager +0x3C; 0x53854 scans entries 1..4.
struct AudioAreaCorner {
    Coord3D m_pos;
    bool m_valid;                        // +0x0C
};

struct AudioTriggerArea {
    PolygonTrigger *m_trigger;
    float m_level;
};
// The saved form of an AudioTriggerArea: loadPostProcess (0x000587C6) looks
// the +0x00 trigger ID up and copies the +0x04 level.
struct AudioTriggerAreaSave {
    int m_triggerID;
    float m_level;
};

// Event position returned by the rowed 0x0005160F (zeros and false when the
// event is not positional); playSample3D hands it to prep3DSample.
struct BfmeEventPositionView : public Coord3D {};
// Info-reference parameter type of the split-out 0x000581FA.
struct Rva0005BA08InfoRef;

// AudioSettings view (Zero Hour's MilesAudioManager reads it through
// m_audioSettings at +0x10): +0x74 is an int distance, +0xB8 a float limit.
// Per-view microphone record of AudioSettings (WorldBuilder's assert names
// m_microphoneSettings), indexed by the manager's +0x678 view type.
// setOcclusionLevels divides the listener distance by +0x30 when it is within
// +0x34 (squared); the 0x5213E volume update reads +0x1C..+0x2C.
struct MicrophoneSettings {
    char at00[0x1C];
    float m_at1C;                        // +0x1C, attenuation start distance
    float m_at20;                        // +0x20, squared distance below which nothing attenuates
    float m_at24;                        // +0x24, attenuation end distance
    float m_at28;                        // +0x28, squared end distance
    float m_at2C;                        // +0x2C, maximum attenuation
    float m_at30;                        // +0x30
    float m_at34;                        // +0x34
    char at38[0x48 - 0x38];
};

struct AudioSettings {
    char at00[0x30];
    float m_at30[5];                     // +0x30, init()'s per-index 0x524EE volumes
    char at44[0x64 - 0x44];
    int m_at64;                          // +0x64, with +0x68 init()'s loop-buffer count
    int m_at68;                          // +0x68
    char at6C[0x74 - 0x6C];
    int m_at74;
    int m_at78;                          // +0x78, compared with a loop's +0x30 (0x59CE6)
    int m_at7C;
    unsigned int m_at80;                 // +0x80, handed to the file cache's 0xA77D9
    char at84[0x8C - 0x84];
    unsigned int m_at8C;                 // +0x8C, over +0x90 the loop-buffer thread's sleep
    unsigned int m_at90;                 // +0x90
    char at94[0xA8 - 0x94];
    int m_atA8;                          // +0xA8, seconds before 0x61C87 reopens the device
    char atAC[0xB0 - 0xAC];
    float m_atB0;                        // +0xB0, position change 0x55C5D ignores
    int m_atB4;                          // +0xB4, processRequest's preload limit
    float m_atB8;
    bool m_atBC;                         // +0xBC, disables occlusion
    char atBD[0xC0 - 0xBD];
    float m_atC0;                        // +0xC0, occlusion floor
    char atC4[0x12C - 0xC4];
    MicrophoneSettings m_microphoneSettings[3]; // +0x12C
};

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_distances(void *sample, float maxDistance, float minDistance);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_position(void *sample, float x, float y, float z);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_volume(void *sample, float volume);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_reverb_levels(void *sample, float dry, float wet);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_effects_level(void *sample3D, float level);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_occlusion(void *sample3D, float occlusion);
extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_playback_rate(void *sample);
typedef void (__stdcall *MilesSampleCallback)(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_init_sample(void *sample);
extern "C" __declspec(dllimport) int __stdcall AIL_set_3D_sample_info(void *sample3D, const MilesSoundInfo *info);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_type(void *sample, int format, unsigned int flags);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_address(void *sample, const void *start, unsigned int len);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_playback_rate(void *sample, int rate);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_loop_count(void *sample, int loops);
extern "C" __declspec(dllimport) MilesSampleCallback __stdcall AIL_register_EOS_callback(void *sample, MilesSampleCallback callback);
extern "C" __declspec(dllimport) int __stdcall AIL_set_sample_file(void *sample, const void *fileImage, int block);
extern "C" __declspec(dllimport) void __stdcall AIL_start_sample(void *sample);
extern "C" __declspec(dllimport) int __stdcall AIL_set_3D_sample_file(void *sample, const void *fileImage);
extern "C" __declspec(dllimport) MilesSampleCallback __stdcall AIL_register_3D_EOS_callback(void *sample, MilesSampleCallback callback);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_loop_count(void *sample, int loops);
extern "C" __declspec(dllimport) void __stdcall AIL_start_3D_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_playback_rate(void *sample, int rate);
extern float g_00DBA4FC;
extern float g_Va00BBDA30;

struct Rva0005A084Element { int m_value; };
typedef _STL::vector<Rva0005A084Element> Rva0005A084Vector;

extern "C" __declspec(dllimport) void __stdcall AIL_lock_mutex();
extern "C" __declspec(dllimport) void __stdcall AIL_unlock_mutex();

// Miles global-mutex scope; its out-of-line constructor is rowed at
// 0x00050E52 and the flag-gated unlock at 0x00050E62.
// The stream map's insert binds the folded helper at 0x004DA240 under the
// ledger's KeyToBucketMap view (NameKeyGeneratorMapInsert.cpp).
class NameKeyGenerator
{
public:
    class KeyToBucketMap
    {
    public:
        struct value_type
        {
            value_type(unsigned int f, void *s) : first(f), second(s) {}
            unsigned int first;
            void *second;
        };
        struct insert_result
        {
            void *first;
            KeyToBucketMap *second;
            bool inserted;
        };
        insert_result insert(const value_type &value);
    };
};

class AILMutexScope {
public:
    AILMutexScope() { AIL_lock_mutex(); m_locked = true; }
    ~AILMutexScope() { if (m_locked) AIL_unlock_mutex(); }
    void unlock(void) { if (m_locked) { AIL_unlock_mutex(); m_locked = false; } }
private:
    bool m_locked;
};

// Miles handle -> PlayingAudio maps at +0xB98/+0xBAC/+0xBC0. The mapped
// value is the raw PlayingAudio pointer (node +8); it is viewed as void *
// so the lookup binds the pinned folded _M_find at 0x002888D4.
typedef _STL::hash_map<unsigned int, void *> MilesHandleMap;

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()(T value) const;
	};

	template <class T> struct equal_to
	{
		bool operator()(const T &left, const T &right) const;
	};
}

// File name -> UnicodeString text map at +0x9E8 (value at node +8 is read
// with StringBase<unsigned short>::isEmpty and queued into a UnicodeString
// vector); its find is the folded hashtable helper at 0x0041534B.
typedef _STL::hash_map<AsciiString, UnicodeString,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > MilesFileTextMap;

class MilesMutexGuard {
public:
    MilesMutexGuard(void *mutex, int defer);
    ~MilesMutexGuard();
    bool rva00041037(int timeout);       // waits up to timeout ms for the lock
private:
    void *m_mutex;
    bool m_held;
};

// TheGameLODManager (0x00DFE144): +0x1770 audio LOD level, per-level
// 8-byte settings at +0x218 whose first word is the ambient stream cap.
struct AudioLODSettings {
    unsigned short m_maxAmbientStreams;
    char at02[2];
    unsigned char m_at04;    // +0x04, Dolby provider allowed (0x51525)
    char at05[3];
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

// The list erase is rowed at 0x00054AA1 under the target-neutral
// OpaqueRefElement4 instantiation, which ICF shares with every four-byte
// owning-ref list; PlayingAudioList erases through that view.
typedef _STL::list<OpaqueRefElement4> OpaqueRefList;

// 0x90-byte AudioEventRTS copies queued per view type at +0xE0, under the
// ledger's established element name (its virtual destructor is rowed at
// 0x002D9A43); +0x0C is the event's playing handle. Their range erase is
// the rowed 0x00056B72.
struct BfmeStringTailRecord144 {
    virtual ~BfmeStringTailRecord144();
    char at04[0x0C - 0x04];
    unsigned int m_playingHandle;  // +0x0C
    char at10[0x88 - 0x10];
    float m_at88;
    bool m_at8C;
    char at8D[3];
};
typedef _STL::vector<BfmeStringTailRecord144> QueuedAudioEvents;
template<> QueuedAudioEvents::iterator QueuedAudioEvents::erase(iterator first, iterator last);

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

// Address-derived callee view for the tree lookup used at 0x0005B1C2.
class Rva001F8437 {
public:
    void *rva001F8437(const AsciiString &key);
};

// Existing donor-derived alias of the rowed STLport tree increment worker.
struct BfmeNode1105;
BfmeNode1105 *__cdecl bfmeNext1105(BfmeNode1105 *node);

// Rowed at 0x0005F279 under its address-derived host.
class Rva0005F279Host { public: void rva0005F279(void); };

// MilesAudioManager's primary base: the vftable at +0x00 starts with the
// scalar deleting destructor (0x00061AA1), and the Snapshot subobject sits at
// +0x0C (its vftable holds the 0x0005D41D destructor thunk, loadPostProcess
// 0x000587C6, the name getter 0x000518B2 and the xfer 0x0005E3E5), so the
// base before it is SubsystemInterface's 12 bytes: vptr, +0x04 flag and the
// +0x08 name (layout of the rowed SubsystemInterface constructor 0x001B4E63).
class SubsystemInterface {
public:
    virtual ~SubsystemInterface();
private:
    bool m_flag;
    AsciiString m_name;
};

class MilesAudioManager : public SubsystemInterface, public Snapshot {
public:
    // Virtual slots 0..74 are not named here; slot 75 (+0x12C) looks an
    // event info up by name.
    virtual void init(); virtual void slot02(); virtual void slot03(); virtual void slot04();
    virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void rva00061C87(unsigned int viewMask);
    virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
    virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
    virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
    virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
    virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
    virtual void slot55(); virtual bool slot56(unsigned int soundClass); virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64();
    virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
    virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74();
    virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &name) const;
    // Slots 76..106 are not named here; slot 107 (+0x1AC, retail vftable
    // 0x007C55B0) is the rowed 0x000516EF.
    virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79(); virtual void slot80();
    virtual void slot81(); virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85();
    virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89(); virtual void slot90();
    virtual void slot91(); virtual void slot92();
    // Slots 93/94 (+0x174/+0x178, vftable entries 0x007C5724/0x007C5728):
    // set or (level 1.0) drop a trigger area's audio level.
    virtual void rva0005824D(PolygonTrigger *trigger, float level);
    virtual void rva000551C2(PolygonTrigger *trigger);
    virtual void slot95();
    virtual void slot96(); virtual void slot97();
    // Slot 98 (+0x188, retail vftable entry 0x007C5738).
    virtual void onAudioLODChanged(void);
    virtual void slot99(); virtual void slot100();
    virtual void slot101(); virtual void slot102(); virtual void slot103(); virtual void slot104(); virtual void slot105();
    virtual void slot106();
    virtual bool rva000516EF(const Coord3D *pos);
    virtual void slot108(); virtual void slot109();
    // Slot 110 (+0x1B8), the first call init() makes.
    virtual void rva000541DB(void);
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
    void rva0005407E(INI *ini);
    void rva000540A7(INI *ini);
    unsigned char rva00054120(INI *ini);
    bool rva00061BD2(int unused);
    void rva0006179C(int opaque);
    AsciiString rva00054714(void);
    PlayingAudioList::iterator rva000544CB(int viewType, int musicSystem, int filter);
    PlayingAudioList::iterator rva0005442A(int viewType, int musicSystem, int filter);
    void rva00057297(Rva00051107AudioRequest &request);
    bool rva000570C8(AudioEventRTS *event);
    void addUnownedAudioEventInfo(AudioEventInfo *eventInfo);
    AudioEventRTS *findLowestPrioritySound(AudioEventRTS *event);
    bool killLowestPrioritySoundImmediately(AudioEventRTS *event);
    float rva0005A9F8(void *ref, int a, int b);
    float rva00059AD0(void *event, int a);
    void unmapPhysicalHandle(unsigned int handle);  // WorldBuilder name (0x000578B3)
    void rva00057948(const void *input);
    void rva000577E3(unsigned int affect, unsigned int viewMask, bool value);
    // Ledger rows name it (refreshAll/rva00052048 share its this).
    class GlobalVolumeData {
    public:
        static void setGlobalSystemVolume(int volumeType, float volume);
        void reset(void);
        void rva00052048(int index);
        void rva00052015(int arg);
        void refreshAll(void);
        float rva0005910F(AudioEventRTS *event);
        // Distance attenuation of +0x94 (WB 0x77A260, unnamed) from the
        // per-view microphone settings and the camera-to-microphone offset.
        void rva0005213E(const MicrophoneSettings *settings, const Coord3D *delta);

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
    void notifyOf2DSampleCompletion();
    void notifyOf3DSampleCompletion();
    void internalSetReverbRoomType(int roomType);
    bool shouldUseDolbyProvider();
    void rva0005452B(void);
    void rva000606CE(bool accelerated);
    void rva00060123(unsigned int viewMask);
    void rva00056FD9(unsigned int viewMask);
    void rva0005B256(Xfer *xfer, PlayingAudioRef &playing, int *unused);
    bool rva000613A9(unsigned int handle);
    bool rva006AD9B0(void);    // 0x00059646, cached reinitialize setting
    void rva00060309(void);
    void rva0006047C(void);
    void rva000544EB(void);
    void startPendingMusicTracks(void);
    void openDevice(void);
    void removeCurrentlyPlayingMusic(int viewType, int arg);
    void rva00057151(int viewType, int musicSystem, int resume);
    void moveDownMusicSystems(int viewType, MusicSystem newMusicSystem, int arg, int resume);
    void rva0005774F(int viewType, int musicSystem, int arg);
    void rva0005876E(int viewType, int musicSystem, int arg, int resume);
    bool addAudioEventMusic(BfmePoolRef10 &event, int requestType, int append);
    int pushMusicEventInternal(AudioEventRTS *event, int arg1, int arg2, int append);
    int addResumeOrPushMultisound(AudioEventRTS *event, int requestType, int arg2, int arg3, int arg4, int arg5);
    BfmePoolRef10 rva0005286A(AudioEventRTS *event, int arg);
    void rva000592B8(AudioEventRTS *event);
    bool shouldPlayLocally(const AudioEventRTS *event);
    void rva00055A58(int viewType, int musicSystem, int arg, int flag);
    void rva00055B40(int viewType, int musicSystem, int arg);
    void rva000567F4(int viewType, int musicSystem, int arg);
    void rva000568CE(int viewType, int musicSystem, int arg);
    void rva000569A8(int viewType, int musicSystem, int arg, int flag);
    Rva00051107AudioRequest *rva00051107(void);
    void processRequest(Rva00051107AudioRequest *req, bool *removeRequest);
    void processRequestList(void);
    void deleteAudioRequest(void *req);
    bool rva00053606(Rva00051107AudioRequest *req);
    void rva00053646(Rva00051107AudioRequest *req, bool *removeRequest);
    void playAudioEvent(Rva00051107AudioRequest *req);
    void rva0005FA3C(unsigned int handle);
    void processAmbientStreams(PlayingAudioList::iterator *streams);
    void processPushMusicRequest(Rva00051107AudioRequest *req);
    PlayingAudioRef allocatePlayingAudio(void);
    void processPopMusicRequest(Rva00051107AudioRequest *req);
    void onPlayingAudioDeleted(PlayingAudio &playingAudioBeingDeleted);
    void releaseMilesHandles(PlayingAudio &playing);
    void moveUpMusicSystems(int newMusicSystem, int viewType, int arg);
    void rva0005AC61(int viewType, int newMusicSystem, int arg);
    bool startNextLoop(PlayingAudioRef &looping);
    void getAppropriateSampleHandleForPlayingAudio(PlayingAudioRef &playing, void **sample, void **sample3D);

    void *get2DSampleHandleForPlayingAudio(void *playing);
    void *get3DSampleHandleForPlayingAudio(PlayingAudioRef &playing);
    void prep3DSample(PlayingAudioRef &playing, const Coord3D *pos);
    void initFilters3D(PlayingAudioRef &playing, const Coord3D *pos);
    void setOcclusionLevels(PlayingAudioRef &playing, const Coord3D *pos);
    float rva00053854(const Coord3D *pos);
    void rva00055C5D(PlayingAudioRef &playing, bool *result);
    void rva00052FA0(PlayingAudioRef &playing);
    void rva000581FA(const Rva0005BA08InfoRef &info, int viewType);
    void rva000535A6(PlayingAudioRef &playing);
    void pauseResumeSound(PlayingAudioRef &playing);
    void prepSample(void *playing);
    BfmeEventPositionView Rva0005160FGet(AudioEventRTS *event, bool &valid);
    bool playSample(PlayingAudioRef &playing);
    bool playSample3D(PlayingAudioRef &playing);
    bool playSample2DOr3DUsingCallbackBuffers(PlayingAudioRef &playing, void *sample, void *sample3D);

    void rva000564C0(unsigned int sample);
    void rva0005653C(unsigned int sample3D);
    void rva0005DB6C(const AsciiString &fileName);
    void rva000565B8(unsigned int stream);

    // WorldBuilder names its destructor MilesAudioManager::LoopBuffer::~LoopBuffer.
    struct LoopBuffer;

    // WorldBuilder name; refills a loop buffer's play buffer up to position.
    void transferBytesToPlayBuffer(LoopBuffer &buffer, unsigned int position);
    // WorldBuilder name; binds a cached file to a loop buffer.
    void putFileIntoLoopBuffer(LoopBuffer *buffer, const AudioFileContainer &file, int arg);
    // WorldBuilder name; hands a finished loop buffer's handles back.
    void cleanUpLoopBuffer(LoopBuffer *buffer);
    // WorldBuilder name (retail 0x0005DD40).
    void checkForNaturalSoundCompletion(PlayingAudioRef &playing);
    // WorldBuilder name (retail 0x0005D734, pinned).
    unsigned int addOrResumeAudioEvent(AudioEventRTS *event, int a, int b, int c, int d);
    // WorldBuilder name; restarts, requeues or retires a finished sound.
    void processAudioCompletion(PlayingAudioRef &completedAudio);
    // WorldBuilder name; maps, configures and starts a stream.
    void playAndStoreStream(PlayingAudioRef &playing, const Rva0010FFA2Packet *resumePosition);
    void rva0005EFE9(void);
    void putPlayingMusicOnStack(int viewType, int arg);
    void rva00059CE6(PlayingAudioRef &looping);
    void rva0005AA72(PlayingAudioRef &playing);

private:
    // Provider teardown at 0x00053352 and selection at 0x000604A3.
    void unselectProvider(void);
    void selectProvider(bool accelerated);
public:
    unsigned int getProviderIndex(const AsciiString &providerName) const;
    void init3DSamplePools();
    void createListener();
protected:
    virtual void loadPostProcess(void);
private:
    AudioSettings *m_audioSettings;      // +0x10 (Zero Hour name)
    char at14[0x3C - 0x14];
    AudioAreaCorner m_corners[5];        // +0x3C, entries 1..4 used by 0x53854
    float m_at8C;                        // +0x8C, distance occlusion scale
    float m_frameDuration;
    int m_at94;                          // +0x94, zeroed by 0x61C87
    Rva00051107AudioRequestList m_audioRequests;    // +0x98
    Rva00051107AudioRequestSet m_requestSet;        // +0x9C
    char atB0[0xBC - 0xB0];
    Rva00059FBBMap m_allAudioEventInfo;  // +0xBC
    unsigned int m_nextHandle;           // +0xD0, next playing handle (0x0005B256)
    char atD4[0xE0 - 0xD4];
    QueuedAudioEvents m_queuedEvents[3];  // +0xE0, per view type (0x60123)
    char at104[0x12C - 0x104];
    // Per-view GlobalVolumeData records, 0x1C4 apart in retail (0x61C87).
    char m_volumeData[3][0x1C4];         // +0x12C
    int m_at678;                         // +0x678, compared with event view types
    char at67C[0x68C - 0x67C];
    int m_at68C;                         // +0x68C, zeroed by 0x60309
    unsigned int m_at690;                // +0x690, per-view-type bits 0x61C87 clears
    unsigned int m_at694;
    unsigned int m_at698;                // +0x698, per-view-type bits processAudioCompletion clears
    unsigned short m_maxAmbientStreams;  // +0x69C
    char at69E[0x6A4 - 0x69E];
    bool m_at6A4;                        // +0x6A4
    char at6A5;
    bool m_forceHeadphones;             // +0x6A6, provider speaker override
    bool m_at6A7;                        // +0x6A7, read by 0x52F4C and 0x53AFA
    bool m_at6A8;
    char at6A9;
    bool m_at6AA;                        // +0x6AA, retest areas on every call (0x55C5D)
    bool m_at6AB;                        // +0x6AB, set by loadPostProcess
    bool m_at6AC;                        // +0x6AC, cleared by loadPostProcess
    char at6AD[0x6B4 - 0x6AD];
    unsigned int m_at6B4[3];             // +0x6B4 per-view-type affect masks
    unsigned int m_at6C0[3];             // +0x6C0
    // Zero Hour's ProviderInfo array; unselectProvider (0x53352) indexes it
    // by m_selectedProvider and 0x607BB compares the selected name.
    struct ProviderInfo { AsciiString name; void *id; int isValid; };
    ProviderInfo m_provider3D[64];       // +0x6CC
    unsigned int m_providerCount;        // +0x9CC
    unsigned int m_selectedProvider;     // +0x9D0, -1 when none
    void *m_mutex;                       // +0x9D4
    char at9D8[0x9E8 - 0x9D8];
    MilesFileTextMap m_fileText;         // +0x9E8
    _STL::vector<UnicodeString> m_pendingFileText;  // +0x9FC
    _STL::vector<AsciiString> m_unknownFileNames;   // +0xA08
    _STL::set<AsciiString> m_atA14[3];   // +0xA14, per view type (0x61C87)
    _STL::list<void *> m_availableSamples;    // +0xA38 (Zero Hour's name)
    _STL::list<void *> m_available3DSamples;  // +0xA3C (Zero Hour's name)
    PlayingAudioList m_playingSounds;    // +0xA40
    PlayingAudioList m_playing3DSounds;  // +0xA44
    PlayingAudioList m_playingStreams;   // +0xA48
    MusicStack m_musicStack[3][2];       // +0xA4C
    MusicSystem m_activeMusicSystem[3];  // +0xB3C
    PlayingAudioRef m_playingMusic[3];   // +0xB48, the active system's stream per view type
    _STL::vector<AudioTriggerArea> m_triggerAreas;  // +0xB54, scanned by 0x55C5D
    _STL::vector<AudioTriggerAreaSave> m_savedTriggerAreas;  // +0xB60, resolved by loadPostProcess
    char atB6C[0xB78 - 0xB6C];           // +0xB6C, cleared through the rowed 0x00054B9A
    char atB78[0xB8C - 0xB78];           // +0xB78, cleared through the rowed 0x00056DA2
    AudioFileCache *m_audioFileCache;    // +0xB8C (WorldBuilder requestFile receiver)
    void *m_atB90;                       // +0xB90, handed to the stream opener 0x000A8D0B
    PlayingAudioList m_completedAudio;   // +0xB94, filled by the EOS handlers
    MilesHandleMap m_sampleMap;          // +0xB98
    MilesHandleMap m_3DSampleMap;        // +0xBAC
    MilesHandleMap m_streamMap;          // +0xBC0
    LoopBuffer *m_loopBuffers;           // +0xBD4 (WB assert name)
    int m_numLoopBuffers;                // +0xBD8
    void *m_loopBufferThread;            // +0xBDC, CreateThread handle
    bool m_atBE0;                        // +0xBE0, stops the 0x5EFE9 thread loop
    char atBE1[0xBE4 - 0xBE1];
    int m_atBE4;                         // +0xBE4, reverb room type (0x530DF zeroes it)
    char atBE8[0xBEC - 0xBE8];
    unsigned int m_atBEC;                // +0xBEC, view types reset since the last update
    int m_selectedSpeakerType;          // +0xBF0, provider-selection speaker type
    char atBF4[0xBF8 - 0xBF4];
    __int64 m_atBF8;                     // +0xBF8, _time64 of the last device open
};
class GameMessageList;
class GameMessage { public:void friend_setList(GameMessageList *);};
class Rva000A8AEE {public:void rva000A8AEE(float);};

class Rva0036CA00Str;
class Rva00058B90 {public:void rva00058B90(const Rva0036CA00Str &);};
class Rva00050D6C {public:int rva00050D6C();};
class Rva000A8A98 {public:int rva000A8A98();};
float GetGameAudioRandomValueReal(float,float,char*,int);
#define MILES_AUDIO_MANAGER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\MilesAudioDevice\\MilesAudioManager.cpp"
void __stdcall setStreamCompleted(void *);
int getAppropriateStreamLoopCount(int,AudioEventRTS*);
void MilesAudioManager::playAndStoreStream(PlayingAudioRef &playing, const Rva0010FFA2Packet *resumePosition)
{
    PlayingAudio *audio = playing.get();
    void *stream = &audio->m_at0C;
    AudioEventInfo *const &info = audio->m_event->m_info;
    {
        AILMutexScope lock;
        ((NameKeyGenerator::KeyToBucketMap *)&m_streamMap)->insert(
            NameKeyGenerator::KeyToBucketMap::value_type(((Rva000A8A98 *)stream)->rva000A8A98(), playing.get()));
    }
    if (!resumePosition) {
        ((Rva000A8B23 *)stream)->rva000A8B23(getAppropriateStreamLoopCount(0, audio->m_event.operator->()));
    }
    ((Rva000A8B4B *)stream)->rva000A8B4B((int)setStreamCompleted);
    rva00053AFA(&playing);
    if (resumePosition)
        ((Rva000A8C6E *)stream)->rva000A8C6E(resumePosition);
    else if (info->m_control & 4) {
        float startPosition = GetGameAudioRandomValueReal(0.0f, 1.0f, MILES_AUDIO_MANAGER_FILE, 12958);
        ((Rva000A8B31 *)stream)->rva000A8B31(startPosition, 0);
    } else
        ((Rva000A8B31 *)stream)->rva000A8B31(0.0f, 0);
    rva000535A6(playing);
    if (info->m_atB0 == 0) {
        AudioEventRTS *event = audio->m_event.operator->();
        int viewType = event->m_viewType;
        MusicSystem musicSystem = event->m_musicSystem;
        if (musicSystem == m_activeMusicSystem[viewType])
            m_playingMusic[viewType] = playing;
        else
            ((Rva00058B90 *)&m_musicStack[viewType][musicSystem])->rva00058B90(*(const Rva0036CA00Str *)&playing);
        return;
    }
    if (!info->m_channelVolumes.empty())
        rva000581FA(*reinterpret_cast<const Rva0005BA08InfoRef *>(&info), audio->m_event->m_viewType);
    m_playingStreams.push_back(playing);
    if ((unsigned char)((Rva00050D6C *)playing.get())->rva00050D6C())
        ((MilesStreamRef *)stream)->rva000A8AC0();
    else
        ((Rva000A8ACC *)stream)->rva000A8ACC();
}
void MilesAudioManager::rva00052FA0(PlayingAudioRef &playing)
{
    switch (playing->m_type) {
    case 0:
    case 1: {
        void *sample = get2DSampleHandleForPlayingAudio(&playing);
        if (sample) {
            if (m_at6A7) {
                float base = playing->m_event->m_info->m_reverbWetLevel;
                float wet = getGlobalReverbMultiplier() * base;
                AIL_set_sample_reverb_levels(sample, playing->m_event->m_info->m_reverbDryLevel, wet);
            } else {
                AIL_set_sample_reverb_levels(sample, 1.0f, 0.0f);
            }
        }
        break;
    }
    case 2:
    case 3: {
        void *sample3D = get3DSampleHandleForPlayingAudio(playing);
        if (sample3D) {
            float level;
            if (m_at6A7) {
                float base = playing->m_event->m_info->m_reverbWetLevel;
                level = getGlobalReverbMultiplier() * playing->m_at34 * base;
            } else
                level = 0.0f;
            AIL_set_3D_sample_effects_level(sample3D, level);
        }
        break;
    }
    case 4:
        if (m_at6A7) {
            float base = playing->m_event->m_info->m_reverbWetLevel;
            float wet = getGlobalReverbMultiplier() * base;
            playing->m_at0C.rva000A8B04(playing->m_event->m_info->m_reverbDryLevel, wet);
        } else {
            playing->m_at0C.rva000A8B04(1.0f, 0.0f);
        }
        break;
    }
}
void MilesAudioManager::rva0005DB6C(const AsciiString &fileName)
{
    if (fileName.isEmpty())
        return;
    MilesMutexGuard guard(&m_mutex, 0);
    MilesFileTextMap::iterator it = m_fileText.find(fileName);
    if (it == m_fileText.end())
        m_unknownFileNames.push_back(fileName);
    else if (!(*it).second.isEmpty())
        m_pendingFileText.push_back((*it).second);
}
// Native 5F2BB..5FA3C RET4; WorldBuilder callgraph names processAmbientStreams.
class Rva005F69C4 {public:void rva005F69C4(unsigned int);};
class Rva0005117B {public:float rva0005117B(float);};
class Rva000554A9 {public:void *rva000554A9(void *);};
struct AmbientInfoNameView {virtual void slot0();virtual const AsciiString &slot1();};
static __forceinline bool ambientSameName(AudioEventInfo *a, AudioEventInfo *b)
{
 const AsciiString &left=reinterpret_cast<AmbientInfoNameView*>(a)->slot1();
 const AsciiString &right=reinterpret_cast<AmbientInfoNameView*>(b)->slot1();
 return reinterpret_cast<const StringBase<char> &>(right).compare(reinterpret_cast<const StringBase<char> &>(left))==0;
}
void MilesAudioManager::processAmbientStreams(PlayingAudioList::iterator *streams)
{
 unsigned int view=1<<m_at678;
 if((m_at690&view)||(m_at694&view)||!slot56(16))return;
 QueuedAudioEvents &events=m_queuedEvents[m_at678];
 QueuedAudioEvents::iterator eventEnd=events.end();
 PlayingAudioList::iterator end=m_playingStreams.end();
 float minimum=m_audioSettings->m_atB8;
 int fadeTime=m_audioSettings->m_at78;
 float bestVolume[2];
 QueuedAudioEvents::iterator bestEvent[2];
 float oldVolume[2];
 QueuedAudioEvents::iterator sameEvent[2];
 for(int init=0;init<2;++init){sameEvent[init]=eventEnd;oldVolume[init]=0;bestEvent[init]=eventEnd;bestVolume[init]=minimum;}
 bool hasExpired=false;
 for(QueuedAudioEvents::iterator event=events.begin();event!=eventEnd;++event) {
  AudioEventRTS *ev=reinterpret_cast<AudioEventRTS *>(event);
  float volume=rva00059AD0(ev,0);
  if(event->m_at8C) {
   event->m_at88+=m_frameDuration;
   if(event->m_at88>=fadeTime){hasExpired=true;continue;}
   volume*=1.0f-event->m_at88/fadeTime;
  }
  if(!(volume>=minimum))continue;
  bool same=false;
  for(int i=0;!same&&i<2;++i) {
   if(streams[i]!=end) {
    PlayingAudioRef playing=(*streams[i]);
    if(ambientSameName(ev->m_info,playing->m_event->m_info)) {
     same=true;
     if(volume>oldVolume[i]){oldVolume[i]=volume;sameEvent[i]=event;}
    }
   }
  }
  if(same)continue;
  for(int i=0;i<2;++i) {
   if(bestEvent[i]==eventEnd)break;
   if(ambientSameName(ev->m_info,reinterpret_cast<AudioEventRTS *>(bestEvent[i])->m_info)) {
    if(volume>bestVolume[i]) {
     if(i<1) {
      memcpy(&bestVolume[i],&bestVolume[i+1],(1-i)*sizeof(float));
      memcpy(&bestEvent[i],&bestEvent[i+1],(1-i)*sizeof(QueuedAudioEvents::iterator));
     }
     bestEvent[1]=eventEnd;bestVolume[1]=minimum;
     break;
    }else same=true;
   }
  }
  if(same)continue;
  for(int i=0;i<2;++i) {
   if(volume>bestVolume[i]) {
    for(int j=1;j>i;--j){bestVolume[j]=bestVolume[j-1];bestEvent[j]=bestEvent[j-1];}
    bestEvent[i]=event;bestVolume[i]=volume;
    break;
   }
  }
 }
 int used=0;
 bool stop[2];
 for(int i=0;i<2;++i) {
  if(streams[i]!=end){++used;stop[i]=false;}else stop[i]=true;
 }
 int available=m_maxAmbientStreams-used;
 bool done=false;
 while(used>0) {
  if(done)break;
  int weakest=-1;
  float low=3.402823466e38f;
  for(int i=0;i<2;++i) {
   if(!stop[i]) {
    float value=oldVolume[i];
    if(value>0.0f&&!(*streams[i])->m_at44)value+=m_audioSettings->m_at7C*0.01f;
    if(low>value){low=value;weakest=i;}
   }
  }
  if(weakest==-1)break;
  if(available>=0&&bestVolume[available]<=low)done=true;
  else {++available;--used;stop[weakest]=true;}
 }
 for(int i=0;i<2;++i) {
  if(streams[i]!=end) {
   PlayingAudioRef playing=*streams[i];
   playing->m_at44=stop[i];
   if(stop[i])playing->m_at30+=m_frameDuration;
   else {
    playing->m_at30-=m_frameDuration;
    if(playing->m_at30<0){playing->m_at30=0;playing->m_at45=false;}
    else playing->m_at45=true;
   }
  }
 }
 for(int i=0;i<2;++i) {
  if(streams[i]!=end) {
   PlayingAudioRef playing=*streams[i];
   float volume=reinterpret_cast<Rva002D94E4 *>(playing->m_event.get())->rva002D94E4()*oldVolume[i];
   if(playing->m_at44)volume*=reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30);
   if(volume<minimum) {
    playing->m_status=1;playing->m_event->m_at4C=true;
    reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(OpaqueRefList::iterator((OpaqueRefList::_Node *)streams[i]._M_node));
    streams[i]=end;
   } else {
    if(!playing->m_at44)volume*=reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30);
    volume*=reinterpret_cast<GlobalVolumeData *>(m_volumeData[m_at678])->rva0005910F(playing->m_event.get());
    reinterpret_cast<Rva000A8AEE *>(&playing->m_at0C)->rva000A8AEE(volume);
    if(m_at6A8)rva00052FA0(playing);
   }
  }
 }
 int candidate=0;
 for(int slot=0;available>0;++slot) {
  if(candidate>=2||bestEvent[candidate]==eventEnd||slot>=2)break;
  if(streams[slot]!=end)continue;
  PlayingAudioRef playing=allocatePlayingAudio();
  playing->m_event.rva00053D26(reinterpret_cast<BfmePoolHolder88 *>(new Rva0051D93(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(bestEvent[candidate]))));
  playing->m_event->m_ownerType=6;
  unsigned int handle=m_nextHandle++;
  reinterpret_cast<GameMessage *>(playing->m_event.get())->friend_setList(reinterpret_cast<GameMessageList *>(handle));
  playing->m_event->generatePlayInfo();playing->m_event->rva002D9ADC();
  reinterpret_cast<Weapon *>(playing->m_event.get())->setLeechRangeActive(false);
  AsciiString filename=playing->m_event->getFilename();
  reinterpret_cast<Rva000A8D0B *>(&playing->m_at0C)->rva000A8D0B(m_atB90,filename,0);
  playing->m_type=4;playing->m_at30=fadeTime-33.333332f;
  if(m_atBEC&(1<<m_at678)){playing->m_at30=0;playing->m_at45=false;}else playing->m_at45=true;
  rva0005DB6C(filename);
  float volume=reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30)*bestVolume[candidate];
  volume*=reinterpret_cast<GlobalVolumeData *>(m_volumeData[m_at678])->rva0005910F(playing->m_event.get());
  volume*=reinterpret_cast<Rva002D94E4 *>(playing->m_event.get())->rva002D94E4();
  reinterpret_cast<Rva000A8AEE *>(&playing->m_at0C)->rva000A8AEE(volume);
  reinterpret_cast<Rva000A8AD8 *>(&playing->m_at0C)->rva000A8AD8(reinterpret_cast<Rva002D94DD *>(playing->m_event.get())->rva002D94DD());
  rva00052FA0(playing);playAndStoreStream(playing,0);
  --available;++candidate;
 }
 if(hasExpired) {
  for(QueuedAudioEvents::iterator event=events.begin();event!=events.end();) {
   if(event->m_at88>=fadeTime){unmapPhysicalHandle(event->m_playingHandle);event=reinterpret_cast<QueuedAudioEvents::iterator>(reinterpret_cast<Rva000554A9 *>(&events)->rva000554A9(event));}
   else ++event;
  }
 }
 m_atBEC&=~(1<<m_at678);
}
