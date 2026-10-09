// ?rva001F4E2D@Rva001F4E2D@@QAE_NXZ
// partial score=0.96 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD
// ?rva001F4E2D@Rva001F4E2D@@QAE_NXZ, retail 0x001F4E2D, 85 bytes.
// Branch on ParticleSystem+8 value selecting helper at +0x94 vs +0x98
// via virtual slot +0x10 with int arg. Guard dword at +0x8C, source at +0x3C.
// Evidence: unlock lane, 6 callers, pin ?Make001FCBD7@@YAPAVParticleSystem@@XZ,
// prev/next /O1 RGBColor getters, ret bool no args.

class ParticleSystem
{
public:
	int m_pad0;
	int m_pad4;
	int m_val;
};
class Rva001F4E2DHelper
{
public:
	virtual void u0();
	virtual void u1();
	virtual void u2();
	virtual void u3();
	virtual bool check(int v);
};
extern ParticleSystem *__cdecl Make001FCBD7();
class Rva001F4E2D
{
public:
	bool rva001F4E2D();
private:
	char m_pad0[0x3c];
	ParticleSystem *m_ps;
	char m_pad40[0x4c];
	int m_flag8C;
	char m_pad90[4];
	Rva001F4E2DHelper *m_h94;
	Rva001F4E2DHelper *m_h98;
};
bool Rva001F4E2D::rva001F4E2D()
{
	ParticleSystem *ps; int v;
	if (m_flag8C != 0)
		goto failed;
	ps = m_ps;
	if (ps == 0)
		ps = Make001FCBD7();
	v = ps->m_val;
	switch(v) {
	case 3: case 4: case 7:
		{ Rva001F4E2DHelper *h=m_h98; if(h) return h->check(v); }
failed:
		return false;
	case 1: case 2: case 5: case 6:
		{ Rva001F4E2DHelper *h=m_h94; if(h) return h->check(v); }
		goto failed;
	default: return true;
	}
}
