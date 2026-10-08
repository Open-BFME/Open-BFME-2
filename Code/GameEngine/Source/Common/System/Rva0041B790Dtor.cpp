// cl: /Ireference/shims/moduledata /MD /EHsc
// Target: 0x0041B790..0x0041B7D9, 73 bytes, ends in RET.
// The rowed deleting destructor at 0x0041B7D9 establishes the existing
// address-derived class name; the original class identity remains unknown.
// Target stores primary/secondary vtables at +0/+0xC, calls 0x0041B603
// with this, restores Snapshot's vtable, then calls the rowed base destructor
// 0x001B4E74. The matched 0x002D3573 destructor supplies the same MI/EH
// compiler pattern. Base layout is target evidence, not a donor name claim.

class GameEngineDeletingBase
{
public:
    virtual ~GameEngineDeletingBase();
private:
    char m_pad04[8];
};

#include "Common/Snapshot.h"

class Rva0041B790 : public GameEngineDeletingBase, public Snapshot
{
public:
    virtual ~Rva0041B790();
    // Target call at 0x0041B7B5: ECX=this, no arguments, callee RET.
    // Its original name and purpose remain unresolved.
    void rva0041B603();
};

Rva0041B790::~Rva0041B790()
{
    rva0041B603();
}
