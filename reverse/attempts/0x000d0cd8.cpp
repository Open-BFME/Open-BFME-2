// ??0W3DBoatWakeModelDrawModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-23
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0W3DBoatWakeModelDrawModuleData@@QAE@XZ, retail 0x000D0CD8, 31 bytes.
// Root ModuleData ctor (no base call): installs vtable 0x00BCDE68
// explicitly, clears the +8 word (and-RMW, barrier-pinned below the vtable
// install per the BuffDraw precedent) and zeroes three floats at
// +0x0C/+0x10/+0x14 via an xmm0-homed fzero local (/arch:SSE emits retail
// xorps+movss). Class size 0x18 proven by the W3DBoatWakeModelDraw data
// factory (news 0x18, sole caller at 0x65080). Row supersedes the ctor pin.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class W3DBoatWakeModelDrawModuleData
{
public:
	W3DBoatWakeModelDrawModuleData();

private:
	// +0x00 vtable (installed explicitly below; no base, no virtuals here).
	const void *m_vtable;
	// +0x04 opaque pad (untouched by this ctor).
	unsigned int m_pad04;
	// +0x08 cleared word.
	unsigned int m_08;
	// +0x0C/+0x10/+0x14 float zeros.
	float m_0C;
	float m_10;
	float m_14;
};

// ??0W3DBoatWakeModelDrawModuleData@@QAE@XZ @0x000D0CD8
W3DBoatWakeModelDrawModuleData::W3DBoatWakeModelDrawModuleData()
{
	float fzero = 0.0f;
	*(unsigned int *)this = 0x00BCDE68;
	_ReadWriteBarrier();
	m_08 &= 0;
	m_0C = fzero;
	m_10 = fzero;
	m_14 = fzero;
}
