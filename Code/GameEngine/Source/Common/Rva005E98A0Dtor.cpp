// cl: /O1 /MD /EHsc
// ??1Rva005E98A0@@QAE@XZ retail 0x005E98A0 65B
// Pointee dtor run by the rowed owning-pointer reset 0x005E9E27. Body (EH
// state 0): reset the member at +0x18 through the rowed
// ?rva005E9705@Rva005E971F 0x005E9705, unload the content at +4 through the
// rowed ?rva0057C2CC@Rva0057C2CC 0x0057C2CC; then the +0x18 member's inline
// dtor runs the same reset. Supersedes Peppy's 0.85 stash
// reverse/attempts/0x005e98a0.cpp (it was a dtor, not a plain method).

struct Rva005E971F
{
	~Rva005E971F() { rva005E9705(); }
	void rva005E9705();
};

struct Rva0057C2CC
{
	void rva0057C2CC();
};

class Rva005E98A0
{
public:
	~Rva005E98A0();

private:
	int m_00;
	Rva0057C2CC *m_content; // +0x04
	unsigned char m_pad08[0x18 - 8];
	Rva005E971F m_18; // +0x18
};

Rva005E98A0::~Rva005E98A0()
{
	m_18.rva005E9705();
	m_content->rva0057C2CC();
}
