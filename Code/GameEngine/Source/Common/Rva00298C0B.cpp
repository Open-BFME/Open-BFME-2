// cl: /DNDEBUG /MD
// ?rva00298C0B@Rva00298C0B@@QAEXPAVTeam@@@Z 107B @0x00298C0B: team scan via 250 plus recurse plus aiIdle.
// Evidence: retail this plus0x250 virtual slot 0x118 plus 0x250 null plus recurse plus rva00298AE4 pin plus aiIdle row. Callers at 0x003A2D3A 0x003A2DA2 plus self.
class Team;
class Object
{
public:
	void rva00298AE4(Team *t);
};

enum CommandSourceType
{
	CST_0 = 0,
	CST_1 = 1,
	CST_2 = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType src);
};

struct Virt118
{
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s0A();
	virtual void s0B();
	virtual void s0C();
	virtual void s0D();
	virtual void s0E();
	virtual void s0F();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s1A();
	virtual void s1B();
	virtual void s1C();
	virtual void s1D();
	virtual void s1E();
	virtual void s1F();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s2A();
	virtual void s2B();
	virtual void s2C();
	virtual void s2D();
	virtual void s2E();
	virtual void s2F();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s3A();
	virtual void s3B();
	virtual void s3C();
	virtual void s3D();
	virtual void s3E();
	virtual void s3F();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void check(void *a);
};

class Rva00298C0B
{
public:
	void rva00298C0B(Team *t);
private:
	char m_pad250[0x250];
	void *m_250;
};

void Rva00298C0B::rva00298C0B(Team *t)
{
	void *p = m_250;
	if (p == 0)
		return;
	void *iter[2];
	((Virt118 *)p)->check(iter);
	void *head = *(void **)iter[1];
	void *cur = *(void **)head;
	if (cur == head)
		return;
	do
	{
		Object *o = *(Object **)((char *)cur + 8);
		if (*(void **)((char *)o + 0x250) != 0)
			((Rva00298C0B *)o)->rva00298C0B(t);
		((Object *)o)->rva00298AE4(t);
		void *m = *(void **)((char *)o + 0x258);
		if (m != 0)
			((AICommandInterface *)((char *)m + 0x20))->aiIdle(CST_2);
		cur = *(void **)cur;
	} while (cur != *(void **)iter[1]);
}
