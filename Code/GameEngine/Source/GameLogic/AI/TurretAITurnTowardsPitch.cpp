// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// TurretAI::friend_turnTowardsPitch, retail 0x004D80EE (200 bytes), ported
// from Zero Hour's GameEngine/Source/GameLogic/AI/TurretAI.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference); Zero Hour's
// body on BFME 2's layout (target evidence): the turret data +0x08 with the
// pitch rate at +0x04 and allows-pitch at +0x66, m_pitch +0x1C,
// m_playPitchSound +0x39. fabs is the CRT call (no /Oi at /O1) and
// normalizeAngle the rowed 0x00238954.
#include <math.h>

typedef bool Bool;
typedef float Real;

Real normalizeAngle(Real angle);

struct TurretAIData
{
	unsigned char m_pad00[0x04];
	Real m_pitchRate; // +0x04
	unsigned char m_pad08[0x66 - 0x08];
	Bool m_isAllowsPitch; // +0x66
};

class TurretAI
{
public:
	Bool friend_turnTowardsPitch(Real desiredPitch, Real rateModifier);
	Bool isAllowsPitch() const { return m_data->m_isAllowsPitch; }
	Real getTurretPitch() const { return m_pitch; }
	Real getPitchRate() const { return m_data->m_pitchRate; }
private:
	unsigned char m_pad00[0x08];
	const TurretAIData *m_data; // +0x08
	unsigned char m_pad0C[0x1C - 0x0C];
	Real m_pitch; // +0x1C
	unsigned char m_pad20[0x39 - 0x20];
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
