// cl: /DNDEBUG /MD
// ??0Rva005E569A@@QAE@HPAX@Z @ 0x005E569A 28B
// Evidence: vtable 0x00877D44 at +0; +4 from arg1; +8 from arg2+0x20; ret 8 two args; caller 0x005E580A passes outer arg and this+8; prev InlineDtorDeletingDtors1 same flags.
extern const void *const g_00C77D44[];

struct Rva005E569AArg2
{
	char m_pad[0x20];
	int m_20;
};

class Rva005E569A
{
public:
	Rva005E569A(int a, void *b);
	virtual ~Rva005E569A();
private:
	int m_04;
	int m_08;
};

Rva005E569A::Rva005E569A(int a, void *b)
	: m_04(a)
	, m_08(((Rva005E569AArg2 *)b)->m_20)
{
}
