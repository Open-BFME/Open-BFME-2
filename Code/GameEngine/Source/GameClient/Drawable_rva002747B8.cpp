// cl: /DNDEBUG /MD
//
// ?rva002747B8@Rva002747B8@@QAEXMMM@Z @0x002747B8 65B
// Subobject at caller+0x8c (0x50B alloc at 0x00276BBD via ctor 0x00271826):
// stores 3 float args at +0x1C/+0x20/+0x24, duplicates them at
// +0x28/+0x2C/+0x30, then marker byte 3 at +0x38 and int -2 at +0x34.
// Evidence: unlock lane, caller 0x00276BA9 passes global+0x30 floats on stack
// with ecx=[ebx+0x8c], ret 0xC three-float thiscall.
class Rva002747B8
{
public:
	void rva002747B8(float a, float b, float c);
private:
	char m_pad[0x1C];
	float m_1C;
	float m_20;
	float m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	unsigned char m_38;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void Rva002747B8::rva002747B8(float a, float b, float c)
{
	m_1C = a;
	m_20 = b;
	m_24 = c;
	_ReadWriteBarrier();
	m_28 = reinterpret_cast<int &>(m_1C);
	m_2C = reinterpret_cast<int &>(m_20);
	m_30 = reinterpret_cast<int &>(m_24);
	m_38 = 3;
	m_34 = -2;
}
