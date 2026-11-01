// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?getQualifiedTriggerAreaByName@ScriptEngine@@QAEPAVPolygonTrigger@@VAsciiString@@@Z
// retail 0x0035768D (333B). Zero Hour's ScriptEngine::getQualifiedTriggerAreaByName
// (ScriptEngine.cpp): "[Skirmish]My/Enemy Inner/Outer Perimeter" become
// "InnerPerimeter<n>" / "OuterPerimeter<n>" for the current player's (or its
// current enemy's) start index + 1, then the terrain logic looks the area up
// and a missing one is reported. BFME 2 offsets: the current player at
// ScriptEngine+0x1A130, the start index at Player+0x2E0, the lookup is
// TerrainLogic vtable slot 0x9C; the current enemy is the rowed 0x002A9BBD.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

#define MY_INNER_PERIMETER "[Skirmish]MyInnerPerimeter"
#define MY_OUTER_PERIMETER "[Skirmish]MyOuterPerimeter"
#define ENEMY_INNER_PERIMETER "[Skirmish]EnemyInnerPerimeter"
#define ENEMY_OUTER_PERIMETER "[Skirmish]EnemyOuterPerimeter"
#define INNER_PERIMETER "InnerPerimeter"
#define OUTER_PERIMETER "OuterPerimeter"

class PolygonTrigger;

// The rowed getter at 0x002A9BBD keeps its address-derived spelling.
class Rva002A9BBD
{
public:
	void *rva002A9BBD();
};

class Player
{
public:
	Int getMpStartIndex() const { return m_mpStartIndex; }
	Player *getCurrentEnemy() { return (Player *)((Rva002A9BBD *)this)->rva002A9BBD(); }

private:
	unsigned char m_pad000[0x2E0];
	Int m_mpStartIndex; // +0x2E0
};

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

class ScriptEngine
{
public:
	Player *getCurrentPlayer();
	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);

private:
	unsigned char m_pad00[0x1A130];
	Player *m_currentPlayer; // +0x1A130
};

PolygonTrigger *ScriptEngine::getQualifiedTriggerAreaByName(AsciiString name)
{
	if (name.compare(MY_INNER_PERIMETER) == 0 || name.compare(MY_OUTER_PERIMETER) == 0) {
		if (m_currentPlayer) {
			Int ndx = m_currentPlayer->getMpStartIndex() + 1;
			if (name.compare(MY_INNER_PERIMETER) == 0) {
				name.format("%s%d", INNER_PERIMETER, ndx);
			} else {
				name.format("%s%d", OUTER_PERIMETER, ndx);
			}
		} else {
			return 0;
		}
	} else if (name.compare(ENEMY_INNER_PERIMETER) == 0 || name.compare(ENEMY_OUTER_PERIMETER) == 0) {
		Int mpNdx;
		mpNdx = -1;
		if (m_currentPlayer) {
			Player *enemy = getCurrentPlayer()->getCurrentEnemy();
			if (enemy) {
				mpNdx = enemy->getMpStartIndex() + 1;
			}
		}
		if (name.compare(ENEMY_INNER_PERIMETER) == 0) {
			name.format("%s%d", INNER_PERIMETER, mpNdx);
		} else {
			name.format("%s%d", OUTER_PERIMETER, mpNdx);
		}
	}
	PolygonTrigger *trig = TheTerrainLogic->getTriggerAreaByName(name);
	if (trig == 0) {
		AsciiString msg = "!!!WARNING!!! Trigger area '";
		((StringBase<char> *)&msg)->concat(*(const StringBase<char> *)&name);
		((StringBase<char> *)&msg)->concat("' not found.");
		AppendDebugMessage(msg, true);
	}

	return trig;
}
