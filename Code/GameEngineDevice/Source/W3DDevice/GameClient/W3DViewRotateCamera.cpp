// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
//
// W3DView::rotateCamera (0x0008647C, 175B) and
// W3DView::rotateCameraTowardObject (0x0008652B, 176B), ported from Open-BFME-1's
// GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp (donor revision
// 6583b3c1ff21db4a561285717028fdafc780b7db).
//
// Identity: retail's W3DView vftable holds them in consecutive slots ahead of
// rotateCameraTowardPosition, which is the order the Zero Hour View declares
// them in. Compiling the BFME 1 donor bodies with W3DView.cpp's flags scored
// them 0.59 and 0.64 against those slots.
//
// BFME 2 changed both signatures, and the shared Zero Hour W3DView header
// still declares the old ones, so this unit declares the class itself. Each
// signature below is read off its retail body. rotateCamera returns 0x14: a
// byte argument after milliseconds that it stores at +0x2438.
// rotateCameraTowardObject returns 0x18: a trailing float that it stores at
// +0x1D8. Both now pass the duration to a three-argument ParabolicEase setter
// (0x0030E51F, RET 0xC) rather than normalizing the ease times themselves,
// and neither clears the waypoint-path flags.
//
// W3DView::rotateCameraTowardPosition (0x00088D65, 335B) is the next vftable
// slot and keeps Zero Hour's signature (RET 0x14), with the same BFME changes.
// It calls the file-static normAngle (0x000855D1, 121B), which retail
// reaches with the angle's address in EAX and no stack arguments. That is
// MSVC 7.1's register passing for a static function it does not inline, so
// normAngle is static here and auto_inline(off) keeps it out of line as
// retail's four call sites do. The Vector2 and WWMath::Sqrt/Acos inlines are
// the real WWMath headers; Sqrt is the library's own x87 fsqrt block.

#include "Lib/BaseType.h"
#include "vector2.h"
#include "wwmath.h"

enum ObjectID { INVALID_ID = 0 };

extern Int TheW3DFrameLengthInMsec;

// BFME's ParabolicEase setter also takes the duration it normalizes against.
class ParabolicEase
{
public:
	void setEaseTimes(Real easeInTime, Real easeOutTime, Real duration);
private:
	Real m_in;
	Real m_out;
};

class W3DView
{
public:
	virtual void rotateCamera(Real rotations, Int milliseconds, Bool flag, Real easeIn, Real easeOut);
	virtual void rotateCameraTowardObject(ObjectID id, Int milliseconds, Int holdMilliseconds, Real easeIn, Real easeOut, Real trailing);
	virtual void rotateCameraTowardPosition(const Coord3D *pLoc, Int milliseconds, Real easeIn, Real easeOut, Bool reverseRotation);
};

// BFME's W3DView rotate state as both bodies address it: m_rcInfo at +0x1AC
// (numFrames, curFrame, the time-multiplier pair, numHoldFrames, the ease,
// trackObject, the angle pair or target id, a trailing float),
// m_doingRotateCamera at +0x1DC, the time multiplier at +0x23D4 and the flag
// rotateCamera stores at +0x2438.
struct BfmeW3DViewRotateFields
{
	unsigned char m_padding0000[0x0C];
	Coord3D m_pos;
	unsigned char m_padding0018[0x28 - 0x18];
	Real m_angle;
	unsigned char m_padding002C[0x1AC - 0x2C];
	Int m_numFrames;
	Int m_curFrame;
	Int m_startTimeMultiplier;
	Int m_endTimeMultiplier;
	Int m_numHoldFrames;
	ParabolicEase m_ease;
	Bool m_trackObject;
	unsigned char m_padding01C9[3];
	union
	{
		struct
		{
			Real startAngle;
			Real endAngle;
		} m_rcAngle;
		ObjectID m_targetObjectID;
	};
	Real m_padding01D4;
	Real m_rcTrailing;
	Bool m_doingRotateCamera;
	unsigned char m_padding01DD[0x23D4 - 0x1DD];
	Int m_timeMultiplier;
	unsigned char m_padding23D8[0x2438 - 0x23D8];
	Bool m_rotateFlag;
};

void W3DView::rotateCamera(Real rotations, Int milliseconds, Bool flag, Real easeIn, Real easeOut)
{
	BfmeW3DViewRotateFields *fields = (BfmeW3DViewRotateFields *)this;
	fields->m_numHoldFrames = 0;
	fields->m_trackObject = false;

	if (milliseconds<1) milliseconds = 1;
	fields->m_numFrames = milliseconds/TheW3DFrameLengthInMsec;
	if (fields->m_numFrames < 1) {
		fields->m_numFrames = 1;
	}
	fields->m_curFrame = 0;
	fields->m_doingRotateCamera = true;
	fields->m_rcAngle.startAngle = fields->m_angle;
	fields->m_rcAngle.endAngle = fields->m_angle + 2*PI*rotations;
	fields->m_startTimeMultiplier = fields->m_timeMultiplier;
	fields->m_endTimeMultiplier = fields->m_timeMultiplier;
	fields->m_ease.setEaseTimes(easeIn, easeOut, (Real)milliseconds);

	fields->m_rotateFlag = flag;
}

void W3DView::rotateCameraTowardObject(ObjectID id, Int milliseconds, Int holdMilliseconds, Real easeIn, Real easeOut, Real trailing)
{
	BfmeW3DViewRotateFields *fields = (BfmeW3DViewRotateFields *)this;
	fields->m_trackObject = true;
	if (holdMilliseconds<1) holdMilliseconds = 0;
	fields->m_numHoldFrames = holdMilliseconds/TheW3DFrameLengthInMsec;
	if (fields->m_numHoldFrames < 1) {
		fields->m_numHoldFrames = 0;
	}

	if (milliseconds<1) milliseconds = 1;
	fields->m_numFrames = milliseconds/TheW3DFrameLengthInMsec;
	if (fields->m_numFrames < 1) {
		fields->m_numFrames = 1;
	}
	fields->m_curFrame = 0;
	fields->m_doingRotateCamera = true;
	fields->m_targetObjectID = id;
	fields->m_startTimeMultiplier = fields->m_timeMultiplier;
	fields->m_endTimeMultiplier = fields->m_timeMultiplier;
	fields->m_ease.setEaseTimes(easeIn, easeOut, (Real)milliseconds);

	fields->m_rcTrailing = trailing;
}

//-------------------------------------------------------------------------------------------------
// Normalizes angle to +- PI.
//-------------------------------------------------------------------------------------------------
#pragma auto_inline(off)
static void normAngle(Real &angle)
{
	if (angle < -10*PI) {
		angle = 0;
	}
	if (angle > 10*PI) {
		angle = 0;
	}
	while (angle < -PI) {
		angle += 2*PI;
	}
	while (angle > PI) {
		angle -= 2*PI;
	}
}
#pragma auto_inline(on)

void W3DView::rotateCameraTowardPosition(const Coord3D *pLoc, Int milliseconds, Real easeIn, Real easeOut, Bool reverseRotation)
{
	BfmeW3DViewRotateFields *fields = (BfmeW3DViewRotateFields *)this;
	fields->m_numHoldFrames = 0;
	fields->m_trackObject = false;

	if (milliseconds<1) milliseconds = 1;
	fields->m_numFrames = milliseconds/TheW3DFrameLengthInMsec;
	if (fields->m_numFrames < 1) {
		fields->m_numFrames = 1;
	}
	const Coord3D *curPos = &fields->m_pos;
	Vector2 pos(curPos->x, curPos->y);
	Vector2 dir(pLoc->x - pos.X, pLoc->y - pos.Y);
	const Real dirLength = dir.Length();
	if (dirLength<0.1f) return;
	Real angle = WWMath::Acos(dir.X/dirLength);
	if (dir.Y<0.0f) {
		angle = -angle;
	}
	// Default camera is rotated 90 degrees, so match.
	angle -= PI/2;
	normAngle(angle);

	if (reverseRotation) {
		if (fields->m_angle < angle) {
			angle -= 2.0f*PI;
		} else {
			angle += 2.0f*PI;
		}
	}

	fields->m_curFrame = 0;
	fields->m_doingRotateCamera = true;
	fields->m_rcAngle.startAngle = fields->m_angle;
	fields->m_rcAngle.endAngle = angle;
	fields->m_startTimeMultiplier = fields->m_timeMultiplier;
	fields->m_endTimeMultiplier = fields->m_timeMultiplier;
	fields->m_ease.setEaseTimes(easeIn, easeOut, (Real)milliseconds);
}
