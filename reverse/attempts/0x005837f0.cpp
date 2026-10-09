// ?rva005837F0@HordeMeleeHoldGround@@QAEXPAVXfer@@@Z
// partial score=0.99 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
#include "ascii_string.h"
class Xfer;
class HordeMeleeHoldGround
{
public:
    void rva005837F0(Xfer *xfer);
};
struct XferVersion
{
    unsigned char version;
    unsigned char current;
};
class Xfer
{
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7(); virtual void slot8();
    virtual void slot9();
    virtual Xfer &xferVersion(XferVersion *version);
    virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16();
    virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22();
    virtual void slot23(); virtual void slot24(); virtual void slot25();
    virtual void slot26();
    virtual Xfer &slot27(AsciiString *name);
};
class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &other);
    ~XferException();
    char *text;
    int tag;
};
static __forceinline const char *TransferHordeVersion(Xfer *xfer, XferVersion &version)
{
    version.version = 1;
    version.current = 1;
    xfer->xferVersion(&version);
    return "HordeMeleeHoldGround";
}
struct HordeTransferHeader
{
    XferVersion version;
    AsciiString expected;
    __forceinline HordeTransferHeader(Xfer *xfer) : expected(TransferHordeVersion(xfer, version)) {}
    __forceinline ~HordeTransferHeader() {}
};
void HordeMeleeHoldGround::rva005837F0(Xfer *xfer)
{
    HordeTransferHeader header(xfer);
    AsciiString actual(header.expected);
    xfer->slot27(&actual);
    if (actual.compare(header.expected) != 0)
        throw XferException(4, "Xfer data saved by %s is now being loaded by %s", actual.str(), header.expected.str());
}
