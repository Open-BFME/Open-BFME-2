// cl: /GX /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/moduledata
// stlport
// OneRingPenaltyUpdate wandering step. Target identity/layout evidence is
// documented below; the original private method name remains unknown.
// ?rva00499D23@OneRingPenaltyUpdate@@AAEXXZ retail 0x00499D23..0x00499E98
// (373 bytes). Private helper on the primary this that update 0x00499E98
// runs while the ring is worn with the +0x24 object id set. WorldBuilder
// twin 0x011FA7D0 (OneRingPenaltyUpdate.cpp; its GameLogicRandomValueReal
// names the file at line 184). Looks up the penalty object by id
// (GameLogic::findObjectByID 0x00049DC5): once the frame reaches start
// (+0x28 plus data +0x0C) plus the data's +0x10 frames it is moved onto the
// owner (Thing::setPosition 0x0030AA80) and rva00499C6C 0x00499C6C ends the
// penalty. Before that while its AI (Object +0x258) answers vtable +0x1B8
// it wanders: the angle at +0x2C turns by a random value in [-PI/2 PI/2]
// and the AI (AICommandInterface at AI +0x20) is sent to the owner's
// position offset by Cos/Sin of the angle times a radius shrinking from the
// data's +0x18 to half of it over the window (z from TheTerrainLogic's
// getGroundHeight vtable +0x18).
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef unsigned int UnsignedInt;

float Cos(float val);
float Sin(float val);
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../Common/Thing/thing.h"
#include "../object.h"


#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
// Retail loads the primary table's slot 6 after Sin and before the Y addition.
// A single-inheritance receiver keeps MSVC 7.1's member pointer one code word;
// TerrainLogic itself has multiple bases and a wider member-pointer format.
// This ABI view has no receiver adjustment and does not declare TerrainLogic.
class TerrainGroundCallReceiver {};
typedef Real (TerrainGroundCallReceiver::*GroundHeightMember)(Real,Real,Coord3D *) const;
struct TerrainGroundCallTable {GroundHeightMember slots[7];};
typedef char GroundMemberWidth[sizeof(GroundHeightMember)==4?1:-1];
extern GameLogic *TheGameLogic;

#include "OneRingPenaltyModuleDataView.h"

#include "../../../../Include/GameLogic/Module/OneRingPenaltyUpdate.h"

void OneRingPenaltyUpdate::rva00499D23()
{
	const OneRingPenaltyUpdateModuleData *oneRingPenaltyUpdateModuleData = reinterpret_cast<const OneRingPenaltyUpdateModuleData *>(getModuleData());
	Object *obj = m_object;
	GameLogic *logic = TheGameLogic;
	Object *ringer = logic->findObjectByID(m_24);
	UnsignedInt now = logic->getFrame();
	UnsignedInt start = m_28 + oneRingPenaltyUpdateModuleData->m_ringTimeBeforeSpawning;
	UnsignedInt end = start + oneRingPenaltyUpdateModuleData->m_timeSpentRoamingAround;

	if (now >= end)
	{
		ringer->setPosition(obj->getPosition());
		rva00499C6C();
		return;
	}

	if (ringer && ringer->getAI() && ringer->getAI()->isIdle())
	{
		Coord3D pos;
		pos.x = obj->getPosition()->x;
		pos.y = obj->getPosition()->y;
		m_2C += GetGameLogicRandomValueReal(-1.5707964f, 1.5707964f,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\OneRingPenaltyUpdate.cpp",
			184);
		Real radius;
		if (now - start == 0)
		{
			radius = oneRingPenaltyUpdateModuleData->m_startingDistanceFromMe;
		}
		else
		{
			Real startRadius = oneRingPenaltyUpdateModuleData->m_startingDistanceFromMe;
			Real ratio = (Real)(now - start) / (Real)(end - start);
			radius = startRadius + ratio * (oneRingPenaltyUpdateModuleData->m_startingDistanceFromMe / 2.0f - startRadius);
		}
		pos.x += Cos(m_2C) * radius;
		Real sine = Sin(m_2C);
		TerrainLogic *terrain = TheTerrainLogic;
		const TerrainGroundCallTable &ground = **reinterpret_cast<TerrainGroundCallTable **>(terrain);
		pos.y += sine * radius;
		pos.z = (reinterpret_cast<TerrainGroundCallReceiver *>(terrain)->*ground.slots[6])(pos.x, pos.y, 0);
		ringer->getAI()->aiMoveToPosition(&pos, CMD_FROM_AI);
	}
}
