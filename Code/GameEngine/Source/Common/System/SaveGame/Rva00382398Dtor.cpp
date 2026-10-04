// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// ??1Rva00382398@@UAE@XZ, retail 0x00382398, 119 bytes.
// Virtual dtor (novtable suppresses its own vptr store) over
// BfmeSaveElement002295D7 base (0x1AC) with five narrow
// StringBase members at +0x1b0/+0x1b4/+0x1b8/+0x1d8/+0x1dc destroyed in
// reverse with EH states 4..0 then the rowed base dtor. Identity from caller
// 0x003831EB (28B deleting dtor calling it then operator delete) and the
// five releaseBuffer calls plus base dtor row.
#include "ascii_string.h"
#include "unicode_string.h"
class Xfer;
class Snapshot {
public:
    __forceinline virtual ~Snapshot() {}
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
class CreateAHeroData : public Snapshot {
    unsigned char fields[0x13C];
public:
    CreateAHeroData(const CreateAHeroData &);
    virtual ~CreateAHeroData();
};
struct BfmeSaveElement002295D7 : Snapshot {
    BfmeSaveElement002295D7();
    virtual ~BfmeSaveElement002295D7();
    unsigned int word04;
    unsigned char flag08, flag09, flag0A;
    unsigned int word0C, word10, word14, word18, word1C, word20, word24, word28, word2C;
    UnicodeString text30;
    AsciiString text34;
    unsigned int word38, word3C, word40, word44;
    unsigned char flag48;
    unsigned int word4C, word50, word54, word58, word5C;
    unsigned char flag60;
    CreateAHeroData hero64;
    unsigned char flag1A4;
    AsciiString text1A8;
};
class __declspec(novtable) Rva00382398 : public BfmeSaveElement002295D7
{
public:
    ~Rva00382398();
private:
    char m_pad1AC[0x1b0 - 0x1ac];
    AsciiString m_1b0;
    AsciiString m_1b4;
    AsciiString m_1b8;
    char m_pad1BC[0x1d8 - 0x1bc];
    AsciiString m_1d8;
    AsciiString m_1dc;
};
inline Rva00382398::~Rva00382398()
{
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva00382398DtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeRva00382398DtorInlineAnchor()
{
    static_cast<Rva00382398 *>(0)->Rva00382398::~Rva00382398();
}
#pragma inline_depth()
