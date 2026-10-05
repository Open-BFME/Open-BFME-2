// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// 0x00069AF5 (215B): SSE audio-spatial falloff leaf. Reads the nullable
// subobject at +0x37C0 (ints at +0x08/+0x0C, later ints at +0x120E0/+0x120E4),
// scales by the shared 5.0f at VA 0x00BC4EB8, lerps the host pair at
// +0x37D8/+0x37DC by the shared 0.5f at 0x00BC26F0, takes the x87 length of
// (e, fa, fb) through the proven inline-asm fsqrt helper, adds the shared
// 10.0f pan terms at 0x00BC2428 when the subobject is present, and writes
// (fa, fb, e, dist) to the out quartet. Shared floats are compiler literals
// holding the retail values (float-ref verified). Address names; host and
// subobject identities unproven.

class Rva00069AF5Sub
{
public:
	char m_pad00[0x08];
	int m_08; // +0x08
	int m_0C; // +0x0C
	char m_big[0x120E0 - 0x10];
	int m_120E0; // +0x120E0
	int m_120E4; // +0x120E4
};

class Rva00069AF5Math
{
public:
// ?Rva00069AF5Math::Sqrt present-unmatched
	static __forceinline float Sqrt(float val)
	{
		float retval;
		__asm {
			fld val
			fsqrt
			fstp retval
		}
		return retval;
	}
};

class Rva00069AF5Host
{
public:
	void rva00069AF5(float *out);
private:
	char m_pad[0x37C0];
	Rva00069AF5Sub *m_sub; // +0x37C0
	char m_pad2[0x37D8 - 0x37C4];
	float m_e1; // +0x37D8
	float m_e2; // +0x37DC
};

void Rva00069AF5Host::rva00069AF5(float *out)
{
	int ai = 0;
	int bi = 0;
	Rva00069AF5Sub *s = m_sub;
	if (s != 0)
	{
		ai = s->m_08;
		bi = s->m_0C;
	}
	float fa = (float)ai * 5.0f;
	float fb = (float)bi * 5.0f;
	float e = (m_e2 - m_e1) * 0.5f + m_e1;
	float t = e * e + fb * fb + fa * fa;
	float dist = Rva00069AF5Math::Sqrt(t);
	if (m_sub != 0)
	{
		fa = (float)m_sub->m_120E0 * 10.0f + fa;
		fb = (float)m_sub->m_120E4 * 10.0f + fb;
	}
	out[2] = e;
	out[0] = fa;
	out[1] = fb;
	out[3] = dist;
}
