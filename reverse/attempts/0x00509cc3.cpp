// ??0Made002CC841@@QAE@XZ
// partial score=0.94 date=2026-10-04
// cl: /Os /DNDEBUG /MD /arch:SSE
// ??0Made002CC841@@QAE@XZ, retail 0x00509CC3, 95 bytes.
// Evidence: pin ??0Made002CC841@@QAE@XZ; rowed base Rva00507823 0x0050775B;
// vtable 0x008646B0 plus dwords +0x128..+0x138=0 plus dword +0x13c=6 plus
// floats +0x140..+0x148=0.0 plus byte +0x14c=0 plus dword +0x150=0; caller
// parseProjectileNugget 0x002CC841 news 0x154; Made002CC907Ctor precedent
// for base+members with /arch:SSE float zeros.
class Rva00507823
{
public:
	Rva00507823();
	virtual void __pad();
private:
	char m_pad[0x128 - 4];
};

class Made002CC841 : public Rva00507823
{
public:
	Made002CC841();
private:
	int m_128;
	int m_12c;
	int m_130;
	int m_134;
	int m_138;
	int m_13c;
	float m_140[3];
	unsigned char m_14c;
	char m_pad14d[3];
	int m_150;
};

Made002CC841::Made002CC841()
{
	m_128 = 0;
	m_12c = 0;
	m_130 = 0;
	m_134 = 0;
	m_138 = 0;
	float *p = m_140;
	m_13c = 6;
	p[0] = 0.0f;
	p[1] = 0.0f;
	p[2] = 0.0f;
	m_14c = 0;
	m_150 = 0;
}
