// cl: /DNDEBUG /MD
//
// ?rva00271779@Rva00271779@@QAEXURGBColor00271779@@HHHMM@Z retail 0x00271779 67B
// Evidence: unlock lane; callers 0x001E0A30 plus 0x002EBDF8 plus 0x000D1A70; TintDrawableFXNugget 0x001E09D8 source RGBColor at +0x148 plus times plus freq plus amp; dest +0x6C contiguous 0x20B via movsd x3 plus mov plus movss; ret 0x20.
struct RGBColor00271779 {
	float red;
	float green;
	float blue;
};
class Rva00271779 {
public:
	void rva00271779(RGBColor00271779 color, int pre, int post, int sustained, float freq, float amp);
private:
	char m_pad[0x6C];
	RGBColor00271779 m_color;
	int m_pre;
	int m_post;
	int m_sustained;
	float m_amp;
	float m_freq;
};
void Rva00271779::rva00271779(RGBColor00271779 color, int pre, int post, int sustained, float freq, float amp)
{
	m_color = color;
	m_pre = pre;
	m_post = post;
	m_sustained = sustained;
	m_freq = freq;
	m_amp = amp;
}
