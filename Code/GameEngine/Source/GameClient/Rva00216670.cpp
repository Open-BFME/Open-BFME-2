// cl: /MD
// Retail RVA 0x00216670, 75 bytes.
// ?rva00216670@Rva00216670@@QAEXIM@Z chain from just-landed 0x00216517: banner offset guard.
// __thiscall Banner setter with (index float): if new float equals slot at +0x3c return; if flag at +0x20 fire SetBannerXOffset via 0x00216517 then store.
// Evidence: callee 0x00216517 rowed int-return firer; callers 0x0052A2F4 0x0052A52B 0x0052AB56; literal SetBannerXOffset; global TheRva00222A8BTarget 0x009FE4CC.
class Rva00222A8BTarget;

int __cdecl Rva00216517Fire(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int *pInt, const float *pFloat);

extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva00216670
{
	char m_pad00[0x20];
	unsigned char m_flag20;
	char m_pad21[3];
	void *m_owner24;
	char m_pad28[0x14];
	float m_values3C[4];
public:
	void rva00216670(unsigned int index, float value);
};

void Rva00216670::rva00216670(unsigned int index, float value)
{
	float *slot = &m_values3C[index];
	if (value == *slot)
		return;
	if (m_flag20)
		Rva00216517Fire(TheRva00222A8BTarget, m_owner24, "SetBannerXOffset", &index, &value);
	*slot = value;
}
