// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// retail 0x0028447F, 32 bytes. Donor game/GameEngine/Source/Common/BfmeConv1035.cpp
// recompiled /Os emits this body byte-identically on unclaimed .text. Dedicated
// TU holding the preamble and this one body; the donor's other five bodies
// (bfmeGo1035A, bfmeGo1035B, bfmeGo1035E, bfmeGo1035F and bfmeGo1035G) are
// omitted -- bfmeGo1035G is recovered in its own TU.
class BfmeX1035;

struct BfmeT1035
{
	void bfmeUse1035(BfmeX1035 *p, int b);

	int m_bfmeV;
};

void __stdcall bfmeGo1035C(BfmeX1035 *p, int b)
{
	if (p == 0)
		return;

	BfmeT1035 t;

	t.m_bfmeV = 0;
	t.bfmeUse1035(p, b);
}
