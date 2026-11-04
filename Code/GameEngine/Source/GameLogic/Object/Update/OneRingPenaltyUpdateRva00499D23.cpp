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

class Rva00499D23AIBase
{
public:
	virtual void slot000(); virtual void slot001(); virtual void slot002(); virtual void slot003();
	virtual void slot004(); virtual void slot005(); virtual void slot006(); virtual void slot007();
	virtual void slot008(); virtual void slot009(); virtual void slot010(); virtual void slot011();
	virtual void slot012(); virtual void slot013(); virtual void slot014(); virtual void slot015();
	virtual void slot016(); virtual void slot017(); virtual void slot018(); virtual void slot019();
	virtual void slot020(); virtual void slot021(); virtual void slot022(); virtual void slot023();
	virtual void slot024(); virtual void slot025(); virtual void slot026(); virtual void slot027();
	virtual void slot028(); virtual void slot029(); virtual void slot030(); virtual void slot031();
	virtual void slot032(); virtual void slot033(); virtual void slot034(); virtual void slot035();
	virtual void slot036(); virtual void slot037(); virtual void slot038(); virtual void slot039();
	virtual void slot040(); virtual void slot041(); virtual void slot042(); virtual void slot043();
	virtual void slot044(); virtual void slot045(); virtual void slot046(); virtual void slot047();
	virtual void slot048(); virtual void slot049(); virtual void slot050(); virtual void slot051();
	virtual void slot052(); virtual void slot053(); virtual void slot054(); virtual void slot055();
	virtual void slot056(); virtual void slot057(); virtual void slot058(); virtual void slot059();
	virtual void slot060(); virtual void slot061(); virtual void slot062(); virtual void slot063();
	virtual void slot064(); virtual void slot065(); virtual void slot066(); virtual void slot067();
	virtual void slot068(); virtual void slot069(); virtual void slot070(); virtual void slot071();
	virtual void slot072(); virtual void slot073(); virtual void slot074(); virtual void slot075();
	virtual void slot076(); virtual void slot077(); virtual void slot078(); virtual void slot079();
	virtual void slot080(); virtual void slot081(); virtual void slot082(); virtual void slot083();
	virtual void slot084(); virtual void slot085(); virtual void slot086(); virtual void slot087();
	virtual void slot088(); virtual void slot089(); virtual void slot090(); virtual void slot091();
	virtual void slot092(); virtual void slot093(); virtual void slot094(); virtual void slot095();
	virtual void slot096(); virtual void slot097(); virtual void slot098(); virtual void slot099();
	virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
	virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
	virtual void slot108(); virtual void slot109();
	virtual bool slot110(); // +0x1B8

private:
	char m_pad04[0x20 - 0x04];
};


#include "../object.h"


class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const; // +0x18
};
extern TerrainLogic *TheTerrainLogic;
// MSVC 7.1 represents this single-inheritance member pointer as one code
// address. Retail's primary vtable slot is that same four-byte code address;
// no receiver adjustment is required. This checked ABI view binds the table
// read after Sin and before the Y addition, preserving retail's x87 scheduling.
// It describes the witnessed slot, not unobserved TerrainLogic methods.
typedef Real (TerrainLogic::*GroundHeightMember)(Real,Real,Coord3D *) const;
struct TerrainGroundCallTable {GroundHeightMember slots[7];};
typedef char GroundMemberWidth[sizeof(GroundHeightMember)==4?1:-1];
extern GameLogic *TheGameLogic;

#include "OneRingPenaltyModuleDataView.h"

class OneRingPenaltyUpdate
{
private:
	void rva00499C6C();
	void rva00499D23();

	void *m_vtbl;
	const OneRingPenaltyUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	ObjectID m_24; // +0x24
	UnsignedInt m_28; // +0x28
	Real m_2C; // +0x2C
};

void OneRingPenaltyUpdate::rva00499D23()
{
	const OneRingPenaltyUpdateModuleData *oneRingPenaltyUpdateModuleData = m_moduleData;
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
		pos.z = (terrain->*ground.slots[6])(pos.x, pos.y, 0);
		ringer->getAI()->aiMoveToPosition(&pos, CMD_FROM_AI);
	}
}
