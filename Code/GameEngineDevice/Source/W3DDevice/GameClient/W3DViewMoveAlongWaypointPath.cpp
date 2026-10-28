// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// W3DView::moveAlongWaypointPath, retail 0x00086F56 (1276B, RET4).
// Semantic guide: Zero Hour W3DView.cpp moveAlongWaypointPath (carried
// through Open-BFME-1 575ba2b04); donor names are not target facts.
// Target evidence: W3DView::updateCameraMovements (0x0008B010) calls this in
// camera mode 1 with TheW3DFrameLengthInMsec, and cameraModLookToward
// (0x000892CB REL32) calls it with 1, so the existing pin carries the private
// W3DView name. Native bytes prove every offset below: the waypoint path at
// +0x280 (the canonical array owner), mode +0x2354, the freeze byte +0x23D0,
// time multiplier +0x23D4, camera offset +0x23E8, ground +0x2408, constraint
// region +0x240C and the offset provider at +0x24C8 (virtual slot 18).
// BFME departs from Zero Hour in four target-proven places: segment distance is
// accumulated in m_1C instead of subtracted, arrival is the W3DView slot 28
// virtual with the waypoint ID, ground blends the path's two ground endpoints
// by the eased time, and the camera offset comes from the +0x24C8 provider
// scaled by +0xA0. The exit clamps are an if/else-if pair (no hi store when lo
// moves); a reference helper keeps retail's direct field stores.

#include "../../../../GameEngine/Include/GameClient/Rva0008990CArrayOwner.h"
#include "../../../../GameEngine/Source/GameClient/Rva000869CF.h"
#include <math.h>

typedef int Int;
typedef bool Bool;
typedef Rva00089894Point Coord3D;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// The +0x24C8 member fills the camera offset through its slot 18.
#define BFME_OFFSET_SLOT(n) virtual void slot##n();
class W3DCameraOffsetProvider
{
public:
	BFME_OFFSET_SLOT(0)  BFME_OFFSET_SLOT(1)  BFME_OFFSET_SLOT(2)
	BFME_OFFSET_SLOT(3)  BFME_OFFSET_SLOT(4)  BFME_OFFSET_SLOT(5)
	BFME_OFFSET_SLOT(6)  BFME_OFFSET_SLOT(7)  BFME_OFFSET_SLOT(8)
	BFME_OFFSET_SLOT(9)  BFME_OFFSET_SLOT(10) BFME_OFFSET_SLOT(11)
	BFME_OFFSET_SLOT(12) BFME_OFFSET_SLOT(13) BFME_OFFSET_SLOT(14)
	BFME_OFFSET_SLOT(15) BFME_OFFSET_SLOT(16) BFME_OFFSET_SLOT(17)
	virtual void getCameraOffset(Coord3D *offset, Int unused);
};
#undef BFME_OFFSET_SLOT

struct W3DCameraRegion
{
	struct { Real x, y; } lo, hi;
};

#define BFME_W3D_SLOT(n) virtual void slot##n() = 0;

class W3DView
{
public:
	BFME_W3D_SLOT(0)  BFME_W3D_SLOT(1)  BFME_W3D_SLOT(2)
	BFME_W3D_SLOT(3)  BFME_W3D_SLOT(4)  BFME_W3D_SLOT(5)
	BFME_W3D_SLOT(6)  BFME_W3D_SLOT(7)  BFME_W3D_SLOT(8)
	BFME_W3D_SLOT(9)  BFME_W3D_SLOT(10) BFME_W3D_SLOT(11)
	BFME_W3D_SLOT(12) BFME_W3D_SLOT(13) BFME_W3D_SLOT(14)
	BFME_W3D_SLOT(15) BFME_W3D_SLOT(16) BFME_W3D_SLOT(17)
	BFME_W3D_SLOT(18) BFME_W3D_SLOT(19) BFME_W3D_SLOT(20)
	BFME_W3D_SLOT(21) BFME_W3D_SLOT(22) BFME_W3D_SLOT(23)
	BFME_W3D_SLOT(24) BFME_W3D_SLOT(25) BFME_W3D_SLOT(26)
	BFME_W3D_SLOT(27)
	virtual void slot28(Int waypointID) = 0;

private:
	void moveAlongWaypointPath(Int milliseconds);

	char m_padding004[0x0C - 4];
	Coord3D m_pos;
	char m_padding018[0x28 - 0x18];
	Real m_angle;
	char m_padding02C[0xA0 - 0x2C];
	Real m_cameraOffsetScale;
	char m_padding0A4[0x280 - 0xA4];
	Rva0089971 m_mcwpInfo;
	char m_padding22F4[0x2354 - 0x22F4];
	Int m_cameraMovementMode;
	char m_padding2358[0x23D0 - 0x2358];
	Bool m_freezeTimeForCameraMovement;
	Int m_timeMultiplier;
	char m_padding23D8[0x23E8 - 0x23D8];
	Coord3D m_cameraOffset;
	char m_padding23F4[0x2408 - 0x23F4];
	Real m_groundLevel;
	W3DCameraRegion m_cameraConstraint;
	char m_padding241C[0x24C8 - 0x241C];
	W3DCameraOffsetProvider m_cameraOffsetProvider;
};

#undef BFME_W3D_SLOT

// Zero Hour's file-static normAngle (0x000855D1, rowed in
// W3DViewRotateCamera.cpp). Retail passes the angle's address in EAX, MSVC
// 7.1's register convention for a static it keeps out of line.
#pragma auto_inline(off)
static void normAngle(Real &angle)
{
	if (angle < -10*3.14159265359f) {
		angle = 0;
	}
	if (angle > 10*3.14159265359f) {
		angle = 0;
	}
	while (angle < -3.14159265359f) {
		angle += 2*3.14159265359f;
	}
	while (angle > 3.14159265359f) {
		angle -= 2*3.14159265359f;
	}
}
#pragma auto_inline(on)

// BaseType.h verbatim: retail holds the inline fld/fistp (x87 blocker).
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

static __forceinline Real interpolate(Real a, Real b, Real factor)
{
	return a + (b - a)*factor;
}

static inline void extendConstraint(Real &lo, Real &hi, Real coordinate)
{
	if (lo > coordinate) lo = coordinate;
	else if (coordinate > hi) hi = coordinate;
}

void W3DView::moveAlongWaypointPath(Int milliseconds)
{
	m_mcwpInfo.m_08 += milliseconds;
	// Zero Hour reads m_disableCameraMovement here; the target flag is +0x9A4.
	if (((unsigned char *)TheWritableGlobalData)[0x9A4]) {
		if (m_mcwpInfo.m_08 > m_mcwpInfo.m_04) {
			reinterpret_cast<Rva000869CF *>(this)->rva000869CF();
			m_freezeTimeForCameraMovement = false;
		}
		return;
	}
	if (m_mcwpInfo.m_08 > m_mcwpInfo.m_04) {
		m_cameraMovementMode = 0;
		slot28(0);
		m_freezeTimeForCameraMovement = false;
		m_angle = m_mcwpInfo.m_cameraAngles[m_mcwpInfo.m_numValues];
		m_groundLevel = m_mcwpInfo.m_groundEnd;
		m_cameraOffsetProvider.getCameraOffset(&m_cameraOffset, 0);
		m_cameraOffset.x *= m_cameraOffsetScale;
		m_cameraOffset.y *= m_cameraOffsetScale;

		const Coord3D &last = m_mcwpInfo.m_arr255[m_mcwpInfo.m_numValues].m_position;
		Coord3D pos;
		pos.x = last.x;
		pos.y = last.y;
		pos.z = 0;
		m_pos = pos;
		// Note - assuming that the scripter knows what he is doing, we adjust the constraints so that
		// the scripted action can occur.
		extendConstraint(m_cameraConstraint.lo.x, m_cameraConstraint.hi.x, pos.x);
		extendConstraint(m_cameraConstraint.lo.y, m_cameraConstraint.hi.y, pos.y);
		return;
	}

	const Real invTotalTime = 1.0f/m_mcwpInfo.m_04;
	const Real ease = m_mcwpInfo.m_10(m_mcwpInfo.m_08*invTotalTime);
	const Real deltaTime = ease - m_mcwpInfo.m_10((m_mcwpInfo.m_08 - milliseconds)*invTotalTime);
	m_mcwpInfo.m_18 += deltaTime*m_mcwpInfo.m_totalDistance;
	while (m_mcwpInfo.m_18 - m_mcwpInfo.m_1C >= m_mcwpInfo.m_values[m_mcwpInfo.m_20]) {
		slot28(m_mcwpInfo.m_arr255[m_mcwpInfo.m_20].m_10);
		m_mcwpInfo.m_1C += m_mcwpInfo.m_values[m_mcwpInfo.m_20];
		++m_mcwpInfo.m_20;
		if (m_mcwpInfo.m_20 >= m_mcwpInfo.m_numValues) {
			m_mcwpInfo.m_04 = 0; // Will end following next frame.
			return;
		}
	}
	Real avgFactor = 1.0f/m_mcwpInfo.m_28;
	Real factor = (m_mcwpInfo.m_18 - m_mcwpInfo.m_1C)/m_mcwpInfo.m_values[m_mcwpInfo.m_20];
	if (m_mcwpInfo.m_20 == m_mcwpInfo.m_numValues - 1) {
		avgFactor = avgFactor + (1.0f - avgFactor)*factor;
	}
	Real angle1 = m_mcwpInfo.m_cameraAngles[m_mcwpInfo.m_20];
	Real angle2 = m_mcwpInfo.m_cameraAngles[m_mcwpInfo.m_20 + 1];
	if (angle2 - angle1 > 3.14159265359f) angle1 += 2*3.14159265359f;
	if (angle2 - angle1 < -3.14159265359f) angle1 -= 2*3.14159265359f;
	Real angle = angle1 + (angle2 - angle1)*factor;

	normAngle(angle);
	Real deltaAngle = angle - m_angle;
	normAngle(deltaAngle);
	fabs((double)deltaAngle); // Zero Hour's "Huh." debug check, compiled out
	m_angle += avgFactor*deltaAngle;
	normAngle(m_angle);

	Real timeMultiplier = (Real)m_mcwpInfo.m_filled[m_mcwpInfo.m_20] +
		((Real)m_mcwpInfo.m_filled[m_mcwpInfo.m_20 + 1] - (Real)m_mcwpInfo.m_filled[m_mcwpInfo.m_20])*factor;
	m_timeMultiplier = fast_float2long_round((float)floor(static_cast<double>(0.5f + timeMultiplier)));

	m_groundLevel = interpolate(m_mcwpInfo.m_groundStart, m_mcwpInfo.m_groundEnd, ease);
	m_cameraOffsetProvider.getCameraOffset(&m_cameraOffset, 0);
	m_cameraOffset.x *= m_cameraOffsetScale;
	m_cameraOffset.y *= m_cameraOffsetScale;

	Coord3D start, mid, end;
	Int seg = m_mcwpInfo.m_20;
	if (factor < 0.5f) {
		start = m_mcwpInfo.m_arr255[seg - 1].m_position;
		start.x += m_mcwpInfo.m_arr255[seg].m_position.x;
		const Coord3D &cur = m_mcwpInfo.m_arr255[seg].m_position;
		start.y += cur.y;
		start.x /= 2;
		start.y /= 2;
		mid = cur;
		end = cur;
		const Coord3D &next = m_mcwpInfo.m_arr255[seg + 1].m_position;
		end.x += next.x;
		end.y += next.y;
		end.x /= 2;
		end.y /= 2;
		factor += 0.5f;
	} else {
		start = m_mcwpInfo.m_arr255[seg].m_position;
		start.x += m_mcwpInfo.m_arr255[seg + 1].m_position.x;
		const Coord3D &cur = m_mcwpInfo.m_arr255[seg + 1].m_position;
		start.y += cur.y;
		start.x /= 2;
		start.y /= 2;
		mid = cur;
		end = cur;
		const Coord3D &next = m_mcwpInfo.m_arr255[seg + 2].m_position;
		end.x += next.x;
		end.y += next.y;
		end.x /= 2;
		end.y /= 2;
		factor -= 0.5f;
	}

	Coord3D result;
	result.z = 0;
	result.x = start.x + factor*(end.x - start.x);
	result.y = start.y + factor*(end.y - start.y);
	result.x += (1 - factor)*factor*(mid.x - end.x + mid.x - start.x);
	result.y += (1 - factor)*factor*(mid.y - end.y + mid.y - start.y);
	m_pos = result;
	extendConstraint(m_cameraConstraint.lo.x, m_cameraConstraint.hi.x, result.x);
	extendConstraint(m_cameraConstraint.lo.y, m_cameraConstraint.hi.y, result.y);
}
