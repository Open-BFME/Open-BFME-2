// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0RousingSpeechUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004ACF76, 135 bytes. The rowed
// ??0Rva0044EF5E base, the compiler's four table installs, the ObjectID list at +0x88 through
// its allocator constructor 0x0029FB3B (the empty allocator temporary lands in the spare stack byte
// at ebp+0xF), then the fields and a clear of the list.

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
struct Rva0029FB3BAlloc
{
	Rva0029FB3BAlloc() {}
};

// ??0RousingSpeechUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004ACF76
RousingSpeechUpdate::RousingSpeechUpdate(Thing *thing, const ModuleData *moduleData) :
	Rva0044EF5E(thing, moduleData),
	m_88(Rva0029FB3BAlloc())
{
	m_8C &= 0;
	m_90 = 0;
	m_94 = 0.0f;
	m_98 = 0.0f;
	m_88.reset();
}
