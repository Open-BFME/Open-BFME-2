// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ScriptEngine::doNamedMapReveal (0x003577DA, 195B) and undoNamedMapReveal
// (0x0035789D, 195B). Zero Hour's pair (BFME 1 donor
// ScriptEngineNamedMapReveal.cpp) reworked for BFME 2:
//   - the reveal list (begin/end at this+0x1A49C/+0x1A4A0, 0x14-byte
//     entries) is searched by the name's CRC (Rva003ECA13Get 0x003ECA13),
//     not by string compare;
//   - each entry carries a kind at +0x10: 0 reveals a radius around the
//     waypoint named at +0x04 (TheTerrainLogic slot 0x88, location at
//     waypoint+0x0C, radius at +0x08), 1 reveals the bounding rect of the
//     trigger area named at +0x04 (getQualifiedTriggerAreaByName 0x0035768D,
//     rect via 0x002E3954);
//   - the player mask comes from rva00357475 0x00357475 on the entry's
//     player name at +0x0C, through TheScriptEngine (the global, as retail
//     loads it) rather than this.
// The shroud calls go to TheShroudManager (0x00DFE74C): do uses the rowed
// rect reveal 0x00739AF0 and the radius reveal 0x00739A30, undo the rowed
// 0x00739CA0 and 0x00739BE0. Unwind-free in retail: no /GX.
#include "ascii_string.h"

typedef bool Bool;

unsigned long Rva003ECA13Get(const AsciiString &name);

struct Pair00739BE0
{
	float x;
	float y;
};

struct FloatRect0073CE30
{
	float x1;
	float y1;
	float x2;
	float y2;
};

class Waypoint
{
public:
	char m_pad00[0x0C];
	Pair00739BE0 m_location;	// +0x0C
};

class PolygonTrigger
{
public:
	void rva002E3954(FloatRect0073CE30 *rect);
	char m_pad00[0x38];
	int m_38;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual Waypoint *getWaypointByName(const AsciiString &name);
};
extern TerrainLogic *TheTerrainLogic;

class Rva00739AF0
{
public:
	void rva00739AF0(FloatRect0073CE30 *world, int extra, unsigned int mask);
};
class Rva00739A30
{
public:
	void rva00739A30(Pair00739BE0 *p, float f, int mask);
};
class Rva00739CA0
{
public:
	void rva00739CA0(FloatRect0073CE30 *world, int extra, unsigned int mask);
};
class Rva00739BE0
{
public:
	void rva00739BE0(Pair00739BE0 *p, float f, int mask);
};

class PartitionManager;
extern PartitionManager *TheShroudManager;

struct NamedReveal
{
	unsigned long m_nameCRC;	// +0x00
	AsciiString m_name;			// +0x04 waypoint or trigger area
	float m_radius;				// +0x08
	AsciiString m_playerName;	// +0x0C
	int m_kind;					// +0x10
};

class ScriptEngine
{
public:
	void doNamedMapReveal(const AsciiString &revealName);
	void undoNamedMapReveal(const AsciiString &revealName);
	int rva00357475(const AsciiString &name, Bool *matchedSpecialName);
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
private:
	char m_pad[0x1A49C];
	NamedReveal *m_namedRevealsBegin;	// +0x1A49C
	NamedReveal *m_namedRevealsEnd;		// +0x1A4A0
};
extern ScriptEngine *TheScriptEngine;

void ScriptEngine::doNamedMapReveal(const AsciiString &revealName)
{
	unsigned long crc = Rva003ECA13Get(revealName);
	NamedReveal *it = m_namedRevealsBegin;
	NamedReveal *end = m_namedRevealsEnd;
	for (; it != end; ++it)
	{
		if (it->m_nameCRC == crc)
		{
			int mask = TheScriptEngine->rva00357475(it->m_playerName, 0);
			switch (it->m_kind)
			{
				case 0:
				{
					Waypoint *way = TheTerrainLogic->getWaypointByName(it->m_name);
					if (way)
						((Rva00739A30 *)TheShroudManager)->rva00739A30(&way->m_location, it->m_radius, mask);
					break;
				}
				case 1:
				{
					PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(it->m_name);
					if (trigger)
					{
						FloatRect0073CE30 rect;
						trigger->rva002E3954(&rect);
						((Rva00739AF0 *)TheShroudManager)->rva00739AF0(&rect, (int)&trigger->m_38, mask);
					}
					break;
				}
			}
			return;
		}
	}
}

void ScriptEngine::undoNamedMapReveal(const AsciiString &revealName)
{
	unsigned long crc = Rva003ECA13Get(revealName);
	NamedReveal *it = m_namedRevealsBegin;
	NamedReveal *end = m_namedRevealsEnd;
	for (; it != end; ++it)
	{
		if (it->m_nameCRC == crc)
		{
			int mask = TheScriptEngine->rva00357475(it->m_playerName, 0);
			switch (it->m_kind)
			{
				case 0:
				{
					Waypoint *way = TheTerrainLogic->getWaypointByName(it->m_name);
					if (way)
						((Rva00739BE0 *)TheShroudManager)->rva00739BE0(&way->m_location, it->m_radius, mask);
					break;
				}
				case 1:
				{
					PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(it->m_name);
					if (trigger)
					{
						FloatRect0073CE30 rect;
						trigger->rva002E3954(&rect);
						((Rva00739CA0 *)TheShroudManager)->rva00739CA0(&rect, (int)&trigger->m_38, mask);
					}
					break;
				}
			}
			return;
		}
	}
}
