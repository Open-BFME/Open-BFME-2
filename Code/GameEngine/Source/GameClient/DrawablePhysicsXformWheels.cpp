// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?calcPhysicsXformWheels@Drawable@@IAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// retail 0x00276CFB..0x0027756D (2162 bytes) thiscall RET 8.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/DrawablePhysicsXformWheels.cpp
// (itself Zero Hour's Drawable::calcPhysicsXformWheels with BFME offsets),
// carried onto the BFME 2 layouts of the matched sibling
// calcPhysicsXformTreads 0x00270817: DrawableLocoInfo (0x58 bytes, rowed ctor
// 0x00270098, wheel info at +0x3C) is created on demand; the locomotor
// template is read directly (accel pitch limit +0x88, bounce kick +0x8C,
// pitch/roll stiffness +0x90/+0x94, pitch/roll damping +0x98/+0x9C, uniform
// axial damping +0xB8, suspension flag +0xDC, maximum wheel extension +0xE0);
// the object needs its +0x258 (AI) and +0x25C pointers; the terrain tilt comes
// from 0x00270276 and the box radii from object +0xCC/+0xD0. Retail caller
// 0x0027BB52 is the WHEELS case of calcPhysicsXform's appearance switch, beside
// the treads call at 0x0027BB45; WorldBuilder twin 0x00CA93C0 (Drawable.cpp,
// random roll at line 3948).

#include <math.h>
#include "Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

#define PI 3.14159265358979323846f

struct TWheelInfo
{
	Real m_frontLeftHeightOffset;
	Real m_frontRightHeightOffset;
	Real m_rearLeftHeightOffset;
	Real m_rearRightHeightOffset;
	Real m_wheelAngle;
	Int m_framesAirborneCounter;
	Int m_framesAirborne;
};

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
	TWheelInfo m_wheelInfo;
};

struct LocomotorTemplate
{
	char m_pad00[0x88];
	Real m_accelPitchLimit;			// +0x88
	Real m_bounceKick;			// +0x8C
	Real m_pitchStiffness;			// +0x90
	Real m_rollStiffness;			// +0x94
	Real m_pitchDamping;			// +0x98
	Real m_rollDamping;			// +0x9C
	char m_padA0[0xB8 - 0xA0];
	Real m_uniformAxialDamping;		// +0xB8
	char m_padBC[0xDC - 0xBC];
	Bool m_hasSuspension;			// +0xDC
	char m_padDD[3];
	Real m_maximumWheelExtension;		// +0xE0
};

class Locomotor
{
public:
	Real getAccelPitchLimit() const { return m_template->m_accelPitchLimit; }
	Real getBounceKick() const { return m_template->m_bounceKick; }
	Real getPitchStiffness() const { return m_template->m_pitchStiffness; }
	Real getRollStiffness() const { return m_template->m_rollStiffness; }
	Real getPitchDamping() const { return m_template->m_pitchDamping; }
	Real getRollDamping() const { return m_template->m_rollDamping; }
	Real getUniformAxialDamping() const { return m_template->m_uniformAxialDamping; }
	Real getMaxWheelExtension() const { return m_template->m_maximumWheelExtension; }
	Bool hasSuspension() const { return m_template->m_hasSuspension; }

private:
	void *m_vtable;
	const LocomotorTemplate *m_template;	// +0x04
};

class Rva002627E8
{
public:
	Real rva002627E8() const;		// current locomotor speed
};

class Object
{
public:
	Rva002627E8 *getAI() const { return m_ai; }
	void *getPhysics() const { return m_physics; }
	Bool isSignificantlyAboveTerrain() const;
	Int rva0028B511() const;		// layer
	Real rva0028AC7D() const;		// current speed
	Real getBoxMajorRadius() const { return m_boxMajorRadius; }
	Real getBoxMinorRadius() const { return m_boxMinorRadius; }

private:
	char m_pad000[0xCC];
	Real m_boxMajorRadius;			// +0xCC
	Real m_boxMinorRadius;			// +0xD0
	char m_padD4[0x258 - 0xD4];
	Rva002627E8 *m_ai;			// +0x258
	void *m_physics;			// +0x25C
};

class TerrainLogic
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
	virtual Real getLayerHeight(Real x, Real y, Int layer, Coord3D *normal, Bool clip);	// slot 7
};
extern TerrainLogic *TheTerrainLogic;

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};
class Rva00270276Host
{
public:
	Bool rva00270276(void *obj, void *locomotor, void *pos, void *dir, Int pitch, Int roll);	// terrain tilt
};

Real Sin(Real x);
Int GetGameClientRandomValue(Int lo, Int hi, char *file, Int line);

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
	void calcPhysicsXformWheels(const Locomotor *locomotor, PhysicsXformInfo &info);

private:
	char m_pad000[0xFC];
	Object *m_object;			// +0xFC
	char m_pad100[0x13C - 0x100];
	DrawableLocoInfo *m_locoInfo;		// +0x13C
};

void Drawable::calcPhysicsXformWheels(const Locomotor *locomotor, PhysicsXformInfo &info)
{
	if (m_locoInfo == 0)
		m_locoInfo = new DrawableLocoInfo;

	const Real ACCEL_PITCH_LIMIT = locomotor->getAccelPitchLimit();
	const Real BOUNCE_ANGLE_KICK = locomotor->getBounceKick();
	const Real PITCH_STIFFNESS = locomotor->getPitchStiffness();
	const Real ROLL_STIFFNESS = locomotor->getRollStiffness();
	const Real PITCH_DAMPING = locomotor->getPitchDamping();
	const Real ROLL_DAMPING = locomotor->getRollDamping();
	const Real UNIFORM_AXIAL_DAMPING = locomotor->getUniformAxialDamping();
	const Real MAX_SUSPENSION_EXTENSION = locomotor->getMaxWheelExtension();
	const Bool DO_WHEELS = locomotor->hasSuspension();

	Object *obj = m_object;
	if (obj == 0)
		return;

	Rva002627E8 *ai = obj->getAI();
	if (ai == 0)
		return;

	if (obj->getPhysics() == 0)
		return;

	const Coord3D *pos = ((const BFMERopeDrawable *)this)->getPosition();
	const Coord3D *dir = ((const Thing *)this)->getUnitDirectionVector2D();
	Real groundPitch = 0.0f;
	Real groundRoll = 0.0f;
	((Rva00270276Host *)this)->rva00270276(obj, (void *)locomotor, (void *)pos, (void *)dir, (Int)&groundPitch, (Int)&groundRoll);
	Real hheight = TheTerrainLogic->getLayerHeight(pos->x, pos->y, obj->rva0028B511(), 0, true);

	Bool airborne = obj->isSignificantlyAboveTerrain();

	if (airborne)
	{
		if (DO_WHEELS)
		{
			m_locoInfo->m_wheelInfo.m_framesAirborne = 0;
			m_locoInfo->m_wheelInfo.m_framesAirborneCounter++;
			if (pos->z - hheight > -MAX_SUSPENSION_EXTENSION)
			{
				m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset += (MAX_SUSPENSION_EXTENSION - m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset) / 2.0f;
				m_locoInfo->m_wheelInfo.m_rearRightHeightOffset += (MAX_SUSPENSION_EXTENSION - m_locoInfo->m_wheelInfo.m_rearRightHeightOffset) / 2.0f;
			}
			else
			{
				m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset += (0 - m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset) / 2.0f;
				m_locoInfo->m_wheelInfo.m_rearRightHeightOffset += (0 - m_locoInfo->m_wheelInfo.m_rearRightHeightOffset) / 2.0f;
			}
		}

		Real length = obj->getBoxMajorRadius();
		Real width = obj->getBoxMinorRadius();
		Real pitchHeight = length * Sin(m_locoInfo->m_accelerationPitch + m_locoInfo->m_pitch - groundPitch);
		Real rollHeight = width * Sin(m_locoInfo->m_accelerationRoll + m_locoInfo->m_roll - groundRoll);
		info.m_totalZ = (fabs(pitchHeight) + fabs(rollHeight)) / 4;
		return;
	}

	Real curSpeed = obj->rva0028AC7D();
	Real maxSpeed = ai->rva002627E8();
	if (!airborne && curSpeed > maxSpeed / 10)
	{
		Real factor = curSpeed / maxSpeed;
		if (fabs(m_locoInfo->m_pitchRate) < factor * BOUNCE_ANGLE_KICK / 4 && fabs(m_locoInfo->m_rollRate) < factor * BOUNCE_ANGLE_KICK / 8)
		{
			switch (GetGameClientRandomValue(0, 3, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable.cpp", 3948))
			{
			case 0:
				m_locoInfo->m_pitchRate -= BOUNCE_ANGLE_KICK * factor;
				m_locoInfo->m_rollRate -= BOUNCE_ANGLE_KICK * factor / 2;
				break;
			case 1:
				m_locoInfo->m_pitchRate += BOUNCE_ANGLE_KICK * factor;
				m_locoInfo->m_rollRate -= BOUNCE_ANGLE_KICK * factor / 2;
				break;
			case 2:
				m_locoInfo->m_pitchRate -= BOUNCE_ANGLE_KICK * factor;
				m_locoInfo->m_rollRate += BOUNCE_ANGLE_KICK * factor / 2;
				break;
			case 3:
				m_locoInfo->m_pitchRate += BOUNCE_ANGLE_KICK * factor;
				m_locoInfo->m_rollRate += BOUNCE_ANGLE_KICK * factor / 2;
				break;
			}
		}
	}

	if (!airborne)
	{
		m_locoInfo->m_pitchRate += ((-PITCH_STIFFNESS * (m_locoInfo->m_pitch - groundPitch)) + (-PITCH_DAMPING * m_locoInfo->m_pitchRate));
		if (m_locoInfo->m_pitchRate > 0.0f)
			m_locoInfo->m_pitchRate *= 0.5f;

		m_locoInfo->m_rollRate += ((-ROLL_STIFFNESS * (m_locoInfo->m_roll - groundRoll)) + (-ROLL_DAMPING * m_locoInfo->m_rollRate));
	}

	m_locoInfo->m_pitch += m_locoInfo->m_pitchRate * UNIFORM_AXIAL_DAMPING;
	m_locoInfo->m_roll += m_locoInfo->m_rollRate * UNIFORM_AXIAL_DAMPING;

	m_locoInfo->m_accelerationPitchRate += ((-PITCH_STIFFNESS * (m_locoInfo->m_accelerationPitch)) + (-PITCH_DAMPING * m_locoInfo->m_accelerationPitchRate));
	m_locoInfo->m_accelerationPitch += m_locoInfo->m_accelerationPitchRate;

	m_locoInfo->m_accelerationRollRate += ((-ROLL_STIFFNESS * m_locoInfo->m_accelerationRoll) + (-ROLL_DAMPING * m_locoInfo->m_accelerationRollRate));
	m_locoInfo->m_accelerationRoll += m_locoInfo->m_accelerationRollRate;

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

	info.m_totalYaw = 0;
	info.m_totalZ = 0;

	Real length = obj->getBoxMajorRadius();
	Real width = obj->getBoxMinorRadius();
	Real pitchHeight = length * Sin(info.m_totalPitch - groundPitch);
	Real rollHeight = width * Sin(info.m_totalRoll - groundRoll);
	if (DO_WHEELS)
	{
		m_locoInfo->m_wheelInfo.m_framesAirborne = m_locoInfo->m_wheelInfo.m_framesAirborneCounter;
		m_locoInfo->m_wheelInfo.m_framesAirborneCounter = 0;
		TWheelInfo newInfo = m_locoInfo->m_wheelInfo;
		newInfo.m_wheelAngle = 0;

		#define WHEEL_SMOOTHNESS 10.0f
		m_locoInfo->m_wheelInfo.m_wheelAngle += (newInfo.m_wheelAngle - m_locoInfo->m_wheelInfo.m_wheelAngle) / WHEEL_SMOOTHNESS;

		const Real SPRING_FACTOR = 0.9f;
		if (pitchHeight < 0)
		{
			newInfo.m_frontLeftHeightOffset = SPRING_FACTOR * (pitchHeight * (1.0f / 3 + 1.0f / 2));
			newInfo.m_frontRightHeightOffset = SPRING_FACTOR * (pitchHeight * (1.0f / 3 + 1.0f / 2));
			newInfo.m_rearLeftHeightOffset = pitchHeight * (-1.0f / 2 + 1.0f / 4);
			newInfo.m_rearRightHeightOffset = pitchHeight * (-1.0f / 2 + 1.0f / 4);
		}
		else
		{
			newInfo.m_frontLeftHeightOffset = (pitchHeight * (-1.0f / 4 + 1.0f / 2));
			newInfo.m_frontRightHeightOffset = (pitchHeight * (-1.0f / 4 + 1.0f / 2));
			newInfo.m_rearLeftHeightOffset = SPRING_FACTOR * (pitchHeight * (-1.0f / 2 - 1.0f / 3));
			newInfo.m_rearRightHeightOffset = SPRING_FACTOR * (pitchHeight * (-1.0f / 2 - 1.0f / 3));
		}
		if (rollHeight > 0)
		{
			newInfo.m_frontRightHeightOffset += -SPRING_FACTOR * (rollHeight * (1.0f / 3 + 1.0f / 2));
			newInfo.m_rearRightHeightOffset += -SPRING_FACTOR * (rollHeight * (1.0f / 3 + 1.0f / 2));
			newInfo.m_rearLeftHeightOffset += rollHeight / 2 - rollHeight / 4;
			newInfo.m_frontLeftHeightOffset += rollHeight / 2 - rollHeight / 4;
		}
		else
		{
			newInfo.m_frontRightHeightOffset += -rollHeight * (1.0f / 2 - 1.0f / 4);
			newInfo.m_rearRightHeightOffset += -rollHeight * (1.0f / 2 - 1.0f / 4);
			newInfo.m_rearLeftHeightOffset += SPRING_FACTOR * (rollHeight * (1.0f / 3 + 1.0f / 2));
			newInfo.m_frontLeftHeightOffset += SPRING_FACTOR * (rollHeight * (1.0f / 3 + 1.0f / 2));
		}
		if (newInfo.m_frontLeftHeightOffset < m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset)
			m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset += (newInfo.m_frontLeftHeightOffset - m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset) / 2.0f;
		else
			m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset = newInfo.m_frontLeftHeightOffset;
		if (newInfo.m_frontRightHeightOffset < m_locoInfo->m_wheelInfo.m_frontRightHeightOffset)
			m_locoInfo->m_wheelInfo.m_frontRightHeightOffset += (newInfo.m_frontRightHeightOffset - m_locoInfo->m_wheelInfo.m_frontRightHeightOffset) / 2.0f;
		else
			m_locoInfo->m_wheelInfo.m_frontRightHeightOffset = newInfo.m_frontRightHeightOffset;
		if (newInfo.m_rearLeftHeightOffset < m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset)
			m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset += (newInfo.m_rearLeftHeightOffset - m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset) / 2.0f;
		else
			m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset = newInfo.m_rearLeftHeightOffset;
		if (newInfo.m_rearRightHeightOffset < m_locoInfo->m_wheelInfo.m_rearRightHeightOffset)
			m_locoInfo->m_wheelInfo.m_rearRightHeightOffset += (newInfo.m_rearRightHeightOffset - m_locoInfo->m_wheelInfo.m_rearRightHeightOffset) / 2.0f;
		else
			m_locoInfo->m_wheelInfo.m_rearRightHeightOffset = newInfo.m_rearRightHeightOffset;

		if (m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset < MAX_SUSPENSION_EXTENSION)
			m_locoInfo->m_wheelInfo.m_frontLeftHeightOffset = MAX_SUSPENSION_EXTENSION;
		if (m_locoInfo->m_wheelInfo.m_frontRightHeightOffset < MAX_SUSPENSION_EXTENSION)
			m_locoInfo->m_wheelInfo.m_frontRightHeightOffset = MAX_SUSPENSION_EXTENSION;
		if (m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset < MAX_SUSPENSION_EXTENSION)
			m_locoInfo->m_wheelInfo.m_rearLeftHeightOffset = MAX_SUSPENSION_EXTENSION;
		if (m_locoInfo->m_wheelInfo.m_rearRightHeightOffset < MAX_SUSPENSION_EXTENSION)
			m_locoInfo->m_wheelInfo.m_rearRightHeightOffset = MAX_SUSPENSION_EXTENSION;
	}

	Real divisor = 4;
	Real pitch = fabs(info.m_totalPitch - groundPitch);

	if (pitch > PI / 8)
		divisor = ((4 * PI / 8) + (1 * (pitch - PI / 8))) / pitch;
	info.m_totalZ += fabs(pitchHeight) / divisor;
	info.m_totalZ += fabs(rollHeight) / divisor;
}
