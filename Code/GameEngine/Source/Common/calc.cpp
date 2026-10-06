// cl: /DNDEBUG /MD /EHs-c-
// ?Rva00503D8EEvaluate@@YAMMMMMM@Z @0x00503D8E 93B: Catmull-Rom scalar evaluate(p0 p1 p2 p3 t).
// Donor: reference/open-bfme-1/Code/GameEngine/Source/Common/calc.cpp (Rva00064410Catmull::evaluate stub)
// and BfmeConv1266.cpp bfmeSpline1266 formula. Callers at 0x00503F61 0x00503F8B 0x00503FB1 0x00504477
// 0x005C718B 0x005C735C 0x005C7386 0x005C73AE. Constants 3.0 5.0 4.0 0.5 in .rdata.
// ?Rva00503F2CCalc@@YAXPAURva00503F2CPoint@@PBU1@111M@Z @0x00503F2C 165B: Catmull-Rom 3D wrapper, 3 evaluate calls.

struct Rva00503F2CPoint
{
	float x;
	float y;
	float z;
};

float __cdecl Rva00503D8EEvaluate(float p0, float p1, float p2, float p3, float t)
{
	return ((((p1 * 3.0f - p0 - p2 * 3.0f + p3) * t + (p0 + p0 - p1 * 5.0f + p2 * 4.0f - p3)) * t + (p2 - p0)) * t + (p1 + p1)) * 0.5f;
}

void __cdecl Rva00503F2CCalc(Rva00503F2CPoint *out, const Rva00503F2CPoint *p0, const Rva00503F2CPoint *p1, const Rva00503F2CPoint *p2, const Rva00503F2CPoint *p3, float t)
{
	volatile float z = Rva00503D8EEvaluate(p0->z, p1->z, p2->z, p3->z, t);
	volatile float y = Rva00503D8EEvaluate(p0->y, p1->y, p2->y, p3->y, t);
	float x = Rva00503D8EEvaluate(p0->x, p1->x, p2->x, p3->x, t);
	out->x = x;
	out->y = y;
	out->z = z;
}
