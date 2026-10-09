// ?rva001E8C1B@Rva001E8C1B@@QAEXHHMM@Z
// partial score=0.6 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva001E8C1B@Rva001E8C1B@@QAEXHHMM@Z retail 0x001E8C1B..0x001E8F03
// (744 bytes thiscall ret 0x10; reached from 0x001E7C2B / 0x001E9045). A
// BFME 2 locomotor steering step (WorldBuilder twin 0xAE4BD0 with its
// model-condition BitFlags asserts): it caps the desired speed at
// 0x001E46E1 and aims at the goal (atan2f; normalizeAngle against the
// object's orientation +0x44). When the template allows backing up (+0xD8)
// and the turn is wider than +0x148 * PI (unless the stored point +0x14 is
// beyond +0x140 and the path distance beyond +0x144) it sets model
// condition bit 28 (Object 0x0028AE6D on change) and the reversing bit 7
// at +0x44 and turns away by PI; else it clears both. It then turns toward
// a point 1000 out (0x001E685F) and scales the turn by the turn-rate test
// 0x001E4845 against +0x40. With a positive top speed it moves on through
// 0x001E6007 at the turn-slowed (4/PI) or reversing speed (zero for model
// condition bits 5 or 6 when +0x13C is set); otherwise a settled turn
// idles the AI (AICommandInterface::aiIdle from AI). Names are
// address-derived.

typedef float Real;
typedef bool Bool;

// class-gate: allow Coord3D the canonical data-only header cannot declare the out-of-line GetLengthEstimate2D (rowed 0x000037D1) called below; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real GetLengthEstimate2D() const;
};

extern "C" float __cdecl atan2f(float y, float x);
extern "C" double __cdecl fabs(double x);
Real normalizeAngle(Real angle);
Real Cos(Real angle);
Real Sin(Real angle);

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

struct Rva001E8C1BAIHead
{
	char m_pad[0x20];
};

class AIUpdateInterface : public Rva001E8C1BAIHead, public AICommandInterface
{
};

class Object
{
public:
	void rva0028AE6D();

	char m_pad000[0x38];
	Coord3D m_pos; // +0x38
	Real m_orientation; // +0x44
	char m_pad048[0x11c - 0x48];
	unsigned int m_modelConditions; // +0x11C
	char m_pad120[0x258 - 0x120];
	AIUpdateInterface *m_ai; // +0x258
};

class Rva001E46E1
{
public:
	Real rva001E46E1(Object *obj);
	Real rva001E4845(Object *obj);
};

class Rva001E685F
{
public:
	void rva001E685F(int obj, int pos, int arg);
};

class Rva001E6007
{
public:
	void rva001e6007(unsigned int obj, unsigned int goalPos, Real onPathDistToGoal, Real desiredSpeed);
};

struct Rva001E8C1BTemplate
{
	char m_pad000[0xd8];
	int m_canReverse; // +0xD8
	char m_pad0DC[0x13c - 0xdc];
	Bool m_13C; // +0x13C
	char m_pad13D[3];
	Real m_reverseDistance; // +0x140
	Real m_reversePathDistance; // +0x144
	Real m_reverseAngle; // +0x148
};

class Rva001E8C1B
{
public:
	void rva001E8C1B(int objArg, int goalArg, Real onPathDistToGoal, Real desiredSpeed);

private:
	void *m_vtbl;
	Rva001E8C1BTemplate *m_template; // +0x04
	char m_pad08[0x14 - 8];
	Coord3D m_point; // +0x14
	char m_pad20[0x40 - 0x20];
	Real m_turnRate; // +0x40
	unsigned int m_flags0 : 7; // +0x44
	unsigned int m_reversing : 1; // +0x44 bit 7
};

void Rva001E8C1B::rva001E8C1B(int objArg, int goalArg, Real onPathDistToGoal, Real desiredSpeed)
{
	Object *obj = (Object *)objArg;
	const Coord3D *goalPos = (const Coord3D *)goalArg;

	Real maxSpeed = reinterpret_cast<Rva001E46E1 *>(this)->rva001E46E1(obj);
	if (desiredSpeed > maxSpeed)
		desiredSpeed = maxSpeed;

	Real angle = obj->m_orientation;
	Real desiredAngle = atan2f(goalPos->y - obj->m_pos.y, goalPos->x - obj->m_pos.x);
	Real relAngle = normalizeAngle(desiredAngle - angle);

	Bool reverse = m_template->m_canReverse != 0;
	if (reverse)
	{
		Coord3D delta;
		delta.x = m_point.x - obj->m_pos.x;
		delta.y = m_point.y - obj->m_pos.y;
		delta.z = m_point.z - obj->m_pos.z;
		if (delta.GetLengthEstimate2D() > m_template->m_reverseDistance && onPathDistToGoal > m_template->m_reversePathDistance)
			reverse = false;
	}

	Real turnRate = m_turnRate;
	if (reverse && fabs(relAngle) > m_template->m_reverseAngle * 3.1415927f)
	{
		if (!(obj->m_modelConditions & 0x10000000))
		{
			obj->m_modelConditions |= 0x10000000;
			obj->rva0028AE6D();
		}
		m_reversing = 1;
	}
	else
	{
		if (obj->m_modelConditions & 0x10000000)
		{
			obj->m_modelConditions &= ~0x10000000;
			obj->rva0028AE6D();
		}
		m_reversing = 0;
	}

	if (m_reversing)
		desiredAngle = normalizeAngle(desiredAngle - 3.1415927f);

	Coord3D target = obj->m_pos;
	target.x += Cos(desiredAngle) * 1000.0f;
	target.y += Sin(desiredAngle) * 1000.0f;
	reinterpret_cast<Rva001E685F *>(this)->rva001E685F((int)obj, (int)&target, 0);

	if (reinterpret_cast<Rva001E46E1 *>(this)->rva001E4845(obj) >= turnRate)
		relAngle *= 2.0f;
	else if (turnRate > maxSpeed * 0.25f)
		relAngle = 0.0f;

	if (maxSpeed > 0.0f)
	{
		Real angleCoeff = fabs(relAngle) * 1.2732395f;
		if (angleCoeff > 1.0f)
			angleCoeff = 1.0f;
		Real goalSpeed;
		if (m_template->m_13C && m_reversing)
		{
			if (((obj->m_modelConditions >> 5) & 1) || ((obj->m_modelConditions >> 6) & 1))
				goalSpeed = 0.0f;
			else
				goalSpeed = desiredSpeed;
		}
		else if (m_reversing)
			goalSpeed = desiredSpeed;
		else
			goalSpeed = (1.0f - angleCoeff) * desiredSpeed;
		desiredSpeed = goalSpeed;
		reinterpret_cast<Rva001E6007 *>(this)->rva001e6007((unsigned int)obj, (unsigned int)goalPos, onPathDistToGoal, desiredSpeed);
	}
	else if (fabs(relAngle) < 0.01f)
	{
		obj->m_ai->aiIdle(CMD_FROM_AI);
	}
}
