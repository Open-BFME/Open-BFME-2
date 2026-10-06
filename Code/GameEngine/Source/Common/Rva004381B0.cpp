// cl: /MD
//
// ?rva004381B0@Rva004381B0@@QAEXM@Z @0x004381B0 20B
// Leaf __thiscall (ret 4, one float stack arg): keeps max of arg and float
// at +0x10 via movss/comiss/jbe. Owner unproven, honest Rva name. Own TU
// because it needs /arch:SSE for movss, which neighbour Rva00438144Update
// (/O1) lacks. Caller 0x00299C43.
class Rva004381B0
{
public:
	void rva004381B0(float v);
private:
	char m_pad00[0x10];
	float m_10;
};

void Rva004381B0::rva004381B0(float v)
{
	if (v > m_10)
		m_10 = v;
}
