// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?postInitAISpecialPower@AISpecialPowerUpdate@@AAEXXZ @0x004B303F 576B.
// WorldBuilder 0x01234F50 AISpecialPowerUpdate::postInitAISpecialPower
// (AISpecialPowerUpdate.cpp) names it; the rowed xfer 0x004B3352 and slot
// 45 0x004B33EB call it. The object's command set (TheControlBar
// findCommandSet of its command-set string) is searched over its 32 buttons
// for the module data's +8 command button name. A found button marks +0x20
// and takes the range of the object's special-power module chosen by its
// special-power template's final override +0x1C; a missing one logs. Then
// the +0x0C AI type builds the AI special power (rowed factory 0x0058A6A8)
// into +0x24 which receives the button and the found range then the data's
// radius (+0x10) and range (+0x14) when positive; an invalid type logs and
// clears +0x20. Last +0x21 is set. Retail keeps the two release logs
// (_bfme_debugReportingEnabled) and drops WB's two "(safe to ignore)" logs
// together with their AOE/targeted tests. Literals copied from retail.
#include "ascii_string.h"

typedef float Real;
enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Common/debug.h"
template <class T> Debug &operator<<(Debug &debug, const StringBase<T> &text);
extern Debug *theDebug;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

#include "../../../../Include/Common/Overridable.h"

struct SpecialPowerTemplateView
{
	char m_pad00[0x1C];
	int m_1C;
};

#include "../../../../Include/Common/SpecialPower.h"
#include "../../../../Include/GameClient/CommandButton.h"
#include "../../../../Include/GameClient/CommandSet.h"

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);	// rowed 0x0031D5F8 (ControlBar::findCommandSet)
};
#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

class Rva0044E6A7FloatChaseField
{
public:
	float get() const;
};

struct ThingTemplateView
{
	const AsciiString &getName() const { return m_name; }
	char m_pad00[0x64];
	AsciiString m_name;
};

enum SpecialPowerType {};
class SpecialAbilityUpdate;
class Object
{
public:
	const AsciiString *rva00290E67() const;	// rowed 0x00290E67 (command-set string selector)
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;
	const ThingTemplateView *getTemplate() const { return m_template; }
private:
	void *m_vtable;
	const ThingTemplateView *m_template;
};

void *Rva0058A6A8_Create(int type);

struct AISpecialPowerView
{
	char m_pad00[8];
	const CommandButton *m_commandButton; // +8
	int m_0C;
	Real m_range;                         // +0x10
	Real m_radius;                        // +0x14
};

struct AISpecialPowerUpdateModuleData
{
	void *m_vtable;
	NameKeyType m_moduleTagNameKey;  // +4
	AsciiString m_commandButtonName; // +8
	int m_specialPowerAIType;        // +0xC
	Real m_specialPowerRadius;       // +0x10
	Real m_specialPowerRange;        // +0x14
};

class AISpecialPowerUpdate
{
public:
	virtual ~AISpecialPowerUpdate();
private:
	void postInitAISpecialPower();
	const AISpecialPowerUpdateModuleData *getAISpecialPowerUpdateModuleData() const { return m_moduleData; }
	NameKeyType getModuleTagNameKey() const { return m_moduleData->m_moduleTagNameKey; }
	Object *getObject() const { return m_object; }

	const AISpecialPowerUpdateModuleData *m_moduleData; // +4
	Object *m_object;                                   // +8
	char m_pad0C[0x20 - 0x0C];
	bool m_hasCommandButton;                            // +0x20
	bool m_initialized;                                 // +0x21
	AISpecialPowerView *m_aiSpecialPower;               // +0x24
};

void AISpecialPowerUpdate::postInitAISpecialPower()
{
	const AISpecialPowerUpdateModuleData *data = getAISpecialPowerUpdateModuleData();
	const CommandButton *commandButton = 0;
	Real range = 0.0f;

	const CommandSet *commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(getObject()->rva00290E67());
	if (commandSet)
	{
		for (int i = 0; i < 32; ++i)
		{
			const CommandButton *button = commandSet->getCommandButton(i);
			if (button && button->getName() == data->m_commandButtonName)
			{
				commandButton = button;
				break;
			}
		}
	}

	if (commandButton)
	{
		m_hasCommandButton = true;
		const Overridable *specialPower = commandButton->getSpecialPowerTemplate();
		if (specialPower)
		{
			int key = ((const SpecialPowerTemplateView *)specialPower->friend_getFinalOverride())->m_1C;
			void *module = getObject()->findSpecialAbilityUpdate((SpecialPowerType)(key));
			if (module)
				range = ((const Rva0044E6A7FloatChaseField *)module)->get();
		}
	}
	else
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "AISpecialPower ("
				<< *(const StringBase<char> *)&TheNameKeyGenerator->keyToName(getModuleTagNameKey())
				<< ") will not work for "
				<< *(const StringBase<char> *)&getObject()->getTemplate()->getName()
				<< ". Command button not found: "
				<< *(const StringBase<char> *)&data->m_commandButtonName
				<< "\n").CrashDone(2);
		}
	}

	if (m_hasCommandButton)
	{
		m_aiSpecialPower = (AISpecialPowerView *)Rva0058A6A8_Create(data->m_specialPowerAIType);
		if (!m_aiSpecialPower)
		{
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				theDebug->SkipNext();
				(theDebug->CrashBegin(0, 0, 0) << "Special power type is invalid for AISpecialPowerModule ("
					<< *(const StringBase<char> *)&TheNameKeyGenerator->keyToName(getModuleTagNameKey())
					<< ") for "
					<< *(const StringBase<char> *)&getObject()->getTemplate()->getName()
					<< ".\n").CrashDone(2);
			}
			m_hasCommandButton = false;
		}
		else
		{
			m_aiSpecialPower->m_commandButton = commandButton;
			if (range > 0.0f)
				m_aiSpecialPower->m_range = range;
			if (data->m_specialPowerRadius > 0.0f)
				m_aiSpecialPower->m_radius = data->m_specialPowerRadius;
			if (data->m_specialPowerRange > 0.0f)
				m_aiSpecialPower->m_range = data->m_specialPowerRange;
		}
	}

	m_initialized = true;
}
