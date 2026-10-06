// cl: /MD
// ??0Rva004ECDC8@@QAE@I@Z @ 0x004ECDA7, 33 bytes.
// Ctor for the 0x14-byte Xfer element (uint at +0, Coord3DBase at +4, int at
// +0x10) proven same class as ?rva004ECDC8@Rva004ECDC8 Xfer helper: caller
// 0x004EDA8C constructs [ebp-0x30] via 0x004ECDA7 (push 0) then xfers it via
// 0x004ECDC8; caller 0x004ED6D2 similar. Evidence: xorps+movss float zero for
// +4/+8/+0xC and and-0 for +0x10 matches Rva layout; next row is the landed
// Xfer helper; Coord3DBase 12B from coord3d.h.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

class Rva004ECDC8
{
public:
	Rva004ECDC8(unsigned int v);
	unsigned int m_unk0;
	Coord3DBase m_unk4;
	int m_unk10;
};

Rva004ECDC8::Rva004ECDC8(unsigned int v)
{
	m_unk0 = v;
	m_unk4.x = 0.0f;
	m_unk4.y = 0.0f;
	m_unk4.z = 0.0f;
	_ReadWriteBarrier();
	m_unk10 = 0;
}
