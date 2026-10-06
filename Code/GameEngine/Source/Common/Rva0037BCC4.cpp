// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// ?Rva0037BCC4Create@@YAPAVRva0037BBED@@XZ @0x0037BCC4 53B
// Evidence: leaf lane; allocates 0xE7C via rowed ??2 0x0002FDA0 then pinned
// ctor 0x0037BB98 with null check and EH prolog; caller 0x0022F6A1 unclaimed;
// class layout copied from Rva0037BBEDDtor.cpp so sizeof is 0xE7C.
#include "unicode_string.h"

class Rva0037BB53
{
public:
    virtual ~Rva0037BB53();
    char m_pad[0xE3C - 4];
};

class GameEngineDeletingBase
{
public:
    virtual ~GameEngineDeletingBase();
    int m_pad04;
    int m_pad08;
};

class Rva0037BBED : public GameEngineDeletingBase
{
public:
    Rva0037BBED();
    virtual ~Rva0037BBED();
private:
    int m_0c;
    void *m_10;
    UnicodeString m_14;
    int m_18;
    int m_1c;
    UnicodeString m_20;
    Rva0037BB53 m_24;
    // Retail new pushes 0xE7C; layout above emits 0xE60, so pad to 0xE7C.
    char m_padE60[0x1C];
};

Rva0037BBED *Rva0037BCC4Create()
{
    return new Rva0037BBED;
}
