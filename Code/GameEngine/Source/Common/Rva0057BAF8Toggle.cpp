// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva0057BAF8@Rva0057BAF8@@QAEX_N@Z, retail 0x0057BAF8, 86 bytes.
// Toggle-button Apt state via rowed AptCall 0x0050E9FE with _enabled/_disabled.
// Skips when bool at +0x2d already equals arg; prefix is +0x18 plus 8 else
// g_Rva0107301CEmptyString; level is +0x14; function SetToggleButtonState.
// Evidence: strings _enabled _disabled SetToggleButtonState; externs
// g_Rva0107301CEmptyString and TheRva00222A8BTarget; caller 0x0057BBBB;
// precedent Rva005F086E 86B same shape (Rva005C7A29 mov-first which).
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva0057BAF8Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva0057BAF8
{
public:
	void rva0057BAF8(bool flag);
private:
	char m_pad00[0x14];
	void *m_level14;
	Rva0057BAF8Inner *m_inner18;
	char m_pad1C[0x2D - 0x1C];
	bool m_flag2D;
};

void Rva0057BAF8::rva0057BAF8(bool flag)
{
	if (flag == m_flag2D)
		return;
	const char *state = "_enabled";
	if (!flag)
		state = "_disabled";
	const char *prefix = m_inner18 ? m_inner18->m_name : g_Rva0107301CEmptyString;
	Rva0050E9FEAptCall(TheRva00222A8BTarget, m_level14, prefix, "SetToggleButtonState", &state);
	m_flag2D = flag;
}
