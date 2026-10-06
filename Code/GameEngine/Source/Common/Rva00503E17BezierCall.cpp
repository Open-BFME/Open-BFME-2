// cl: /DNDEBUG /MD /EHs-c-
// ?rva00503E17@Rva00503E17@@QAEMXZ @0x00503E17 56B
// Bezier caller sibling of 0x00503DEB: Evaluate(0.0 g_863BFC 0.5 g_7BB8D8 minus m_14).
// SSE for t computation, x87 for args. Unlocks 0x005042F2.
// Evidence: movss global minus [ecx+0x14] then fldz fld globals pattern, caller 0x005043DF.
float __cdecl Rva00503D26Evaluate(float a, float b, float c, float t);
extern float g_Va00863BFC;
// g_Va00863BFC: matched references place it at VA 0xc63bfc (retail .rdata value 0.41666666f).
float g_Va00863BFC = 0.41666666f;
struct Rva00503E17
{
	char m_pad[0x14];
	float m_14;
	float rva00503E17();
};
float Rva00503E17::rva00503E17()
{
	return Rva00503D26Evaluate(0.0f, g_Va00863BFC, 0.5f, 1.0f - m_14);
}
