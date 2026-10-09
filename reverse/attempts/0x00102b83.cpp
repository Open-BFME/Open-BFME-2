// ?transitionLiveMode@W3DCamTransform@@QAEXPAVVector3@@0PAVView@@@Z
// partial score=0.95 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?transitionLiveMode@W3DCamTransform@@QAEXPAVVector3@@0PAVView@@@Z,
// retail 0x00102B83..0x00102F83 (1024B), thiscall ret 0xC; sole caller is the
// W3DView camera update near 0x00103A6F, which passes the view as the third
// argument.
//
// Live-camera transition state machine (state at +0x28, target at +0x2C and
// position at +0x38). The current live mode name (global AsciiString
// 0x00DEC290) selects "Target" (2) or "Zoom" (3). Losing the controlled object
// (view +0xA4) resets the timers and the state. State 2 eases the target
// towards the object with an accelerating zoom timer, state 3 eases both target
// and position (after a screen-centre terrain query on TheTacticalView) and
// states 0, 1 and 4 hand over between them; reaching state 3 in the requested
// mode sets the view's +0xB4 / +0xB8 pair to 16 / 2.
//
// Evidence (target): WorldBuilder twin 0x7E73D0 is
// W3DCamTransform::transitionLiveMode in W3DCamTransform.cpp (asserts
// "W3DView-TransitionLiveCamera - no controlled object" at lines 529 and 569)
// and inlines Vector3::Lerp; two guarded static Vector3s (the second unused in
// retail), four zero-initialised static timers and four tuning statics
// (0.5 / 0.05 and 0.4 / 0.03). Callees StringBase::compare(text) 0x000069B1 and
// GameLogic::findObjectByID 0x00049DC5 (rowed).

#include "ascii_string.h"
#include "Coord3D.h"
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;

	Vector3() {}
	Vector3(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}

	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}

	void Set(Real x, Real y, Real z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	static __forceinline void Lerp(const Vector3 &a, const Vector3 &b, Real alpha, Vector3 *set_result)
	{
		set_result->X = (a.X + (b.X - a.X) * alpha);
		set_result->Y = (a.Y + (b.Y - a.Y) * alpha);
		set_result->Z = (a.Z + (b.Z - a.Z) * alpha);
	}
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_pos;					// +0x38
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class View
{
public:
	PAD_VIRTUALS10(v0) PAD_VIRTUALS10(v1) PAD_VIRTUALS10(v2) PAD_VIRTUALS10(v3) PAD_VIRTUALS10(v4)
	PAD_VIRTUALS10(v5) PAD_VIRTUALS10(v6) PAD_VIRTUALS10(v7) PAD_VIRTUALS10(v8)
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);	// slot 90

	unsigned char m_pad004[0x9C - 0x04];
	Bool m_9c;					// +0x9C
	unsigned char m_pad09d[0xA4 - 0x9D];
	ObjectID m_cameraLock;				// +0xA4
	unsigned char m_pad0a8[0xB4 - 0xA8];
	Int m_b4;					// +0xB4
	Int m_b8;					// +0xB8
	Int m_width;					// +0xBC
	Int m_height;					// +0xC0
};

extern View *TheTacticalView;
extern GameLogic *TheGameLogic;
extern unsigned int g_Va00DEC290;	// live camera mode name (AsciiString)

class W3DCamTransform
{
public:
	void transitionLiveMode(Vector3 *pos, Vector3 *target, View *view);
private:
	unsigned char m_pad00[0x28];
	Int m_liveState;				// +0x28
	Vector3 m_liveTarget;				// +0x2C
	Vector3 m_livePos;				// +0x38
};

static __forceinline const AsciiString &liveModeName()
{
	return *(const AsciiString *)&g_Va00DEC290;
}

void W3DCamTransform::transitionLiveMode(Vector3 *pos, Vector3 *target, View *view)
{
	static Vector3 startPos;
	static Vector3 unusedPos;
	static Real zoomT = 0.0f;
	static Real zoomSpeed = 0.0f;
	static Real targetT = 0.0f;
	static Real targetSpeed = 0.0f;
	static Real targetMaxSpeed = 0.5f;
	static Real targetAccel = 0.05f;
	static Real zoomMaxSpeed = 0.4f;
	static Real zoomAccel = 0.03f;

	Int liveMode = -1;
	if (liveModeName().compare("Target") == 0)
		liveMode = 2;
	else if (liveModeName().compare("Zoom") == 0)
		liveMode = 3;

	Object *obj = TheGameLogic->findObjectByID(view->m_cameraLock);
	if (!obj)
	{
		zoomT = targetT = 0.0f;
		zoomSpeed = targetSpeed = 0.0f;
		m_liveState = 0;
	}

	if (!view->m_9c)
	{
		m_liveTarget = *target;
		m_livePos = *pos;
	}

	switch (m_liveState)
	{
		case 0:
			if (view->m_9c)
			{
				m_liveState = 3;
				if (liveMode == m_liveState)
				{
					startPos = m_livePos;
					view->m_b4 = 16;
					view->m_b8 = 2;
				}
			}
			break;

		case 1:
			if (!view->m_9c)
				m_liveState = 4;
			break;

		case 2:
		{
			Real maxSpeed = zoomMaxSpeed;
			Real accel = zoomAccel;
			zoomT += zoomSpeed;
			if (zoomSpeed < maxSpeed)
				zoomSpeed += accel;

			Object *lockObj = TheGameLogic->findObjectByID(view->m_cameraLock);
			Vector3 objPos;
			objPos.Set(lockObj->getPosition()->x, lockObj->getPosition()->y, lockObj->getPosition()->z);
			Vector3::Lerp(m_liveTarget, objPos, zoomT, target);
			*pos = m_livePos;
			if (zoomT >= 1.0f)
			{
				m_liveState = 3;
				zoomT = 0.0f;
				zoomSpeed = 0.0f;
				startPos = m_livePos;
				if (liveMode == m_liveState)
				{
					view->m_b4 = 16;
					view->m_b8 = 2;
				}
			}
			break;
		}

		case 3:
		{
			Real maxSpeed = targetMaxSpeed;
			Real accel = targetAccel;
			targetT += targetSpeed;
			if (targetSpeed < maxSpeed)
				targetSpeed += accel;

			if (targetT < 0.9f)
			{
				Object *lockObj = TheGameLogic->findObjectByID(view->m_cameraLock);
				Vector3 objPos;
				objPos.Set(lockObj->getPosition()->x, lockObj->getPosition()->y, lockObj->getPosition()->z);
				Coord3D world;
				ICoord2D center;
				center.x = view->m_width / 2;
				center.y = view->m_height / 2;
				TheTacticalView->screenToTerrain(&center, &world, false);
				Vector3::Lerp(m_liveTarget, objPos, targetT, target);
				Vector3::Lerp(startPos, m_liveTarget, targetT, pos);
			}
			else
			{
				m_liveState = 1;
				targetT = 0.0f;
				targetSpeed = 0.0f;
				view->m_b4 = 0;
				view->m_b8 = 0;
			}
			break;
		}

		case 4:
			m_liveState = 0;
			break;
	}
}
