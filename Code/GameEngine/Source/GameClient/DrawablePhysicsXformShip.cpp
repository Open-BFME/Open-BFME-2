// ?rva00272FB6@Drawable@@IAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?rva00272FB6@Drawable@@IAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// retail 0x00272FB6..0x00273648 (1682 bytes) thiscall RET 8.
//
// SHIP case of Drawable::calcPhysicsXform's appearance switch (caller
// 0x0027BA95, appearance 9 of the LocomotorAppearance name table at
// 0x00DB8E40). WorldBuilder twin 0x00CA79F0 (Drawable.cpp, random pitch kick
// at line 3486; retail line 3491). Target facts: the 0x58-byte
// DrawableLocoInfo (rowed ctor 0x00270098) created on demand, the locomotor
// template reads (+0x88 accel pitch limit, +0x8C pitch kick, +0x90/+0x94
// pitch/roll stiffness, +0x98/+0x9C pitch/roll damping, +0xA8/+0xB0/+0xB4
// forward velocity / forward / lateral acceleration coefficients, +0xB8
// uniform axial damping, +0x114..+0x120 bobbing amplitudes and rates), the
// object's +0x258/+0x25C pointers, the drawable's position history at
// +0x40C/+0x418/+0x424 and its model-condition bits 0x85/0x86 at +0x258. The
// spring/damper equations follow the matched sibling calcPhysicsXformTreads.
// Reference guide: Open-BFME-1 b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b,
// game/GameEngine/Source/GameClient/Drawable.cpp, and the matched target
// calcPhysicsXformTreads / calcPhysicsXform dispatcher. Exact target identity
// and offsets are distinguished from the donor field meanings above.
// The float overloads of <math.h> inline here; dllimport keeps them from
// emitting out-of-line copies that differ from retail's fsin/fcos ones
// (0x2FBB0/0x2FBC0). Same wrap as wwmath.cpp.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
#include "Coord3DInline.h"

// ?length@Coord3D@@QBEMXZ
inline float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

// ?normalize@Coord3D@@QAEXXZ
inline void Coord3D::normalize()
{
	float len = length();
	if (len != 0.0f) {
		float scale = 1.0f / len;
		x *= scale;
		y *= scale;
		z *= scale;
	}
}

typedef float Real;
typedef int Int;
typedef bool Bool;

class DrawableLocoInfo
{
public:
	virtual ~DrawableLocoInfo() {}
	DrawableLocoInfo();
	// Reconstruction helper shared by the four spring integrations below.
	// Its name is local source structure, not a recovered retail method name.
	__forceinline void springStep(Real &rate, Real position, Real stiffness, Real damping)
	{
		rate += (-stiffness * (position * (1.0f - damping))) + (-damping * rate);
	}

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
	Real m_pitchKick;			// +0x8C
	Real m_pitchStiffness;			// +0x90
	Real m_rollStiffness;			// +0x94
	Real m_pitchDamping;			// +0x98
	Real m_rollDamping;			// +0x9C
	char m_padA0[0xA8 - 0xA0];
	Real m_forwardVelCoef;			// +0xA8
	char m_padAC[4];
	Real m_forwardAccelCoef;		// +0xB0
	Real m_lateralAccelCoef;		// +0xB4
	Real m_uniformAxialDamping;		// +0xB8
	char m_padBC[0x114 - 0xBC];
	Real m_pitchBobAmplitude;		// +0x114
	Real m_pitchBobRate;			// +0x118
	Real m_rollBobAmplitude;		// +0x11C
	Real m_rollBobRate;			// +0x120
};

class Object;
enum KindOfType { KINDOF_FIRST };

class Rva001E46E1
{
public:
	Real rva001E4845(Object *obj);
};

class Rva001E3F27FloatChaseField
{
public:
	Real get() const;
};

class Locomotor
{
public:
	void *m_vtable;
	const LocomotorTemplate *m_template;	// +0x04
};

class Rva002627E8
{
public:
	Real rva002627E8() const;
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class Object
{
public:
	Bool isKindOf(KindOfType t) const;
	Real rva0028AC7D() const;
	Rva002627E8 *getAI() const { return m_ai; }
	void *getPhysics() const { return m_physics; }
	Bool isAirborne() const { return (m_status438 & 1) != 0; }

	char m_pad000[0xA8];
	GeometryInfo m_geometryInfo;		// +0xA8
	char m_padA9[0xCC - 0xA9];
	Real m_boxMajorRadius;			// +0xCC
	Real m_boxMinorRadius;			// +0xD0
	char m_padD4[0x258 - 0xD4];
	Rva002627E8 *m_ai;			// +0x258
	void *m_physics;			// +0x25C
	char m_pad260[0x438 - 0x260];
	unsigned char m_status438;		// +0x438
};

#include "../Common/Thing/thing.h"

Real Sin(Real x);
Int GetGameClientRandomValue(Int lo, Int hi, char *file, Int line);

extern int BfmeLogicFramesPerSecond;
extern int BfmeClientFramesPerSecond;

struct ModelConditionBits
{
	unsigned m_words[19];
	Bool test(Int bit) const { return ((m_words[bit >> 5] >> (bit & 31)) & 1) != 0; }
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
	void rva00272FB6(const Locomotor *locomotor, PhysicsXformInfo &info);

private:
	char m_pad000[0xFC];
	Object *m_object;			// +0xFC
	char m_pad100[0x13C - 0x100];
	DrawableLocoInfo *m_locoInfo;		// +0x13C
	char m_pad140[0x258 - 0x140];
	ModelConditionBits m_conditionBits;	// +0x258
	char m_pad2A4[0x40C - 0x2A4];
	Coord3D m_position2;			// +0x40C
	Coord3D m_position1;			// +0x418
	Coord3D m_position0;			// +0x424
};

void Drawable::rva00272FB6(const Locomotor *locomotor, PhysicsXformInfo &info)
{
	if (m_locoInfo == 0)
		m_locoInfo = new DrawableLocoInfo;

	const Real ACCEL_PITCH_LIMIT = locomotor->m_template->m_accelPitchLimit;
	const Real PITCH_STIFFNESS = locomotor->m_template->m_pitchStiffness;
	const Real ROLL_STIFFNESS = locomotor->m_template->m_rollStiffness;
	const Real PITCH_DAMPING = locomotor->m_template->m_pitchDamping;
	const Real ROLL_DAMPING = locomotor->m_template->m_rollDamping;
	const Real FORWARD_VEL_COEF = locomotor->m_template->m_forwardVelCoef;
	const Real FORWARD_ACCEL_COEF = locomotor->m_template->m_forwardAccelCoef;
	const Real LATERAL_ACCEL_COEF = locomotor->m_template->m_lateralAccelCoef;
	const Real UNIFORM_AXIAL_DAMPING = locomotor->m_template->m_uniformAxialDamping;
	const Real PITCH_KICK = locomotor->m_template->m_pitchKick;
	const Real LATERAL_SCALE = 12.0f;
	const Real REVERSE_SCALE = 0.8f;

	Object *obj = m_object;
	if (obj == 0)
		return;
	Rva002627E8 *ai = obj->getAI();
	if (ai == 0)
		return;
	if (obj->getPhysics() == 0)
		return;

	const Coord3D *dir = ((const Thing *)this)->getUnitDirectionVector2D();

	Coord3D accel;
	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;

	Coord3D vel;
	vel.set(&m_position0);
	vel.sub(&m_position1);
	Coord3D prevVel;
	prevVel.set(&m_position1);
	prevVel.sub(&m_position2);

	if (obj->isKindOf((KindOfType)0x87))
	{
		accel = vel;
		accel.normalize();
		Real v = ((Rva001E46E1 *)locomotor)->rva001E4845(obj);
		accel.scaleInlined(v);
	}
	else if (obj->isKindOf((KindOfType)0x88))
	{
		accel = vel;
		accel.normalize();
		Real v = -((Rva001E46E1 *)locomotor)->rva001E4845(obj) * REVERSE_SCALE;
		accel.scaleInlined(v);
	}

	vel.scaleInlined((Real)BfmeLogicFramesPerSecond / BfmeClientFramesPerSecond);
	accel.scaleInlined((Real)BfmeLogicFramesPerSecond / BfmeClientFramesPerSecond);

	m_locoInfo->springStep(m_locoInfo->m_pitchRate, m_locoInfo->m_pitch, PITCH_STIFFNESS, PITCH_DAMPING);
	m_locoInfo->springStep(m_locoInfo->m_rollRate, m_locoInfo->m_roll, ROLL_STIFFNESS, ROLL_DAMPING);
	m_locoInfo->m_pitch += UNIFORM_AXIAL_DAMPING * m_locoInfo->m_pitchRate;
	m_locoInfo->m_roll += UNIFORM_AXIAL_DAMPING * m_locoInfo->m_rollRate;

	m_locoInfo->springStep(m_locoInfo->m_accelerationPitchRate, m_locoInfo->m_accelerationPitch, PITCH_STIFFNESS, PITCH_DAMPING);
	m_locoInfo->m_accelerationPitch += m_locoInfo->m_accelerationPitchRate;
	m_locoInfo->springStep(m_locoInfo->m_accelerationRollRate, m_locoInfo->m_accelerationRoll, ROLL_STIFFNESS, ROLL_DAMPING);
	m_locoInfo->m_accelerationRoll += m_locoInfo->m_accelerationRollRate;

	Real totalPitchRate = m_locoInfo->m_pitchRate + m_locoInfo->m_accelerationPitchRate;
	info.m_totalPitch = m_locoInfo->m_pitch + m_locoInfo->m_accelerationPitch;
	info.m_totalRoll = m_locoInfo->m_roll + m_locoInfo->m_accelerationRoll;

	if (!obj->isAirborne())
	{
		Real forwardVel = vel.x * dir->x + vel.y * dir->y;
		m_locoInfo->m_pitchRate += -(FORWARD_VEL_COEF * forwardVel);
		Real forwardAccel = accel.x * dir->x + accel.y * dir->y;
		m_locoInfo->m_accelerationPitchRate += -(FORWARD_ACCEL_COEF * forwardAccel);

		Real lateral = 0.0f;
		Real speedScale = ((const Rva001E3F27FloatChaseField *)locomotor)->get();
		if (speedScale < 1.0f)
			speedScale = 1.0f;
		lateral = vel.length() * LATERAL_SCALE * (1.0f / speedScale);
		if (m_conditionBits.test(0x86))
			lateral = -lateral;
		else if (m_conditionBits.test(0x85))
			;
		else
			lateral = 0.0f;
		m_locoInfo->m_accelerationRollRate += -(LATERAL_ACCEL_COEF * lateral);
	}

	if (m_locoInfo->m_accelerationPitch > ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationPitch = ACCEL_PITCH_LIMIT;
	else if (-ACCEL_PITCH_LIMIT > m_locoInfo->m_accelerationPitch)
		m_locoInfo->m_accelerationPitch = -ACCEL_PITCH_LIMIT;

	if (m_locoInfo->m_accelerationRoll > ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationRoll = ACCEL_PITCH_LIMIT;
	else if (-ACCEL_PITCH_LIMIT > m_locoInfo->m_accelerationRoll)
		m_locoInfo->m_accelerationRoll = -ACCEL_PITCH_LIMIT;

	Real speed = obj->rva0028AC7D();
	Real maxSpeed = ai->rva002627E8();
	if (maxSpeed / 3.0f < speed)
	{
		Real ratio = speed / maxSpeed;
		Real threshold = ratio * PITCH_KICK / 4.0f;
		if (fabs(totalPitchRate) < threshold)
		{
			if (GetGameClientRandomValue(0, 3, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable.cpp", 3491) == 0)
				m_locoInfo->m_pitchRate -= PITCH_KICK * ratio;
		}
	}

	const Real ROLL_BOB_AMPLITUDE = locomotor->m_template->m_rollBobAmplitude;
	const Real ROLL_BOB_RATE = locomotor->m_template->m_rollBobRate;
	const Real PITCH_BOB_AMPLITUDE = locomotor->m_template->m_pitchBobAmplitude;
	const Real PITCH_BOB_RATE = locomotor->m_template->m_pitchBobRate;
	m_locoInfo->m_yawModulator += ROLL_BOB_RATE;
	info.m_totalRoll += sin(m_locoInfo->m_yawModulator) * ROLL_BOB_AMPLITUDE;
	m_locoInfo->m_pitchModulator += PITCH_BOB_RATE;
	info.m_totalPitch += cos(m_locoInfo->m_pitchModulator) * PITCH_BOB_AMPLITUDE;

	Real length = obj->m_boxMajorRadius;
	Real width = obj->m_boxMinorRadius;
	Real height = obj->m_geometryInfo.getMaxHeightAbovePosition();
	Real pitchHeight = Sin(info.m_totalPitch) * length;
	Real rollHeight = Sin(info.m_totalRoll) * width;
	const Real Z_SCALE = 0.7f;
	info.m_totalZ = 0.0f;
	info.m_totalZ += fabs(pitchHeight);
	info.m_totalZ += fabs(rollHeight);
	info.m_totalZ *= Z_SCALE;
	info.m_totalZ -= 0.5f * height;
	if (info.m_totalZ < 0.0f)
		info.m_totalZ = 0.0f;
}
