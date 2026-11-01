// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?drawSkirmishAIStats@W3DDisplay@@QAEXXZ, retail 0x0004A1B8..0x0004A3C4
// (524 bytes, RET 0): the skirmish AI debug page. drawCurrentDebugDisplay
// (W3DDisplayDebugPlaceholders.cpp) calls it for SkirmishAIDebugDisplay, whose
// retail message says it is "a placeholder for drawSkirmishAIStats()";
// WorldBuilder 0x0096CC30 W3DDisplay::drawSkirmishAIStats (W3DDisplay.cpp,
// assert dTree at line 3038, callgraph match) agrees.
// Target facts: for every player passing 0x002AA245, the skirmish AI manager
// (global 0x009FEEF8, owner name TheSkirmishAIManager) record 0x002A8AB1 lists markers
// at +0x164 -> +0x20 whose position (+4) and radius (+0x14) become red spheres,
// and the 0x002A8F24 owner's tree at +0x10 (pointer array +0x10..+0x14,
// positions by 0x00049D20, radius at element +4) draws spheres in the player
// colour (+0x280), all through slot +0x38 of TheDisplay +0x2C. The page string
// at this +0x1CC is then coloured white on black, placed at (3, 3) and sized.
// The marker, tree and colour names are structural inferences; the sphere
// slot's last two arguments are unnamed. The position is copied into a local
// Vector3 (all three loads precede the matrix stores) and the marker vector is
// read through a reference (begin after end via +0x20), as retail does.

class Player;
class PlayerList
{
public:
	Player *getNthPlayer(int index);
	char m_pad00[0x14];
	int m_playerCount;			// +0x14
};
extern PlayerList *ThePlayerList;

class Player
{
public:
	bool rva002AA245() const;
	char m_pad00[0x280];
	int m_color;				// +0x280
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class Vector4
{
public:
	float X, Y, Z, W;
	void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
};

class Matrix3D
{
public:
	// Matrix3DO1Inlines owns the translation constructor; use its inlined Set here.
	void Set(const Vector3 &position)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, position.X);
		Row[1].Set(0.0f, 1.0f, 0.0f, position.Y);
		Row[2].Set(0.0f, 0.0f, 1.0f, position.Z);
	}
	Vector4 Row[3];
};

struct SkirmishAIStatsMarker
{
	char m_pad00[4];
	Vector3 m_position;			// +0x04
	char m_pad10[4];
	float m_radius;				// +0x14
};

struct SkirmishAIStatsMarkerVector
{
	SkirmishAIStatsMarker **begin() const { return m_begin; }
	SkirmishAIStatsMarker **end() const { return m_end; }
	SkirmishAIStatsMarker **m_begin;
	SkirmishAIStatsMarker **m_end;
	SkirmishAIStatsMarker **m_capacity;
};

struct SkirmishAIStatsMarkerList
{
	char m_pad00[0x20];
	SkirmishAIStatsMarkerVector m_markers;	// +0x20
};

struct Rva002A8AB1Record
{
	char m_pad000[0x164];
	SkirmishAIStatsMarkerList *m_markers;	// +0x164
};

struct SkirmishAIStatsNode
{
	char m_pad00[4];
	float m_radius;				// +0x04
};

class Rva00049D20
{
public:
	void *rva00049D20(void *out, int index);
	unsigned int size() const { return m_end - m_begin; }
	float getRadius(int index) const { return m_begin[index]->m_radius; }
	char m_pad00[0x10];
	SkirmishAIStatsNode **m_begin;	// +0x10
	SkirmishAIStatsNode **m_end;	// +0x14
};

struct SkirmishAIStatsOwner
{
	char m_pad00[0x10];
	Rva00049D20 *m_tree;		// +0x10
};

#include "../../../../GameEngine/Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

class SkirmishAIStatsDebugDraw
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34();
	virtual void drawSphere(const Matrix3D &transform, float radius, int color, int a, int b);	// +0x38
};

struct SkirmishAIStatsDisplayView
{
	char m_pad00[0x2C];
	SkirmishAIStatsDebugDraw *m_debugDraw;	// +0x2C
};
class Display;
extern Display *TheDisplay;

class SkirmishAIStatsString
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24();
	virtual void setColor(int color, int dropColor);			// +0x28
	virtual void slot2c(); virtual void slot30(); virtual void slot34();
	virtual void place(int x, int y, int width, int height);	// +0x38
	virtual void getSize(int *width, int *height);			// +0x3C
};

#define GameMakeColor(r, g, b, a) ((int)(((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

class W3DDisplay
{
public:
	void drawSkirmishAIStats();
private:
	char m_pad000[0x1CC];
	SkirmishAIStatsString *m_skirmishAIStrings[1];	// +0x1CC
};

void W3DDisplay::drawSkirmishAIStats()
{
	int width, height;
	for (int i = 0; i < ThePlayerList->m_playerCount; ++i) {
		Player *player = ThePlayerList->getNthPlayer(i);
		if (!player->rva002AA245())
			continue;
		Rva002A8AB1Record *record = TheSkirmishAIManager->rva002A8AB1(player);
		if (record) {
			const SkirmishAIStatsMarkerVector &markers = record->m_markers->m_markers;
			SkirmishAIStatsMarker **end = markers.end();
			for (SkirmishAIStatsMarker **it = markers.begin(); it != end; ++it) {
				Vector3 pos = (*it)->m_position;
				Matrix3D tm;
				tm.Set(pos);
				((SkirmishAIStatsDisplayView *)TheDisplay)->m_debugDraw->drawSphere(tm, (*it)->m_radius, GameMakeColor(255, 0, 0, 255), 0, 1);
			}
		}
		if (TheSkirmishAIManager->rva002A8F24(player)) {
			Rva00049D20 *dTree = ((SkirmishAIStatsOwner *)TheSkirmishAIManager->rva002A8F24(player))->m_tree;
			for (unsigned int j = 0; j < dTree->size(); ++j) {
				Vector3 tmp;
				Vector3 pos = *(Vector3 *)dTree->rva00049D20(&tmp, j);
				Matrix3D tm;
				tm.Set(pos);
				((SkirmishAIStatsDisplayView *)TheDisplay)->m_debugDraw->drawSphere(tm, dTree->getRadius(j), player->m_color, 0, 1);
			}
		}
	}
	int x = 3;
	int y = 3;
	int color = GameMakeColor(255, 255, 255, 255);
	int dropColor = GameMakeColor(0, 0, 0, 255);
	for (int k = 0; k < 1; ++k) {
		m_skirmishAIStrings[k]->setColor(color, dropColor);
		m_skirmishAIStrings[k]->place(x, y, 1, 1);
		m_skirmishAIStrings[k]->getSize(&width, &height);
		y += height;
	}
}
