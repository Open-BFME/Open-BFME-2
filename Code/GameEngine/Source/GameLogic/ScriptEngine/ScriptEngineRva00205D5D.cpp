// cl: /Ireference/shims/bfme2_ascii /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?findAttackInfo@ScriptEngine@@QAEPAVAttackPriorityInfo@@ABVAsciiString@@_N@Z, retail 0x00205D5D, 128 bytes.
// ScriptEngine attack-priority-set table: 256 entries of 0x10 at 0x19100 with
// AsciiString at +4, count at 0x1A100. Searches index 1.. for compare==0,
// returns entry start (string-4); else if create and count<0x100 appends via
// AsciiString::operator=, bumps count and returns new entry; else null.
// Evidence: chain caller 0x002061D7 shares this with ScriptEngine::
// AppendDebugMessage (same this) and names the "***Error allocating attack
// priority set" limit; callees are rowed StringBase::compare and pinned
// AsciiString::operator=.
#include "../../../Include/GameLogic/ObjectTypesClass.h"
#include "../../../Include/GameLogic/AttackPriorityInfo.h"
class ThingTemplate;
#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

// BFME 2 keeps the AI's attack priority sets in a list under TheAI's data
// (+0x18, sets at +0xFC); each set owns a list of (template name, priority).
struct Rva00205DDDItem
{
	Rva00205DDDItem *m_next;
	Rva00205DDDItem *m_prev;
	AsciiString m_templateName;
	int m_priority;
};
struct Rva00205DDDSet
{
	int m_00;
	AsciiString m_name;
	int m_defaultPriority;
	Rva00205DDDItem *m_priorityList;
	Rva00205DDDSet *m_next;
};
struct Rva00205DDDData
{
	char m_pad[0xFC];
	Rva00205DDDSet *m_attackPrioritySets;
};
struct Rva00205DDDAI
{
	char m_pad[0x18];
	Rva00205DDDData *m_data;
};
class AI;
extern AI *TheAI;


#include "../../Common/debug.h"
extern Debug *theDebug;
template <class T> Debug &operator<<(Debug &debug, const StringBase<T> &string);
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

#include "../../../Include/GameLogic/ScriptParameter.h"

#include "../../../Include/GameLogic/ScriptAction.h"


#include "../../../Include/GameLogic/ScriptEngine.h"

extern ScriptEngine *TheScriptEngine;

AttackPriorityInfo *ScriptEngine::findAttackInfo(const AsciiString &asciiString, bool create)
{
	for (int i = 1; i < m_numAttackInfo; ++i)
	{
		if (m_attackPriorityInfo[i].m_name.compare(asciiString) == 0)
			return &m_attackPriorityInfo[i];
	}
	if (create && m_numAttackInfo < 0x100)
	{
		m_attackPriorityInfo[m_numAttackInfo].m_name = asciiString;
		++m_numAttackInfo;
		return &m_attackPriorityInfo[m_numAttackInfo - 1];
	}
	return 0;
}

// ?getAttackInfo@ScriptEngine@@QAEPBVAttackPriorityInfo@@ABVAsciiString@@@Z,
// retail 0x00205DDD, 271 bytes. Open-BFME-1 ScriptEngineAttackInfo.cpp (same
// shape): look the name up in the live table (entry 0 is the default), else
// find the AI's attack priority set of that name, create the table entry with
// the set's default priority and its (template, priority) list, else report an
// undefined priority through the debug stream and return the default entry.
const AttackPriorityInfo *ScriptEngine::getAttackInfo(const AsciiString &name)
{
	int i;
	for (i = 1; i < m_numAttackInfo; ++i)
	{
		if (m_attackPriorityInfo[i].m_name.compare(name) == 0)
			return &m_attackPriorityInfo[i];
	}

	for (Rva00205DDDSet *set = ((Rva00205DDDAI *)TheAI)->m_data->m_attackPrioritySets; set; set = set->m_next)
	{
		if (set->m_name.compare(name) == 0)
		{
			AttackPriorityInfo *info = findAttackInfo(name, true);
			if (!info)
				break;

			info->m_defaultPriority = set->m_defaultPriority;
			Rva00205DDDItem *item = set->m_priorityList->m_next;
			while (item != set->m_priorityList)
			{
				const ThingTemplate *thing = TheThingFactory->findTemplate(item->m_templateName);
				if (thing)
					info->setPriority(thing, item->m_priority);
				item = item->m_next;
			}
			return reinterpret_cast<const AttackPriorityInfo *>(info);
		}
	}

	if (bfmeRva000387C0())
	{
		_bfme_debugRecordCallsite(1);
		theDebug->SkipNext();
		Debug &dbg = theDebug->CrashBegin(0, 0, 0);
		(dbg << "Attempting to use an undefined attack priority - '" << (const StringBase<char> &)name << "'\n").CrashDone(2);
	}
	return &m_attackPriorityInfo[0];
}

// ?setPriorityThing@ScriptEngine@@IAEXPAVScriptAction@@@Z, retail 0x00205EEC,
// 561 bytes. Zero Hour's ScriptEngineSetPriorityThing.cpp is the semantic
// donor; the BFME 2 body differs only in the table lookups (rva00205D5D and
// the 0x002041AC name getter) and in the outer-branch message spellings, which
// the bytes fix: the "invalid thing" message is a call temporary (its release
// is emitted between the two AppendDebugMessage calls) and the "error
// allocating" message is a named AsciiString local. The two inner message
// sites are scoped AsciiString locals; their inline ctor/dtor call retail's
// out-of-line StringBase(const char *) and releaseBuffer.
void ScriptEngine::setPriorityThing(ScriptAction *action)
{
	AsciiString typeArgument = action->getParameter(1)->getString();
	ObjectTypes *types = TheScriptEngine->getObjectTypes(typeArgument);
	if (!types)
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(typeArgument);
		if (!thingTemplate)
		{
			AppendDebugMessage(AsciiString("***Attempting to set attack priority on an invalid thing:***"), false);
			AppendDebugMessage(action->getParameter(0)->getString(), false);
			return;
		}

		AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
		if (!info)
		{
			AsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
			AppendDebugMessage(message, false);
			return;
		}
		info->setPriority(thingTemplate, action->getParameter(2)->getInt());
		return;
	}
	else
	{
		for (unsigned int typeIndex = 0; typeIndex < types->getListSize(); typeIndex++)
		{
			AsciiString thisTypeName = types->getNthInList(typeIndex);
			const ThingTemplate *thisType = TheThingFactory->findTemplate(thisTypeName);
			if (!thisType)
			{
				{
					AsciiString message("***Attempting to set attack priority on an invalid thing:***");
					AppendDebugMessage(*(const AsciiString *)&message, false);
				}
				AppendDebugMessage(action->getParameter(0)->getString(), false);
				return;
			}

			AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
			if (!info)
			{
				AsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
				AppendDebugMessage(*(const AsciiString *)&message, false);
				return;
			}
			info->setPriority(thisType, action->getParameter(2)->getInt());
		}
		return;
	}
}
