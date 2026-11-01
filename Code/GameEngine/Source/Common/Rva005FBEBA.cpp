// cl: /MD
// ?rva005FBEBA@Rva005FBEBA@@QAEXXZ @0x005FBEBA 30B: audio remove-event setter via TheAudio slot 0x6c plus handle at +0x24 reset to 1. Evidence: TheAudio plus removeAudioEvent precedent Rva004CBF9AClear plus 3 callers.
typedef unsigned int AudioHandle;
#include "../../Include/Common/GameAudio.h"
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
