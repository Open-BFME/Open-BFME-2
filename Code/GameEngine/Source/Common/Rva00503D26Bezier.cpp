// cl: /DNDEBUG /MD /EHs-c-
// ?Rva00503D26Evaluate@@YAMMMMM@Z @0x00503D26 40B
// Quadratic Bezier scalar evaluate(a b c t) = (1-t)^2*a + 2*(1-t)*t*b + t^2*c.
// Pure x87, EBP frame. Unlocks 0x00503DEB 0x00503E17.
// Evidence: fld1 fsub t then a*u 2*b*t sum*u c*t*t pattern, callers 0x00503E0E 0x00503E46.
float __cdecl Rva00503D26Evaluate(float a, float b, float c, float t);
float __cdecl Rva00503D26Evaluate(float a, float b, float c, float t)
{
	float u = 1 - t;
	float s = a * u + 2 * b * t;
	s = s * u + c * t * t;
	return s;
}
extern float g_Va00863BF8;
// g_Va00863BF8: matched references place it at VA 0xc63bf8 (retail .rdata value 0.5833333f).
float g_Va00863BF8 = 0.5833333f;
struct Rva00503DEB
{
	char m_pad[0x10];
	float m_10;
	float rva00503DEB();
};
float Rva00503DEB::rva00503DEB()
{
	return Rva00503D26Evaluate(0.5f, g_Va00863BF8, 1.0f, m_10);
}
float __cdecl Rva00503D4ECubic(float a, float b, float c, float d, float t);
float __cdecl Rva00503D4ECubic(float a, float b, float c, float d, float t)
{
	float u = 1 - t;
	float s = a * u + b * t * 3.0f;
	s = s * u + c * t * t * 3.0f;
	s = s * u + d * t * t * t;
	return s;
}
