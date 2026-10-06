// cl: /MD
// ??0Rva00084CA5@@QAE@XZ @0x00084CA5 74B
// Ctor-like init: sets +0xC to 0x10441B, zeroes +0x0/+0x4/+0x8/+0x10/+0x14/+0x18,
// copies GlobalData +0x110/+0x114/+0x118 to +0x1C/+0x20/+0x24. No vptr.
// Evidence: retail bytes, caller 0x00091B5E, extern TheWritableGlobalData in use.
class GlobalData
{
public:
	char m_pad[0x110];
	int m_110;
	int m_114;
	int m_118;
};

extern class GlobalData *TheWritableGlobalData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva00084CA5
{
public:
	Rva00084CA5();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
};

Rva00084CA5::Rva00084CA5() : m_0C(0x10441b)
{
	_ReadWriteBarrier();
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_04 = 0;
	m_08 = 0;
	m_00 = 0;
	m_1C = TheWritableGlobalData->m_110;
	m_20 = TheWritableGlobalData->m_114;
	m_24 = TheWritableGlobalData->m_118;
}
