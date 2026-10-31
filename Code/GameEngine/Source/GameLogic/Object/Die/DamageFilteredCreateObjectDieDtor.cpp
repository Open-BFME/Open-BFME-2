// cl: /MD
//
// ??1DamageFilteredCreateObjectDie@@UAE@XZ, retail 0x00485EC3, 32 bytes.
// Target evidence: the audited scalar deleting dtor 0x00485FC7 calls this
// body; slot 4 -> 0x00485EFD uses class-name string
// "DamageFilteredCreateObjectDie". Shape follows DieModuleDerived.cpp with one
// more empty polymorphic base: vptr restores at +0x00/+0x0C/+0x10/+0x14, then
// a tail jmp to DieModule::~DieModule 0x0045CE54. The empty bases are
// structural stand-ins; their real types are unrecovered.

#include "../../../../Include/GameLogic/Module/DieModule.h"

// The +0x14 subobject is DamageFilteredCreateObjectDie's damage-module
// interface (table 0x00C4AA84, per the matched ctor); its overrides live in
// DamageFilteredCreateObjectDieDamageSlots.cpp, so this TU only declares.
class Rva00C4AA84Iface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(void *arg) = 0;
};

enum NameKeyType { NK_UNKNOWN = 0 };

class DamageFilteredCreateObjectDie : public DieModule, public Rva00C4AA84Iface
{
public:
	virtual ~DamageFilteredCreateObjectDie();
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onDie(const DamageInfo *damageInfo);
	virtual void onHealing(void *arg);
	virtual NameKeyType getModuleNameKey() const;
private:
	unsigned int m_frame;		// +0x18
	int m_playerValue;		// +0x1C
};

DamageFilteredCreateObjectDie::~DamageFilteredCreateObjectDie()
{
}
