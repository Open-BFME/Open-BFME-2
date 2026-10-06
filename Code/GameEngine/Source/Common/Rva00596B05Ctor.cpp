// cl: /Ireference/shims/bfme2_ascii /Ob2 /MD /EHsc
// ??0Rva00596B05@@QAE@XZ-style ctor @0x00596BF3 120B calls base ??0Rva0055B0CC then stores vtable 0x00870A98
// Evidence: base call 0x0055B048 plus vptr store plus 4 stack args (ret 0x10) plus AsciiString temp "AIMoneyLender" set to +0x0C
#include "ascii_string.h"

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
protected:
	int m_04;
	int m_08;
	AsciiString m_0C;
	unsigned char m_pad10[0x2C - 0x10];
};

class Rva00596B05 : public Rva0055B0CC
{
public:
	Rva00596B05(void *a1, void *a2, int a3, int a4);
	virtual ~Rva00596B05();
private:
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
};

Rva00596B05::Rva00596B05(void *a1, void *a2, int a3, int a4)
{
	m_2C = *(int *)((char *)a1 + 0x54);
	m_30 = *(int *)((char *)a2 + 0x54);
	m_34 = a3;
	m_38 = a4;
	m_0C = AsciiString("AIMoneyLender");
}
