// cl: /MD
// Range-27 xfer feed sequence.
// ?Rva0051FFF5@Holder0051FFF5@@QAEXPAVXfer0051FFF5@@@Z @0x0051FFF5 125B
// Thiscall feeds holder fields to an Xfer-like object's virtual slots
// 0x68/0x7C/0x6C/0x7C (TU-local vtable view, slots positional), preserves
// m_10 across a temp, then runs five cdecl out-param helpers: pinned
// 0x0039C4F7 and 0x004EE9E9 plus the rowed 0x0040E269 Xfer vector helper
// three times (local cdecl spellings via pins). The trailing out-param
// reuses dead this with an in-place +0x44 adjust.
class Xfer0051FFF5
{
public:
	virtual ~Xfer0051FFF5();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26(void *out);
	virtual void slot27(void *out);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31(void *out);
};

void Rva0039C4F7(Xfer0051FFF5 *x, void *out);
void Rva004EE9E9(Xfer0051FFF5 *x, void *out);
void Rva0040E269(Xfer0051FFF5 *x, void *out);

struct Out120051FFF5
{
	char m_bytes[12];
};

struct Holder0051FFF5
{
	char m_pad[4];
	int m_4;
	int m_8;
	int m_C;
	int m_10;
	Out120051FFF5 m_outs[5];
	void Rva0051FFF5(Xfer0051FFF5 *x);
};

void Holder0051FFF5::Rva0051FFF5(Xfer0051FFF5 *x)
{
	x->slot26(&m_4);
	x->slot31(&m_8);
	x->slot27(&m_C);
	int tmp = m_10;
	x->slot31(&tmp);
	m_10 = tmp;
	Rva0039C4F7(x, &m_outs[0]);
	Rva004EE9E9(x, &m_outs[1]);
	Rva0040E269(x, &m_outs[2]);
	Rva0040E269(x, &m_outs[3]);
	char *tail = (char *)this + 0x44;
	Rva0040E269(x, tail);
}
