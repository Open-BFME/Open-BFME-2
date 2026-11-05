// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// ?loadPostProcess@SpecialPowerModule@@MAEXXZ, retail 0x00493B1E..0x00493BD4
// (182B, EH): slot 1 of SpecialPowerModule's table 0x00C4E868 (loadPostProcess
// in 123 of 144 named sibling module tables), a Ghidra-unlisted gap body. It is
// Zero Hour's SpecialPowerModule::loadPostProcess: after the (folded, empty)
// BehaviorModule::loadPostProcess base call, the public-timer registration: unpaused (+0x1C), a
// shared-n-sync template with a public timer (final override bytes +0x59 and
// +0x58), a controlling player and a structure object (kind-of bit 0x80 of
// the template word +0x108) register the superweapon with TheInGameUI
// (slot 34: player index, power name, object id, template).
#include "ascii_string.h"

#include "../../../../Include/Common/Overridable.h"

struct SpecialPowerTemplateView
{
	char m_pad00[0x58];
	bool m_hasPublicTimer;									// +0x58
	bool m_sharedNSync;										// +0x59
};

#include "../../../../Include/Common/Player.h"

struct ThingTemplateKindOfView
{
	char m_pad000[0x108];
	unsigned int m_kindOf;									// +0x108
};

class Object
{
public:
	Player *getControllingPlayer() const;					// 0x0028AFA9
	int m_00;
	ThingTemplateKindOfView *m_template;					// +0x04
	char m_pad08[0x74 - 8];
	int m_id;												// +0x74
	int getID() const { return m_id; }
};

#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

#include "../../../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

// 0x000B3FD0 is the one-byte empty body the toolchain folds many empties into.
class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class SpecialPowerModuleBase
{
public:
	virtual void s0();
	SpecialPowerModuleData *m_moduleData;					// +0x04
	Object *m_object;										// +0x08
	int m_0C;
};

class SpecialPowerModuleInterface
{
public:
	virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3();
	virtual void i4();
	virtual AsciiString getPowerName() const;
	virtual const Overridable *getSpecialPowerTemplate() const;
	int m_14;
	int m_18;
};

class SpecialPowerModule : public SpecialPowerModuleBase, public SpecialPowerModuleInterface
{
public:
	Object *getObject() const { return m_object; }
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }
protected:
	virtual void loadPostProcess();
private:
	int m_pausedCount;										// +0x1C
};

void SpecialPowerModule::loadPostProcess()
{
	((Rva000B3FD0 *)this)->rva000B3FD0();
	if (m_pausedCount == 0 &&
			((const SpecialPowerTemplateView *)getSpecialPowerTemplate()->friend_getFinalOverride())->m_sharedNSync &&
			((const SpecialPowerTemplateView *)getSpecialPowerTemplate()->friend_getFinalOverride())->m_hasPublicTimer &&
			m_object->getControllingPlayer() &&
			(m_object->m_template->m_kindOf & 0x80))
	{
		TheInGameUI->addSuperweapon(getObject()->getControllingPlayer()->getPlayerIndex(),
																getPowerName(),
																(ObjectID)getObject()->getID(),
																getSpecialPowerModuleData()->m_specialPowerTemplate);
	}
}
