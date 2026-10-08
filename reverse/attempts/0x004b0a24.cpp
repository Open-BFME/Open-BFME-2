// ?rva004B0A24@Rva004B0A24Owner@@QAEXPAURva004B0A24Out@@MM@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004B0A24, 134 bytes, thiscall with a Coord2D out pointer and two
// float offsets (ret 0xC). The owner's +8 object supplies a float angle at
// +0x44 and a base position at +0x38/+0x3C; the offset is rotated by sin and
// cos of the angle and added to the base, written to the out pointer.
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);

struct Rva004B0A24Out
{
	float x;
	float y;
};

class Rva004B0A24Object
{
public:
	char m_pad[0x38];
	float m_baseX;			// +0x38
	float m_baseY;			// +0x3C
	char m_pad2[4];
	unsigned int m_angleBits;	// +0x44
};

class Rva004B0A24Owner
{
public:
	void rva004B0A24(Rva004B0A24Out *out, float x, float y);
	char m_pad[8];
	Rva004B0A24Object *m_object;	// +0x8
};

void Rva004B0A24Owner::rva004B0A24(Rva004B0A24Out *out, float x, float y)
{
	volatile float angle = *(float *)&m_object->m_angleBits;
	volatile float s = (float)sin((double)angle);
	angle = (float)cos((double)angle);
	float c = angle;
	float cy = c * y;
	float cx = c * x;
	float sx = s * x;
	float sy = s * y;
	float ty = m_object->m_baseY + (cy + sx);
	float tx = m_object->m_baseX + (cx - sy);
	out->x = tx;
	out->y = ty;
}
