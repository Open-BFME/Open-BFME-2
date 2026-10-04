// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ??0Rva0004708A@@QAE@XZ @0x0004708A 22B leaf ctor zeroing two ints plus member Rva0042526Member at +8; callee row ??0Rva0042526Member@@QAE@XZ; caller 0x0004B36B
class Rva0042526Member
{
public:
	Rva0042526Member();
};

class Rva0004708A
{
public:
	Rva0004708A();
private:
	int m_00;
	int m_04;
	Rva0042526Member m_08;
};

Rva0004708A::Rva0004708A() : m_00(0), m_04(0)
{
}
