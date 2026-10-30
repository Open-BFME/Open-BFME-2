// cl: /MD /O1 /arch:SSE /G7 /Oa
// ?rva0056AB35@Rva0056ACC5@@QAEXH@Z @0x0056AB35 83B, slot 2 of the 0x0086D0FC vftable
// (class of the rowed ??1Rva0056ACC5@@UAE@XZ). Retail: if the +0x14 id equals the argument,
// clear the byte at +0x20 of the +0x10 helper, pass a 2-float pair {0.380859375, 0.7213541865}
// and the float 0.599609375 to the rowed Rva0029B187 member on TheInGameUI (0x009FEDF0), then
// set the +0x18 flag.
//
// Schedule note (target-evidence, measured with toys, W7-S2 r14): retail issues the byte store
// BEFORE the fstp of the float argument and loads the TheInGameUI receiver AFTER it. cl's list
// scheduler lets that receiver load fill the x87 `fld` latency shadow ahead of the store unless
// both accesses are volatile: a volatile store followed by a volatile load keeps source order.
// The volatile accesses are done through casts so the declarations stay plain.
struct Rva004E57E6Pair {
	float m_0;
	float m_4;
};

class Rva0029B187 {
public:
	void rva0029B187(Rva004E57E6Pair *p, float f);
};

class InGameUI;
extern class InGameUI *TheInGameUI;

struct Rva0056AB35Helper {
	char m_pad[0x20];
	unsigned char m_20;
};

class Rva0056ACC5 {
	char m_pad[0x10];
public:
	Rva0056AB35Helper *m_10;
	int m_14;
	unsigned char m_18;
	void rva0056AB35(int id);
};

void Rva0056ACC5::rva0056AB35(int id)
{
	if (m_14 != id)
		return;
	*(volatile unsigned char *)&m_10->m_20 = 0;
	{
	Rva004E57E6Pair tmp = { 0.380859375f, 0.7213541865348816f };
	((Rva0029B187 *)*(InGameUI * volatile *)&TheInGameUI)->rva0029B187(&tmp, 0.599609375f);
	}
	m_18 = 1;
}
