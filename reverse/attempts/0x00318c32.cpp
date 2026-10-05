// ?rva00318C32@Rva00318C79Owner@@QAEPAVRva00318C32Ret@@XZ
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva00318C32@Rva00318C79Owner@@QAEPAVRva00318C32Ret@@XZ @0x00318C32 71B.
// Builds a 3-float search key from +0x44/+0x48 plus 0.0f and calls the rowed
// Rva0020EE29::rva0020FAEA 0x0020FAEA via g_009FEF10->+0xB0 with the void* at
// +0x8C; stores the result back to +0x8C and returns it for the wrapper
// 0x00318C79. Evidence: 4 matched callers; movss/xorps need /arch:SSE.
// Row 0x0020FAEA declares void return but the body uses eax as a pointer
// (inner finder result); declared here as returning void* for honest codegen.
class Rva00318C32Ret
{
public:
	char m_pad00[0x12C];
	int m_12C;
};

class Rva0020EE29
{
public:
	void *rva0020FAEA(float *a1, void *a2);
};

class Rva002BA8F1Logic
{
public:
	char m_pad00[0xB0];
	Rva0020EE29 *m_B0;
};

extern Rva002BA8F1Logic *g_009FEF10;

class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
private:
	char m_pad00[0x44];
	float m_44;
	float m_48;
	char m_pad4C[0x40];
	void *m_8C;
};

// ?rva00318C32@Rva00318C79Owner@@QAEPAVRva00318C32Ret@@XZ present-unmatched
Rva00318C32Ret *Rva00318C79Owner::rva00318C32()
{
	float v[3];
	v[0] = m_44;
	Rva002BA8F1Logic *g = g_009FEF10;
	v[1] = m_48;
	v[2] = 0.0f;
	Rva00318C32Ret *r = (Rva00318C32Ret *)g->m_B0->rva0020FAEA(v, m_8C);
	m_8C = r;
	return r;
}
