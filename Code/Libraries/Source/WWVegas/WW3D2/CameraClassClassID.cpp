// cl: /DNDEBUG /MD
//
// ?Class_ID@CameraClass@@UBEHXZ, retail 0x0007C3F8, 4 bytes.
// BFME1/ZH camera.h: `virtual int Class_ID(void) const { return CLASSID_CAMERA; }`
// (CLASSID_CAMERA = 8). Evidence: slot 3 of ??_7CameraClass (0x00BD26E0) points here;
// slot 3 is RenderObjClass::Class_ID (its own slot holds the CLASSID_UNKNOWN body), and
// the sibling tables' slot 3 bodies return their donor ids (Line3D 6, ParticleEmitter
// 15, Null3D 22, HLod 25, AABox 26, OBBox 27, SegLine 28). Size-optimised PUSH 8 / POP EAX.

class CameraClass
{
public:
	enum { CLASSID_CAMERA = 8 };
	virtual int Class_ID(void) const;
};

int CameraClass::Class_ID(void) const
{
	return CLASSID_CAMERA;
}
