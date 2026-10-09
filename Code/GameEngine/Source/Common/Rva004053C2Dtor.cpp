// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ??1Rva004053C2@@UAE@XZ @0x004053C2 79B dtor stores C388D4 plus C388C4 calls rowed 0x00405350 restores BBB554 calls rowed base 0x001B4E74 caller deleting dtor 0x0040559F
struct Rva00405350 { ~Rva00405350(); };
// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"
class Snapshot { public: virtual ~Snapshot() {} };
class Rva004053C2 : public SubsystemInterface, public Snapshot {
public: virtual ~Rva004053C2();
private: char m_pad10[272]; Rva00405350 m_vec120;
};
Rva004053C2::~Rva004053C2() {}
