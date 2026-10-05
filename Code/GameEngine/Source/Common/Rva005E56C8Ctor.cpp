// cl: /O1 /DNDEBUG /MD
// ??0Rva005E56C8@@QAE@HPAX@Z @ 0x005E56C8 31B
// Evidence: vtable 0x00877D58 at +0; +4 from arg1; +8 from arg2+0x12c; ret 8 two args; sibling 0x005E569A same shape.
extern const void *const g_00C77D58[];

struct Rva005E56C8Arg2
{
	char m_pad[0x12c];
	int m_12c;
};

class Rva005E56C8
{
public:
	Rva005E56C8(int a, void *b);
	virtual ~Rva005E56C8();
private:
	int m_04;
	int m_08;
};

Rva005E56C8::Rva005E56C8(int a, void *b)
	: m_04(a)
	, m_08(((Rva005E56C8Arg2 *)b)->m_12c)
{
}
