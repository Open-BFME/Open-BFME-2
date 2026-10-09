// ?setPriorityThing@ScriptEngine@@IAEXPAVScriptAction@@@Z
// partial score=0.97 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ScriptEngine::setPriorityThing, retail 0x00205EEC (561 bytes), the
// attack-priority-set action for one thing type or an ObjectTypes list.
// Semantic donor: Zero Hour's ScriptEngine::setPriorityThing and Open-BFME-1's
// ScriptEngineSetPriorityThing.cpp (ScriptEngine::setPriorityThing at retail
// 0x0033E040 there); the BFME2 body is the same statement sequence. Identity
// evidence: WorldBuilder's debug body (ScriptEngine.cpp:2308 "Not enough
// parameters", the two attack-priority error strings) and its neighbours
// 0x002061D7 setPriorityDefault and 0x00205D5D findAttackInfo. The thing
// lookup is the ledger's 0x002D06CA registry lookup and the per-info setter
// is the ledger's address-named 0x00358333 body.

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class BFMERetailAsciiString
{
public:
	// Declared only: the donor's inline ctor/dtor are retail's out-of-line
	// StringBase(const char *) and releaseBuffer.
	BFMERetailAsciiString(const char *string);
	~BFMERetailAsciiString();

private:
	void releaseBuffer();
	char *m_data;
};

class Parameter
{
public:
	Int getInt(void) const { return m_integer; }
	const AsciiString &getString(void) const { return m_string; }

private:
	char m_unknown[8];
	Int m_integer;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	Parameter *getParameter(Int index)
	{
		if (index >= 0 && index < m_parameterCount)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	Int m_parameterCount;
	Parameter *m_parameters[12];
};

// 0x002041AC: bounds-checked name getter over the vector at +8/+0xC.
class Rva002041AC
{
public:
	AsciiString rva002041AC(unsigned int index) const;
};

class ObjectTypes
{
public:
	unsigned int getListSize(void) const { return m_end - m_begin; }

private:
	void *m_vptr;
	AsciiString m_listName;
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

// ThingFactory's template lookup (ledger 0x002D06CA, held under this name).
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
extern Rva002D06CA *TheThingFactory;

// Image/Overridable are the placeholder row's spelling of (template, priority).
class Overridable;
class Image;

class Rva0034C5E0
{
public:
	void rva00358333(Overridable *thing, Image *priority);
};

struct Rva00205D5DEntry : public Rva0034C5E0
{
	int m_00;
	AsciiString m_name;
	int m_08;
	int m_0C;
};

class ScriptEngine
{
public:
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	Rva00205D5DEntry *rva00205D5D(const AsciiString &name, bool addIfNotFound);
	void AppendDebugMessage(const AsciiString &message, bool forcePause);

protected:
	void setPriorityThing(ScriptAction *action);
};

extern ScriptEngine *TheScriptEngine;

// ?setPriorityThing@ScriptEngine@@IAEXPAVScriptAction@@@Z
void ScriptEngine::setPriorityThing(ScriptAction *action)
{
	AsciiString typeArgument = action->getParameter(1)->getString();
	ObjectTypes *types = TheScriptEngine->getObjectTypes(typeArgument);
	if (!types)
	{
		Overridable *thingTemplate = (Overridable *)TheThingFactory->rva002D06CA(&typeArgument);
		if (!thingTemplate)
		{
			{
				BFMERetailAsciiString message("***Attempting to set attack priority on an invalid thing:***");
				AppendDebugMessage(*(const AsciiString *)&message, false);
			}
			AppendDebugMessage(action->getParameter(0)->getString(), false);
			return;
		}

		Rva00205D5DEntry *info = rva00205D5D(action->getParameter(0)->getString(), true);
		if (!info)
		{
			BFMERetailAsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
			AppendDebugMessage(*(const AsciiString *)&message, false);
			return;
		}
		info->rva00358333(thingTemplate, (Image *)action->getParameter(2)->getInt());
		return;
	}
	else
	{
		for (unsigned int typeIndex = 0; typeIndex < types->getListSize(); typeIndex++)
		{
			AsciiString thisTypeName = ((const Rva002041AC *)types)->rva002041AC(typeIndex);
			Overridable *thisType = (Overridable *)TheThingFactory->rva002D06CA(&thisTypeName);
			if (!thisType)
			{
				{
					BFMERetailAsciiString message("***Attempting to set attack priority on an invalid thing:***");
					AppendDebugMessage(*(const AsciiString *)&message, false);
				}
				AppendDebugMessage(action->getParameter(0)->getString(), false);
				return;
			}

			Rva00205D5DEntry *info = rva00205D5D(action->getParameter(0)->getString(), true);
			if (!info)
			{
				BFMERetailAsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
				AppendDebugMessage(*(const AsciiString *)&message, false);
				return;
			}
			info->rva00358333(thisType, (Image *)action->getParameter(2)->getInt());
		}
		return;
	}
}
