// cl: /O1 /arch:SSE /MD /EHsc /DNDEBUG
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

typedef float Real;
typedef int Int;
typedef bool Bool;
enum ObjectID { INVALID_ID = 0 };

#define PI 3.14159265359f

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
};

// BFME's W3DView rotate state as both bodies address it: m_rcInfo at +0x1AC
// (numFrames, curFrame, the time-multiplier pair, numHoldFrames, the ease,
// trackObject, the angle pair or target id, a trailing float),
// m_doingRotateCamera at +0x1DC, the time multiplier at +0x23D4 and the flag
// rotateCamera stores at +0x2438.
struct BfmeW3DViewRotateFields
{
	unsigned char m_padding0000[0x28];
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
