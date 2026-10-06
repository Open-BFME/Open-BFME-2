// cl: /MD
// ?rva004D38D8@Rva004D38D8@@QAE_NM@Z 0x004D38D8 46 ratio check vs float arg, early true when count <= 0
// Evidence: gap between 0x004D38C5+19 and 0x004D3906; reads ecx+0x260 count and ecx+0x264 total; cvtsi2ss/divss/comiss/jbe shape; callers at 0x004D44B9 0x004D44E7 0x004D44FC 0x004D465E 0x004D4684 0x004D4796.

class Rva004D38D8
{
public:
	bool rva004D38D8(float f);
private:
	char m_pad[0x260];
	int m_260;
	int m_264;
};

bool Rva004D38D8::rva004D38D8(float f)
{
	if (m_260 <= 0)
		return true;
	float ratio = (float)m_264 / (float)m_260;
	if (f > ratio)
		return false;
	return true;
}
