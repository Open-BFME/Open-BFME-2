// cl: /arch:SSE /G7 /DNDEBUG /MD /O2
//
// ?rva0015E2B0@SegmentedLineClass@@QAEXMM@Z @0x0015E2B0 54B: clamp two floats
// to >=0 storing to +0xE4 and +0xF8 plus clear flag bit 1 at +0x12.
// Evidence: movss xorps comiss ja movaps twice plus and 0xFD; caller
// W3DLaserDraw doDrawModule; neighbours Set_Width Set_Color prove class.
#define MAX(a, b) ((a) > (b) ? (a) : (b))

class SegmentedLineClass
{
public:
	void rva0015E2B0(float a, float b);
private:
	char m_pad00[0x12];
	unsigned char m_flag12;
	char m_pad13[0xD1];
	float m_E4;
	char m_padE8[0x10];
	float m_F8;
};

void SegmentedLineClass::rva0015E2B0(float a, float b)
{
	float c = MAX(a, 0.0f);
	m_E4 = c;
	float d = MAX(b, 0.0f);
	m_flag12 &= (unsigned char)0xFD;
	m_F8 = d;
}
