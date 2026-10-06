// cl: /MD
// ??0Rva0036CB94@@QAE@HHHH_N@Z @0x0036CB94 49B
// Stack-struct ctor: +0=arg1, +4/+8/+0xC zero, +0x10/+0x14/+0x18 args,
// +0x1C byte arg. Callers 0x00379788 and 0x0037FCD8 build it on the stack
// and pass it to 0x00372571. Owner unproven so honest address names used.
class Rva0036CB94
{
public:
	Rva0036CB94(int a1, int a2, int a3, int a4, bool a5);
	int m_00;
	unsigned char m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	bool m_1c;
};

Rva0036CB94::Rva0036CB94(int a1, int a2, int a3, int a4, bool a5)
{
	m_00 = a1;
	m_04 = 0;
	m_08 = 0;
	m_0c = 0;
	m_10 = a2;
	m_14 = a3;
	m_18 = a4;
	m_1c = a5;
}
