// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// stlport
//
// CameraAnimationTrack<T>::getFrameData for the LookAt camera channel,
// retail 0x00541955 (281 bytes, ret 8). WorldBuilder's debug twin 0x00454320
// is CameraAnimationTrack<class LookAtCameraAnimationCameraFrameData>::
// getFrameData (CameraAnimationTrack.h, asserts at lines 124..139); the frame
// data keeps the address name of the rowed interpolator's result
// Rva00540D94 (0x00540DCA). A negative frame returns the first key; else the
// pinned locator 0x00541579 moves the last used key to the floored frame,
// the last key (or a key whose successor shares its frame) is returned as
// is, and otherwise the four surrounding keys (clamped at both ends) are
// interpolated at the fraction between the key and its successor.
//
// The frame data's out-of-line copy constructor is ICF-folded with the rowed
// Region3D copy constructor 0x0009AC04 (six dword copies, ret 4).
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include <vector>

struct Rva00540E9DSrc
{
	int a, b, c;
};
class Rva00540D94
{
public:
	__declspec(noinline) Rva00540D94(const Rva00540D94 &other);
	int mode;
	Rva00540E9DSrc position;
	float scalar10, scalar14;
};

Rva00540D94::Rva00540D94(const Rva00540D94 &other)
{
	mode = other.mode;
	position.a = other.position.a;
	position.b = other.position.b;
	position.c = other.position.c;
	scalar10 = other.scalar10;
	scalar14 = other.scalar14;
}

Rva00540D94 Rva00540DCAGet(float t, Rva00540D94 *a, int ta, Rva00540D94 *b, int tb, Rva00540D94 *c, int tc, Rva00540D94 *d, int td);

// The look-at channel's 16-byte frame data, whose out-of-line copy
// constructor is ICF-folded with the rowed Region2D copy constructor
// 0x0004254E (four dword copies, ret 4).
class Rva00540E9D
{
public:
	__declspec(noinline) Rva00540E9D(const Rva00540E9D &other);
	int m_00;
	Rva00540E9DSrc m_04;
};

Rva00540E9D::Rva00540E9D(const Rva00540E9D &other)
{
	m_00 = other.m_00;
	m_04.a = other.m_04.a;
	m_04.b = other.m_04.b;
	m_04.c = other.m_04.c;
}

class Rva005C71ADView;
Rva00540E9D rva00540EBD(float value, void *arg10, void *arg14, Rva005C71ADView *view,
	void *arg1C, void *arg20, void *arg24, void *arg28, void *arg2C);

// The banked sorted-key locators, pinned under their address names.
class Rva00541579
{
public:
	bool rva00541579(int frame);
};
class Rva005418CB
{
public:
	bool rva00541641(int frame);
};

// The free camera's 0x24-byte frame (rowed copy constructor 0x0053FF5F),
// its pinned locator 0x0054034A and the rowed evaluator 0x0053FE64, which
// fills the frame through its first stack word (pinned here under a
// by-value spelling).
class Rva0053FDE6
{
public:
	Rva0053FDE6(const Rva0053FDE6 &other);
	int m_00;
	char m_04[0x20];
};
class Rva0054034A
{
public:
	bool rva0054034A(int frame);
};
Rva0053FDE6 Rva0053FE64Get(float t, Rva0053FDE6 *a, int ta, Rva0053FDE6 *b, int tb,
	Rva0053FDE6 *c, int tc, Rva0053FDE6 *d, int td);

// Per-channel locator and interpolator.
static inline void cameraTrackSeek(void *track, int frame, const Rva0053FDE6 *)
{
	((Rva0054034A *)track)->rva0054034A(frame);
}
static inline Rva0053FDE6 cameraTrackInterpolate(float t, Rva0053FDE6 *a, int ta, Rva0053FDE6 *b, int tb,
	Rva0053FDE6 *c, int tc, Rva0053FDE6 *d, int td)
{
	return Rva0053FE64Get(t, a, ta, b, tb, c, tc, d, td);
}
static inline void cameraTrackSeek(void *track, int frame, const Rva00540D94 *)
{
	((Rva00541579 *)track)->rva00541579(frame);
}
static inline void cameraTrackSeek(void *track, int frame, const Rva00540E9D *)
{
	((Rva005418CB *)track)->rva00541641(frame);
}
static inline Rva00540D94 cameraTrackInterpolate(float fraction, Rva00540D94 *prevKey, int ta, Rva00540D94 *startKey, int tb,
	Rva00540D94 *endKey, int tc, Rva00540D94 *nextKey, int td)
{
	return Rva00540DCAGet(fraction, prevKey, ta, startKey, tb, endKey, tc, nextKey, td);
}
static inline Rva00540E9D cameraTrackInterpolate(float fraction, Rva00540E9D *prevKey, int ta, Rva00540E9D *startKey, int tb,
	Rva00540E9D *endKey, int tc, Rva00540E9D *nextKey, int td)
{
	return rva00540EBD(fraction, prevKey, (void *)ta, (Rva005C71ADView *)startKey, (void *)tb, endKey, (void *)tc, nextKey, (void *)td);
}

template <class T>
struct CameraAnimationKeyFrame
{
	int m_frame;
	T m_data;
};

template <class T>
class CameraAnimationTrack
{
public:
	T getFrameData(float frameNum);
private:
	typedef CameraAnimationKeyFrame<T> KeyFrame;
	char m_pad00[0x10];
	_STL::vector<KeyFrame> m_keyFrames;	// +0x10
	int m_lastUsedKeyFrame;		// +0x1C
};

template <class T>
T CameraAnimationTrack<T>::getFrameData(float frameNum)
{
	if (frameNum < 0.0f)
		return m_keyFrames[0].m_data;
	cameraTrackSeek(this, (int)floor(frameNum), (const T *)0);
	if ((unsigned int)m_lastUsedKeyFrame >= m_keyFrames.size() - 1)
		return m_keyFrames[m_lastUsedKeyFrame].m_data;
	const KeyFrame &k0 = m_keyFrames[m_lastUsedKeyFrame];
	const KeyFrame &k1 = m_keyFrames[m_lastUsedKeyFrame + 1];
	if (k0.m_frame == k1.m_frame)
		return k0.m_data;
	frameNum = (frameNum - k0.m_frame) / (k1.m_frame - k0.m_frame);
	const KeyFrame &kPrev = m_lastUsedKeyFrame > 0 ? m_keyFrames[m_lastUsedKeyFrame - 1] : k0;
	const KeyFrame &kNext = m_lastUsedKeyFrame + 2 < m_keyFrames.size() ? m_keyFrames[m_lastUsedKeyFrame + 2] : k1;
	return cameraTrackInterpolate(frameNum, (T *)&kPrev.m_data, kPrev.m_frame, (T *)&k0.m_data, k0.m_frame,
		(T *)&k1.m_data, k1.m_frame, (T *)&kNext.m_data, kNext.m_frame);
}

template Rva00540D94 CameraAnimationTrack<Rva00540D94>::getFrameData(float frameNum);
template Rva00540E9D CameraAnimationTrack<Rva00540E9D>::getFrameData(float frameNum);
template Rva0053FDE6 CameraAnimationTrack<Rva0053FDE6>::getFrameData(float frameNum);

// ?rva00541F72@LookAtCameraAnimation@@QAEXABMPAURva00540888Transform@@@Z retail
// 0x00541F72 (90 bytes, ret 8): the look-at camera animation's transform
// slot (table 0x00C69510, beside the free-camera sibling 0x00540888 of the
// same signature). It samples the camera track (+0x24) and the target track
// (+0x44) at the time, aims the output matrix from the camera position at
// the target with the camera frame's roll (rowed Matrix3D::Look_At) and
// copies its field of view. Owner and output names are address-derived.
class Vector3;
class Matrix3D
{
public:
	void Look_At(const Vector3 &p, const Vector3 &t, float roll);
	float m_rows[12];
};
struct Rva00540888Transform
{
	Matrix3D m_transform;	// +0x00
	float m_fov;	// +0x30
};
class LookAtCameraAnimation
{
public:
	void rva00541F72(const float &time, Rva00540888Transform *out);
private:
	char m_pad00[0x24];
	CameraAnimationTrack<Rva00540D94> m_cameraTrack;	// +0x24
	CameraAnimationTrack<Rva00540E9D> m_targetTrack;	// +0x44
};

void LookAtCameraAnimation::rva00541F72(const float &time, Rva00540888Transform *out)
{
	Rva00540D94 camera = m_cameraTrack.getFrameData(time);
	Rva00540E9D target = m_targetTrack.getFrameData(time);
	out->m_transform.Look_At((const Vector3 &)camera.position, (const Vector3 &)target.m_04, camera.scalar10);
	out->m_fov = camera.scalar14;
}
