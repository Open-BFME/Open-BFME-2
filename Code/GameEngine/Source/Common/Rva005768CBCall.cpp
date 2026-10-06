// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva005768CB@Rva005768CBCall@@QAEXPAX@Z @0x005768CB 123B evidence: caller 0x00576ACB in MemberBaseDtorsB01.cpp calls this-0xC; calls rowed ctor 0x0057664C new 0x18 flag from +0x14 and 0x1e pin AddItem 0x005CD0C2 row Release 0x0007DEEF
void *operator new(unsigned int);
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct BfmeRefPtr
{
	TargetRef00217D4C *m_ptr;
	BfmeRefPtr(TargetRef00217D4C *p) : m_ptr(p)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	~BfmeRefPtr()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva0057682F : public TargetRef00217D4C
{
public:
	Rva0057682F(void *a, void *b, int c);
	char m_pad[16];
};
class Rva005CD1A9
{
public:
	void AddItem(struct BfmeRefPtr *p);
};
class Rva005768CBCall
{
public:
	void rva005768CB(void *lookup);
private:
	char m_pad[4];
	Rva005CD1A9 m_04;
};
void Rva005768CBCall::rva005768CB(void *lookup)
{
	int flag = ((*(int *)((char *)lookup + 0x14) & 0x1e) != 0);
	Rva0057682F *p = new Rva0057682F(this, lookup, flag);
	BfmeRefPtr ref(p);
	m_04.AddItem(&ref);
}
