// cl: /MD /Oy- /Os
// ?rva00538CB4@Rva00538CB4@@QAEXPAURva00538CB4Input@@@Z @0x00538CB4 59B
// Banked attempt reverse/attempts/0x00538cb4.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// ?rva00538CB4@Rva00538CB4@@QAEXPAURva00538CB4Input@@@Z, retail 0x00538CB4, 59 bytes.
// Target-evidence ABI view: calls input vtable slots +0x28 and +0x50, then the
// rowed 0x003EFE82 getter with the input and this+0x0C. The interface identity
// and the meanings of the output fields remain unknown.

struct Rva00538CB4Input
{
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28(bool *flags) = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50(void *out) = 0;
};

struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(Rva003EFE82Obj *object, void *out);

class Rva00538CB4
{
public:
	void rva00538CB4(Rva00538CB4Input *input);

private:
	char m_pad0[4];
	int m_4;
	char m_pad8[4];
	int m_c;
};

void Rva00538CB4::rva00538CB4(Rva00538CB4Input *input)
{
	bool flags[2];
	flags[0] = 1;
	flags[1] = 1;
	input->slot28(flags);
	input->slot50(&m_4);
	Rva003EFE82Get((Rva003EFE82Obj *)input, &m_c);
}
