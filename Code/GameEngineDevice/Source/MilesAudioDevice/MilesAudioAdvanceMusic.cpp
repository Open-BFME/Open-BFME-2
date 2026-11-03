// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/GameEngine/Include /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// Native 0x0005BBE2..0x0005BD20, RET4; WB 0x00798170 supplies the
// music-track advance/previous flow. The retail vtable and accesses establish
// the manager receiver and +0x678 view, +0x9D4 lock, +0xA48 stream list, and
// +0xB3C active systems. Field names follow the rowed MilesAudioManager home.
// The string precedes the null owning reference in WB; retail EH state 2
// retains that reference at -0x18. The mutable iterator return is converted
// to a const iterator, leaving its return temporary separate from the live node.
// PlayingAudio +0x1C and event +0x0C are independently used by matched music
// workers in MilesAudioManager.cpp. Callee names remain the established ledger
// spellings; the event prefix uses its canonical header.

#include <list>
#include "Common/BfmeAudioEventPrefix136.h"

// Keep the node comparison local rather than emitting the conflicting
// out-of-line list-base comparison alongside the already inlined loop test.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

struct AudioEventRTS { char head[0xC]; int m_playingHandle; };
struct PlayingEventRef { AudioEventRTS *m_ptr; AudioEventRTS *get() const { return m_ptr; } AudioEventRTS *operator->() const { return m_ptr; } };
struct PlayingAudio { char head[0x1C]; PlayingEventRef m_event; };
class PlayingAudioRef { public: PlayingAudio *m_ptr; PlayingAudio *operator->() const { return m_ptr; } };
typedef _STL::list<PlayingAudioRef> PlayingAudioList;
#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"
class Rva002D9AC3 { public: const char *rva002D9AC3(); };
struct AudioEventInfoRef {
    OpaqueRefCounted *m_ptr;
    AudioEventInfoRef() : m_ptr(0) {}
    ~AudioEventInfoRef() { if (m_ptr) m_ptr->Release_Ref(); }
};

class MilesAudioManager {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
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
    virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
    virtual void slot26();
    virtual void removeAudioEvent(int handle);
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
    virtual void slot56();
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
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &name);
    PlayingAudioList::iterator rva0005442A(int viewType, int musicSystem, int filter);
    AsciiString rva0005B19E(const AsciiString &key);
    AsciiString rva0005B1FA(const AsciiString &key);
    void rva0005BBE2(int previous);
    char at04[0x678 - 4];
    int m_viewType;
    char at67C[0x9d4 - 0x67c];
    void *m_mutex;
    char at9D8[0xa48 - 0x9d8];
    PlayingAudioList m_playingStreams;
    char atA4C[0xb3c - 0xa4c];
    int m_activeMusicSystem[3];
};

void MilesAudioManager::rva0005BBE2(int previous)
{
    MilesAudioManager *mgr = this;
    MilesMutexGuard guard(&mgr->m_mutex, 0);
    AsciiString trackName;
    AudioEventInfoRef unused;
    int handle = 1;
    PlayingAudioList::const_iterator it = mgr->rva0005442A(mgr->m_viewType, mgr->m_activeMusicSystem[mgr->m_viewType], 1);
    if (it != mgr->m_playingStreams.end()) {
        trackName = *reinterpret_cast<const AsciiString *>(reinterpret_cast<Rva002D9AC3 *>((*it)->m_event.get())->rva002D9AC3());
        handle = (*it)->m_event->m_playingHandle;
    }
    mgr->removeAudioEvent(handle);
    if (previous == 0)
        trackName = mgr->rva0005B19E(trackName);
    else
        trackName = mgr->rva0005B1FA(trackName);
    AudioEventInfoRef info = mgr->findAudioEventInfo(trackName);
    BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4 *>(&info), mgr->m_viewType);
    mgr->addAudioEvent(&event);
}
