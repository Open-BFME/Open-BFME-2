// cl: /O1 /GX /DNDEBUG /MD /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
typedef bool Bool;
#include "subsystem_interface.h"
#include "Common/Snapshot.h"
struct EmitVtableTag;

// Native5109D..510B3: the +C Snapshot base is proved by rowed
// adjusting thunk51C9A. Its inline destructor restores canonical BBB554;
// the primary base tail-calls SubsystemInterface's rowed14B destructor1B4E74.
// Its canonical header preserves the 12-byte base and owned name at +8.
// Retail has no derived-table stores before the nullable Snapshot-base
// conversion. novtable preserves that empty abstract-destructor shape.
class __declspec(novtable) Rva005109D : public SubsystemInterface, public Snapshot
{
public:
    Rva005109D(EmitVtableTag *);
    __declspec(noinline) virtual ~Rva005109D();
};

Rva005109D::~Rva005109D()
{
}
