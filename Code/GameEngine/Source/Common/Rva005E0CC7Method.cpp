// cl: /MD
//
// ?rva005E0CC7@Rva005E0CC7@@QAEXXZ @0x005E0CC7 36B
// Unlock via rowed byte-chase get 0x0057C22F plus rowed setter 0x005C39AA.
// Calls virtual slot2 on +4 member to get pointer then get then tail to setter.
// Evidence: rowed callees plus caller jmp at 0x005E0D97 and unblocks 0x005E0D94.
class Rva0057C22FByteChaseField
{
public:
	unsigned char get() const;
};

class Rva005C39AA
{
public:
	void rva005C39AA();
};

class Rva005E0CC7Inner
{
public:
	virtual void f0();
	virtual void f1();
	virtual void *f2();
};

class Rva005E0CC7
{
public:
	void rva005E0CC7();
private:
	char m_pad00[4];
	Rva005E0CC7Inner *m_04;
};

void Rva005E0CC7::rva005E0CC7()
{
	void *p = m_04->f2();
	if (p == 0)
		return;
	if (((Rva0057C22FByteChaseField *)p)->get() == 0)
		return;
	return ((Rva005C39AA *)p)->rva005C39AA();
}
