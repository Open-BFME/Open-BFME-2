// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// TerrainResourceClientBehavior destructor and deleting wrapper (vtable 0x00BEFF20),
// which uses the same bool at +0x0C and holder cleanup as the separately
// compiled slot-eighteen method. Slot methods stay in their original unit;
// the destructor needs only the already recovered cleanup helper.
class Rva004E7B0CHolder
{
public:
	void rva004E7B0C();
	void rva004E7D1D();
};

// TheInGameUI's holder at +0x58C. Retail adds the offset to the global loaded
// straight into ecx (add ecx, 0x58C); cl 7.1 emits that for byte-pointer
// arithmetic written in the body.
class InGameUI;
extern InGameUI *TheInGameUI;

class ModuleData;
class Object;
#include "Common/Snapshot.h"

// Native constructor chain 0x00252DEB -> 0x00252B68 fixes the base prefix; the
// twelve-byte extent follows its members +4/+8 and the derived bool +0x0C.
// The intermediate vptr reset in this destructor is 0x00BEFE48. The terminal
// destructor is the established folded 0x0049B47C body; its original base
// name is not established here. The vptr-derived base view does not add another
// private definition of the already conflicting Rva00252B68 constructor class.
class Rva0049B47C
{
public:
    virtual ~Rva0049B47C();
protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};
class Rva00BEFE48TerrainBase : public Rva0049B47C
{
public:
    __forceinline virtual ~Rva00BEFE48TerrainBase() {}
};
class TerrainResourceClientBehavior : public Rva00BEFE48TerrainBase
{
public:
    virtual ~TerrainResourceClientBehavior();
    virtual void rva004CC5FA();
    virtual void rva004CC61A();
private:
    bool m_0C;
};

// The terminal folded destructor's existing pin names this opaque base;
// Snapshot supplies its already rowed seven-byte link definition.
#pragma comment(linker, "/alternatename:??1Rva0049B47C@@UAE@XZ=??1Snapshot@@UAE@XZ")

// Retail Ghidra 0x004CC5AA..0x004CC5FA (80B). Class identity is target-backed:
// slot-zero wrapper 0x00252E56 and slot-four class-name body 0x00252E0B.
// Cleanup is the same holder used by the matched slot-eighteen body below.
TerrainResourceClientBehavior::~TerrainResourceClientBehavior()
{
    if (m_0C)
    {
        Rva004E7B0CHolder *holder = (Rva004E7B0CHolder *)((char *)TheInGameUI + 0x58C);
        holder->rva004E7D1D();
    }
}
