// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?calcPhysicsXformTreads@Drawable@@IAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// retail 0x00270817..0x00270B0F (760 bytes) thiscall RET 8.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/Drawable.cpp
// Drawable::calcPhysicsXformTreads (itself the Zero Hour body with BFME
// offsets). The BFME 2 body is the same spring/damper update minus BFME 1's
// rudder/elevator tail: create the 0x58-byte DrawableLocoInfo on demand
// (rowed ctor 0x00270098 under an EH state as in WB 0x00CA7580); read the
// locomotor template's accel pitch limit +0x88 pitch/roll stiffness +0x90/+0x94
// pitch/roll damping +0x98/+0x9C and uniform axial damping +0xB8; bail without
// an object (+0xFC) or its +0x258 pointer; integrate pitch/roll rates; when the
// object's +0x438 bit 0 is clear integrate pitch/roll and the acceleration
// springs, else halve the acceleration terms and snap them to zero below
// 0.0001 (out-of-line _fabs); write total pitch/roll; clamp the acceleration
// terms to the pitch limit; zero total Z. Retail caller 0x0027BB45 is the
// appearance switch of calcPhysicsXform (template +0x74 cases 2 and 3 = TREADS
// and HOVER as in the donor). Target facts: offsets m_locoInfo
// +0x13C and m_object +0xFC; the method name, the airborne meaning of bit 0
// and the +0x258 (AI) meaning are carried from the donor. WB's twin is unnamed.
#include <math.h>

typedef float Real;
typedef int Int;

class DrawableLocoInfo
{
public:
	virtual ~DrawableLocoInfo() {}
	DrawableLocoInfo();
	Real m_pitch;
	Real m_pitchRate;
	Real m_roll;
	Real m_rollRate;
	Real m_yaw;
	Real m_accelerationPitch;
	Real m_accelerationPitchRate;
	Real m_accelerationRoll;
	Real m_accelerationRollRate;
	Real m_overlapZVel;
	Real m_overlapZ;
	Real m_wobble;
	Real m_yawModulator;
	Real m_pitchModulator;
	Real m_wheelInfo[7];
};

struct LocomotorTemplate
{
	char m_pad00[0x88];
	Real m_accelPitchLimit;			// +0x88
	Real m_decelPitchLimit;			// +0x8C
	Real m_pitchStiffness;			// +0x90
	Real m_rollStiffness;			// +0x94
	Real m_pitchDamping;			// +0x98
	Real m_rollDamping;				// +0x9C
	char m_padA0[0xB8 - 0xA0];
	Real m_uniformAxialDamping;		// +0xB8
};

class Locomotor
{
public:
	Real getAccelPitchLimit() const { return m_template->m_accelPitchLimit; }
	Real getPitchStiffness() const { return m_template->m_pitchStiffness; }
	Real getRollStiffness() const { return m_template->m_rollStiffness; }
	Real getPitchDamping() const { return m_template->m_pitchDamping; }
	Real getRollDamping() const { return m_template->m_rollDamping; }
	Real getUniformAxialDamping() const { return m_template->m_uniformAxialDamping; }

private:
	void *m_vtable;
	const LocomotorTemplate *m_template;	// +0x04
};

class Object
{
public:
	void *getAI() const { return m_ai; }
	bool isAirborne() const { return (m_status438 & 1) != 0; }

private:
	char m_pad000[0x258];
	void *m_ai;							// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_status438;			// +0x438
};

class Drawable
{
public:
	struct PhysicsXformInfo
	{
		Real m_totalPitch;
		Real m_totalRoll;
		Real m_totalYaw;
		Real m_totalZ;
	};

protected:
	void calcPhysicsXformTreads(const Locomotor *locomotor, PhysicsXformInfo &info);

private:
	char m_pad000[0xFC];
	Object *m_object;					// +0xFC
	char m_pad100[0x13C - 0x100];
	DrawableLocoInfo *m_locoInfo;		// +0x13C
};

void Drawable::calcPhysicsXformTreads(const Locomotor *locomotor, PhysicsXformInfo &info)
{
	if (m_locoInfo == 0)
		m_locoInfo = new DrawableLocoInfo;

	const Real ACCEL_PITCH_LIMIT = locomotor->getAccelPitchLimit();
	const Real PITCH_STIFFNESS = locomotor->getPitchStiffness();
	const Real ROLL_STIFFNESS = locomotor->getRollStiffness();
	const Real PITCH_DAMPING = locomotor->getPitchDamping();
	const Real ROLL_DAMPING = locomotor->getRollDamping();
	const Real UNIFORM_AXIAL_DAMPING = locomotor->getUniformAxialDamping();

	const Object *obj = m_object;
	if (obj == 0 || obj->getAI() == 0)
		return;

	m_locoInfo->m_pitchRate += ((-PITCH_STIFFNESS * m_locoInfo->m_pitch) + (-PITCH_DAMPING * m_locoInfo->m_pitchRate));
	m_locoInfo->m_rollRate += ((-ROLL_STIFFNESS * m_locoInfo->m_roll) + (-ROLL_DAMPING * m_locoInfo->m_rollRate));

	if (!obj->isAirborne())
	{
		m_locoInfo->m_pitch += m_locoInfo->m_pitchRate * UNIFORM_AXIAL_DAMPING;
		m_locoInfo->m_roll += m_locoInfo->m_rollRate * UNIFORM_AXIAL_DAMPING;

		m_locoInfo->m_accelerationPitchRate += ((-PITCH_STIFFNESS * m_locoInfo->m_accelerationPitch) + (-PITCH_DAMPING * m_locoInfo->m_accelerationPitchRate));
		m_locoInfo->m_accelerationPitch += m_locoInfo->m_accelerationPitchRate;

		m_locoInfo->m_accelerationRollRate += ((-ROLL_STIFFNESS * m_locoInfo->m_accelerationRoll) + (-ROLL_DAMPING * m_locoInfo->m_accelerationRollRate));
		m_locoInfo->m_accelerationRoll += m_locoInfo->m_accelerationRollRate;
	}
	else
	{
		m_locoInfo->m_accelerationPitch *= 0.5f;
		if (fabs(m_locoInfo->m_accelerationPitch) < 0.0001f)
			m_locoInfo->m_accelerationPitch = 0.0f;
		m_locoInfo->m_accelerationRoll *= 0.5f;
		if (fabs(m_locoInfo->m_accelerationRoll) < 0.0001f)
			m_locoInfo->m_accelerationRoll = 0.0f;
	}

	info.m_totalPitch = m_locoInfo->m_accelerationPitch + m_locoInfo->m_pitch;
	info.m_totalRoll = m_locoInfo->m_accelerationRoll + m_locoInfo->m_roll;

	if (m_locoInfo->m_accelerationPitch > ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationPitch = ACCEL_PITCH_LIMIT;
	else if (m_locoInfo->m_accelerationPitch < -ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationPitch = -ACCEL_PITCH_LIMIT;

	if (m_locoInfo->m_accelerationRoll > ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationRoll = ACCEL_PITCH_LIMIT;
	else if (m_locoInfo->m_accelerationRoll < -ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationRoll = -ACCEL_PITCH_LIMIT;

	info.m_totalZ = 0.0f;
}
