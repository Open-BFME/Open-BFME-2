// cl: /DNDEBUG /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?Class_ID@CameraClass@@UBEHXZ, retail 0x0007C3F8, 4 bytes.
// BFME1/ZH camera.h: `virtual int Class_ID(void) const { return CLASSID_CAMERA; }`
// (CLASSID_CAMERA = 8). Evidence: slot 3 of ??_7CameraClass (0x00BD26E0) points here;
// slot 3 is RenderObjClass::Class_ID (its own slot holds the CLASSID_UNKNOWN body), and
// the sibling tables' slot 3 bodies return their donor ids (Line3D 6, ParticleEmitter
// 15, Null3D 22, HLod 25, AABox 26, OBBox 27, SegLine 28). Size-optimised PUSH 8 / POP EAX.

#include "CameraClass.h"

int CameraClass::Class_ID(void) const
{
	return CLASSID_CAMERA;
}
