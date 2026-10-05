// ?chooseGoodLocomotorFromCurrentSet@AIUpdateInterface@@QAEXXZ
// partial score=0.98 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?chooseGoodLocomotorFromCurrentSet@AIUpdateInterface@@QAEXXZ @0x00263FA7 194B
// BFME2 AIUpdateInterface::chooseGoodLocomotorFromCurrentSet. Ported from
// Open-BFME-1 game/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// chooseGoodLocomotorFromCurrentSet plus the split donor file
// AIUpdate_chooseGoodLocomotorFromCurrentSet.cpp. Retail keeps the donor
// prev/cur shape and the three flag clears at loco+0x44, but chooses the
// fallback surfaces from the object template and a group query and marks
// radar data instead of recomputing group speed. Evidence: pinned name,
// callers at 0x00268B53 0x0026A3EB 0x0036B58A, rowed callees 0x0028B511
// 0x002E74C6 0x001E48E8 0x00313EAF. Row 0x002E74C6 declares void but retail
// leaves the inner find result in eax and this body tests it so it is
// declared here as returning Locomotor.
// ?rva0028B511@Object@@QBEHXZ present-unmatched
// ?friend_getRadarData@Object@@QAEPAVRadarObject@@XZ present-unmatched
// ?rva001E48E8@Rva001E48E8@@QAEPAXI@Z present-unmatched

typedef int Int;
typedef unsigned int UnsignedInt;
#define NULL 0

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND_ENUM = 0
};

class Locomotor
{
public:
	unsigned char m_pad00[0x44]; // +0x00..0x44
	UnsignedInt m_flags; // +0x44
};

class Rva001E48E8ElemInner
{
public:
	char _00[0x14];
	UnsignedInt m_14;
};

class Rva001E48E8Elem
{
public:
	char _00[4];
	Rva001E48E8ElemInner *m_04;
};

class Rva001E48E8
{
public:
	void *rva001E48E8(UnsignedInt mask);
	char _00[4];
	Rva001E48E8Elem **m_04;
	Rva001E48E8Elem **m_08;
};

class Pathfinder
{
public:
	Locomotor *rva002E74C6(PathfindLayerEnum layer, Rva001E48E8 *set, const Coord3D *pos);
};

class ThingTemplate
{
public:
	char _00[0x11F]; // +0x00..0x11F
	unsigned char m_11F; // +0x11F
};

class RadarObject
{
public:
	char _00[0x0C]; // +0x00..0x0C
	unsigned char m_0C; // +0x0C
};

class GroupHolder
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
	virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64();
	virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual void slot75(); virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83(); virtual void slot84();
	virtual void slot85(); virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89();
	virtual void slot90(); virtual void slot91(); virtual void slot92(); virtual void slot93(); virtual void slot94();
	virtual void slot95(); virtual void slot96();
	virtual int slot97();
};

class Object
{
public:
	Int rva0028B511() const;
	RadarObject *friend_getRadarData();
	const Coord3D *getPosition() const { return &m_position; }
	char _00[4]; // +0x00..0x04
	ThingTemplate *m_template; // +0x04
	char _08[0x38 - 0x08]; // +0x08..0x38
	Coord3D m_position; // +0x38
	char _44[0x258 - 0x44]; // +0x44..0x258
	GroupHolder *m_258; // +0x258
};

class AI
{
public:
	char m_pad[0x10]; // +0x00..0x10
	Pathfinder *m_pathfinder; // +0x10
	Pathfinder *pathfinder() { return m_pathfinder; }
};

extern AI *g_Va009FF0F8;

class AIUpdateInterface
{
public:
	void chooseGoodLocomotorFromCurrentSet();
private:
	char _00[8]; // +0x00..0x08
	Object *m_object; // +0x08
	char _0C[0x1CC - 0x0C]; // +0x0C..0x1CC
	Rva001E48E8 m_locomotorSet; // +0x1CC
	char _pad[0x1F0 - 0x1CC - 12]; // +0x1D8..0x1F0
	Locomotor *m_curLocomotor; // +0x1F0
};

// ?chooseGoodLocomotorFromCurrentSet@AIUpdateInterface@@QAEXXZ present-unmatched
void AIUpdateInterface::chooseGoodLocomotorFromCurrentSet()
{
	Locomotor *prevLoco = m_curLocomotor;
	Object *obj = m_object;
	Pathfinder *pf = g_Va009FF0F8->pathfinder();
	Locomotor *newLoco = pf->rva002E74C6((PathfindLayerEnum)obj->rva0028B511(), &m_locomotorSet, obj->getPosition());
	if (newLoco == NULL)
	{
		if (prevLoco != NULL)
			newLoco = prevLoco;
		else
		{
			if (obj->m_template->m_11F & 0x80)
				newLoco = (Locomotor *)m_locomotorSet.rva001E48E8(0x80);
			else
			{
				GroupHolder *group = obj->m_258;
				if (group != NULL && group->slot97())
					newLoco = (Locomotor *)m_locomotorSet.rva001E48E8(8);
				else
					newLoco = (Locomotor *)m_locomotorSet.rva001E48E8(1);
			}
		}
	}
	m_curLocomotor = newLoco;
	if (prevLoco != m_curLocomotor)
	{
		if (m_object->friend_getRadarData())
			m_object->friend_getRadarData()->m_0C = 1;
		m_curLocomotor->m_flags &= ~8u;
		m_curLocomotor->m_flags &= ~0x10u;
		m_curLocomotor->m_flags &= ~0x40u;
	}
}
