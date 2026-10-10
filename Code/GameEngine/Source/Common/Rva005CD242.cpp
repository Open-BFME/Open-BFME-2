// cl: /O1 /G7 /arch:SSE /MD
// Native 0x005CD242..0x005CD257: full 21 bytes RET 0.
// Five neighboring table slots refer to this shared wrapper. Target bytes
// establish the +0x1C inner pointer and virtual slot 1, forwarded once to
// the owned bool Rva005CCB7B provider on the outer receiver.
// Its rowed 8B bool forwarder and absence of any return-value conversion
// support a bool virtual result. The earlier bank's int callee spelling
// was an existing pin alias; this declaration uses the ledger's bool owner.
// The original class and method names remain unknown; spellings are neutral.
struct Rva005CD242Inner
{
	virtual void f0();
	virtual bool f1();
};

class Rva005CCB7B
{
public:
	void rva005CCB7B(bool v);
};

class Rva005CD242
{
public:
	void rva005CD242();
private:
	char m_pad[0x1C];
	Rva005CD242Inner *m_1C;
};

void Rva005CD242::rva005CD242()
{
	((Rva005CCB7B *)this)->rva005CCB7B(m_1C->f1());
}
