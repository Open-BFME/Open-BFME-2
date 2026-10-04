// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// TurretAI::friend_turnTowardsPitch, retail 0x004D80EE (200 bytes), and
// friend_turnTowardsAngle, retail 0x004D8990 (431 bytes), ported from Zero
// Hour's GameEngine/Source/GameLogic/AI/TurretAI.cpp (GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference); Zero Hour's bodies on
// BFME 2's layout (target evidence): the turret data +0x08 with the turn rate
// at +0x00, the pitch rate at +0x04, the natural angle at +0x08 and
// allows-pitch at +0x66; m_whichTurret +0x0C, owner +0x10, m_angle +0x18,
// m_pitch +0x1C, m_playRotSound +0x38, m_playPitchSound +0x39. fabs is the
// CRT call (no /Oi at /O1) and normalizeAngle the rowed 0x00238954.
// BFME 2 adds an angle limit to friend_turnTowardsAngle (target evidence):
// when the data's +0x68 / +0x6C arc (below / above the natural angle) is
// less than a full turn, a desired angle outside it turns the turret to its
// natural angle instead (the final alignment test still uses the desired
// angle). MODELCONDITION_TURRET_ROTATE is bit 58 (Object +0x10C flags, the
// rowed notifier Object::rva0028AE6D); reactToTurretChange is 0x0028B141.
#include <math.h>

typedef bool Bool;
typedef float Real;
typedef int Int;

Real normalizeAngle(Real angle);
#define TWO_PI 6.28318548f

enum WhichTurretType
{
	TURRET_INVALID = -1
};

enum ModelConditionFlagType
{
	MODELCONDITION_TURRET_ROTATE = 58
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	void rva0028AE6D();
	void reactToTurretChange(WhichTurretType turret, Real oldRotation, Real oldPitch);
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad00[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};

struct TurretAIData
{
	Real m_turnRate; // +0x00
	Real m_pitchRate; // +0x04
	Real m_naturalTurretAngle; // +0x08
	unsigned char m_pad0C[0x66 - 0x0C];
	Bool m_isAllowsPitch; // +0x66
	unsigned char m_pad67[0x68 - 0x67];
	Real m_bfmeMinAngleOffset; // +0x68
	Real m_bfmeMaxAngleOffset; // +0x6C
};

class TurretAI
{
public:
	Bool friend_turnTowardsPitch(Real desiredPitch, Real rateModifier);
	Bool friend_turnTowardsAngle(Real desiredAngle, Real rateModifier, Real relThresh);
	Bool isAllowsPitch() const { return m_data->m_isAllowsPitch; }
	Real getTurretPitch() const { return m_pitch; }
	Real getPitchRate() const { return m_data->m_pitchRate; }
	Real getTurretAngle() const { return m_angle; }
	Real getTurnRate() const { return m_data->m_turnRate; }
	Real getNaturalTurretAngle() const { return m_data->m_naturalTurretAngle; }
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x08];
	const TurretAIData *m_data; // +0x08
	WhichTurretType m_whichTurret; // +0x0C
	Object *m_owner; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	Real m_angle; // +0x18
	Real m_pitch; // +0x1C
	unsigned char m_pad20[0x38 - 0x20];
	Bool m_playRotSound; // +0x38
	Bool m_playPitchSound; // +0x39
};

//----------------------------------------------------------------------------------------------------------
Bool TurretAI::friend_turnTowardsPitch(Real desiredPitch, Real rateModifier)
{
	if (!isAllowsPitch())
		return true;

	desiredPitch = normalizeAngle(desiredPitch);

	// rotate turret back to zero angle
	Real actualPitch = getTurretPitch();
	Real pitchRate = getPitchRate() * rateModifier;
	Real pitchDiff = normalizeAngle(desiredPitch - actualPitch);

	if (fabs(pitchDiff) < pitchRate)
	{
		// we are centered
		actualPitch = desiredPitch;
	}
	else
	{
		if (pitchDiff > 0)
			actualPitch += pitchRate;
		else
			actualPitch -= pitchRate;
		m_playPitchSound = true;
	}

	m_pitch = normalizeAngle(actualPitch);

	return (m_pitch == desiredPitch);
}

//----------------------------------------------------------------------------------------------------------
Bool TurretAI::friend_turnTowardsAngle(Real desiredAngle, Real rateModifier, Real relThresh)
{
	desiredAngle = normalizeAngle(desiredAngle);
	Real targetAngle = desiredAngle;

	// BFME 2: keep the turret inside its arc, else send it home.
	Real minOffset = m_data->m_bfmeMinAngleOffset;
	Real maxOffset = m_data->m_bfmeMaxAngleOffset;
	if (maxOffset + minOffset < TWO_PI)
	{
		Real natural = getNaturalTurretAngle();
		Real lo = normalizeAngle(natural - minOffset);
		Real hi = normalizeAngle(natural + maxOffset);
		if (lo > hi)
		{
			if (lo > desiredAngle && desiredAngle > hi)
				targetAngle = natural;
		}
		else
		{
			if (lo > desiredAngle || desiredAngle > hi)
				targetAngle = natural;
		}
	}

	// rotate turret back to zero angle
	Real origAngle = getTurretAngle();
	Real actualAngle = origAngle;
	Real turnRate = getTurnRate() * rateModifier;
	Real angleDiff = normalizeAngle(targetAngle - actualAngle);

	// Are we close enough to the desired angle to just snap there?
	if (fabs(angleDiff) < turnRate)
	{
		// we are centered
		actualAngle = targetAngle;

		getOwner()->clearModelConditionState(MODELCONDITION_TURRET_ROTATE);
	}
	else
	{
		if (angleDiff > 0)
			actualAngle += turnRate;
		else
			actualAngle -= turnRate;

		getOwner()->setModelConditionState(MODELCONDITION_TURRET_ROTATE);
		m_playRotSound = true;
	}

	m_angle = normalizeAngle(actualAngle);

	if( m_angle != origAngle )
		getOwner()->reactToTurretChange( m_whichTurret, origAngle, m_pitch );

	Bool aligned = fabs(m_angle - desiredAngle) <= relThresh;

	return aligned;
}
