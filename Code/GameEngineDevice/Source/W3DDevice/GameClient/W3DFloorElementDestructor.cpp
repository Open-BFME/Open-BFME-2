// cl: /MD /EHs /Ireference/shims/bfme2_ascii
// Complete floor-element cleanup at 0x000E5033 (104 bytes through RET).
// Semantic guide: Open-BFME-1 6c1e0b51, BaseHeightMapFloorElementDestructor.cpp.
// Native and WB 0x881140 prove the two texture handles at +20/+24, strings
// at +8C/+90, and the leading call to the shared E4567 resource cleanup.
// BFME 1's member offsets differ; retain the target's existing unwind-pin
// name rather than asserting its virtual class identity. The target constructor
// starts with sphere floats, and this nonvirtual destructor writes no vptr.
// The four EH states and their cleanup actions are verified independently.
#include "ascii_string.h"

class TextureBaseClass { public: void Release_Ref(); };
struct FloorTextureRef {
    TextureBaseClass *pointer;
    ~FloorTextureRef() { if (pointer) pointer->Release_Ref(); }
};
class Rva000E4567 { public: void rva000E4567(); };

class Gen_uw_000e5033 {
public:
    ~Gen_uw_000e5033();
private:
    char m_prefix00[0x20];
    FloorTextureRef m_texture20;
    FloorTextureRef m_texture24;
    char m_middle28[0x8c-0x28];
    AsciiString m_name8c;
    AsciiString m_name90;
    char m_tail94[0xa0-0x94];
};

Gen_uw_000e5033::~Gen_uw_000e5033()
{
    reinterpret_cast<Rva000E4567 *>(this)->rva000E4567();
}
