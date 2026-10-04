// cl: /O1 /MD /arch:SSE /Op
// ?rva00261988@Rva001E438B@@QAEPAMPAMPAV1@@Z RVA 0x00261988 24B
// Evidence: calls Rva001E438B::rva001E438B 0x001E438B with dst and src+0x38, returns dst;
//   thiscall pass-through ecx proven by caller 0x00261B3F mov ecx,[esi+8]; unblocks 0x003698CD 0x00261ABB 0x00296065.

class Rva001E438B
{
public:
	void rva001E438B(float *dst, const float *src);
	float *rva00261988(float *dst, Rva001E438B *src);
	char _00[0x38];
	float m_38;
	float m_3c;
	float m_40;
};

float *Rva001E438B::rva00261988(float *dst, Rva001E438B *src)
{
	rva001E438B(dst, &src->m_38);
	return dst;
}
