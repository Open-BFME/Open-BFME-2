// cl: /DNDEBUG /MD /EHsc
// ??1ThreatFinderUpdate@@UAE@XZ @0x003ECF64 (88B): virtual dtor that
// restores the primary plus +0x0C/+0x10 vtable slots via the shared
// UpdateModule base view (vptrs at +0 +0x0C +0x10 size 0x20) deletes the +0x20
// heap object through its rowed Rva003ECDB7 dtor plus rowed operator delete
// then calls the rowed UpdateModule base dtor 0x0024A797. Called by the
// matched deleting dtor 0x003ED0A8. Pool key 0x003ECCD6 plus ctor 0x003ECCA2
// prove the class.
#include "../../../../Include/GameLogic/Module/Rva003ECDB7Object.h"

// Base view matching Common/Rva0024A797DeletingDtor.cpp: vptrs at +0, +0xC,
// +0x10; 0x20 bytes (copied from SpecialAbilityUpdateDtor.cpp).
class Rva0049B47C
{
public:
	virtual ~Rva0049B47C() throw();

private:
	char m_pad04[8];
};

#include "../../../../Include/Common/MiBase1.h"

class PrimaryP451F45 : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP451F45() {}
};

// Retail's base +0x10 vftable (0x00BFBCE4, stored by ~UpdateModule
// 0x0024A797) holds _purecall in slot 0: the slot is pure.
class Rva0024A797_B2
{
public:
	virtual void f2() = 0;

private:
	char m_pad08[12];
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class ThreatFinderUpdate : public UpdateModule
{
public:
	virtual ~ThreatFinderUpdate();
	// Retail primary table 0x00C360CC slots 3 and 4: the rowed overrides 0x003ECED5 and
	// 0x003ECCD6 (ThreatFinderUpdate.cpp), so both units emit one table.
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void xfer(Xfer *xfer);

private:
	Rva003ECDB7Object *m_heap;
protected:
	virtual const char *GetSnapshotName() const;	// primary slot 2: retail 0x003ECCD0
};

ThreatFinderUpdate::~ThreatFinderUpdate()
{
	delete m_heap;
}
