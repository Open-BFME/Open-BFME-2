// cl: /EHsc /O1 /DNDEBUG /MD
// Gamma-setter at 0x00043073 (85B): when the +0x18 flag is clear, takes the
// DX8 device lock, sets the gamma ramp, and releases. The inline unwind guard
// couples the rowed acquire 0x0011F520 with the rowed release 0x00120F50, and
// its try-level state is what carries the /EHsc frame (with the helper-style
// __EH_prolog that /O1 selects); the guard itself emits no code. The fourth
// parameter is the bool Set_Gamma slot and the fifth is a literal 0, which is
// what orders the pushes as push-0 then push-f.
void BFME_DX8_Thread_Lock();
class DX8Wrapper
{
public:
	static void Set_Gamma(float r, float g, float b, bool f, bool x);
};
bool BFME_DX8_Thread_Assert();

struct Rva00043073Guard
{
	Rva00043073Guard() { BFME_DX8_Thread_Lock(); }
	~Rva00043073Guard() { BFME_DX8_Thread_Assert(); }
};

class Rva00043073
{
	char m_pad[0x18];
	unsigned char m_flag18;
public:
	void rva00043073(float a, float b, float c, bool f);
};

void Rva00043073::rva00043073(float a, float b, float c, bool f)
{
	if (m_flag18 == 0)
	{
		Rva00043073Guard g;
		DX8Wrapper::Set_Gamma(a, b, c, f, 0);
	}
}
