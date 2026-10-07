// cl: /O1 /arch:SSE /G7 /MD
// ?rva002BE7FA@Rva002BE7FA@@QAEXII@Z @0x002BE7FA 57B.
// Setter for the dword at +0x14 with a 0/1/3 switch notifying via vtable
// slots 0xA0 (case 1) and 0xA4 (cases 0 with arg and 3 with 0); early-out
// when the new value equals +0x14. VTABLE slot 19 of the table at
// 0x007FE508. Caller at 0x0009C790 passes the two stack args through.
// Prev 0x002BE7DB Rva002BE7DBCopy, next 0x002BE833 Rva002BE833Xfer.
typedef unsigned int UnsignedInt;

class Rva002BE7FA
{
public:
	void rva002BE7FA(UnsignedInt newVal, UnsignedInt arg);
	virtual void _00();
	virtual void _01();
	virtual void _02();
	virtual void _03();
	virtual void _04();
	virtual void _05();
	virtual void _06();
	virtual void _07();
	virtual void _08();
	virtual void _09();
	virtual void _10();
	virtual void _11();
	virtual void _12();
	virtual void _13();
	virtual void _14();
	virtual void _15();
	virtual void _16();
	virtual void _17();
	virtual void _18();
	virtual void _19();
	virtual void _20();
	virtual void _21();
	virtual void _22();
	virtual void _23();
	virtual void _24();
	virtual void _25();
	virtual void _26();
	virtual void _27();
	virtual void _28();
	virtual void _29();
	virtual void _30();
	virtual void _31();
	virtual void _32();
	virtual void _33();
	virtual void _34();
	virtual void _35();
	virtual void _36();
	virtual void _37();
	virtual void _38();
	virtual void _39();
	virtual void v40(UnsignedInt arg);
	virtual void v41(UnsignedInt arg);
private:
	unsigned char m_pad[0x10];
	UnsignedInt m_14;
};

void Rva002BE7FA::rva002BE7FA(UnsignedInt newVal, UnsignedInt arg)
{
	if (newVal == m_14)
		return;
	m_14 = newVal;
	switch (newVal) {
	case 0:
		v41(arg);
		break;
	case 1:
		v40(arg);
		break;
	case 3:
		v41(0);
		break;
	default:
		break;
	}
}
