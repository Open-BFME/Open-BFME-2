// ?rva00499D23@OneRingPenaltyUpdate@@AAEXXZ
// partial score=0.9856523681858802 date=2026-10-10
// ?rva00499D23@OneRingPenaltyUpdate@@AAEXXZ
// partial score=0.98 date=2026-10-09
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD
// NEAR draft for Code/GameEngine/Source/GameLogic/Object/Update/OneRingPenaltyUpdateRva00499D23.cpp
// (relative includes assume that path). Remaining diffs are scheduling only:
// retail loads start as [esi+0x28] then adds [ebx+0xC] (cl swaps the two
// loads whatever the source order) and fetches TheTerrainLogic's vtable
// before the pos.y fadd instead of after the argument pushes.
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
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
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

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

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

class AIUpdateInterface : public Rva00499D23AIBase, public AICommandInterface
{
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	const Coord3D *getPosition() const { return &m_pos; }

private:
	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai; // +0x258
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const; // +0x18
};
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;

struct OneRingPenaltyUpdateModuleData
{
	unsigned char m_pad00[0x0C];
	UnsignedInt m_0C; // +0x0C
	UnsignedInt m_10; // +0x10
	UnsignedInt m_14; // +0x14
	Real m_18; // +0x18
};

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
	Object *obj = m_object;
	const OneRingPenaltyUpdateModuleData *d = m_moduleData;
	GameLogic *logic = TheGameLogic;
	Object *ringer = logic->findObjectByID(m_24);
	UnsignedInt now = logic->getFrame();
	UnsignedInt start = d->m_0C + m_28;
	UnsignedInt end = start + d->m_10;

	if (now >= end)
	{
		ringer->setPosition(obj->getPosition());
		rva00499C6C();
		return;
	}

	if (ringer && ringer->getAI() && ringer->getAI()->slot110())
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
			radius = d->m_18;
		}
		else
		{
			Real startRadius = d->m_18;
			Real ratio = (Real)(now - start) / (Real)(end - start);
			radius = startRadius + ratio * (d->m_18 / 2.0f - startRadius);
		}
		pos.x += Cos(m_2C) * radius;
		Real yOffset=Sin(m_2C)*radius; _ReadWriteBarrier(); pos.y+=yOffset;
		pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
		ringer->getAI()->aiMoveToPosition(&pos, CMD_FROM_AI);
	}
}
