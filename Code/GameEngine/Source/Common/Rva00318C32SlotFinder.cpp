// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva00318C32@Rva00318C79Owner@@QAEPAVRva00318C32Ret@@XZ @0x00318C32 71B.
// Builds a 3-float search key from +0x44/+0x48 plus 0.0f and calls the rowed
// Rva0020EE29::rva0020FAEA 0x0020FAEA via g_009FEF10->+0xB0 with the void* at
// +0x8C; stores the result back to +0x8C and returns it for the wrapper
// 0x00318C79. Evidence: 4 matched callers; movss/xorps need /arch:SSE.
// The shared 0x0020FAEA provider now returns void* with all 87 bytes exact.
// The manager pointer is fetched into its own local after the key is built: the
// retail load of the +0xB0 field follows the three key stores.
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

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

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

Rva00318C32Ret *Rva00318C79Owner::rva00318C32()
{
	float v[3];
	v[0] = m_44;
	v[1] = m_48;
	v[2] = 0.0f;
	Rva002BA8F1Logic *l = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic);
	Rva0020EE29 *mgr = l->m_B0;
	m_8C = mgr->rva0020FAEA(v, m_8C);
	return (Rva00318C32Ret *)m_8C;
}
