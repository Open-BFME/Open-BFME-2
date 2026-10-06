// cl: /MD /EHsc
// ?rva005FC8FD@Rva005FC8FD@@QAEXXZ @0x005FC8FD 227B: triple Apt overlay setter via rowed AptCall 0x0050E9FE with SetState plus SetNotThereOverlayState plus SetDisbandingOverlayState. Evidence: callers jmp 0x005FC9F8 plus TheRva00222A8BTarget plus g_Rva0107301CEmptyString plus strings _selected _up _show _hide.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva005FC8FDInner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva005FC8FD
{
public:
	void rva005FC8FD();
private:
	char m_pad0[8];
	void *m_8;
	Rva005FC8FDInner *m_C;
	char m_pad10[0x34 - 0x10];
	unsigned char m_34;
};

void Rva005FC8FD::rva005FC8FD()
{
	if (!(m_34 & 0x10)) {
		const char *state = (m_34 & 1) ? "_selected" : "_up";
		const char *prefix = m_C ? m_C->m_name : g_Rva0107301CEmptyString;
		Rva0050E9FEAptCall(TheRva00222A8BTarget, m_8, prefix, "SetState", &state);
		m_34 |= 0x10;
	}
	if (!(m_34 & 0x20)) {
		const char *state = (m_34 & 2) ? "_show" : "_hide";
		const char *prefix = m_C ? m_C->m_name : g_Rva0107301CEmptyString;
		Rva0050E9FEAptCall(TheRva00222A8BTarget, m_8, prefix, "SetNotThereOverlayState", &state);
		m_34 |= 0x20;
	}
	if (!(m_34 & 0x40)) {
		const char *state = (m_34 & 4) ? "_show" : "_hide";
		const char *prefix = m_C ? m_C->m_name : g_Rva0107301CEmptyString;
		Rva0050E9FEAptCall(TheRva00222A8BTarget, m_8, prefix, "SetDisbandingOverlayState", &state);
		m_34 |= 0x40;
	}
}
