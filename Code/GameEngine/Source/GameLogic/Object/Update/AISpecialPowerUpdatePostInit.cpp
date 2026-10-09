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

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Debug &operator<<(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual Debug &slot6C(int first, int second, int third);
};
template <class T> Debug &operator<<(Debug &debug, const StringBase<T> &text);
extern Debug *theDebug;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

struct SpecialPowerTemplateView
{
	char m_pad00[0x1C];
	int m_1C;
};

class CommandButton
{
public:
	const AsciiString &getName() const { return m_name; }
	char m_pad00[0x10];
	AsciiString m_name;              // +0x10
	char m_pad14[0x44 - 0x14];
	const Overridable *m_specialPower; // +0x44
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};
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

class Object
{
public:
	const AsciiString &getCommandSetString() const;
	void *rva0028BD92(int key);
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

	const CommandSet *commandSet = TheControlBar->findCommandSet(getObject()->getCommandSetString());
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
		const Overridable *specialPower = commandButton->m_specialPower;
		if (specialPower)
		{
			int key = ((const SpecialPowerTemplateView *)specialPower->friend_getFinalOverride())->m_1C;
			void *module = getObject()->rva0028BD92(key);
			if (module)
				range = ((const Rva0044E6A7FloatChaseField *)module)->get();
		}
	}
	else
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->slot60();
			(theDebug->slot6C(0, 0, 0) << "AISpecialPower ("
				<< *(const StringBase<char> *)&TheNameKeyGenerator->keyToName(getModuleTagNameKey())
				<< ") will not work for "
				<< *(const StringBase<char> *)&getObject()->getTemplate()->getName()
				<< ". Command button not found: "
				<< *(const StringBase<char> *)&data->m_commandButtonName
				<< "\n").slot4C(2);
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
				theDebug->slot60();
				(theDebug->slot6C(0, 0, 0) << "Special power type is invalid for AISpecialPowerModule ("
					<< *(const StringBase<char> *)&TheNameKeyGenerator->keyToName(getModuleTagNameKey())
					<< ") for "
					<< *(const StringBase<char> *)&getObject()->getTemplate()->getName()
					<< ".\n").slot4C(2);
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
