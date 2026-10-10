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

// The object's AI (+0x258) as 0x00270B0F uses it: virtual slot 0x168/4
// gates the banking and slot 0x188/4 returns the record whose +0x53C float
// drives it. Slot meanings are not recovered; only the offsets are target
// facts.
struct Rva00270B0FBankSource
{
	char m_pad000[0x53C];
	Real m_value;						// +0x53C
};

class Rva00270B0FAIView
{
public:
#define BFME_AI_SLOT(n) virtual void slot##n();
	BFME_AI_SLOT(00) BFME_AI_SLOT(01) BFME_AI_SLOT(02) BFME_AI_SLOT(03) BFME_AI_SLOT(04)
	BFME_AI_SLOT(05) BFME_AI_SLOT(06) BFME_AI_SLOT(07) BFME_AI_SLOT(08) BFME_AI_SLOT(09)
	BFME_AI_SLOT(10) BFME_AI_SLOT(11) BFME_AI_SLOT(12) BFME_AI_SLOT(13) BFME_AI_SLOT(14)
	BFME_AI_SLOT(15) BFME_AI_SLOT(16) BFME_AI_SLOT(17) BFME_AI_SLOT(18) BFME_AI_SLOT(19)
	BFME_AI_SLOT(20) BFME_AI_SLOT(21) BFME_AI_SLOT(22) BFME_AI_SLOT(23) BFME_AI_SLOT(24)
	BFME_AI_SLOT(25) BFME_AI_SLOT(26) BFME_AI_SLOT(27) BFME_AI_SLOT(28) BFME_AI_SLOT(29)
	BFME_AI_SLOT(30) BFME_AI_SLOT(31) BFME_AI_SLOT(32) BFME_AI_SLOT(33) BFME_AI_SLOT(34)
	BFME_AI_SLOT(35) BFME_AI_SLOT(36) BFME_AI_SLOT(37) BFME_AI_SLOT(38) BFME_AI_SLOT(39)
	BFME_AI_SLOT(40) BFME_AI_SLOT(41) BFME_AI_SLOT(42) BFME_AI_SLOT(43) BFME_AI_SLOT(44)
	BFME_AI_SLOT(45) BFME_AI_SLOT(46) BFME_AI_SLOT(47) BFME_AI_SLOT(48) BFME_AI_SLOT(49)
	BFME_AI_SLOT(50) BFME_AI_SLOT(51) BFME_AI_SLOT(52) BFME_AI_SLOT(53) BFME_AI_SLOT(54)
	BFME_AI_SLOT(55) BFME_AI_SLOT(56) BFME_AI_SLOT(57) BFME_AI_SLOT(58) BFME_AI_SLOT(59)
	BFME_AI_SLOT(60) BFME_AI_SLOT(61) BFME_AI_SLOT(62) BFME_AI_SLOT(63) BFME_AI_SLOT(64)
	BFME_AI_SLOT(65) BFME_AI_SLOT(66) BFME_AI_SLOT(67) BFME_AI_SLOT(68) BFME_AI_SLOT(69)
	BFME_AI_SLOT(70) BFME_AI_SLOT(71) BFME_AI_SLOT(72) BFME_AI_SLOT(73) BFME_AI_SLOT(74)
	BFME_AI_SLOT(75) BFME_AI_SLOT(76) BFME_AI_SLOT(77) BFME_AI_SLOT(78) BFME_AI_SLOT(79)
	BFME_AI_SLOT(80) BFME_AI_SLOT(81) BFME_AI_SLOT(82) BFME_AI_SLOT(83) BFME_AI_SLOT(84)
	BFME_AI_SLOT(85) BFME_AI_SLOT(86) BFME_AI_SLOT(87) BFME_AI_SLOT(88) BFME_AI_SLOT(89)
	virtual bool slot90();				// +0x168
	BFME_AI_SLOT(91) BFME_AI_SLOT(92) BFME_AI_SLOT(93) BFME_AI_SLOT(94)
	BFME_AI_SLOT(95) BFME_AI_SLOT(96) BFME_AI_SLOT(97)
	virtual Rva00270B0FBankSource *slot98();	// +0x188
#undef BFME_AI_SLOT
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
	void rva00270B0F(const Locomotor *locomotor, PhysicsXformInfo &info);

private:
	char m_pad000[0xFC];
	Object *m_object;					// +0xFC
	char m_pad100[0x13C - 0x100];
	DrawableLocoInfo *m_locoInfo;		// +0x13C
	Real m_bankRoll;					// +0x140
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

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

// Retail 0x00270B0F..0x00270BA8 (153 bytes) thiscall RET 8, right after
// calcPhysicsXformTreads: the appearance switch of calcPhysicsXform
// (0x0027BB2B, template +0x74 case 5) calls it with the locomotor (unused)
// and the info. While the object's AI reports slot 0x168 it eases the roll
// at +0x140 toward four times the +0x53C value of the AI's slot-0x188
// record (0.8 old + 0.2 new), clamps it to +-0.8 and writes it to the
// info's total roll. Native tests the lower bound twice: the windef-style
// min/max macros evaluate the inner max in both arms of the outer min.
void Drawable::rva00270B0F(const Locomotor *locomotor, PhysicsXformInfo &info)
{
	const Object *obj = m_object;
	if (obj == 0)
		return;
	Rva00270B0FAIView *ai = (Rva00270B0FAIView *)obj->getAI();
	if (ai == 0 || !ai->slot90())
		return;
	Real target = ai->slot98()->m_value * 4.0f;
	Real roll = m_bankRoll * 0.8f + target * 0.2f;
	m_bankRoll = min(0.8f, max(-0.8f, roll));
	info.m_totalRoll = m_bankRoll;
}
