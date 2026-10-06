// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva00363BC7@Rva00363BC7@@QAEPAXPAUCoord2D@@PAM@Z, retail 0x00363BC7, 170 bytes.
// Unlock: if +0x08 null zeroes out vec and sets *len to g_00BCF628 returning
// null; else builds dx dy from template +0xC/+0x10 minus this +0xC/+0x10,
// length via rowed Coord2D::length, clamps *len to g_00BCF628, normalizes out
// vec by the 1.0f literal pooled at 0x00BBB8D8. Evidence: unlock lane, callers
// 0x001E3572 0x00365F4B; len kept in ST0 via local. The literal (not a named
// extern global) is what puts the `movss xmm1,[out]` load before the 1.0f load.


struct Coord2D
{
	float x;
	float y;
	float length() const;
};

struct LocomotorTemplate
{
	char m_pad[0xC];
	float m_x0C;
	float m_y10;
};

class Rva00363BC7
{
public:
	void *rva00363BC7(Coord2D *out, float *outLen);
	char m_pad00[8];
	LocomotorTemplate *m_08;
	float m_0C;
	float m_10;
};

void *Rva00363BC7::rva00363BC7(Coord2D *out, float *outLen)
{
	if (m_08 == 0) {
		out->y = 0.0f;
		out->x = 0.0f;
		*outLen = 0.01f;
		return 0;
	}
	out->x = m_08->m_x0C - m_0C;
	out->y = m_08->m_y10 - m_10;
	float len = out->length();
	*outLen = len;
	if (0.01f > len) {
		*outLen = 0.01f;
	}
	float inv = 1.0f / *outLen;
	out->x *= inv;
	out->y *= inv;
	return m_08;
}
