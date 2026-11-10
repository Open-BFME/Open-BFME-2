// cl: /O2 /Ob0

// Retail stores the class vtable (0x00BC64B0) here; the BFME1 donor baked
// its own vtable VA as a literal, which cannot transfer. The address of a
// sacrificial anchor stands in (mov-imm-DIR32, patched from retail); a plain
// extern would load through a register and reschedule the stores.
extern "C" char __identifier("??_7BfmeBaseCC@@6B@");

class Rva0081C2F0
{
	void *m_vt;
	int m_04, m_08, m_width, m_height, m_textureWidth, m_textureHeight, m_pitch;
	float m_20;
	int m_24;
	char m_28;

public:
	Rva0081C2F0 &set(int n);
};

Rva0081C2F0 &Rva0081C2F0::set(int n)
{
	m_20 = 1.0f;
	m_vt = (void *)&__identifier("??_7BfmeBaseCC@@6B@");
	m_04 = 0;
	m_08 = 0;
	m_width = 0;
	m_height = 0;
	m_textureWidth = 0;
	m_textureHeight = 0;
	m_pitch = 0;
	m_24 = n;
	m_28 = 0;
	if (n >= 6 || n < 0)
		m_24 = 0;
	return *this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0VideoBuffer@@QAE@H@Z=?set@Rva0081C2F0@@QAEAAV1@H@Z")
