// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// ?Rva0037BCC4Create@@YAPAVRva0037BBED@@XZ @0x0037BCC4 53B
// Evidence: leaf lane; allocates 0xE7C via rowed ??2 0x0002FDA0 then pinned
// ctor 0x0037BB98 with null check and EH prolog; caller 0x0022F6A1 unclaimed;
// class layout copied from Rva0037BBEDDtor.cpp so sizeof is 0xE7C.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva0037BB53
{
public:
    Rva0037BB53();
    virtual ~Rva0037BB53();
    char m_pad[0xE3C - 4];
};

class GameEngineDeletingBase
{
public:
    GameEngineDeletingBase();
    virtual ~GameEngineDeletingBase();
    int m_pad04;
    int m_pad08;
};

class Rva0037BBED : public GameEngineDeletingBase
{
public:
    Rva0037BBED();
    virtual ~Rva0037BBED();
    virtual void rva0037B326();
private:
    int m_0c;
    void *m_10;
    UnicodeString m_14;
    int m_18;
    int m_1c;
    UnicodeString m_20;
    Rva0037BB53 m_24;
    // Retail new pushes 0xE7C; the constructor explicitly clears the final +0xE78 word.
    int m_e60, m_e64, m_e68, m_e6c;
    unsigned char m_e70;
    char m_padE71[3];
    int m_e74;
    int m_frameE78;
};

Rva0037BBED *Rva0037BCC4Create()
{
    return new Rva0037BBED;
}

// Native Ghidra extent 0x0037BB98..0x0037BBED, 85 bytes, thiscall RET 0.
// The existing allocator and destructor establish this receiver and vtable.
// Two default UnicodeStrings and the +0x24 GameInfo-shaped member explain
// EH states 0..3; native calls identify its constructor and the reset worker.
// The ZH Recorder constructor has the same member/reset relationship; target
// offsets and the final +0xE78 clear are taken from retail rather than the donor.
Rva0037BBED::Rva0037BBED()
{
    m_frameE78 = 0;
    rva0037B326();
}

// Native Ghidra extent 0x0037B326..0x0037B3D1, 171 bytes, thiscall RET 0.
// The recorder vtable at VA 0x00C18828 places this method in slot 1.
// ZH Recorder::init supplies the clear/reset/map/seed sequence; retail proves
// every receiver/global offset and the additional CRC/analysis state stores.
// Separate setMap calls preserve retail's two by-value argument temporaries.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern int NET_CRC_INTERVAL;
unsigned int GetGameLogicRandomSeed();
class GameInfo {
public:
 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
 virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
 virtual void reset();
 void clearSlotList(); void setMap(AsciiString s); void setSeed(int);
 char opaque04[0x34];
};

struct RecorderGlobalView {
    char opaque00[0x0C];
    AsciiString map0C;
    char opaque10[0xAC0-0x10];
    AsciiString pendingAC0;
};
void Rva0037BBED::rva0037B326()
{
	m_10 = 0;
	m_e74 = 9;
	m_1c = 2;
	m_14.clear();
	m_18 = 0;
	GameInfo *gi = reinterpret_cast<GameInfo *>(&m_24);
	gi->clearSlotList();
	gi->reset();
	const RecorderGlobalView *wd = reinterpret_cast<const RecorderGlobalView *>(TheWritableGlobalData);
	if (((const StringBase<char> &)wd->pendingAC0).isEmpty())
		gi->setMap(wd->map0C);
	else
		gi->setMap(wd->pendingAC0);
	gi->setSeed(GetGameLogicRandomSeed());
	m_e64 = -1;
	m_e60 = NET_CRC_INTERVAL;
	m_e68 = 0;
	m_e6c = -1;
	m_e70 = 0;
}
