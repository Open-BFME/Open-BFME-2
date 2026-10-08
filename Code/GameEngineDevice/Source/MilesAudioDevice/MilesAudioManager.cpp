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
#include <vector>
#undef free
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

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

#include "../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

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

class AudioEventRTS {
public:
    bool isPositionalAudio(void) const;
    ObjectID getObjectID(void);
    unsigned int getSoundClass(void) const;
    bool hasMoreLoops(void) const;
    void rva002D9ADC(void);
    void advanceNextPlayPortion(void);
    // Inline in WorldBuilder too (its twin copies the read into a temp);
    // putFileIntoLoopBuffer's first reads go through it into a register.
    int getNextPlayPortion(void) const { return m_portionToPlayNext; }
    // Inline getter (WorldBuilder calls it on the +0x08 reference); the
    // loop-buffer refill's decay test reads through it.
    const AudioEventInfo *getAudioEventInfo(void) const { return m_info; }
    char at00[0x08];
    AudioEventInfo *m_info;  // +0x08 (owning ref in WB)
    int m_playingHandle;     // +0x0C, copied into a requeued loop's request
    char at10[0x30 - 0x10];
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
};

// Owning AudioEventRTS reference (its refcount base sits at event +0x88);
// the ledger's established name, assignment rowed at 0x00051971.
struct BfmePoolHolder88;

class BfmePoolRef10 {
public:
    AudioEventRTS *operator->(void) const { return m_ptr; }
    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
    void rva00053D26(BfmePoolHolder88 *p);  // assign from a raw event (0x00053D26)
    void rva000519BD(void);                 // release then null (0x000519BD)
private:
    AudioEventRTS *m_ptr;
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
    char at44[0x49 - 0x44];
    bool m_at49;                         // +0x49
    bool m_at4A;                         // +0x4A
    bool m_at4B;                         // +0x4B, set by 0x000535A6
    char at4C[0x4E - 0x4C];
    bool m_at4E;                         // +0x4E, m_at24 holds a position
};

// Retain-and-replace setter rowed at 0x000A8CE5 under its address-derived owner.
class Rva000A8C9B {
public:
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
        return req ? req->m_at08 : 0;
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
// WorldBuilder calls this AudioEventRTS::setExtraVolumeMultiplier; retail
// folded it to 0x00481FAF, rowed under this neutral float-slot name.
class Rva00481FAFFloatSlot { public: void store(float value); };
// Float-returning event query rowed at 0x002DA153; prep3DSample compares it
// with AudioSettings +0xB8 to treat a sound as global.
class Rva002DA153 { public: float rva002DA153(void); };
// Event pitch-shift multiplier (rowed 0x002D94DD, a const float product
// getter); initFilters3D scales the 3D playback rate by it when non-zero.
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

// Event position returned by the rowed 0x0005160F (zeros and false when the
// event is not positional); playSample3D hands it to prep3DSample.
struct BfmeEventPositionView : public Coord3D {};
// Info-reference parameter type of the split-out 0x000581FA.
struct Rva0005BA08InfoRef;

// AudioSettings view (Zero Hour's MilesAudioManager reads it through
// m_audioSettings at +0x10): +0x74 is an int distance, +0xB8 a float limit.
// Per-view record of AudioSettings, indexed by the manager's +0x678 view
// type; setOcclusionLevels divides the listener distance by +0x00 when it is
// within +0x04 (squared).
struct AudioViewSettings {
    float m_at00;
    float m_at04;
    char at08[0x48 - 0x08];
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
    char at7C[0x80 - 0x7C];
    unsigned int m_at80;                 // +0x80, handed to the file cache's 0xA77D9
    char at84[0x8C - 0x84];
    unsigned int m_at8C;                 // +0x8C, over +0x90 the loop-buffer thread's sleep
    unsigned int m_at90;                 // +0x90
    char at94[0xB0 - 0x94];
    float m_atB0;                        // +0xB0, position change 0x55C5D ignores
    int m_atB4;                          // +0xB4, processRequest's preload limit
    float m_atB8;
    bool m_atBC;                         // +0xBC, disables occlusion
    char atBD[0xC0 - 0xBD];
    float m_atC0;                        // +0xC0, occlusion floor
    char atC4[0x15C - 0xC4];
    AudioViewSettings m_viewSettings[3]; // +0x15C
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

// The list erase is rowed at 0x00054AA1 under the target-neutral
// OpaqueRefElement4 instantiation, which ICF shares with every four-byte
// owning-ref list; PlayingAudioList erases through that view.
typedef _STL::list<OpaqueRefElement4> OpaqueRefList;

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

class MilesAudioManager {
public:
    // Virtual slots 0..74 are not named here; slot 75 (+0x12C) looks an
    // event info up by name.
    virtual void slot00(); virtual void init(); virtual void slot02(); virtual void slot03(); virtual void slot04();
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
    // Slots 76..106 are not named here; slot 107 (+0x1AC, retail vftable
    // 0x007C55B0) is the rowed 0x000516EF.
    virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79(); virtual void slot80();
    virtual void slot81(); virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85();
    virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89(); virtual void slot90();
    virtual void slot91(); virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
    virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99(); virtual void slot100();
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
    void rva00057297(Rva00051107AudioRequest &request);
    bool rva000570C8(AudioEventRTS *event);
    void addUnownedAudioEventInfo(AudioEventInfo *eventInfo);
    AudioEventRTS *findLowestPrioritySound(AudioEventRTS *event);
    bool killLowestPrioritySoundImmediately(AudioEventRTS *event);
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
    void openDevice(void);
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
    void processRequest(Rva00051107AudioRequest *req, bool *removeRequest);
    void processRequestList(void);
    void deleteAudioRequest(void *req);
    bool rva00053606(Rva00051107AudioRequest *req);
    void rva00053646(Rva00051107AudioRequest *req, bool *removeRequest);
    void playAudioEvent(Rva00051107AudioRequest *req);
    void rva0005FA3C(unsigned int handle);
    void processPushMusicRequest(Rva00051107AudioRequest *req);
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
    void rva0005EFE9(void);
    void putPlayingMusicOnStack(int viewType, int arg);
    void rva00059CE6(PlayingAudioRef &looping);
    void rva0005AA72(PlayingAudioRef &playing);

private:
    char at04[0x10 - 0x04];
    AudioSettings *m_audioSettings;      // +0x10 (Zero Hour name)
    char at14[0x3C - 0x14];
    AudioAreaCorner m_corners[5];        // +0x3C, entries 1..4 used by 0x53854
    float m_at8C;                        // +0x8C, distance occlusion scale
    char at90[0x98 - 0x90];
    Rva00051107AudioRequestList m_audioRequests;    // +0x98
    Rva00051107AudioRequestSet m_requestSet;        // +0x9C
    char atB0[0xBC - 0xB0];
    Rva00059FBBMap m_allAudioEventInfo;  // +0xBC
    char atD0[0x678 - 0xD0];
    int m_at678;                         // +0x678, compared with event view types
    char at67C[0x69C - 0x67C];
    unsigned short m_maxAmbientStreams;  // +0x69C
    char at69E[0x6A4 - 0x69E];
    bool m_at6A4;                        // +0x6A4
    char at6A5[0x6A7 - 0x6A5];
    bool m_at6A7;                        // +0x6A7, read by 0x52F4C and 0x53AFA
    char at6A8[0x6AA - 0x6A8];
    bool m_at6AA;                        // +0x6AA, retest areas on every call (0x55C5D)
    char at6AB[0x6B4 - 0x6AB];
    unsigned int m_at6B4[3];             // +0x6B4 per-view-type affect masks
    unsigned int m_at6C0[3];             // +0x6C0
    char at6CC[0x9D4 - 0x6CC];
    void *m_mutex;                       // +0x9D4
    char at9D8[0x9E8 - 0x9D8];
    MilesFileTextMap m_fileText;         // +0x9E8
    _STL::vector<UnicodeString> m_pendingFileText;  // +0x9FC
    _STL::vector<AsciiString> m_unknownFileNames;   // +0xA08
    char atA14[0xA38 - 0xA14];
    _STL::list<void *> m_availableSamples;    // +0xA38 (Zero Hour's name)
    _STL::list<void *> m_available3DSamples;  // +0xA3C (Zero Hour's name)
    PlayingAudioList m_playingSounds;    // +0xA40
    PlayingAudioList m_playing3DSounds;  // +0xA44
    PlayingAudioList m_playingStreams;   // +0xA48
    MusicStack m_musicStack[3][2];       // +0xA4C
    MusicSystem m_activeMusicSystem[3];  // +0xB3C
    char atB48[0xB54 - 0xB48];
    _STL::vector<AudioTriggerArea> m_triggerAreas;  // +0xB54, scanned by 0x55C5D
    char atB60[0xB8C - 0xB60];
    AudioFileCache *m_audioFileCache;    // +0xB8C (WorldBuilder requestFile receiver)
    char atB90[0xB94 - 0xB90];
    PlayingAudioList m_completedAudio;   // +0xB94, filled by the EOS handlers
    MilesHandleMap m_sampleMap;          // +0xB98
    MilesHandleMap m_3DSampleMap;        // +0xBAC
    MilesHandleMap m_streamMap;          // +0xBC0
    LoopBuffer *m_loopBuffers;           // +0xBD4 (WB assert name)
    int m_numLoopBuffers;                // +0xBD8
    void *m_loopBufferThread;            // +0xBDC, CreateThread handle
    bool m_atBE0;                        // +0xBE0, stops the 0x5EFE9 thread loop
};

// Rowed under address-derived names at 0x00051038 (pinned) and 0x00050FE3;
// the destructor below hands its Miles handles back through them.
class Rva0005F279Elem { public: bool rva00051038() throw(); bool rva0005106A(); };
// The guarded 2D and 3D playing-sample count decrements (WorldBuilder's
// notifyOf2DSampleCompletion/notifyOf3DSampleCompletion), rowed at 0x000514EB
// and 0x000514FB under an address-derived owner.
class Rva000514EB { public: void rva000514EB(); void rva000514FB(); };
class Rva00050FE3 { public: void rva00050FE3() throw(); };
// The loop buffer's play position, start and loop count, rowed at 0x00050FFD,
// 0x00050FC9 and 0x00051017 under address-derived names.
class Rva00050FFD { public: unsigned int rva00050FFD(); };
class Rva00050FC9 { public: void rva00050FC9(); };
class Rva00051017 { public: void rva00051017(int loopCount); };

// Reference at +0x0C that drops the referent's count at +0x88 on destruction.
struct LoopBufferSource {
    char at00[0x88];
    OpaqueRefCounted m_ref;              // +0x88
};
class LoopBufferSourceRef {
public:
    LoopBufferSourceRef() : m_source(0) {}
    ~LoopBufferSourceRef() { if (m_source) m_source->m_ref.Release_Ref(); }
private:
    LoopBufferSource *m_source;
};

// 72-byte retail record (WB's debug record is 84 bytes); +0x14 named by the
// WB assert in onPlayingAudioDeleted, m_isValid by the one in ~LoopBuffer.
struct MilesAudioManager::LoopBuffer {
    LoopBuffer();
    ~LoopBuffer();

    bool m_isValid;                      // +0x00 (WB assert name)
    char at01;
    bool m_is3D;                         // +0x02 selects the handle below
    bool m_at03;                         // +0x03, completion check pending
    void *m_3DSample;                    // +0x04
    void *m_sample;                      // +0x08
    LoopBufferSourceRef m_source;        // +0x0C
    bool m_at10;                         // +0x10
    PlayingAudio *m_playingAudio;        // +0x14
    unsigned char *m_at18;               // +0x18, freed with delete[]
    unsigned int m_playBufferSize;       // +0x1C (WB assert name)
    Rva00690FF0Handle m_at20;            // +0x20
    Rva00690FF0Handle m_at24;            // +0x24
    Rva00690FF0Handle m_at28;            // +0x28
    unsigned int m_at2C;                 // +0x2C
    unsigned int m_at30;                 // +0x30
    unsigned int m_endOfLastCopy;        // +0x34 (WB assert name)
    unsigned int m_at38;                 // +0x38
    unsigned int m_at3C;                 // +0x3C
    unsigned int m_at40;                 // +0x40
    bool m_at44;                         // +0x44
};

// Retail 0x00052568, the element constructor init()'s new[] hands to the
// vector constructor iterator: an empty, invalid 3D buffer.
MilesAudioManager::LoopBuffer::LoopBuffer()
    : m_isValid(false), at01(0), m_is3D(true), m_at03(false), m_3DSample(0), m_sample(0),
      m_at10(false), m_playingAudio(0), m_at18(0), m_playBufferSize(0),
      m_at2C(0), m_at30(0), m_endOfLastCopy(0), m_at38(0), m_at3C(0), m_at40(0), m_at44(false)
{
}

// Retail 0x000525E5 (WorldBuilder twin 0x0077AF80, which asserts !m_isValid
// first): release the Miles handles unless 0x51038 already has, then free the
// +0x18 buffer.
MilesAudioManager::LoopBuffer::~LoopBuffer()
{
    if (!((Rva0005F279Elem *)this)->rva00051038())
        ((Rva00050FE3 *)this)->rva00050FE3();
    if (m_at18) {
        delete[] m_at18;
        m_at18 = 0;
    }
}

// ?deleteLoopBuffers@@YAXPAULoopBuffer@MilesAudioManager@@@Z absent-from-retail
// Emits the vector deleting destructor (retail 0x0005277C) that
// ~MilesAudioManager's delete[] m_loopBuffers calls; that destructor is not
// rowed yet.
void deleteLoopBuffers(MilesAudioManager::LoopBuffer *loopBuffers)
{
    delete[] loopBuffers;
}

// Retail 0x0005E98E (WorldBuilder twin 0x0077B150): steps the source event's
// play portion, queues the next portion's file, then binds file to the play
// buffer: its sound data runs from m_at30 to m_at2C within m_at20's image.
void MilesAudioManager::putFileIntoLoopBuffer(LoopBuffer *buffer, const AudioFileContainer &file, int arg)
{
    BfmePoolRef10 &source = (BfmePoolRef10 &)buffer->m_source;
    source->m_at50 = true;
    if (source->getNextPlayPortion() != 2 || arg == 1)
        source->advanceNextPlayPortion();
    source->rva002D9ADC();
    if (source->getNextPlayPortion() == 2) {
        if (!buffer->m_at28.isValid())
            reinterpret_cast<Rva00691040Handle &>(buffer->m_at28) = m_audioFileCache->requestFile(source, 0);
    } else if (source->m_portionToPlayNext != 3) {
        reinterpret_cast<Rva00691040Handle &>(buffer->m_at24) = m_audioFileCache->requestFile(source, 0);
    }
    reinterpret_cast<Rva00691040Handle &>(buffer->m_at20) = file;
    if (!file.isValid()) {
        buffer->m_at30 = 0;
        buffer->m_at2C = 0;
        return;
    }
    const MilesSoundInfo *soundInfo = file.getMilesSoundInfo();
    buffer->m_at30 = (const char *)soundInfo->m_dataPtr - (const char *)buffer->m_at20.getFileImage();
    buffer->m_at2C = soundInfo->m_dataLen + buffer->m_at30;
    rva0005DB6C(file.getFileName());
}

// Retail 0x0005EA8F (WorldBuilder twin 0x0077B710, names from its asserts):
// once 0x5106A says the buffer may go, runs the pending completion check,
// unmaps its Miles sample under the Miles mutex and returns the handle to the
// available list, then drops the buffer's data, files, playing audio and
// source.
void MilesAudioManager::cleanUpLoopBuffer(LoopBuffer *buffer)
{
    if (!((Rva0005F279Elem *)buffer)->rva0005106A())
        return;
    if (buffer->m_at03) {
        checkForNaturalSoundCompletion(PlayingAudioRef(buffer->m_playingAudio));
        buffer->m_at03 = false;
    }
    if (buffer->m_is3D) {
        if (buffer->m_3DSample) {
            if (buffer->m_playingAudio) {
                AILMutexScope lock;
                MilesHandleMap::iterator it = m_3DSampleMap.find(reinterpret_cast<unsigned int &>(buffer->m_3DSample));
                if (it == m_3DSampleMap.end())
                    lock.unlock();
                else if ((*it).second != buffer->m_playingAudio)
                    lock.unlock();
                else
                    m_3DSampleMap.erase(it);
            }
            m_available3DSamples.push_back(buffer->m_3DSample);
            buffer->m_3DSample = 0;
            ((Rva000514EB *)this)->rva000514FB();
        }
    } else if (buffer->m_sample) {
        if (buffer->m_playingAudio) {
            AILMutexScope lock;
            MilesHandleMap::iterator it = m_sampleMap.find(reinterpret_cast<unsigned int &>(buffer->m_sample));
            if (it == m_sampleMap.end())
                lock.unlock();
            else if ((*it).second != buffer->m_playingAudio)
                lock.unlock();
            else
                m_sampleMap.erase(it);
        }
        m_availableSamples.push_back(buffer->m_sample);
        buffer->m_sample = 0;
        ((Rva000514EB *)this)->rva000514EB();
    }
    if (buffer->m_at18) {
        delete[] buffer->m_at18;
        buffer->m_at18 = 0;
    }
    ((Rva000A8A6C *)&buffer->m_at20)->rva000A8A6C();
    buffer->m_at30 = 0;
    buffer->m_at2C = 0;
    buffer->m_endOfLastCopy = 0;
    ((Rva000A8A6C *)&buffer->m_at24)->rva000A8A6C();
    ((Rva000A8A6C *)&buffer->m_at28)->rva000A8A6C();
    if (buffer->m_playingAudio) {
        buffer->m_playingAudio->m_status = 1;
        buffer->m_playingAudio->m_type = 5;
        buffer->m_playingAudio = 0;
    }
    ((BfmePoolRef10 &)buffer->m_source).rva000519BD();
    buffer->m_at10 = false;
}

// Retail 0x0005EC7A (WorldBuilder twin 0x0077D5F0, names from its asserts):
// fills the play buffer from m_endOfLastCopy up to position, zero filling once
// the event is done and switching to the decay or next primary file whenever
// the bound one runs out; gives up after 15 tries.
void MilesAudioManager::transferBytesToPlayBuffer(LoopBuffer &buffer, unsigned int position)
{
    const int MAX_TRIES = 15;
    int tries = 0;
    bool done;
    do {
        done = true;
        ++tries;
        int bytesToCopy = position - buffer.m_endOfLastCopy;
        if (bytesToCopy <= 0)
            return;
        if (tries == MAX_TRIES) {
            ((Rva000A8A6C *)&buffer.m_at20)->rva000A8A6C();
            return;
        }
        if (!buffer.m_at20.isValid()) {
            BfmePoolRef10 &source = (BfmePoolRef10 &)buffer.m_source;
            if (source->m_portionToPlayNext == 3) {
                memset(buffer.m_at18 + buffer.m_endOfLastCopy, 0, bytesToCopy);
                buffer.m_endOfLastCopy = position;
                if (buffer.m_endOfLastCopy >= buffer.m_playBufferSize) {
                    buffer.m_endOfLastCopy = 0;
                    buffer.m_at44 = true;
                }
            } else {
                if (source->m_portionToPlayNext == 2) {
                    if (((Rva00050DBD *)&buffer.m_at28)->rva00050DBD()) {
                        source->m_at50 = true;
                        putFileIntoLoopBuffer(&buffer, buffer.m_at28.rva000A89E3(), 1);
                    } else if (!buffer.m_at28.isValid()) {
                        reinterpret_cast<Rva00691040Handle &>(buffer.m_at28) = m_audioFileCache->requestFile(source, 2);
                        if (((Rva00050DBD *)&buffer.m_at28)->rva00050DBD())
                            putFileIntoLoopBuffer(&buffer, buffer.m_at28.rva000A89E3(), 1);
                    } else if (((Rva00050DD0 *)&buffer.m_at28)->rva00050DD0()) {
                        ((Rva002D94FEDwordSlot *)source.operator->())->set(3);
                    } else if (buffer.m_at28.getAt3C() < 2) {
                        reinterpret_cast<Rva00691040Handle &>(buffer.m_at28) =
                            m_audioFileCache->requestFile(buffer.m_at28.getFileName(), 2);
                    }
                } else if (source->m_portionToPlayNext != 3) {
                    if (((Rva00050DD0 *)&buffer.m_at24)->rva00050DD0()) {
                        source->m_at50 = true;
                        source->rva002D9ADC();
                        reinterpret_cast<Rva00691040Handle &>(buffer.m_at24) = m_audioFileCache->requestFile(source, 2);
                    } else if (!((Rva00050DBD *)&buffer.m_at24)->rva00050DBD() && buffer.m_at24.getAt3C() < 2) {
                        reinterpret_cast<Rva00691040Handle &>(buffer.m_at24) =
                            m_audioFileCache->requestFile(buffer.m_at24.getFileName(), 2);
                    }
                }
                if (((Rva00050DBD *)&buffer.m_at24)->rva00050DBD()) {
                    bool usePrimary;
                    switch (source->getNextPlayPortion()) {
                    case 2:
                        usePrimary = !buffer.m_at20.isValid() && (source->getAudioEventInfo()->m_control & 1);
                        break;
                    case 3:
                        usePrimary = false;
                        break;
                    default:
                        usePrimary = true;
                        break;
                    }
                    if (usePrimary)
                        putFileIntoLoopBuffer(&buffer, buffer.m_at24.rva000A89E3(), 0);
                }
                if (buffer.m_at20.isValid()) {
                    const MilesSoundInfo *info = buffer.m_at20.getMilesSoundInfo();
                    if (info->m_bits != buffer.m_at3C)
                        buffer.m_at30 = buffer.m_at2C;
                    if (info->m_rate != buffer.m_at38)
                        buffer.m_at30 = buffer.m_at2C;
                    if (info->m_channels != buffer.m_at40)
                        buffer.m_at30 = buffer.m_at2C;
                }
            }
        }
        if (buffer.m_at20.isValid()) {
            int bytesLeftInCurrentFile = buffer.m_at2C - buffer.m_at30;
            if (bytesLeftInCurrentFile > 0)
                memcpy(buffer.m_at18 + buffer.m_endOfLastCopy,
                       (char *)buffer.m_at20.getFileImage() + buffer.m_at30,
                       _STL::min(bytesToCopy, bytesLeftInCurrentFile));
            if (bytesToCopy < bytesLeftInCurrentFile) {
                buffer.m_at30 += bytesToCopy;
                buffer.m_endOfLastCopy = position;
                if (buffer.m_endOfLastCopy >= buffer.m_playBufferSize) {
                    buffer.m_endOfLastCopy = 0;
                    buffer.m_at44 = true;
                }
            } else {
                buffer.m_at30 += bytesLeftInCurrentFile;
                done = false;
                buffer.m_endOfLastCopy += bytesLeftInCurrentFile;
                if (buffer.m_endOfLastCopy >= buffer.m_playBufferSize) {
                    buffer.m_endOfLastCopy = 0;
                    buffer.m_at44 = true;
                }
                ((Rva000A8A6C *)&buffer.m_at20)->rva000A8A6C();
            }
        }
    } while (!done);
}

class File;
class FileSystem {
public:
    File *openFile(const char *fileName, int access, int bufferSize);
};
extern FileSystem *TheFileSystem;

// Retail 0x000518B8, the open callback init() hands AIL_set_file_callbacks
// first (Zero Hour's streamingFileOpen). 0x141 is Zero Hour's
// File::READ | File::BINARY | File::STREAMING.
unsigned int __stdcall streamingFileOpen(const char *fileName, unsigned int *fileHandle)
{
    *fileHandle = (unsigned int)TheFileSystem->openFile(fileName, 0x141, 0);
    return *fileHandle != 0;
}

// Retail 0x0005F267, the loop-buffer thread init() starts with CreateThread.
extern "C" __declspec(dllimport) unsigned int __stdcall AIL_ms_count(void);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

// Retail 0x0005EFE9 (WorldBuilder twin 0x0077C240): the loop-buffer thread.
// Reads the cycle time from the settings, then until m_atBE0 is set refills
// every valid loop buffer under the manager mutex and sleeps out the cycle.
void MilesAudioManager::rva0005EFE9(void)
{
    unsigned int sleepTime = 50;
    {
        MilesMutexGuard guard(&m_mutex, 1);
        while (!guard.rva00041037(100)) {
            if (m_atBE0)
                return;
        }
        if (m_audioSettings)
            sleepTime = m_audioSettings->m_at8C / m_audioSettings->m_at90;
    }
    if (m_atBE0)
        return;
    do {
        unsigned int start = AIL_ms_count();
        for (int i = 0; i < m_numLoopBuffers; ++i) {
            LoopBuffer *buffer = &m_loopBuffers[i];
            if (!buffer->m_isValid)
                continue;
            MilesMutexGuard guard(&m_mutex, 1);
            while (!guard.rva00041037(100)) {
                if (m_atBE0)
                    return;
            }
            if (!buffer->m_isValid)
                continue;
            if (buffer->at01) {
                ((Rva00050FE3 *)buffer)->rva00050FE3();
                buffer->m_isValid = false;
                continue;
            }
            BfmePoolRef10 &source = (BfmePoolRef10 &)buffer->m_source;
            if (source->m_at4C && !buffer->m_at28.isValid() && source->m_portionToPlayNext == 1) {
                source->advanceNextPlayPortion();
                if (source->m_portionToPlayNext == 2)
                    reinterpret_cast<Rva00691040Handle &>(buffer->m_at28) = m_audioFileCache->requestFile(source, 1);
            }
            unsigned int position = ((Rva00050FFD *)buffer)->rva00050FFD();
            if (position >= buffer->m_playBufferSize)
                position = 0;
            bool wasFull = buffer->m_at44;
            bool keepGoing = true;
            if (position > buffer->m_endOfLastCopy) {
                transferBytesToPlayBuffer(*buffer, position);
            } else if (position < buffer->m_endOfLastCopy) {
                transferBytesToPlayBuffer(*buffer, buffer->m_playBufferSize);
                if (buffer->m_endOfLastCopy == 0) {
                    if (!buffer->m_at20.isValid() && source->m_portionToPlayNext == 3) {
                        ((Rva00051017 *)buffer)->rva00051017(1);
                        keepGoing = false;
                    } else {
                        transferBytesToPlayBuffer(*buffer, position);
                    }
                }
            }
            if (!keepGoing) {
                if (!source->m_at4C)
                    buffer->m_at03 = true;
                buffer->m_isValid = false;
            } else if (buffer->m_at44 && !wasFull) {
                ((Rva00050FC9 *)buffer)->rva00050FC9();
                pauseResumeSound(PlayingAudioRef(buffer->m_playingAudio));
            }
        }
        if (m_atBE0)
            return;
        unsigned int now = AIL_ms_count();
        if (now - start <= sleepTime)
            Sleep(start - now + sleepTime);
    } while (!m_atBE0);
}

unsigned long __stdcall rva0005F267(void *param)
{
    MilesAudioManager *manager = (MilesAudioManager *)param;
    if (manager)
        manager->rva0005EFE9();
    return 0;
}

// The close, seek and read callbacks are rowed under BFME 1 donor names.
typedef unsigned int (__stdcall *MilesFileOpenCallback)(const char *fileName, unsigned int *fileHandle);
typedef void (__stdcall *MilesFileCloseCallback)(unsigned int fileHandle);
typedef int (__stdcall *MilesFileSeekCallback)(unsigned int fileHandle, int offset, unsigned int type);
typedef unsigned int (__stdcall *MilesFileReadCallback)(unsigned int fileHandle, void *buffer, unsigned int bytes);
extern "C" __declspec(dllimport) void __stdcall AIL_set_file_callbacks(MilesFileOpenCallback open,
    MilesFileCloseCallback close, MilesFileSeekCallback seek, MilesFileReadCallback read);
void __stdcall Rva000518E0Thunk(void *file);
struct Rva006963B0Receiver;
struct Rva006963D0Receiver;
int __stdcall rva006963B0ForwardSlot5(Rva006963B0Receiver *file, int a, int b);
int __stdcall rva006963D0ForwardSlot3(Rva006963D0Receiver *file, int a, int b);
extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *attributes, unsigned long stackSize,
    unsigned long (__stdcall *start)(void *), void *param, unsigned long flags, unsigned long *threadId);
void rva000524EE(int index, float volume);
// AudioFileCache's guarded setter, rowed under an address-derived name.
class Rva000A77D9 {
public:
    void rva000A77D9(void *value);
};

// Retail 0x00061ABD (WorldBuilder twin 0x00789160, named by its asserts):
// set the five system volumes, allocate the loop buffers and start their
// thread, then open the device and hand Miles the file callbacks.
void MilesAudioManager::init()
{
    rva000541DB();
    for (int i = 0; i < 5; ++i)
        rva000524EE(i, m_audioSettings ? m_audioSettings->m_at30[i] : 0.55f);
    m_numLoopBuffers = m_audioSettings->m_at68 + m_audioSettings->m_at64;
    m_loopBuffers = new LoopBuffer[m_numLoopBuffers];
    m_atBE0 = false;
    m_loopBufferThread = CreateThread(0, 0, rva0005F267, this, 0, 0);
    openDevice();
    ((Rva000A77D9 *)m_audioFileCache)->rva000A77D9((void *)m_audioSettings->m_at80);
    AIL_set_file_callbacks(streamingFileOpen, (MilesFileCloseCallback)Rva000518E0Thunk,
        (MilesFileSeekCallback)rva006963B0ForwardSlot5, (MilesFileReadCallback)rva006963D0ForwardSlot3);
    setMaxAmbientStreams();
}

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

void MilesAudioManager::rva00059CE6(PlayingAudioRef &looping)
{
    looping->m_status = 1;
    Rva00051107AudioRequest *request = rva00051107();
    request->m_request = 0;
    request->m_pendingEvent = looping->m_event;
    request->m_at11 = true;
    request->m_at12 = looping->m_at49;
    request->m_at13 = looping->m_at4A;
    if (looping->m_at30 >= m_audioSettings->m_at78)
        ((Weapon *)request->m_pendingEvent.operator->())->setLeechRangeActive(true);
    request->m_at08 = request->m_pendingEvent->m_playingHandle;
    if (looping->m_at40 > 0.0f) {
        ((Rva00481FAFFloatSlot *)request->m_pendingEvent.operator->())->store(looping->m_at3C);
        looping->m_at40 = 0.0f;
    }
    _STL::pair<Rva00051107AudioRequestSet::iterator, bool> result = m_requestSet.insert(request);
    if (!result.second)
        deleteAudioRequest(request);
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

bool MilesAudioManager::killLowestPrioritySoundImmediately(AudioEventRTS *event)
{
    if (event->isPositionalAudio()) {
        ((Rva0005F279Host *)this)->rva0005F279();
        if (!m_available3DSamples.empty())
            return true;
    }
    AudioEventRTS *lowestPriorityEvent = findLowestPrioritySound(event);
    if (lowestPriorityEvent) {
        PlayingAudioList::iterator it;
        if (event->isPositionalAudio()) {
            for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); it++) {
                PlayingAudioRef playing = *it;
                if (!playing.get())
                    continue;
                if (playing->m_event.operator->() == lowestPriorityEvent) {
                    if (playing->m_event->hasMoreLoops())
                        rva0005AA72(playing);
                    releaseMilesHandles(*playing.get());
                    reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(
                        OpaqueRefList::iterator((OpaqueRefList::_Node *)it._M_node));
                    return true;
                }
            }
        } else {
            for (it = m_playingSounds.begin(); it != m_playingSounds.end(); it++) {
                PlayingAudioRef playing = *it;
                if (!playing.get())
                    continue;
                if (playing->m_event.operator->() == lowestPriorityEvent) {
                    if (playing->m_event->hasMoreLoops())
                        rva0005AA72(playing);
                    releaseMilesHandles(*playing.get());
                    reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(
                        OpaqueRefList::iterator((OpaqueRefList::_Node *)it._M_node));
                    return true;
                }
            }
        }
    }
    return false;
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

// The 2D twin of get3DSampleHandleForPlayingAudio (WorldBuilder 0x77FFB0):
// type 0 holds the sample itself, type 1 indexes a 2D loop buffer. Its ledger
// spelling takes the PlayingAudioRef by address.
void *MilesAudioManager::get2DSampleHandleForPlayingAudio(void *ref)
{
    PlayingAudioRef &playing = *static_cast<PlayingAudioRef *>(ref);
    switch (playing->m_type) {
    case 0:
        return (void *)playing->m_handle;
    case 1:
        break;
    default:
        return 0;
    }
    if (!m_loopBuffers[playing->m_handle].m_is3D)
        return m_loopBuffers[playing->m_handle].m_sample;
    return 0;
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

// WorldBuilder 0x78B4F0 (unnamed): switch on the playing type. 2D samples
// (types 0/1) and the type-4 receiver get the event info's reverb dry/wet pair,
// 3D samples (2/3) an effects level scaled by +0x34; with reverb off the pair is
// 1/0 and the level 0.
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

// WorldBuilder 0x797C60 MilesAudioManager::setOcclusionLevels: no occlusion
// when the settings disable it or slot 107 rejects the position; otherwise the
// event info's +0x90 factor, reduced by the listener distance (0x53854) under
// the per-view settings, sets the 3D sample occlusion within [floor, 1].
void MilesAudioManager::setOcclusionLevels(PlayingAudioRef &playing, const Coord3D *pos)
{
    void *sample3D = get3DSampleHandleForPlayingAudio(playing);
    if (m_audioSettings->m_atBC || rva000516EF(pos)) {
        AIL_set_3D_sample_occlusion(sample3D, 0.0f);
        return;
    }
    float occlusion = 1.0f;
    if (playing->m_event->m_info->m_at90 > 0.0f)
        occlusion *= playing->m_event->m_info->m_at90;
    if (m_at8C > 0.0f && playing->m_event->m_info->m_atA4 > 0.0f) {
        float distSqr = rva00053854(pos);
        float scale;
        if (distSqr > m_audioSettings->m_viewSettings[m_at678].m_at04)
            scale = 1.0f;
        else
            scale = sqrt(distSqr) / m_audioSettings->m_viewSettings[m_at678].m_at00;
        occlusion *= 1.0 - scale * m_at8C * playing->m_event->m_info->m_atA4;
    }
    float finalOcclusion = 1.0f - occlusion;
    if (finalOcclusion > 1.0f)
        finalOcclusion = 1.0f;
    else if (finalOcclusion < m_audioSettings->m_atC0)
        finalOcclusion = 0.0f;
    AIL_set_3D_sample_occlusion(sample3D, finalOcclusion);
}

// WorldBuilder 0x7A3290: squared 2D distance from pos to the outline of
// corners 1..4, via the nearest valid corner and its two adjacent edges;
// +inf when no corner is valid.
float MilesAudioManager::rva00053854(const Coord3D *pos)
{
    int nearest = 5;
    float best = g_Va00BBDA30;
    for (int i = 1; i < 5; ++i) {
        if (m_corners[i].m_valid) {
            Coord2D delta(*pos);
            float dist = delta.Sub(m_corners[i].m_pos).GetLengthSqrd();
            if (dist < best) {
                nearest = i;
                best = dist;
            }
        }
    }
    if (nearest == 5)
        return g_Va00BBDA30;

    int next = nearest + 1;
    if (next == 5)
        next = 1;
    {
        LineSegment2D edge(Coord2D(m_corners[nearest].m_pos), Coord2D(m_corners[next].m_pos));
        Coord2D closest = ClosestPointOnLineSegment(edge, Coord2D(*pos));
        float dist = closest.Sub(*pos).GetLengthSqrd();
        if (dist < best)
            best = dist;
    }

    int prev = nearest - 1;
    if (prev < 1)
        prev = 4;
    {
        LineSegment2D edge(Coord2D(m_corners[nearest].m_pos), Coord2D(m_corners[prev].m_pos));
        Coord2D closest = ClosestPointOnLineSegment(edge, Coord2D(*pos));
        float dist = closest.Sub(*pos).GetLengthSqrd();
        if (dist < best)
            best = dist;
    }
    return best;
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

// End-of-sample handlers: under the Miles mutex, the PlayingAudio mapped to
// the finished handle is queued on the +0xB94 completion list. The inner
// block lets the reference reuse the dead handle's parameter slot. The 2D,
// 3D and stream variants read the maps at +0xB98, +0xBAC and +0xBC0; the
// callbacks below (registered by playSample, playSample3D and the stream
// setup at 0x0005AB5E) forward the handle here. Names stay address-derived.
void MilesAudioManager::rva000564C0(unsigned int sample)
{
    AILMutexScope lock;
    MilesHandleMap::iterator it = m_sampleMap.find(sample);
    {
        PlayingAudioRef playing;
        if (it == m_sampleMap.end())
            return;
        playing.set((PlayingAudio *)(*it).second);
        if (!playing.get())
            return;
        m_completedAudio.push_back(playing);
    }
}

void MilesAudioManager::rva0005653C(unsigned int sample3D)
{
    AILMutexScope lock;
    MilesHandleMap::iterator it = m_3DSampleMap.find(sample3D);
    {
        PlayingAudioRef playing;
        if (it == m_3DSampleMap.end())
            return;
        playing.set((PlayingAudio *)(*it).second);
        if (!playing.get())
            return;
        m_completedAudio.push_back(playing);
    }
}

void MilesAudioManager::rva000565B8(unsigned int stream)
{
    AILMutexScope lock;
    MilesHandleMap::iterator it = m_streamMap.find(stream);
    {
        PlayingAudioRef playing;
        if (it == m_streamMap.end())
            return;
        playing.set((PlayingAudio *)(*it).second);
        if (!playing.get())
            return;
        m_completedAudio.push_back(playing);
    }
}

// Zero Hour's AILCALLBACK end-of-sample callbacks (static there), which
// forward the finished handle to TheAudio.
class AudioManager;
extern AudioManager *TheAudio;

void __stdcall setSampleCompleted(void *sampleCompleted)
{
    if (TheAudio)
        reinterpret_cast<MilesAudioManager *>(TheAudio)->rva000564C0((unsigned int)sampleCompleted);
}

void __stdcall set3DSampleCompleted(void *sample3DCompleted)
{
    if (TheAudio)
        reinterpret_cast<MilesAudioManager *>(TheAudio)->rva0005653C((unsigned int)sample3DCompleted);
}

void __stdcall setStreamCompleted(void *streamCompleted)
{
    if (TheAudio)
        reinterpret_cast<MilesAudioManager *>(TheAudio)->rva000565B8((unsigned int)streamCompleted);
}

// Queues the text mapped to a played file name (0x0005E24E passes the
// sample's file name); names with no entry are collected instead.
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

void MilesAudioManager::prep3DSample(PlayingAudioRef &playing, const Coord3D *pos)
{
    void *sample3D = get3DSampleHandleForPlayingAudio(playing);
    BfmePoolRef10 &event = playing->m_event;
    if (!event->m_info->m_channelVolumes.empty())
        rva000581FA(*reinterpret_cast<const Rva0005BA08InfoRef *>(&event->m_info), event->m_viewType);
    float minDistance;
    if ((event->m_info->m_type & 8)
        || reinterpret_cast<Rva002DA153 *>(event.operator->())->rva002DA153() > m_audioSettings->m_atB8)
        minDistance = (float)m_audioSettings->m_at74;
    else
        minDistance = event->m_info->m_minDistance;
    minDistance *= 2.0f;
    AIL_set_3D_sample_distances(sample3D, event->m_info->m_maxDistance, minDistance);
    AIL_set_3D_position(sample3D, pos->x, pos->y, -pos->z);
    initFilters3D(playing, pos);
}

// WorldBuilder twin MilesAudioManager::initFilters3D (0x798000): volume, pitch
// scaled playback rate, then the occlusion and two unnamed filter passes.
void MilesAudioManager::initFilters3D(PlayingAudioRef &playing, const Coord3D *pos)
{
    void *sample3D = get3DSampleHandleForPlayingAudio(playing);
    BfmePoolRef10 &event = playing->m_event;
    AIL_set_3D_sample_volume(sample3D, rva0005A9F8(&playing, 1, 1));
    float pitchShift = reinterpret_cast<const Rva002D94DD *>(event.operator->())->rva002D94DD();
    if (pitchShift != 0.0f)
        AIL_set_3D_sample_playback_rate(sample3D, (int)(AIL_3D_sample_playback_rate(sample3D) * pitchShift));
    setOcclusionLevels(playing, pos);
    {
        bool result;
        rva00055C5D(playing, &result);
    }
    rva00052FA0(playing);
}

// File-static helper with its playing ref in EAX (retail caller 0x55DFF
// `mov eax, ecx`): an object-owned event tests its object, any other the
// trigger polygon at the position.
static bool rva00055C1A(PlayingAudioRef &playing, const Coord3D *pos, PolygonTrigger *trigger)
{
    if (playing->m_event->m_ownerType == 2 && TheGameLogic) {
        Object *obj = TheGameLogic->findObjectByID(playing->m_event->getObjectID());
        if (obj)
            return obj->isInside(trigger);
    }
    return trigger->rva002E3A39(*pos);
}

// WorldBuilder twin 0x78B740 (unnamed): picks the lowest area level whose
// trigger holds the event, scanning backwards from the last hit, and reports
// whether +0x34 changed.
void MilesAudioManager::rva00055C5D(PlayingAudioRef &playing, bool *result)
{
    if (m_triggerAreas.empty()) {
        *result = playing->m_at34 != 1.0f;
        playing->m_at34 = 1.0f;
        return;
    }
    if (playing->m_event->m_viewType != 0) {
        *result = playing->m_at34 != 0.0f;
        playing->m_at34 = 0.0f;
        return;
    }
    bool valid;
    BfmeEventPositionView pos = Rva0005160FGet(playing->m_event.operator->(), valid);
    if (!valid) {
        if (!playing->m_at4E) {
            *result = playing->m_at34 != 1.0f;
            playing->m_at34 = 1.0f;
            return;
        }
        if (!m_at6AA) {
            *result = false;
            return;
        }
        static_cast<Coord3D &>(pos) = playing->m_at24;
    } else if (!m_at6AA) {
        float dx = pos.x - playing->m_at24.x;
        float dy = pos.y - playing->m_at24.y;
        float limit = m_audioSettings->m_atB0;
        if (dx <= limit && -limit <= dx && dy <= limit && -limit <= dy) {
            *result = false;
            return;
        }
    }
    playing->m_at24 = pos;
    playing->m_at4E = true;
    int start = playing->m_at38;
    if (start < 0)
        start = 0;
    else if (start >= m_triggerAreas.size())
        start = m_triggerAreas.size() - 1;
    int i = start;
    int best = start;
    float bestLevel = 1.0f;
    do {
        if (m_triggerAreas[i].m_level < bestLevel && rva00055C1A(playing, &pos, m_triggerAreas[i].m_trigger)) {
            bestLevel = m_triggerAreas[i].m_level;
            best = i;
        }
        if (i == 0)
            i = m_triggerAreas.size() - 1;
        else
            --i;
    } while (i != start);
    *result = bestLevel != playing->m_at34;
    playing->m_at34 = bestLevel;
    playing->m_at38 = best;
}

void __stdcall setSampleCompleted(void *sampleCompleted);
void __stdcall set3DSampleCompleted(void *sample3DCompleted);

// WorldBuilder twin MilesAudioManager::playSample (0x7A4CB0).
bool MilesAudioManager::playSample(PlayingAudioRef &playing)
{
    void *sample = (void *)playing->m_handle;
    BfmePoolRef10 &event = playing->m_event;
    AIL_init_sample(sample);
    AIL_register_EOS_callback(sample, setSampleCompleted);
    if (playing->m_file.isOpen()) {
        prepSample(&playing);
        AIL_set_sample_file(sample, playing->m_file.getFileImage(), 0);
        AIL_start_sample(sample);
        event->m_at50 = true;
        rva000535A6(playing);
        pauseResumeSound(playing);
        rva0005DB6C(playing->m_file.getFileName());
        return true;
    }
    return false;
}

// WorldBuilder twin MilesAudioManager::playSample3D (0x7A5130): only mono
// files play in 3D.
bool MilesAudioManager::playSample3D(PlayingAudioRef &playing)
{
    BfmePoolRef10 &event = playing->m_event;
    void *sample3D = get3DSampleHandleForPlayingAudio(playing);
    bool valid;
    BfmeEventPositionView pos = Rva0005160FGet(event.operator->(), valid);
    if (valid && playing->m_file.isOpen()) {
        rva0005DB6C(playing->m_file.getFileName());
        if (playing->m_file.getMilesSoundInfo()->m_channels == 1) {
            AIL_set_3D_sample_file(sample3D, playing->m_file.getFileImage());
            AIL_register_3D_EOS_callback(sample3D, set3DSampleCompleted);
            prep3DSample(playing, &pos);
            AIL_set_3D_sample_loop_count(sample3D, 1);
            AIL_start_3D_sample(sample3D);
            event->m_at50 = true;
            rva000535A6(playing);
            pauseResumeSound(playing);
            return true;
        }
    }
    return false;
}

// Preloads the file of a short play request the gate admits, then dispatches
// the request by type; a refused play request burns one loop instead.
void MilesAudioManager::processRequest(Rva00051107AudioRequest *req, bool *removeRequest)
{
    int canPlay = 2;
    if (req->m_request == 0 && !req->m_file.isOpen() && req->m_pendingEvent.operator->()) {
        float length = req->m_pendingEvent->m_at64;
        if ((float)m_audioSettings->m_atB4 > length
            && req->m_pendingEvent->m_info->m_atB0 == 2) {
            if (canPlay == 2)
                canPlay = reinterpret_cast<Rva0005E13CHost *>(this)->rva0005E13C(
                    reinterpret_cast<const Rva0005E13CArg *>(req)) ? 1 : 0;
            if (canPlay == 1)
                reinterpret_cast<Rva00691040Handle &>(req->m_file) = m_audioFileCache->requestFile(
                    // Shorter than one client frame (WorldBuilder tests it out of line).
                    req->m_pendingEvent, !(req->m_pendingEvent->m_at64 >= g_00DBA4FC));
        }
    }

    if (!rva00053606(req)) {
        *removeRequest = false;
        rva00053646(req, removeRequest);
        return;
    }

    if (canPlay == 2) {
        if (req->m_at11)
            canPlay = reinterpret_cast<Rva0005E13CHost *>(this)->rva0005E13C(
                reinterpret_cast<const Rva0005E13CArg *>(req)) ? 1 : 0;
        else
            canPlay = 1;
    }

    if (canPlay == 1) {
        switch (req->m_request) {
        case 0:
            playAudioEvent(req);
            break;
        case 1:
            rva0005FA3C(req->m_at08);
            break;
        case 2:
            rva00057297(*req);
            break;
        case 3:
            processPushMusicRequest(req);
            break;
        case 4:
            processPopMusicRequest(req);
            break;
        case 5:
            rva0005AC61(req->m_pendingEvent->m_viewType, req->m_pendingEvent->m_musicSystem, !req->m_at10);
            break;
        case 6: {
            MusicSystem musicSystem = req->m_pendingEvent->m_musicSystem;
            int viewType = req->m_pendingEvent->m_viewType;
            rva0005876E(viewType, musicSystem, !req->m_at10,
                !reinterpret_cast<Rva000CB12FByteField *>(req->m_pendingEvent.operator->())->get());
            break;
        }
        case 7:
            rva0005774F(req->m_pendingEvent->m_viewType, req->m_pendingEvent->m_musicSystem, !req->m_at10);
            break;
        }
    } else if (req->m_request == 0 && req->m_pendingEvent.operator->()
        && req->m_pendingEvent->hasMoreLoops()) {
        req->m_pendingEvent->rva002D9ADC();
        req->m_file.rva000A8A6C();
        if (req->m_pendingEvent->hasMoreLoops()) {
            *removeRequest = false;
            req->m_pendingEvent->m_at4B = true;
        }
    }
}

// Processes the queued requests, dropping each one that is done, then the
// request set: a request kept alive goes back into the emptied set and is
// deleted if an equal one is already there.
void MilesAudioManager::processRequestList(void)
{
    bool removeRequest;
    Rva00051107AudioRequestList::iterator it = m_audioRequests.begin();
    while (it != m_audioRequests.end()) {
        Rva00051107AudioRequest *req = *it;
        if (req == NULL) {
            it = m_audioRequests.erase(it);
            continue;
        }
        removeRequest = true;
        processRequest(req, &removeRequest);
        if (removeRequest) {
            deleteAudioRequest(req);
            it = m_audioRequests.erase(it);
        } else {
            ++it;
        }
    }

    {
        Rva00051107AudioRequestSet pending(m_requestSet);
        m_requestSet.clear();
        while (pending.size() != 0) {
            Rva00051107AudioRequest *req = *pending.begin();
            pending.erase(req);
            removeRequest = true;
            if (req)
                processRequest(req, &removeRequest);
            if (removeRequest) {
                deleteAudioRequest(req);
            } else {
                _STL::pair<Rva00051107AudioRequestSet::iterator, bool> result = m_requestSet.insert(req);
                if (!result.second)
                    deleteAudioRequest(req);
            }
        }
    }
}
