// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include
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
#include <math.h>
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define TRUE 1
#define INT_TO_REAL(x) ((Real)(x))

class Thing;
class ModuleData;

class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline Vector4(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	__forceinline Vector4 &operator=(const Vector4 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = v.W;
		return *this;
	}
	__forceinline float &operator[](int i) { return (&X)[i]; }
	__forceinline void Set(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
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
	const Matrix3D *getInstanceMatrix() const { return &m_instance; }
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

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = 0, Real *terrainZ = 0, Int unused = 0);
};

extern TerrainLogic *TheTerrainLogic;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_unknown00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

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
