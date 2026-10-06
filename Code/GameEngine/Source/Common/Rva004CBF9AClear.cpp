// cl: /MD
//
// ?clear@Rva004CBF9A@@QAEXXZ, RVA 0x004CBF9A, 45 bytes.
// Opaque audio+holder clear: if TheAudio (data 0x009FE6E8) is present and the
// +0x14 handle is >= 5, calls AudioManager slot 0x6c (removeAudioEvent,
// precedent CastleMemberBehaviorDtor/FoundationAIUpdateSlot14) with the
// handle, resets it to 1 (AHSV_NoSound), then tail-calls the rowed
// ?clear@Rva000A8C9B@@QAEXXZ (0x000A8C9B) on the +0x18 holder. Callers are
// 0x004CBFFA (referent-change arm of FUN_008cbfc7) and 0x004CC12A (dtor-like
// FUN_008cc0fe); TheAudio extern idiom copied from FoundationAIUpdateSlot14.

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

class Rva000A8C9B
{
public:
    void clear();
};

class Rva004CBF9A
{
public:
    void clear();

private:
    char m_pad[0x14];
    unsigned int m_handle14;
    Rva000A8C9B m_holder18;
};

void Rva004CBF9A::clear()
{
    if (TheAudio != 0 && m_handle14 >= 5)
    {
        TheAudio->removeAudioEvent(m_handle14);
        m_handle14 = 1;
        m_holder18.clear();
    }
}
