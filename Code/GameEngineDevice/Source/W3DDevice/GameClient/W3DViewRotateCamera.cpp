// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
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

#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern Int TheW3DFrameLengthInMsec;

// BFME's ParabolicEase setter also takes the duration it normalizes against.
class ParabolicEase
{
public:
	void setEaseTimes(Real easeInTime, Real easeOutTime, Real duration);
	Real operator()(Real param) const;
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
	virtual void cameraModFreezeAngle(void);
	void rva0008ADEA(Int unused, ObjectID id, Bool enable, Bool snap);
private:
	void rva0008AAD4(void);
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
	unsigned char m_padding002C[0x138 - 0x2C];
	Real m_trackHeight;			// +0x138
	unsigned char m_padding013C[0x1AC - 0x13C];
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
		struct
		{
			ObjectID id;
			Coord3D pos;
		} m_rcTarget;
	};
	Bool m_doingRotateCamera;
	unsigned char m_padding01DD[0x16E8 - 0x1DD];
	Real m_mcwpCameraAngle[(0x22F0 - 0x16E8) / 4];	// +0x16E8, m_mcwpInfo.cameraAngle
	Int m_mcwpNumWaypoints;				// +0x22F0
	unsigned char m_padding22F4[0x2354 - 0x22F4];
	Int m_doingMoveCameraOnWaypointPath;		// +0x2354, 1 while moving
	unsigned char m_padding2358[0x23D0 - 0x2358];
	Bool m_freezeTimeForCameraMovement;	// +0x23D0
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

	fields->m_rcTarget.pos.z = trailing;
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

//-------------------------------------------------------------------------------------------------
// ?rva0008ADEA@W3DView@@QAEXHW4ObjectID@@_N1@Z, retail 0x0008ADEA..0x0008AFDC
// (498B), W3DView vftable slot 116 (+0x1D0), RET 0x10. Starts or stops
// following an object with the camera. Turning it off goes through slot
// +0x1DC (0x00087642, which restores the camera saved here). Turning it on
// for an object whose +0x74 id differs from the followed id (slots +0x1D4 /
// +0x1D8) saves the camera into the file statics at VA 0x00DE2024..
// 0x00DE2067 unless already following, sets the follow flag +0x2449, the
// pitch limits (slot +0x210: -5 and 89 degrees), looks at the object's
// position (slot +0x54) and copies its template's +0x620 offset
// (0x000854CF) to +0x23E8. Unless already following without snap it also
// zooms (slot +0xF4) to the template's +0x62C degrees and sets the camera
// angle from the object's orientation +0x44 (less a quarter turn when
// +0x2493 is set; zero when +0x2491 is set) through the file-static
// normAngle 0x000855D1, which takes the angle's address in EAX: that private
// register convention is why this body lives in normAngle's unit. Every
// path but an already-following start resets the mouse (TheMouse
// 0x001EDE9C).
//-------------------------------------------------------------------------------------------------
extern float g_Va00DE2024;
extern float g_Va00DE2028;
extern float g_Va00DE202C;
extern float g_Va00DE2030;
extern float g_Va00DE2034;
extern float g_Va00DE2038;
extern float g_Va00DE203C;
extern Coord3D g_Va00DE2050;
extern Coord3D g_Va00DE205C;

extern GameLogic *TheGameLogic;

class Mouse
{
public:
	void rva001EDE9C();
};

extern Mouse *TheMouse;

struct Out12
{
	Real x, y, z;
};

class Rva000854CF
{
public:
	Out12 *rva000854CF(Out12 *out);
};

// The followed object's template: an offset at +0x620 (read through
// 0x000854CF) and a zoom angle in degrees at +0x62C.
struct BfmeFollowTemplate
{
	unsigned char m_padding0000[0x62C];
	Real m_zoomDegrees;
	Real getZoomRadians() const { return m_zoomDegrees * 0.0174532924f; }
};

struct BfmeFollowObject
{
	void *m_vtable;
	BfmeFollowTemplate *m_template;		// +0x04
	unsigned char m_padding0008[0x38 - 0x08];
	Coord3D m_position;			// +0x38
	Real m_orientation;			// +0x44
	unsigned char m_padding0048[0x74 - 0x48];
	Int m_followID;				// +0x74
};

#define BFME_FOLLOW_SLOT(n) virtual void slot##n();

class BfmeW3DViewFollowSlots
{
public:
	BFME_FOLLOW_SLOT(0)   BFME_FOLLOW_SLOT(1)   BFME_FOLLOW_SLOT(2)   BFME_FOLLOW_SLOT(3)
	BFME_FOLLOW_SLOT(4)   BFME_FOLLOW_SLOT(5)   BFME_FOLLOW_SLOT(6)   BFME_FOLLOW_SLOT(7)
	BFME_FOLLOW_SLOT(8)   BFME_FOLLOW_SLOT(9)   BFME_FOLLOW_SLOT(10)  BFME_FOLLOW_SLOT(11)
	BFME_FOLLOW_SLOT(12)  BFME_FOLLOW_SLOT(13)  BFME_FOLLOW_SLOT(14)  BFME_FOLLOW_SLOT(15)
	BFME_FOLLOW_SLOT(16)  BFME_FOLLOW_SLOT(17)  BFME_FOLLOW_SLOT(18)  BFME_FOLLOW_SLOT(19)
	BFME_FOLLOW_SLOT(20)
	virtual void lookAt(const Coord3D *pos);			// +0x54
	BFME_FOLLOW_SLOT(22)  BFME_FOLLOW_SLOT(23)
	BFME_FOLLOW_SLOT(24)  BFME_FOLLOW_SLOT(25)  BFME_FOLLOW_SLOT(26)  BFME_FOLLOW_SLOT(27)
	BFME_FOLLOW_SLOT(28)  BFME_FOLLOW_SLOT(29)  BFME_FOLLOW_SLOT(30)  BFME_FOLLOW_SLOT(31)
	BFME_FOLLOW_SLOT(32)  BFME_FOLLOW_SLOT(33)  BFME_FOLLOW_SLOT(34)  BFME_FOLLOW_SLOT(35)
	BFME_FOLLOW_SLOT(36)  BFME_FOLLOW_SLOT(37)  BFME_FOLLOW_SLOT(38)  BFME_FOLLOW_SLOT(39)
	BFME_FOLLOW_SLOT(40)  BFME_FOLLOW_SLOT(41)  BFME_FOLLOW_SLOT(42)  BFME_FOLLOW_SLOT(43)
	BFME_FOLLOW_SLOT(44)  BFME_FOLLOW_SLOT(45)  BFME_FOLLOW_SLOT(46)  BFME_FOLLOW_SLOT(47)
	BFME_FOLLOW_SLOT(48)  BFME_FOLLOW_SLOT(49)  BFME_FOLLOW_SLOT(50)  BFME_FOLLOW_SLOT(51)
	BFME_FOLLOW_SLOT(52)  BFME_FOLLOW_SLOT(53)  BFME_FOLLOW_SLOT(54)  BFME_FOLLOW_SLOT(55)
	BFME_FOLLOW_SLOT(56)  BFME_FOLLOW_SLOT(57)  BFME_FOLLOW_SLOT(58)  BFME_FOLLOW_SLOT(59)
	BFME_FOLLOW_SLOT(60)
	virtual void zoomCamera(Real finalZoom, Bool flag, Real easeIn, Real easeOut);	// +0xF4
	BFME_FOLLOW_SLOT(62)  BFME_FOLLOW_SLOT(63)
	BFME_FOLLOW_SLOT(64)  BFME_FOLLOW_SLOT(65)  BFME_FOLLOW_SLOT(66)  BFME_FOLLOW_SLOT(67)
	BFME_FOLLOW_SLOT(68)  BFME_FOLLOW_SLOT(69)  BFME_FOLLOW_SLOT(70)  BFME_FOLLOW_SLOT(71)
	BFME_FOLLOW_SLOT(72)  BFME_FOLLOW_SLOT(73)  BFME_FOLLOW_SLOT(74)  BFME_FOLLOW_SLOT(75)
	BFME_FOLLOW_SLOT(76)  BFME_FOLLOW_SLOT(77)  BFME_FOLLOW_SLOT(78)  BFME_FOLLOW_SLOT(79)
	BFME_FOLLOW_SLOT(80)  BFME_FOLLOW_SLOT(81)  BFME_FOLLOW_SLOT(82)  BFME_FOLLOW_SLOT(83)
	BFME_FOLLOW_SLOT(84)  BFME_FOLLOW_SLOT(85)  BFME_FOLLOW_SLOT(86)  BFME_FOLLOW_SLOT(87)
	BFME_FOLLOW_SLOT(88)  BFME_FOLLOW_SLOT(89)  BFME_FOLLOW_SLOT(90)  BFME_FOLLOW_SLOT(91)
	BFME_FOLLOW_SLOT(92)  BFME_FOLLOW_SLOT(93)  BFME_FOLLOW_SLOT(94)  BFME_FOLLOW_SLOT(95)
	BFME_FOLLOW_SLOT(96)  BFME_FOLLOW_SLOT(97)  BFME_FOLLOW_SLOT(98)  BFME_FOLLOW_SLOT(99)
	BFME_FOLLOW_SLOT(100) BFME_FOLLOW_SLOT(101) BFME_FOLLOW_SLOT(102) BFME_FOLLOW_SLOT(103)
	BFME_FOLLOW_SLOT(104) BFME_FOLLOW_SLOT(105) BFME_FOLLOW_SLOT(106) BFME_FOLLOW_SLOT(107)
	BFME_FOLLOW_SLOT(108) BFME_FOLLOW_SLOT(109) BFME_FOLLOW_SLOT(110) BFME_FOLLOW_SLOT(111)
	BFME_FOLLOW_SLOT(112) BFME_FOLLOW_SLOT(113) BFME_FOLLOW_SLOT(114)
	virtual Bool isFollowing();				// +0x1CC
	BFME_FOLLOW_SLOT(116)
	virtual Int getFollowedID();				// +0x1D4
	virtual void setFollowedID(Int id);			// +0x1D8
	virtual void stopFollowing();				// +0x1DC
	BFME_FOLLOW_SLOT(120) BFME_FOLLOW_SLOT(121) BFME_FOLLOW_SLOT(122) BFME_FOLLOW_SLOT(123)
	BFME_FOLLOW_SLOT(124) BFME_FOLLOW_SLOT(125) BFME_FOLLOW_SLOT(126) BFME_FOLLOW_SLOT(127)
	BFME_FOLLOW_SLOT(128) BFME_FOLLOW_SLOT(129) BFME_FOLLOW_SLOT(130) BFME_FOLLOW_SLOT(131)
	virtual void setPitchLimits(Real low, Real high);	// +0x210
};

#undef BFME_FOLLOW_SLOT

struct BfmeW3DViewFollowFields
{
	unsigned char m_padding0000[0x0C];
	Coord3D m_pos;				// +0x0C
	unsigned char m_padding0018[0x28 - 0x18];
	Real m_angle;				// +0x28
	unsigned char m_padding002C[0x3C - 0x2C];
	Real m_3c;				// +0x3C
	unsigned char m_padding0040[0x50 - 0x40];
	Real m_50;				// +0x50
	unsigned char m_padding0054[0x6C - 0x54];
	Real m_6c;				// +0x6C
	Real m_zoom;				// +0x70
	unsigned char m_padding0074[0xAC - 0x74];
	Real m_ac;				// +0xAC
	Real m_b0;				// +0xB0
	unsigned char m_padding00B4[0x23E8 - 0xB4];
	Coord3D m_23e8;				// +0x23E8
	unsigned char m_padding23F4[0x2449 - 0x23F4];
	Bool m_following;			// +0x2449
	unsigned char m_padding244A[0x2491 - 0x244A];
	Bool m_2491;				// +0x2491
	Bool m_2492;				// +0x2492
	Bool m_2493;				// +0x2493
};

void W3DView::rva0008ADEA(Int unused, ObjectID id, Bool enable, Bool snap)
{
	BfmeW3DViewFollowSlots *view = (BfmeW3DViewFollowSlots *)this;
	BfmeW3DViewFollowFields *fields = (BfmeW3DViewFollowFields *)this;
	if (enable) {
		if (view->isFollowing())
			return;
		BfmeFollowObject *obj = (BfmeFollowObject *)TheGameLogic->findObjectByID(id);
		if (obj) {
			view->getFollowedID();
			Int objID = obj->m_followID;
			if (objID != view->getFollowedID()) {
				if (!fields->m_following) {
					Real saved6c = fields->m_6c;
					g_Va00DE2050 = fields->m_pos;
					g_Va00DE203C = saved6c;
					g_Va00DE2038 = fields->m_3c;
					Real saved50 = fields->m_50;
					g_Va00DE205C = fields->m_23e8;
					g_Va00DE2034 = saved50;
					g_Va00DE2030 = fields->m_angle;
					g_Va00DE202C = fields->m_zoom;
					g_Va00DE2028 = fields->m_ac;
					g_Va00DE2024 = fields->m_b0;
				}
				fields->m_following = true;
				view->setFollowedID(obj->m_followID);
				view->setPitchLimits(-0.0872664675f, 1.55334306f);
				view->lookAt(&obj->m_position);
				Out12 offset;
				fields->m_23e8 = *(Coord3D *)((Rva000854CF *)obj->m_template)->rva000854CF(&offset);
				if (!fields->m_following || snap) {
					Real zoom = obj->m_template->getZoomRadians();
					fields->m_zoom = zoom;
					view->zoomCamera(zoom, true, 0.0f, 0.0f);
					if (fields->m_2493)
						fields->m_angle = obj->m_orientation - PI/2;
					else if (fields->m_2491)
						fields->m_angle = 0.0f;
					else
						fields->m_angle = obj->m_orientation;
					normAngle(fields->m_angle);
					fields->m_6c = 0.87266463f;
				}
				fields->m_2492 = true;
			}
		}
	} else {
		view->stopFollowing();
	}
	TheMouse->rva001EDE9C();
}

//-------------------------------------------------------------------------------------------------
// ?rva0008AAD4@W3DView@@AAEXXZ, retail 0x0008AAD4..0x0008AD96 (706B), plain
// ret. Zero Hour's W3DView::rotateCameraOneFrame with BFME's changes: called
// by W3DView::updateCameraMovements (0x0008B010) on its own this while
// m_doingRotateCamera (+0x1DC) is set. With camera movement disabled
// (TheWritableGlobalData +0x9A4, as the one-frame siblings 0x00086CDA..
// read it) it only ends the rotation and clears +0x2438. Tracking copies the
// object's x and y (not z) into the target and interpolates the target z
// (rotateCameraTowardObject's trailing float) into +0x138. The file-static
// normAngle takes its argument in EAX and retail keeps ECX live across it,
// so this body lives in normAngle's unit.
//-------------------------------------------------------------------------------------------------
class GlobalData
{
public:
	unsigned char m_padding0000[0x9A4];
	Bool m_disableCameraMovement;		// +0x9A4
};

extern GlobalData *TheWritableGlobalData;

void W3DView::rva0008AAD4(void)
{
	BfmeW3DViewRotateFields *fields = (BfmeW3DViewRotateFields *)this;
	Int curFrame = ++fields->m_curFrame;
	if (TheWritableGlobalData->m_disableCameraMovement) {
		if (curFrame >= fields->m_numFrames + fields->m_numHoldFrames) {
			fields->m_doingRotateCamera = false;
			fields->m_freezeTimeForCameraMovement = false;
		}
		fields->m_rotateFlag = false;
		return;
	}

	Int numFrames;
	if (fields->m_trackObject)
	{
		if (curFrame <= (numFrames = fields->m_numFrames) + fields->m_numHoldFrames)
		{
			const BfmeFollowObject *obj = (const BfmeFollowObject *)TheGameLogic->findObjectByID(fields->m_rcTarget.id);
			if (obj)
			{
				fields->m_rcTarget.pos.x = obj->m_position.x;
				fields->m_rcTarget.pos.y = obj->m_position.y;
			}
			fields->m_trackHeight = ((Real)curFrame) / numFrames * fields->m_rcTarget.pos.z;
			const Vector2 dir(fields->m_rcTarget.pos.x - fields->m_pos.x,
				fields->m_rcTarget.pos.y - fields->m_pos.y);
			const Real dirLength = dir.Length();
			if (dirLength >= 0.1f)
			{
				Real angle = WWMath::Acos(dir.X / dirLength);
				if (dir.Y < 0.0f) {
					angle = -angle;
				}
				angle -= PI/2;
				normAngle(angle);

				Int frame = fields->m_curFrame;
				numFrames = fields->m_numFrames;
				if (frame <= numFrames)
				{
					Real factor = fields->m_ease(((Real)frame) / numFrames);
					Real angleDiff = angle - fields->m_angle;
					normAngle(angleDiff);
					fields->m_angle += angleDiff * factor;
					normAngle(fields->m_angle);
					fields->m_timeMultiplier = fields->m_startTimeMultiplier + fast_float2long_round(floor(
						0.5 + (fields->m_endTimeMultiplier - fields->m_startTimeMultiplier) * factor));
				}
				else
				{
					fields->m_angle = angle;
				}
			}
		}
	}
	else if (curFrame <= (numFrames = fields->m_numFrames))
	{
		Real factor = fields->m_ease(((Real)curFrame) / numFrames);
		fields->m_angle = WWMath::Lerp(fields->m_rcAngle.startAngle, fields->m_rcAngle.endAngle, factor);
		normAngle(fields->m_angle);
		fields->m_timeMultiplier = fields->m_startTimeMultiplier + fast_float2long_round(
			floor(0.5 + (fields->m_endTimeMultiplier - fields->m_startTimeMultiplier) * factor));
	}

	if (fields->m_curFrame >= fields->m_numFrames + fields->m_numHoldFrames) {
		fields->m_doingRotateCamera = false;
		fields->m_freezeTimeForCameraMovement = false;
		if (!fields->m_trackObject)
		{
			fields->m_angle = fields->m_rcAngle.endAngle;
		}
	}
}

// W3DView::cameraModFreezeAngle, retail 0x00086702..0x00086761 (95B, RET):
// the vftable slot between cameraModFinalPitch and cameraModLookToward.
// Zero Hour's body; BFME 2 keeps the waypoint-move state as an int tested
// against 1 (+0x2354) and the waypoint camera angles at +0x16E8.
void W3DView::cameraModFreezeAngle(void)
{
	BfmeW3DViewRotateFields *fields = (BfmeW3DViewRotateFields *)this;
	if (fields->m_doingRotateCamera) {
		if (fields->m_trackObject) {
			fields->m_targetObjectID = (ObjectID)0;	// INVALID_ID
		} else {
			fields->m_rcAngle.startAngle = fields->m_rcAngle.endAngle = fields->m_angle;
		}
	}
	if (fields->m_doingMoveCameraOnWaypointPath == 1) {
		Int i;
		for (i=0; i<fields->m_mcwpNumWaypoints; i++) {
			fields->m_mcwpCameraAngle[i+1] = fields->m_mcwpCameraAngle[0];
		}
	}
}
