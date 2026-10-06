// cl: /DNDEBUG /MD /EHsc
// ??0Rva002E73D4@@QAE@HHH@Z @0x002E73D4 39B ctor with three ints at +0/+4/+8 plus zeroed tail; caller at 0x002F3297
class Rva002E73D4
{
public:
	Rva002E73D4(int a, int b, int c);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	bool m_10;
	int m_14;
	int m_18;
};

Rva002E73D4::Rva002E73D4(int a, int b, int c)
	: m_00(a)
	, m_04(b)
	, m_08(c)
	, m_0C(0)
	, m_10(false)
	, m_14(0)
	, m_18(0)
{
}
