// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// ?updateSway@SwayClientUpdate@@IAEXXZ, retail 0x004C9125, 278 bytes.
// ?clientUpdate@SwayClientUpdate@@UAEXXZ, retail 0x004C923B, 714 bytes.
// ?loadPostProcess@SwayClientUpdate@@MAEXXZ, retail 0x004C9593, 5 bytes.
//
// Donor: BFME 1's SwayClientUpdate.cpp (reference/open-bfme-1/game/
// GameEngine/Source/GameClient/Drawable/Update/SwayClientUpdate.cpp), over
// Zero Hour's. Target facts:
// - The class is the one the rowed ctor 0x004C908B builds: ZH's members
//   from +0x0C to +0x23 and two BFME floats
//   at +0x24/+0x28, the sine and cosine of the breeze direction relative to
//   the drawable's facing, which updateSway writes and clientUpdate scales
//   the X and Y sway by.
// - TheScriptEngine's breeze info is at +0x1A4A8 (direction +0, intensity
//   +0x0C, lean +0x10, randomness +0x14, period +0x18, version +0x1A).
// - updateSway reads the frames-per-second int at TheGameEngine+0x38 (BFME 1
//   reads +0x34) and the drawable's facing through the pinned
//   Drawable::getTransformMatrix 0x0027628E. Its three client-random calls
//   push the retail file string 0x00C5EAC8 with lines 73, 74 and 75.
// - The vftable 0x00C5EA8C (installed by the ctor) holds loadPostProcess in
//   slot 1, the xfer 0x004C9505 in slot 3, the "SwayClientUpdate" pool key
//   0x004C90E0 in slot 4 and clientUpdate in slot 12. As in ZH,
//   loadPostProcess extends the empty base and re-runs updateSway, a tail
//   jump.
// - clientUpdate tests the drawable's visible byte at +0x441, copies the
//   instance matrix at +0x1A0 and hands it to the two-argument
//   setInstanceMatrix (0x002711C6) with false. The burned test is the rowed
//   Object::testStatus (0x0004E536) with status 11, and the dead test is the
//   private-status bit 0 at Object+0x438.

#include "matrix3d.h"

typedef bool Bool;
typedef int Int;
typedef short Short;
typedef unsigned char UnsignedByte;
typedef float Real;

#define PI 3.14159265359f

Real Sin(Real x);
Real Cos(Real x);

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);
#define GameClientRandomValueReal(lo, hi) GetGameClientRandomValueReal((lo), (hi), __FILE__, __LINE__)

struct BreezeInfo
{
	Real m_direction; // +0x00
	Real m_directionVec[2]; // +0x04
	Real m_intensity; // +0x0C
	Real m_lean; // +0x10
	Real m_randomness; // +0x14
	Short m_breezePeriod; // +0x18
	Short m_breezeVersion; // +0x1A
};

class ScriptEngine
{
public:
	const BreezeInfo &getBreezeInfo() const { return m_breezeInfo; }

private:
	unsigned char m_pad00000[0x1A4A8];
	BreezeInfo m_breezeInfo; // +0x1A4A8
};

extern ScriptEngine *TheScriptEngine;

class GameEngine
{
public:
	// The conversion sits in the getter: an int read in the expression is
	// scheduled ahead of the random call, retail reads it after.
	Real getFramesPerSecond() const { return (Real)m_framesPerSecond; }

private:
	unsigned char m_pad000[0x38];
	Int m_framesPerSecond; // +0x38
};

extern GameEngine *TheGameEngine;

enum ObjectStatusTypes
{
	OBJECT_STATUS_BURNED = 11
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	unsigned char m_pad000[0x438];
	UnsignedByte m_privateStatus; // +0x438
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	const Matrix3D *getInstanceMatrix() const { return &m_instance; }
	void setInstanceMatrix(const Matrix3D *instance, Bool preservePrevious);
	Object *getObject() { return m_object; }
	Bool isVisible() const { return m_isVisible; }

private:
	unsigned char m_pad000[0xFC];
	Object *m_object; // +0xFC
	unsigned char m_pad100[0x1A0 - 0x100];
	Matrix3D m_instance; // +0x1A0
	unsigned char m_pad1d0[0x441 - 0x1D0];
	Bool m_isVisible; // +0x441
};

class ModuleData;

class Module
{
public:
	virtual ~Module();

private:
	const ModuleData *m_moduleData; // +0x04
};

class DrawableModule : public Module
{
protected:
	Drawable *getDrawable() const { return m_drawable; }

private:
	Drawable *m_drawable; // +0x08
};

class ClientUpdateModule : public DrawableModule
{
public:
	virtual void clientUpdate() = 0;
};

class SwayClientUpdate : public ClientUpdateModule
{
public:
	virtual void clientUpdate();

	void stopSway() { m_swaying = false; }

protected:
	Real m_curValue; // +0x0C
	Real m_curAngle; // +0x10
	Real m_curDelta; // +0x14
	Real m_curAngleLimit; // +0x18
	Real m_leanAngle; // +0x1C
	Short m_curVersion; // +0x20
	Bool m_swaying; // +0x22
	Bool m_unused; // +0x23
	Real m_directionSin; // +0x24
	Real m_directionCos; // +0x28

	void updateSway();

	virtual void loadPostProcess();
};

// ?updateSway@SwayClientUpdate@@IAEXXZ
void SwayClientUpdate::updateSway()
{
	const BreezeInfo &info = TheScriptEngine->getBreezeInfo();
	if (info.m_randomness == 0.0f)
	{
		m_curValue = 0;
	}
	Real delta = info.m_randomness * 0.5f;
#line 73 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable\\Update\\SwayClientUpdate.cpp"
	m_curAngleLimit = info.m_intensity * GameClientRandomValueReal(1.0f - delta, 1.0f + delta);
	m_curDelta = 2 * PI / (TheGameEngine->getFramesPerSecond() * info.m_breezePeriod) * GameClientRandomValueReal(1.0f - delta, 1.0f + delta);
	m_leanAngle = info.m_lean * GameClientRandomValueReal(1.0f - delta, 1.0f + delta);
	m_curVersion = info.m_breezeVersion;
	Drawable *draw = getDrawable();
	if (draw)
	{
		Real angle = info.m_direction - draw->getTransformMatrix()->Get_Z_Rotation();
		m_directionSin = Sin(angle);
		m_directionCos = Cos(angle);
	}
}

// ?clientUpdate@SwayClientUpdate@@UAEXXZ
void SwayClientUpdate::clientUpdate()
{
	if (!m_swaying)
		return;

	Drawable *draw = getDrawable();

	// if breeze changes, always process the full update, even if not visible,
	// so that things offscreen won't 'pop' when first viewed
	if (TheScriptEngine->getBreezeInfo().m_breezeVersion != m_curVersion)
	{
		updateSway();
	}
	else
	{
		// Otherwise, only update visible drawables
		if (!draw || !draw->isVisible())
			return;
	}

	m_curValue += m_curDelta;
	if (m_curValue > 2*PI)
		m_curValue -= 2*PI;
	Real cosine = Sin(m_curValue);

	Real targetAngle = cosine * m_curAngleLimit + m_leanAngle;
	Real deltaAngle = targetAngle - m_curAngle;

	Matrix3D xfrm = *draw->getInstanceMatrix();
	xfrm.In_Place_Pre_Rotate_X(-deltaAngle * m_directionSin);
	xfrm.In_Place_Pre_Rotate_Y(deltaAngle * m_directionCos);
	draw->setInstanceMatrix(&xfrm, false);

	m_curAngle = targetAngle;

	// burned things don't sway.
	Object *obj = draw->getObject();
	if (obj && (obj->testStatus(OBJECT_STATUS_BURNED) || obj->isEffectivelyDead()))
		stopSway();
}

// ?loadPostProcess@SwayClientUpdate@@MAEXXZ
void SwayClientUpdate::loadPostProcess()
{
	// extend base class (empty)
	updateSway();
}
