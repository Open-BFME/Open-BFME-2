// cl: /DNDEBUG /MD /EHsc
// flags: GameEngine retail region default /O1 /arch:SSE /G7
// Target 0x0035BD5D/33B: Shell receiver corroborated by update and CreditsExit.
// Native TheAudio VA 0x00DFE6E8, handle Shell+0x68, virtual query slot 0xD0.
// Ghidra starts at 0x0035BD5D and ends at 0x0035BD7E; local false branches
// target 0x0035BD7B, which is inside this body. The next Shell::top starts
// at 0x0035BD7E. Rowed Shell::update and AptMainMenu::CreditsExit supply
// independent Shell-receiver call sites for the existing Bool member pin.
// Reference: BFME1 34f59164 inputs/reference/CnC_Generals_Zero_Hour/
// GeneralsMD GameAudio.h isCurrentlyPlaying(AudioHandle) is a semantic
// query lead only. Target slot52 remains opaque; no EA method name is claimed.
class AudioManager { public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void slot2() = 0;
    virtual void slot3() = 0;
    virtual void slot4() = 0;
    virtual void slot5() = 0;
    virtual void slot6() = 0;
    virtual void slot7() = 0;
    virtual void slot8() = 0;
    virtual void slot9() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual void slot48() = 0;
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual bool slot52(unsigned int handle) = 0;
};
extern AudioManager *TheAudio;
class Shell {
    unsigned char m_pad00[0x68];
    unsigned int m_musicHandle;
public:
    bool rva0035BD5D();
};
bool Shell::rva0035BD5D()
{
    return TheAudio != 0 && TheAudio->slot52(m_musicHandle);
}
