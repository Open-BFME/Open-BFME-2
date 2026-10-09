// ?updateCameraMovements@W3DView@@QAE_NXZ
// partial score=1.0 date=2026-10-09
// Reference: Open-BFME-1 revision874e38488c7dcf8cf3343452e8e5371bb3a0e64c,
// W3DViewUpdateCameraMovementsBfme.cpp supplies modes1/2 and flag dispatch.
// Target WB98A520 and native8B010..8B1E5 prove mode3 timestamp gating,
// mode4 owned-motion update/delete, client vslot7C, and target offsets.
// Global disable9C1 and frame40/last24C4; path flag23C8 and lookAt23F4.
// The 8AAD4 callee retains an address-qualified name; the spline helper's
// name is independently carried by the WB998EC0 call mapping. Provider RVAs
// below are caller REL32s to proven in-image boundaries; no alias owners.
// cl: /O1 /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
// readable body of ?updateCameraMovements@W3DView@@: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
// BFME2 W3DView::updateCameraMovements, retail0x0008B010.

typedef int Int;
typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_padding[0x9C1];
	Bool m_disableCameraMovement;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_padding[0x40];
	Int m_frame;
};

extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
extern Int TheW3DFrameLengthInMsec;

#include "Coord3D.h"
#include "Coord2D.h"
class Rva00086761CameraMove {public:void rva00086CDA();};
class Rva00086D73 {public:void rva00086D73();};
class Rva00086E24 {public:void rva00086E24();};
class Rva00086EBD {public:void rva00086EBD();};
class Rva00086C4A {public:void rva00086C4A();};
class GameClient {public:
virtual void slot000();
virtual void slot004();
virtual void slot008();
virtual void slot00C();
virtual void slot010();
virtual void slot014();
virtual void slot018();
virtual void slot01C();
virtual void slot020();
virtual void slot024();
virtual void slot028();
virtual void slot02C();
virtual void slot030();
virtual void slot034();
virtual void slot038();
virtual void slot03C();
virtual void slot040();
virtual void slot044();
virtual void slot048();
virtual void slot04C();
virtual void slot050();
virtual void slot054();
virtual void slot058();
virtual void slot05C();
virtual void slot060();
virtual void slot064();
virtual void slot068();
virtual void slot06C();
virtual void slot070();
virtual void slot074();
virtual void slot078();
virtual unsigned getTimestamp();};
extern GameClient *TheGameClient;
extern int g_009BA4E8;
class CameraMotion {public:virtual ~CameraMotion();virtual void update(float);char pad[0x18];bool active;};
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
public:
	Bool updateCameraMovements(void);

private:


	// Two more one-frame easers with no upstream twin; each is guarded by the
	// flag named after it and blends one Real field, +0x70 and +0x30.


	void rva0008AAD4(void);

	void moveAlongWaypointPath(Int milliseconds);
	void moveCameraOrLocatorAlongSplinePath(Int milliseconds, Bool alternate);

	char m_padding000[0x0C];
	Coord3D m_pos;
	char m_padding018[0x1DC - 0x18];
	Bool m_doingRotateCamera;
	char m_padding1DD[0x204 - 0x1DD];
	Bool m_doingCameraUpdate;
	char m_padding205[0x228 - 0x205];
	Bool m_doingZoomCamera;
	char m_padding229[0x254 - 0x229];
	Bool m_doingPitchCamera;
	char m_padding255[0x27C - 0x255];
	Bool m_doingCameraUpdateAlternate;
	Bool m_cameraMovementFinished;
	char m_padding27E[0x2354 - 0x27E];
	Int m_cameraMovementMode;
 unsigned lastTimestamp; CameraMotion *motion; unsigned motionTimestamp;
	char m_padding2364[0x23C8 - 0x2364];
	Bool m_doingMoveCameraOnWaypointPath;
	char m_padding23B9[0x23F4 - 0x23C9];
	Coord2D m_previousLookAtPosition;
	char m_padding23EC[0x24C4 - 0x23FC];
	Int m_cameraMovementLastFrame;
};

// ?updateCameraMovements@W3DView@@QAE_NXZ
Bool W3DView::updateCameraMovements(void)
{
	register Bool didUpdate = false;

	if (TheWritableGlobalData->m_disableCameraMovement) {
		Int frame = TheGameLogic->m_frame;
		if (m_cameraMovementLastFrame < frame) {
			m_cameraMovementLastFrame = frame;
		}
	}

	if (m_doingZoomCamera) {
		reinterpret_cast<Rva00086761CameraMove*>(this)->rva00086CDA();
		didUpdate = true;
	}
	if (m_doingPitchCamera) {
		reinterpret_cast<Rva00086D73*>(this)->rva00086D73();
		didUpdate = true;
	}
	if (m_doingCameraUpdate) {
		reinterpret_cast<Rva00086E24*>(this)->rva00086E24();
		didUpdate = true;
	}
	if (m_doingCameraUpdateAlternate) {
		reinterpret_cast<Rva00086EBD*>(this)->rva00086EBD();
		didUpdate = true;
	}
	if (m_doingRotateCamera) {
		m_previousLookAtPosition = *(const Coord2D *)&m_pos;
		rva0008AAD4();
		didUpdate = true;
	}
	if (m_doingMoveCameraOnWaypointPath) {
		moveCameraOrLocatorAlongSplinePath(TheW3DFrameLengthInMsec, true);
		didUpdate = true;
	}

	switch (m_cameraMovementMode) {
    case 4:
        if(motion){
            unsigned timestamp=TheGameClient->getTimestamp();
            motion->update((timestamp-motionTimestamp)*(30.0f/g_009BA4E8));
            motionTimestamp=timestamp;
            if(!motion->active){::delete motion;motion=0;m_cameraMovementMode=0;goto camera_movement_finished;}
            goto camera_movement_updated;
        }
        break;
	case 1:
		m_previousLookAtPosition = *(const Coord2D *)&m_pos;
		moveAlongWaypointPath(TheW3DFrameLengthInMsec);
		goto camera_movement_updated;
	case 2:
		m_previousLookAtPosition = *(const Coord2D *)&m_pos;
		moveCameraOrLocatorAlongSplinePath(TheW3DFrameLengthInMsec, false);
		goto camera_movement_updated;
	case 3:
        {unsigned timestamp=TheGameClient->getTimestamp();
         if(timestamp!=lastTimestamp){reinterpret_cast<Rva00086C4A*>(this)->rva00086C4A();lastTimestamp=timestamp;}}
		goto camera_movement_updated;
	}
	goto camera_movement_finished;

camera_movement_updated:
	didUpdate = true;

camera_movement_finished:

	if (m_cameraMovementFinished) {
		didUpdate = true;
	}
	return didUpdate;
}
