// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva0033FF2B@@UAE@XZ, retail 0x0033FF2B, 75 bytes.
// Dtor restoring vtable 0x00810DE8, then if TheAudio (data 0x009FE6E8) is
// present and the +0x40 handle is >= 5 calls AudioManager slot 0x6c
// (removeAudioEvent, precedent CastleMemberBehaviorDtor/AudioLoopUpgradeDtor
// plus Rva004CBF9AClear >=5 check) with the handle (state 0), then calls the
// fold base at 0x0049B47C via the Rva0049B47C pin (packet annotates the
// WindModuleInfo row at the same fold address; honest unknown base per
// CastleMember/AnimationSound precedent). Callers are the five derived dtors
// 0x00340BDC/0x00340D1F/0x0034280A-family plus 0x00345CAB/0x00345F21 which call
// here as base; deleting dtor is 0x0034280A/28 plus thunk 0x00368793.

typedef unsigned int AudioHandle;

class AudioManager
{
public:
    virtual void _pad00() = 0;
    virtual void _pad01() = 0;
    virtual void _pad02() = 0;
    virtual void _pad03() = 0;
    virtual void _pad04() = 0;
    virtual void _pad05() = 0;
    virtual void _pad06() = 0;
    virtual void _pad07() = 0;
    virtual void _pad08() = 0;
    virtual void _pad09() = 0;
    virtual void _pad10() = 0;
    virtual void _pad11() = 0;
    virtual void _pad12() = 0;
    virtual void _pad13() = 0;
    virtual void _pad14() = 0;
    virtual void _pad15() = 0;
    virtual void _pad16() = 0;
    virtual void _pad17() = 0;
    virtual void _pad18() = 0;
    virtual void _pad19() = 0;
    virtual void _pad20() = 0;
    virtual void _pad21() = 0;
    virtual void _pad22() = 0;
    virtual void _pad23() = 0;
    virtual void _pad24() = 0;
    virtual void _pad25() = 0;
    virtual void _pad26() = 0;
    virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

class Rva0049B47C
{
public:
    virtual ~Rva0049B47C();

private:
    char m_pad04[8];
};

class Rva0033FF2B : public Rva0049B47C
{
public:
    virtual ~Rva0033FF2B();

private:
    char m_pad0C[0x40 - 0x0C];
    unsigned int m_handle40;
};

Rva0033FF2B::~Rva0033FF2B()
{
    if (TheAudio != 0 && m_handle40 >= 5)
        TheAudio->removeAudioEvent(m_handle40);
}
