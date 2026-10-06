// cl: /MD /Oi
// ??0Rva0027C36A@@QAE@XZ @0x0027C36A 166B
// Evidence: thiscall default ctor returns this; two vector-iterator arrays at +0x6c Region3D x4 and +0x9c 6B x2; floats zeroed via movss; callers 11 including 0x00280C4C.
#include <cstring>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Region3D
{
public:
	Region3D();
	float m_x;
	float m_y;
	float m_z;
};

class Rva0027C36ASix
{
public:
	Rva0027C36ASix();
	char m_d[6];
};

class Rva0027C36A
{
public:
	Rva0027C36A();
	float m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
	float m_24;
	float m_28;
	float m_2c;
	float m_30;
	float m_34;
	float m_38;
	float m_3c;
	float m_40;
	float m_44;
	float m_48;
	int m_4c;
	int m_50;
	int m_54;
	int m_58[4];
	unsigned char m_68;
	char m_pad69[3];
	Region3D m_6c[4];
	Rva0027C36ASix m_9c[2];
};

Rva0027C36A::Rva0027C36A()
{
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	m_1c = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_2c = 0.0f;
	m_30 = 0.0f;
	m_34 = 0.0f;
	m_38 = 0.0f;
	m_3c = 0.0f;
	m_40 = 0.0f;
	m_44 = 0.0f;
	m_48 = 0.0f;
	_ReadWriteBarrier();
	m_4c = 0;
	m_50 = 0;
	m_68 = 0;
	m_54 = 0;
	memset(m_58, 0, sizeof(m_58));
}
