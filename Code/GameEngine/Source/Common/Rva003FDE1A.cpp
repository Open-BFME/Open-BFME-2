// cl: /O1 /MD
// ?rva003FDE1A@Rva003FDE1AHelper@@QAEXH@Z @0x003FDE1A 54B: iterate [+0x2C,+0x30) forwarding int arg to rowed 0x0056B8F4 then tail virtual slot 0x20 with (byte from 0x003FDD29 row, 1). Evidence: retail push ebx esi edi loop push [esp+0x10] call row add 4 cmp jne then push 1 call 0x003FDD29 push eax call [esi+0x20] ret 4; caller 0x00318BDE passes int via Helper at +0x88.
class Rva0056B8F4
{
public:
	void rva0056B8F4(unsigned int arg);
};

class Rva003FDD29
{
public:
	unsigned char rva003FDD29();
};

class Rva003FDE1AHelper
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void slot8(unsigned char b, int one);
	void rva003FDE1A(int value);
private:
	char m_pad[0x2C - 4];
	Rva0056B8F4 **m_begin; // +0x2C
	Rva0056B8F4 **m_end; // +0x30
};

void Rva003FDE1AHelper::rva003FDE1A(int value)
{
	Rva0056B8F4 **first = m_begin;
	Rva0056B8F4 **last = m_end;
	for (; first != last; ++first)
		(*first)->rva0056B8F4((unsigned int)value);
	slot8(((Rva003FDD29 *)this)->rva003FDD29(), 1);
}
