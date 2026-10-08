// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Semantic guide: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngineDevice/Source/W3DDevice/GameClient/
// Rva006DED60RoadBufferDestructor.cpp. The original BFME2 class name is unknown.
// Identity/layout come from native D3996..D3A17 RET0, the rowed reset atD3A17,
// constructor atD3A8A (two ten-element 12B arrays), and paired release74011F.
// Target differs from the donor by calling the existing paired release first.
// Its slot-A cleanup owns the string at+4; slot-B cleanup destroys the tree.
// The nonvirtual deleting wrapper at665BF calls this complete destructor.
class Rva000D3A17Resource { public: virtual void Delete_This()=0; int references; };
#include "ascii_string.h"
struct Rva000D3A8AElemA
{
    Rva000D3A17Resource *pointer;
    AsciiString name;
    unsigned char flag;
    // ?Rva000D3A8AElemA::~Rva000D3A8AElemA present-unmatched
    // Native array callback folds onto the existing 8B CameraMarker cleanup
    // at29D7C2: string member at+4 and the same releaseBuffer relocation.
    ~Rva000D3A8AElemA() {}
};
class Rva000D20A9 {public: ~Rva000D20A9(); private: void *head; int count;};
struct Rva000D3A8AElemB {Rva000D20A9 tree; int extra; ~Rva000D3A8AElemB() {} };
class Rva0074011F {public: void rva0074011F(); private: void *first,*second; };
class Rva000D3A17 {
public: ~Rva000D3A17();
private: Rva0074011F buffers; int field08,field0c,field10,field14; Rva000D3A8AElemA refs[10]; int field90; Rva000D3A8AElemB sets[10]; unsigned char field10c;
};
Rva000D3A17::~Rva000D3A17() {
 buffers.rva0074011F();
 for(int i=0;i<10;++i) {Rva000D3A17Resource *p=refs[i].pointer; if(p) {if(--p->references==0) p->Delete_This(); refs[i].pointer=0;}}
}
// ?Rva000D3A17DeleteAnchor absent-from-retail
void Rva000D3A17DeleteAnchor(Rva000D3A17 *p) {delete p;}
