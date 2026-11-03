// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// ??1Rva00382398@@UAE@XZ, retail 0x00382398, 119 bytes.
// Virtual dtor (novtable suppresses its own vptr store) over
// GameSlot base (0x1AC) with five narrow
// StringBase members at +0x1b0/+0x1b4/+0x1b8/+0x1d8/+0x1dc destroyed in
// reverse with EH states 4..0 then the rowed base dtor. Identity from caller
// 0x003831EB (28B deleting dtor calling it then operator delete) and the
// five releaseBuffer calls plus base dtor row.
#include "ascii_string.h"
#include "unicode_string.h"
class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/GameLogic/CreateAHeroData.h"
#include "../../../../Include/GameNetwork/GameInfo.h"
class __declspec(novtable) Rva00382398 : public GameSlot
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
