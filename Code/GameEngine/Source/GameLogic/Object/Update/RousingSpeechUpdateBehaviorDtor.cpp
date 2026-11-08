// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1RousingSpeechUpdate@@UAE@XZ, retail 0x004ACE96, 60 bytes. The compiler's four table installs, a
// clear of the list, then the member's destructor 0x00268902 and the base destructor's tail call.

class RousingSpeechUpdateModuleData;
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
#include "../../../../Include/GameLogic/Module/Rva0029FB3BMember.h"

class Rva0044EF5E : public SpecialAbilityUpdate
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
};
// Retail's tables: 0x00C54FE8 (23 slots), 0x00C4D640 at +0x0C, 0x00C54FD8 at +0x10 and 0x00C552A4 at +0x20.
class RousingSpeechUpdate : public Rva0044EF5E
{
public:
	RousingSpeechUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~RousingSpeechUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void startPreparation();
	void rva004ACF1D();
	void rva004AD176();
	virtual void triggerAbilityEffect();
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
private:
	Rva0029FB3BMember m_88; // +0x88
	unsigned int m_8C; // +0x8C
	bool m_90; // +0x90
	float m_94; // +0x94
	float m_98; // +0x98
};

// ??1RousingSpeechUpdate@@UAE@XZ @0x004ACE96
RousingSpeechUpdate::~RousingSpeechUpdate()
{
	m_88.reset();
}
