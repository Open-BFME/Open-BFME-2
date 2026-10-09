// ?rva0005BBE2@Rva0005BBE2@@QAEXH@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
#include "Common/BfmeAudioEventPrefix136.h"

class PlayingAudioRef { public: OpaqueRefElement4 *m_unused; };
typedef _STL::list<PlayingAudioRef> PlayingAudioList;
class MilesMutexGuard {
public:
    MilesMutexGuard(void *, int);
    ~MilesMutexGuard();
private:
    void *mutex;
    bool held;
};
class Rva002D9AC3 { public: const char *rva002D9AC3(); };
struct AudioEventInfoRefView {
    OpaqueRefCounted *m_ptr;
    ~AudioEventInfoRefView() { if (m_ptr) m_ptr->Release_Ref(); }
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
    virtual AudioEventInfoRefView findAudioEventInfo(const AsciiString &name);
    PlayingAudioList::iterator rva0005442A(int viewType, int musicSystem, int filter);
    AsciiString rva0005B19E(const AsciiString &key);
    AsciiString rva0005B1FA(const AsciiString &key);
    char at04[0x678 - 4];
    int m_viewType;
    char at67C[0x9d4 - 0x67c];
    void *m_mutex;
    char at9D8[0xa48 - 0x9d8];
    PlayingAudioList m_playingStreams;
    char atA4C[0xb3c - 0xa4c];
    int m_activeMusicSystem[3];
};

class Rva0005BBE2 {
public:
    void rva0005BBE2(int previous);
};

void Rva0005BBE2::rva0005BBE2(int previous)
{
    MilesAudioManager *mgr = reinterpret_cast<MilesAudioManager *>(this);
    MilesMutexGuard guard(&mgr->m_mutex, 0);
    AsciiString trackName;
    int handle = 1;
    PlayingAudioList::iterator it = mgr->rva0005442A(mgr->m_viewType, mgr->m_activeMusicSystem[mgr->m_viewType], 1);
    if (it != mgr->m_playingStreams.end()) {
        char *playing = *reinterpret_cast<char **>(reinterpret_cast<char *>(it._M_node) + 8);
        char *event = *reinterpret_cast<char **>(playing + 0x1c);
        trackName = *reinterpret_cast<const AsciiString *>(reinterpret_cast<Rva002D9AC3 *>(event)->rva002D9AC3());
        handle = *reinterpret_cast<int *>(event + 0xc);
    }
    mgr->removeAudioEvent(handle);
    if (previous)
        trackName = mgr->rva0005B1FA(trackName);
    else
        trackName = mgr->rva0005B19E(trackName);
    AudioEventInfoRefView info = mgr->findAudioEventInfo(trackName);
    BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4 *>(&info), mgr->m_viewType);
    mgr->addAudioEvent(&event);
}
