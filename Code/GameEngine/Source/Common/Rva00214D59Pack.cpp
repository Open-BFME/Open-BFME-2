// cl: /DNDEBUG /MD
// ?rva00214D59@Rva00214D59@@QAEHXZ retail 0x00214D59 169B
// Packed 0xFFRRGGBB from +0x64/+0x68/+0x6c scaled by +0x70 plus double-based
// base; upper clamp via cmov and lower via branch; final add/shl pack.
// Evidence: same +0x64 +0x68 +0x6c +0x70 layout in all four lanes; double
// helpers 1.0 255.0 via x87 ftol row 0x00629228; float scale
// 255.0f; caller at 0x0009569A.
// The 1.0/255.0 doubles and the 255.0f scale are literals (the banked
// attempt read them through globals), and the pack is written as shifted
// sums with the 0xFF000000 alpha last, which the compiler folds into the
// add 0xFF00 / shl 8 chain retail has.
class Rva00214D59
{
public:
	int rva00214D59();
private:
	char _pad[0x64];
	float m_64;
	float m_68;
	float m_6C;
	float m_70;
};
int Rva00214D59::rva00214D59()
{
	int base = (int)((1.0 - m_70) * 255.0);
	if (base > 255)
		base = 255;
	if (base < 0)
		base = 0;
	float fbase = (float)base;
	float tr = m_64 * m_70;
	int r = (int)(tr * 255.0f + fbase);
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	float tg = m_68 * m_70;
	int g = (int)(tg * 255.0f + fbase);
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	float tb = m_6C * m_70;
	int b = (int)(tb * 255.0f + fbase);
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return (r << 16) + (g << 8) + b + 0xFF000000;
}
