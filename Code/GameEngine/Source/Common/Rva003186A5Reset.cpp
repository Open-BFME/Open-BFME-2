// cl: /MD /EHsc /Ireference/shims/bfme2_ascii /DWIN32 /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc/stl
// stlport
// Reconstruction of the reset-style body at 0x003186A5 (73B): zero the int
// fields, drop the audio handle through TheAudio slot 0x6c (removeAudioEvent,
// same idiom as Rva0033FF2BDtor), clear the +0x20 string to "", reseed the
// handle word, and zero the +0x58 word. All names are address-derived; the
// member offsets and the early-pushed handle are target facts.
#define _STLP_NO_EXCEPTIONS 1
#include <cstddef>
#include "_alloc.h"
#include <string.h>
#pragma function(memset)
#include "ascii_string.h"

typedef unsigned int AudioHandle;

#include "../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

class Rva003186A5Owner {
public:
    void reset();
private:
    unsigned char pad00[0x10];
    int m_10;
    AudioHandle m_audioHandle;
    int m_18;
    int m_1c;
    AsciiString m_str20;
    int m_24;
    int m_28;
    int m_2c;
    unsigned char pad30[0x58 - 0x30];
    int m_58;
};

void Rva003186A5Owner::reset()
{
    m_10 = 0;
    m_28 = 0;
    m_2c = 0;
    TheAudio->removeAudioEvent(m_audioHandle);
    m_audioHandle = 1;
    m_18 = 0;
    m_str20 = "";
    memset(&m_58, 0, 4);
    m_24 = 0;
}
