// FILE: MilesAudioManager.h /////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 MilesAudioManager, the Miles Sound System AudioManager.
//
// Target facts (code addresses are RVAs, table addresses VAs):
//  - Identity: the Snapshot name slot 0x000518B2 returns the string "MilesAudioManager"
//    (VA 0x00BC5300). Win32GameEngine's factory 0x0005E959 pushes 0xC08 to operator new
//    (0x0005E964) and calls the constructor 0x0005CF5F (0x0005E97D): sizeof 0xC08.
//  - Constructor 0x0005CF5F calls AudioManager's 0x0005107D (0x0005CF74), then stores the
//    primary table 0x00BC55B0 at +0 (0x0005CF84) and the Snapshot table 0x00BC559C at +0xC
//    (0x0005CF8A). Destructor 0x00060FE2 stores the same two tables (0x00060FF6, 0x00060FFC)
//    and ends in AudioManager's destructor 0x0005109D (0x00061396). Constructor and destructor
//    agree; AudioManager's own tables 0x00BC5148/0x00BC5138 appear only inside its bodies.
//  - 0x00BC55B0 has 111 slots: AudioManager's 105 and six new ones (105..110, rowed below).
//    Slot 0 is the scalar deleting destructor 0x00061AA1. Of SubsystemInterface's slots this
//    class overrides 1 init 0x00061ABD, 4 vslot04 0x00061BD2, 5 vslot05 0x00051155, 9 reset
//    0x00051173 and 10 update 0x00062690; 2, 3, 6, 7, 8, 11, 12 and 13 equal AudioManager's.
//    Every slot 14..104 (pure in AudioManager) is overridden; each declaration below keeps the
//    parent's spelling and names the retail target and the ledger row there. Slots 72, 77, 78,
//    79 and 104 hold folded bodies: 0x0036CBE7 `lea eax,[ecx+18h]`, 0x001DB09D
//    `mov eax,[ecx+10h]`, 0x0057E556 `mov eax,[ecx+14h]` (78 and 79) and 0x000B3FD0 `ret`.
//  - 0x00BC559C (Snapshot at +0xC): thunk 0x0005D41D (sub ecx,0Ch), loadPostProcess
//    0x000587C6, the name getter 0x000518B2 (rowed as the non-virtual name()), xfer 0x0005E3E5.
//  - Data from the constructor's stores and member constructor calls: +0x10 and +0x14 receive
//    new 0x204 (0x00041589) and new 0xF4 (0x001ED70C) objects (0x0005D3BB, 0x0005D3E0); +0x18
//    is zeroed and +0x24 set to (0, 1.0, 0) like Zero Hour's listener position and
//    orientation; +0x3C ScreenToTerrainSet (0x00052751, five 0x10 elements in the destructor);
//    +0x98/+0xA38..+0xA48/+0xB94 lists, +0x9C/+0x104/+0x118/+0x9E8/+0xB78/+0xB98/+0xBAC/+0xBC0
//    hash tables, +0xB0 set<AsciiString>, +0xD4/+0x9FC/+0xA08/+0xB54/+0xB60 vectors, +0xB6C map,
//    +0xE0 three 0xC records, +0x12C three 0x1C4 GlobalVolumeData, +0x6CC 64 0xC provider
//    records, +0x9D4 Mutex (0x00040F1E), +0xA14 three sets, +0xA4C six 0x28 music stacks,
//    +0xB48 three 4-byte refs; scalar stores give +0x678..+0x6B0, +0x9CC..+0x9E4 and
//    +0xB8C..+0xC00. +0xBF8 takes _time64's EDX:EAX (0x0005D350).
//  - Field evidence: 0x0005125D loads +0x94 with the unsigned fild correction (0x00051267);
//    0x0005178D (initDelayFilter) stores +0x9E4; 0x00051782 stores the
//    provider count +0x9CC; 0x000533C1 resets +0x9D0 to -1; 0x000616F2 passes &+0x9DC to
//    AIL_quick_handles; 0x000533A2 closes the +0x9E0 listener; the destructor deletes +0xBD4
//    through LoopBuffer's 0x0005277C, +0xB8C through ~AudioFileCache (0x00061105) and +0xBE8
//    through ~SubTitleWindow (0x00061151). Provider records are 0xC apart (0x00060584) with
//    the AsciiString at +0 (0x00051774) and the handle at +4 (0x00060587).
// Donor (Zero Hour MilesAudioManager.h, GameAudio.h) facts: the names m_audioSettings,
// m_miscAudio, m_listenerPosition, m_listenerOrientation, ProviderInfo, m_provider3D,
// m_providerCount, m_selectedProvider, m_digitalHandle, m_listener, m_delayFilter,
// m_audioCache, m_availableSamples and m_available3DSamples. initSamplePools 0x00056746 and
// init3DSamplePools 0x000566B6 append to +0xA38 and +0xA3C through the rowed list<int>
// push_back 0x0005548F; 0x000544EB, 0x0005456B, 0x0005452B and 0x00054596 erase from them
// through the rowed list<int> erase 0x00438539. Other members keep their offset as a neutral
// name. Members whose types have no shared header (the other STLport containers,
// ScreenToTerrainSet, GlobalVolumeData, Mutex, the +0xB90 device reference, the +0xB48 refs)
// stay opaque byte spans of the retail size.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_MILESAUDIOMANAGER_H
#define BFME2_MILESAUDIOMANAGER_H

#include "../../../GameEngine/Include/Common/GameAudio.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class UnicodeString;
class AudioEventRTS;
class PlayingAudioRef;
struct PlayingAudio;
class INI;
class ScreenToTerrainSet;
class AudioFileContainer;
class AudioFileCache;
class SubTitleWindow;
class Rva00052B3D;
struct Rva00051107AudioRequest;
struct BfmeEventPositionView;
struct Rva0010FFA2Packet;
struct Rva0005BA08InfoRef;
struct Rva0005A084Element;
enum ObjectID;
enum MusicSystem;
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
template <class T> struct _Nonconst_traits;
template <class T, class Traits> struct _List_iterator;
}

struct ProviderInfo
{
    AsciiString name;
    unsigned int id;
    bool m_isValid;
};

class MilesAudioManager : public AudioManager
{
public:
    struct LoopBuffer;
    class GlobalVolumeData;

    MilesAudioManager();
    virtual ~MilesAudioManager();

    virtual void init();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual void reset();
    virtual void update();

    virtual void slot14(); // 14: 0x00061C87 rva00061C87
    virtual void stopAudio(AudioAffect affect); // 15: 0x00054284 stopAudio
    virtual void slot16(); // 16: 0x000583BA rva000583BA
    virtual void slot17(); // 17: 0x00058591 rva00058591
    virtual void slot18(); // 18: 0x0005CAE2 rva0005CAE2
    virtual void slot19(); // 19: 0x0005CB39 rva0005CB39
    virtual void setViewFocus(int viewType); // 20: 0x0005DAFC setViewFocus
    virtual void slot21(); // 21: 0x0005189D rva0005189D
    virtual void slot22(); // 22: 0x0005116B rva0005116B
    virtual void slot23(); // 23: 0x0005DACF rva0005DACF
    virtual void slot24(); // 24: 0x0005DACF rva0005DACF
    virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event); // 25: 0x0005DABB addAudioEvent
    virtual void slot26(); // 26: 0x000609A1 removePlayingAudio
    virtual void removeAudioEvent(unsigned int handle); // 27: 0x00057787 rva00057787
    virtual bool killAudioEventImmediately(unsigned int handle); // 28: 0x000615DA killAudioEventImmediately
    virtual void slot29(); // 29: 0x0005DAE6 resumeAudioEvent
    virtual void slot30(); // 30: 0x00057408 rva00057408
    virtual bool isValidAudioEvent(const BfmeAudioEventPrefix136 *event) const; // 31: 0x000527E2 rva000527E2
    virtual void slot32(); // 32: 0x00055E6C rva00055E6C
    virtual void slot33(); // 33: 0x0005A7BE rva0005A7BE
    virtual void slot34(); // 34: 0x00055A58 rva00055A58
    virtual void slot35(); // 35: 0x00055B40 rva00055B40
    virtual void slot36(); // 36: 0x000568CE rva000568CE
    virtual void slot37(); // 37: 0x000569A8 rva000569A8
    virtual void slot38(); // 38: 0x000567F4 rva000567F4
    virtual void slot39(); // 39: 0x000518A4 rva000518A4
    virtual void slot40(); // 40: 0x00052917 rva00052917
    virtual void slot41(); // 41: 0x0005538C rva0005538C
    virtual void slot42(); // 42: 0x00054714 rva00054714
    virtual void slot43(); // 43: 0x0005BD20 rva0005BD20
    virtual void slot44(); // 44: 0x0005BD28 rva0005BD28
    virtual void slot45(); // 45: 0x0005E322 rva0005E322
    virtual void slot46(); // 46: 0x00059DF5 rva00059DF5
    virtual void slot47(); // 47: 0x00059E5C rva00059E5C
    virtual void slot48(); // 48: 0x0005CA03 rva0005CA03
    virtual void slot49(); // 49: 0x0005E377 rva0005E377
    virtual void slot50(); // 50: 0x0005CA75 rva0005CA75
    virtual void slot51(); // 51: 0x0005A95B rva0005A95B
    virtual bool isCurrentlyPlaying(unsigned int handle); // 52: 0x000572DC rva000572DC
    virtual void slot53(); // 53: 0x00057378 rva00057378
    virtual void slot54(); // 54: 0x00057492 rva00057492
    virtual void slot55(); // 55: 0x00057530 rva00057530
    virtual void slot56(); // 56: 0x0005164F rva0005164F
    virtual void setOn(bool turnOn, int whichToAffect); // 57: 0x0005168C rva0005168C
    virtual void slot58(); // 58: 0x0005CB90 rva0005CB90
    virtual void slot59(); // 59: 0x00053CE1 rva00053CE1
    virtual void setVolume(float volume, int whichToAffect); // 60: 0x0005C8BB rva0005C8BB
    virtual void slot61(); // 61: 0x000537F4 rva000537F4
    virtual void slot62(); // 62: 0x00059A25 rva00059A25
    virtual void slot63(); // 63: 0x0005E168 rva0005E168
    virtual void slot64(); // 64: 0x00059A7C rva00059A7C
    virtual void slot65(); // 65: 0x000515AB rva000515AB
    virtual void slot66(); // 66: 0x000515B3 rva000515B3
    virtual void slot67(); // 67: 0x000533CB rva000533CB
    virtual void slot68(); // 68: 0x000515A4 rva000515A4
    virtual void slot69(); // 69: 0x000517F1 rva000517F1
    virtual void slot70(); // 70: 0x0005181B rva0005181B
    virtual void slot71(); // 71: 0x00051840 rva00051840
    virtual void slot72(); // 72: 0x0036CBE7
    virtual void slot73(); // 73: 0x0005AC80 newOwnedAudioEventInfo
    virtual void slot74(); // 74: 0x0005ADA3 addUnownedAudioEventInfo
    virtual void slot75(); // 75: 0x00059EAE findAudioEventInfo
    virtual void slot76(); // 76: 0x0005AF92 friend_onAudioEventInfoDestruction
    virtual const AudioSettings *getAudioSettings() const { return m_audioSettings; } // 77: 0x001DB09D
    virtual const MiscAudio *getMiscAudio() const { return m_miscAudio; } // 78: 0x0057E556
    virtual void slot79(); // 79: 0x0057E556
    virtual void slot80(); // 80: 0x000549A3 getAudioLengthMS
    virtual void slot81(); // 81: 0x00051846 bfmeMilesPreferenceProduct
    virtual void slot82(); // 82: 0x0005185E rva0005185E
    virtual bool isMusicAlreadyLoaded() const; // 83: 0x0005B017 isMusicAlreadyLoaded
    virtual void slot84(); // 84: 0x00051896 rva00051896
    virtual void slot85(); // 85: 0x0005AE2B rva0005AE2B
    virtual void slot86(); // 86: 0x0005AEDD rva0005AEDD
    virtual void slot87(); // 87: 0x0055D96F rva0055D96F
    virtual void xferAudioHandle(Xfer *xfer, unsigned int *handle); // 88: 0x000596E9 rva000596E9
    virtual void slot89(); // 89: 0x0005522C rva0005522C
    virtual void slot90(); // 90: 0x00054243 rva00054243
    virtual void slot91(); // 91: 0x000530DF rva000530DF
    virtual void slot92(); // 92: 0x00058314 rva00058314
    virtual void slot93(); // 93: 0x0005824D rva0005824D
    virtual void slot94(); // 94: 0x000551C2 rva000551C2
    virtual void slot95(); // 95: 0x0005710F rva0005710F
    virtual void slot96(); // 96: 0x000512BC rva000512BC
    virtual void slot97(); // 97: 0x000619D1 rva000619D1
    virtual void onAudioLODChanged(); // 98: 0x000607BB onAudioLODChanged
    virtual bool slot99(); // 99: 0x000531F6 rva000531F6
    virtual void slot100(); // 100: 0x000514BB rva000514BB
    virtual void slot101(); // 101: 0x00053281 rva00053281
    virtual void slot102(); // 102: 0x0005329C rva0005329C
    virtual void friend_xferSubAudioEventRTS(Xfer *xfer, BfmePoolRef10 *eventRef); // 103: 0x0005987D friend_xferSubAudioEventRTS
    virtual void slot104() {} // 104: 0x000B3FD0

    virtual void rva000511C3(Coord3D *); // 105: 0x000511C3
    virtual void getScreenToTerrainPositions(ScreenToTerrainSet *); // 106: 0x0005294A
    virtual bool rva000516EF(const Coord3D *); // 107: 0x000516EF
    virtual unsigned char slot108(BfmeAudioEventPrefix136 *); // 108: 0x000527FB
    virtual float rva0005121F(); // 109: 0x0005121F
    virtual void rva000541DB(); // 110: 0x000541DB

    Rva00051107AudioRequest *rva00051107(); // 0x00051107
    void internalSetReverbRoomType(int); // 0x000512C4
    void rva00051353(const UnicodeString &); // 0x00051353
    void notifyOf2DSampleCompletion(); // 0x000514EB
    void notifyOf3DSampleCompletion(); // 0x000514FB
    bool shouldUseDolbyProvider(); // 0x00051525
    void setMaxAmbientStreams(); // 0x00051565
    BfmeEventPositionView Rva0005160FGet(AudioEventRTS *, bool &); // 0x0005160F
    const char *name() const; // 0x000518B2
    void *get3DSampleHandleForPlayingAudio(PlayingAudioRef &); // 0x00052662
    void *get2DSampleHandleForPlayingAudio(void *); // 0x00052696
    void getAppropriateSampleHandleForPlayingAudio(PlayingAudioRef &, void **, void **); // 0x000526C5
    void deleteAudioRequest(void *); // 0x000527C7
    BfmePoolRef10 rva0005286A(AudioEventRTS *, int); // 0x0005286A
    void recalculateMicrophone(); // 0x00052B53
    int rva00052F1E(void *); // 0x00052F1E
    float getGlobalReverbMultiplier(); // 0x00052F4C
    void rva00052FA0(PlayingAudioRef &); // 0x00052FA0
    void pauseResumeSound(PlayingAudioRef &); // 0x00053113
    PlayingAudioRef allocatePlayingAudio(); // 0x0005320F
    int rva000532B7(Xfer *); // 0x000532B7
    bool processFade(PlayingAudioRef &); // 0x00053448
    void rva000535A6(PlayingAudioRef &); // 0x000535A6
    bool rva00053606(Rva00051107AudioRequest *); // 0x00053606
    void rva00053646(Rva00051107AudioRequest *, bool *); // 0x00053646
    float rva00053854(const Coord3D *); // 0x00053854
    float rva00053A1F(void *); // 0x00053A1F
    void rva00053AFA(void *); // 0x00053AFA
    void createListener(); // 0x00053B63
    bool shouldPlayLocally(const AudioEventRTS *); // 0x00053BA1
    void rva0005407E(INI *); // 0x0005407E
    void rva000540A7(INI *); // 0x000540A7
    unsigned char rva00054120(INI *); // 0x00054120
    _STL::_List_iterator<PlayingAudioRef,_STL::_Nonconst_traits<PlayingAudioRef> > rva0005442A(int, int, int); // 0x0005442A
    _STL::_List_iterator<PlayingAudioRef,_STL::_Nonconst_traits<PlayingAudioRef> > rva000544CB(int, int, int); // 0x000544CB
    void rva000544EB(); // 0x000544EB
    void rva0005452B(); // 0x0005452B
    int rva0005456B(); // 0x0005456B
    int rva00054596(); // 0x00054596
    void setOcclusionLevels(PlayingAudioRef &, const Coord3D *); // 0x000545C1
    AsciiString getProviderName(unsigned int) const; // 0x000547F3
    bool rva00054839(AudioEventRTS *); // 0x00054839
    bool rva00054899(ObjectID, int); // 0x00054899
    // Called directly (0x00054A16, 0x00054A32, 0x00054A4E); no table holds 0x0005492A.
    float getFileLengthMS(AsciiString) const; // 0x0005492A
    void removeCurrentlyPlayingMusic(int, int); // 0x000552C5
    bool rva00055426(int); // 0x00055426
    bool addAudioEventMusic(BfmePoolRef10 &, int, int); // 0x000559D0
    void rva00055C5D(PlayingAudioRef &, bool *); // 0x00055C5D
    bool rva00055FCA(int, void **, PlayingAudioRef *); // 0x00055FCA
    bool rva0005623E(int, void **, int); // 0x0005623E
    void rva000562A2(int, const void *); // 0x000562A2
    void rva000562CF(int); // 0x000562CF
    bool rva000562FA(int, BfmeEventPositionView *); // 0x000562FA
    void rva0005634C(int, float, int); // 0x0005634C
    void rva000563FE(Xfer *, int); // 0x000563FE
    void rva000564C0(unsigned int); // 0x000564C0
    void rva0005653C(unsigned int); // 0x0005653C
    void rva000565B8(unsigned int); // 0x000565B8
    unsigned int getProviderIndex(const AsciiString &) const; // 0x00056634
    bool rva00056670(ObjectID); // 0x00056670
    void init3DSamplePools(); // 0x000566B6
    void rva000567C5(unsigned int); // 0x000567C5
    void removeAllAudioRequests(unsigned int); // 0x00056FD9
    bool rva000570C8(AudioEventRTS *); // 0x000570C8
    void moveDownMusicSystems(int, MusicSystem, int, int); // 0x000571D0
    void processPopMusicRequest(Rva00051107AudioRequest *); // 0x00057232
    void rva00057297(Rva00051107AudioRequest &); // 0x00057297
    bool rva000575CE(AudioEventRTS *); // 0x000575CE
    void rva0005774F(int, int, int); // 0x0005774F
    void rva000577E3(unsigned int, unsigned int, bool); // 0x000577E3
    void unmapPhysicalHandle(unsigned int); // 0x000578B3
    void rva00057948(const void *); // 0x00057948
    void rva000581FA(const Rva0005BA08InfoRef &, int); // 0x000581FA
    void rva0005876E(int, int, int, int); // 0x0005876E
    void rva000592B8(AudioEventRTS *); // 0x000592B8
    unsigned int rva0005933D(AudioEventRTS *, int); // 0x0005933D
    void mapLogicalHandleToPhysicalHandle(unsigned int, unsigned int); // 0x000593CD
    int pushMusicEventInternal(AudioEventRTS *, int, int, int); // 0x0005952D
    bool rva006AD9B0(); // 0x00059646
    float rva00059AD0(void *, int); // 0x00059AD0
    void rva00059CE6(PlayingAudioRef &); // 0x00059CE6
    bool startNextLoop(PlayingAudioRef &); // 0x00059DAB
    int addResumeOrPushMultisound(AudioEventRTS *, int, int, int, int, int); // 0x0005A451
    void putPlayingMusicOnStack(int, int); // 0x0005A812
    void moveUpMusicSystems(int, int, int); // 0x0005A908
    void rva0005A92A(int, _STL::vector<Rva0005A084Element,_STL::allocator<Rva0005A084Element> > *); // 0x0005A92A
    float rva0005A9F8(void *, int, int); // 0x0005A9F8
    void rva0005AA72(PlayingAudioRef &); // 0x0005AA72
    void playAndStoreStream(PlayingAudioRef &, const Rva0010FFA2Packet *); // 0x0005AADD
    void rva0005AC61(int, int, int); // 0x0005AC61
    void rva0005B137(); // 0x0005B137
    AsciiString rva0005B19E(const AsciiString &); // 0x0005B19E
    AsciiString rva0005B1FA(const AsciiString &); // 0x0005B1FA
    void rva0005B256(Xfer *, PlayingAudioRef &, int *); // 0x0005B256
    void rva0005B708(); // 0x0005B708
    void adjustPlayingVolume(void *); // 0x0005B96D
    void prepSample(void *); // 0x0005BA08
    void initFilters3D(PlayingAudioRef &, const Coord3D *); // 0x0005BB52
    void rva0005BBE2(int); // 0x0005BBE2
    AudioEventRTS *findLowestPrioritySound(AudioEventRTS *); // 0x0005BD30
    bool isPlayingLowerPriority(AudioEventRTS *); // 0x0005BDD2
    void rva0005BE59(void *, float, void *); // 0x0005BE59
    void startPendingMusicTracks(); // 0x0005C16E
    void processPlayingList(Rva00052B3D *); // 0x0005C23C
    void prep3DSample(PlayingAudioRef &, const Coord3D *); // 0x0005C931
    bool addAudioEventSound(BfmePoolRef10 &, int, int); // 0x0005D57B
    unsigned int addOrResumeAudioEvent(AudioEventRTS *, int, int, int, int); // 0x0005D734
    void rva0005DB6C(const AsciiString &); // 0x0005DB6C
    void processPushMusicRequest(Rva00051107AudioRequest *); // 0x0005DBFD
    void checkForNaturalSoundCompletion(PlayingAudioRef &); // 0x0005DD40
    void processAudioCompletion(PlayingAudioRef &); // 0x0005DF9D
    void rva0005E0A4(); // 0x0005E0A4
    bool playSample(PlayingAudioRef &); // 0x0005E1BF
    bool playSample3D(PlayingAudioRef &); // 0x0005E24E
    void putFileIntoLoopBuffer(MilesAudioManager::LoopBuffer *, const AudioFileContainer &, int); // 0x0005E98E
    void cleanUpLoopBuffer(MilesAudioManager::LoopBuffer *); // 0x0005EA8F
    void transferBytesToPlayBuffer(MilesAudioManager::LoopBuffer &, unsigned int); // 0x0005EC7A
    void rva0005EFE9(); // 0x0005EFE9
    void processAmbientStreams(_STL::_List_iterator<PlayingAudioRef,_STL::_Nonconst_traits<PlayingAudioRef> > *); // 0x0005F2BB
    void rva0005FA3C(unsigned int); // 0x0005FA3C
    void releaseMilesHandles(PlayingAudio &); // 0x0005FDCA
    void onPlayingAudioDeleted(PlayingAudio &); // 0x000600BA
    void rva00060123(unsigned int); // 0x00060123
    void rva00060309(); // 0x00060309
    void rva000603ED(); // 0x000603ED
    void rva0006047C(); // 0x0006047C
    void rva000606CE(bool); // 0x000606CE
    bool killLowestPrioritySoundImmediately(AudioEventRTS *); // 0x00060869
    bool playSample2DOr3DUsingCallbackBuffers(PlayingAudioRef &, void *, void *); // 0x00060D0D
    bool rva000613A9(unsigned int); // 0x000613A9
    void openDevice(); // 0x00061680
    void rva0006179C(int); // 0x0006179C
    bool rva00061A7D(PlayingAudioRef &, void *); // 0x00061A7D
    bool rva00061A8F(PlayingAudioRef &, void *); // 0x00061A8F
    void playAudioEvent(Rva00051107AudioRequest *); // 0x00061E37
    void processRequest(Rva00051107AudioRequest *, bool *); // 0x0006236D
    void processRequestList(); // 0x0006258D

protected:
    void initDelayFilter(); // 0x0005178D
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess(); // 0x000587C6
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *xfer);
#endif

public:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void DoXfer(Xfer *xfer);
#else
    virtual void xfer(Xfer *xfer); // 0x0005E3E5
#endif

private:
    void buildProviderList(); // 0x00051744
    void unselectProvider(); // 0x00053352
    void initSamplePools(); // 0x00056746
    void selectProvider(bool); // 0x000604A3

public:
    AudioSettings *m_audioSettings;          // +0x10
    MiscAudio *m_miscAudio;                  // +0x14
    Coord3D m_listenerPosition;              // +0x18
    Coord3D m_listenerOrientation;           // +0x24
    Coord3D m_30;                            // +0x30
    unsigned char m_3C[0x50];                // +0x3C ScreenToTerrainSet
    float m_8C;                              // +0x8C
    float m_90;                              // +0x90
    unsigned int m_94;                       // +0x94
    unsigned char m_98[0x4];                 // +0x98 list
    unsigned char m_9C[0x14];                // +0x9C hash table
    unsigned char m_B0[0xC];                 // +0xB0 set<AsciiString>
    unsigned char m_BC[0x14];                // +0xBC hash table
    unsigned int m_D0;                       // +0xD0
    unsigned char m_D4[0xC];                 // +0xD4 vector
    unsigned char m_E0[0x24];                // +0xE0 three 0xC records
    unsigned char m_104[0x14];               // +0x104 hash table
    unsigned char m_118[0x14];               // +0x118 hash table
    unsigned char m_12C[0x54C];              // +0x12C three GlobalVolumeData
    int m_678;                               // +0x678
    unsigned int m_67C;                      // +0x67C
    unsigned int m_680;                      // +0x680
    unsigned int m_684;                      // +0x684
    unsigned int m_688;                      // +0x688
    unsigned int m_68C;                      // +0x68C
    unsigned int m_690;                      // +0x690
    unsigned int m_694;                      // +0x694
    unsigned int m_698;                      // +0x698
    unsigned short m_69C;                    // +0x69C
    bool m_69E;                              // +0x69E
    bool m_69F;                              // +0x69F
    bool m_6A0;                              // +0x6A0
    bool m_6A1;                              // +0x6A1
    bool m_6A2;                              // +0x6A2
    bool m_6A3;                              // +0x6A3
    bool m_6A4;                              // +0x6A4
    bool m_6A5;                              // +0x6A5
    bool m_6A6;                              // +0x6A6
    bool m_6A7;                              // +0x6A7
    bool m_6A8;                              // +0x6A8
    bool m_6A9;                              // +0x6A9
    bool m_6AA;                              // +0x6AA
    bool m_6AB;                              // +0x6AB
    bool m_6AC;                              // +0x6AC
    int m_6B0;                               // +0x6B0
    unsigned int m_6B4[3];                   // +0x6B4
    unsigned int m_6C0[3];                   // +0x6C0
    ProviderInfo m_provider3D[64];           // +0x6CC
    unsigned int m_providerCount;            // +0x9CC
    unsigned int m_selectedProvider;         // +0x9D0
    unsigned char m_9D4[0x8];                // +0x9D4 Mutex
    void *m_digitalHandle;                   // +0x9DC
    void *m_listener;                        // +0x9E0
    void *m_delayFilter;                     // +0x9E4
    unsigned char m_9E8[0x14];               // +0x9E8 hash table
    unsigned char m_9FC[0xC];                // +0x9FC vector
    unsigned char m_A08[0xC];                // +0xA08 vector
    unsigned char m_A14[0x24];               // +0xA14 three sets
    // STLport lists are typed where the unit included STLport's <list> first; elsewhere
    // the same bytes stay opaque, so non-STLport includers compile unchanged.
#ifdef _STLP_INTERNAL_LIST_H
    _STL::list<int> m_availableSamples;      // +0xA38
    _STL::list<int> m_available3DSamples;    // +0xA3C
#else
    unsigned char m_A38[0x4];                // +0xA38 list
    unsigned char m_A3C[0x4];                // +0xA3C list
#endif
    unsigned char m_A40[0x4];                // +0xA40 list
    unsigned char m_A44[0x4];                // +0xA44 list
    unsigned char m_A48[0x4];                // +0xA48 list
    unsigned char m_A4C[0xF0];               // +0xA4C six music stacks
    int m_B3C[3];                            // +0xB3C
    unsigned char m_B48[0xC];                // +0xB48 three refs
    unsigned char m_B54[0xC];                // +0xB54 vector
    unsigned char m_B60[0xC];                // +0xB60 vector
    unsigned char m_B6C[0xC];                // +0xB6C map
    unsigned char m_B78[0x14];               // +0xB78 hash table
    AudioFileCache *m_audioCache;            // +0xB8C
    unsigned char m_B90[0x4];                // +0xB90 device reference
    unsigned char m_B94[0x4];                // +0xB94 list
    unsigned char m_B98[0x14];               // +0xB98 hash table
    unsigned char m_BAC[0x14];               // +0xBAC hash table
    unsigned char m_BC0[0x14];               // +0xBC0 hash table
    LoopBuffer *m_BD4;                       // +0xBD4
    int m_BD8;                               // +0xBD8
    void *m_BDC;                             // +0xBDC
    bool m_BE0;                              // +0xBE0
    int m_BE4;                               // +0xBE4
    SubTitleWindow *m_BE8;                   // +0xBE8
    unsigned int m_BEC;                      // +0xBEC
    int m_BF0;                               // +0xBF0
    __int64 m_BF8;                           // +0xBF8
    bool m_C00;                              // +0xC00
};

#endif // BFME2_MILESAUDIOMANAGER_H
