// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// Reference: GeneralsMD Common/RTS/Player.cpp through open-bfme-1 revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76. Radar count/disable-proof logic
// is reused; target proves +A0/+A4/+A8 and index+54. Event data is target's
// 136-byte prefix and MiscAudio references at +C/+10; original ref-field names
// follow donor semantics where caller behavior agrees. Native add/removal and
// enable/disable boundaries independently establish each member identity.
// Keep hasRadar in this unit: MSVC observes its ECX-preserving body and omits
// the reload before the edge predicate, as the native notification bodies do.
// The edge predicate's bool interface aliases the rowed normalized0/1 worker.
#include "Common/BfmeAudioEventPrefix136.h"
#pragma comment(linker, "/alternatename:?okToPlayRadarEdgeSound@Player@@QAE_NXZ=?rva002AA04C@Rva002AA04C@@QAEHXZ")
class AudioManager; extern AudioManager *TheAudio;

class Rva0033F15DDwordSlot { public: void set(int); char lead[0x6C]; int value; };
struct Rva002AA9C2MiscView { char unknown[0xC]; OpaqueRefElement4 radarOnline; OpaqueRefElement4 radarLost; };
class Rva002AA9C2AudioView { public:
    virtual void slot0();
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
    virtual void addAudioEvent(const BfmeAudioEventPrefix136 *);
    virtual void slot26();
    virtual void slot27();
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
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual const Rva002AA9C2MiscView *getMiscAudio();
};
class Player {
    char lead[0x54];
    int playerIndex;
    char mid[0xA0-0x58];
    int radarCount;
    int proofCount;
    unsigned char radarDisabled;
public:
    bool hasRadar() const;
    bool okToPlayRadarEdgeSound();
    void removeRadar(bool);
    void addRadar(bool);
    void disableRadar();
    void enableRadar();
};

bool Player::hasRadar() const
{
    if (radarDisabled && (proofCount == 0)) return false;
    return radarCount > 0;
}

// Native boundary2AA9C2-2AAA65.
void Player::removeRadar(bool disableProof)
{
    bool had = hasRadar();
    --radarCount;
    if (disableProof) --proofCount;
    if (had && !hasRadar() && okToPlayRadarEdgeSound()) {
        BfmeAudioEventPrefix136 event(reinterpret_cast<Rva002AA9C2AudioView *>(TheAudio)->getMiscAudio()->radarLost, 0);
        reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(playerIndex);
        reinterpret_cast<Rva002AA9C2AudioView *>(TheAudio)->addAudioEvent(&event);
    }
}

void Player::addRadar(bool disableProof)
{
    bool had = hasRadar();
    ++radarCount;
    if (disableProof) ++proofCount;
    if (!had && hasRadar() && okToPlayRadarEdgeSound()) {
        BfmeAudioEventPrefix136 event(reinterpret_cast<Rva002AA9C2AudioView *>(TheAudio)->getMiscAudio()->radarOnline, 0);
        reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(playerIndex);
        reinterpret_cast<Rva002AA9C2AudioView *>(TheAudio)->addAudioEvent(&event);
    }
}

void Player::disableRadar()
{
    bool had = hasRadar();
    radarDisabled=true;
    if (had && !hasRadar() && okToPlayRadarEdgeSound()) {
        BfmeAudioEventPrefix136 event(reinterpret_cast<Rva002AA9C2AudioView *>(TheAudio)->getMiscAudio()->radarLost, 0);
        reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(playerIndex);
        reinterpret_cast<Rva002AA9C2AudioView *>(TheAudio)->addAudioEvent(&event);
    }
}

void Player::enableRadar()
{
    bool had = hasRadar();
    radarDisabled=false;
    if (!had && hasRadar() && okToPlayRadarEdgeSound()) {
        BfmeAudioEventPrefix136 event(reinterpret_cast<Rva002AA9C2AudioView *>(TheAudio)->getMiscAudio()->radarOnline, 0);
        reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(playerIndex);
        reinterpret_cast<Rva002AA9C2AudioView *>(TheAudio)->addAudioEvent(&event);
    }
}
