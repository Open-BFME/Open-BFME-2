// cl: /MD
//
// ??0Rva005CD7BD@@QAE@PAXHH@Z retail 0x005CD7BD 29B init 3 dwords plus 0.
// Evidence: 3 callers lea +0x18/+0x28 push 3; ret 0xC; stores +0/+4/+8; byte 0 +0xC.
class Rva005CD7BD
{
public:
	Rva005CD7BD(void *a, int b, int c);
private:
	void *m_0;
	int m_4;
	int m_8;
	bool m_C;
};

Rva005CD7BD::Rva005CD7BD(void *a, int b, int c)
	: m_0(a)
	, m_4(b)
	, m_8(c)
	, m_C(false)
{
}
