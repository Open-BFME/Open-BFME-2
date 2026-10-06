// ?rva00091E83@Rva00091E83@@QAEXHMMMMHMHHHPAX@Z
// partial score=0.5 date=2026-10-06
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// ?rva00091E83@Rva00091E83@@QAEXHHHHHHHHHHH@Z @0x00091E83 90B: marshal and
// forward. When +0x14 is set, packs four floats into a stack struct and
// forwards (p1, struct, p6, p7-float, p8..p10, struct-ptr) to the pinned
// same-frame 0x0006813B on +0x14. Honest address-derived names; boundary
// verified (frame at 0x91E83, ret 0x2C at end).

struct RvaFloat4
{
	float a;
	float b;
	float c;
	float d;
	RvaFloat4(float a_, float b_, float c_, float d_) : a(a_), b(b_), c(c_), d(d_) {}
};

class Rva0006813BTarget
{
public:
	void rva0006813B(int p1, RvaFloat4 s, int p6, float p7, int p8, int p9, int p10, RvaFloat4 *sp);
};

class Rva00091E83
{
public:
	void rva00091E83(int p1, float p2, float p3, float p4, float p5, int p6, float p7, int p8, int p9, int p10, void *p11);

private:
	char m_pad00[0x14];
	Rva0006813BTarget *m_14;
};

// ?rva00091E83@Rva00091E83@@QAEXHHHHHHHHHHH@Z
void Rva00091E83::rva00091E83(int p1, float p2, float p3, float p4, float p5, int p6, float p7, int p8, int p9, int p10, void *p11)
{
	if (!m_14)
		return;
	RvaFloat4 s(p2, p3, p4, p5);
	m_14->rva0006813B(p1, s, p6, p7, p8, p9, p10, &s);
}
