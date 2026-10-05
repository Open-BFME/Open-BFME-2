// ?update@FlammableUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.5 date=2026-10-05
// cl: /O1 /arch:SSE /DNDEBUG /MD /GX
// ?update@FlammableUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048D0BE 977B
// FlammableUpdate::update: slot 0 of the secondary UpdateModule vtable
// (VA 0x00C4C3C8, installed at +0x10 by the rowed ctor 0x0048C64F; the slot
// mapping is proven by DeletionUpdate, whose rowed update@0x0048846F sits in
// the same slot of its own +0x10 table). Ghidra FUN_0088d0be 977B ends where
// 0x0048D48F starts; the bytes are unclaimed and carry no verdicts.
// BFME 2 runs a burning-panic pass ZH never had: when the ignite timer fires
// it grid-scans nearby cells in SSE floats, keeps the nearest
// partition-clear cell the pathfinder accepts, orders the AI there,
// deselects and raises statuses 3/5, then runs the three ZH-style end-frame
// timers (damage/burned/aflame) and the sleep gate. ZH FlammableUpdate.cpp
// (GeneralsMD) is the semantic scaffold for the timer half; retail bytes are
// the arbiter for everything. The ZH-shaped present-unmatched update in the
// home TU is removed in the same commit (else link dupe).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

// BFME 2's status enum is unrecovered; the values below are the exact retail
// immediates, named by value so no ZH identity is implied.
enum ObjectStatusTypes
{
	ST_03 = 3,
	ST_05 = 5,
	ST_11 = 11
};

enum NameKeyType
{
	NK_NONE = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Module;
class BodyModule;
class TerrainLogic;
class AI;
class Pathfinder;
class AIUpdate;
class AIUpdateInterface;
class AICommandInterface;
class NameKeyGenerator;
class GameLogic;
class FlammableUpdateModuleData;
class Rva002918E0Object;
class FlameCleanup00293E50;
class FlammableUpdate;

extern GameLogic *TheGameLogic;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;
extern NameKeyGenerator *TheNameKeyGenerator;
extern int g_Va00DBA4E4;

class Module
{
};

class BodyModule
{
public:
	char m_pad00[0x11F];
	unsigned char m_flag11F;
};

class TerrainLogic
{
public:
	virtual void _s00(); virtual void _s01(); virtual void _s02(); virtual void _s03();
	virtual void _s04(); virtual void _s05(); virtual void _s06(); virtual void _s07();
	virtual void _s08(); virtual void _s09(); virtual void _s10(); virtual void _s11();
	virtual void _s12(); virtual void _s13(); virtual void _s14(); virtual void _s15();
	virtual void _s16(); virtual void _s17(); virtual void _s18();
	virtual Bool queryClear(float x, float z, TerrainLogic *a, TerrainLogic *b, Int c, Int d, Int e);
	virtual void _s20(); virtual void _s21(); virtual void _s22(); virtual void _s23();
	virtual void _s24();
	virtual float queryValue(float x, float z, TerrainLogic *a, TerrainLogic *b, Int c, Int d, Int e);
	virtual void _s26(); virtual void _s27();
};

class Pathfinder
{
public:
	Bool rva002F477E(Object *obj, const Coord3D *from, const Coord3D *to, Int zero);
};

class AI
{
public:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
	char m_pad14[0x2C];
	Int m_40;
};

class AICommandInterface
{
public:
	void rva0026C26D(const Coord3D *pos, Int cmdSource);
};

class AIUpdateInterface
{
public:
	Bool isMoving() const;
};

class AIUpdate
{
public:
	virtual void _s000(); virtual void _s001(); virtual void _s002(); virtual void _s003();
	virtual void _s004(); virtual void _s005(); virtual void _s006(); virtual void _s007();
	virtual void _s008(); virtual void _s009(); virtual void _s010(); virtual void _s011();
	virtual void _s012(); virtual void _s013(); virtual void _s014(); virtual void _s015();
	virtual void _s016(); virtual void _s017(); virtual void _s018(); virtual void _s019();
	virtual void _s020(); virtual void _s021(); virtual void _s022(); virtual void _s023();
	virtual void _s024(); virtual void _s025(); virtual void _s026(); virtual void _s027();
	virtual void _s028(); virtual void _s029(); virtual void _s030(); virtual void _s031();
	virtual void _s032(); virtual void _s033(); virtual void _s034(); virtual void _s035();
	virtual void _s036(); virtual void _s037(); virtual void _s038(); virtual void _s039();
	virtual void _s040(); virtual void _s041(); virtual void _s042(); virtual void _s043();
	virtual void _s044(); virtual void _s045(); virtual void _s046(); virtual void _s047();
	virtual void _s048(); virtual void _s049(); virtual void _s050(); virtual void _s051();
	virtual void _s052(); virtual void _s053(); virtual void _s054(); virtual void _s055();
	virtual void _s056(); virtual void _s057(); virtual void _s058(); virtual void _s059();
	virtual void _s060(); virtual void _s061(); virtual void _s062(); virtual void _s063();
	virtual void _s064(); virtual void _s065(); virtual void _s066(); virtual void _s067();
	virtual void _s068(); virtual void _s069(); virtual void _s070(); virtual void _s071();
	virtual void _s072(); virtual void _s073(); virtual void _s074(); virtual void _s075();
	virtual void _s076(); virtual void _s077(); virtual void _s078(); virtual void _s079();
	virtual void _s080(); virtual void _s081(); virtual void _s082(); virtual void _s083();
	virtual void _s084(); virtual void _s085(); virtual void _s086(); virtual void _s087();
	virtual void _s088(); virtual void _s089(); virtual void _s090(); virtual void _s091();
	virtual void _s092(); virtual void _s093(); virtual void _s094(); virtual void _s095();
	virtual void _s096(); virtual void _s097(); virtual void _s098(); virtual void _s099();
	virtual void _s100(); virtual void _s101(); virtual void _s102(); virtual void _s103();
	virtual void _s104(); virtual void _s105(); virtual void _s106(); virtual void _s107();
	virtual void _s108(); virtual void _s109(); virtual void _s110(); virtual void _s111();
	virtual void _s112(); virtual void _s113(); virtual void _s114(); virtual void _s115();
	virtual void _s116(); virtual void _s117(); virtual void _s118(); virtual void _s119();
	virtual void _s120(); virtual void _s121(); virtual void _s122(); virtual void _s123();
	virtual void _s124(); virtual void _s125(); virtual void _s126(); virtual void _s127();
	virtual void _s128(); virtual void _s129(); virtual void _s130(); virtual void _s131();
	virtual void _s132(); virtual void _s133(); virtual void _s134(); virtual void _s135();
	virtual void _s136(); virtual void _s137(); virtual void _s138(); virtual void _s139();
	virtual void _s140(); virtual void _s141();
	virtual void setCond142(Int v);
public:
	char m_pad04[0x3C9 - 0x04];
	unsigned char m_flag3C9;
};

// Secondary UpdateModule-interface view: this points at obj+0x10, so the
// object and its module data hang at negative offsets while this unit's own
// fields stay positive. Casting through (char *)this keeps each access in a
// single retail memory operand (mov esi,[ecx-8], never a lea).
class FlammableUpdate
{
public:
	virtual UpdateSleepTime update();
	void rva0048C771();
	Int rva0048C50D();
private:
	char m_pad04[0x14];
public:
	UnsignedInt m_field18;
	UnsignedInt m_field1C;
	UnsignedInt m_field20;
private:
	char m_pad24[0x0C];
public:
	unsigned char m_flag30;
private:
	char m_pad31[0x03];
public:
	UnsignedInt m_ignFrame;
private:
	char m_pad38[0x04];
public:
	unsigned char m_flag3C;
};

class Object
{
	friend UpdateSleepTime FlammableUpdate::update(void);
public:
	void setStatus(ObjectStatusTypes bit, Bool flag);
	void rva0028AE6D();
protected:
	Module *findModule(NameKeyType key) const;
public:
	void *m_vptr;
	BodyModule *m_body;
	char m_pad08[0x30];
	Coord3D m_pos;
	char m_pad44[0x114 - 0x44];
	UnsignedInt m_flags114;
	char m_pad118[0x258 - 0x118];
	AIUpdate *m_ai;
};

class GameLogic
{
public:
	void deselectObject(Object *obj, UnsignedInt playerMask, Int affectClient);
};

// BFME2 reads the GameLogic frame at +0x40 (home-TU precedent): a TU-local
// view keeps the +0x40 load inline with no external getFrame reference.
class FlammableGameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame;
};
#define TheGameLogicF (*(FlammableGameLogic **)&TheGameLogic)

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};

class Rva002918E0Object
{
public:
	void set(unsigned char value);
	void rva004B239A(unsigned char a, unsigned char b);
};

class FlameCleanup00293E50
{
public:
	void apply();
};

class FlammableUpdateModuleData
{
public:
	char m_pad00[0x10];
	UnsignedInt m_10;
	char m_pad14[0x20];
	unsigned char m_34;
	char m_pad35[0x05];
	unsigned char m_3A;
	char m_pad3B[0x01];
	float m_f3C;
	float m_40;
	float m_44;
	unsigned char m_48;
};

// ?update@FlammableUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime FlammableUpdate::update(void)
{
	void *pme = *(void**)((char*)this - 8);
	UnsignedInt now = TheGameLogicF->getFrame();
	void *pdata = *(void**)((char*)this - 12);
	register Object *me = (Object*)pme;
	FlammableUpdateModuleData *data = (FlammableUpdateModuleData*)pdata;

	if (m_ignFrame > 0 && now >= m_ignFrame)
	{
		m_ignFrame = 0;
		if (data->m_3A)
		{
			AIUpdate *ai = me->m_ai;
			Coord3D fleePos = { 10000000.0f, 10000000.0f, 10000000.0f };
			if (ai != NULL)
			{
				Coord3D *pos = &me->m_pos;
				float r0 = data->m_40;
				float r1 = data->m_44;
				float x = (float)(Int)(pos->x - r0);
				while (pos->x + r0 >= x)
				{
					float y = (float)(Int)(pos->y - r0);
					while (pos->y + r0 >= y)
					{
						float q = TheTerrainLogic->queryValue(x, y, TheTerrainLogic, TheTerrainLogic, 0, 0, 0);
						if (q > data->m_f3C)
						{
							Coord3D cand;
							cand.z = pos->z;
							cand.x = x;
							cand.y = y;
							float dxFlee = pos->x - fleePos.x;
							float dyFlee = pos->y - fleePos.y;
							float dxCand = pos->x - cand.x;
							float dyCand = pos->y - cand.y;
							float candD2 = dxCand * dxCand + dyCand * dyCand;
							float fleeD2 = dxFlee * dxFlee + dyFlee * dyFlee;
							if (fleeD2 > candD2)
							{
								if (TheAI->m_pathfinder->rva002F477E(me, pos, &cand, 0))
									fleePos = cand;
							}
						}
						y = (float)(Int)(y + r1);
					}
					x = (float)(Int)(x + r1);
				}

				static NameKeyType key = TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
				Module *ent = me->findModule(key);
				if (TheTerrainLogic->queryClear(fleePos.x, fleePos.y, TheTerrainLogic, TheTerrainLogic, 0, 0, 0))
				{
					if (data->m_48)
					{
						if (ai != NULL)
						{
							ai->setCond142(4);
							ai->m_flag3C9 = 1;
							m_flag3C = 1;
						}
					}
					((AICommandInterface*)((char*)ai + 0x20))->rva0026C26D(&fleePos, 1);
					m_flag30 = 1;
					TheGameLogic->deselectObject(me, 0xFFFFF, 1);
					me->setStatus(ST_03, true);
					me->setStatus(ST_05, true);
					if (ent != NULL)
						((Rva002918E0Object*)ent)->set(1);
				}
				else
				{
					if (ent != NULL)
						((Rva002918E0Object*)ent)->rva004B239A(1, 0);
				}
			}
		}
		return UPDATE_SLEEP_NONE;
	}

	BodyModule *body = me->m_body;
	if ((body->m_flag11F & 0x80) == 0)
	{
		if (TheTerrainLogic->queryClear(me->m_pos.x, me->m_pos.z, TheTerrainLogic, TheTerrainLogic, 0, 0, 0))
		{
			AIUpdate *ai2 = me->m_ai;
			if (ai2 != NULL && !((AIUpdateInterface*)ai2)->isMoving())
			{
				Int v = g_Va00DBA4E4 * 3 + TheAI->m_40;
				m_field18 = m_field18 < v ? m_field18 : v;
				m_flag30 = 0;
			}
		}
	}

	if (m_field20 != 0 && now >= m_field20)
	{
		m_field20 = data->m_10 + now;
		((FlammableUpdate*)((char*)this - 0x10))->rva0048C771();
	}
	if (m_field1C != 0 && now >= m_field1C && data->m_34)
	{
		me->setStatus(ST_11, true);
		me->m_flags114 |= 0x10000;
		me->rva0028AE6D();
	}
	if (m_field18 != 0 && now >= m_field18)
	{
		((FlameCleanup00293E50*)((char*)this - 0x10))->apply();
	}
	return (UpdateSleepTime)((FlammableUpdate*)((char*)this - 0x10))->rva0048C50D();
}
