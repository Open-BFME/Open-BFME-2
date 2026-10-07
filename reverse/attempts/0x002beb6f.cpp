// ?rva002BEB6F@Rva002BEB6FInterpolator@@QAEXPBURva002BEB6FPoint@@0PAU2@M@Z
// partial score=0.5 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Retail 002BEB6F..002BEBE3 RET16. Two coordinate components each use
// the same this+28 curve evaluated at the input time. Original names are
// unknown; prefix and ABI come directly from native accesses and calls.
struct Rva002BEB6FPoint { float x, y; };
class Rva00504BA9Curve { public: float rva00504BA9(float time); };
class Rva002BEB6FInterpolator {
public:
 void rva002BEB6F(const Rva002BEB6FPoint *start, const Rva002BEB6FPoint *end, Rva002BEB6FPoint *out, float time);
private:
 char unknown00[0x28]; Rva00504BA9Curve curve;
};
void Rva002BEB6FInterpolator::rva002BEB6F(const Rva002BEB6FPoint *start, const Rva002BEB6FPoint *end, Rva002BEB6FPoint *out, float time)
{
 float factor = curve.rva00504BA9(time);
 out->x = start->x + (end->x - start->x) * factor;
 time = curve.rva00504BA9(time);
 out->y = start->y + (end->y - start->y) * time;
}
