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

class Rva0037D097CRCView
{
public:
    void rva0037D097(unsigned int crc);
    unsigned int rva0037BD64();
};

class Rva0037B5DF;

class Rva0037BBED : public GameEngineDeletingBase
{
public:
    Rva0037BBED();
    virtual ~Rva0037BBED();
    virtual void rva0037B326();
    bool rva0037CBB6(Rva0037B5DF &header);
    bool rva0037D0EF(UnicodeString filename);
    void rva0037D0A7(unsigned int crc, int player, bool fromPlayback, unsigned int frame);
private:
    Rva0037D097CRCView *m_0c;
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

class GameLogic;
extern GameLogic *TheGameLogic;
class Rva00241529CRCView
{
public:
    void rva00241529(unsigned int crc, int player, unsigned int frame,
        void *message, bool forced, void *stream);
    char opaque00[0x71];
    bool crcProcessing71;
};

// Native Ghidra 0x0037D0A7..0x0037D0EF; 72 bytes; thiscall RET 16.
// Reference: BFME 1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/Common/System/RecorderHandleCRCMessage.cpp.
// The four argument roles and processing sequence follow that readable donor;
// retail proves +0xC receiver storage, +0x71 flag and all three call targets.
// Native rva0037BD64 already checks the queue before removing its front value.
// Its folded list wrappers are named opaquely here: the FXList ledger spelling
// at those addresses does not establish a recorder's CRC storage as FXList.
void Rva0037BBED::rva0037D0A7(unsigned int crc, int player, bool fromPlayback, unsigned int frame)
{
    if (fromPlayback)
        m_0c->rva0037D097(crc);
    m_0c->rva0037BD64();
    if (frame > 0)
    {
        Rva00241529CRCView *logic = reinterpret_cast<Rva00241529CRCView *>(TheGameLogic);
        if (!logic->crcProcessing71)
            logic->rva00241529(crc, player, frame, 0, false, 0);
    }
}

// Same 0x5C string-bearing header as the independently rowed destructor.
// Target accesses, not the donor layout, establish the six string offsets.
class Rva0037B5DF
{
public:
    ~Rva0037B5DF();
    char opaque00[0x20];
    AsciiString options20;
    int player24;
    UnicodeString filename28;
    bool forPlayback2C;
    char opaque2D[3];
    UnicodeString name30;
    char time34[0x10];
    UnicodeString version44;
    UnicodeString versionTime48;
    unsigned int iniCRC4C;
    char opaque50[8];
    UnicodeString string58;
};
// Target's 42B StringBase<unsigned short>::compare wrapper is nonthrowing:
// it forwards a string buffer/length to the native comparator at 0x000067B1.
// This opaque ABI view preserves the donor's throw() contract without changing
// the shared string header or asserting another real name on the folded RVA.
class Rva00006A7A
{
public:
    int rva00006A7A(const UnicodeString &that) const throw();
};
class Version
{
public:
    UnicodeString getFullUnicodeVersion();
    UnicodeString getUnicodeBuildTime();
};
extern Version *TheVersion;
struct RecorderCRCGlobalView
{
    char opaque00[0xB04];
    unsigned int iniCRCB04;
};

// Native Ghidra 0x0037D0EF..0x0037D1E6; 247 bytes; thiscall RET 4.
// ZH Recorder::testVersionPlayback and BFME1 1399ad37 RecorderReadReplayHeader
// supply the comparison sequence. Target uses a Unicode filename and omits
// the donor's version-number/executable checks. The destructor proves header
// storage; retail proves forPlayback+2C, version+44/+48, and CRC+4C/global+B04.
bool Rva0037BBED::rva0037D0EF(UnicodeString filename)
{
    Rva0037B5DF header;
    header.forPlayback2C = true;
    header.filename28 = filename;
    bool success = rva0037CBB6(header);
    if (!success)
        return false;
    bool versionStringDiff = reinterpret_cast<const Rva00006A7A *>(&header.version44)->rva00006A7A(TheVersion->getFullUnicodeVersion()) != 0;
    bool versionTimeStringDiff = reinterpret_cast<const Rva00006A7A *>(&header.versionTime48)->rva00006A7A(TheVersion->getUnicodeBuildTime()) != 0;
    bool exeDifferent = versionStringDiff || versionTimeStringDiff;
    bool iniDifferent = header.iniCRC4C != reinterpret_cast<const RecorderCRCGlobalView *>(TheWritableGlobalData)->iniCRCB04;
    if (exeDifferent || iniDifferent)
        return true;
    return false;
}
