// ?rva002ED236@Pathfinder@@QAEHPAVRva0028B984ByteField@@UTwoFloats@@M@Z
// partial score=0.98 date=2026-10-06
// ?rva002ED236@Pathfinder@@QAEHPAVRva0028B984ByteField@@UTwoFloats@@M@Z
// partial score=0.98 date=2026-10-05
// cl: /O1 /MD /arch:SSE
// ?rva002ED236@Pathfinder@@QAEHPAVRva0028B984ByteField@@UTwoFloats@@M@Z
// recovered 2026-10-05 from packet 0x002ED236 221B lane=linkbody LINK 4 files 807B.
// Evidence: rowed get 0x0028B984 and IsOdd 0x002EBBFB; pin Pathfinder 0x001E3647; rowed Rva0036666B 0x0036666B; float adds via g_00BC4EB8 and compare via g_00C52ACC; callers 0x002803E7 0x0028B9DB 0x002EF801 etc.
// ?rva002ED236@Pathfinder@@QAEHPAVRva0028B984ByteField@@UTwoFloats@@M@Z present-unmatched
class Rva0028B984ByteField
{
public:
	unsigned char get() const;
};

unsigned char __cdecl Rva002EBBFBIsOdd(void *p);

class Rva0036666B
{
public:
	char m_pad[0x34];
	int m_a;
	int m_b;
	bool rva0036666B();
};

struct Rva001E3647Result
{
	char m_pad[0x0C];
	unsigned int m_tag;
};

class Pathfinder;

struct PathfinderEntry
{
	Rva0036666B m_check;
	int m_h;
};

struct TwoFloats
{
	float x;
	float y;
};

class Pathfinder
{
public:
	void *rva001E3647(int a, int b);
	int rva002ED236(Rva0028B984ByteField *p, TwoFloats v, float c);
private:
	char m_pad[0xE0];
	PathfinderEntry m_entries[16];
};

extern float g_00BC4EB8;
extern float g_00C52ACC;

int Pathfinder::rva002ED236(Rva0028B984ByteField *p, TwoFloats v, float c)
{
	if (p != 0) {
		if (p->get() != 0) {
			return 1;
		}
		if (Rva002EBBFBIsOdd(p) != 0) {
			goto loop;
		}
		float f = g_00BC4EB8;
		v.x = v.x + f;
		v.y = v.y + f;
	}
loop:
	{
		int i = 2;
		int *pb = &m_entries[0].m_check.m_b;
		for (;;) {
			Rva0036666B *chk = (Rva0036666B *)(pb - 14);
			if (chk->rva0036666B()) {
				if (*pb != 0) {
					Rva001E3647Result *r = (Rva001E3647Result *)rva001E3647(i, (int)&v);
					if (r != 0) {
						unsigned int vv = r->m_tag;
						if (((vv >> 4) & 0x3F) == (unsigned int)i) {
							if ((vv & 0xF) != 5) {
								float hf = (float)*(pb + 1);
								float d = hf - c;
								if (g_00C52ACC > d) {
									return i;
								}
							}
						}
					}
				}
			}
			++i;
			pb += 16;
			if (i > 0xF) {
				break;
			}
		}
	}
	{
		Rva001E3647Result *r2 = (Rva001E3647Result *)rva001E3647(1, (int)&v);
		if (r2 != 0) {
			return ((r2->m_tag >> 4) & 0x3F);
		}
		return 1;
	}
}
