// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
// Target 0x0006B804..0x0006B895, RET0. Same-this call to the
// established terrain texture method at 0x0006ACBD identifies the receiver.
// The second surface guard deliberately reloads the first pointer, as retail does.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"

class Rva000E6594 { public: void rva000E6594(); };
class Rva00073BFE { public: virtual ~Rva00073BFE(); };
class GlobalData;
extern GlobalData *TheWritableGlobalData;

class BaseHeightMapRenderObjClass {
    char pad[0x3820];
    AsciiString texture0;
    char pad3824[8];
    AsciiString texture1;
    char pad3830[4];
    bool textureFlag;
    char pad3835[0x3850 - 0x3835];
    Rva000E6594 *surface0;
    Rva000E6594 *surface1;
    char pad3858[0x387C - 0x3858];
    Rva00073BFE *resource;
public:
    void rva0006B804();
    void rva0006ACBD(AsciiString);
    void rva0006ABE7(AsciiString, bool);
};

void BaseHeightMapRenderObjClass::rva0006B804()
{
    if (surface0) surface0->rva000E6594();
    if (surface1) surface0->rva000E6594();
    reinterpret_cast<unsigned char *>(TheWritableGlobalData)[0xC6A] = 0;
    Rva00073BFE *oldResource = resource;
    if (oldResource) {
        oldResource->Rva00073BFE::~Rva00073BFE();
        operator delete(oldResource);
        resource = 0;
    }
    rva0006ACBD(texture0);
    rva0006ABE7(texture1, textureFlag);
}
