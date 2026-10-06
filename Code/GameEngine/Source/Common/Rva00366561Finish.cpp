// ?rva00366561@Rva00366561@@QAE_NHH@Z
// partial score=0.93 date=2026-10-01
// cl: /MD
// ?rva00366561@Rva00366561@@QAE_NHH@Z 0x00366561 42B via two dword guards at +0x34/+0x38
// Evidence: retail checks [ecx+0x34]==0 and [ecx+0x38]==0 then sets [0x2c]=-1 and stores args at +0x34/+0x28; no callees; caller FUN_006e71bf
class Rva00366561
{
public:
	char m_lead[0x28];
	int m_28;
	int m_2c;
	unsigned char m_30;
	char m_pad[3];
	int m_34;
	int m_38;
	bool rva00366561(int a, int b);
};
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

bool Rva00366561::rva00366561(int a, int b)
{
	if (m_34 != 0 || m_38 != 0)
		return false;
	m_2c = -1;
	m_34 = a;
	int tb = b;
	m_28 = tb;
	m_30 = 0;
	return true;
}
