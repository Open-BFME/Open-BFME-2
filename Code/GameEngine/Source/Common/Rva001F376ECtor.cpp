// cl: /MD
// ??0Rva001F376E@@QAE@XZ, RVA 0x001F376E, 80B.
// Unlock lane: no callees. Callers at 0x001F4B76/0x001F9BDD.
// Ctor storing vtable 0x007E15B4 and zeroing twelve floats at
// +0x04/+0x08/+0x0C/+0x28/+0x2C/+0x30/+0x1C/+0x20/+0x24/+0x10/+0x14/
// +0x18, int at +0x34 and byte at +0x38.
class Rva001F376E
{
public:
	Rva001F376E();
	virtual ~Rva001F376E();
private:
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
	int m_34;
	unsigned char m_38;
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
Rva001F376E::Rva001F376E()
{
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	m_28 = 0.0f;
	m_2c = 0.0f;
	m_30 = 0.0f;
	m_1c = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	_ReadWriteBarrier();
	m_34 = 0;
	m_38 = 0;
}
