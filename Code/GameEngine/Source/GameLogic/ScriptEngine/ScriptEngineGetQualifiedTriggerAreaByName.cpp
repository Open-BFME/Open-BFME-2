// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual PolygonTrigger *getTriggerAreaByName(const AsciiString &name); // +0x9C
};
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
