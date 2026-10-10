// ??1Rva0007311B@@QAE@XZ
// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native7311B..731AE RET and wrapper66667..66683 establish opaque destructor relationship.
// Target-owned offsets: arrays18/38/3C; texture1C; flag34; counted ref40; member map4C.
// Nonvirtual ABI view avoids the unsupported multiple-inheritance/vptr model formerly used only by the wrapper.
#include "refcount.h"
class TextureClass {public:void Release_Ref();};
struct Rva0007311BTexture {TextureClass *ptr;~Rva0007311BTexture(){if(ptr)ptr->Release_Ref();}};
struct Rva0007311BRef {RefCountClass *ptr;~Rva0007311BRef(){if(ptr)ptr->Release_Ref();}};
struct Rva00072FE6 {~Rva00072FE6();char pad[0x18];};
class Rva000728E2 {public: void rva000728E2();};
class Rva0007311B {
public: ~Rva0007311B();void *rva00066667(unsigned flags);
private:
 char unknown00[0x18];
 char *p18;
 Rva0007311BTexture texture;
 char unknown20[0x34-0x20];
 bool b34;char unknown35[3];
 char *p38,*p3c;
 Rva0007311BRef object;
 char unknown44[8];
 Rva00072FE6 map;
};
Rva0007311B::~Rva0007311B()
{
 ((Rva000728E2*)this)->rva000728E2();
 if(p18)delete[] p18;p18=0;
 if(p38)delete[] p38;p38=0;
 if(p3c)delete[] p3c;p3c=0;
 b34=false;
}

void *Rva0007311B::rva00066667(unsigned flags)
{
    this->~Rva0007311B();
    if(flags&1) ::operator delete(this);
    return this;
}
