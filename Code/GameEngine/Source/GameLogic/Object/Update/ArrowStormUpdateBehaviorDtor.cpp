// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1ArrowStormUpdate@@UAE@XZ, retail 0x004907C0, 49 bytes. The compiler's four table installs, the
// list member's destructor 0x00268902 (which clears the list itself: unlike its siblings this body
// has no separate clear) and the base destructor's tail call.

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
#include "../../../../Include/GameLogic/Module/Rva0029FB3BMember.h"

class Rva0044EF5E : public SpecialAbilityUpdate
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
};
// Retail's tables: 0x00C4D700 (23 slots), 0x00C4D640 at +0x0C, 0x00C4DEE8 at +0x10 and 0x00C4D61C at +0x20.
class ArrowStormUpdate : public Rva0044EF5E
{
public:
	ArrowStormUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~ArrowStormUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void startPreparation();
	virtual void triggerAbilityEffect();
	virtual bool continuePreparation(); // primary slot 16, 0x00490628
	virtual bool vslot08(int value); // +0x20 slot 8, 0x004906CD
protected:
	virtual void xfer(Xfer *xfer);
private:
	Rva0029FB3BMember m_88; // +0x88
	int m_8C; // +0x8C
	int m_90; // +0x90
	int m_94; // +0x94
	bool m_98; // +0x98
};

// ??1ArrowStormUpdate@@UAE@XZ @0x004907C0
ArrowStormUpdate::~ArrowStormUpdate()
{
}
