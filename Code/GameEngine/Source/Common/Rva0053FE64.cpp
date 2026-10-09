// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0053FE64@Rva0053FE64@@SAPAXPAXM0H0H0H0H@Z retail 0x0053FE64..
// 0x0053FF1D (185B) cdecl.
//
// Camera animation channel evaluator: builds the interpolated frame from four
// (frame time) keys. The first stack word is the hidden by-value return slot
// (retail returns it in eax; caller 0x00540660 pushes it last and pops 0x28).
// Each channel is interpolated through the second key's own type at +0
// (thiscall on the second key): the float at +0x20 through
// CameraAnimationFrameData::doInterpolate 0x005C70DB; the quaternion at +0x10
// through 0x005C7098 and the Vector3 at +0x04 through 0x005C71AD (both return
// by value through a hidden slot); the frame is then built through
// 0x0053FE2A (position quaternion value key) with the second key's type.
// Arguments of the final call are evaluated right to left: the key word is
// pushed first then float then quaternion then vector channel.
// WorldBuilder twin 0xA9C950 (unnamed) has the same call sequence.
// The two earlier blocked attempts modelled the hidden slot but spelled a
// void return; retail reloads eax from it so the return is the slot pointer.

struct S12;
struct S16;
class Quaternion;

class Rva0053FE2A
{
public:
	Rva0053FE2A &rva0053FE2A(S12 *a1, S16 *a2, float f, int d);
};

class CameraAnimationFrameData
{
public:
	float doInterpolate(float t, float *pa, int ta, float *pc, int tc, float *pf, int tf, float *pd, int td);
};

class Rva005C7098
{
public:
	Quaternion *rva005C7098(Quaternion *dst, float t, int a3, int a4, const Quaternion *src1, int a6, const Quaternion *src2, int a8, int a9, int a10);
};

class Rva005C71ADView
{
public:
	void *rva005C71AD(void *result, float t, void *pa, void *ta, void *pc, void *tc, void *pf, void *tf, void *pd, void *td);
};

// One key's frame data: interpolation type, position, orientation, value.
struct Rva0053FE64Frame
{
	int m_type;			// +0x00
	float m_position[3];		// +0x04
	float m_orientation[4];		// +0x10
	float m_value;			// +0x20
};

struct Rva0053FE64Vec
{
	float v[3];
};

struct Rva0053FE64Quat
{
	float q[4];
};

class Rva0053FE64
{
public:
	static void *rva0053FE64(void *result, float t, void *key0, int t0, void *key1, int t1, void *key2, int t2, void *key3, int t3);
};

void *Rva0053FE64::rva0053FE64(void *result, float t, void *key0, int t0, void *key1, int t1, void *key2, int t2, void *key3, int t3)
{
	Rva0053FE64Frame *p0 = (Rva0053FE64Frame *)key0;
	Rva0053FE64Frame *p1 = (Rva0053FE64Frame *)key1;
	Rva0053FE64Frame *p2 = (Rva0053FE64Frame *)key2;
	Rva0053FE64Frame *p3 = (Rva0053FE64Frame *)key3;
	Rva0053FE64Quat orientation;
	Rva0053FE64Vec position;
	((Rva0053FE2A *)result)->rva0053FE2A(
		(S12 *)((Rva005C71ADView *)p1)->rva005C71AD(&position, t,
			p0->m_position, (void *)t0, p1->m_position, (void *)t1,
			p2->m_position, (void *)t2, p3->m_position, (void *)t3),
		(S16 *)((Rva005C7098 *)p1)->rva005C7098((Quaternion *)&orientation, t,
			(int)p0->m_orientation, t0, (const Quaternion *)p1->m_orientation, t1,
			(const Quaternion *)p2->m_orientation, t2, (int)p3->m_orientation, t3),
		((CameraAnimationFrameData *)p1)->doInterpolate(t, &p0->m_value, t0,
			&p1->m_value, t1, &p2->m_value, t2, &p3->m_value, t3),
		p1->m_type);
	return result;
}
