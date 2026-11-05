// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ArrowStormUpdate's slot-15 and slot-17 overrides (vftable 0x00C4D700,
// slot-2 name getter "ArrowStormUpdate"). Each first runs the base
// SpecialAbilityUpdate slot (rowed startPreparation / triggerAbilityEffect) and carries
// that slot's address name, which cl 7.1 needs to place the override; the
// method identities are not established. The +0x88 list is the one the
// rowed ArrowStormUpdate::xfer transfers.
//
// ?triggerAbilityEffect@ArrowStormUpdate@@UAEXXZ, retail 0x00490A74, 81 bytes.
// Slot 17: with module data +0xDC clear and an empty list, sets the flag at
// +0x98; otherwise retries the pinned bool member 0x0049083C up to module
// data +0xD4 times, keeping its result in +0x98, until it succeeds.
//
// ?startPreparation@ArrowStormUpdate@@UAEXXZ, retail 0x00490D0A, 53 bytes.
// Slot 15: resets the list (rowed 0x0026549E), zeroes +0x8C/+0x90/+0x94 and
// the flag at +0x98, then tail-calls the rowed member 0x00490AC5.

class ModuleData;

struct Rva0029FB3BNode
{
	Rva0029FB3BNode *m_next;
	Rva0029FB3BNode *m_previous;
	int m_value;
};

#include "../../../../Include/GameLogic/Module/Rva0029FB3BMember.h"

struct ArrowStormUpdateModuleData
{
	unsigned char m_pad00[0xD4];
	int m_shotsPerBurst;
	unsigned char m_padD8[0xDC - 0xD8];
	bool m_DC;
};

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class ArrowStormUpdate : public SpecialAbilityUpdate
{
public:
	virtual void startPreparation();
	virtual void triggerAbilityEffect();

	void rva00490AC5();	// row 0x00490AC5

private:
	bool rva0049083C();

	Rva0029FB3BMember m_88;
	int m_8C;
	int m_90;
	int m_94;
	bool m_98;
};

// ?triggerAbilityEffect@ArrowStormUpdate@@UAEXXZ @0x00490A74
void ArrowStormUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	const ArrowStormUpdateModuleData *data = (const ArrowStormUpdateModuleData *)m_moduleData;
	if (!data->m_DC && m_88.empty())
	{
		m_98 = true;
		return;
	}
	for (int i = 0; i < data->m_shotsPerBurst; )
	{
		bool done = rva0049083C();
		++i;
		m_98 = done;
		if (done)
			break;
	}
}

// ?startPreparation@ArrowStormUpdate@@UAEXXZ @0x00490D0A
void ArrowStormUpdate::startPreparation()
{
	SpecialAbilityUpdate::startPreparation();
	m_88.reset();
	m_8C = 0;
	m_90 = 0;
	m_94 = 0;
	m_98 = false;
	rva00490AC5();
}
