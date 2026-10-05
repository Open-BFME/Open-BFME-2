// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?scatterToNearbyPosition@TunnelContain@@IAEXPAVObject@@@Z @0x0047E16B 253B.
//
// TunnelContain override that scatters an exiting rider to a random nearby
// position: random angle in [0, 2*PI), random distance in
// [minRadius, minRadius * 1.5], position from Cos/Sin plus the container
// center, z from the terrain, then either an AI-driven move (through the
// container position, ignoring the container as an obstacle) or a direct
// setPosition when the rider has no AI.
//
// Donor: ZH GeneralsMD TunnelContain::scatterToNearbyPosition (TunnelContain.cpp).
// Retail proves the home TU is TunnelContain.cpp, not OpenContain.cpp: both
// GameLogicRandomValueReal sites pass __FILE__ = the TunnelContain.cpp path
// (VA 0x00C477C8) with lines 337 and 344. The assignment's OpenContain name
// is the drift classifier attributing ZH OpenContain.cpp's same-named body;
// the TunnelContain override is the body retail carries.
//
// BFME2 deltas from the ZH donor, all read off retail 0x0047E16B:
// - z comes from TerrainLogic::getGroundHeight(x, y) (virtual slot 6), not
//   getLayerHeight(x, y, layer): only three argument slots (x, y, NULL).
// - maxRadius is minRadius * 1.5f (mulss against the 1.5f literal), not
//   minRadius + minRadius / 2.0f (which would emit divss+addss).
// - Object layout is BFME2's (ObjectInterfaceSlots.cpp precedent): position
//   at +0x38, GeometryInfo at +0xA8 with the bounding radius float at +0x10
//   (hence the [esi+0xB8] load); ZH headers place that radius at +0xC0, so
//   the TU uses a view-local layout instead of the ZH Object headers.
// - The rider's AI interface sits at +0x258 and its command interface at
//   AI+0x20 (ZH spells the latter +0x1C); both are applied as explicit
//   offsets with the real callee declarations, so every call resolves to
//   the already-rowed body (setOrientation 0x0030AB9D, setPosition
//   0x0030AA80, ignoreObstacle 0x00268D88, aiMoveToPosition 0x0026C26D,
//   GetGameLogicRandomValueReal 0x00234092, Cos/Sin 0x002FBC0/0x002FBB0).

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Object;
class AIUpdateInterface;

class Thing
{
public:
	void setOrientation(Real angle);
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	const Coord3D *bfmePosition() const { return (const Coord3D *)((const char *)this + 0x38); }
	Real bfmeBoundingRadius() const { return *(const Real *)((const char *)this + 0xB8); }
	AIUpdateInterface *bfmeAI() { return *(AIUpdateInterface **)((char *)this + 0x258); }
};

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
};

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType src);
};

class TerrainLogic
{
public:
	virtual void bfmeSlot0() = 0;
	virtual void bfmeSlot1() = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void bfmeSlot5() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) = 0;
};
extern TerrainLogic *TheTerrainLogic;

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
extern char g_00C477C8[];
float cos(float v);
float sin(float v);

#define PI 3.14159265f

class TunnelContain
{
protected:
	void scatterToNearbyPosition(Object *rider);

private:
	char m_pad00[8];
	Object *m_object; // +0x08
};

void TunnelContain::scatterToNearbyPosition(Object *rider)
{
	Object *theContainer = m_object;

	Real angle = GetGameLogicRandomValueReal(0.0f, 2.0f * PI, g_00C477C8, 0x151);

	Real minRadius = theContainer->bfmeBoundingRadius();
	const Coord3D *containerPos = theContainer->bfmePosition();
	Real dist = GetGameLogicRandomValueReal(minRadius, minRadius * 1.5f, g_00C477C8, 0x158);

	Coord3D pos;
	pos.x = dist * cos(angle) + containerPos->x;
	pos.y = dist * sin(angle) + containerPos->y;
	pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);

	// set orientation
	rider->setOrientation(angle);

	AIUpdateInterface *ai = rider->bfmeAI();
	if (ai)
	{
		// set position of the object at center of building and move them toward pos
		rider->setPosition(containerPos);
		ai->ignoreObstacle(theContainer);
		((AICommandInterface *)((char *)ai + 0x20))->aiMoveToPosition(&pos, CMD_FROM_AI);
	}
	else
	{
		// no ai, just set position at the target pos
		rider->setPosition(&pos);
	}
}
