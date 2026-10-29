// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
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
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <math.h>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}
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
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <map>
#include <vector>
#include <limits>
#undef free
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
// Retail's Coord2D has user constructors and a destructor (exported), so a
// by-value Coord2D returns through a hidden pointer (0x53854).
#define COORD2D_VIEW_DTOR
#include "../../../Libraries/Include/Lib/Coord2DCtorView.h"
#include "Common/Snapshot.h"

// Version pair xfer (slot 10) reads and rewrites; xfer (0x0005E3E5) seeds
// 1 and 4 and gates its later fields on the second byte.
struct XferVersion {
    unsigned char m_version;
    unsigned char m_currentVersion;
};

// Xfer view: slot 1 tells a load from a save; +0x78 and +0x90 xfer an
// unsigned int and a bool (0x0005B256). xfer (0x0005E3E5) also calls
// slot 3 (+0x0C, CRC pass), 10 (+0x28), 28 (+0x70, float) and 31 (+0x7C, int).
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../GameEngine/Include/Common/BfmeXfer.h"
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
    bool rva00050EFA(void);  // add a reference unless the count already reached zero (0x00050EFA)
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
// Use the retail deque erase emitted by StlportOwnedDeque.cpp.
namespace _STL { template <> MusicStack::iterator MusicStack::erase(MusicStack::iterator); }

// The vector destructor is provided by StlportVectorDtorDeferred.cpp.
namespace _STL { template <> vector<OpaqueRefElement4>::~vector(); }

enum MusicSystem { MUSIC_SYSTEM_0, MUSIC_SYSTEM_1 };
inline MusicSystem &operator--(MusicSystem &ms, int) { ms = (MusicSystem)(ms - 1); return ms; }

#include "../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"
// bfme link decl-only begin
namespace _STL { template <> UnicodeString * __uninitialized_copy<UnicodeString *, UnicodeString *>(UnicodeString *, UnicodeString *, UnicodeString *, __false_type const &); }
namespace _STL { template <> UnicodeString * __uninitialized_fill_n<UnicodeString *, unsigned int, UnicodeString>(UnicodeString *, unsigned int, UnicodeString const &, __false_type const &); }
namespace _STL { template <> _List_node<void *> * list<void *, allocator<void *> >::_M_create_node(void *const &); }
namespace _STL { template <> void vector<UnicodeString, allocator<UnicodeString> >::_M_insert_overflow(UnicodeString *, UnicodeString const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> UnicodeString * vector<UnicodeString, allocator<UnicodeString> >::erase(UnicodeString *, UnicodeString *); }
namespace _STL { template <> void vector<UnicodeString, allocator<UnicodeString> >::push_back(const UnicodeString &); }
namespace _STL { template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left, _STLP_alloc_proxy<void **, void *, allocator<void *> > &right) { swap(left._M_data, right._M_data); } }
// bfme link decl-only end
// Retail list insertion (0x55475 -> 0x54B75 -> 0x53DA3) copies its
// four-byte owning reference through _Construct<Rva0036CA00Str> (0x2393AA).
// Keep the visible list operations, binding only their element copy to that
// existing counted-reference operation (copy ctor 0xA8C7C increments pointee+4).
class PlayingAudioRef;
class Rva0036CA00Str;
namespace _STL {
template <> void _Construct<Rva0036CA00Str,Rva0036CA00Str>(Rva0036CA00Str *,const Rva0036CA00Str &) throw();
template <> __declspec(dllimport) __forceinline void _Construct<PlayingAudioRef,PlayingAudioRef>(PlayingAudioRef *dest,const PlayingAudioRef &source)
{
    _Construct(reinterpret_cast<Rva0036CA00Str *>(dest),reinterpret_cast<const Rva0036CA00Str &>(source));
}
}
// Suppress this TU's non-retail copy of ??$copy_backward@U?$_Deque_iterator@UOpaqueRefElement4@@U?$_Nonconst_traits@UOpaqueRefElem:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct OpaqueRefElement4;
namespace _STL { template <> _Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> > copy_backward<_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> >,_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> > >(_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> >,_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> >,_Deque_iterator<OpaqueRefElement4,_Nonconst_traits<OpaqueRefElement4> >); }
class Image;
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UOpaqueRefElement4@@V?$allocator@UOpaqueRefElement4@@@_STL@@@_STL@@QAE@X:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct OpaqueRefElement4;
namespace _STL { template <> _Vector_base<OpaqueRefElement4,allocator<OpaqueRefElement4> >::~_Vector_base(); }

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> void vector<AsciiString, allocator<AsciiString> >::reserve(size_t);
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);
}

// (channel, volume) entry of AudioEventInfo +0xB8: 0x0005818B reads the
// channel index first (-1 skips) and the float second.
struct AudioEventChannelVolume {
    int m_channel;
    float m_volume;
};

// AudioEventInfo view: +0x44 is the priority the lowest-priority scan ranks by.
// prep3DSample passes +0x94 as AIL_set_3D_sample_distances' max distance and
// +0x98 (non-global sounds) as its min distance.
struct RvaPair001D9F62 { AsciiString m_key; int m_value; ~RvaPair001D9F62(); };
struct AudioEventInfo {
    const _STL::vector<RvaPair001D9F62> &getSoundsVector(void) const;
    int getVolumeSlider(void);
    bool isTightlyCoupledSound(void) const;
    char at00[0x08];
    AsciiString m_audioName;                 // +0x08
    char at0C[0x1C - 0x0C]; float m_at1C; char at20[0x30 - 0x20];
    float m_at30;                            // +0x30, playAudioEvent drops a sound effect when a random draw exceeds it
    char at34[0x38 - 0x34];
    int m_at38;                              // +0x38, playAudioEvent compares it with g_00DBA4FC
    char at3C[0x44 - 0x3C];
    int m_priority;                          // +0x44
    unsigned int m_type;                     // +0x48, bit 3 global
    unsigned int m_control;                  // +0x4C, Zero Hour's AudioControl bits (AC_LOOP = 1)
    char at50[0x90 - 0x50];
    float m_at90;                            // +0x90, occlusion factor when positive
    float m_maxDistance;                     // +0x94
    float m_minDistance;                     // +0x98
    char at9C[0xA4 - 0x9C];
    float m_distanceOcclusionWeight;                            // +0xA4, distance occlusion weight
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
    // Retail 0x00051931 (rowed in stlport_stringtailrecord144_dtor.cpp), visible
    // like the copy below so 0x0005286A keeps its new reference in ESI.
    __declspec(noinline) BfmePoolRef10(BfmePoolHolder88 *p) : m_ptr(reinterpret_cast<AudioEventRTS *>(p)) { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(reinterpret_cast<char *>(m_ptr) + 0x88)->Add_Ref(); }
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
    char at18[0x2C - 0x18];
    float m_at2C;            // +0x2C, volume (kept across 0x000563FE's event xfer)
    int m_viewType;          // +0x30
    // Inline view-type getter: the 0x000583BA pause tests read it through
    // this (the value lands in EAX first, as retail), the stream test does not.
    int getViewType(void) const { return m_viewType; }
    char at34[0x38 - 0x34];
    int m_ownerType;         // +0x38, 2 when object-owned (getObjectID's test)
    char at3C[0x4A - 0x3C];
    bool m_at4A;             // +0x4A, playAudioEvent tests it on type-1 streams
    bool m_at4B;             // +0x4B
    bool m_at4C;             // +0x4C, the loop-buffer thread's decay/loop test
    char at4D[0x4F - 0x4D];
    bool m_at4F;             // +0x4F, cleared by playAudioEvent
    bool m_startedPlaying;             // +0x50, set once a sample starts playing
    char at51[0x52 - 0x51];
    bool m_at52;             // +0x52, playAudioEvent tests it after starting a stream
    bool m_at53;
    char at54[0x64 - 0x54];
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
    int getAt3C(void) const { return m_ptr ? m_ptr->m_at3C : 0; }
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
// The +0x0C stream predicate tested by the 0x00055E6C music lookup,
// rowed at 0x000A8B59 under its own address-derived owner.
class Rva000A8B59 { public: bool rva000A8B59(int x); };
// Further +0x0C stream-holder forwarders (PinnedForwarders1830.cpp).
struct Rva0010FFA2Packet;
class Rva000A8B4B { public: void rva000A8B4B(int callback); };
class Rva000A8C6E { public: void rva000A8C6E(const Rva0010FFA2Packet *packet); };
class Rva000A8B31 { public: void rva000A8B31(float position, int arg); };
class Rva000A8ACC { public: void rva000A8ACC(void); };
class MilesStreamRef { public: void rva000A8AC0(void); };
class Rva000A8AD8 { public: void rva000A8AD8(float level); };
// Opens a stream file into the +0x0C holder (0x000A8D0B, operator new(0x28)).

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
    bool m_pushedTrackResumed;                         // +0x45, set when a pushed track resumes
    bool m_at46;                         // +0x46
    bool m_fadeUpFromShroud;                         // +0x47, fade-up-from-shroud flag (processFade)
    bool m_at48;                         // +0x48, overrides +0x44/+0x46 in that test
    bool m_at49;                         // +0x49
    bool m_at4A;                         // +0x4A
    bool m_at4B;                         // +0x4B, set by 0x000535A6
    bool m_at4C;
    bool m_raiseScriptFlagOnRelease;                         // +0x4D, raise the event's script flag on release (0x5FDCA)
    bool m_hasLastTestedPosition;                         // +0x4E, m_at24 holds a position
    bool m_at4F;                         // +0x4F, set when 0x5634C hands on a new extra volume
};

// Retain-and-replace setter rowed at 0x000A8CE5 under its address-derived owner.
class Rva000A8C9B {
public:
    // Rowed here at 0x000A8C9B; visible here so the unit
    // knows it keeps no pointer to the holder it clears.
    __declspec(noinline) void clear(void)
    {
        if (m_ptr) {
            m_ptr->Release_Ref();
            m_ptr = 0;
        }
    }
    void rva000A8CE5(OpaqueRefCounted *value);
    void rva000A8D0B(int owner, int filename, int arg);
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
    // Release then null (inline in playAudioEvent).
    void clear(void) { if (m_ptr) { asRefCounted()->Release_Ref(); m_ptr = 0; } }
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
        return req == 0 ? 0 : req->m_at08;
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
typedef _STL::hashtable<Rva00051107AudioRequest *, Rva00051107AudioRequest *, Rva00051B89Hash,
    _STL::_Identity<Rva00051107AudioRequest *>, Rva00050E1CEqualTo,
    _STL::allocator<Rva00051107AudioRequest *> > MilesAudioRequestTable;
namespace _STL { template <> void MilesAudioRequestTable::resize(unsigned int); }

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
    // Rowed constructor 0x000A8531 (0x54 bytes) takes the manager's mutex.
    AudioFileCache(void *mutex);
    ~AudioFileCache();                   // rowed 0x000A7CF3
    Rva00690FF0Handle requestFile(const BfmePoolRef10 &event, int shortSound);
    Rva00690FF0Handle requestFile(const AsciiString &fileName, int priority);
    void rva000A77B3(void);             // rowed 0x000A77B3: stop the loader thread
private:
    char m_body[0x54];                   // native operator new(0x54) at 0x0005D3DA
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
    Rva0051D93(const struct BfmeAudioEventPrefix136 &source);
private:
    char opaque[0x90];
};

// Event field setters rowed by address: 0x002D94CE stores the view type at
// +0x30 and the ICF-folded Weapon::setLeechRangeActive (0x002D95FE) a flag.
class Rva002D94CE { public: void rva002D94CE(int value); };
#include "../../../GameEngine/Include/GameLogic/Weapon.h"
class Rva002D9BDC { public: void rva002D9BDC(float lo, float hi); };
// WorldBuilder calls this AudioEventRTS::setExtraVolumeMultiplier; retail
// folded it to 0x00481FAF, rowed under this neutral float-slot name.
class Rva00481FAFFloatSlot { public: void store(float value); };
// The event's own xfer (rowed at 0x002D9FD9 under an address-derived owner).
class Rva002D9FD9Arg;
class Rva002D9FD9Owner { public: void rva002D9FD9(Rva002D9FD9Arg *xfer); };
// Float-returning event query rowed at 0x002DA153; prep3DSample compares it
// with AudioSettings +0xB8 to treat a sound as global.
class Rva002DA153 { public: float rva002DA153(void); };
// Event pitch-shift multiplier (rowed 0x002D94DD, a const float product
// getter); initFilters3D scales the 3D playback rate by it when non-zero.
class Rva002D94DD { public: float rva002D94DD(void) const; };
// 8-byte record of the manager's +0xB54 vector: 0x55C5D passes +0x00 to
// Object::isInside(PolygonTrigger *) and keeps the lowest +0x04 level whose
// trigger holds the event. Names are descriptive.
// +0x44 is the trigger ID xfer saves and loadPostProcess looks up again.
class PolygonTrigger {
public:
    bool rva002E3A39(const Coord3D &pos);
    int getID(void) const { return m_triggerID; }
private:
    char at00[0x44];
    int m_triggerID;
};
class Object { public: bool isInside(PolygonTrigger *trigger); };
extern GameLogic *TheGameLogic;
inline float sqr(float value) { return value * value; }

// 0x53854's 2D distance steps, inlined as retail inlined them.
inline Coord2D &subtractXY(Coord2D &v, const Coord3D &that) { v.x -= that.x; v.y -= that.y; return v; }
inline float lengthSqrdXY(const Coord2D &v) { return v.x * v.x + sqr(v.y); }

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

// The same five corners as recalculateMicrophone's local (rowed: element
// ctor 0x00051CA2 with the folded empty dtor; array ctor 0x00052751) and the
// rowed five-corner comparison 0x00051CF1.
class Rva00051CA2 {
public:
    Rva00051CA2();
    ~Rva00051CA2();
private:
    float x, y, z;
    bool active;
};
class ScreenToTerrainSet {
public:
    ScreenToTerrainSet();
    ~ScreenToTerrainSet() {}
    AudioAreaCorner &operator[](int i) { return reinterpret_cast<AudioAreaCorner *>(slots)[i]; }
private:
    Rva00051CA2 slots[5];
};
class Rva00051CF1 { public: bool rva00051CF1(Rva00051CF1 &other); };

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
// Use the folded erase bodies emitted by stlport_pod_vector_malloc_bodies.cpp.
namespace _STL {
template <> AudioTriggerArea *vector<AudioTriggerArea>::erase(AudioTriggerArea *, AudioTriggerArea *);
template <> AudioTriggerAreaSave *vector<AudioTriggerAreaSave>::erase(AudioTriggerAreaSave *, AudioTriggerAreaSave *);
}
// xfer (0x0005E3E5) appends through the no-EH 8-byte push_back 0x00539A2E,
// which stlport_vector_e8_allocate_copy.cpp instantiates; this /EHsc unit
// would emit another _M_insert_overflow for it, so it only declares it.
template<> void _STL::vector<AudioTriggerAreaSave, _STL::allocator<AudioTriggerAreaSave> >::push_back(const AudioTriggerAreaSave &value);

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
    float m_at00;                        // +0x00, fraction past the far limit
    float m_at04;                        // +0x04, squared-distance scale
    float m_at08;                        // +0x08, numerator between the limits
    float m_at0C;                        // +0x0C, near squared limit
    float m_at10;                        // +0x10, numerator past the far limit
    float m_at14;                        // +0x14, far squared limit
    float m_at18;                        // +0x18, pull toward corner 0
    float m_at1C;                        // +0x1C, attenuation start distance
    float m_at20;                        // +0x20, squared distance below which nothing attenuates
    float m_at24;                        // +0x24, attenuation end distance
    float m_at28;                        // +0x28, squared end distance
    float m_at2C;                        // +0x2C, maximum attenuation
    float m_at30;                        // +0x30
    float m_at34;                        // +0x34
    float m_at38;                        // +0x38, outer corner distance
    float m_at3C;                        // +0x3C, outer squared limit
    float m_at40;                        // +0x40, inner corner distance
    float m_at44;                        // +0x44, inner squared limit
};

struct AudioSettings {
    char at00[0x30];
    float m_at30[5];                     // +0x30, init()'s per-index 0x524EE volumes
    char at44[0x64 - 0x44];
    int m_at64;                          // +0x64, with +0x68 init()'s loop-buffer count
    int m_sampleCount3D;                          // +0x68
    char at6C[0x74 - 0x6C];
    int m_globalMaxRange;
    int m_timeToFadeAudio;                          // +0x78, compared with a loop's +0x30 (0x59CE6)
    int m_ambientStreamHysteresisVolume;
    unsigned int m_at80;                 // +0x80, handed to the file cache's 0xA77D9
    char at84[0x8C - 0x84];
    unsigned int m_at8C;                 // +0x8C, over +0x90 the loop-buffer thread's sleep
    unsigned int m_at90;                 // +0x90
    char at94[0xA8 - 0x94];
    int m_forceResetTimeSeconds;                          // +0xA8, seconds before 0x61C87 reopens the device
    int m_atAC;                          // +0xAC, seconds before the update reopens the device
    float m_atB0;                        // +0xB0, position change 0x55C5D ignores
    int m_preloadLimit;                          // +0xB4, processRequest's preload limit
    float m_minSampleVolume;
    bool m_disableOcclusion;                         // +0xBC, disables occlusion
    char atBD[0xC0 - 0xBD];
    float m_occlusionFloor;                        // +0xC0, occlusion floor
    char atC4[0x12C - 0xC4];
    MicrophoneSettings m_microphoneSettings[3]; // +0x12C
};

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_distances(void *sample, float maxDistance, float minDistance);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_position(void *sample, float x, float y, float z);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_orientation(void *obj, float xFace, float yFace, float zFace, float xUp, float yUp, float zUp);
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
#include <limits>

struct Rva0005A084Element { int m_value; };
// Use the complete retail push_back at 0x0005A084 from StlportVectorPushBackFamily.
// push_back on this element is rowed in its overflow owner as vector<Rva00058BBDElement>.
struct Rva00058BBDElement { int a[1]; };
namespace _STL {
template <> void vector<Rva00058BBDElement>::push_back(const Rva00058BBDElement &);
template <> __declspec(dllimport) __forceinline void vector<Rva0005A084Element>::push_back(const Rva0005A084Element &x)
{ ((vector<Rva00058BBDElement> *)this)->push_back(*(const Rva00058BBDElement *)&x); }
}
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
            value_type(const unsigned int &a, const unsigned int &b) : first(a), second(reinterpret_cast<void *>(b)) {}
            unsigned int first;
            void *second;
        };
        struct insert_result
        {
            void *first;
            KeyToBucketMap *second;
            bool inserted;
        };
        struct equal_result
        {
            void *node;
            KeyToBucketMap *table;
        };
        insert_result insert(const value_type &value);
        equal_result rva00057C5C(const value_type &value);
    };
};

// Logical/physical handle alias tables at +0x104/+0x118 (mapLogicalHandleToPhysicalHandle).
typedef _STL::hash_multimap<unsigned int, int> MilesKeyAliases;
typedef _STL::hash_map<unsigned int, int> MilesPhysicalHandles;

class AILMutexScope {
public:
    AILMutexScope() { AIL_lock_mutex(); m_locked = true; }
    ~AILMutexScope() { if (m_locked) AIL_unlock_mutex(); }
    void unlock(void) { if (m_locked) { AIL_unlock_mutex(); m_locked = false; } }
private:
    bool m_locked;
};

// Native bucket erasure inlines this allocator/deletion chain. Keep the
// bfmealloc/STLport definitions visible without emitting redundant COMDATs
// that would replace other units' differently compiled out-of-line copies.
typedef MilesKeyAliases::iterator::_Node MilesAliasNode;
typedef MilesKeyAliases::iterator::_Hashtable MilesAliasTable;
namespace _STL {
// Native 0x56B39 keeps an unwind state around clear(): C++ free may throw.
// The C-linkage declaration lets cl elide that state and emits only 24/57 bytes.
template<> __declspec(dllimport) __forceinline
void allocator<MilesAliasNode>::deallocate(MilesAliasNode *p, size_t n) const
{ if (p != 0) _STL::free((void *)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<unsigned int, MilesAliasNode, allocator<MilesAliasNode> >::deallocate(MilesAliasNode *p, size_t n)
{ static_cast<allocator<MilesAliasNode>&>(*this).deallocate(p, n); }
// ?MilesAliasTable::_M_delete_node present-unmatched
template<> __declspec(dllimport) __forceinline
void MilesAliasTable::_M_delete_node(MilesAliasNode *milesAliasNode)
{ _Destroy(&milesAliasNode->_M_val); _M_num_elements.deallocate(milesAliasNode, 1); }
}

// Miles handle -> PlayingAudio maps at +0xB98/+0xBAC/+0xBC0. The mapped
// value is the raw PlayingAudio pointer (node +8); it is viewed as void *
// so the lookup binds the pinned folded _M_find at 0x002888D4.
// The sample/stream handle maps share their destructor 0x00056B39 with the
// +0x104/+0x118 tables; the address-named hash keeps their instantiation apart.
typedef _STL::hash_map<unsigned int, void *> MilesHandleMap;
struct Rva00056B39Hash : public _STL::hash<unsigned int> {};
typedef _STL::hash_map<unsigned int, void *, Rva00056B39Hash> MilesSampleHandleMap;

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

// Range-erase provider for the alias multimap (rowed 0x00056B0A); the hash
// functors are never called by erase, so the file's rts views are reused.
enum NameKeyType;
class DamageFX { public: int m_valueWords[0x1E0]; };
typedef _STL::hash_map<NameKeyType, DamageFX, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ExistingRangeErase;
namespace _STL { template<> void ExistingRangeErase::erase(ExistingRangeErase::iterator, ExistingRangeErase::iterator); }

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
// Retail keeps one vector<BfmePod8>::erase (0x00054B3F); this unit calls it
// rather than leading link order with its own copy.
namespace _STL {
template <> BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *);
}

// Tree-like member at GlobalVolumeData +0x1B8; its clear is rowed at
// 0x00057B74 under this address-derived name.
class Rva00056CF8 {
public:
    void rva00057B74(void);
    unsigned int rva0005B633(const AsciiString &key);
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
    char at04[0x08 - 0x04];
    AudioEventInfo *m_info;                // +0x08, named by the 0x000609A1 sweep
    unsigned int m_playingHandle;  // +0x0C
    char at10[0x88 - 0x10];
    float m_at88;
    bool m_at8C;
    char at8D[3];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<BfmeStringTailRecord144>(BfmeStringTailRecord144 *p) { typedef BfmeStringTailRecord144 BfmeDestroyT; p->~BfmeDestroyT(); } }
// Use the whole-body verified range destructor at 0x5401D.
namespace _STL { template <> void __destroy_aux<BfmeStringTailRecord144 *>(
    BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, const __false_type &); }
// Retain the same native range wrapper as the overflow and dtor owners.
namespace _STL { template <> void _Destroy<BfmeStringTailRecord144 *>(
    BfmeStringTailRecord144 *, BfmeStringTailRecord144 *); }
typedef _STL::vector<BfmeStringTailRecord144> QueuedAudioEvents;
template <> QueuedAudioEvents::~vector();
namespace _STL { template <> _Vector_base<BfmeStringTailRecord144, allocator<BfmeStringTailRecord144> >::~_Vector_base(); }
template<> QueuedAudioEvents::iterator QueuedAudioEvents::erase(iterator first, iterator last);

// Owning AudioEventInfo reference returned by the slot-75 lookup.
class Rva00051ADA {
public:
    ~Rva00051ADA() { if (m_ptr) m_ptr->Release_Ref(); }
    AudioEventInfo *get() const { return (AudioEventInfo *)m_ptr; }
private:
    OpaqueRefCounted *m_ptr;
};
class AudioEventInfoRef {
public:
    // Retail 0x00051914 (AudioEventInfoRefConstructor.cpp; this unit's struct
    // AudioEventInfo spelling is a byte-identical alias there).
    __declspec(noinline) AudioEventInfoRef(const AudioEventInfo *info) : m_ptr(reinterpret_cast<OpaqueRefCounted *>(const_cast<AudioEventInfo *>(info))) { if (m_ptr) m_ptr->Add_Ref(); }
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
// Built by the folded hash-container constructor 0x0005B505 like every
// other 0x14-byte table of the manager.
class Rva00059FBBMap : public _STL::hash_map<AsciiString, AudioEventInfo *,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > {
public:
    AudioEventInfo *&rva00059FBB(const AsciiString &name);
};

// Address-derived callee view for the tree lookup used at 0x0005B1C2.
class Rva001F8437 {
public:
    void *rva001F8437(const AsciiString &key);
};


// Rowed at 0x0005F279 under its address-derived host.
class Rva0005F279Host { public: void rva0005F279(void); };

// MilesAudioManager's primary base: the vftable at +0x00 starts with the
// scalar deleting destructor (0x00061AA1), and the Snapshot subobject sits at
// +0x0C (its vftable holds the 0x0005D41D destructor thunk, loadPostProcess
// 0x000587C6, the name getter 0x000518B2 and the xfer 0x0005E3E5), so the
// base before it is SubsystemInterface's 12 bytes: vptr, +0x04 flag and the
// +0x08 name (layout of the rowed SubsystemInterface constructor 0x001B4E63).
typedef bool Bool;
#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"

// Native base constructor 0x0005107D: SubsystemInterface 0x001B4E63, then
// the Snapshot and the abstract base's own vftables (BC5148/BC5138) -- Zero
// Hour's AudioManager, which MilesAudioManager derives from.
// Its destructor is the rowed 0x0005109D (address-named class there).
class Rva005109D : public SubsystemInterface, public Snapshot {
public:
    virtual ~Rva005109D();
};
class AudioManager : public Rva005109D {
public:
    AudioManager();
};
// Coord3D members the constructor initializes in place (WB 0x7803C0 stores
// x, y, z before the corner records are built).
struct MilesCtorCoord3D : public Coord3D {
    MilesCtorCoord3D(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
// Per-view volume record (0x1C4 bytes): eh-vector constructed through
// ctor 0x0005A2E6 / dtor 0x0005925E; methods use the GlobalVolumeData view.
class Rva006ABC60 { public: Rva006ABC60(); ~Rva006ABC60(); int m_myViewFocus; private: char m_body[0x1C0]; };
// The manager's mutex at +0x9D4, built by the rowed Mutex(1, 0, 0) 0x00040F1E.
// Its virtual destructor is the rowed 0x00040EDB (address-named class there).
#include "../../../GameEngine/Include/Common/Rva00041004Lock.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
class Mutex : public Rva0040EDB { public: Mutex(int, const char *, void *); };
// Objects the constructor allocates: 0x204-byte settings (ctor 0x00041589)
// and the 0xF4-byte record at +0x14 (ctor 0x001ED70C).
// The +0xB90 stream owner: zero-initialized in place and destroyed on unwind
// (the constructor's EH map gives it its own state); readers take the pointer.
class Rva00A897D { public: virtual ~Rva00A897D(); void rva000A89C1(void); };

class MilesStreamOwnerRef {
public:
    MilesStreamOwnerRef() : m_owner(0) {}
    __declspec(noinline) ~MilesStreamOwnerRef()
    {
        Rva00A897D *owner = static_cast<Rva00A897D *>(m_owner);
        m_owner = 0;
        if (owner) {
            owner->Rva00A897D::~Rva00A897D();
            ::operator delete(owner);
        }
    }
    operator void *() const { return m_owner; }
private:
    void *m_owner;
};
class Rva000416E7 { public: Rva000416E7(); virtual ~Rva000416E7(); private: char m_body[0x200]; };
class Rva001ED70C { public: Rva001ED70C(); ~Rva001ED70C(); private: char m_body[0xF4]; };
class Image;
typedef _STL::map<unsigned int, Image *> Rva0005B256HandleMap;
// +0xB78: built by the folded hash constructor like the handle maps but
// destroyed by its own 0x00057AEE, so a distinct table type.
typedef _STL::hash_map<unsigned int, Image *> Rva00056DA2Map;
// +0xB6C: the folded map constructor 0x0033C432 builds it and its own
// 0x000554FA destroys it, apart from map<unsigned, Image*>'s 0x002D922A.
struct Rva00053DC5Less : public _STL::less<unsigned int> {};
typedef _STL::map<unsigned int, Image *, Rva00053DC5Less> Rva00053DC5Map;
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64 *);

class Rva00057151 { public: void rva00057151(int, int, int); };
class Rva0036CA00Str;
struct Rva0010F149Handle;
class Rva00052B3D;
struct BfmeAudioEventPrefix136;
struct Rva000527E2Event;
struct BfmeEventPositionView;
class MilesAudioManager : public AudioManager {
public:
    MilesAudioManager();
    virtual ~MilesAudioManager();
    // SubsystemInterface supplies slots 0..13; later virtuals retain retail order.
    virtual void init();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual void reset();
    // Slot 10 (retail 0x00062690) is the per-frame update below.
    virtual void update(); virtual void rva00061C87(unsigned int viewMask);
    virtual void stopAudio(enum AudioAffect affect); virtual void rva000583BA(unsigned int affect, unsigned int viewMask, int arg); virtual void rva00058591(unsigned int affect, unsigned int viewMask, int keepMasks); virtual void rva0005CAE2(); virtual void rva0005CB39();
    virtual void setViewFocus(int viewType); virtual int rva0005189D() const; virtual void rva0005116B(); virtual void slot23(const int &a); virtual void rva0005DACF(const int &a);
    virtual void rva0005DABB(int a); virtual void removePlayingAudio(const AsciiString &eventName, int viewType); virtual void rva00057787(unsigned int id);
    // Slot 28 (+0x70): kills the sound playing under a handle and reports
    // whether it did (playAudioEvent's handle-to-kill test; Zero Hour name).
    virtual bool killAudioEventImmediately(unsigned int handle); virtual void rva0005DAE6(int a, int b);
    virtual void rva00057408(unsigned int key); virtual bool rva000527E2(const Rva000527E2Event *event); virtual bool rva00055E6C(const AsciiString &name, int streamArg, int viewType, int musicSystem); virtual int rva0005A7BE(AudioEventRTS *event, int arg1); virtual void rva00055A58(int viewType, int musicSystem, int arg, int flag);
    virtual void rva00055B40(int viewType, int musicSystem, int arg); virtual void rva000568CE(int viewType, int musicSystem, int arg); virtual void rva000569A8(int viewType, int musicSystem, int arg, int flag); virtual void rva000567F4(int viewType, int musicSystem, int arg); virtual int rva000518A4(int index);
    virtual int rva00052917(); virtual bool rva0005538C(void); virtual AsciiString rva00054714(void); virtual void rva0005BD20(); virtual void rva0005BD28();
    virtual void rva0005E322(const AsciiString *key, int idx); virtual void rva00059DF5(const AsciiString &a, int idx); virtual void rva00059E5C(int idx); virtual void rva0005CA03(void *a, float b, int idx); virtual void rva0005E377(const AsciiString &key, int viewType);
    virtual void rva0005CA75(int a); virtual void rva0005A95B(unsigned int key, Rva0005A084Vector *output); virtual bool rva000572DC(unsigned int key); virtual void rva00057378(unsigned int key, const void *value); virtual bool rva00057492(unsigned int key, BfmeEventPositionView *output);
    virtual void rva00057530(unsigned int key, float value, int mode); virtual unsigned char rva0005164F(unsigned char soundClass); virtual void rva0005168C(unsigned char val, unsigned char flags); virtual void rva0005CB90(int a, float b); virtual void rva00053CE1(float volume, int flags, int idx);
    virtual void rva0005C8BB(float volume, int flags); virtual void rva000537F4(float a, float b, float c, float d, float e, int index); virtual void rva00059A25(const AsciiString &name, int idx); virtual void rva0005E168(const AsciiString &s, int idx); virtual void rva00059A7C(int idx);
    virtual void rva000515AB(); virtual void rva000515B3(int value); virtual void rva000533CB(); virtual unsigned char rva000515A4() const; virtual void rva000517F1();
    virtual void rva0005181B(); virtual void rva00051840(); virtual const MilesCtorCoord3D &slot72() const { return m_micPos; } virtual Rva0010F149Handle newOwnedAudioEventInfo(const AsciiString &name, int context); virtual void addUnownedAudioEventInfo(AudioEventInfo *eventInfo);
    virtual Rva00051ADA findAudioEventInfo(const AsciiString &name) const;
    // Slots 76..106 are not named here; slot 107 (+0x1AC, retail vftable
    // 0x007C55B0) is the rowed 0x000516EF.
    virtual void friend_onAudioEventInfoDestruction(AudioEventInfo *info); virtual AudioSettings *slot77() const { return m_audioSettings; } virtual Rva001ED70C *slot78() const { return m_at14; } virtual Rva001ED70C *slot79() const { return m_at14; } virtual float getAudioLengthMS(const BfmeAudioEventPrefix136 *event);
    virtual int bfmeMilesPreferenceProduct(); virtual void rva0005185E(int *a, int *b, int *c); virtual bool isMusicAlreadyLoaded() const; virtual unsigned char rva00051896() const; virtual void rva0005AE2B(int type, Rva0005A084Vector *output);
    virtual void rva0005AEDD(int type, Rva0005A084Vector *output); virtual void *rva0055D96F() const; virtual void rva000596E9(Xfer *xfer, unsigned int *handle); virtual void rva0005522C(const AsciiString &name); virtual AsciiString rva00054243() const;
    virtual void rva000530DF(); virtual const _STL::vector<const char *> &rva00058314();
    // Slots 93/94 (+0x174/+0x178, vftable entries 0x007C5724/0x007C5728):
    // set or (level 1.0) drop a trigger area's audio level.
    virtual void rva0005824D(PolygonTrigger *trigger, float level);
    virtual void rva000551C2(int key);
    virtual void rva0005710F();
    virtual void rva000512BC(); virtual bool rva000619D1(bool enabled);
    // Slot 98 (+0x188, retail vftable entry 0x007C5738).
    virtual void onAudioLODChanged(void);
    virtual bool rva000531F6(); virtual void rva000514BB();
    virtual void rva00053281(); virtual void rva0005329C(); virtual void friend_xferSubAudioEventRTS(Xfer *xfer, BfmePoolRef10 *eventRef); virtual void slot104() {}
    virtual void rva000511C3(Coord3D *out);
    virtual void getScreenToTerrainPositions(ScreenToTerrainSet *corners);
    virtual bool rva000516EF(const Coord3D *pos);
    // Slot 109 (+0x1B4) returns the frame's elapsed time the update keeps at +0x90.
    virtual unsigned char slot108(BfmeAudioEventPrefix136 *); virtual float rva0005121F();
    // Slot 110 (+0x1B8), the first call init() makes.
    virtual void rva000541DB(void);
    bool rva00055FCA(int key, void **result, PlayingAudioRef *playingOut);
    bool rva0005623E(int key, void **result, int flags);
    void rva000563FE(Xfer *xfer, int handle);
    void rva0005634C(int handle, float volume, int mode);
    bool rva00054899(ObjectID objectID, int otherID);
    bool rva00056670(ObjectID objectID);
    bool rva00055426(int objectID);
    float getGlobalReverbMultiplier(void);
    void rva00053AFA(void *pendingSlot);
    void rva000562CF(int key);
    void rva000562A2(int key, const void *value);
    void rva0005A92A(int key, Rva0005A084Vector *output);
    void rva0005B137(void);
    void recalculateMicrophone(void);
    void rva0005BE59(void *slot, float value, void *index);
    AsciiString rva0005B19E(const AsciiString &key);
    AsciiString rva0005B1FA(const AsciiString &key);
    // These audio INI calls use the manager receiver and an explicit INI*.
    // The receiver type is supported by 0x61BD2's +0x9D4 mutex access; names
    // for 0x5407E/0x540A7 remain address-derived, with helper identity open.
    void rva0005407E(INI *ini);
    void rva000540A7(INI *ini);
    unsigned char rva00054120(INI *ini);
    void rva0006179C(int skipRequestRefresh);
    PlayingAudioList::iterator rva000544CB(int viewType, int musicSystem, int filter);
    PlayingAudioList::iterator rva0005442A(int viewType, int musicSystem, int filter);
    void rva00057297(Rva00051107AudioRequest &request);
    bool rva000570C8(AudioEventRTS *event);
    AudioEventRTS *findLowestPrioritySound(AudioEventRTS *event);
    bool killLowestPrioritySoundImmediately(AudioEventRTS *event);
    // First free 3D and 2D Miles sample (Zero Hour's getFirst3DSample and
    // getFirst2DSample play this role), rowed at 0x00054596 and 0x0005456B.
    int rva00054596(void);
    int rva0005456B(void);
    float rva0005A9F8(void *ref, int a, int b);
    float rva00059AD0(void *event, int a);
    void unmapPhysicalHandle(unsigned int handle);  // WorldBuilder name (0x000578B3)
    void mapLogicalHandleToPhysicalHandle(unsigned int logical, unsigned int physical);
    void rva00057948(const void *input);
    void rva000577E3(unsigned int affect, unsigned int viewMask, bool value);
    // Ledger rows name it (refreshAll/rva00052048 share its this).
    class GlobalVolumeData {
    public:
        static void setGlobalSystemVolume(int volumeType, float volume);
        void reset(void);
        void rva00052048(int index);
        void rva00052015(int arg);
        unsigned char rva000520F4(const AudioEventInfoRef &, int);
        float rva0005910F(AudioEventRTS *event);
        void refreshAll(void);
        // Distance attenuation of +0x94 (WB 0x77A260, unnamed) from the
        // per-view microphone settings and the camera-to-microphone offset.
        void rva0005213E(const MicrophoneSettings *settings, const Coord3D *delta);
        // Per-view volume state transfer (rowed 0x0005CE7E).
        void rva0005CE7E(Xfer *transfer);
        // Per-frame step with the frame time (0x000521F4, pinned) and the
        // end-of-frame step (rowed 0x000520C6); both from the update 0x62690.
        void rva000521F4(float elapsed);
        void rva000520C6(void);

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
    void removeAllAudioRequests(unsigned int viewMask);
    void rva0005B256(Xfer *xfer, PlayingAudioRef &playing, int *unused);
    bool rva000613A9(unsigned int handle);
    bool rva006AD9B0(void);    // 0x00059646, cached reinitialize setting
    void rva0005E0A4(void);    // 0x0005E0A4 (pinned), called by the update
    void rva0005B708(void);    // 0x0005B708 (rowed in MilesAudioSubtitleDrain.cpp)
    void processAmbientStreams(PlayingAudioList::iterator *streams);
    void rva00060309(void);
    void rva0006047C(void);
    void rva000603ED(void);
    void rva000544EB(void);
    void startPendingMusicTracks(void);
    void processPlayingList(Rva00052B3D *streams);
    int rva00052F1E(void *);
    void adjustPlayingVolume(void *ref);
    bool processFade(PlayingAudioRef &playing);
    void openDevice(void);
    void removeCurrentlyPlayingMusic(int viewType, int arg);
    /* the rowed Rva00057151::rva00057151 */ __declspec(dllimport) __forceinline void rva00057151(int p0, int p1, int p2) { ((Rva00057151 *)this)->rva00057151(p0, p1, p2); }
    void moveDownMusicSystems(int viewType, MusicSystem newMusicSystem, int arg, int resume);
    void rva0005774F(int viewType, int musicSystem, int arg);
    void rva0005876E(int viewType, int musicSystem, int arg, int resume);
    bool addAudioEventMusic(BfmePoolRef10 &event, int requestType, int append);
    int pushMusicEventInternal(AudioEventRTS *event, int arg1, int arg2, int append);
    int addResumeOrPushMultisound(AudioEventRTS *event, int requestType, int arg2, int arg3, int arg4, int arg5);
    BfmePoolRef10 rva0005286A(AudioEventRTS *event, int arg);
    void rva000592B8(AudioEventRTS *event);
    bool shouldPlayLocally(const AudioEventRTS *event);
    Rva00051107AudioRequest *rva00051107(void);
    void processRequest(Rva00051107AudioRequest *req, bool *removeRequest);
    void processRequestList(void);
    void deleteAudioRequest(void *req);
    bool rva00053606(Rva00051107AudioRequest *req);
    void rva00053646(Rva00051107AudioRequest *req, bool *removeRequest);
    void playAudioEvent(Rva00051107AudioRequest *req);
    void rva0005FA3C(unsigned int handle);
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
public:
    virtual void xfer(Xfer *transfer);
private:
    AudioSettings *m_audioSettings;      // +0x10 (Zero Hour name)
    Rva001ED70C *m_at14;
    MilesCtorCoord3D m_micPos;           // +0x18, Miles listener position
    MilesCtorCoord3D m_micDir;           // +0x24, Miles listener facing
    MilesCtorCoord3D m_cameraPos;        // +0x30, camera at the last recalculation
    ScreenToTerrainSet m_corners;             // +0x3C, entries 1..4 used by 0x53854
    float m_at8C;                        // +0x8C, distance occlusion scale
    float m_at90;                        // +0x90, zeroed by every xfer
    int m_at94;                          // +0x94, zeroed by 0x61C87
    Rva00051107AudioRequestList m_audioRequests;    // +0x98
    Rva00051107AudioRequestSet m_requestSet;        // +0x9C
    _STL::set<AsciiString> m_atB0;      // +0xB0, cleared by the constructor
    Rva00059FBBMap m_allAudioEventInfo;  // +0xBC
    unsigned int m_nextHandle;           // +0xD0, next playing handle (0x0005B256)
    // Zero Hour's inline AudioManager::allocateNewHandle.
    unsigned int allocateNewHandle(void) { return m_nextHandle++; }
    _STL::vector<OpaqueRefElement4> m_atD4;  // +0xD4 (destroyed by 0x00057994)
    QueuedAudioEvents m_queuedEvents[3];  // +0xE0, per view type (0x60123)
    // Native handle-map operations establish these two 20-byte tables.
    MilesKeyAliases m_handleAliases;       // +0x104
    MilesPhysicalHandles m_physicalHandles; // +0x118
    // Per-view GlobalVolumeData records, 0x1C4 apart in retail (0x61C87).
    Rva006ABC60 m_volumeData[3];         // +0x12C
    int m_at678;                         // +0x678, compared with event view types
    int m_at67C;
    int m_at680;
    int m_num2DSamplesPlaying;           // +0x684, counted up by playAudioEvent
    int m_num3DSamplesPlaying;           // +0x688, counted up by playAudioEvent
    int m_at68C;                         // +0x68C, zeroed by 0x60309
    unsigned int m_at690;                // +0x690, per-view-type bits 0x61C87 clears
    unsigned int m_musicPausedViewTypes;                // +0x694, view types whose music is paused for affect bit 0x20 (0x583BA)
    unsigned int m_at698;                // +0x698, per-view-type bits processAudioCompletion clears
    unsigned short m_maxAmbientStreams;  // +0x69C
    bool m_at69E, m_at69F, m_at6A0, m_at6A1, m_at6A2, m_at6A3;
    bool m_at6A4;                        // +0x6A4
    bool m_viewTypeChanged;                        // +0x6A5, marks a view-type change (0x5DAFC, xfer)
    bool m_forceHeadphones;             // +0x6A6, provider speaker override
    bool m_at6A7;                        // +0x6A7, read by 0x52F4C and 0x53AFA
    bool m_at6A8;                        // +0x6A8, cleared by the update
    bool m_areasNeedRetest;                        // +0x6A9, set by the update when areas need a retest
    bool m_retestAreasEveryCall;                        // +0x6AA, retest areas on every call (0x55C5D)
    bool m_at6AB;                        // +0x6AB, set by loadPostProcess
    bool m_at6AC;                        // +0x6AC, cleared by loadPostProcess
    char at6AD[0x6B0 - 0x6AD];
    int m_at6B0;                         // +0x6B0, zeroed by a loading xfer
    unsigned int m_at6B4[3];             // +0x6B4 per-view-type affect masks
    unsigned int m_at6C0[3];             // +0x6C0
    // Zero Hour's ProviderInfo array; unselectProvider (0x53352) indexes it
    // by m_selectedProvider and 0x607BB compares the selected name.
    struct ProviderInfo { AsciiString name; void *id; int isValid; };
    ProviderInfo m_provider3D[64];       // +0x6CC
    unsigned int m_providerCount;        // +0x9CC
    unsigned int m_selectedProvider;     // +0x9D0, -1 when none
    Mutex m_mutex;                       // +0x9D4
    int m_at9DC;
    void *m_listener;                    // +0x9E0 (Zero Hour name), unselectProvider closes it
    int m_at9E4;
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
    Rva00053DC5Map atB6C;           // +0xB6C, cleared through the rowed 0x00054B9A
    Rva00056DA2Map atB78;           // +0xB78, cleared through the rowed 0x00056DA2
    AudioFileCache *m_audioFileCache;    // +0xB8C (WorldBuilder requestFile receiver)
    MilesStreamOwnerRef m_atB90;         // +0xB90, handed to the stream opener 0x000A8D0B
    PlayingAudioList m_completedAudio;   // +0xB94, filled by the EOS handlers
    MilesSampleHandleMap m_sampleMap;          // +0xB98
    MilesSampleHandleMap m_3DSampleMap;        // +0xBAC
    MilesSampleHandleMap m_streamMap;          // +0xBC0
    LoopBuffer *m_loopBuffers;           // +0xBD4 (WB assert name)
    int m_numLoopBuffers;                // +0xBD8
    void *m_loopBufferThread;            // +0xBDC, CreateThread handle
    bool m_stopLoopBufferThread;                        // +0xBE0, stops the 0x5EFE9 thread loop
    char atBE1[0xBE4 - 0xBE1];
    int m_reverbRoomType;                         // +0xBE4, reverb room type (0x530DF zeroes it)
    class SubTitleWindow *m_subTitleWindow; // +0xBE8, deleted by the update once finished
    unsigned int m_viewTypesResetSinceUpdate;                // +0xBEC, view types reset since the last update
    int m_selectedSpeakerType;          // +0xBF0, provider-selection speaker type
    char atBF4[0xBF8 - 0xBF4];
    __int64 m_lastDeviceOpenTime;                     // +0xBF8, _time64 of the last device open
    bool m_transferViewType2;                        // +0xC00, view type 2 is transferred when set (version 3+)
};

namespace _STL {
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}

// ??0MilesAudioManager@@QAE@XZ @0x0005CF5F 1214B (native 0x0005CF5F..
// 0x0005D41D, RET0; the served 0x0005CF69 is interior, after the EH prolog).
// WB 0x007803C0 is the same constructor (members in declaration order);
// Zero Hour's MilesAudioManager/AudioManager constructors are the semantic
// guide: listener orientation (0,1,0), provider index -1, the settings and
// misc-audio allocations and the file cache sharing the manager mutex.
MilesAudioManager::MilesAudioManager()
    : m_audioSettings(0), m_at14(0), m_micPos(0.0f, 0.0f, 0.0f), m_micDir(0.0f, 1.0f, 0.0f),
      m_cameraPos(0.0f, 0.0f, 0.0f), m_at8C(0.0f), m_at90(g_00DBA4FC), m_at94(0),
      m_nextHandle(5), m_at678(2), m_at67C(0), m_at680(0),
      m_num2DSamplesPlaying(0), m_num3DSamplesPlaying(0), m_at68C(0), m_at690(0), m_musicPausedViewTypes(0), m_at698(0),
      m_maxAmbientStreams(2), m_at69E(true), m_at69F(true), m_at6A0(true), m_at6A1(true), m_at6A2(true),
      m_at6A3(false), m_at6A4(false), m_viewTypeChanged(false), m_forceHeadphones(false), m_at6A7(false),
      m_at6A8(false), m_areasNeedRetest(false), m_retestAreasEveryCall(false), m_at6AB(true), m_at6AC(false), m_at6B0(0),
      m_providerCount(0), m_selectedProvider((unsigned int)-1), m_mutex(1, 0, 0),
      m_at9DC(0), m_listener(0), m_at9E4(0),
      m_audioFileCache(0),
      m_loopBuffers(0), m_numLoopBuffers(0), m_loopBufferThread(0), m_stopLoopBufferThread(false), m_reverbRoomType(0),
      m_subTitleWindow(0), m_viewTypesResetSinceUpdate(7), m_selectedSpeakerType(0), m_lastDeviceOpenTime(_time64(0)), m_transferViewType2(false)
{
    m_atB0.clear();
    for (int i = 0; i < 3; ++i) {
        GlobalVolumeData *volume = reinterpret_cast<GlobalVolumeData *>(&m_volumeData[i]);
        m_activeMusicSystem[i] = MUSIC_SYSTEM_0;
        volume->m_myViewFocus = i;
        m_at6B4[i] = 0;
        m_at6C0[i] = 0;
    }
    m_audioSettings = reinterpret_cast<AudioSettings *>(new Rva000416E7());
    m_at14 = new Rva001ED70C();
    m_audioFileCache = new AudioFileCache(&m_mutex);
}

// Rowed under address-derived names at 0x00051038 (pinned) and 0x00050FE3;
// the destructor below hands its Miles handles back through them.
class Rva0005F279Elem { public: bool rva00051038() throw(); bool rva0005106A(); };
// The guarded 2D and 3D playing-sample count decrements (WorldBuilder's
// notifyOf2DSampleCompletion/notifyOf3DSampleCompletion), rowed at 0x000514EB
// and 0x000514FB under an address-derived owner.
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
    volatile bool m_heldPaused;                // +0x01, shared with the loop-buffer thread; held paused
    bool m_is3D;                         // +0x02 selects the handle below
    bool m_completionCheckPending;                         // +0x03, completion check pending
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
    : m_isValid(false), m_heldPaused(false), m_is3D(true), m_completionCheckPending(false), m_3DSample(0), m_sample(0),
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
    source->m_startedPlaying = true;
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
    if (buffer->m_completionCheckPending) {
        checkForNaturalSoundCompletion(PlayingAudioRef(buffer->m_playingAudio));
        buffer->m_completionCheckPending = false;
    }
    if (buffer->m_is3D) {
        if (buffer->m_3DSample) {
            if (buffer->m_playingAudio) {
                AILMutexScope lock;
                MilesSampleHandleMap::iterator it = m_3DSampleMap.find(reinterpret_cast<unsigned int &>(buffer->m_3DSample));
                if (it == m_3DSampleMap.end())
                    lock.unlock();
                else if ((*it).second != buffer->m_playingAudio)
                    lock.unlock();
                else
                    m_3DSampleMap.erase(it);
            }
            m_available3DSamples.push_back(buffer->m_3DSample);
            buffer->m_3DSample = 0;
            notifyOf3DSampleCompletion();
        }
    } else if (buffer->m_sample) {
        if (buffer->m_playingAudio) {
            AILMutexScope lock;
            MilesSampleHandleMap::iterator it = m_sampleMap.find(reinterpret_cast<unsigned int &>(buffer->m_sample));
            if (it == m_sampleMap.end())
                lock.unlock();
            else if ((*it).second != buffer->m_playingAudio)
                lock.unlock();
            else
                m_sampleMap.erase(it);
        }
        m_availableSamples.push_back(buffer->m_sample);
        buffer->m_sample = 0;
        notifyOf2DSampleCompletion();
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
                        source->m_startedPlaying = true;
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
                        source->m_startedPlaying = true;
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

// Retail 0x00051E7D (WorldBuilder twin 0x0079C6F0 names it; BFME 1's
// StartAudioStream loop-count helper is the semantic donor): the loop count
// a stream is started or restarted with. Retail takes the event in EDX and
// reads nothing from ECX, so the fastcall's first register stays unused.
static int __fastcall getAppropriateStreamLoopCount(void *unusedEcx, const AudioEventRTS *event)
{
    const AudioEventInfo *info = event->m_info;
    if (!info)
        return 1;
    switch (info->m_atB0) {
    case 1:
    case 4:
    {
        bool looping = (info->m_control & 1) != 0;
        return looping ? 1000000 : 1;
    }
    case 3:
        return 1000000;
    case 0:
    {
        int loops = event->m_loopCount;
        if (loops == -12345)
            return 1000000;
        if (loops >= 1)
            return loops;
        return 1;
    }
    default:
        return 1;
    }
}

// Retail 0x00051EC2 (unnamed; WorldBuilder keeps it out of line at 0x007857C0
// and calls it from processRequest): whether a request's event lasts less
// than one client frame. Retail inlines every call and still emits this
// static copy under cl's register convention (handle in EAX).
static int rva00051EC2(const BfmePoolRef10 &event)
{
    return !(event->m_at64 >= g_00DBA4FC);
}

// Retail 0x0005DD40 (WorldBuilder twin 0x0079B840 names it from its asserts
// at lines 10100..10113): once a sound or stream stops on its own it checks
// that it is still tracked (a stream or music track among the playing
// streams or on its music stack or pending push/pop slot; a 2D or 3D sound
// among the playing sounds) and that a paused or resumed track was not
// merely parked; then the event waiting on this one (+0x10) is detached and
// counted down and once nothing else holds it back it is replayed through
// addOrResumeAudioEvent (0x0005D734) with its play count spent; otherwise a
// script-named event (+0x84) marks its playing audio (+0x4D). WorldBuilder
// only reports multisounds (type 3) and unknown types.
void MilesAudioManager::checkForNaturalSoundCompletion(PlayingAudioRef &playing)
{
    if (playing->m_event->getAt84().isEmpty() && playing->m_event->m_at10 == 0)
        return;
    if (playing->m_event->m_at4C)
        return;

    bool foundPlaying = false;
    bool foundOnStack = false;
    bool foundPending = false;
    PlayingAudioList::iterator it;
    PlayingAudioList::iterator end;
    int viewType;
    int type = playing->m_event->getAudioEventInfo()->m_atB0;
    switch (type) {
    case 0:
    case 1:
    case 4:
        it = m_playingStreams.begin();
        end = m_playingStreams.end();
        while (!foundPlaying && it != end) {
            foundPlaying = (*it == playing);
            ++it;
        }
        if (type == 0) {
            viewType = playing->m_event->m_viewType;
            MusicSystem musicSystem = playing->m_event->m_musicSystem;
            MusicStack::iterator stackIt = m_musicStack[viewType][musicSystem].begin();
            MusicStack::iterator stackEnd = m_musicStack[viewType][musicSystem].end();
            while (!foundOnStack && stackIt != stackEnd) {
                foundOnStack = (reinterpret_cast<PlayingAudioRef &>(*stackIt) == playing);
                ++stackIt;
            }
            foundPending = (m_playingMusic[viewType] == playing);
        }
        if (!foundPlaying && !foundPending && !foundOnStack)
            return;
        break;
    case 2:
        it = m_playingSounds.begin();
        end = m_playingSounds.end();
        while (!foundPlaying && it != end) {
            foundPlaying = (*it == playing);
            ++it;
        }
        it = m_playing3DSounds.begin();
        end = m_playing3DSounds.end();
        while (!foundPlaying && it != end) {
            foundPlaying = (*it == playing);
            ++it;
        }
        if (!foundPlaying && !foundPending && !foundOnStack)
            return;
        break;
    default:
        return;
    }

    if ((playing->m_at44 || playing->m_at46) && !playing->m_at48 && !foundPending && !foundOnStack)
        return;

    if (playing->m_event->m_at10 != 0) {
        BfmePoolRef10 waiting(reinterpret_cast<const BfmePoolRef10 &>(playing->m_event->m_at10));
        reinterpret_cast<Rva002D9AD4 *>(playing->m_event.get())->rva002D9AD4(BfmePoolRef10());
        waiting->decrementNumberOfEventsNeedingToBeDoneBeforeReplaying();
        if (waiting->m_at14 <= 0) {
            if (waiting->m_loopCount != -12345 && waiting->m_loopCount > 0)
                waiting->setNumberOfTimesToPlayMusicOrMultisound(waiting->m_loopCount - 1);
            if (waiting->m_loopCount == -12345 || waiting->m_loopCount > 0) {
                int how = 0;
                if (foundOnStack)
                    how = 2;
                addOrResumeAudioEvent(waiting.get(), how, 1, 1, 0);
                return;
            }
        }
    }
    if (!playing->m_event->getAt84().isEmpty())
        playing->m_raiseScriptFlagOnRelease = true;
}

// Retail 0x0005DF9D (WorldBuilder twin 0x0079C1D0, names from its asserts):
// a looping sound restarts its next loop, a stream whose type keeps looping
// restarts in place, anything else with portions left is requeued, and the
// rest is checked for natural completion and marked done.
void MilesAudioManager::processAudioCompletion(PlayingAudioRef &completedAudio)
{
    if (!completedAudio.get())
        return;
    unsigned int viewBit = 1 << completedAudio->m_event->m_viewType;
    // Retail tests the bits in memory but clears them with a fresh RMW.
    volatile unsigned int *viewBits = &m_at698;
    if ((*viewBits & viewBit) && completedAudio->m_event->m_info->m_atB0 == 1)
        m_at698 &= ~viewBit;
    if (completedAudio->m_event->m_info->m_control & 1) {
        if (completedAudio->m_event->m_portionToPlayNext == 0)
            ((Rva002D94FEDwordSlot *)completedAudio->m_event.operator->())->set(1);
        if (completedAudio->m_event->m_portionToPlayNext == 1 && startNextLoop(completedAudio))
            return;
    }
    completedAudio->m_event->advanceNextPlayPortion();
    if (completedAudio->m_event->m_portionToPlayNext != 3 && completedAudio->m_type != 4) {
        completedAudio->m_event->rva002D9ADC();
        rva00059CE6(completedAudio);
        return;
    }
    if (completedAudio->m_type == 4 && !completedAudio->m_event->m_at4C) {
        bool restart;
        switch (completedAudio->m_event->m_info->m_atB0) {
        case 0:
            restart = completedAudio->m_event->m_loopCount == -12345;
            break;
        case 1:
        case 4:
            restart = (completedAudio->m_event->m_info->m_control & 1) != 0;
            break;
        case 3:
            restart = true;
            break;
        default:
            restart = false;
            break;
        }
        if (restart) {
            AudioEventRTS *event = completedAudio->m_event.operator->();
            ((Rva000A8B23 *)&completedAudio->m_at0C)->rva000A8B23(getAppropriateStreamLoopCount(event, event));
            ((Rva000A8AB4 *)&completedAudio->m_at0C)->rva000A8AB4();
            return;
        }
    }
    checkForNaturalSoundCompletion(completedAudio);
    completedAudio->m_status = 1;
}

// Native 0005E0A4..0005E13C (WorldBuilder twin 0x0079C930, unnamed), called
// by the per-frame update after the request and playing passes: drains the
// +0xB94 completion list that the end-of-sample handlers fill. Each entry is
// taken off the list under the Miles mutex (the scope ends before the call),
// then handed to processAudioCompletion unlocked; the list is re-tested with
// the mutex held again. Name stays address-derived.
void MilesAudioManager::rva0005E0A4(void)
{
    for (;;) {
        PlayingAudioRef playing;
        {
            AILMutexScope lock;
            if (m_completedAudio.empty())
                break;
            playing = m_completedAudio.front();
            reinterpret_cast<OpaqueRefList &>(m_completedAudio).pop_front();
        }
        processAudioCompletion(playing);
    }
}

class Rva0036CA00Str;
class Rva00058B90 { public: void rva00058B90(const Rva0036CA00Str &t); };
class Rva00050D6C { public: int rva00050D6C(void); };
class Rva000A8A98 { public: int rva000A8A98(void); };
float GetGameAudioRandomValueReal(float lo, float hi, char *file, int line);
#define MILES_AUDIO_MANAGER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\MilesAudioDevice\\MilesAudioManager.cpp"
void __stdcall setStreamCompleted(void *streamCompleted);

// Retail 0x0005AADD (WorldBuilder twin 0x007A4860 names it): maps the stream
// handle to its playing audio, sets the loop count, end callback and start
// position, then parks music on its system's slot or stack, or queues any
// other stream and starts or pauses it.
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
// Reads the cycle time from the settings, then until m_stopLoopBufferThread is set refills
// every valid loop buffer under the manager mutex and sleeps out the cycle.
void MilesAudioManager::rva0005EFE9(void)
{
    unsigned int sleepTime = 50;
    {
        MilesMutexGuard guard(&m_mutex, 1);
        while (!guard.rva00041037(100)) {
            if (m_stopLoopBufferThread)
                return;
        }
        if (m_audioSettings)
            sleepTime = m_audioSettings->m_at8C / m_audioSettings->m_at90;
    }
    if (m_stopLoopBufferThread)
        return;
    do {
        unsigned int start = AIL_ms_count();
        for (int i = 0; i < m_numLoopBuffers; ++i) {
            LoopBuffer *buffer = &m_loopBuffers[i];
            if (!buffer->m_isValid)
                continue;
            MilesMutexGuard guard(&m_mutex, 1);
            while (!guard.rva00041037(100)) {
                if (m_stopLoopBufferThread)
                    return;
            }
            if (!buffer->m_isValid)
                continue;
            if (buffer->m_heldPaused) {
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
                    buffer->m_completionCheckPending = true;
                buffer->m_isValid = false;
            } else if (buffer->m_at44 && !wasFull) {
                ((Rva00050FC9 *)buffer)->rva00050FC9();
                pauseResumeSound(PlayingAudioRef(buffer->m_playingAudio));
            }
        }
        if (m_stopLoopBufferThread)
            return;
        unsigned int now = AIL_ms_count();
        if (now - start <= sleepTime)
            Sleep(start - now + sleepTime);
    } while (!m_stopLoopBufferThread);
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
        GlobalVolumeData::setGlobalSystemVolume(i, m_audioSettings ? m_audioSettings->m_at30[i] : 0.55f);
    m_numLoopBuffers = m_audioSettings->m_sampleCount3D + m_audioSettings->m_at64;
    m_loopBuffers = new LoopBuffer[m_numLoopBuffers];
    m_stopLoopBufferThread = false;
    m_loopBufferThread = CreateThread(0, 0, rva0005F267, this, 0, 0);
    openDevice();
    ((Rva000A77D9 *)m_audioFileCache)->rva000A77D9((void *)m_audioSettings->m_at80);
    AIL_set_file_callbacks(streamingFileOpen, (MilesFileCloseCallback)Rva000518E0Thunk,
        (MilesFileSeekCallback)rva006963B0ForwardSlot5, (MilesFileReadCallback)rva006963D0ForwardSlot3);
    setMaxAmbientStreams();
}

// Native61BD2..61C87 RET4 returns the persistent reload flag. The
// unnamed WB7896D0 lead's debug string says attemptReload, but its unused
// argument type is unresolved and retained as an opaque DWORD view.
// Existing INI extent888 and mutex9D4 are measured by matched siblings.
// Native interface slot16 is a cdecl varargs call consuming one wide
// string by value; this prefix view does not assert the other UI slots.
class Rva00061BD2MessageView {
public:
#define RELOAD_UI_SLOT(N) virtual void slot##N();
 RELOAD_UI_SLOT(0) RELOAD_UI_SLOT(1) RELOAD_UI_SLOT(2) RELOAD_UI_SLOT(3)
 RELOAD_UI_SLOT(4) RELOAD_UI_SLOT(5) RELOAD_UI_SLOT(6) RELOAD_UI_SLOT(7)
 RELOAD_UI_SLOT(8) RELOAD_UI_SLOT(9) RELOAD_UI_SLOT(10) RELOAD_UI_SLOT(11)
 RELOAD_UI_SLOT(12) RELOAD_UI_SLOT(13) RELOAD_UI_SLOT(14) RELOAD_UI_SLOT(15)
#undef RELOAD_UI_SLOT
 virtual void __cdecl message(UnicodeString text, ...);
};
class InGameUI;
extern InGameUI *TheInGameUI;
// Descriptive name: the native byteDE1E4C is initially zero and is set
// only after the manager's rowed audio INI reload reports success.
bool AudioEventsReloaded;

bool MilesAudioManager::vslot04(int unused)
{
 MilesMutexGuard guard(&m_mutex, 0);
 INI ini;
 ini.m_at08 = 5;
 if (rva00054120(&ini)) {
  AudioEventsReloaded = true;
  reinterpret_cast<Rva00061BD2MessageView *>(TheInGameUI)->message(
   UnicodeString((const unsigned short *)L"RIF: AudioEvents reloaded. Resetting audio engine"));
  rva0006179C(0);
 }
 return AudioEventsReloaded;
}

// The pending-request set's erase(iterator) is the rowed hashtable
// instantiation over Rva00051B89Keyed pointers (0x00054C44); the same set
// layout and hasher, reached through that type.
typedef _STL::hash_set<Rva00051B89Keyed *, Rva00051B89Hash, _STL::equal_to<Rva00051B89Keyed *> >
    Rva00051B89KeyedSet;
// Bind the bucket lookup to its rowed STLport instantiation.
namespace _STL {
typedef hashtable<Rva00051B89Keyed *, Rva00051B89Keyed *, Rva00051B89Hash, _Identity<Rva00051B89Keyed *>, equal_to<Rva00051B89Keyed *>, allocator<Rva00051B89Keyed *> > MilesKeyedTable;
template <> unsigned int MilesKeyedTable::_M_bkt_num_key(Rva00051B89Keyed *const &) const;
}

// Retail 0x00056FD9: drops the queued audio requests of the view types in
// viewMask (all of them for 7; a request without an event counts as view
// type 3, kept unless the mask is 7) from the request list and the pending
// request set, deleting each one.
void MilesAudioManager::removeAllAudioRequests(unsigned int viewMask)
{
    Rva00051107AudioRequestList::iterator it = m_audioRequests.begin();
    while (it != m_audioRequests.end()) {
        Rva00051107AudioRequest *request = *it;
        int viewType = 3;
        if (request->m_pendingEvent.get())
            viewType = request->m_pendingEvent->m_viewType;
        if (viewMask == 7 || (viewType != 3 && (viewMask & (1 << viewType)))) {
            it = m_audioRequests.erase(it);
            deleteAudioRequest(request);
        } else {
            ++it;
        }
    }
    Rva00051107AudioRequestSet::iterator pending;
    pending = m_requestSet.begin();
    while (pending != m_requestSet.end()) {
        Rva00051107AudioRequest *request = *pending;
        int viewType = 3;
        if (request->m_pendingEvent.get())
            viewType = request->m_pendingEvent->m_viewType;
        if (viewMask == 7 || (viewType != 3 && (viewMask & (1 << viewType)))) {
            Rva00051107AudioRequestSet::iterator doomed = pending;
            ++pending;
            reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(
                reinterpret_cast<Rva00051B89KeyedSet::iterator &>(doomed));
            deleteAudioRequest(request);
        } else {
            ++pending;
        }
    }
}

// The CRT clock, imported (this unit builds with /D_CRTIMP=).
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64 *timer);

// The file-text map's clear: the rowed hashtable clear at 0x00057FC1, under
// the address-derived element spelling its unit (StlSweepR3Rva00057FC1.cpp) uses.
struct Rva00057FC1Record { Rva00057FC1Record(); Rva00057FC1Record(const Rva00057FC1Record&); ~Rva00057FC1Record(); Rva00057FC1Record&operator=(const Rva00057FC1Record&); char bytes[1]; bool operator==(const Rva00057FC1Record&) const; bool operator<(const Rva00057FC1Record&) const; };
namespace _STL { template<> struct hash<Rva00057FC1Record> { unsigned int operator()(const Rva00057FC1Record&) const; }; }
typedef _STL::hashtable<_STL::pair<Rva00057FC1Record const, Rva00057FC1Record>, Rva00057FC1Record, _STL::hash<Rva00057FC1Record>, _STL::_Select1st<_STL::pair<Rva00057FC1Record const, Rva00057FC1Record> >, _STL::equal_to<Rva00057FC1Record>, _STL::allocator<_STL::pair<Rva00057FC1Record const, Rva00057FC1Record> > > Rva00057FC1Table;
namespace _STL { template<> void Rva00057FC1Table::clear(); }

// Retail 0x00061C87, vftable 0x007C55B0 slot 14: resets the view types in
// viewMask under the manager mutex -- their queued events (0x60123) and
// requests (0x56FD9), and for the main view the trigger areas -- then each
// selected view's volume data, name set, music system and affect masks, the
// per-view bits and the file-text caches. A main-view reset reopens the
// device (0x6179C) once the configured interval since the last open has
// passed, if the cached reinitialize setting allows it.
void MilesAudioManager::rva00061C87(unsigned int viewMask)
{
    MilesMutexGuard guard(&m_mutex, 0);
    rva00060123(viewMask);
    removeAllAudioRequests(viewMask);
    if (viewMask & 1) {
        rva000530DF();
        m_triggerAreas.clear();
        m_retestAreasEveryCall = true;
        m_at94 = 0;
    }
    m_viewTypesResetSinceUpdate |= viewMask;
    for (int i = 0; i < 3; ++i) {
        if (viewMask & (1 << i)) {
            reinterpret_cast<GlobalVolumeData *>(&m_volumeData[i])->reset();
            m_atA14[i].clear();
            m_activeMusicSystem[i] = MUSIC_SYSTEM_0;
            m_at6B4[i] = 0;
            m_at6C0[i] = 0;
        }
    }
    m_at690 &= ~viewMask;
    m_at698 &= ~viewMask;
    reinterpret_cast<Rva00057FC1Table *>(&m_fileText)->clear();
    m_pendingFileText.clear();
    m_unknownFileNames.clear();
    m_unknownFileNames.reserve(m_audioSettings->m_sampleCount3D + m_audioSettings->m_at64);
    if ((viewMask & 1) && m_audioSettings->m_forceResetTimeSeconds > 0) {
        if (_time64(0) - m_lastDeviceOpenTime > m_audioSettings->m_forceResetTimeSeconds) {
            static bool allowReinitialize = rva006AD9B0();
            if (allowReinitialize)
                rva0006179C(1);
        }
    }
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

// Native 0x544CB..0x544EB and WorldBuilder 0x7919C0 forward the
// same three lookup parameters through a one-pointer iterator return.
PlayingAudioList::iterator MilesAudioManager::rva000544CB(int viewType, int musicSystem, int filter)
{
    return PlayingAudioList::iterator(static_cast<_STL::_List_node<PlayingAudioRef> *>(rva0005442A(viewType, musicSystem, filter)._M_node));
}

class Rva002D9AC3 { public: const char *rva002D9AC3(); };

// Native 0x54714 first searches pending play requests for music in the
// focused view, then uses the current-system stream lookup. The 0x2D9AC3
// address-derived getter returns info +8 here: the copy-ctor call proves
// this caller treats that address as an AsciiString, not character storage.
AsciiString MilesAudioManager::rva00054714(void)
{
    MilesMutexGuard guard(&m_mutex, 0);
    for (Rva00051107AudioRequestList::iterator it = m_audioRequests.begin();
         it != m_audioRequests.end(); ++it) {
        if ((*it)->m_request == 0 && (*it)->m_pendingEvent.get()) {
            AudioEventRTS *event = (*it)->m_pendingEvent.get();
            if (event->m_viewType == m_at678) {
                if (event->m_info->m_atB0 == 0)
                    return *reinterpret_cast<const AsciiString *>(
                        reinterpret_cast<Rva002D9AC3 *>((*it)->m_pendingEvent.get())->rva002D9AC3());
            }
        }
    }
    PlayingAudioList::iterator it = rva000544CB(m_at678, m_activeMusicSystem[m_at678], 1);
    if (it != m_playingStreams.end())
        return *reinterpret_cast<const AsciiString *>(
            reinterpret_cast<Rva002D9AC3 *>((*it)->m_event.get())->rva002D9AC3());
    return AsciiString::TheEmptyString;
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

// The request set's lookup by playing handle, rowed at 0x00055951 under
// its address-derived owner. It returns the request table's own iterator,
// so the out-of-line find (0x00054EBE) builds it in this call's return slot.
class Rva00055951 {
public:
    MilesAudioRequestTable::iterator rva00055951(unsigned int handle);
};

// Retail 0x00055FCA (628 bytes): Zero Hour's isCurrentlyPlaying(handle)
// with outputs. Handles below 5 are never live. Looks through the playing
// lists then per view type the queued events and both music stacks then
// the request list's pending events and the pending request set; reports
// the event (and for a playing sound a reference to it through the third
// argument, a PlayingAudioRef pointer the callers pass as zero).
bool MilesAudioManager::rva00055FCA(int handle, void **result, PlayingAudioRef *playingOut)
{
    AudioEventRTS **eventOut = reinterpret_cast<AudioEventRTS **>(result);
    if (eventOut)
        *eventOut = 0;
    if (playingOut)
        reinterpret_cast<Rva000A8C9B *>(playingOut)->clear();
    if ((unsigned int)handle < 5)
        return false;

    PlayingAudioRef playing;
    OpaqueRefList::iterator it;
    for (it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
         it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end(); ++it) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get() && playing->m_event->m_playingHandle == handle) {
            if (eventOut)
                *eventOut = playing->m_event.get();
            if (playingOut)
                *playingOut = playing;
            return true;
        }
    }
    for (it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
         it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end(); ++it) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get() && playing->m_event->m_playingHandle == handle) {
            if (eventOut)
                *eventOut = playing->m_event.get();
            if (playingOut)
                *playingOut = playing;
            return true;
        }
    }
    for (it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).begin();
         it != reinterpret_cast<OpaqueRefList &>(m_playingStreams).end(); ++it) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get() && playing->m_event->m_playingHandle == handle) {
            if (eventOut)
                *eventOut = playing->m_event.get();
            if (playingOut)
                *playingOut = playing;
            return true;
        }
    }

    for (int viewType = 0; viewType < 3; ++viewType) {
        QueuedAudioEvents::iterator event;
        for (event = m_queuedEvents[viewType].begin(); event != m_queuedEvents[viewType].end(); ++event) {
            if (event->m_playingHandle == handle) {
                if (eventOut)
                    *eventOut = reinterpret_cast<AudioEventRTS *>(&*event);
                return true;
            }
        }
        for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
            MusicStack::iterator end = m_musicStack[viewType][musicSystem].end();
            for (MusicStack::iterator music = m_musicStack[viewType][musicSystem].begin();
                 music != end; ++music) {
                playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
                if (playing.get() && playing->m_event->m_playingHandle == handle) {
                    if (eventOut)
                        *eventOut = playing->m_event.get();
                    if (playingOut)
                        *playingOut = playing;
                    return true;
                }
            }
        }
    }

    Rva00051107AudioRequestList::iterator request;
    for (request = m_audioRequests.begin(); request != m_audioRequests.end(); ++request) {
        Rva00051107AudioRequest *req = *request;
        if (req && req->m_pendingEvent.get()
            && req->m_pendingEvent->m_playingHandle == handle) {
            if (eventOut)
                *eventOut = req->m_pendingEvent.get();
            return true;
        }
    }

    {
        MilesAudioRequestTable::iterator found =
            reinterpret_cast<Rva00055951 &>(m_requestSet).rva00055951((unsigned int)handle);
        if (found._M_cur) {
            Rva00051107AudioRequest *req = *reinterpret_cast<Rva00051107AudioRequestSet::iterator &>(found);
            if (eventOut)
                *eventOut = req->m_pendingEvent.get();
            return true;
        }
    }
    return false;
}

// Retail 0x00055E6C (350 bytes): banked at 352B (see reverse/attempts/
// 0x00055e6c.cpp); retry with the class decl and Rva000A8B59 forwarder above.

// AudioEventInfo's slot-1 event-name getter (0x000609A1's compares go
// through it); the view keeps the vtable use out of AudioEventInfo itself.
class BfmeAudioEventInfoNameView {
public:
    virtual void slot0();
    virtual const AsciiString &getEventName(void) const;
};

// The queued-event vector's single erase, rowed under an address name.
class Rva000554A9 { public: void *rva000554A9(void *position); };

// Retail 0x000609A1 (876 bytes, vftable slot 26): banked at 889B (see
// reverse/attempts/0x000609a1.cpp); retry with the slot26 rename, the two
// views above and BfmeStringTailRecord144::m_info.

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

// Address-derived callee views for the event-info table at +0xBC: the find
// (rowed 0x0041534B on 0x56F61's table), the by-value erase (0x003A37DC) and
// the first/next walk (0x00427195/0x00411084), all banked under these names.
class Rva00056F61;
struct Rva0041534BIter {
    void *m_node;
    Rva00056F61 *m_table;
};
class Rva00056F61 {
public:
    __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *key);
};
struct VideoPair {
    struct { void *first; void *second; } s;
    inline VideoPair(void *a, void *b) { s.first = a; s.second = b; }
    inline VideoPair(const VideoPair &other) { s.first = other.s.first; s.second = other.s.second; }
};
class Rva000411084 {
public:
    void *next();
    void *m_current;
    void *m_table;
};
class Rva000427195 {
public:
    void *first(Rva000411084 *iter);
    void rva003A37DC(VideoPair pair);
};
// Slot 1 of an event info's vftable hands back its name.
class AudioEventInfoVirtuals {
public:
    virtual void slot0();
    virtual const AsciiString &slot1();
};

// Retail 0x0005AF92 (address-derived): under the mutex, erases the table entry
// for the info's name when it still maps to this very info, then marks the
// name tree stale.
void MilesAudioManager::friend_onAudioEventInfoDestruction(AudioEventInfo *info)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva0041534BIter found = reinterpret_cast<Rva00056F61 *>(&m_allAudioEventInfo)->rva0041534B(&info->m_audioName);
    if (found.m_node && *reinterpret_cast<AudioEventInfo **>(reinterpret_cast<char *>(found.m_node) + 8) == info)
        reinterpret_cast<Rva000427195 *>(&m_allAudioEventInfo)->rva003A37DC(*reinterpret_cast<VideoPair *>(&found));
    m_at6A4 = false;
}

// Retail 0x0005B137 (pinned): rebuilds the +0xB0 name tree from the event info
// table, keeping the names of infos of type 0 whose type bits 9 and 10 are clear.
void MilesAudioManager::rva0005B137(void)
{
    _STL::set<AsciiString> *names = reinterpret_cast<_STL::set<AsciiString> *>(reinterpret_cast<char *>(this) + 0xB0);
    names->clear();
    Rva000411084 iter;
    reinterpret_cast<Rva000427195 *>(&m_allAudioEventInfo)->first(&iter);
    while (iter.m_current) {
        AudioEventInfo *info = *reinterpret_cast<AudioEventInfo **>(reinterpret_cast<char *>(iter.m_current) + 8);
        if (info->m_atB0 == 0 && !(info->m_type & 0x600))
            names->insert(reinterpret_cast<AudioEventInfoVirtuals *>(info)->slot1());
        iter.next();
    }
    m_at6A4 = true;
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
        next = _STL::_Rb_global<bool>::_M_increment(static_cast<_STL::_Rb_tree_node_base *>(next));

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
// Callee views for 0x0005B256. The event's own xfer (0x002D9F9F) and the
// stream holder's (+0x0C) load and save halves (0x000A8C2B 0x000A8B79) are
// rowed under address-derived owners; the load half ignores its receiver.
// The playing-handle store (0x005F69C4: event +0x0C = argument) is the
// ICF-folded setter pinned as GameMessage::friend_setList.
class Rva002D9F9FArg;
class Rva002D9F9FOwner { public: void rva002D9F9F(Rva002D9F9FArg *xfer); };
class Rva000A8C2BObj;
class Rva000A8B6D { public: void rva000A8B79(Rva000A8C2BObj *xfer); void rva000A8B6D(void); };
class Rva000A8C2B { public: void rva000A8C2B(Rva000A8C2BObj *xfer, int *resumePosition); };
class GameMessageList;
class GameMessage { public: void friend_setList(GameMessageList *list); };
// Saved stream position the load half fills and playAndStoreStream resumes from.
struct Rva0010FFA2Packet {
    int m_event0;
    int m_value4;
    float m_value8;
};
// Saved-handle -> live-handle map at +0xB6C, viewed as the folded
// map<unsigned int, Image *> instantiation whose insert_unique is rowed at
// 0x004D795B.

// Retail 0x0005B256 (676 bytes; WorldBuilder twin 0x007AA3A0 unnamed;
// callers are the manager's xfer 0x0005E3E5 per saved stream): xfers one
// playing stream. On load it allocates the playing audio and a fresh event
// then xfers the event and the +0x49 flag; on load it also registers the
// event (0x000592B8) and reads the saved handle and the stream position. A
// stream whose event has no info is dropped. Otherwise the saved handle is
// mapped to a fresh one (+0xD0 counter); when it was already mapped the
// queued and pending requests for the mapped handle are deleted. The event
// takes the handle and is replayed (generatePlayInfo 0x002D9ADC) and the
// stream file is reopened at the saved position and stored. On save it
// writes the event's playing handle and the stream position.
void MilesAudioManager::rva0005B256(Xfer *xfer, PlayingAudioRef &playing, int *unused)
{
    if (xfer->IsLoading()) {
        playing = allocatePlayingAudio();
        playing->m_event.rva00053D26(
            reinterpret_cast<BfmePoolHolder88 *>(new Rva0051D93(OpaqueRefElement4(), 0)));
    }
    reinterpret_cast<Rva002D9F9FOwner *>(playing->m_event.get())->rva002D9F9F(
        reinterpret_cast<Rva002D9F9FArg *>(xfer));
    *xfer == playing->m_at49;
    if (xfer->IsLoading()) {
        rva000592B8(playing->m_event.get());
        unsigned int savedHandle;
        *xfer == savedHandle;
        Rva0010FFA2Packet resumePosition;
        reinterpret_cast<Rva000A8C2B *>(&playing->m_at0C)->rva000A8C2B(reinterpret_cast<Rva000A8C2BObj *>(xfer), reinterpret_cast<int *>(&resumePosition));
        if (!playing->m_event->m_info) {
            reinterpret_cast<Rva000A8C9B *>(&playing)->clear();
            return;
        }
        playing->m_at4C = 1;
        unsigned int handle = m_nextHandle++;
        _STL::pair<Rva0005B256HandleMap::iterator, bool> result =
            reinterpret_cast<Rva0005B256HandleMap *>(&atB6C)->insert(
                Rva0005B256HandleMap::value_type(savedHandle, reinterpret_cast<Image *>(handle)));
        if (!result.second) {
            handle = reinterpret_cast<unsigned int>(result.first->second);
            Rva00051107AudioRequestList::iterator it = m_audioRequests.begin();
            while (it != m_audioRequests.end()) {
                Rva00051107AudioRequest *req = *it;
                if (req->m_pendingEvent.get() && req->m_pendingEvent->m_playingHandle == handle) {
                    it = m_audioRequests.erase(it);
                    deleteAudioRequest(req);
                } else {
                    ++it;
                }
            }
            MilesAudioRequestTable::iterator found =
                reinterpret_cast<Rva00055951 &>(m_requestSet).rva00055951(handle);
            if (found._M_cur) {
                Rva00051107AudioRequest *req = *reinterpret_cast<Rva00051107AudioRequestSet::iterator &>(found);
                reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(
                    reinterpret_cast<Rva00051B89KeyedSet::iterator &>(found));
                deleteAudioRequest(req);
            }
        }
        reinterpret_cast<GameMessage *>(playing->m_event.get())->friend_setList(
            reinterpret_cast<GameMessageList *>(handle));
        playing->m_event->generatePlayInfo();
        playing->m_event->rva002D9ADC();
        AsciiString file = playing->m_event->getFilename();
        void *owner = m_atB90;
        ((Rva000A8C9B *)&playing->m_at0C)->rva000A8D0B(reinterpret_cast<int>(owner), reinterpret_cast<int>(&file), 0);
        PlayingAudio *playingAudio = playing.get();
        ((Rva000A8AD8 *)&playingAudio->m_at0C)->rva000A8AD8(((Rva002D94DD *)playingAudio->m_event.get())->rva002D94DD());
        playing->m_type = 4;
        playAndStoreStream(playing, &resumePosition);
    } else {
        unsigned int handle = playing->m_event->m_playingHandle;
        *xfer == handle;
        reinterpret_cast<Rva000A8B6D *>(&playing->m_at0C)->rva000A8B79(
            reinterpret_cast<Rva000A8C2BObj *>(xfer));
    }
}

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
    if (looping->m_at30 >= m_audioSettings->m_timeToFadeAudio)
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
        ((Rva002D9BDC *)playing->m_event.operator->())->rva002D9BDC(g_00DBA4FC + 1.0f, _STL::_LimG<bool>::_F_inf.val);
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

// Retail 0x00057232 (WorldBuilder twin 0x00792970 names it and asserts
// request.m_request == AR_PopMusic and a bound pending event, lines 7641..7642).
void MilesAudioManager::processPopMusicRequest(Rva00051107AudioRequest *req)
{
    Rva00051107AudioRequest &request = *req;
    AudioEventRTS *event = request.m_pendingEvent.operator->();
    int viewType = event->m_viewType;
    int musicSystem = event->m_musicSystem;
    if (m_activeMusicSystem[viewType] == musicSystem) {
        removeCurrentlyPlayingMusic(viewType, !request.m_at10);
        int resume = !((Rva000CB12FByteField *)request.m_pendingEvent.operator->())->get();
        rva00057151(viewType, musicSystem, resume);
    } else if (!m_musicStack[viewType][musicSystem].empty()) {
        m_musicStack[viewType][musicSystem].pop_back();
    }
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
    unmapPhysicalHandle(*reinterpret_cast<const unsigned int *>(
        reinterpret_cast<const char *>(input) + 0x0C));
}

// Native 000577E3..000578B3, RET12. Every pending request (the +0x9C set,
// then the +0x98 queue, whose events must also carry an info) whose event's
// view type is in viewMask and whose sound class meets affect gets value in
// its +0x13 flag when affect has bit 0x20, else in its +0x12 flag.
void MilesAudioManager::rva000577E3(unsigned int affect, unsigned int viewMask, bool value)
{
    Rva00051107AudioRequestSet::iterator it;
    for (it = m_requestSet.begin(); it != m_requestSet.end(); ++it) {
        Rva00051107AudioRequest *req = *it;
        if (req && req->m_pendingEvent.get()
            && (viewMask & (1 << req->m_pendingEvent->m_viewType))
            && (req->m_pendingEvent->getSoundClass() & affect)) {
            if (affect & 0x20)
                req->m_at13 = value;
            else
                req->m_at12 = value;
        }
    }
    for (Rva00051107AudioRequestList::iterator node = m_audioRequests.begin();
         node != m_audioRequests.end(); ++node) {
        Rva00051107AudioRequest *req = *node;
        if (req && req->m_pendingEvent.get()
            && (viewMask & (1 << req->m_pendingEvent->m_viewType))
            && req->m_pendingEvent->m_info
            && (req->m_pendingEvent->getSoundClass() & affect)) {
            if (affect & 0x20)
                req->m_at13 = value;
            else
                req->m_at12 = value;
        }
    }
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
    Rva00051ADA existing = findAudioEventInfo(eventInfo->m_audioName);
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
    if (m_audioSettings->m_disableOcclusion || rva000516EF(pos)) {
        AIL_set_3D_sample_occlusion(sample3D, 0.0f);
        return;
    }
    float occlusion = 1.0f;
    if (playing->m_event->m_info->m_at90 > 0.0f)
        occlusion *= playing->m_event->m_info->m_at90;
    if (m_at8C > 0.0f && playing->m_event->m_info->m_distanceOcclusionWeight > 0.0f) {
        float distSqr = rva00053854(pos);
        float scale;
        if (distSqr > m_audioSettings->m_microphoneSettings[m_at678].m_at34)
            scale = 1.0f;
        else
            scale = sqrt(distSqr) / m_audioSettings->m_microphoneSettings[m_at678].m_at30;
        occlusion *= 1.0 - scale * m_at8C * playing->m_event->m_info->m_distanceOcclusionWeight;
    }
    float finalOcclusion = 1.0f - occlusion;
    if (finalOcclusion > 1.0f)
        finalOcclusion = 1.0f;
    else if (finalOcclusion < m_audioSettings->m_occlusionFloor)
        finalOcclusion = 0.0f;
    AIL_set_3D_sample_occlusion(sample3D, finalOcclusion);
}

// WorldBuilder 0x7A3290: squared 2D distance from pos to the outline of
// corners 1..4, via the nearest valid corner and its two adjacent edges;
// +inf when no corner is valid.
float MilesAudioManager::rva00053854(const Coord3D *pos)
{
    int nearest = 5;
    float best = _STL::_LimG<bool>::_F_inf.val;
    for (int i = 1; i < 5; ++i) {
        if (m_corners[i].m_valid) {
            Coord2D delta(pos->x, pos->y);
            float dist = lengthSqrdXY(subtractXY(delta, m_corners[i].m_pos));
            if (dist < best) {
                nearest = i;
                best = dist;
            }
        }
    }
    if (nearest == 5)
        return _STL::_LimG<bool>::_F_inf.val;

    int next = nearest + 1;
    if (next == 5)
        next = 1;
    {
        const Coord3D &start = m_corners[nearest].m_pos;
        const Coord3D &end = m_corners[next].m_pos;
        LineSegment2D edge(Coord2D(start.x, start.y), Coord2D(end.x, end.y));
        Coord2D closest = ClosestPointOnLineSegment(edge, Coord2D(pos->x, pos->y));
        float dist = lengthSqrdXY(subtractXY(closest, *pos));
        if (dist < best)
            best = dist;
    }

    int prev = nearest - 1;
    if (prev < 1)
        prev = 4;
    {
        const Coord3D &start = m_corners[nearest].m_pos;
        const Coord3D &end = m_corners[prev].m_pos;
        LineSegment2D edge(Coord2D(start.x, start.y), Coord2D(end.x, end.y));
        Coord2D closest = ClosestPointOnLineSegment(edge, Coord2D(pos->x, pos->y));
        float dist = lengthSqrdXY(subtractXY(closest, *pos));
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
    MilesSampleHandleMap::iterator it = m_sampleMap.find(sample);
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
    MilesSampleHandleMap::iterator it = m_3DSampleMap.find(sample3D);
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
    MilesSampleHandleMap::iterator it = m_streamMap.find(stream);
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
        || reinterpret_cast<Rva002DA153 *>(event.operator->())->rva002DA153() > m_audioSettings->m_minSampleVolume)
        minDistance = (float)m_audioSettings->m_globalMaxRange;
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
        if (!playing->m_hasLastTestedPosition) {
            *result = playing->m_at34 != 1.0f;
            playing->m_at34 = 1.0f;
            return;
        }
        if (!m_retestAreasEveryCall) {
            *result = false;
            return;
        }
        static_cast<Coord3D &>(pos) = playing->m_at24;
    } else if (!m_retestAreasEveryCall) {
        float dx = pos.x - playing->m_at24.x;
        float dy = pos.y - playing->m_at24.y;
        float limit = m_audioSettings->m_atB0;
        if (dx <= limit && -limit <= dx && dy <= limit && -limit <= dy) {
            *result = false;
            return;
        }
    }
    playing->m_at24 = pos;
    playing->m_hasLastTestedPosition = true;
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
        event->m_startedPlaying = true;
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
            event->m_startedPlaying = true;
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
        if ((float)m_audioSettings->m_preloadLimit > length
            && req->m_pendingEvent->m_info->m_atB0 == 2) {
            if (canPlay == 2)
                canPlay = reinterpret_cast<Rva0005E13CHost *>(this)->rva0005E13C(
                    reinterpret_cast<const Rva0005E13CArg *>(req)) ? 1 : 0;
            if (canPlay == 1)
                reinterpret_cast<Rva00691040Handle &>(req->m_file) = m_audioFileCache->requestFile(
                    // Shorter than one client frame (WorldBuilder tests it out of line).
                    req->m_pendingEvent, rva00051EC2(req->m_pendingEvent));
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

// Counted playing-audio copy whose constructor stays out of line at
// 0x000A8C7C (rowed as Rva0036CA00Str); 0x606CE releases it unguarded.
class Rva0036CA00Str {
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
    __forceinline Rva0036CA00Str(const AudioEventInfo *info) { reinterpret_cast<AudioEventInfoRef *>(&m_ptr)->AudioEventInfoRef::AudioEventInfoRef(info); }
    ~Rva0036CA00Str() { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(m_ptr)->Release_Ref(); }
    PlayingAudio *operator->(void) const { return m_ptr; }
    PlayingAudio *get(void) const { return m_ptr; }
private:
    PlayingAudio *m_ptr;
};

// MilesAudioManager::shouldPlayLocally, retail 0x00053BA1 (320 B; WB 0x007A88A0,
// MilesAudioManager.cpp:14080..14109). Zero Hour's AudioManager test with
// BFME's two owner kinds: music (+0xB0 sound type 0) and type 3, sounds with
// no player restriction (+0x48 bits 0x20/0x40/0x80/0x100) and "everyone"
// sounds always play. A game-owned event (+0x30 kind 0) compares its owning
// player with the local one (the player bit when they are the same, else
// the allies or enemies bit by relationship to the local default team); a
// living-world event (kind 1) compares its owner with the living-world local
// player and its alliance test. The info reference (+0x08) is held counted.
class BfmeMemberRV;
class BfmeThingRV { public: BfmeMemberRV *bfmePickRV(void); };
class Team;
enum Relationship { REL_ENEMIES, REL_NEUTRAL, REL_ALLIES };
class Player
{
public:
    Relationship getRelationship(const Team *that) const;
    char at000[0x2EC];
    Team *m_defaultTeam;    // +0x2EC
};
class PlayerList { public: Player *getNthPlayer(int index); };
extern PlayerList *ThePlayerList;
class Rva002DA414 { public: void *rva002DA414(void); };
class Rva002D9C7A { public: int rva002D9C7A(void); };
class Rva002B2B66 { public: int rva002B2B66(void); };
class Rva002E071E { public: int rva002E0BC0(int playerID); };
struct LivingWorldLogicAudioView
{
    char at00[0x98];
    Rva002E071E *m_localPlayer;     // +0x98
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

bool MilesAudioManager::shouldPlayLocally(const AudioEventRTS *event)
{
    Rva0036CA00Str infoRef(*reinterpret_cast<const Rva0036CA00Str *>(&event->m_info));
    const AudioEventInfo *ei = reinterpret_cast<const AudioEventInfo *>(infoRef.get());

    if (ei->m_atB0 == 0 || ei->m_atB0 == 3 || (ei->m_type & 0x1E0) == 0 || (ei->m_type & 0x100))
        return true;

    if (event->m_viewType == 0)
    {
        if (!ThePlayerList)
            return true;
        Player *localPlayer = (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();
        Player *owningPlayer = ThePlayerList->getNthPlayer((int)((Rva002DA414 *)event)->rva002DA414());
        if ((ei->m_type & 0x20) && (ei->m_type & 1) && owningPlayer == 0)
            return true;
        if (owningPlayer == 0)
            return false;
        if (localPlayer == 0)
            return false;
        const Team *localTeam = localPlayer->m_defaultTeam;
        if (localTeam == 0)
            return false;
        if (owningPlayer == localPlayer)
            return (ei->m_type >> 5) & 1;
        if (owningPlayer->getRelationship(localTeam) == REL_ALLIES)
            return (ei->m_type >> 6) & 1;
        return (ei->m_type >> 7) & 1;
    }
    else if (event->m_viewType == 1)
    {
        int owner = ((Rva002D9C7A *)event)->rva002D9C7A();
        if (((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66() == owner)
            return (ei->m_type >> 5) & 1;
        Rva002E071E *local = ((LivingWorldLogicAudioView *)TheLivingWorldLogic)->m_localPlayer;
        if (!local || !(unsigned char)local->rva002E0BC0(owner))
            return (ei->m_type >> 7) & 1;
        return (ei->m_type >> 6) & 1;
    }
    else
        return true;
}

// Native 00060123..00060309 (WorldBuilder twin 0x007967E0, unnamed). For
// every view type in viewMask: playing sounds, 3D sounds and streams give
// their Miles handles back and leave their lists, queued events unmap their
// playing handles and are cleared, and both music stacks are emptied.
void MilesAudioManager::rva00060123(unsigned int viewMask)
{
    PlayingAudioRef playing;
    OpaqueRefList::iterator it;

    it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get()) {
            int viewType = playing->m_event->m_viewType;
            if (viewMask & (1 << viewType)) {
                releaseMilesHandles(*playing.get());
                it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
                continue;
            }
        }
        ++it;
    }
    it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get()) {
            int viewType = playing->m_event->m_viewType;
            if (viewMask & (1 << viewType)) {
                releaseMilesHandles(*playing.get());
                it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
                continue;
            }
        }
        ++it;
    }
    it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingStreams).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get()) {
            int viewType = playing->m_event->m_viewType;
            if (viewMask & (1 << viewType)) {
                releaseMilesHandles(*playing.get());
                it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(it);
                continue;
            }
        }
        ++it;
    }

    for (int viewType = 0; viewType < 3; ++viewType) {
        if (viewMask & (1 << viewType)) {
            QueuedAudioEvents::iterator event;
            for (event = m_queuedEvents[viewType].begin(); event != m_queuedEvents[viewType].end(); ++event)
                unmapPhysicalHandle(event->m_playingHandle);
            m_queuedEvents[viewType].clear();
            for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
                while (!m_musicStack[viewType][musicSystem].empty()) {
                    releaseMilesHandles(*reinterpret_cast<PlayingAudio *>(m_musicStack[viewType][musicSystem].back().referent));
                    m_musicStack[viewType][musicSystem].pop_back();
                }
            }
        }
    }
}

// Native 0005824D..00058314, vftable slot 93. Under the mutex a trigger's
// level is clamped to [0, 1] and stored in its +0xB54 area entry (appended
// when absent); a full level instead drops the entry through slot 94. Any
// change marks the areas for retesting (+0x6AA).
void MilesAudioManager::rva0005824D(PolygonTrigger *trigger, float level)
{
    MilesMutexGuard guard(&m_mutex, 0);
    if (!trigger)
        return;
    if (level == 1.0f) {
        rva000551C2(reinterpret_cast<int>(trigger));
        return;
    }
    if (level > 1.0f)
        level = 1.0f;
    if (0.0f > level)
        level = 0.0f;
    for (_STL::vector<AudioTriggerArea>::iterator it = m_triggerAreas.begin(); it != m_triggerAreas.end(); ++it) {
        if (it->m_trigger == trigger) {
            if (it->m_level != level) {
                it->m_level = level;
                m_retestAreasEveryCall = true;
            }
            return;
        }
    }
    AudioTriggerArea area;
    area.m_trigger = trigger;
    area.m_level = level;
    m_triggerAreas.push_back(area);
    m_retestAreasEveryCall = true;
}

// Native 000583BA..00058591. Under the mutex, pauses every sound (affect bit
// 0x02), 3D sound (0x04) and stream whose class meets affect in the view
// types of viewMask: bit 0x20 marks the playing audio at +0x4A, otherwise
// +0x49, then pauseResumeSound applies it. Music (0x10) records the views
// at +0x694/+0x690, pending requests are flagged through 0x577E3, and
// unless arg is set the per-view masks at +0x6C0/+0x6B4 remember affect.
void MilesAudioManager::rva000583BA(unsigned int affect, unsigned int viewMask, int arg)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    PlayingAudioList::iterator it;
    if (affect & 0x02) {
        for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
            playing = *it;
            if (playing.get() && (viewMask & (1 << playing->m_event->getViewType()))) {
                if (affect & 0x20)
                    playing->m_at4A = true;
                else
                    playing->m_at49 = true;
                pauseResumeSound(playing);
            }
        }
    }
    if (affect & 0x04) {
        for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it) {
            playing = *it;
            if (playing.get() && (viewMask & (1 << playing->m_event->getViewType()))) {
                if (affect & 0x20)
                    playing->m_at4A = true;
                else
                    playing->m_at49 = true;
                pauseResumeSound(playing);
            }
        }
    }
    for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        playing = *it;
        if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))
            && (playing->m_event->getSoundClass() & affect)) {
            if (affect & 0x20)
                playing->m_at4A = true;
            else
                playing->m_at49 = true;
            pauseResumeSound(playing);
        }
    }
    if (affect & 0x10) {
        if (affect & 0x20)
            m_musicPausedViewTypes |= viewMask;
        else
            m_at690 |= viewMask;
    }
    rva000577E3(affect, viewMask, true);
    if (!arg) {
        for (int viewType = 0; viewType < 3; ++viewType) {
            if (viewMask & (1 << viewType)) {
                if (affect & 0x20)
                    m_at6C0[viewType] |= affect & ~0x20;
                else
                    m_at6B4[viewType] |= affect;
            }
        }
    }
}



// Native 00058591..0005876E, the resume half of 0x000583BA (the next slot
// of the manager's table): clears the pause flags it set, lets each sound
// resume, drops the music view masks and the per-view affect masks, and
// clears the pending-request flags through 0x577E3.
void MilesAudioManager::rva00058591(unsigned int affect, unsigned int viewMask, int keepMasks)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    PlayingAudioList::iterator it;
    if (affect & 0x02) {
        for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
            playing = *it;
            if (playing.get() && (viewMask & (1 << playing->m_event->getViewType()))) {
                if (affect & 0x20)
                    playing->m_at4A = false;
                else
                    playing->m_at49 = false;
                pauseResumeSound(playing);
            }
        }
    }
    if (affect & 0x04) {
        for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it) {
            playing = *it;
            if (playing.get() && (viewMask & (1 << playing->m_event->getViewType()))) {
                if (affect & 0x20)
                    playing->m_at4A = false;
                else
                    playing->m_at49 = false;
                pauseResumeSound(playing);
            }
        }
    }
    for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        playing = *it;
        if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))
            && (playing->m_event->getSoundClass() & affect)) {
            if (affect & 0x20)
                playing->m_at4A = false;
            else
                playing->m_at49 = false;
            pauseResumeSound(playing);
        }
    }
    if (affect & 0x10) {
        if (affect & 0x20)
            m_musicPausedViewTypes &= ~viewMask;
        else
            m_at690 &= ~viewMask;
    }
    rva000577E3(affect, viewMask, false);
    if (!keepMasks) {
        for (int viewType = 0; viewType < 3; ++viewType) {
            if (viewMask & (1 << viewType)) {
                if (affect & 0x20)
                    m_at6C0[viewType] &= ~(affect & ~0x20);
                else
                    m_at6B4[viewType] &= ~affect;
            }
        }
    }
}

// Retail 0x000606CE, called from onAudioLODChanged (0x607BB) and 0x61A2E.
// With a provider selected it releases every playing 3D sound under the
// mutex and unselects it, then reselects through 0x604A3 and, if that found
// one, reapplies the reverb room type and calls vtable slot 10.
void MilesAudioManager::rva000606CE(bool accelerated)
{
    if (m_selectedProvider != (unsigned int)-1) {
        MilesMutexGuard guard(&m_mutex, 0);
        OpaqueRefList &sounds = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds);
        OpaqueRefList::iterator it = sounds.begin();
        while (it != sounds.end()) {
            Rva0036CA00Str playing(*reinterpret_cast<const Rva0036CA00Str *>(&*it));
            if (playing->m_event->hasMoreLoops())
                rva0005AA72(*reinterpret_cast<PlayingAudioRef *>(&playing));
            releaseMilesHandles(*playing.get());
            it = sounds.erase(it);
        }
        rva0005452B();
        unselectProvider();
    }
    selectProvider(accelerated);
    if (m_selectedProvider != (unsigned int)-1) {
        internalSetReverbRoomType(m_reverbRoomType);
        update();
    }
}

// Retail 0x000607BB (WorldBuilder twin 0x0079DCD0 names it). Under the
// mutex, a selected EAX 3 provider, or one whose Dolby-ness already agrees
// with 0x51525 (WB shouldUseDolbyProvider), only gets the reverb room type
// reapplied; otherwise the provider is reselected through 0x606CE. The
// ambient stream cap is refreshed either way.
// Retail 0x00051525. Defined in this unit ahead of onAudioLODChanged: retail
// keeps a byte in dl across the call, which MSVC does only for a callee whose
// register use it has already seen. The null-manager guard keeps an explicit
// else so the shared true block stays between the guard and the body.
// WorldBuilder 0x0079CB00 names shouldUseDolbyProvider; its speaker-type
// range and measured retail LOD offsets independently prove this owner.
bool MilesAudioManager::shouldUseDolbyProvider(void)
{
    int value = m_selectedSpeakerType;
    if (value <= 0 || value > 5)
        return false;
    GameLODManager *lod = TheGameLODManager;
    if (lod == 0)
        return true;
    else {
        int level = lod->m_audioLOD;
        if (level < 0 || level >= 2)
            return true;
        return lod->m_audioLODSettings[level].m_at04;
    }
}

void MilesAudioManager::onAudioLODChanged(void)
{
    MilesMutexGuard guard(&m_mutex, 0);
    bool needReselect = true;
    if (m_selectedProvider != (unsigned int)-1) {
        const AsciiString &eaxName = m_provider3D[m_selectedProvider].name;
        if (eaxName.compare("Creative Labs EAX 3 (TM)") == 0) {
            needReselect = false;
        } else {
            const AsciiString &dolbyName = m_provider3D[m_selectedProvider].name;
            bool isDolby = dolbyName.compare("Dolby Surround") == 0;
            if (shouldUseDolbyProvider() == isDolby)
                needReselect = false;
        }
    }
    if (needReselect)
        rva000606CE(false);
    else
        internalSetReverbRoomType(m_reverbRoomType);
    setMaxAmbientStreams();
}

extern "C" __declspec(dllimport) int __stdcall AIL_sample_status(void *sample);
extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_status(void *sample3D);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_3D_sample(void *sample3D);
extern "C" __declspec(dllimport) void __stdcall AIL_resume_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_quick_shutdown(void);
extern "C" __declspec(dllimport) void __stdcall AIL_shutdown(void);

// Rowed at 0x00053D89; clears the holder at +0xB90.
class Rva00053D89 { public: void clear(void); };

// Native 00060309..000603ED (WorldBuilder twin 0x00797100, unnamed). Under
// the mutex every loop buffer's sample is stopped, then each is invalidated
// and, when still bound, cleaned up; all view types are then stopped
// (0x60123 with mask 7), the 2D samples and 3D sample handles released, and
// +0x68C cleared.
void MilesAudioManager::rva00060309(void)
{
    MilesMutexGuard guard(&m_mutex, 0);
    int i;
    for (i = 0; i < m_numLoopBuffers; ++i) {
        if (m_loopBuffers[i].m_is3D) {
            if (m_loopBuffers[i].m_3DSample)
                AIL_stop_3D_sample(m_loopBuffers[i].m_3DSample);
        } else if (m_loopBuffers[i].m_sample) {
            AIL_stop_sample(m_loopBuffers[i].m_sample);
        }
    }
    for (i = 0; i < m_numLoopBuffers; ++i) {
        m_loopBuffers[i].m_isValid = false;
        if (m_loopBuffers[i].m_at10)
            cleanUpLoopBuffer(&m_loopBuffers[i]);
    }
    rva00060123(7);
    rva000544EB();
    rva0005452B();
    m_at68C = 0;
}

// Native 0006047C..000604A3 (WorldBuilder twin 0x00798C10, unnamed): stop
// everything, unselect the provider, clear +0xB90 and shut Miles down.
void MilesAudioManager::rva0006047C(void)
{
    rva00060309();
    unselectProvider();
    reinterpret_cast<Rva00053D89 *>(&m_atB90)->clear();
    AIL_quick_shutdown();
    AIL_shutdown();
}

// Retail 0x000603ED (address-derived): gives back the Miles handles of every
// playing stream whose event info type (+0xB0) is 1 and drops it from the list.
void MilesAudioManager::rva000603ED(void)
{
    PlayingAudioRef playing;
    OpaqueRefList::iterator it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingStreams).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get()) {
            if (playing->m_event->getAudioEventInfo()->m_atB0 == 1) {
                releaseMilesHandles(*playing.get());
                it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(it);
            } else {
                ++it;
            }
        }
    }
}

// Retail 0x0005623E (symbols.csv pin): the playing lookup 0x55FCA run into a
// local PlayingAudioRef; the event goes to the caller's slot and the playing
// reference replaces the caller's when one was supplied.
// The unit's own holder: retail tests and then reloads the pointer in memory.
class PlayingAudioHolder {
public:
    PlayingAudioHolder() : m_ptr(0) {}
    ~PlayingAudioHolder() { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(m_ptr)->Release_Ref(); }
    PlayingAudio *get(void) const { return m_ptr; }
private:
    PlayingAudio *volatile m_ptr;
};

bool MilesAudioManager::rva0005623E(int key, void **result, int flags)
{
    PlayingAudioHolder playing;
    bool found = rva00055FCA(key, reinterpret_cast<void **>(&key), reinterpret_cast<PlayingAudioRef *>(&playing));
    if (result)
        *result = reinterpret_cast<void *>(key);
    if (flags)
        reinterpret_cast<PlayingAudioRef *>(flags)->set(playing.get());
    return found;
}

// Retail 0x000563FE (address-derived, RET 8; WorldBuilder twin 0x0079AA60):
// xfers one logical handle's event. The event and its playing record come
// from the 0x55FCA lookup; it counts as present only when found, not
// flagged at +0x4C and not finished (+0x44). After the present flag, a
// present event is xferred with the record's pending extra volume applied
// when one is set (+0x40 > 0), then its own volume is put back.
void MilesAudioManager::rva000563FE(Xfer *xfer, int handle)
{
    PlayingAudioRef playing;
    AudioEventRTS *event;
    bool present = rva00055FCA(handle, reinterpret_cast<void **>(&event), &playing);
    if (present) {
        if (event == 0)
            present = false;
        else if (event->m_at4C)
            present = false;
        if (playing.get() != 0 && playing->m_at44)
            present = false;
    }
    *xfer == present;
    if (present) {
        float volume = event->m_at2C;
        if (playing.get() != 0 && playing->m_at40 > 0.0f)
            reinterpret_cast<Rva00481FAFFloatSlot *>(event)->store(playing->m_at3C);
        reinterpret_cast<Rva002D9FD9Owner *>(event)->rva002D9FD9(reinterpret_cast<Rva002D9FD9Arg *>(xfer));
        reinterpret_cast<Rva00481FAFFloatSlot *>(event)->store(volume);
    }
}

// Retail 0x0005634C (address-derived, RET 0xC; called by the alias forwarder
// 0x00057530): sets a handle's extra volume. Mode 1 stores it on the event
// (0x481FAF) and, for a playing record, flags it and restarts its clock;
// otherwise a playing record takes it with the settings' +0x78 clock, and a
// queued event just stores it.
void MilesAudioManager::rva0005634C(int handle, float volume, int mode)
{
    AudioEventRTS *event = 0;
    PlayingAudioRef playing;
    if (rva00055FCA(handle, reinterpret_cast<void **>(&event), &playing)) {
        if (mode == 1) {
            if (event) {
                reinterpret_cast<Rva00481FAFFloatSlot *>(event)->store(volume);
                if (playing.get()) {
                    playing->m_at4F = true;
                    playing->m_at3C = volume;
                    playing->m_at40 = 0.0f;
                }
            }
        } else if (playing.get()) {
            playing->m_at3C = volume;
            playing->m_at40 = static_cast<float>(m_audioSettings->m_timeToFadeAudio);
        } else if (event) {
            reinterpret_cast<Rva00481FAFFloatSlot *>(event)->store(volume);
        }
    }
}

// Retail 0x0005E377 (address-derived): under the mutex, erases the key from
// the view type's +0x1B8 member of its GlobalVolumeData record, then hands the
// key and view type to the unrowed 0x5BE59 (pinned, typed void* there) with
// the -1.0 value.
void MilesAudioManager::rva0005E377(const AsciiString &key, int viewType)
{
    MilesMutexGuard guard(&m_mutex, 0);
    reinterpret_cast<GlobalVolumeData *>(&m_volumeData[viewType])->m_at1B8.rva0005B633(key);
    rva0005BE59(const_cast<AsciiString *>(&key), -1.0f, reinterpret_cast<void *>(viewType));
}

// Retail 0x0005538C (address-derived): under the mutex, whether any view type
// has a music stream playing for its active system or music queued on an
// inactive system's stack.
bool MilesAudioManager::rva0005538C(void)
{
    MilesMutexGuard guard(&m_mutex, 0);
    int *active = reinterpret_cast<int *>(m_activeMusicSystem);
    for (int view = 0; view < 3; ++view, ++active) {
        for (int system = 0; system < 2; ++system) {
            if (system == *active) {
                PlayingAudioList::iterator it = rva000544CB(view, system, 1);
                if (it != m_playingStreams.end())
                    return true;
            } else if (!m_musicStack[view][system].empty()) {
                return true;
            }
        }
    }
    return false;
}

class Rva00052B3D;
class Rva0005C892 { public: void rva0005C892(void); };

// Retail 0x0005DAFC (address-derived): under the mutex, switches the active
// view type (+0x678) and refreshes the reverb, the microphone and the 0x5C892
// state; +0x6A5 marks the change.
void MilesAudioManager::setViewFocus(int viewType)
{
    MilesMutexGuard guard(&m_mutex, 0);
    if (viewType != m_at678) {
        m_at678 = viewType;
        m_viewTypeChanged = true;
        internalSetReverbRoomType(m_reverbRoomType);
        recalculateMicrophone();
        reinterpret_cast<Rva0005C892 *>(this)->rva0005C892();
    }
}

// Retail 0x0005A7BE..0x5A812 (Ghidra splits the prolog off at 0x5A7BE and starts the body at 0x5A7CA; address-derived): pushMusicEventInternal under the mutex
// with no second argument and append set.
int MilesAudioManager::rva0005A7BE(AudioEventRTS *event, int arg1)
{
    MilesMutexGuard guard(&m_mutex, 0);
    return pushMusicEventInternal(event, arg1, 0, 1);
}

class Rva00050DF0 { public: bool rva00050DF0(void); };

// Retail 0x00053606 (pinned): whether a request may be serviced now. The
// triple-flag predicate 0x50DF0 and an event whose +0x64 (shorter than one
// client frame) reaches the cutoff both refuse it, as does a preloaded file
// that is not ready yet.
bool MilesAudioManager::rva00053606(Rva00051107AudioRequest *req)
{
    if (reinterpret_cast<Rva00050DF0 *>(req)->rva00050DF0())
        return false;
    if (req->m_pendingEvent.get() && req->m_pendingEvent->m_at64 >= g_00DBA4FC)
        return false;
    if (req->m_file.isOpen() && !reinterpret_cast<Rva00050DBD *>(&req->m_file)->rva00050DBD())
        return false;
    return true;
}

// Retail 0x0005910F (address-derived): the volume of the float table at +0xC8
// for an event, indexed by its info's volume slider, whether it is positional
// (or a type 3 info), and two flags: the name is not tracked in +0xA0, and the
// info has no channel volumes.
float MilesAudioManager::GlobalVolumeData::rva0005910F(AudioEventRTS *event)
{
    int positional = event->isPositionalAudio() || event->getAudioEventInfo()->m_atB0 == 3 ? 1 : 0;
    int flags = 0;
    if (m_names.size() == 0 || m_names.find(reinterpret_cast<AudioEventInfoVirtuals *>(const_cast<AudioEventInfo *>(event->getAudioEventInfo()))->slot1()) == m_names.end())
        flags = 1;
    AudioEventInfo *info = const_cast<AudioEventInfo *>(event->getAudioEventInfo());
    if (info->m_channelVolumes.empty())
        flags |= 2;
    return reinterpret_cast<float *>(reinterpret_cast<char *>(this) + 0xC8)[flags + (positional + info->getVolumeSlider() * 2) * 4];
}

extern "C" __declspec(dllimport) void __stdcall AIL_resume_3D_sample(void *sample3D);

// Retail 0x00053113 (WorldBuilder twin 0x0078E1E0 names it and asserts a
// sound is not both 2D and 3D, line 6474). 0x50D6C says whether the sound
// should now be paused: streams pause or resume through their stream view,
// samples stop unless already done, or resume from stopped unless their
// loop buffer (types 1 and 3) is held at +0x01.
void MilesAudioManager::pauseResumeSound(PlayingAudioRef &playing)
{
    PlayingAudio *audio = playing.get();
    if (audio->m_type == 4) {
        if ((unsigned char)((Rva00050D6C *)audio)->rva00050D6C())
            ((MilesStreamRef *)&audio->m_at0C)->rva000A8AC0();
        else
            ((Rva000A8ACC *)&audio->m_at0C)->rva000A8ACC();
        return;
    }
    void *sample;
    void *sample3D;
    getAppropriateSampleHandleForPlayingAudio(playing, &sample, &sample3D);
    if (!sample && !sample3D)
        return;
    int status;
    if (!sample)
        status = AIL_3D_sample_status(sample3D);
    else
        status = AIL_sample_status(sample);
    audio = playing.get();
    if ((unsigned char)((Rva00050D6C *)audio)->rva00050D6C()) {
        if (status != 2) {
            if (!sample)
                AIL_stop_3D_sample(sample3D);
            else
                AIL_stop_sample(sample);
        }
    } else if (status == 8) {
        if (audio->m_type == 3 || audio->m_type == 1) {
            LoopBuffer *buffer = &m_loopBuffers[audio->m_handle];
            if (buffer->m_heldPaused)
                return;
        }
        if (!sample)
            AIL_resume_3D_sample(sample3D);
        else
            AIL_resume_sample(sample);
    }
}

class Rva000A8AEE { public: void rva000A8AEE(float volume); };


// WorldBuilder twin 0x7A0720 names it (assert at MilesAudioManager.cpp:11501):
// each view type's pending music track that is not already playing gets its
// channel volumes, position and volume, joins the playing streams and starts
// unless paused; the pending slot is then cleared.
void MilesAudioManager::startPendingMusicTracks(void)
{
    for (int view = 0; view < 3; ++view) {
        PlayingAudioRef &track = m_playingMusic[view];
        // Retail re-reads the slot on every access, never caching it in a register.
        PlayingAudio *volatile &pending = *reinterpret_cast<PlayingAudio *volatile *>(&track);
        if (!pending)
            continue;
        bool found = false;
        for (PlayingAudioList::iterator it = m_playingStreams.begin(); it != m_playingStreams.end() && !found; ++it) {
            PlayingAudio *current = pending;
            if ((*it).get() == current)
                found = true;
        }
        if (!found) {
            PlayingAudio *audio = pending;
            AudioEventRTS *event = audio->m_event.operator->();
            AudioEventInfo *const &info = event->m_info;
            if (!info->m_channelVolumes.empty())
                rva000581FA(*reinterpret_cast<const Rva0005BA08InfoRef *>(&info), event->m_viewType);
            rva00053AFA(&track);
            ((Rva000A8AEE *)&pending->m_at0C)->rva000A8AEE(rva0005A9F8(&track, 1, 1));
            m_playingStreams.push_back(track);
            audio = pending;
            if (!(unsigned char)((Rva00050D6C *)audio)->rva00050D6C())
                ((Rva000A8ACC *)&audio->m_at0C)->rva000A8ACC();
        }
        ((Rva000A8C9B *)&track)->clear();
    }
}

// Retail 0x0002E36D5Find: the polygon trigger with this ID, or null.
void *Rva002E36D5Find(int id);
class Rva00053DC5 { public: void rva00054B9A(void); };
class Rva00056DA2 { public: void rva00056DA2(void); };
// XferException's throw information (0x00CFFD18) is what the missing-trigger
// path throws; tag 5 is Zero Hour's invalid-data code.
class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &that);
    ~XferException(void);
    char *text;
    int tag;
};

// WorldBuilder twin 0x7AB6E0 (MilesAudioManager::LoadPostProcess, assert at
// line 15099: unable to find reverb suppression polygon trigger by ID).
void MilesAudioManager::loadPostProcess(void)
{
    MilesMutexGuard guard(&m_mutex, 0);
    m_at6AC = false;
    m_at6AB = true;
    m_triggerAreas.clear();
    m_triggerAreas.reserve(m_savedTriggerAreas.size());
    for (_STL::vector<AudioTriggerAreaSave>::iterator it = m_savedTriggerAreas.begin(); it != m_savedTriggerAreas.end(); ++it) {
        AudioTriggerArea area;
        area.m_level = it->m_level;
        area.m_trigger = (PolygonTrigger *)Rva002E36D5Find(it->m_triggerID);
        if (!area.m_trigger)
            throw XferException(5, 0);
        m_triggerAreas.push_back(area);
    }
    m_savedTriggerAreas.clear();
    ((Rva00053DC5 *)&atB6C)->rva00054B9A();
    ((Rva00056DA2 *)&atB78)->rva00056DA2();
}

// Transfer helpers MilesAudioManager::xfer calls, rowed in their own units.
class AudioReceiver;
void Rva00050C61Dispatch(AudioReceiver *receiver, void *value);
void Rva00050C79Dispatch(AudioReceiver *receiver, void *value);
void Rva00050C91Dispatch(AudioReceiver *receiver, void *value);
void XferAudioAffect(Xfer *xfer, void *value);
Xfer *Rva00058DC6Xfer(Xfer *xfer, _STL::set<AsciiString> *value);
Xfer *xferUnicodeStringVector(Xfer *xfer, _STL::vector<UnicodeString> *vec);
Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

// WorldBuilder twin 0x7AA970 (MilesAudioManager::DoXfer). Snapshot slot 3,
// reached through the +0x0C Snapshot subobject. Version 3 skips view type 2
// unless m_transferViewType2 is set; version 4 adds the per-view affect masks.
void MilesAudioManager::xfer(Xfer *transfer)
{
    if (transfer->IsCRC())
        return;
    MilesMutexGuard guard(&m_mutex, 0);
    if (transfer->IsLoading()) {
        m_at6AC = true;
        m_at6B0 = 0;
    }
    XferVersion version;
    version.m_version = 1;
    version.m_currentVersion = 4;
    *transfer == (Xfer::Version &)version;
    int oldViewType = m_at678;
    Rva00050C61Dispatch(reinterpret_cast<AudioReceiver *>(transfer), &m_at678);
    if (oldViewType != m_at678)
        m_viewTypeChanged = true;
    Rva00050C79Dispatch(reinterpret_cast<AudioReceiver *>(transfer), &m_at690);
    *transfer == m_at6A7;
    int viewType;
    for (viewType = 0; viewType < 3; ++viewType) {
        if (viewType == 2 && version.m_currentVersion >= 3 && !m_transferViewType2)
            continue;
        Rva00050C91Dispatch(reinterpret_cast<AudioReceiver *>(transfer), &m_activeMusicSystem[viewType]);
        reinterpret_cast<GlobalVolumeData *>(&m_volumeData[viewType])->rva0005CE7E(transfer);
        Rva00058DC6Xfer(transfer, &m_atA14[viewType]);
        if (version.m_currentVersion >= 4)
            XferAudioAffect(transfer, &m_at6B4[viewType]);
    }
    if (transfer->IsLoading()) {
        m_savedTriggerAreas.clear();
        int count;
        *transfer == count;
        while (count) {
            AudioTriggerAreaSave area;
            *transfer == area.m_triggerID;
            *transfer == area.m_level;
            m_savedTriggerAreas.push_back(area);
            --count;
        }
        m_retestAreasEveryCall = true;
    } else {
        int count = static_cast<int>(m_triggerAreas.size());
        *transfer == count;
        for (_STL::vector<AudioTriggerArea>::iterator it = m_triggerAreas.begin(); it != m_triggerAreas.end(); ++it) {
            int triggerID = it->m_trigger->getID();
            *transfer == triggerID;
            float level = it->m_level;
            *transfer == level;
        }
    }
    *transfer == m_reverbRoomType;
    if (transfer->IsLoading())
        internalSetReverbRoomType(m_reverbRoomType);
    if (version.m_currentVersion >= 2)
        *transfer == *(reinterpret_cast<unsigned int *>(&m_at94));
    else
        m_at94 = -1;
    m_at90 = 0.0f;
    if (transfer->IsLoading()) {
        m_cameraPos.x = _STL::numeric_limits<float>::quiet_NaN();
        m_cameraPos.y = _STL::numeric_limits<float>::quiet_NaN();
        m_cameraPos.z = _STL::numeric_limits<float>::quiet_NaN();
    }
    if (transfer->IsLoading()) {
        int count;
        *transfer == count;
        for (int index = 0; index < count; ++index) {
            PlayingAudioRef playing;
            rva0005B256(transfer, playing, reinterpret_cast<int *>(&version));
            startPendingMusicTracks();
        }
        for (viewType = 0; viewType < 3; ++viewType) {
            if (viewType == 2 && version.m_currentVersion >= 3 && !m_transferViewType2)
                continue;
            for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
                MusicStack &stack = m_musicStack[viewType][musicSystem];
                int oldSize = static_cast<int>(stack.size());
                int stackCount;
                *transfer == stackCount;
                for (int index = 0; index < stackCount; ++index) {
                    PlayingAudioRef playing;
                    rva0005B256(transfer, playing, reinterpret_cast<int *>(&version));
                    if (playing.get() && static_cast<int>(stack.size()) == oldSize)
                        reinterpret_cast<Rva00058B90 *>(&stack)->rva00058B90(*reinterpret_cast<Rva0036CA00Str *>(&playing));
                    oldSize = static_cast<int>(stack.size());
                }
            }
        }
        for (viewType = 0; viewType < 3; ++viewType) {
            if (viewType == 2 && version.m_currentVersion >= 3 && !m_transferViewType2)
                continue;
            reinterpret_cast<Rva000A8C9B *>(&m_playingMusic[viewType])->clear();
        }
        m_pendingFileText.clear();
        m_unknownFileNames.clear();
    } else {
        PlayingAudioList savedStreams;
        for (PlayingAudioList::iterator it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
            PlayingAudioRef &playing = *it;
            if (playing.get() && playing->m_event.get() &&
                (playing->m_event->getAudioEventInfo()->m_atB0 == 0 || playing->m_event->getAudioEventInfo()->m_atB0 == 1) &&
                (playing->m_event->m_viewType != 2 || m_transferViewType2) && !playing->m_at44 &&
                !playing->m_event->at51[0])
                savedStreams.push_back(playing);
        }
        int count = static_cast<int>(savedStreams.size());
        *transfer == count;
        for (PlayingAudioList::iterator it = savedStreams.begin(); it != savedStreams.end(); ++it) {
            PlayingAudioRef &playing = *it;
            rva0005B256(transfer, playing, reinterpret_cast<int *>(&version));
        }
        for (viewType = 0; viewType < 3; ++viewType) {
            if (viewType == 2 && version.m_currentVersion >= 3 && !m_transferViewType2)
                continue;
            for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
                MusicStack &stack = m_musicStack[viewType][musicSystem];
                int stackCount = static_cast<int>(stack.size());
                *transfer == stackCount;
                for (MusicStack::iterator it = stack.begin(); it != stack.end(); ++it) {
                    PlayingAudioRef playing = *reinterpret_cast<PlayingAudioRef *>(&*it);
                    rva0005B256(transfer, playing, reinterpret_cast<int *>(&version));
                }
            }
        }
    }
    xferUnicodeStringVector(transfer, &m_pendingFileText);
    xferAsciiStringVector(transfer, &m_unknownFileNames);
}

// WorldBuilder 0x788390 (MilesAudioManager.cpp asserts 4319..4335): Music
// events only; a multisound info (type 5) goes through
// addResumeOrPushMultisound, a muted sound class returns 1, a sound not for
// the local player 3. Otherwise it queues push-music request 3 in front of
// (or, with append, behind) the request list and returns the event handle.
int MilesAudioManager::pushMusicEventInternal(AudioEventRTS *event, int arg1, int arg2, int append)
{
    const AudioEventInfo *info = event->getAudioEventInfo();
    if (info == 0)
        return 0;
    if (info->m_atB0 == 5)
        return addResumeOrPushMultisound(event, 2, 1, arg1, arg2, append);
    if (event->getAudioEventInfo()->m_atB0 != 0)
        return 0;
    if (!rva0005164F(event->getSoundClass()))
        return 1;
    BfmePoolRef10 ref = rva0005286A(event, arg2);
    rva000592B8(ref.get());
    if (!shouldPlayLocally(ref.get()))
        return 3;
    Rva00051107AudioRequest *request = rva00051107();
    request->m_pendingEvent = ref;
    request->m_request = 3;
    request->m_at10 = arg1 == 0;
    if (!append)
        m_audioRequests.push_front(request);
    else
        m_audioRequests.push_back(request);
    return ref->m_playingHandle;
}

void MilesAudioManager::processPushMusicRequest(Rva00051107AudioRequest *req)
{
    int viewType = req->m_pendingEvent->m_viewType;
    int musicSystem = req->m_pendingEvent->m_musicSystem;
    MusicSystem *active = &m_activeMusicSystem[viewType];
    if (musicSystem > *active)
        moveUpMusicSystems(musicSystem, viewType, req->m_at10 == 0);
    PlayingAudioRef playing = allocatePlayingAudio();
    playing->m_event = req->m_pendingEvent;
    AsciiString file = playing->m_event->getFilename();
    void *owner = m_atB90;
    ((Rva000A8C9B *)&playing->m_at0C)->rva000A8D0B(reinterpret_cast<int>(owner), reinterpret_cast<int>(&file), 0);
    PlayingAudio *playingAudio = playing.get();
    ((Rva000A8AD8 *)&playingAudio->m_at0C)->rva000A8AD8(((Rva002D94DD *)playingAudio->m_event.get())->rva002D94DD());
    rva0005DB6C(file);
    playing->m_type = 4;
    if (musicSystem == *active) {
        putPlayingMusicOnStack(viewType, req->m_at10 == 0);
        if (((Rva000CB12FByteField *)playing->m_event.get())->get()) {
            playing->m_pushedTrackResumed = true;
            playing->m_at30 = (float)m_audioSettings->m_timeToFadeAudio;
            ((Weapon *)playing->m_event.get())->setLeechRangeActive(false);
        }
    }
    playAndStoreStream(playing, 0);
}

// WorldBuilder twin MilesAudioManager::playSample2DOr3DUsingCallbackBuffers
// (0x7A5710): binds a free loop buffer to the sound and feeds Miles from it.
bool MilesAudioManager::playSample2DOr3DUsingCallbackBuffers(PlayingAudioRef &playing, void *sample, void *sample3D)
{
    bool is3D = sample == 0;
    int i;
    for (i = 0; i < m_numLoopBuffers; ++i) {
        if (!m_loopBuffers[i].m_isValid && ((Rva0005F279Elem *)&m_loopBuffers[i])->rva00051038())
            break;
    }
    if (i == m_numLoopBuffers) {
        if (is3D)
            notifyOf3DSampleCompletion();
        else
            notifyOf2DSampleCompletion();
        return false;
    }
    playing->m_handle = i;
    if (is3D)
        playing->m_type = 3;
    else
        playing->m_type = 1;
    LoopBuffer *loop = &m_loopBuffers[i];
    if (loop->m_at10)
        cleanUpLoopBuffer(loop);
    bool valid = false;
    BfmeEventPositionView pos;
    if (is3D) {
        pos = Rva0005160FGet(playing->m_event.get(), valid);
        if (!valid)
            return false;
    } else {
        AIL_init_sample(sample);
    }
    loop->m_is3D = is3D;
    loop->m_3DSample = sample3D;
    loop->m_sample = sample;
    loop->m_heldPaused = false;
    loop->m_at44 = false;
    (BfmePoolRef10 &)loop->m_source = playing->m_event;
    loop->m_endOfLastCopy = 0;
    loop->m_playingAudio = playing.get();
    loop->m_at10 = true;
    if (!playing->m_file.isOpen())
        return false;
    const MilesSoundInfo *soundInfo = playing->m_file.getMilesSoundInfo();
    if (is3D && soundInfo->m_channels != 1) {
        playing->m_file.rva000A8A6C();
        return false;
    }
    loop->m_at3C = soundInfo->m_bits;
    loop->m_at38 = soundInfo->m_rate;
    loop->m_at40 = soundInfo->m_channels;
    putFileIntoLoopBuffer(loop, (const AudioFileContainer &)playing->m_file, 2);
    playing->m_file.rva000A8A6C();
    loop->m_playBufferSize = m_audioSettings->m_at8C * loop->m_at40 * loop->m_at38 * loop->m_at3C / 8000;
    if ((int)loop->m_playBufferSize < 0x8400)
        loop->m_playBufferSize = 0x8400;
    unsigned int rem = loop->m_playBufferSize % 4;
    if (rem)
        loop->m_playBufferSize += 4 - rem;
    loop->m_at18 = (unsigned char *)new unsigned int[loop->m_playBufferSize / 4];
    transferBytesToPlayBuffer(*loop, loop->m_playBufferSize);
    MilesSoundInfo info = *soundInfo;
    info.m_dataPtr = loop->m_at18;
    info.m_dataLen = loop->m_playBufferSize;
    if (is3D) {
        AIL_set_3D_sample_info(sample3D, &info);
        AIL_register_3D_EOS_callback(sample3D, 0);
        prep3DSample(playing, &pos);
        AIL_set_3D_sample_loop_count(sample3D, 0);
    } else {
        int format;
        if (info.m_bits == 8) {
            if (info.m_channels == 1)
                format = 0;
            else if (info.m_channels == 2)
                format = 2;
            else
                return false;
        } else if (info.m_bits == 16) {
            if (info.m_channels == 1)
                format = 1;
            else if (info.m_channels == 2)
                format = 3;
            else
                return false;
        } else {
            return false;
        }
        AIL_set_sample_type(sample, format, 0);
        AIL_set_sample_address(sample, info.m_dataPtr, info.m_dataLen);
        AIL_set_sample_playback_rate(sample, info.m_rate);
        AIL_register_EOS_callback(sample, 0);
        prepSample(&playing);
        AIL_set_sample_loop_count(sample, 0);
    }
    rva000535A6(playing);
    pauseResumeSound(playing);
    if (loop->m_at44) {
        if (is3D)
            AIL_start_3D_sample(sample3D);
        else
            AIL_start_sample(sample);
    }
    loop->m_isValid = true;
    return true;
}

// WorldBuilder 0x77A260 (unnamed) has the same three settings copies, the
// Coord3D::GetLengthSqrd call, the sqrt and the trailing column refresh.
void MilesAudioManager::GlobalVolumeData::rva0005213E(const MicrophoneSettings *settings, const Coord3D *delta)
{
    float maxAttenuation = settings->m_at2C;
    float endSqr = settings->m_at28;
    if (maxAttenuation > 0.0f) {
        float distSqr = delta->GetLengthSqrd();
        if (distSqr < settings->m_at20)
            m_at94 = 1.0f;
        else if (distSqr < endSqr) {
            float dist = sqrt(distSqr);
            float start = settings->m_at1C;
            float end = settings->m_at24;
            float fraction = (dist - start) / (end - start);
            m_at94 = 1.0f - fraction * maxAttenuation;
        } else
            m_at94 = 1.0f - maxAttenuation;
    }
    rva00052015(1);
}

// A playing-audio copy that owns its reference only when one is held: retail
// copies through the out-of-line counted copy 0x000A8C7C (Rva0036CA00Str) and
// releases only a non-null reference. The explicit constructor call keeps the
// copy inline without placement new's null test.
class NullablePlayingAudioCopy {
public:
    __forceinline NullablePlayingAudioCopy(const PlayingAudioRef &other)
    {
        value()->Rva0036CA00Str::Rva0036CA00Str(
            *reinterpret_cast<const Rva0036CA00Str *>(&other));
    }
    ~NullablePlayingAudioCopy()
    {
        if (value()->get())
            reinterpret_cast<OpaqueRefCounted *>(value()->get())->Release_Ref();
    }
    PlayingAudio *get() const { return value()->get(); }
    PlayingAudio *operator->() const { return get(); }
private:
    Rva0036CA00Str *value() const { return reinterpret_cast<Rva0036CA00Str *>(const_cast<unsigned int *>(m_storage)); }
    unsigned int m_storage[1];
};

// Native 0x5442A..0x544CB and WB 0x7917E0: prefer an unstacked
// matching music stream; retain the last stacked match when filter is zero.
PlayingAudioList::iterator MilesAudioManager::rva0005442A(int viewType, int musicSystem, int filter)
{
    PlayingAudioList::iterator found = m_playingStreams.end();
    for (PlayingAudioList::iterator it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        NullablePlayingAudioCopy playing(*it);
        if (!playing.get())
            continue;
        AudioEventRTS *event = playing->m_event.get();
        if (event->m_info->m_atB0 != 0)
            continue;
        if (event->m_viewType != viewType)
            continue;
        if (event->m_musicSystem != musicSystem)
            continue;
        if (playing->m_at44) {
            if (!filter)
                found = it;
            continue;
        }
        return PlayingAudioList::iterator(static_cast<_STL::_List_node<PlayingAudioRef> *>(it._M_node));
    }
    return found;
}


// Zero Hour's provider-name lookup, previously rowed in
// MilesAudioManagerGetProviderIndex.cpp. Retail 0x56634/60 uses the
// same 12-byte provider records at +0x6CC and count at +0x9CC.
// Keep it in the home unit: selectProvider's native string cleanup
// relies on the compiler knowing this query's nonthrowing body.
unsigned int MilesAudioManager::getProviderIndex(const AsciiString &providerName) const
{
    for (unsigned int i = 0; i < m_providerCount; ++i) {
        if (providerName.compare(m_provider3D[i].name) == 0)
            return i;
    }
    return 0xffffffff;
}

// Native COM dispatch: IDirectSound::GetSpeakerConfig at slot 8 uses
// stdcall with the receiver on the stack, unlike the engine interfaces.
class MilesProviderDirectSound {
public:
 virtual void __stdcall slot0(); virtual void __stdcall slot1();
 virtual void __stdcall slot2(); virtual void __stdcall slot3();
 virtual void __stdcall slot4(); virtual void __stdcall slot5();
 virtual void __stdcall slot6(); virtual void __stdcall slot7();
 virtual long __stdcall GetSpeakerConfig(unsigned long *config);
};
extern "C" __declspec(dllimport) void __stdcall AIL_get_DirectSound_info(void *,MilesProviderDirectSound **,void *);
extern "C" __declspec(dllimport) int __stdcall AIL_open_3D_provider(void *);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_rolloff_factor(void *,float);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_speaker_type(void *,int);
class VideoPlayerInterface {
public:
 virtual ~VideoPlayerInterface();
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
 virtual void notifyVideoPlayerOfNewProvider(bool selected);
};
extern VideoPlayerInterface *TheVideoPlayer;

// Source guide: Zero Hour MilesAudioManager.cpp::selectProvider at the
// verified Open-BFME-1 pointer 0bef414b52a39a3ab1ec98dca60d8a214de4260e.
// WB 0x79CCB0 names this method; native callers pass a bool EAX3 preference.
// Retail 0x604A3..0x606CE includes the complete eight-entry switch table.
// Cases 0/2/4 share its default target. The remaining targets map DirectSound
// configurations 1/3/5/6/7 to Miles speaker types 1/3/2/4/5 respectively.
// TheVideoPlayer is the existing data-ledger global at VA 0xE0ABA8;
// native dispatch and the reference interface agree on callback slot 26.
void MilesAudioManager::selectProvider(bool accelerated)
{
 if(!rva0005164F(4))return;
 if(m_selectedProvider<m_providerCount) {
  rva00060309();
  unselectProvider();
 }
 MilesProviderDirectSound *directSound=0;
 AIL_get_DirectSound_info(0,&directSound,0);
 if(directSound) {
  unsigned long configuration;
  directSound->GetSpeakerConfig(&configuration);
  switch((unsigned char)configuration) {
  case 0:case 2:case 4:m_selectedSpeakerType=0;break;
  case 1:m_selectedSpeakerType=1;break;
  case 3:m_selectedSpeakerType=3;break;
  case 5:m_selectedSpeakerType=2;break;
  case 6:m_selectedSpeakerType=4;break;
  case 7:m_selectedSpeakerType=5;break;
  default:m_selectedSpeakerType=0;break;
  }
 }else m_selectedSpeakerType=0;
 bool success=false;
 bool setSpeaker=false;
 unsigned provider=0xffffffff;
 if(accelerated) {
  provider=getProviderIndex(AsciiString("Creative Labs EAX 3 (TM)"));
  if(provider!=0xffffffff) {
   success=AIL_open_3D_provider(m_provider3D[provider].id)==0;
   if(success)setSpeaker=false;
  }
 }
 if(!success) {
  if(shouldUseDolbyProvider()) {
   provider=getProviderIndex(AsciiString("Dolby Surround"));
   if(provider!=0xffffffff)success=AIL_open_3D_provider(m_provider3D[provider].id)==0;
   if(success)setSpeaker=true;
  }
  if(!success) {
   m_selectedProvider=0xffffffff;
   provider=getProviderIndex(AsciiString("Miles Fast 2D Positional Audio"));
   success=AIL_open_3D_provider(m_provider3D[provider].id)==0;
   if(success)setSpeaker=true;
  }
 }
 if(success) {
  m_selectedProvider=provider;
  AIL_set_3D_rolloff_factor(m_provider3D[provider].id,0.0f);
  init3DSamplePools();
  createListener();
  if(setSpeaker) {
   if(m_forceHeadphones)AIL_set_3D_speaker_type(m_provider3D[provider].id,1);
   else AIL_set_3D_speaker_type(m_provider3D[provider].id,m_selectedSpeakerType);
  }
  if(TheVideoPlayer)TheVideoPlayer->notifyVideoPlayerOfNewProvider(true);
 }
}

// Retail 0x000552C5 (WorldBuilder twin 0x00791E20 names it; its assert at
// MilesAudioManager.cpp line 7482 ties the pending track at +0xB48 to the
// active music system). Releases the view type's pending track, else stops
// the active system's stream found by 0x5442A: arg zero only flags it
// (+0x44) while a nonzero arg closes its stream, records the settings' +0x78
// value at +0x30 and erases it. Defined after 0x5442A: retail schedules the
// iterator reload ahead of the +0x30 store, which MSVC does only once it has
// compiled 0x5442A and seen that the returned iterator's address stays put.
void MilesAudioManager::removeCurrentlyPlayingMusic(int viewType, int arg)
{
    for (;;) {
        MusicSystem activeMusicSystem = m_activeMusicSystem[viewType];
        if (m_playingMusic[viewType].get()) {
            ((Rva000A8C9B *)&m_playingMusic[viewType])->clear();
            continue;
        }
        PlayingAudioList::iterator it = rva0005442A(viewType, activeMusicSystem, arg == 0);
        if (it._M_node == m_playingStreams.end()._M_node)
            return;
        PlayingAudioRef playing = *it;
        playing->m_pushedTrackResumed = false;
        if (!arg) {
            playing->m_at44 = 1;
        } else {
            playing->m_at44 = 0;
            ((MilesStreamRef *)&playing->m_at0C)->rva000A8AC0();
            playing->m_at30 = (float)m_audioSettings->m_timeToFadeAudio;
            reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(
                OpaqueRefList::iterator((OpaqueRefList::_Node *)it._M_node));
        }
    }
}

// Retail 0x0005FDCA (WorldBuilder twin 0x00795670 names it; its asserts sit
// at MilesAudioManager.cpp lines 8207..8276). Accounts for the finished
// event (music clears its view type's bit at +0x698; sounds drop the 2D or
// 3D sample count through notifyOf2D/3DSampleCompletion) and raises the script flag named
// by the event's +0x84 string when the playing audio asks for it (+0x4D).
// Then, per playing type, stops the Miles handle and under the Miles mutex
// unmaps it when the map still points at this playing audio and returns a
// sample to its available list, or (loop buffers) clears the buffer's valid
// flag under the manager mutex and stops and cleans the buffer. The type
// becomes 5; a released event with channel volumes goes to 0x5516F.
// Retail calls the two available-list push_backs separately (ICF folded two
// instantiations at 0x5548F), so the 3D list pushes through the list<int>
// view; and it stores no unwind reset before 0x5516F, whose view is nothrow.
class Rva000A8CC9 { public: void rva000A8CC9(void); };
class ScriptEngine {
protected:
    bool *bfmeFlagForWrite(AsciiString name);   // 0x002088A0
    friend class MilesAudioManager;
};
extern ScriptEngine *TheScriptEngine;
struct Holder;
class Rva0005516F { public: void rva0005516F(Holder *holder, int viewType) throw(); };

void MilesAudioManager::releaseMilesHandles(PlayingAudio &playing)
{
    if (playing.m_event.get() && playing.m_event->m_info) {
        switch (playing.m_event->m_info->m_atB0) {
        case 1:
            {
                int viewType = playing.m_event->m_viewType;
                m_at698 &= ~(1 << viewType);
            }
            break;
        case 2:
            if (playing.m_type == 0) {
                if (playing.m_handle)
                    notifyOf2DSampleCompletion();
            } else if (playing.m_type == 2) {
                if (playing.m_handle)
                    notifyOf3DSampleCompletion();
            }
            break;
        }
        if (playing.m_raiseScriptFlagOnRelease)
            *TheScriptEngine->bfmeFlagForWrite(*(const AsciiString *)((const char *)playing.m_event.get() + 0x84)) = true;
    }
    bool released = false;
    switch (playing.m_type) {
    case 0:
        if (playing.m_handle) {
            AIL_register_EOS_callback((void *)playing.m_handle, 0);
            AIL_stop_sample((void *)playing.m_handle);
            AILMutexScope lock;
            MilesSampleHandleMap::iterator it = m_sampleMap.find(reinterpret_cast<unsigned int &>(playing.m_handle));
            if (it == m_sampleMap.end())
                lock.unlock();
            else if ((*it).second != &playing)
                lock.unlock();
            else
                m_sampleMap.erase(it);
            m_availableSamples.push_back(reinterpret_cast<void *&>(playing.m_handle));
            released = true;
        }
        break;
    case 1:
    case 3:
        {
            MilesMutexGuard guard(&m_mutex, 0);
            m_loopBuffers[playing.m_handle].m_isValid = false;
        }
        if (m_loopBuffers[playing.m_handle].m_is3D)
            AIL_stop_3D_sample(m_loopBuffers[playing.m_handle].m_3DSample);
        else
            AIL_stop_sample(m_loopBuffers[playing.m_handle].m_sample);
        cleanUpLoopBuffer(&m_loopBuffers[playing.m_handle]);
        released = true;
        break;
    case 2:
        if (playing.m_handle) {
            AIL_register_3D_EOS_callback((void *)playing.m_handle, 0);
            AIL_stop_3D_sample((void *)playing.m_handle);
            AILMutexScope lock;
            MilesSampleHandleMap::iterator it = m_3DSampleMap.find(reinterpret_cast<unsigned int &>(playing.m_handle));
            if (it == m_3DSampleMap.end())
                lock.unlock();
            else if ((*it).second != &playing)
                lock.unlock();
            else
                m_3DSampleMap.erase(it);
            reinterpret_cast<_STL::list<int> &>(m_available3DSamples).push_back(playing.m_handle);
            released = true;
        }
        break;
    case 4:
        if (*(void **)&playing.m_at0C) {
            ((Rva000A8B4B *)&playing.m_at0C)->rva000A8B4B(0);
            ((Rva000A8CC9 *)&playing.m_at0C)->rva000A8CC9();
            AILMutexScope lock;
            unsigned int stream = ((Rva000A8A98 *)&playing.m_at0C)->rva000A8A98();
            MilesSampleHandleMap::iterator it = m_streamMap.find(stream);
            if (it == m_streamMap.end())
                lock.unlock();
            else if ((*it).second != &playing)
                lock.unlock();
            else
                m_streamMap.erase(it);
            released = true;
        }
        break;
    }
    playing.m_type = 5;
    if (released) {
        AudioEventRTS *event = playing.m_event.get();
        if (event && event->m_info && !event->m_info->m_channelVolumes.empty())
            ((Rva0005516F *)this)->rva0005516F((Holder *)&event->m_info, event->m_viewType);
    }
}

// Retail 0x000613A9 (561 bytes; WorldBuilder twin 0x00794760 unnamed;
// called by 0x000615DA): kills everything that carries one playing handle
// and reports whether anything was found. The pending request found in the
// request set through 0x00055951 is erased and deleted; every queued play
// (type 0) or push-music (type 3) request whose handle or pending event
// matches is deleted and erased; the first matching 3D sound 2D sound and
// stream gives its Miles handles back (0x0005FDCA) and leaves its list; and
// the first matching track of each music stack is released and erased.
bool MilesAudioManager::rva000613A9(unsigned int handle)
{
    bool removed = false;
    {
        MilesAudioRequestTable::iterator found =
            reinterpret_cast<Rva00055951 &>(m_requestSet).rva00055951(handle);
        if (found._M_cur) {
            Rva00051107AudioRequest *req = *reinterpret_cast<Rva00051107AudioRequestSet::iterator &>(found);
            reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(
                reinterpret_cast<Rva00051B89KeyedSet::iterator &>(found));
            deleteAudioRequest(req);
            removed = true;
        }
    }

    Rva00051107AudioRequestList::iterator request = m_audioRequests.begin();
    while (request != m_audioRequests.end()) {
        Rva00051107AudioRequest *req = *request;
        bool match;
        if (req && (req->m_request == 0 || req->m_request == 3)) {
            match = req->m_at08 == handle;
            if (req->m_pendingEvent.get())
                match = match || req->m_pendingEvent->m_playingHandle == handle;
        } else {
            match = false;
        }
        if (match) {
            deleteAudioRequest(req);
            request = m_audioRequests.erase(request);
            removed = true;
        } else {
            ++request;
        }
    }

    PlayingAudioList::iterator it;
    for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it) {
        if (it->get() && (*it)->m_event->m_playingHandle == handle) {
            releaseMilesHandles(*it->get());
            reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(
                OpaqueRefList::iterator((OpaqueRefList::_Node *)it._M_node));
            removed = true;
            break;
        }
    }
    for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
        if (it->get() && (*it)->m_event->m_playingHandle == handle) {
            releaseMilesHandles(*it->get());
            reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(
                OpaqueRefList::iterator((OpaqueRefList::_Node *)it._M_node));
            removed = true;
            break;
        }
    }
    for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        if (it->get() && (*it)->m_event->m_playingHandle == handle) {
            releaseMilesHandles(*it->get());
            reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(
                OpaqueRefList::iterator((OpaqueRefList::_Node *)it._M_node));
            removed = true;
            break;
        }
    }

    for (int viewType = 0; viewType < 3; ++viewType) {
        for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
            MusicStack &stack = m_musicStack[viewType][musicSystem];
            for (MusicStack::iterator music = stack.begin(); music != stack.end(); ++music) {
                PlayingAudioRef &track = reinterpret_cast<PlayingAudioRef &>(*music);
                if (track.get() && track->m_event->m_playingHandle == handle) {
                    releaseMilesHandles(*track.get());
                    stack.erase(music);
                    removed = true;
                    break;
                }
            }
        }
    }
    return removed;
}

// playAudioEvent's callees under address-derived owners: the event's
// handle-to-kill getter (0x002A79A1), the stream holder's assignment
// (0x000A8CAE) and its forwarder 0x000A8AA6.
class Rva002A79A1DwordField { public: int get(void) const; };
class Rva000A8CAE { public: Rva000A8CAE &operator=(const Rva000A8CAE &other); };
class Rva000A8AA6 { public: void rva000A8AA6(int arg); };
// Local stream holder (PlayingAudio +0x0C shape): zeroing constructor
// 0x0007E81F (pinned PlayingAudioUnknown0C) and the counted release at
// 0x0010F149 its base destructor names (PlayingAudioConstructor.cpp view).
class BfmeStringTailRecord156 {
public:
    ~BfmeStringTailRecord156();
    bool isOpen(void) const { return m_ptr != 0; }
private:
    void *m_ptr;
};
class PlayingAudioUnknown0C : public BfmeStringTailRecord156 {
public:
    PlayingAudioUnknown0C();
    // Opens a file through 0x000A8D0B. Retail reads the owner into a
    // register after the file name temporary is built, as an inline
    // forwarder's parameter; a direct call pushes the member from memory.
    void open(void *owner, const AsciiString &file, int arg) { reinterpret_cast<Rva000A8C9B *>(this)->rva000A8D0B(reinterpret_cast<int>(owner), reinterpret_cast<int>(&file), arg); }
private:
    int m_at04;
};
// Counted copy of the event's info reference: out-of-line copy 0x000A8C7C
// (BfmeObject476Copy.cpp view, same bytes) and an inline guarded release.
// The copy stays visible to this unit so cl knows it keeps no pointer to
// the local: retail skips the release on the early null return and
// releases unguarded at the end.
struct Rva0010F149Handle {
    __forceinline Rva0010F149Handle(const AudioEventInfo *info) { reinterpret_cast<AudioEventInfoRef *>(&referent)->AudioEventInfoRef::AudioEventInfoRef(info); }
    __declspec(noinline) __declspec(nothrow) Rva0010F149Handle(const Rva0010F149Handle &r) : referent(r.referent) { if (referent) referent->Add_Ref(); }
    ~Rva0010F149Handle() { if (referent) referent->Release_Ref(); }
    AudioEventInfo *operator->(void) const { return reinterpret_cast<AudioEventInfo *>(referent); }
    OpaqueRefCounted *referent;
};

// Native 00061E37..0006236D RET4 (WorldBuilder twin 0x0078F8D0 names it,
// asserts at MilesAudioManager.cpp 6961..7246). Zero Hour's playAudioEvent
// is the ancestor: a stream (info type 0, 1 or 4) opens its file into a
// local holder and starts through playAndStoreStream; a sound effect
// (type 2) passes its play-percent draw, takes a 3D or 2D sample (killing
// the handle to kill or the lowest-priority sound first), maps it and plays
// it directly or through the callback buffers. A sound left holding more
// loops is requeued. The unused PlayingAudioRef is Zero Hour's `playing`
// (retail zeroes its slot and never releases it); the insert's value and
// result are named locals because retail packs them with the stream
// holder's slot.
void MilesAudioManager::playAudioEvent(Rva00051107AudioRequest *req)
{
    BfmePoolRef10 &event = req->m_pendingEvent;
    Rva0010F149Handle info(*reinterpret_cast<const Rva0010F149Handle *>(&event->m_info));
    if (!info.referent)
        return;
    PlayingAudioRef replaced;
    unsigned int handleToKill = reinterpret_cast<Rva002A79A1DwordField *>(event.get())->get();
    PlayingAudioRef playing = allocatePlayingAudio();
    playing->m_event = event;
    if (event->m_at4F && (float)event->getAudioEventInfo()->m_at38 < g_00DBA4FC)
        reinterpret_cast<Weapon *>(event.get())->setLeechRangeActive(true);
    event->m_at4F = false;
    if (reinterpret_cast<Rva000CB12FByteField *>(event.get())->get()) {
        playing->m_pushedTrackResumed = true;
        playing->m_at30 = (float)m_audioSettings->m_timeToFadeAudio;
        reinterpret_cast<Weapon *>(event.get())->setLeechRangeActive(false);
    }
    event->m_at4B = false;
    switch (info->m_atB0) {
    case 0:
    case 1:
    case 4: {
        if (info->m_atB0 == 1 && event->m_at4A) {
            rva000603ED();
        } else if (info->m_atB0 == 0) {
            MusicSystem musicSystem = event->m_musicSystem;
            int viewType = event->m_viewType;
            if (musicSystem > m_activeMusicSystem[viewType])
                moveUpMusicSystems(musicSystem, viewType, 0);
        }
        bool killed = false;
        if (handleToKill)
            killed = killAudioEventImmediately(handleToKill);
        PlayingAudioUnknown0C stream;
        if (!handleToKill || killed) {
            stream.open(m_atB90, event->getFilename(), 0);
            rva0005DB6C(event->getFilename());
        }
        reinterpret_cast<Rva000A8CAE &>(playing->m_at0C) = reinterpret_cast<Rva000A8CAE &>(stream);
        playing->m_type = 4;
        if (stream.isOpen()) {
            if (info->m_atB0 == 1 && event->m_at4A)
                m_at698 |= 1 << event->m_viewType;
            reinterpret_cast<Rva000A8AEE *>(&stream)->rva000A8AEE(rva0005A9F8(&playing, 1, 1));
            reinterpret_cast<Rva000A8AD8 *>(&stream)->rva000A8AD8(
                reinterpret_cast<Rva002D94DD *>(playing->m_event.get())->rva002D94DD());
            playAndStoreStream(playing, 0);
            if (playing->m_event->m_at52) {
                if (info->m_atB0 == 0)
                    startPendingMusicTracks();
                reinterpret_cast<Rva000A8AA6 *>(&stream)->rva000A8AA6(0);
                reinterpret_cast<Rva000A8B6D *>(&stream)->rva000A8B6D();
            }
            playing.clear();
        }
        break;
    }
    case 2: {
        float playPercent = info->m_at30;
        if (GetGameAudioRandomValueReal(1e-7f, 1.0f, MILES_AUDIO_MANAGER_FILE, 7064) > playPercent)
            break;
        if (event->isPositionalAudio()) {
            bool killed = false;
            if (handleToKill)
                killed = killAudioEventImmediately(handleToKill);
            int sample3D;
            if (!handleToKill || killed) {
                sample3D = rva00054596();
                if (!sample3D && killLowestPrioritySoundImmediately(event.get()))
                    sample3D = rva00054596();
            } else {
                sample3D = 0;
            }
            playing->m_handle = sample3D;
            reinterpret_cast<Rva00691040Handle &>(playing->m_file) =
                reinterpret_cast<const Rva00690FF0Handle &>(req->m_file).rva000A89E3();
            playing->m_type = 2;
            m_playing3DSounds.push_back(playing);
            if (sample3D) {
                {
                    AILMutexScope lock;
                    NameKeyGenerator::KeyToBucketMap::value_type value(sample3D, playing.get());
                    NameKeyGenerator::KeyToBucketMap::insert_result result =
                        ((NameKeyGenerator::KeyToBucketMap *)&m_3DSampleMap)->insert(value);
                }
                ++m_num3DSamplesPlaying;
                if (info->isTightlyCoupledSound()) {
                    if (playSample2DOr3DUsingCallbackBuffers(playing, 0, (void *)sample3D)) {
                        playing.clear();
                    } else {
                        reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).pop_back();
                        if (playing->m_event->hasMoreLoops()) {
                            rva0005AA72(playing);
                            playing.clear();
                        }
                    }
                } else if (!playSample3D(playing)) {
                    reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).pop_back();
                } else {
                    playing.clear();
                }
            } else {
                reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).pop_back();
                if (playing->m_event->hasMoreLoops()) {
                    rva0005AA72(playing);
                    playing.clear();
                }
            }
        } else {
            bool killed = false;
            if (handleToKill)
                killed = killAudioEventImmediately(handleToKill);
            int sample;
            if (!handleToKill || killed) {
                sample = rva0005456B();
                if (!sample && killLowestPrioritySoundImmediately(event.get()))
                    sample = rva0005456B();
            } else {
                sample = 0;
            }
            playing->m_handle = sample;
            reinterpret_cast<Rva00691040Handle &>(playing->m_file) =
                reinterpret_cast<const Rva00690FF0Handle &>(req->m_file).rva000A89E3();
            playing->m_type = 0;
            m_playingSounds.push_back(playing);
            if (sample) {
                {
                    AILMutexScope lock;
                    NameKeyGenerator::KeyToBucketMap::value_type value(sample, playing.get());
                    NameKeyGenerator::KeyToBucketMap::insert_result result =
                        ((NameKeyGenerator::KeyToBucketMap *)&m_sampleMap)->insert(value);
                }
                ++m_num2DSamplesPlaying;
                if (info->isTightlyCoupledSound()) {
                    if (playSample2DOr3DUsingCallbackBuffers(playing, (void *)sample, 0)) {
                        playing.clear();
                    } else {
                        reinterpret_cast<OpaqueRefList &>(m_playingSounds).pop_back();
                        if (playing->m_event->hasMoreLoops()) {
                            rva0005AA72(playing);
                            playing.clear();
                        }
                    }
                } else if (!playSample(playing)) {
                    reinterpret_cast<OpaqueRefList &>(m_playingSounds).pop_back();
                } else {
                    playing.clear();
                }
            } else {
                reinterpret_cast<OpaqueRefList &>(m_playingSounds).pop_back();
                if (playing->m_event->hasMoreLoops()) {
                    rva0005AA72(playing);
                    playing.clear();
                }
            }
        }
        break;
    }
    }
    if (playing.get() && playing->m_event->hasMoreLoops())
        rva0005AA72(playing);
}

// Views for the per-frame update 0x00062690 below.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
// The global audio switch the update tests first.
struct Rva00062690GlobalDataView
{
    char at000[0x99C];
    bool m_audioOn;                      // +0x99C
};

class GameEngine
{
    friend class MilesAudioManager;
private:
    bool rva00225D38(void);              // 0x00225D38 (rowed, private)
};
extern GameEngine *TheGameEngine;

// The ambient-stream pass state built on the stack (rowed ctor 0x00052B3D).
class Rva00052B3D
{
public:
    Rva00052B3D();
    PlayingAudioList::iterator m_streams[2];
};

// The subtitle window the update deletes once it reports itself finished.
class SubTitleWindow
{
public:
    ~SubTitleWindow();
    bool rva00045837() const;
};

// Zero Hour's LatchRestore: restores the latched value when the scope ends
// (vftable 0x007C5314, ??_7?$LatchRestore@_N@@6B@).
template <class T>
class LatchRestore
{
public:
    LatchRestore(T &dest, const T &src) : m_whereToRestore(dest)
    {
        m_valueToRestore = dest;
        dest = src;
    }
    virtual ~LatchRestore(void) { m_whereToRestore = m_valueToRestore; }

protected:
    T m_valueToRestore;
    T &m_whereToRestore;
};

// Retail 0x00062690 (587 bytes, slot 10; WorldBuilder twin 0x0078A530):
// the per-frame update. Skipped while audio is off; under the manager mutex
// and a re-entry latch it reopens the device once the configured interval
// since the last open has passed (if the cached reinitialize setting allows
// it), clears +0xB78, keeps the frame time from slot 109, flags the trigger
// areas for a retest, recalculates the microphone, steps the view-2 and the
// current view's volume records, runs the request, music and ambient passes,
// clears the per-frame flags, ends each view's volume frame and deletes a
// finished subtitle window.
void MilesAudioManager::update()
{
    if (TheWritableGlobalData && !((Rva00062690GlobalDataView *)TheWritableGlobalData)->m_audioOn)
        return;
    MilesMutexGuard guard(&m_mutex, 0);
    static bool inUpdate;
    if (inUpdate)
        return;
    LatchRestore<bool> latch(inUpdate, true);
    if (m_audioSettings->m_atAC > 0) {
        if (_time64(0) - m_lastDeviceOpenTime > m_audioSettings->m_atAC) {
            static bool allowReinitialize = rva006AD9B0();
            if (allowReinitialize)
                rva0006179C(1);
        }
    }
    ((Rva00056DA2 *)&atB78)->rva00056DA2();
    m_at90 = rva0005121F();
    if (m_retestAreasEveryCall || (!m_triggerAreas.empty() && TheGameEngine && TheGameEngine->rva00225D38()))
        m_areasNeedRetest = true;
    if (m_at6AB)
        recalculateMicrophone();
    reinterpret_cast<GlobalVolumeData *>(&m_volumeData[2])->rva000521F4(m_at90);
    if (m_at678 != 2 && TheGameLogic && !TheGameLogic->isGamePaused())
        reinterpret_cast<GlobalVolumeData *>(&m_volumeData[m_at678])->rva000521F4(m_at90);
    rva0005E0A4();
    ((Rva0005F279Host *)this)->rva0005F279();
    processRequestList();
    startPendingMusicTracks();
    Rva00052B3D ambient;
    processPlayingList(&ambient);
    processAmbientStreams(ambient.m_streams);
    rva0005B708();
    m_viewTypeChanged = false;
    m_at6A8 = false;
    m_areasNeedRetest = false;
    m_retestAreasEveryCall = false;
    for (int i = 0; i < 3; ++i)
        reinterpret_cast<GlobalVolumeData *>(&m_volumeData[i])->rva000520C6();
    SubTitleWindow *subTitles = m_subTitleWindow;
    if (subTitles && !subTitles->rva00045837()) {
        delete subTitles;
        m_subTitleWindow = 0;
    }
}

// The memory stream the save pass writes into (0x006023C1) and its buffer
// hand-off (0x006021A4), under their rowed address-derived names.
class BfmeMade_009CB5F0;
BfmeMade_009CB5F0 *bfmeMake_009CB5F0(void *owner);
class BfmeThingEC { public: int bfmeTakeEC(int *out); };
// XferSave (ctor 0x0060D1F7, dtor 0x0060D0B3, open 0x0060D10A); its close
// 0x0060C8CD is rowed under an address-derived owner.
class Gen009D6DD0 { public: void bfmeClose(); };
class XferSave : public Xfer {
public:
    XferSave();
    virtual ~XferSave();
    unsigned char Open(Xfer *file, int a, bool b);
private:
    char m_data[0x3C];
public:
	// A concrete Xfer overrides every pure virtual slot of the base.
	virtual int BeginBlock(const char *name);
	virtual void EndBlock();
	virtual void SkipBlock(const char *name);
	virtual Xfer &operator==(const char *const &value);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size);
};
// The load-side Xfer: built from three null pointers by 0x0060C5FA, opened by
// 0x0060C3C3, closed by 0x0060C45E and torn down by the base destructor.
class Rva0060C5FA : public Xfer {
public:
    Rva0060C5FA(void *a1, void *a2, void *a3);
private:
    unsigned char m_pad04[0x20 - 4];
public:
	// A concrete Xfer overrides every pure virtual slot of the base.
	virtual int BeginBlock(const char *name);
	virtual void EndBlock();
	virtual void SkipBlock(const char *name);
	virtual Xfer &operator==(const char *const &value);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size);
};
struct Rva0060C3C3Stream;
class XferLoad { public: bool Open(Rva0060C3C3Stream *stream, int *version); };
class Rva0060C45E { public: void clear(); };
class File { public: virtual ~File(); };
File *createMemoryReadFile(char *data, int size);
// The event refresh rowed at 0x002DAAD5 (play info regenerated around +0x74).
class Rva002DAAD5Owner { public: void rva002DAAD5(); };

// Retail 0x0006179C..0x000619D1 (RET 4, WorldBuilder twin 0x00798C50
// MilesAudioManager::reinitializeAudioSystem): snapshot, reopen and reload the device.
void MilesAudioManager::rva0006179C(int skipRequestRefresh)
{
    LatchRestore<bool> latch(m_transferViewType2, true);
    BfmeMade_009CB5F0 *writeFile = bfmeMake_009CB5F0(0);
    if (!writeFile)
        return;
    try {
        XferSave xferSave;
        xferSave.Open((Xfer *)writeFile, 0, false);
        Xfer *xfer = &xferSave;
        *xfer == *this;
        ((Gen009D6DD0 *)&xferSave)->bfmeClose();
    } catch (const XferException &xferException) {
        // WorldBuilder reports e here; retail keeps only its catch-object slot.
    }
    for (PlayingAudioList::iterator it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it)
        rva00059CE6(*it);
    for (PlayingAudioList::iterator it3D = m_playing3DSounds.begin(); it3D != m_playing3DSounds.end(); ++it3D)
        rva00059CE6(*it3D);
    rva0006047C();
    Sleep(10);
    if (!skipRequestRefresh) {
        Rva00051107AudioRequestList::iterator req = m_audioRequests.begin();
        Rva00051107AudioRequestList::iterator reqEnd = m_audioRequests.end();
        while (req != reqEnd) {
            if ((*req)->m_pendingEvent.get()) {
                ((Rva002DAAD5Owner *)(*req)->m_pendingEvent.get())->rva002DAAD5();
                rva000592B8((*req)->m_pendingEvent.get());
            }
            ++req;
        }
        Rva00051107AudioRequestSet::iterator pending = m_requestSet.begin();
        Rva00051107AudioRequestSet::iterator pendingEnd = m_requestSet.end();
        while (pending != pendingEnd) {
            if ((*pending)->m_pendingEvent.get()) {
                ((Rva002DAAD5Owner *)(*pending)->m_pendingEvent.get())->rva002DAAD5();
                rva000592B8((*pending)->m_pendingEvent.get());
            }
            ++pending;
        }
    }
    openDevice();
    int size = 0;
    char *buffer = (char *)((BfmeThingEC *)writeFile)->bfmeTakeEC(&size);
    File *readFile = createMemoryReadFile(buffer, size);
    try {
        Rva0060C5FA xferLoad(0, 0, 0);
        int version;
        ((XferLoad *)&xferLoad)->Open((Rva0060C3C3Stream *)readFile, &version);
        Xfer *xfer = &xferLoad;
        *xfer == *this;
        ((Rva0060C45E *)&xferLoad)->clear();
        m_at6B0 = 1;
        loadPostProcess();
    } catch (const XferException &xferException) {
        // WorldBuilder reports "internal xfer load failed" with e here.
    }
    free(buffer);
    ::delete readFile;
    update();
}

static __forceinline const AsciiString &bfmeEventName(const AudioEventInfo *info)
{
    return reinterpret_cast<const BfmeAudioEventInfoNameView *>(info)->getEventName();
}

// Retail 0x000609A1 (876 bytes, vftable slot 26): Zero Hour's
// removePlayingAudio by event name, limited to one view type. Under the mutex
// it releases and drops every matching sound, 3D sound and stream, erases
// matching music from the view's two stacks (the music test reads the view
// type through the inline getter, as the 0x583BA sound loops do), erases
// matching queued events (0x554A9) and drops matching pending requests.
void MilesAudioManager::removePlayingAudio(const AsciiString &eventName, int viewType)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    PlayingAudio *audio;
    OpaqueRefList::iterator it;

    it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
        } else {
            ++it;
        }
    }
    it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
        } else {
            ++it;
        }
    }
    it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingStreams).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(it);
        } else {
            ++it;
        }
    }

    for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
        MusicStack &stack = m_musicStack[viewType][musicSystem];
        MusicStack::iterator music = stack.begin();
        while (music != stack.end()) {
            playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
            audio = playing.get();
            if (audio && bfmeEventName(audio->m_event->m_info) == eventName
                && audio->m_event->getViewType() == viewType) {
                music = stack.erase(music);
            } else {
                ++music;
            }
        }
    }

    QueuedAudioEvents::iterator event = m_queuedEvents[viewType].begin();
    while (event != m_queuedEvents[viewType].end()) {
        if (bfmeEventName(event->m_info) == eventName) {
            unmapPhysicalHandle(event->m_playingHandle);
            event = (QueuedAudioEvents::iterator)reinterpret_cast<Rva000554A9 &>(m_queuedEvents[viewType]).rva000554A9(event);

        } else {
            ++event;
        }
    }

    Rva00051107AudioRequestSet::iterator pending = m_requestSet.begin();

    while (pending != m_requestSet.end()) {
        if ((*pending)->m_pendingEvent.get()
            && bfmeEventName((*pending)->m_pendingEvent->m_info) == eventName) {
            Rva00051107AudioRequestSet::iterator doomed = pending;
            ++pending;
            Rva00051107AudioRequest *request = *doomed;
            reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(
                reinterpret_cast<Rva00051B89KeyedSet::iterator &>(doomed));
            deleteAudioRequest(request);
        } else {
            ++pending;
        }
    }

    Rva00051107AudioRequestList::iterator request = m_audioRequests.begin();
    while (request != m_audioRequests.end()) {
        if ((*request)->m_request == 0 && (*request)->m_pendingEvent.get()
            && bfmeEventName((*request)->m_pendingEvent->m_info) == eventName) {
            request = m_audioRequests.erase(request);
        } else {
            ++request;
        }
    }
}

// The 0x90-byte event copy 0x0005286A allocates (copy ctor 0x00051DCC).
struct BfmeAudioEventPrefix136;
class Rva005813E
{
public:
    Rva005813E();
    Rva005813E(const BfmeAudioEventPrefix136 &source);
private:
    char m_opaque[0x90];
};

// Retail 0x0005286A (address-derived, RET 0xC; WorldBuilder twin 0x00786D30,
// Zero Hour's addAudioEvent preparation): copies the event into a new pooled
// event, gives it a fresh playing handle unless the caller keeps its own, and
// generates its file and play info.
BfmePoolRef10 MilesAudioManager::rva0005286A(AudioEventRTS *event, int arg)
{
    BfmePoolRef10 copy(reinterpret_cast<BfmePoolHolder88 *>(new Rva005813E(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(event))));
    if (!arg)
        reinterpret_cast<GameMessage *>(copy.get())->friend_setList(reinterpret_cast<GameMessageList *>(allocateNewHandle()));
    copy->rva002D9ADC();
    copy->generatePlayInfo();
    return copy;
}

// The event-info table at +0xBC is walked through the rowed 0x00427195
// (first cursor) and 0x00411084 (advance) declared above.
struct AudioEventInfoTableNode
{
    void *m_next;
    AsciiString m_name;
    AudioEventInfo *m_info;
};
class Rva001D98BD { public: bool rva001D98BD(int type); };

// Native 0005AE2B..0005AEDD, RET8. Under the mutex, appends a counted
// reference to every event info of the given +0xB0 type that 0x00050EFA can
// still add a reference to; that extra reference is dropped once queued.
void MilesAudioManager::rva0005AE2B(int type, Rva0005A084Vector *output)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva000411084 it;
    {
        Rva000411084 first;
        reinterpret_cast<Rva000427195 *>(&m_allAudioEventInfo)->first(&first);
        it = first;
    }
    for (; it.m_current; it.next()) {
        AudioEventInfo *info = reinterpret_cast<AudioEventInfoTableNode *>(it.m_current)->m_info;
        OpaqueRefCounted *counted = reinterpret_cast<OpaqueRefCounted *>(info);
        if (info->m_atB0 == type && counted->rva00050EFA()) {
            output->push_back(*reinterpret_cast<const Rva0005A084Element *>(&AudioEventInfoRef(info)));
            counted->Release_Ref();
        }
    }
}

// Native 0005AEDD..0005AF92, RET8. As 0x5AE2B, with the type test made by
// the recursive 0x001D98BD (composite infos of type 5 test their children).
void MilesAudioManager::rva0005AEDD(int type, Rva0005A084Vector *output)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva000411084 it;
    {
        Rva000411084 first;
        reinterpret_cast<Rva000427195 *>(&m_allAudioEventInfo)->first(&first);
        it = first;
    }
    for (; it.m_current; it.next()) {
        AudioEventInfo *info = reinterpret_cast<AudioEventInfoTableNode *>(it.m_current)->m_info;
        OpaqueRefCounted *counted = reinterpret_cast<OpaqueRefCounted *>(info);
        if (reinterpret_cast<Rva001D98BD *>(info)->rva001D98BD(type) && counted->rva00050EFA()) {
            output->push_back(*reinterpret_cast<const Rva0005A084Element *>(&AudioEventInfoRef(info)));
            counted->Release_Ref();
        }
    }
}

// Look direction from the camera to the first corner, in the WB shape (a copy of
// the camera position, the corner subtracted in place, then the squared length):
// the struct form puts lookDir.z in xmm0 and the squared length in xmm2 as retail
// does; the plain component expressions swap those registers.
struct MicVec : public Coord3D {
    MicVec(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
    void sub(const Coord3D &c) { x -= c.x; y -= c.y; z -= c.z; }
    float lenSqr() const { return x * x + y * y + z * z; }
};

// WorldBuilder twin MilesAudioManager::recalculateMicrophone (0x78A8C0):
// pulls the listener from the camera toward the ground, faces it along the
// camera's ground heading and scales +0x8C by the shortest corner edge.
void MilesAudioManager::recalculateMicrophone(void)
{
    const MicrophoneSettings *settings = &m_audioSettings->m_microphoneSettings[m_at678];
    m_at6AB = false;
    Coord3D cameraPos;
    cameraPos.x = 0.0f;
    cameraPos.y = 0.0f;
    cameraPos.z = 0.0f;
    rva000511C3(&cameraPos);
    ScreenToTerrainSet corners;
    getScreenToTerrainPositions(&corners);
    if (m_cameraPos == cameraPos && ((Rva00051CF1 *)&m_corners)->rva00051CF1((Rva00051CF1 &)corners))
        return;
    m_corners = corners;
    (Coord3D &)m_cameraPos = cameraPos;

    MicVec lookDir(cameraPos);
    lookDir.sub(m_corners[0].m_pos);
    float lengthSqr = lookDir.lenSqr();
    float fraction;
    if (lengthSqr * settings->m_at04 >= settings->m_at14) {
        float dist = sqrtf(lengthSqr);
        fraction = settings->m_at10 / dist;
    } else if (lengthSqr <= settings->m_at0C)
        fraction = 1.0f;
    else if (lengthSqr * settings->m_at04 <= settings->m_at0C) {
        float dist = sqrtf(lengthSqr);
        fraction = settings->m_at08 / dist;
    } else
        fraction = settings->m_at00;

    {
        Coord3D scaled;
        scaled.x = lookDir.x * fraction;
        scaled.y = lookDir.y * fraction;
        scaled.z = lookDir.z * fraction;
        Coord3D mic;
        mic.x = cameraPos.x - scaled.x;
        mic.y = cameraPos.y - scaled.y;
        mic.z = cameraPos.z - scaled.z;
        if (m_corners[0].m_valid) {
            m_micPos.x = (m_corners[0].m_pos.x - mic.x) * settings->m_at18 + mic.x;
            m_micPos.y = (m_corners[0].m_pos.y - mic.y) * settings->m_at18 + mic.y;
            m_micPos.z = mic.z;
        } else {
            (Coord3D &)m_micPos = mic;
        }
    }
    if (lookDir.x != 0.0f || lookDir.y != 0.0f) {
        m_micDir.x = -lookDir.x;
        m_micDir.y = -lookDir.y;
        m_micDir.z = 0.0f;
        m_micDir.Normalize();
    }
    if (m_listener) {
        AIL_set_3D_orientation(m_listener, m_micDir.x, m_micDir.y, -m_micDir.z, 0.0f, 0.0f, -1.0f);
        AIL_set_3D_position(m_listener, m_micPos.x, m_micPos.y, -m_micPos.z);
    }

    {
        Coord3D delta;
        delta.x = cameraPos.x - m_micPos.x;
        delta.y = cameraPos.y - m_micPos.y;
        delta.z = cameraPos.z - m_micPos.z;
        reinterpret_cast<GlobalVolumeData *>(&m_volumeData[m_at678])->rva0005213E(settings, &delta);
    }

    float shortest = _STL::_LimG<bool>::_F_inf.val;
    for (int i = 1; i < 5; ++i) {
        int next = i + 1;
        if (next == 5)
            next = 1;
        if (m_corners[i].m_valid && m_corners[next].m_valid) {
            const AudioAreaCorner &audioAreaCorner = m_corners[i];
            const AudioAreaCorner &b = m_corners[next];
            float ex = audioAreaCorner.m_pos.x - b.m_pos.x;
            float ey = audioAreaCorner.m_pos.y - b.m_pos.y;
            float edgeSqr = ex * ex + ey * ey;
            if (shortest > edgeSqr)
                shortest = edgeSqr;
        }
    }
    if (shortest >= settings->m_at3C)
        m_at8C = 0.0f;
    else if (shortest <= settings->m_at44)
        m_at8C = 1.0f;
    else
    {
        float dist = sqrtf(shortest);
        m_at8C = (settings->m_at38 - dist) / (settings->m_at38 - settings->m_at40);
    }
}

// MilesAudioManager::processFade (WorldBuilder twin 0x7A0EB0, asserts at
// MilesAudioManager.cpp lines 11651..11740; retail 0x00053448, 350 B): advances
// the volume fade toward m_at3C and the fade-down / fade-up time in m_at30 by
// this frame's step (m_at90, or g_00DBA4FC for a view-type-2 event on the
// tactical view while the step is below 1); true while a fade is in progress.
class Rva00050D86 { public: bool rva00050D86(unsigned char mask); };

bool MilesAudioManager::processFade(PlayingAudioRef &playing)
{
    PlayingAudio *audio = playing.get();
    if (((Rva00050D86 *)audio)->rva00050D86(4))
        return false;
    const float &frame = m_at90;
    float elapsed = frame;
    // A named condition keeps the step in its spill slot (retail stores it
    // right after the load); the inline && chain keeps it in a register.
    bool alt = m_at678 == 0 && frame < 1.0f && audio->m_event->m_viewType == 2;
    if (alt)
        elapsed = g_00DBA4FC;
    bool fading = false;
    if (audio->m_at40 > 0.0f) {
        float remaining = audio->m_at40;
        audio->m_at40 -= elapsed;
        if (playing->m_at40 <= 0.0f) {
            playing->m_at40 = 0.0f;
            ((Rva00481FAFFloatSlot *)playing->m_event.operator->())->store(playing->m_at3C);
        } else {
            float volume = playing->m_event->m_at2C;
            float delta = volume - playing->m_at3C;
            if (remaining == 0.0f)
                remaining = 1.0f;
            ((Rva00481FAFFloatSlot *)playing->m_event.operator->())->store(volume - delta * (elapsed / remaining));
        }
        fading = true;
    }
    if (playing->m_at44 || playing->m_at46) {
        playing->m_at30 += elapsed;
        if (playing->m_at30 >= (float)m_audioSettings->m_timeToFadeAudio) {
            playing->m_at30 = (float)m_audioSettings->m_timeToFadeAudio;
            if (!playing->m_at44)
                playing->m_at48 = true;
            playing->m_at44 = false;
            playing->m_at46 = false;
            playing->m_pushedTrackResumed = false;
            playing->m_fadeUpFromShroud = false;
        }
        return true;
    }
    if (playing->m_pushedTrackResumed || playing->m_fadeUpFromShroud) {
        playing->m_at30 -= elapsed;
        if (playing->m_at30 <= 0.0f) {
            playing->m_at30 = 0.0f;
            playing->m_pushedTrackResumed = false;
            playing->m_fadeUpFromShroud = false;
        }
        return true;
    }
    return fading;
}

// Native 5F2BB..5FA3C RET4; WorldBuilder callgraph names processAmbientStreams.
// The event's volume product getter, rowed at 0x002D94E4 under an
// address-derived owner.
class Rva002D94E4 {public:float rva002D94E4(void) const;};

// Ambient stream fade fraction (retail 0x0005117B, address-derived owner):
// 1 - fadeFrames / AudioSettings +0x78, clamped to [0, 1]. Its body has to
// be visible here: processAmbientStreams keeps a playing stream's +0x44
// flag in dl across the calls only because cl sees this callee touches
// neither edx nor memory (same as Rva000515E4Less and 0x5BD30 above).
class Rva0005117B {
public:
    float rva0005117B(float v);
private:
    char m_lead[0x10];
    AudioSettings *m_audioSettings;      // +0x10, MilesAudioManager's
};
float Rva0005117B::rva0005117B(float v)
{
    float f = 1.0f - v / (float)m_audioSettings->m_timeToFadeAudio;
    if (f < 0.0f)
        v = 0.0f;
    else if (f > 1.0f)
        v = 1.0f;
    else
        v = f;
    return v;
}
struct AmbientInfoNameView {virtual void slot0();virtual const AsciiString &slot1();};
static __forceinline bool ambientSameName(AudioEventInfo *audioEventInfo, AudioEventInfo *b)
{
 const AsciiString &left=reinterpret_cast<AmbientInfoNameView*>(audioEventInfo)->slot1();
 const AsciiString &right=reinterpret_cast<AmbientInfoNameView*>(b)->slot1();
 return reinterpret_cast<const StringBase<char> &>(right).compare(reinterpret_cast<const StringBase<char> &>(left))==0;
}
static __forceinline bool ambientSameNameR(AudioEventInfo *audioEventInfo, AudioEventInfo *a)
{
 const AsciiString &left=reinterpret_cast<AmbientInfoNameView*>(a)->slot1();
 const AsciiString &right=reinterpret_cast<AmbientInfoNameView*>(audioEventInfo)->slot1();
 return reinterpret_cast<const StringBase<char> &>(right).compare(reinterpret_cast<const StringBase<char> &>(left))==0;
}
void MilesAudioManager::processAmbientStreams(PlayingAudioList::iterator *streams)
{
    unsigned int view = 1 << m_at678;
    if ((m_at690 & view) || (m_musicPausedViewTypes & view) || !rva0005164F(16))
        return;
    QueuedAudioEvents &events = m_queuedEvents[m_at678];
    QueuedAudioEvents::iterator eventEnd = events.end();
    PlayingAudioList::iterator streamEnd = m_playingStreams.end();
    float minimum = m_audioSettings->m_minSampleVolume;
    int fadeTime = m_audioSettings->m_timeToFadeAudio;

    // Loudest queued markers not yet playing, and the loudest marker that
    // matches each playing stream.
    float bestVolume[2];
    QueuedAudioEvents::iterator bestEvent[2];
    float oldVolume[2];
    QueuedAudioEvents::iterator sameEvent[2];
    for (int init = 0; init < 2; ++init) {
        sameEvent[init] = eventEnd;
        oldVolume[init] = 0;
        bestEvent[init] = eventEnd;
        bestVolume[init] = minimum;
    }

    bool hasExpired = false;
    for (QueuedAudioEvents::iterator it = events.begin(); it != eventEnd; ++it) {
        BfmeStringTailRecord144 *event = it;
        float volume = rva00059AD0(event, 0);
        if (it->m_at8C) {
            it->m_at88 += m_at90;
            if (it->m_at88 >= fadeTime) {
                hasExpired = true;
                continue;
            }
            volume *= 1.0f - it->m_at88 / fadeTime;
        }
        if (volume >= minimum) {
            bool found = false;
            for (int i = 0; !found && i < 2; ++i) {
                if (streams[i] != streamEnd) {
                    PlayingAudioRef playing = *streams[i];
                    if (ambientSameName(event->m_info, playing->m_event->m_info)) {
                        found = true;
                        if (volume > oldVolume[i]) {
                            oldVolume[i] = volume;
                            sameEvent[i] = it;
                        }
                    }
                }
            }
            if (!found) {
            for (int i = 0; i < 2 && bestEvent[i] != eventEnd; ++i) {
                if (ambientSameNameR(bestEvent[i]->m_info, event->m_info)) {
                    if (volume > bestVolume[i]) {
                        for (int j = i; j < 1; ++j) {
                            bestEvent[j] = bestEvent[j + 1];
                            bestVolume[j] = bestVolume[j + 1];
                        }
                        bestEvent[1] = eventEnd;
                        bestVolume[1] = minimum;
                        break;
                    } else {
                        found = true;
                    }
                }
            }
            }
            if (!found) {
            for (int k = 0; k < 2; ++k) {
                if (volume > bestVolume[k] && (m_at6A8 != 0 || m_at6A8 == 0)) {
                    for (int j = 1; j > k; --j) {
                        bestEvent[j] = bestEvent[j - 1];
                        bestVolume[j] = bestVolume[j - 1];
                    }
                    bestEvent[k] = it;
                    bestVolume[k] = volume;
                    break;
                }
            }
            }
        }
    }

    int used = 0;
    bool stop[2];
    for (int i = 0; i < 2; ++i) {
        if (streams[i] != streamEnd) {
            ++used;
            stop[i] = false;
        } else {
            stop[i] = true;
        }
    }

    int available = m_maxAmbientStreams - used;
    bool done = false;
    while (used > 0 && !done) {
        int weakest = -1;
        float low = 3.402823466e38f;
        for (int i = 0; i < 2; ++i) {
            if (stop[i])
                continue;
            float value = oldVolume[i];
            if (value > 0.0f && !(*streams[i])->m_at44)
                value += m_audioSettings->m_ambientStreamHysteresisVolume * 0.01f;
            if (value < low) {
                low = value;
                weakest = i;
            }
        }
        if (weakest == -1)
            break;
        if (available < 0 || low < bestVolume[available]) {
            stop[weakest] = true;
            ++available;
            --used;
        } else {
            done = true;
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (streams[i] != streamEnd) {
            PlayingAudioRef playing = *streams[i];
            playing->m_at44 = stop[i];
            if (stop[i]) {
                playing->m_at30 += m_at90;
            } else {
                playing->m_at30 -= m_at90;
                if (playing->m_at30 < 0.0f) {
                    playing->m_at30 = 0;
                    playing->m_pushedTrackResumed = false;
                } else {
                    playing->m_pushedTrackResumed = true;
                }
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (streams[i] != streamEnd) {
            PlayingAudioRef playing = *streams[i];
            float volume = oldVolume[i];
            volume = reinterpret_cast<Rva002D94E4 *>(playing->m_event.get())->rva002D94E4() * volume;
            if (playing->m_at44)
                volume *= reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30);
            if (volume < minimum) {
                playing->m_status = 1;
                playing->m_event->m_at4C = true;
                reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(
                    reinterpret_cast<OpaqueRefList::iterator &>(streams[i]));
                streams[i] = streamEnd;
            } else {
                if (!playing->m_at44)
                    volume *= reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30);
                volume *= reinterpret_cast<GlobalVolumeData *>(&m_volumeData[m_at678])->rva0005910F(playing->m_event.get());
                reinterpret_cast<Rva000A8AEE *>(&playing->m_at0C)->rva000A8AEE(volume);
                if (m_at6A8)
                    rva00052FA0(playing);
            }
        }
    }

    int candidate = 0;
    for (int slot = 0; available > 0 && candidate < 2 && bestEvent[candidate] != eventEnd && slot < 2; ++slot) {
        if (streams[slot] == streamEnd) {
            PlayingAudioRef playing = allocatePlayingAudio();
            playing->m_event.rva00053D26(reinterpret_cast<BfmePoolHolder88 *>(
                new Rva0051D93(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(bestEvent[candidate]))));
            playing->m_event->m_ownerType = 6;
            reinterpret_cast<GameMessage *>(playing->m_event.get())->friend_setList(
                reinterpret_cast<GameMessageList *>(m_nextHandle++));
            playing->m_event->generatePlayInfo();
            playing->m_event->rva002D9ADC();
            reinterpret_cast<Weapon *>(playing->m_event.get())->setLeechRangeActive(false);
            AsciiString filename = playing->m_event->getFilename();
            void *owner = m_atB90;
            reinterpret_cast<Rva000A8C9B *>(&playing->m_at0C)->rva000A8D0B(reinterpret_cast<int>(owner), reinterpret_cast<int>(&filename), 0);
            playing->m_type = 4;
            playing->m_at30 = fadeTime - g_00DBA4FC;
            if (m_viewTypesResetSinceUpdate & (1 << m_at678)) {
                playing->m_at30 = 0;
                playing->m_pushedTrackResumed = false;
            } else {
                playing->m_pushedTrackResumed = true;
            }
            rva0005DB6C(filename);
            if (0) { AsciiString dbg(filename); rva0005DB6C(dbg); }
            float volume = reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30) * bestVolume[candidate];
            volume *= reinterpret_cast<GlobalVolumeData *>(&m_volumeData[m_at678])->rva0005910F(playing->m_event.get());
            volume *= reinterpret_cast<Rva002D94E4 *>(playing->m_event.get())->rva002D94E4();
            reinterpret_cast<Rva000A8AEE *>(&playing->m_at0C)->rva000A8AEE(volume);
            reinterpret_cast<Rva000A8AD8 *>(&playing->m_at0C)->rva000A8AD8(
                reinterpret_cast<Rva002D94DD *>(playing->m_event.get())->rva002D94DD());
            rva00052FA0(playing);
            playAndStoreStream(playing, 0);
            --available;
            ++candidate;
        }
    }

    if (hasExpired) {
        QueuedAudioEvents::iterator it = events.begin();
        while (it != eventEnd) {
            if (it->m_at88 >= fadeTime) {
                unmapPhysicalHandle(it->m_playingHandle);
                it = reinterpret_cast<QueuedAudioEvents::iterator>(
                    reinterpret_cast<Rva000554A9 *>(&events)->rva000554A9(it));
                eventEnd = events.end();
            } else {
                ++it;
            }
        }
    }
    m_viewTypesResetSinceUpdate &= ~(1 << m_at678);
}


// Retail 0x000533CB (125B, MilesAudioManager vtable 0x00BC55B0 slot 67):
// takes the +0x9D4 mutex guard, ignores the call when no provider is
// selected, flips the +0x6A6 headphone override and applies the resulting
// speaker type to the selected provider: 1 when the override turns on, else
// 5 for the Dolby selection (+0xBF0 == 1), else the stored speaker type.
void MilesAudioManager::rva000533CB(void)
{
    MilesMutexGuard guard(&m_mutex, 0);
    unsigned int provider = m_selectedProvider;
    if (provider >= m_providerCount)
        return;
    bool enable = (m_forceHeadphones == 0);
    m_forceHeadphones = enable;
    if (enable)
        AIL_set_3D_speaker_type(m_provider3D[provider].id, 1);
    else if (m_selectedSpeakerType == 1)
        AIL_set_3D_speaker_type(m_provider3D[provider].id, 5);
    else
        AIL_set_3D_speaker_type(m_provider3D[provider].id, m_selectedSpeakerType);
}

// Existing event-delay subtractor, rowed at 0x002D94EB.
class Rva002D94EB { public: void rva002D94EB(float value); };
// Retail 0x00053646: processRequest's failed-file/portion fallback.
// See reverse/attempt_evidence/0x00053646_visibility.txt.
void MilesAudioManager::rva00053646(Rva00051107AudioRequest *req, bool *removeRequest)
{
    BfmePoolRef10 &event = req->m_pendingEvent;
    AudioEventRTS *first = event.get();
    if (!first) return;
    if (first->getNextPlayPortion() == 3) { *removeRequest = true; return; }
    if (req->m_at14 && !m_at6AC) {
        req->m_at14 = false;
        if (!m_at6B0) reinterpret_cast<Weapon *>(first)->setLeechRangeActive(true);
    }
    if (reinterpret_cast<Rva00050DD0 *>(&req->m_file)->rva00050DD0()) {
        int oldPortion = event->m_portionToPlayNext;
        event->m_at53 = true;
        event->advanceNextPlayPortion();
        event->m_startedPlaying = true;
        event->rva002D9ADC();
        if (event->m_portionToPlayNext != 3) {
            if (oldPortion != event->m_portionToPlayNext) {
                reinterpret_cast<Rva00691040Handle &>(req->m_file) = m_audioFileCache->requestFile(event, req->m_file.getAt3C());
            } else if (event->m_portionToPlayNext == 1) {
                int count = event->m_info->getSoundsVector().size();
                for (int i=0; i<count; ++i) {
                    reinterpret_cast<Rva00691040Handle &>(req->m_file) = m_audioFileCache->requestFile(event, req->m_file.getAt3C());
                    if (!reinterpret_cast<Rva00050DD0 *>(&req->m_file)->rva00050DD0()) break;
                    event->m_startedPlaying = true;
                    event->rva002D9ADC();
                }
                if (reinterpret_cast<Rva00050DD0 *>(&req->m_file)->rva00050DD0()) *removeRequest = true;
            } else *removeRequest = true;
        } else *removeRequest = true;
        event->m_at53 = false;
    }
    if (!reinterpret_cast<Rva00050DF0 *>(req)->rva00050DF0()) {
        reinterpret_cast<Rva002D94EB *>(event.get())->rva002D94EB(m_at90);
        req->m_at11 = true;
    }
}
// WorldBuilder names putPlayingMusicOnStack (assert line 7431).
// Retail 0x0005A812..0x0005A908. The visible deque chain below proves that
// pushing the counted copy does not retain its address, so its release stays
// in EDI and the iterator's return value can share the dead argument slot.
void MilesAudioManager::putPlayingMusicOnStack(int viewType, int arg)
{
    MusicSystem activeMusicSystem = m_activeMusicSystem[viewType];
    PlayingAudioRef &music = m_playingMusic[viewType];
    if (music.get()) {
        MusicSystem musicSystem = music->m_event->m_musicSystem;
        ((Rva00058B90 *)&m_musicStack[viewType][musicSystem])->rva00058B90(*(const Rva0036CA00Str *)&music);
        ((Rva000A8C9B *)&music)->clear();
        return;
    }
    PlayingAudioList::iterator it = rva0005442A(viewType, activeMusicSystem, 1);
    if (it != m_playingStreams.end()) {
        const Rva0036CA00Str ref(*reinterpret_cast<const Rva0036CA00Str *>(&*it));
        ((Rva00058B90 *)&m_musicStack[viewType][activeMusicSystem])->rva00058B90(ref);
        PlayingAudio *playing = ref.get();
        playing->m_pushedTrackResumed = false;
        if (!arg) {
            playing->m_at44 = true;
        } else {
            playing->m_at44 = false;
            ((MilesStreamRef *)&playing->m_at0C)->rva000A8AC0();
            playing->m_at30 = (float)m_audioSettings->m_timeToFadeAudio;
            reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(
                OpaqueRefList::iterator((OpaqueRefList::_Node *)it._M_node));
        }
    }
}

// Exact select-any copies of the existing 31/18/45/132-byte owners. All four
// bodies and their relocations were checked against retail; see the evidence.
__declspec(noinline) inline Rva0036CA00Str::Rva0036CA00Str(const Rva0036CA00Str &other)
    : m_ptr(other.m_ptr)
{
    if (m_ptr)
        InterlockedIncrement((long volatile *)((char *)m_ptr + 4));
}

class Rva0005800A { public: void rva0005800A(const Rva0036CA00Str &); };
namespace _STL {
template <> __declspec(noinline) inline void _Construct<Rva0036CA00Str, Rva0036CA00Str>(
    Rva0036CA00Str *p, const Rva0036CA00Str &v) throw()
{
    new (p) Rva0036CA00Str(v);
}
}
struct StackIterator {
    void set_node(Rva0036CA00Str **n) { node = n; first = *n; last = first + 32; }
    Rva0036CA00Str *cur, *first, *last;
    Rva0036CA00Str **node;
};
struct StackLayout {
    StackIterator start, finish;
    Rva0036CA00Str **map;
    unsigned mapSize;
};
__declspec(noinline) inline void Rva00058B90::rva00058B90(const Rva0036CA00Str &v)
{
    StackLayout *p = (StackLayout *)this;
    if (p->finish.cur != p->finish.last - 1) {
        _STL::_Construct(p->finish.cur, v);
        ++p->finish.cur;
    } else {
        ((Rva0005800A *)this)->rva0005800A(v);
    }
}

namespace _STL { template <> void deque<void *, allocator<void *> >::_M_reserve_map_at_back(unsigned int); }
struct StackReserve : _STL::deque<void *, _STL::allocator<void *> > {
    using _STL::deque<void *, _STL::allocator<void *> >::_M_reserve_map_at_back;
};
// Like NullablePlayingAudioCopy above, this guard constructs the counted value
// explicitly and releases only a non-null copy, matching the slow path's EH.
class StackCopy {
    unsigned storage;
public:
    StackCopy(const Rva0036CA00Str &v) { value()->Rva0036CA00Str::Rva0036CA00Str(v); }
    ~StackCopy() { if (value()->get()) reinterpret_cast<OpaqueRefCounted *>(value()->get())->Release_Ref(); }
    Rva0036CA00Str *value() { return (Rva0036CA00Str *)&storage; }
};
__declspec(noinline) inline void Rva0005800A::rva0005800A(const Rva0036CA00Str &v)
{
    StackCopy copy(v);
    StackLayout *p = (StackLayout *)this;
    ((StackReserve *)this)->_M_reserve_map_at_back(1);
    *(p->finish.node + 1) = (Rva0036CA00Str *)_STL::allocator<char>().allocate(0x80, 0);
    new (p->finish.cur) Rva0036CA00Str(*copy.value());
    p->finish.set_node(p->finish.node + 1);
    p->finish.cur = p->finish.first;
}

// Native5987D..59A13,406B RET8; WB79AEB0 names friend_xferSubAudioEventRTS.
// Saved event IDs share the pooled event through the hash table at+B78.
// The native29B pair constructor,36B insert and112B noresize chain establish
// the two-word payload and by-value iterator/bool result. Let the complete
// STLport chain remain visible so its result shares the dead lookup slots.
typedef _STL::hash_map<unsigned int, BfmePoolRef10> MilesSavedAudioEventMap;

void MilesAudioManager::friend_xferSubAudioEventRTS(Xfer *xfer, BfmePoolRef10 *eventRef)
{
    XferVersion version;
    version.m_version = 1;
    version.m_currentVersion = 1;
    *xfer == (Xfer::Version &)version;
    bool present = *reinterpret_cast<AudioEventRTS *const *>(eventRef) != 0;
    *xfer == present;
    if (present) {
        unsigned int id = reinterpret_cast<unsigned int>(eventRef->get());
        *xfer == *(reinterpret_cast<int *>(&id));
        MilesHandleMap *loaded = reinterpret_cast<MilesHandleMap *>(&atB78);
        {
            MilesHandleMap::iterator found = loaded->find(id);
            // Compare the nodes directly, avoiding an unused external iterator wrapper.
            if (found._M_cur != loaded->end()._M_cur) {
                if (xfer->IsLoading())
                    *eventRef = *reinterpret_cast<const BfmePoolRef10 *>(&found->second);
                return;
            }
        }
        {
            if (xfer->IsLoading())
                eventRef->rva00053D26(reinterpret_cast<BfmePoolHolder88 *>(new Rva005813E()));
            unsigned int savedHandle = (*eventRef)->m_playingHandle;
            *xfer == savedHandle;
            if (xfer->IsLoading()) {
                reinterpret_cast<GameMessage *>(eventRef->get())->friend_setList(reinterpret_cast<GameMessageList *>(allocateNewHandle()));
                _STL::pair<Rva0005B256HandleMap::iterator, bool> result =
                    reinterpret_cast<Rva0005B256HandleMap *>(&atB6C)->insert(
                        Rva0005B256HandleMap::value_type(savedHandle, reinterpret_cast<Image *>((*eventRef)->m_playingHandle)));
                if (!result.second)
                    reinterpret_cast<GameMessage *>(eventRef->get())->friend_setList(reinterpret_cast<GameMessageList *>(result.first->second));
            }
            reinterpret_cast<MilesSavedAudioEventMap *>(loaded)->insert(
                MilesSavedAudioEventMap::value_type(id, *eventRef));
            reinterpret_cast<Rva002D9F9FOwner *>(eventRef->get())->rva002D9F9F(reinterpret_cast<Rva002D9F9FArg *>(xfer));
        }
    } else if (xfer->IsLoading()) {
        eventRef->rva000519BD();
    }
}

// Rowed gate535CC and audibility predicate52F1E, rehomed with their caller.
class Rva002DA318 { public: bool rva002DA318(); };
class Rva000535CC
{
public:
    void rva000535CC(void *p);
private:
    char at00[0x10];
    AudioSettings *m_audioSettings;
    char at14[0x6AC - 0x14];
    bool m_at6AC;
    char at6AD[0x6B0 - 0x6AD];
    int m_at6B0;
};

void Rva000535CC::rva000535CC(void *p)
{
    if ((*(PlayingAudio **)p)->m_at4C == 0)
        return;
    if (m_at6AC != 0)
        return;
    (*(PlayingAudio **)p)->m_at4C = 0;
    if (m_at6B0 != 0)
        return;
    (*(PlayingAudio **)p)->m_pushedTrackResumed = 1;
    (*(PlayingAudio **)p)->m_at30 = (float)m_audioSettings->m_timeToFadeAudio;
}

// Retail 0x00052F1E: an event stays audible below the settings' +0xB8
// cutoff when its info's type bit 3 is set, its priority is 4 or its +0x1C
// reaches the cutoff.
int MilesAudioManager::rva00052F1E(void *event)
{
    AudioEventRTS *audioEventRTS = (AudioEventRTS *)event;
    if ((audioEventRTS->m_info->m_type & 8) || audioEventRTS->m_info->m_priority == 4 || audioEventRTS->m_info->m_at1C >= m_audioSettings->m_minSampleVolume)
        return true;
    return false;
}


extern const float BfmeZeroRange;  // data-ledger zero at VA 0x00BBAEAC

// These two rowed volume helpers must be visible together. Read the referent
// explicitly after each call: this preserves native reloads without binding a
// pointer-reference local that makes the caller's PlayingAudioRef escape.
class Rva001D990C
{
public:
	bool rva001D990C(int v);
};
__declspec(noinline) inline float MilesAudioManager::rva0005A9F8(void *ref, int a, int b)
{
	AudioEventRTS *event = (*(PlayingAudio **)ref)->m_event.get();
	float volume = rva00059AD0(event, a);
	if (b == 1)
		volume *= ((Rva0005117B *)this)->rva0005117B((*(PlayingAudio **)ref)->m_at30);

	event = (*(PlayingAudio **)ref)->m_event.get();
	if (event->m_at52 && volume < 0.01f && event->m_info != 0
		&& !((Rva001D990C *)event->m_info)->rva001D990C(2))
		volume = 0.01f;
	return volume;
}

extern "C" __declspec(dllimport) void __stdcall AIL_sample_volume_pan(void *, float *, float *);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_volume_pan(void *, float, float);
__declspec(noinline) inline void MilesAudioManager::adjustPlayingVolume(void *ref)
{
	float volume = rva0005A9F8(ref, 1, 1);
	PlayingAudio *playing = *(PlayingAudio **)ref;
	int type = playing->m_type;
	if (type == 0 || type == 1)
	{
		void *sample = get2DSampleHandleForPlayingAudio(ref);
		float pan;
		AIL_sample_volume_pan(sample, 0, &pan);
		AIL_set_sample_volume_pan(sample, volume, pan);
	}
	else if (type == 2 || type == 3)
	{
		void *sample3D = get3DSampleHandleForPlayingAudio(*(PlayingAudioRef *)ref);
		if (sample3D != 0)
			AIL_set_3D_sample_volume(sample3D, volume);
	}
	else if (type == 4)
	{
		((Rva000A8AEE *)&playing->m_at0C)->rva000A8AEE(volume);
	}
	(*(PlayingAudio **)ref)->m_at4F = 0;
}

// Retail 0x0005C23C (WorldBuilder twin 0x007A14A0, unnamed; Zero Hour's
// processPlayingList is the semantic guide): every playing 2D sound, 3D
// sound and stream applies pending pauses, fades and volume changes and
// leaves its list once stopped or finished; the 3D pass also moves its
// sample. The first two music streams of the current view type are handed
// back in streams, the rest of it filled with the stream list's end.
void MilesAudioManager::processPlayingList(Rva00052B3D *streams)
{
    PlayingAudioRef playing;
    OpaqueRefList::iterator it;

    it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        PlayingAudio *audio = playing.get();
        if (!audio) {
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
            continue;
        }
        if (m_viewTypeChanged || (audio->m_at4C && !m_at6AC)) {
            ((Rva000535CC *)this)->rva000535CC(&playing);
            rva000535A6(playing);
            pauseResumeSound(playing);
        }
        if (((Rva002DA318 *)audio->m_event.operator->())->rva002DA318())
            audio->m_event->m_at4C = true;
        if (audio->m_event->m_at4C && (audio->m_event->m_info->m_control & 0x10))
            audio->m_at44 = true;
        bool fading = processFade(playing);
        bool done = audio->m_at30 >= (float)m_audioSettings->m_timeToFadeAudio && !audio->m_pushedTrackResumed && !audio->m_fadeUpFromShroud;
        if (done && audio->m_at48) {
            if (audio->m_event->hasMoreLoops())
                rva0005AA72(playing);
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
        } else if (audio->m_status == 1 || done) {
            AIL_stop_sample(get2DSampleHandleForPlayingAudio(&playing));
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
        } else {
            if (reinterpret_cast<GlobalVolumeData *>(&m_volumeData[audio->m_event->getViewType()])->rva000520F4(*reinterpret_cast<const AudioEventInfoRef *>(&audio->m_event->m_info), 0)
                || m_viewTypeChanged || fading || audio->m_at4F)
                adjustPlayingVolume(&playing);
            if (m_at6A8)
                rva00052FA0(playing);
            ++it;
        }
    }

    it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        PlayingAudio *audio = playing.get();
        if (!audio) {
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
            continue;
        }
        if (m_viewTypeChanged || (audio->m_at4C && !m_at6AC)) {
            ((Rva000535CC *)this)->rva000535CC(&playing);
            rva000535A6(playing);
            pauseResumeSound(playing);
        }
        if (((Rva002DA318 *)audio->m_event.operator->())->rva002DA318())
            audio->m_event->m_at4C = true;
        if (audio->m_event->m_at4C && (audio->m_event->m_info->m_control & 0x10))
            audio->m_at44 = true;
        processFade(playing);
        bool done = audio->m_at30 >= (float)m_audioSettings->m_timeToFadeAudio && !audio->m_pushedTrackResumed && !audio->m_fadeUpFromShroud;
        void *sample3D = get3DSampleHandleForPlayingAudio(playing);
        if (done && audio->m_at48) {
            if (audio->m_event->hasMoreLoops())
                rva0005AA72(playing);
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
        } else if (audio->m_status == 1 || done) {
            if (sample3D)
                AIL_stop_3D_sample(sample3D);
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
        } else if (!sample3D) {
            ++it;
        } else {
            bool valid;
            BfmeEventPositionView pos = Rva0005160FGet(audio->m_event.operator->(), valid);
            if (valid) {
            if (slot108(reinterpret_cast<BfmeAudioEventPrefix136 *>(audio->m_event.operator->()))) {
                audio->m_at46 = true;
                audio->m_fadeUpFromShroud = false;
            } else if (audio->m_at46) {
                audio->m_at46 = false;
                audio->m_fadeUpFromShroud = true;
            }
            float volume = rva0005A9F8(&playing, 0, 0);
            AudioEventRTS *event = audio->m_event.operator->();
            unsigned char audible = (unsigned char)rva00052F1E(event);
            if (m_audioSettings->m_minSampleVolume > volume && !audible) {
                if (event->hasMoreLoops())
                    rva0005AA72(playing);
                AIL_register_3D_EOS_callback(sample3D, 0);
                it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
                continue;
            }
            setOcclusionLevels(playing, reinterpret_cast<const Coord3D *>(&pos));
            bool retest = false;
            if (m_areasNeedRetest && audio->m_event->m_info->m_reverbWetLevel > BfmeZeroRange)
                rva00055C5D(playing, &retest);
            if (m_at6A8 || retest)
                rva00052FA0(playing);
            float level = rva0005A9F8(&playing, 1, 1);
            AIL_set_3D_position(sample3D, pos.x, pos.y, -pos.z);
            AIL_set_3D_sample_volume(sample3D, level);
            ++it;
            } else {
                if (audio->m_event->hasMoreLoops())
                    rva0005AA72(playing);
                AIL_register_3D_EOS_callback(sample3D, 0);
                it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
            }
        }
    }

    OpaqueRefList::iterator *found = reinterpret_cast<OpaqueRefList::iterator *>(streams);
    int count = 0;
    OpaqueRefList &list = reinterpret_cast<OpaqueRefList &>(m_playingStreams);
    it = list.begin();
    while (it != list.end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        PlayingAudio *audio = playing.get();
        if (!audio) {
            it = list.erase(it);
            continue;
        }
        if (m_viewTypeChanged || (audio->m_at4C && !m_at6AC)) {
            ((Rva000535CC *)this)->rva000535CC(&playing);
            rva000535A6(playing);
            pauseResumeSound(playing);
        }
        if (((Rva002DA318 *)audio->m_event.operator->())->rva002DA318())
            audio->m_event->m_at4C = true;
        if (audio->m_event->m_info->m_atB0 == 3) {
            if (audio->m_event->m_viewType == m_at678)
                found[count++] = it;
            ++it;
            continue;
        }
        if (audio->m_event->m_at4C) {
            if (audio->m_event->m_info->m_control & 0x10)
                audio->m_at44 = true;
            else
                audio->m_status = 1;
        }
        bool fading = processFade(playing);
        bool done = audio->m_at30 >= (float)m_audioSettings->m_timeToFadeAudio && !audio->m_pushedTrackResumed && !audio->m_fadeUpFromShroud;
        if (done && audio->m_at48) {
            if (audio->m_event->hasMoreLoops())
                rva0005AA72(playing);
            ((MilesStreamRef *)&audio->m_at0C)->rva000A8AC0();
            it = list.erase(it);
        } else if (audio->m_status == 1 || done) {
            ((MilesStreamRef *)&audio->m_at0C)->rva000A8AC0();
            it = list.erase(it);
        } else {
            if (m_at6A8)
                rva00052FA0(playing);
            if (reinterpret_cast<GlobalVolumeData *>(&m_volumeData[audio->m_event->getViewType()])->rva000520F4(*reinterpret_cast<const AudioEventInfoRef *>(&audio->m_event->m_info), 0)
                || fading || m_viewTypeChanged || audio->m_at4F)
                adjustPlayingVolume(&playing);
            ++it;
        }
    }
    for (; count < 2; ++count)
        found[count] = list.end();
}

// Native 593CD..5952D, RET8; WorldBuilder 785D00 names this method.
// The matched alias operations independently establish the tables at +104/+118.
// Keep the real insert/erase template chains visible: the returned iterators
// and key pairs can then share their native stack homes across insert calls.
void MilesAudioManager::mapLogicalHandleToPhysicalHandle(unsigned int logical, unsigned int physical)
{
    if (physical < 5)
        return;
    MilesKeyAliases::iterator it = m_handleAliases.find(physical);
    if (it != m_handleAliases.end()) {
        MilesKeyAliases::iterator first = it;
        _STL::list<int> children;
        do {
            children.push_back(it->second);
            ++it;
        } while (it != m_handleAliases.end() && it->first == physical);
        m_handleAliases.erase(first, it);
        for (_STL::list<int>::iterator child = children.begin(); child != children.end(); ++child) {
            unsigned key = *child;
            m_handleAliases.insert(MilesKeyAliases::value_type(logical, key));
            MilesPhysicalHandles::iterator p = m_physicalHandles.find(key);
            if (p == m_physicalHandles.end())
                m_physicalHandles.insert(MilesPhysicalHandles::value_type(key, logical));
            else
                p->second = logical;
        }
    } else {
        m_handleAliases.insert(MilesKeyAliases::value_type(logical, physical));
        m_physicalHandles.insert(MilesPhysicalHandles::value_type(physical, logical));
    }
}

// ??1MilesAudioManager@@UAE@XZ @0x00060FE2 967B (native 0x00060FE2..
// 0x000613A9; WB 0x00780FC0 names it). Zero Hour's ~MilesAudioManager is the
// semantic guide: stop the loop-buffer thread, close the device, clear
// TheAudio, drain the completed list and both request containers, then free
// the loop buffers, the file cache, the misc record and the settings.
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long ms);
MilesAudioManager::~MilesAudioManager()
{
    m_stopLoopBufferThread = true;
    if (m_audioFileCache)
        m_audioFileCache->rva000A77B3();
    if (m_atB90)
        reinterpret_cast<Rva00A897D *>((void *)m_atB90)->rva000A89C1();
    if (m_loopBufferThread) {
        WaitForSingleObject(m_loopBufferThread, (unsigned long)-1);
        m_loopBufferThread = 0;
    }
    rva0006047C();
    if (TheAudio == this)
        TheAudio = 0;
    m_completedAudio.clear();
    while (!m_audioRequests.empty()) {
        Rva00051107AudioRequest *request = m_audioRequests.back();
        m_audioRequests.pop_back();
        deleteAudioRequest(request);
    }
    Rva00051107AudioRequestSet::iterator it = m_requestSet.begin();
    while (it != m_requestSet.end()) {
        Rva00051107AudioRequest *request = *it;
        m_requestSet.erase(it);
        it = m_requestSet.begin();
        deleteAudioRequest(request);
    }
    m_numLoopBuffers = 0;
    delete[] m_loopBuffers;
    delete m_audioFileCache;
    if (m_at14) {
        delete m_at14;
        m_at14 = 0;
    }
    if (m_audioSettings) {
        ::delete reinterpret_cast<Rva000416E7 *>(m_audioSettings);
        m_audioSettings = 0;
    }
    if (m_subTitleWindow) {
        delete m_subTitleWindow;
        m_subTitleWindow = 0;
    }
}

// Retail 0x00055E6C (350 B, RET 0x10): is a stream named `name` already playing for (viewType, musicSystem)?
// WorldBuilder 0x00798510 gives both walks: the playing-stream list (info type 0, view, music system, event
// name, then the +0xC handle test) and the music stack deque of that view/system (same tests without the
// music-system compare). The second walk's handle call keeps the event pointer live through an equal-arm
// conditional, which reproduces retail's register choice for the stack end pointer (lea esi,[eax+0x10])
// and emits no code of its own.
static __forceinline bool rva00055E6CNameMatches(AudioEventRTS *event, const AsciiString &name)
{
    const AsciiString *eventName = reinterpret_cast<const AsciiString *>(reinterpret_cast<Rva002D9AC3 *>(event)->rva002D9AC3());
    return eventName->compare(name) == 0;
}

bool MilesAudioManager::rva00055E6C(const AsciiString &name, int streamArg, int viewType, int musicSystem)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    for (PlayingAudioList::iterator it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        playing = *it;
        if (playing.get() && playing->m_event->m_info->m_atB0 == 0 && playing->m_event->m_viewType == viewType
            && playing->m_event->m_musicSystem == musicSystem
            && rva00055E6CNameMatches(playing->m_event.get(), name)
            && reinterpret_cast<Rva000A8B59 *>(&playing->m_at0C)->rva000A8B59(streamArg))
            return true;
    }
    MusicStack &stack = m_musicStack[viewType][musicSystem];
    for (MusicStack::iterator music = stack.begin(); music != stack.end(); ++music) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
        if (playing.get() && playing->m_event->m_info->m_atB0 == 0 && playing->m_event->m_viewType == viewType
            && rva00055E6CNameMatches(playing->m_event.get(), name)
            && reinterpret_cast<Rva000A8B59 *>((playing->m_event.get() ? &playing->m_at0C : &playing->m_at0C))->rva000A8B59(streamArg))
            return true;
    }
    return false;
}


// 0x0005AC80 (vtable 0x007C55B0 slot 73): the counted event-info handle for a name,
// registering a new 0xC4-byte info (Rva001DA2D5) when the map at +0xBC has no usable entry.
// The return uses the existing four-byte Rva0010F149Handle view: native return-slot
// cleanup 0x0075DBAF calls the null-checked destructor 0x0010F149. Its copy and raw
// construction share the existing counted-handle providers; original types remain unknown.

namespace _STL {
// Use the existing clear provider for checked element teardown.
template <> void vector<Rva0036CA00Str, allocator<Rva0036CA00Str> >::_M_clear();
template <> __declspec(noinline) inline void vector<Rva0036CA00Str, allocator<Rva0036CA00Str> >::push_back(const Rva0036CA00Str &value)
{
    if (this->_M_finish != this->_M_end_of_storage._M_data) {
        _Construct(this->_M_finish, value);
        ++this->_M_finish;
    } else {
        _M_insert_overflow(this->_M_finish, value, __false_type(), 1, true);
    }
}
}

class Rva001DA2D5 { char native[0xc4]; public: Rva001DA2D5(); };
struct AudioInfoNode { void *next; AsciiString key; AudioEventInfo *info; };

Rva0010F149Handle MilesAudioManager::newOwnedAudioEventInfo(const AsciiString &name, int context)
{
    MilesMutexGuard guard(&m_mutex, 0);
    {
        Rva0041534BIter found = reinterpret_cast<Rva00056F61 *>(&m_allAudioEventInfo)->rva0041534B(&name);
        if (found.m_node && reinterpret_cast<OpaqueRefCounted *>(static_cast<AudioInfoNode *>(found.m_node)->info)->rva00050EFA()) {
            AudioEventInfoRef result(static_cast<AudioInfoNode *>(found.m_node)->info);
            reinterpret_cast<OpaqueRefCounted *>(result.get())->Release_Ref();
            return *reinterpret_cast<const Rva0010F149Handle *>(&result);
        }
    }
    {
        m_at6A4 = false;
        AudioEventInfoRef temp(reinterpret_cast<AudioEventInfo *>(new Rva001DA2D5));
        reinterpret_cast<_STL::vector<Rva0036CA00Str> &>(m_atD4).push_back(*reinterpret_cast<const Rva0036CA00Str *>(&temp));
        AudioEventInfo *ownedInfo = temp.get();
        m_allAudioEventInfo.rva00059FBB(name) = ownedInfo;
        return Rva0010F149Handle(m_allAudioEventInfo.rva00059FBB(name));
    }
}

struct QueuedStopEvent {char at00[0x8C];bool m_at8C;};
// Native5FA3C..5FDC8 RET4; BF1 f989 rva006AFD00 is the primary clean
// stop-chain donor. BFME2 adds the independently measured +80 stop holds
// and queued-event +8C expiry request; all state collections are owned.
// Loop 1 has WorldBuilder 0x792D90's shape (if (hold <= 0) {...} else return;
// break;). Its found block reaches the event through two equal views of the
// stream (the smart pointer and a raw copy): with one view cl 7.1 hoists
// &audio->m_event into a register for the three loads, which retail does not.
void MilesAudioManager::rva0005FA3C(unsigned int handle)
{
 if(handle<5)return;
 {
 for(PlayingAudioList::iterator it=m_playingStreams.begin();it!=m_playingStreams.end();++it) {
  PlayingAudioRef audio=*it;
  if(!audio.get())continue;
  if(audio->m_event->m_playingHandle==handle) {
   PlayingAudio *playing=audio.get();
   --audio->m_event->m_at80;
   if(playing->m_event->m_at80<=0) {
    audio->m_event->m_at4C=true;
    if(!(playing->m_event->m_info->m_control&0x10))processAudioCompletion(audio);
   } else {
    return;
   }
   break;
  }
 }
 }
 for(PlayingAudioList::iterator it=m_playingSounds.begin();it!=m_playingSounds.end();++it) {
  PlayingAudioRef audio=*it;
  if(!audio.get())continue;
  if(audio->m_event->m_playingHandle==handle) {
   --audio->m_event->m_at80;
   if(audio->m_event->m_at80>0)return;
   audio->m_event->m_at4C=true;
   break;
  }
 }
 for(PlayingAudioList::iterator it=m_playing3DSounds.begin();it!=m_playing3DSounds.end();++it) {
  PlayingAudioRef audio=*it;
  if(!audio.get())continue;
  if(audio->m_event->m_playingHandle==handle) {
   --audio->m_event->m_at80;
   if(audio->m_event->m_at80>0)return;
   audio->m_event->m_at4C=true;
   break;
  }
 }
 for(int i=0;i<3;++i) {
  for(QueuedAudioEvents::iterator it=m_queuedEvents[i].begin();it!=m_queuedEvents[i].end();++it) {
   if(it->m_playingHandle==handle) {
    AudioEventRTS *event=reinterpret_cast<AudioEventRTS *>(it);
    if(--event->m_at80>0)return;
    reinterpret_cast<QueuedStopEvent *>(event)->m_at8C=true;
    break;
   }
  }
  PlayingAudioRef &music=m_playingMusic[i];
  if(music.get()&&music->m_event->m_playingHandle==handle) {
   --music->m_event->m_at80;
   if(music->m_event->m_at80>0)return;
   reinterpret_cast<Rva000A8C9B *>(&music)->clear();
  }
  for(int j=0;j<2;++j) {
   MusicStack &stack=m_musicStack[i][j];
   for(MusicStack::iterator it=stack.begin();it!=stack.end();++it) {
    PlayingAudioRef &audio=reinterpret_cast<PlayingAudioRef &>(*it);
    if(audio.get()&&audio->m_event->m_playingHandle==handle) {
     --audio->m_event->m_at80;
     if(audio->m_event->m_at80>0)return;
     stack.erase(it);break;
    }
   }
  }
 }
 {
  MilesAudioRequestTable::iterator found=reinterpret_cast<Rva00055951 &>(m_requestSet).rva00055951(handle);
  if(found._M_cur) {
   Rva00051107AudioRequest *request = *reinterpret_cast<Rva00051107AudioRequestSet::iterator &>(found);
   --request->m_pendingEvent->m_at80;
   if(request->m_pendingEvent->m_at80>0)return;
   MilesAudioRequestTable::iterator copy=found;
   reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(reinterpret_cast<Rva00051B89KeyedSet::iterator &>(copy));
   deleteAudioRequest(request);
  }
 }
 for(Rva00051107AudioRequestList::iterator it=m_audioRequests.begin();it!=m_audioRequests.end();) {
  Rva00051107AudioRequest *request=*it;
  if(request&&request->m_request==0) {
   bool matches;
   if(request->m_pendingEvent.get())matches=request->m_pendingEvent->m_playingHandle==handle;
   else matches=request->m_at08==handle;
   if(matches) {
    if(request->m_pendingEvent.get())--request->m_pendingEvent->m_at80;
    if(request->m_pendingEvent.get()&&request->m_pendingEvent->m_at80>0)return;
    deleteAudioRequest(request);
    it=m_audioRequests.erase(it);continue;
   }
  }
  ++it;
 }
}

class __declspec(novtable) Rva00A86CE
{
public:
    virtual ~Rva00A86CE();
    int m_04;
    unsigned int m_08;
    int m_0C;
    int m_10;
    int m_14;
};

class __declspec(novtable) Rva000A8684 : public Rva00A86CE
{
public:
    Rva000A8684();
};

__declspec(noinline) inline MilesAudioRequestTable::iterator Rva00055951::rva00055951(unsigned int handle)
{
    Rva000A8684 request;
    request.m_08 = handle;
    return reinterpret_cast<MilesAudioRequestTable *>(this)->find(reinterpret_cast<Rva00051107AudioRequest *>(&request));
}

// model=gpt-6.1-sol; restores the request lookup and removes the extra volatile read.
// See reverse/attempt_support/miles-stop-5fa3c-20261019.md for the remaining +0xBD mismatch.

// RVA 0x0005BE59: view-scoped audio volume refresh. WB supports function-scope
// pan and inline getViewType accesses; both source details preserve retail allocation.
void MilesAudioManager::rva0005BE59(void *slot, float value, void *index)
{
    const AsciiString &eventName = *reinterpret_cast<const AsciiString *>(slot);
    int viewType = reinterpret_cast<int>(index);
    float pan;
    PlayingAudioRef playing;
    PlayingAudioList::iterator it;
    for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
        playing = *it;
        if (playing.get()
            && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
                || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
            && playing->m_event->getViewType() == viewType) {
            void *sample = get2DSampleHandleForPlayingAudio(&playing);
            if (sample) {
                rva000592B8(playing->m_event.get());
                float volume = rva0005A9F8(&playing, 1, 1);
                AIL_sample_volume_pan(sample, 0, &pan);
                AIL_set_sample_volume_pan(sample, volume, pan);
            }
        }
    }
    for (PlayingAudioList::iterator it3D = m_playing3DSounds.begin(); it3D != m_playing3DSounds.end(); ++it3D) {
        playing = *it3D;
        if (playing.get()
            && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
                || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)) {
            AudioEventRTS *event = playing->m_event.get();
            if (event->getViewType() == viewType) {
                void *sample3D = get3DSampleHandleForPlayingAudio(playing);
                if (sample3D) {
                    rva000592B8(event);
                    AIL_set_3D_sample_volume(sample3D, rva0005A9F8(&playing, 1, 1));
                }
            }
        }
    }
    for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        playing = *it;
        if (playing.get()
            && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
                || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
            && playing->m_event->getViewType() == viewType
            && playing->m_event->m_info->m_atB0 != 3) {
            rva000592B8(playing->m_event.get());
            ((Rva000A8AEE *)&playing->m_at0C)->rva000A8AEE(rva0005A9F8(&playing, 1, 1));
        }
    }
    for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
        MusicStack &stack = m_musicStack[viewType][musicSystem];
        for (MusicStack::iterator music = stack.begin(), end = stack.end(); music != end; ++music) {
            playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
            if (playing.get()
                && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
                    || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
                && playing->m_event->getViewType() == viewType)
                rva000592B8(playing->m_event.get());
        }
    }
    QueuedAudioEvents::iterator queuedEnd = m_queuedEvents[viewType].end();
    for (QueuedAudioEvents::iterator event = m_queuedEvents[viewType].begin(); event != queuedEnd; ++event) {
        if (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
            || reinterpret_cast<const BfmeAudioEventInfoNameView *>(event->m_info)->getEventName() == eventName)
            rva000592B8(playing->m_event.get());
    }
}
