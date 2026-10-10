// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ?rva00540888@Rva00540845@@QAEXABMPAURva00540888Transform@@@Z, retail
// 0x00540888 (259 bytes, thiscall, ret 8).  Samples the camera track at
// +0x24 of the free-camera animation (vtable 0x00C694F8, copy ctor
// 0x00540845) at the given time through 0x00540559 (WorldBuilder's
// CameraAnimationTrack<FreeCameraAnimationFrameData>::getFrameData, returning
// the 0x24-byte Rva0053FDE6 frame: position +0x04, orientation quaternion
// +0x10 (identity w = 1.0 at +0x1C, rowed ctor 0x0053FDE6), field of view
// +0x20) and writes the WWMath Build_Matrix3D rotation (its double 1.0 and
// 2.0 constants and the reversed zero-translation chain are retail's), the
// position as translation and the field of view.  Owner and output names
// are address-derived.
#include "matrix3d.h"
#include "quat.h"

class Rva0053FDE6
{
public:
	Rva0053FDE6(const Rva0053FDE6 &other);
	int m_00;
	Vector3 m_position;	// +0x04
	Quaternion m_orientation;	// +0x10
	float m_fov;	// +0x20
};

struct Rva00540888Transform
{
	Matrix3D m_transform;	// +0x00
	float m_fov;	// +0x30
};

class Rva0054034A
{
public:
	Rva0053FDE6 rva00540559(float time);
};

class Rva00540845
{
public:
	void rva00540888(const float &time, Rva00540888Transform *out);
private:
	char m_pad00[0x24];
	Rva0054034A m_track;	// +0x24
};

void Rva00540845::rva00540888(const float &time, Rva00540888Transform *out)
{
	Rva0053FDE6 frame = m_track.rva00540559(time);
	const Quaternion &q = frame.m_orientation;
	Matrix3D &m = out->m_transform;
	Build_Matrix3D(q, m);
	m.Set_Translation(frame.m_position);
	out->m_fov = frame.m_fov;
}
