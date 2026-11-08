// cl: /DNDEBUG /MD
//
// AIUpdateInterface::ignoreObstacle (BFME2 build)
// retail 0x00268D88, 304 bytes. BFME2 AIUpdateInterface::ignoreObstacle with
// CritterDesync fprintf logging (game _fprintf at 0x2CEC42, flag byte
// VA 0x00E03745, sink VA 0x00DFEFF0, TheGameLogic 0x009FE78C). Donor is BFME1
// AIUpdateInterfaceIgnoreObstacle (name at ThingTemplate+0x64, id at
// Object+0x74, m_object at +8, m_ignoreObstacleID at +0x164).
// The desync flag byte and the log sink are real extern globals here; the
// banked attempt read TheGameLogic and the flag through literal-address
// macros, which reordered the loads. Callers 0x00269CEA 0x0026A2DE 0x0026BB26.

extern unsigned char g_00E03745;
// g_00E03745: matched references place it at VA 0xe03745 (zero-filled .bss).
unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" void __cdecl fprintf(void *sink, const char *format, ...);

#include "../../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../../../../Include/Common/Overridable.h"
#include "../../../../../Include/Common/ThingTemplate.h"


#include "../../../../Common/GameLogicObjectLookupView.h"

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }

private:
	void *m_vtable;
	const ThingTemplate *m_template;
	char m_pad08[0x74 - 0x08];
	ObjectID m_id;
};


extern GameLogic *TheGameLogic;

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::ignoreObstacle(const Object *obj)
{
	if (g_00E03745)
	{
		if (obj)
		{
			if (theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile,
					"  CritterDesync - Critter %s(%d) set to ignore %s(%d)",
					m_object->getTemplate()->getName().str(), m_object->getID(),
					obj->getTemplate()->getName().str(), obj->getID());
		}
		else
		{
			Object *old = TheGameLogic->findObjectByID(m_ignoreObstacleID);
			if (old)
			{
				if (theLogicRandomLogFile)
					fprintf(theLogicRandomLogFile,
						"  CritterDesync - Critter %s(%d) set to ignore NOTHING. Was previously ignoring %s(%d)",
						m_object->getTemplate()->getName().str(), m_object->getID(),
						old->getTemplate()->getName().str(), old->getID());
			}
			else
			{
				if (theLogicRandomLogFile)
					fprintf(theLogicRandomLogFile,
						"  CritterDesync - Critter %s(%d) set to ignore NOTHING. Was previously ignoring NOTHING",
						m_object->getTemplate()->getName().str(), m_object->getID());
			}
		}
	}
	m_ignoreObstacleID = obj ? obj->getID() : INVALID_OBJECT_ID;
}

// ?getIgnoredObstacleID@AIUpdateInterface@@QBE?AW4ObjectID@@XZ present-unmatched
ObjectID AIUpdateInterface::getIgnoredObstacleID() const
{
	return m_ignoreObstacleID;
}

// _theLogicRandomLogFile: retail VA 0x00DFEFF0 (desync log file)
extern "C" void *theLogicRandomLogFile = 0;
