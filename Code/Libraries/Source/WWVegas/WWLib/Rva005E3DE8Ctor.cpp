// ??0Rva005E3DE8@@QAE@XZ
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
#include "ascii_string.h"
class Rva0022167C
{
public:
	~Rva0022167C();
private:
	char m_bytes[8]; // +0x00
};
#include "../../../../GameEngine/Include/Common/Rva00221635.h"
class Rva005E3DE8 : public Rva00221635 {
public: Rva005E3DE8(); virtual void pure();
private: AsciiString name;
};
Rva005E3DE8::Rva005E3DE8() : Rva00221635((int)&AsciiString("ArmyDetailsPanel")), name() {}

// Identity/layout: native83B head005E3D95..005E3DE8 constructs the8B
// holder base from an ArmyDetailsPanel AsciiString temporary, then stores
// vtableC77CC4 and clears own AsciiString+8. Vtable slot0 deleting wrapper
//005E3EEE calls at005E3EF1 into adjacent matched Rva005E3DE8 destructor005E3DE8.
// Existing constructor carrier Rva00221635(int) and cleanup Rva0022167C
// describe the same8B physical base; keep their established names with
// explicit compatible-layout view, without adding a second name pin.
// This polymorphic ctor view is separate from the old opaque-member dtor
// view because merging changes that native dtor's vptr store codegen.

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?pure@Rva005E3DE8@@UAEXXZ=??_GRva005E3DE8@@QAEPAXI@Z")
