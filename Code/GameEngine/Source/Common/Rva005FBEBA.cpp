// cl: /MD
// ?rva005FBEBA@Rva005FBEBA@@QAEXXZ @0x005FBEBA 30B: audio remove-event setter via TheAudio slot 0x6c plus handle at +0x24 reset to 1. Evidence: TheAudio plus removeAudioEvent precedent Rva004CBF9AClear plus 3 callers.
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
class Rva005FBEBA
{
public:
    void rva005FBEBA();
private:
    char m_pad[0x24];
    AudioHandle m_handle;
};
void Rva005FBEBA::rva005FBEBA()
{
    if (TheAudio == 0)
        return;
    TheAudio->removeAudioEvent(m_handle);
    m_handle = 1;
}
