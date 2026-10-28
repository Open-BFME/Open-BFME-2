// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
//
// Opaque scalar deleting destructors, batch B05: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md)
// beyond the secondary-base offsets their adjustor thunks prove.
//
//   wrapper     dtor        vtable#slot
//   0x0025361E  0x0047A724  0x00C465F8#0
//   0x00254418  0x004905B0  0x00C4B6C8#0
//   0x002563B2  0x002563CE  0x00BF3AC0#0
//   0x0025E51D  0x0025E4CD  0x00BF6040#0
//   0x0026E81A  0x0026E7EA  0x00BFA3A4#0
//   0x0026F597  0x0026F445  0x00BFABB8#0
//   0x00279FFC  0x002793F0  0x00BFB0B4#7
//   0x00287C05  0x00286F8F  0x00BFB7BC#0
//   0x002896EA  0x002894A2  0x00BFB840#0
//   0x0029A10F  0x00299CE4  0x00BFC300#7
//   0x002A6A11  0x002A5B30  0x00BFD410#0
//   0x002BAEE5  0x002B964F  0x00BFE2E4#0
//   0x002BFD53  0x002BFB2D  0x00BFE508#0
//   0x002C5590  0x002C5398  0x00BFF658#0
//   0x002C65EB  0x002C6354  0x00C004E4#0
//   0x002CE047  0x002CD4A6  0x00C02170#0
//   0x002D09F5  0x002D0588  0x00C0233C#0
//   0x002D2C9E  0x005248D0  0x00C02A80#0
//   0x002D579A  0x002D5333  0x00C02C1C#0

struct EmitVtableTag;

class Rva0047A724
{
public:
	Rva0047A724(EmitVtableTag *);
public:
	virtual ~Rva0047A724();
};

// ?<Rva0047A724::Rva0047A724> absent-from-retail
Rva0047A724::Rva0047A724(EmitVtableTag *)
{
}

class Rva004905B0
{
public:
	Rva004905B0(EmitVtableTag *);
public:
	virtual ~Rva004905B0();
};

// ?<Rva004905B0::Rva004905B0> absent-from-retail
Rva004905B0::Rva004905B0(EmitVtableTag *)
{
}

class Rva002563CE
{
public:
	Rva002563CE(EmitVtableTag *);
public:
	virtual ~Rva002563CE();
};

// ?<Rva002563CE::Rva002563CE> absent-from-retail
Rva002563CE::Rva002563CE(EmitVtableTag *)
{
}

class Rva0025E4CD
{
public:
	Rva0025E4CD(EmitVtableTag *);
public:
	virtual ~Rva0025E4CD();
};

// ?<Rva0025E4CD::Rva0025E4CD> absent-from-retail
Rva0025E4CD::Rva0025E4CD(EmitVtableTag *)
{
}

class Rva0026E7EA
{
public:
	Rva0026E7EA(EmitVtableTag *);
public:
	virtual ~Rva0026E7EA();
};

// ?<Rva0026E7EA::Rva0026E7EA> absent-from-retail
Rva0026E7EA::Rva0026E7EA(EmitVtableTag *)
{
}

class Rva0026F445
{
public:
	Rva0026F445(EmitVtableTag *);
public:
	virtual ~Rva0026F445();
};

// ?<Rva0026F445::Rva0026F445> absent-from-retail
Rva0026F445::Rva0026F445(EmitVtableTag *)
{
}

class __declspec(novtable) Rva002793F0Base0
{
public:
	virtual ~Rva002793F0Base0();
private:
	char m_unmodelled_04[0x60 - 0x04];
};

// Secondary base at +0x60: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x60) at 0x0027966F in its vtable is target evidence for it.
class __declspec(novtable) Rva002793F0Base60
{
public:
	virtual ~Rva002793F0Base60();
};
class Rva002793F0 : public Rva002793F0Base0, public Rva002793F0Base60
{
public:
	Rva002793F0(EmitVtableTag *);
public:
	virtual ~Rva002793F0();
};

// ?<Rva002793F0::Rva002793F0> absent-from-retail
Rva002793F0::Rva002793F0(EmitVtableTag *)
{
}

typedef bool Bool;
#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

class FireLogicSystem : public SubsystemInterface, public Snapshot
{
public:
	FireLogicSystem(EmitVtableTag *);
	virtual ~FireLogicSystem();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
};

// ?<FireLogicSystem::FireLogicSystem> absent-from-retail
FireLogicSystem::FireLogicSystem(EmitVtableTag *)
{
}

class Rva002894A2
{
public:
	Rva002894A2(EmitVtableTag *);
public:
	virtual ~Rva002894A2();
};

// ?<Rva002894A2::Rva002894A2> absent-from-retail
Rva002894A2::Rva002894A2(EmitVtableTag *)
{
}

class __declspec(novtable) Rva00299CE4Base0
{
public:
	virtual ~Rva00299CE4Base0();
private:
	char m_unmodelled_04[0x60 - 0x04];
};

// Secondary base at +0x60: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x60) in its vtable is target evidence for it.
class __declspec(novtable) Rva00299CE4Base60
{
public:
	virtual ~Rva00299CE4Base60();
};
class Rva00299CE4 : public Rva00299CE4Base0, public Rva00299CE4Base60
{
public:
	Rva00299CE4(EmitVtableTag *);
public:
	virtual ~Rva00299CE4();
};

// ?<Rva00299CE4::Rva00299CE4> absent-from-retail
Rva00299CE4::Rva00299CE4(EmitVtableTag *)
{
}

class __declspec(novtable) Rva002A5B30Base0
{
public:
	virtual ~Rva002A5B30Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x002A5EDE in its vtable is target evidence for it.
class __declspec(novtable) Rva002A5B30BaseC
{
public:
	virtual ~Rva002A5B30BaseC();
};
class Rva002A5B30 : public Rva002A5B30Base0, public Rva002A5B30BaseC
{
public:
	Rva002A5B30(EmitVtableTag *);
public:
	virtual ~Rva002A5B30();
};

// ?<Rva002A5B30::Rva002A5B30> absent-from-retail
Rva002A5B30::Rva002A5B30(EmitVtableTag *)
{
}

class __declspec(novtable) Rva002B964FBase0
{
public:
	virtual ~Rva002B964FBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) in its vtable is target evidence for it.
class __declspec(novtable) Rva002B964FBaseC
{
public:
	virtual ~Rva002B964FBaseC();
};
class LivingWorldLogic : public Rva002B964FBase0, public Rva002B964FBaseC
{
public:
	LivingWorldLogic(EmitVtableTag *);
public:
	virtual ~LivingWorldLogic();
};

// ?<LivingWorldLogic::LivingWorldLogic> absent-from-retail
LivingWorldLogic::LivingWorldLogic(EmitVtableTag *)
{
}

class Rva002BFB2D
{
public:
	Rva002BFB2D(EmitVtableTag *);
public:
	virtual ~Rva002BFB2D();
};

// ?<Rva002BFB2D::Rva002BFB2D> absent-from-retail
Rva002BFB2D::Rva002BFB2D(EmitVtableTag *)
{
}

class Rva002C5398
{
public:
	Rva002C5398(EmitVtableTag *);
public:
	virtual ~Rva002C5398();
};

// ?<Rva002C5398::Rva002C5398> absent-from-retail
Rva002C5398::Rva002C5398(EmitVtableTag *)
{
}

// Target destructor proves cleanup on this, then free of the vector's first
// pointer and an external base destructor. Original owner identity is unknown.
#include <stdlib.h>
// Pointer-only transfer ABI established by native calls and the existing
// entry serializer. Coordinate temporary lifetime is visible in the EH flags.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"
class Xfer::Version { public: Version(unsigned char a,unsigned char b):current(a),minimum(b){} unsigned char current,minimum; };
class Coord3DBase {
public:
 Coord3DBase(float xCoord, float yCoord, float zCoord) : x(xCoord), y(yCoord), z(zCoord) {}
 ~Coord3DBase() {}
 float x,y,z;
};
class Rva002C5EF0 {
public:
 Rva002C5EF0(const Coord3DBase &, float, unsigned);
 void rva002C5EF0(Xfer *);
private:
 unsigned m_0; Coord3DBase m_4;
 unsigned m_10; float m_14,m_18; unsigned m_1C;
};
class AITargetChooser { public: void xfer(Xfer *); };
class AITacticsGenerator { public: void DoXfer(Xfer *); };
class ModuleData;
struct Rva002C6354Buffer
{
    void *begin, *end, *capacity;
    ~Rva002C6354Buffer() { if (begin != 0) free(begin); }
};
// The ctor is rowed at 0x00506B1B (vptr plus byte 0 at +4); declaring it keeps
// this unit from emitting an implicit vptr-only copy under the same name.
class Rva00506B1B
{
public:
    Rva00506B1B();
    virtual ~Rva00506B1B();
private:
    char m_unmodelled04[4];
};
class Rva002C61AF { public: void rva002C61AF(); };

class Rva002C6354 : public Rva00506B1B
{
public:
	Rva002C6354(EmitVtableTag *);
public:
	virtual ~Rva002C6354();
    void DoXfer(Xfer *x);
private:
    unsigned m_player;
    AITargetChooser *m_targetChooser;
    AITacticsGenerator *m_10;
    char m_unmodelled14[12];
    Rva002C6354Buffer m_buffer;
};

// ?<Rva002C6354::Rva002C6354> absent-from-retail
Rva002C6354::Rva002C6354(EmitVtableTag *)
{
}

class Rva002CD4A6
{
public:
	Rva002CD4A6(EmitVtableTag *);
public:
	virtual ~Rva002CD4A6();
};

// ?<Rva002CD4A6::Rva002CD4A6> absent-from-retail
Rva002CD4A6::Rva002CD4A6(EmitVtableTag *)
{
}

class Rva002D0588
{
public:
	Rva002D0588(EmitVtableTag *);
public:
	virtual ~Rva002D0588();
};

// ?<Rva002D0588::Rva002D0588> absent-from-retail
Rva002D0588::Rva002D0588(EmitVtableTag *)
{
}

class Rva005248D0
{
public:
	Rva005248D0(EmitVtableTag *);
public:
	virtual ~Rva005248D0();
};

// ?<Rva005248D0::Rva005248D0> absent-from-retail
Rva005248D0::Rva005248D0(EmitVtableTag *)
{
}

Rva002C6354::~Rva002C6354()
{
    ((Rva002C61AF *)this)->rva002C61AF();
}

// Native 0x002C63A1..0x002C64D0; WB TacticalAI::DoXfer at 0x00E894D0
// corroborates the chooser/generator calls and interest-zone save/load loops.
// Keep the established address owner until its complete class identity is
// reconciled. The ModuleData vector spelling supplies the existing four-byte
// pointer insertion ABI only; it is not a claim about the entry's identity.
void Rva002C6354::DoXfer(Xfer *x)
{
 Xfer::Version version(1,1);
 (*x == version);
 bool hasChooser = m_targetChooser != 0;
 (*x == hasChooser);
 if (m_targetChooser) m_targetChooser->xfer(x);
 m_10->DoXfer(x);
 _STL::vector<const ModuleData *> &entries =
     *reinterpret_cast<_STL::vector<const ModuleData *> *>(&m_buffer);
 unsigned count = entries.size();
 (*x == count);
 if (x->IsStoring()) {
  const ModuleData **last = (const ModuleData **)m_buffer.end;
  for (const ModuleData **it = (const ModuleData **)m_buffer.begin; it != last; ++it)
   ((Rva002C5EF0 *)*it)->rva002C5EF0(x);
 } else if (x->IsLoading()) {
  for (unsigned i=0; i<count; ++i) {
   const ModuleData *slot = (const ModuleData *)new Rva002C5EF0(Coord3DBase(0,0,0), 0.0f, m_player);
   ((Rva002C5EF0 *)slot)->rva002C5EF0(x);
   entries.push_back(slot);
  }
 }
}

// Complete destructors the deleting destructors above call, bound to the rows at their retail
// addresses (the dtor column of the table at the top of this file).
#pragma comment(linker, "/alternatename:??1Rva0026F445@@UAE@XZ=??1UpgradeCenter@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva002793F0@@UAE@XZ=??1Drawable@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva00299CE4@@UAE@XZ=??1Object@@MAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva002A5B30@@UAE@XZ=??1InGameUI@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva002BFB2D@@UAE@XZ=??1LivingWorld@@UAE@XZ")
// Callees bound to their rows at retail's call targets: ~Rva002C6354 calls 0x002C61AF and
// DoXfer constructs its slot with the constructor at 0x002C6234.
#pragma comment(linker, "/alternatename:?rva002C61AF@Rva002C61AF@@QAEXXZ=?rva002C61AF@Rva002C60E4@@QAEXXZ")
#pragma comment(linker, "/alternatename:??0Rva002C5EF0@@QAE@ABVCoord3DBase@@MI@Z=??0Rva002C5EF0@@QAE@ABUCoord3DBase@@MPAVPlayer@@@Z")
