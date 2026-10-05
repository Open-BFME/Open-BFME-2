// cl: /O1 /DNDEBUG /MD /EHs-c- /Oy- /G7 /arch:SSE
// ?rva0027541E@Drawable@@QAEXPBURGBColor@@III@Z @0x0027541E 114B evidence: lazy TintEnvelope at +0x68 via rowed new 0x2FDA0 and ctor 0x271826, TintEnvelope::play 0x2744F2 row, float 1.0f via g_Va00BBB8D8, clears bit 2 at +0x114; neighbours Rva00275376/Drawable_rva00275545 same flags.
struct RGBColor
{
	float r;
	float g;
	float b;
};

class Rva00271826
{
public:
	Rva00271826() throw();
private:
	char m_pad[0x50];
};

class TintEnvelope
{
public:
	void play(const RGBColor *peak, unsigned int attackFrames, unsigned int decayFrames, unsigned int sustainAtPeak);
};

extern float g_Va00BBB8D8;

void *operator new(unsigned int s) throw();

class Drawable
{
public:
	void rva0027541E(const RGBColor *peak, unsigned int a1, unsigned int a2, unsigned int a3);
private:
	unsigned char m_pad00[0x68];
	Rva00271826 *m_68;
	unsigned char m_pad6C[0x114 - 0x6C];
	int m_114;
};

void Drawable::rva0027541E(const RGBColor *peak, unsigned int a1, unsigned int a2, unsigned int a3)
{
	if (m_68 == 0)
		m_68 = new Rva00271826;
	if (peak != 0) {
		((TintEnvelope *)m_68)->play(peak, a2, a1, a3);
	} else {
		float white = g_Va00BBB8D8;
		RGBColor tmp;
		tmp.r = white;
		tmp.g = white;
		tmp.b = white;
		((TintEnvelope *)m_68)->play(&tmp, 1, 4, 1);
	}
	m_114 &= ~4;
}
