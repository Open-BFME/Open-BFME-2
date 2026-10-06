// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?Rva00358A53Play@@YAXXZ @ 0x00358A53 120B
// Evidence: honest free-function name; TheAudio null gate plus getMiscAudio slot 0x138 null gate,
// then BfmeAudioEventPrefix136 event from Misc+0x80 with value30 0, posted via addAudioEvent slot 0x64.
// Slots match Player_Radar (addAudioEvent at 0x64, getMiscAudio at 0x138) and GameWindowCursorSearch
// Misc layout (element at +0x80 vs +0x88 there); callers at 0x003593E8/0x00359556.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

struct Rva00358A53MiscView
{
    char unknown[0x80];
    OpaqueRefElement4 field80;
};

class Rva00358A53AudioView
{
public:
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
    virtual const Rva00358A53MiscView *getMiscAudio();
};

void Rva00358A53Play()
{
    if (TheAudio == 0)
        return;
    if (reinterpret_cast<Rva00358A53AudioView *>(TheAudio)->getMiscAudio() == 0)
        return;
    BfmeAudioEventPrefix136 event(reinterpret_cast<Rva00358A53AudioView *>(TheAudio)->getMiscAudio()->field80, 0);
    reinterpret_cast<Rva00358A53AudioView *>(TheAudio)->addAudioEvent(&event);
}

struct Rva00358ACBMiscView
{
    char unknown[0x84];
    OpaqueRefElement4 field84;
};

class Rva00358ACBAudioView
{
public:
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
    virtual const Rva00358ACBMiscView *getMiscAudio();
};

void Rva00358ACBPlay()
{
    if (TheAudio == 0)
        return;
    if (reinterpret_cast<Rva00358ACBAudioView *>(TheAudio)->getMiscAudio() == 0)
        return;
    BfmeAudioEventPrefix136 event(reinterpret_cast<Rva00358ACBAudioView *>(TheAudio)->getMiscAudio()->field84, 0);
    reinterpret_cast<Rva00358ACBAudioView *>(TheAudio)->addAudioEvent(&event);
}
