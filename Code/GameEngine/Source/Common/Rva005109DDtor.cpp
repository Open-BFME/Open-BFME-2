// cl: /O1 /GX /DNDEBUG /MD /Ireference/shims/moduledata
#include "Common/Snapshot.h"
struct EmitVtableTag;

// Native5109D..510B3: the +C Snapshot base is proved by rowed
// adjusting thunk51C9A. Its inline destructor restores canonical BBB554;
// the primary base tail-calls the rowed14B destructor1B4E74. Primary
// fields are opaque here; that provider accesses its owned word at +8.
class GameEngineDeletingBase
{
public:
    GameEngineDeletingBase();
    virtual ~GameEngineDeletingBase();
private:
    char m_unknown04[8];
};
// Retail has no derived-table stores before the nullable Snapshot-base
// conversion. novtable preserves that empty abstract-destructor shape.
class __declspec(novtable) Rva005109D : public GameEngineDeletingBase, public Snapshot
{
public:
    Rva005109D(EmitVtableTag *);
    __declspec(noinline) virtual ~Rva005109D();
};

Rva005109D::~Rva005109D()
{
}

