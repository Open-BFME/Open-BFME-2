// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1Rva0060237D@@UAE@XZ @0x0060237D 68B evidence: vtable VA 0x0087A7B8 at +0; delete[] at +0x14 via 0x0002FD80; StringBase char releaseBuffer at +0x24 via 0x00036410; base File dtor via 0x006025CE row; unblocks deleting dtor 0x006023F6

#include <new>

typedef void *FileHandle;

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"


#include "../../../Include/Common/File.h"

class Rva0060237D : public File
{
public:
	virtual ~Rva0060237D();
private:
	char *m_14;
	char m_pad18[0x0C];
	AsciiString m_24;
};

Rva0060237D::~Rva0060237D()
{
	delete[] m_14;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot03@File@@UAEXXZ=?write@RAMFile@@UAEHPBXH@Z")
#pragma comment(linker, "/alternatename:?slot05@File@@UAEXXZ=?seek@MemoryReadFile@@UAEHHW4seekMode@File@@@Z")
#pragma comment(linker, "/alternatename:?slot10@File@@UAEXXZ=?print@File@@UAA_NPBDZZ")
#pragma comment(linker, "/alternatename:?slot11@File@@UAEXXZ=?get@Rva002A79A1DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?slot12@File@@UAEXXZ=?getData@NetWrapperCommandMsg@@QAEPAEXZ")
#pragma comment(linker, "/alternatename:?slot13@File@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot04@File@@UAEXXZ=?write@MemoryWriteFile@@UAEHPBXH@Z")
#pragma comment(linker, "/alternatename:?slot06@File@@UAEXXZ=?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")
#pragma comment(linker, "/alternatename:?slot07@File@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?slot08@File@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?slot09@File@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?slot14@File@@UAEXXZ=??0RealRange@@QAE@XZ")
