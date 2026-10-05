// ?rva004A0194@Rva004A0194@@QAE_NPAUCoord3D@@PAM@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva004A0194@Rva004A0194@@QAE_NPAUCoord3D@@PAM@Z @0x004A0194 212B ret 8.
// Transform the holder vector at this-0x1C by the 3x4 matrix at (this-0x18)+8.
// The extra float is holder+0x2C plus the matrix object +0x44.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva004A0194Mat
{
	char m_pad[8];
	float m[3][4];
	char m_gap[0xC];
	float m_44;
};

struct Rva004A0194Holder
{
	char m_pad[8];
	Coord3D m_v;
	char m_gap[0x18];
	float m_extra;
};

class Rva004A0194
{
public:
	bool rva004A0194(Coord3D *outPos, float *outExtra);
};

bool Rva004A0194::rva004A0194(Coord3D *outPos, float *outExtra)
{
	Rva004A0194Mat *obj = *(Rva004A0194Mat **)((char *)this - 0x18);
	if (obj == 0)
		return false;
	Rva004A0194Holder *holder = *(Rva004A0194Holder **)((char *)this - 0x1C);
	float y = holder->m_v.y;
	float z = holder->m_v.z;
	float x = holder->m_v.x;
	Coord3D result;
	result.x = (obj->m[0][2] * z + obj->m[0][1] * y) + obj->m[0][0] * x + obj->m[0][3];
	result.y = (obj->m[1][2] * z + obj->m[1][0] * x) + obj->m[1][1] * y + obj->m[1][3];
	result.z = (obj->m[2][1] * y + obj->m[2][2] * z) + obj->m[2][0] * x + obj->m[2][3];
	*outPos = result;
	*outExtra = holder->m_extra + (*(Rva004A0194Mat **)((char *)this - 0x18))->m_44;
	return true;
}
