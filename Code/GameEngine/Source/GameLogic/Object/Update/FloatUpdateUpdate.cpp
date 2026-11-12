// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// platformsdk
//
// FloatUpdate::update (BFME 2), from the Generals Zero Hour FloatUpdate.cpp.
//
// The ZH body compiles to retail's code under this region's SSE flags. The
// ZH-port unit FloatUpdate.cpp builds without them and keeps its copy
// present-unmatched. Target facts that differ from the ZH headers:
// - TerrainLogic::isUnderwater sits in vftable slot 19 and takes one more
//   trailing argument, which this call passes as 0 (see the
//   FlammableUpdateDtor.cpp view).
// - GameLogic's frame counter is at +0x40.
// - Drawable's instance matrix is at +0x1A0. setInstanceMatrix is the rowed
//   two-argument 0x002711C6; preservePrevious is false here.
// update is slot 0 of FloatUpdate's UpdateModuleInterface vftable; m_enabled
// is at +0x20 (the rowed ctor 0x0048D7C4 copies it from the module data).
// Keep MSVC's float overloads local; the matched trig operations inline.
#define inline static inline
#include <math.h>
#undef inline
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define INT_TO_REAL(x) ((Real)(x))

class Thing;
class ModuleData;

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

class Matrix3D
{
public:
	__forceinline Matrix3D(const Matrix3D &matrix3D)
	{
		Row[0] = matrix3D.Row[0];
		Row[1] = matrix3D.Row[1];
		Row[2] = matrix3D.Row[2];
	}

	float Get_Z_Rotation(void) const;

	__forceinline void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

	__forceinline void Rotate_X(float theta)
	{
		float tmp1, tmp2;
		float s, c;

		s = sinf(theta);
		c = cosf(theta);

		tmp1 = Row[0][1]; tmp2 = Row[0][2];
		Row[0][1] = (float)( c*tmp1 + s*tmp2);
		Row[0][2] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[1][1]; tmp2 = Row[1][2];
		Row[1][1] = (float)( c*tmp1 + s*tmp2);
		Row[1][2] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[2][1]; tmp2 = Row[2][2];
		Row[2][1] = (float)( c*tmp1 + s*tmp2);
		Row[2][2] = (float)(-s*tmp1 + c*tmp2);
	}

	__forceinline void Rotate_Y(float theta)
	{
		float tmp1, tmp2;
		float s, c;

		s = sinf(theta);
		c = cosf(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][2];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[0][2] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][2];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][2];
		Row[2][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
	}

	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float c, s;

		c = cosf(theta);
		s = sinf(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( c*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
	}

	Vector4 Row[3];
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Drawable
{
public:
	__declspec(dllimport) __forceinline const Matrix3D *getInstanceMatrix() const { return &m_instance; }
	// BFME 2's setInstanceMatrix (0x002711C6) adds preservePrevious.
	void setInstanceMatrix(const Matrix3D *instance, Bool preservePrevious);

private:
	char m_unknown000[0x1A0];
	Matrix3D m_instance; // +0x1A0
};

class Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	void setPosition(const Coord3D *pos);
	Drawable *getDrawable() const;

private:
	char m_unknown00[0x38];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
};

#include "../../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

#include "../../../Common/GameLogicObjectLookupView.h"
#include <windows.h>

extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/BehaviorModuleBase.h"

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class FloatUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

private:
	Bool m_enabled; // +0x20
};

// ?update@FloatUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048D813 945B
UpdateSleepTime FloatUpdate::update( void )
{
/// @todo srj use SLEEPY_UPDATE here

	// if we're not enabled, do nothing
	if( m_enabled == TRUE )
	{
		// get object position
		const Coord3D *pos = getObject()->getPosition();

		// get the height of the water here
		Real waterZ;
		TheTerrainLogic->isUnderwater( pos->x, pos->y, &waterZ );

		// snap to the water surface
		Coord3D newPos;
		newPos.x = pos->x;
		newPos.y = pos->y;
		newPos.z = waterZ;
		getObject()->setPosition( &newPos );

	}

	Drawable *draw = getObject()->getDrawable();
	if (draw)
	{

		Real angle = INT_TO_REAL(TheGameLogic->getFrame());
		Real yaw = sin(angle * 0.0291f) * 0.05f;
		Real pitch = sin(angle * 0.0515f) * 0.05f;

		Matrix3D mx = *draw->getInstanceMatrix();

		Real zRot = mx.Get_Z_Rotation();
		mx.Make_Identity();
		mx.Rotate_Z(zRot);
		mx.Rotate_Y(yaw);
		mx.Rotate_X(pitch);

		draw->setInstanceMatrix(&mx, false);
	}

	return UPDATE_SLEEP_NONE;
}  // end update
