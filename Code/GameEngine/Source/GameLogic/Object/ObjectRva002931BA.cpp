// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002931BA@Object@@QAE_NXZ, retail 0x002931BA, 59 bytes.
// Object helper: if testStatus(FAERIE_FIRE 0x26) return producerID (+0x78)
// nonzero; else if producerID zero return false; else look up producer via
// TheGameLogic findObjectByID (rowed 0x00049DC5) and return its template
// kind byte +0x115 bit 0x20. Evidence: Object offsets template +0x04
// (Object_isAbleToAttack/ObjectScriptStatus), producer +0x78
// (ObjectSetProducer), TheGameLogic at 0x00DFE78C; neighbours
// 0x00292ED0 (ObjectScriptStatus.cpp /O1 /G7) and 0x002931F5
// (ObjectRva002931F5.cpp /O1 /G7) prove Object owner; status 0x26 is
// FAERIE_FIRE per ZH ObjectStatusTypes.h and ObjectScriptStatus.cpp;
// template +0x115 &0x20 matches isAbleToAttack container gate.

typedef bool Bool;

#include "../../Common/GameLogicObjectLookupView.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_FAERIE_FIRE = 0x26
};

#include "../../../Include/Common/ThingTemplate.h"

class Object;


extern GameLogic *TheGameLogic;

#include "object.h"

Bool Object::rva002931BA()
{
	ObjectID producerID = m_producerID;
	if (testStatus(OBJECT_STATUS_FAERIE_FIRE))
	{
		if (producerID == 0)
			goto isFalse;
		goto isTrue;
	}
	if (producerID == 0)
		goto isFalse;
	Object *producer = TheGameLogic->findObjectByID(producerID);
	if (producer != 0 && (producer->m_template->m_kindof[3] & (1U << 13)) != 0)
		goto isTrue;
isFalse:
	return false;
isTrue:
	return true;
}
