// cl: /MD /EHs-c- /DNDEBUG
// Clean BFME1 W3DViewCameraModFinalMoveToBfme at6d9434269164392c5ba62aaa7c15a86b5b020d76
// guides the translation algorithm. Target Ghidra86761/177B/RET4 and
// complete raw byte equality prove guards1DC/2354, signed count22F0,
// three-float prefixes at2AC with20B stride, and iteration2 through count.
// These data offsets agree with the verified owner8990C/89971 at+280.
// Real constructor8B7CF calls owner8990C withECX=this+280. Its primary
// table BC7568 slot39/BC7604 selects this body; no direct E8/E9 callers.
// Original class/method/argument names and complete parent size unknown.
#include "../../../../GameEngine/Include/GameClient/Rva0008990CArrayOwner.h"


void Rva00086761CameraMove::rva00086761(Rva00089894Point *pLoc)
{
	if (m_doingRotateCamera) {
		return;
	}
	if (m_cameraMovementMode == 1) {
		int i;
		Rva00089894Point delta, start;
		start = m_cameraPath.m_arr255[m_cameraPath.m_numValues].m_position;
		delta = *pLoc;
		delta.x -= start.x;
		delta.y -= start.y;
		delta.z -= start.z;
		for (i = 2; i <= m_cameraPath.m_numValues; i++) {
			Rva00089894Point start;
			start.x = m_cameraPath.m_arr255[i].m_position.x;
			start.y = m_cameraPath.m_arr255[i].m_position.y;
			start.z = m_cameraPath.m_arr255[i].m_position.z;
			start.x += delta.x;
			start.y += delta.y;
			start.z += delta.z;
			m_cameraPath.m_arr255[i].m_position = start;
		}
	}
}

// Clean BFME1 Rva0073C420Set at6d943 guides this signed clamp.
// Target8690A21B is between Ghidra86812+248 and8691F; RET4.
// Same primary tableBC7568 slot32/BC75E8 selects this method. The field
// parent2A8 is canonical owner base m_28 at280+28. EAX incidentally holds
// normalized value; original return contract remains unknown.
void Rva00086761CameraMove::rva0008690A(int value)
{
 if (value<=1) value=1;
 m_cameraPath.m_28=value;
}

// Clean BFME1 W3DViewZoomCameraBfme6d943 O1/G7/SSE/MD guides duration,
// frame and interpolation setup. Target132B/RET16, primary slot59/BC7654,
// unchanged-this call to86CDA and matching fields prove the association.
// Runtime period VA DE204C has genuine zero PE storage; writer4C6C6 and
// startup7AC08C configure it. Their code is not recovered by this unit.
// Original method/global names and complete receiver size remain unknown.
int g_Va00DE204C;

void Rva00086761CameraMove::rva00088EB4(float finalValue, int milliseconds, float easeIn, float easeOut)
{
 int &duration = milliseconds;
 register Rva00086761CameraMove *view = this;
 view->m_228 = true;
 if (duration < 1) duration = 1;
 int frames = duration / g_Va00DE204C;
 if (frames < 1) frames = 1;
 view->m_208 = frames;
 view->m_210 = view->m_3C;
 view->m_214 = finalValue;
 view->m_20C = 0;
 view->m_220.rva0030E51F(easeIn, easeOut, (float)duration);
 if (duration == 1) view->rva00086CDA();
}

// Native86812..8690A, 248 bytes, RET4; primary BC7568 slot33.
// BF1 f989 cameraModFinalTimeMultiplier supplies the semantic spine.
// Native independently proves every accessed offset below and default23D4.
// These are data-only views of the five control blocks and waypoint values;
// the receiver remains the canonical array owner. Untouched members remain
// donor-carried or opaque. Double interpolation preserves native x87 shape.
extern "C" __declspec(dllimport) double __cdecl floor(double);


// BaseType.h verbatim: C cast emits out-of-line _ftol plus qword shape;
// retail holds inline fld/fistp so the helper is load-bearing (x87 blocker).
__forceinline long fast_float2long_round(float f)
{
 long i;
 __asm {
  fld [f]
  fistp [i]
 }
 return i;
}
typedef int Int;typedef bool Bool;
// The matched camera one-frame bodies establish this two-Real easing object.
struct BfmeSpeedEase
{
	Real in;
	Real out;
};

// BFME camera-update state at +0x1E0.  The state body at 0x0073C970 proves
// the frame/start/end/ease/active offsets; this method additionally proves the
// final time-multiplier word at +0x1F8.
struct BfmeSpeedCameraUpdate
{
	Int numFrames;                 // +0x00
	Int curFrame;                  // +0x04
	Int unmodelled08;              // +0x08
	Real start;                    // +0x0C
	Real end;                      // +0x10
	Int unmodelled14;              // +0x14
	Int endTimeMultiplier;         // +0x18
	BfmeSpeedEase ease;            // +0x1C
	Bool active;                   // +0x24
};

// BFME zoom state at +0x208.  0x0073C7C0 proves the block and active flag;
// this method proves the intervening final-time word at +0x21C.
struct BfmeSpeedZoom
{
	Int numFrames;                 // +0x00
	Int curFrame;                  // +0x04
	Real startZoom;                // +0x08
	Real endZoom;                  // +0x0C
	Int unmodelled10;              // +0x10
	Int endTimeMultiplier;         // +0x14
	BfmeSpeedEase ease;            // +0x18
	Bool active;                   // +0x20
};

// BFME pitch state at +0x22C.  0x0073FCF0 and 0x0073C890 prove the frame,
// pitch and easing offsets; this method proves its final-time word at +0x248.
struct BfmeSpeedPitch
{
	Int numFrames;                 // +0x00
	Int curFrame;                  // +0x04
	Real angle;                    // +0x08
	Real finalPitch;               // +0x0C
	Real startPitch;               // +0x10
	Real endPitch;                 // +0x14
	Int unmodelled18;              // +0x18
	Int endTimeMultiplier;         // +0x1C
	BfmeSpeedEase ease;            // +0x20
	Bool active;                   // +0x28
};

// BFME alternate camera-update state at +0x258.  0x0073CA40 proves the
// frame/start/end/ease/active offsets; this method proves +0x270.
struct BfmeSpeedAlternate
{
	Int numFrames;                 // +0x00
	Int curFrame;                  // +0x04
	Int unmodelled08;              // +0x08
	Real start;                    // +0x0C
	Real end;                      // +0x10
	Int unmodelled14;              // +0x14
	Int endTimeMultiplier;         // +0x18
	BfmeSpeedEase ease;            // +0x1C
	Bool active;                   // +0x24
};

// The already-matched rotate setter establishes this complete state at
// +0x1AC, including endTimeMultiplier at +0x1B8 and active at +0x1DC.
struct BfmeSpeedRotate
{
	Int numFrames;
	Int curFrame;
	Int startTimeMultiplier;
	Int endTimeMultiplier;
	Int numHoldFrames;
	BfmeSpeedEase ease;
	Bool trackObject;
	unsigned char unmodelled1D[3];
	Real startAngle;
	Real endAngle;
};


struct BfmeCameraSpeedFields {

	char padding0004[0x1AC];
	BfmeSpeedRotate rotateCamera; // +0x1AC, active at +0x1DC
	char padding1D4[0x1DC - 0x1D4];
	Bool doingRotateCamera;         // +0x1DC
	char padding1DD[0x1E0 - 0x1DD];
	BfmeSpeedCameraUpdate cameraUpdate; // +0x1E0, active at +0x204
	BfmeSpeedZoom zoomCamera;     // +0x208, active at +0x228
	BfmeSpeedPitch pitchCamera;   // +0x22C, active at +0x254
	BfmeSpeedAlternate alternateCamera; // +0x258, active at +0x27C
	// The four state blocks end at the compiler's +0x280 boundary.  The
	// matched retail path array begins at +0x1AE4; this explicit real gap
	// keeps that member at its proven offset rather than relying on an empty
	// overlay.
	char padding280[0x1AE4 - 0x280];
	Real waySegmentLength[0x101];   // +0x1AE4
	Real totalDistance;             // +0x1EE8
	char unmodelled1EEC[8];
	Int timeMultiplier[0xFF];        // +0x1EF4, indexed from [i+1]
	Int numWaypoints;                // +0x22F0
	char padding22F4[0x2354 - 0x22F4];
	Int cameraMovementMode;          // +0x2354; mode 1 is waypoint movement
	char padding2358[0x23D4 - 0x2358];
	Int timeMultiplierDefault;       // +0x23D4

};
void Rva00086761CameraMove::rva00086812(Int finalMultiplier)
{
 BfmeCameraSpeedFields *state=(BfmeCameraSpeedFields*)this;
	if (state->zoomCamera.active)
		state->zoomCamera.endTimeMultiplier = finalMultiplier;
	if (state->pitchCamera.active)
		state->pitchCamera.endTimeMultiplier = finalMultiplier;
	if (state->cameraUpdate.active)
		state->cameraUpdate.endTimeMultiplier = finalMultiplier;
	if (state->alternateCamera.active)
		state->alternateCamera.endTimeMultiplier = finalMultiplier;
	if (state->doingRotateCamera)
		state->rotateCamera.endTimeMultiplier = finalMultiplier;
	if (state->cameraMovementMode == 1)
	{
		Int i;
		Real curDistance = 0;
		for (i = 0; i < state->numWaypoints; i++)
		{
			curDistance += state->waySegmentLength[i];
			Real factor2 = curDistance / state->totalDistance;
			double factor1 = 1.0 - factor2;
			state->timeMultiplier[i + 1] = fast_float2long_round((float)floor(
				0.5 + state->timeMultiplier[i + 1] * factor1 + (double)(float)finalMultiplier * factor2));
		}
	}
	else
	{
		state->timeMultiplierDefault = finalMultiplier;
	}
}

#undef REAL_TO_INT_FLOOR

// BF1 f989 W3DViewPitchCameraBfme supplies the pitch/easing guide.
// Target88F38..88FF6 RET16 proves time2C/30 fields34/38/3C/40
// ease24C and active254; rowed updater86D73 accesses the same state.
// Native88F38 uses virtual slots134/135 for the pitch conversions;
// these neutral positions specify the observed ABI without asserting names.
#define BFME_PITCH_RESERVED(n) virtual void reserved##n() = 0;
class BfmePitchDispatch {public:
BFME_PITCH_RESERVED(0) BFME_PITCH_RESERVED(1) BFME_PITCH_RESERVED(2) BFME_PITCH_RESERVED(3) BFME_PITCH_RESERVED(4) BFME_PITCH_RESERVED(5)
BFME_PITCH_RESERVED(6) BFME_PITCH_RESERVED(7) BFME_PITCH_RESERVED(8) BFME_PITCH_RESERVED(9) BFME_PITCH_RESERVED(10) BFME_PITCH_RESERVED(11)
BFME_PITCH_RESERVED(12) BFME_PITCH_RESERVED(13) BFME_PITCH_RESERVED(14) BFME_PITCH_RESERVED(15) BFME_PITCH_RESERVED(16) BFME_PITCH_RESERVED(17)
BFME_PITCH_RESERVED(18) BFME_PITCH_RESERVED(19) BFME_PITCH_RESERVED(20) BFME_PITCH_RESERVED(21) BFME_PITCH_RESERVED(22) BFME_PITCH_RESERVED(23)
BFME_PITCH_RESERVED(24) BFME_PITCH_RESERVED(25) BFME_PITCH_RESERVED(26) BFME_PITCH_RESERVED(27) BFME_PITCH_RESERVED(28) BFME_PITCH_RESERVED(29)
BFME_PITCH_RESERVED(30) BFME_PITCH_RESERVED(31) BFME_PITCH_RESERVED(32) BFME_PITCH_RESERVED(33) BFME_PITCH_RESERVED(34) BFME_PITCH_RESERVED(35)
BFME_PITCH_RESERVED(36) BFME_PITCH_RESERVED(37) BFME_PITCH_RESERVED(38) BFME_PITCH_RESERVED(39) BFME_PITCH_RESERVED(40) BFME_PITCH_RESERVED(41)
BFME_PITCH_RESERVED(42) BFME_PITCH_RESERVED(43) BFME_PITCH_RESERVED(44) BFME_PITCH_RESERVED(45) BFME_PITCH_RESERVED(46) BFME_PITCH_RESERVED(47)
BFME_PITCH_RESERVED(48) BFME_PITCH_RESERVED(49) BFME_PITCH_RESERVED(50) BFME_PITCH_RESERVED(51) BFME_PITCH_RESERVED(52) BFME_PITCH_RESERVED(53)
BFME_PITCH_RESERVED(54) BFME_PITCH_RESERVED(55) BFME_PITCH_RESERVED(56) BFME_PITCH_RESERVED(57) BFME_PITCH_RESERVED(58) BFME_PITCH_RESERVED(59)
BFME_PITCH_RESERVED(60) BFME_PITCH_RESERVED(61) BFME_PITCH_RESERVED(62) BFME_PITCH_RESERVED(63) BFME_PITCH_RESERVED(64) BFME_PITCH_RESERVED(65)
BFME_PITCH_RESERVED(66) BFME_PITCH_RESERVED(67) BFME_PITCH_RESERVED(68) BFME_PITCH_RESERVED(69) BFME_PITCH_RESERVED(70) BFME_PITCH_RESERVED(71)
BFME_PITCH_RESERVED(72) BFME_PITCH_RESERVED(73) BFME_PITCH_RESERVED(74) BFME_PITCH_RESERVED(75) BFME_PITCH_RESERVED(76) BFME_PITCH_RESERVED(77)
BFME_PITCH_RESERVED(78) BFME_PITCH_RESERVED(79) BFME_PITCH_RESERVED(80) BFME_PITCH_RESERVED(81) BFME_PITCH_RESERVED(82) BFME_PITCH_RESERVED(83)
BFME_PITCH_RESERVED(84) BFME_PITCH_RESERVED(85) BFME_PITCH_RESERVED(86) BFME_PITCH_RESERVED(87) BFME_PITCH_RESERVED(88) BFME_PITCH_RESERVED(89)
BFME_PITCH_RESERVED(90) BFME_PITCH_RESERVED(91) BFME_PITCH_RESERVED(92) BFME_PITCH_RESERVED(93) BFME_PITCH_RESERVED(94) BFME_PITCH_RESERVED(95)
BFME_PITCH_RESERVED(96) BFME_PITCH_RESERVED(97) BFME_PITCH_RESERVED(98) BFME_PITCH_RESERVED(99) BFME_PITCH_RESERVED(100) BFME_PITCH_RESERVED(101)
BFME_PITCH_RESERVED(102) BFME_PITCH_RESERVED(103) BFME_PITCH_RESERVED(104) BFME_PITCH_RESERVED(105) BFME_PITCH_RESERVED(106) BFME_PITCH_RESERVED(107)
BFME_PITCH_RESERVED(108) BFME_PITCH_RESERVED(109) BFME_PITCH_RESERVED(110) BFME_PITCH_RESERVED(111) BFME_PITCH_RESERVED(112) BFME_PITCH_RESERVED(113)
BFME_PITCH_RESERVED(114) BFME_PITCH_RESERVED(115) BFME_PITCH_RESERVED(116) BFME_PITCH_RESERVED(117) BFME_PITCH_RESERVED(118) BFME_PITCH_RESERVED(119)
BFME_PITCH_RESERVED(120) BFME_PITCH_RESERVED(121) BFME_PITCH_RESERVED(122) BFME_PITCH_RESERVED(123) BFME_PITCH_RESERVED(124) BFME_PITCH_RESERVED(125)
BFME_PITCH_RESERVED(126) BFME_PITCH_RESERVED(127) BFME_PITCH_RESERVED(128) BFME_PITCH_RESERVED(129) BFME_PITCH_RESERVED(130) BFME_PITCH_RESERVED(131)
BFME_PITCH_RESERVED(132) BFME_PITCH_RESERVED(133)
virtual float pitchStart(float)=0; virtual float pitchEnd(float)=0;
};
#undef BFME_PITCH_RESERVED
class Rva00086D73 { public: void rva00086D73(); };
void Rva00086761CameraMove::rva00088F38(float finalPitch,int milliseconds,float easeIn,float easeOut) {
 BfmeCameraSpeedFields*view=(BfmeCameraSpeedFields*)this;
 int&duration=milliseconds;
 view->pitchCamera.active=true;
 if(duration<1)duration=1;
 int frames=duration/g_Va00DE204C;
 if(frames<1)frames=1;
 view->pitchCamera.numFrames=frames;
 view->pitchCamera.curFrame=0;
 float currentPitch=*(float*)((char*)this+0x6c);
 view->pitchCamera.startPitch=currentPitch*57.295776f;
 view->pitchCamera.endPitch=((BfmePitchDispatch*)this)->pitchEnd(finalPitch);
 view->pitchCamera.angle=((BfmePitchDispatch*)this)->pitchStart(*(float*)((char*)this+0x6c));
 view->pitchCamera.finalPitch=finalPitch;
 ((ParabolicEase*)&view->pitchCamera.ease)->rva0030E51F(easeIn,easeOut,(float)duration);
 if(duration==1)((Rva00086D73*)this)->rva00086D73();
}
