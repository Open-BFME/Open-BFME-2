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
#include "../../../Include/GameLogic/Rva002A9BBD.h"

#include "../../../Include/Common/Player.h"
// Zero Hour's inline Player accessors, as unit-local helpers over the header's members.
static inline Int getMpStartIndex(const Player *player) { return player->m_mpStartIndex; }
static inline Player *getCurrentEnemy(Player *player) { return (Player *)((Rva002A9BBD *)player)->rva002A9BBD(); }

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/GameLogic/ScriptEngine.h"

PolygonTrigger *ScriptEngine::getQualifiedTriggerAreaByName(AsciiString name)
{
	if (name.compare(MY_INNER_PERIMETER) == 0 || name.compare(MY_OUTER_PERIMETER) == 0) {
		if (m_currentPlayer) {
			Int ndx = getMpStartIndex(m_currentPlayer) + 1;
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
			Player *enemy = getCurrentEnemy(getCurrentPlayer());
			if (enemy) {
				mpNdx = getMpStartIndex(enemy) + 1;
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
