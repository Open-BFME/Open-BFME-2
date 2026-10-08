// ?Rva004BD8A2@@YGXAAUBfmeVec2f@@@Z
// partial score=0.9 date=2026-10-08
// cl: /MD
// ?Rva004BD8A2@@YGXAAUBfmeVec2f@@@Z @0x004BD8A2 27B: stdcall, one reference argument, ret 4.
// Zeroes both float members of the referenced pair (x at +0, y at +4).
// Member names and the pair's owning type are address-derived views only.
struct BfmeVec2f
{
	float x;
	float y;
};

void __stdcall Rva004BD8A2(BfmeVec2f &v)
{
	volatile int unused = 0;
	v.x = 0.0f;
	v.y = 0.0f;
}
