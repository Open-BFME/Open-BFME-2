// cl: /MD /Op
//
// ?rva001E438B@Rva001E438B@@QAEXPAMPBM@Z, retail 0x001e438b, 54 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// ?rva001E438B@Rva001E438B@@QAEXPAM0@Z @0x001E438B 54B
// __thiscall void (float *, float *): dst[0..2] = src[0..2] minus the 3-float
// vector at this+0x38/0x3c/0x40.
// Evidence: self-contained subss shape; callers 0x001E9D72 0x00261994
// 0x00375D32 0x004D9177; neighbours Bfme5SixtyTwo Rva001E43CFCopy.
class Rva001E438B
{
public:
	void rva001E438B(float *dst, const float *src);
	char _00[0x38];
	float m_38;
	float m_3c;
	float m_40;
};
void Rva001E438B::rva001E438B(float *dst, const float *src)
{
	float x = src[0];
	x -= m_38;
	float y = src[1];
	y -= m_3c;
	float z = src[2];
	z -= m_40;
	dst[0] = x;
	dst[1] = y;
	dst[2] = z;
}
