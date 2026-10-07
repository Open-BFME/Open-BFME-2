// cl: -O1 -GR- -EHsc-
// ?Run@Rva005B4CC6@@QAEXXZ @0x005B4CC6 90B: IME-gated 27C prep plus setters.
// If m_D is clear, run TheIMEManager slot-0x44 and set it; then with m_4's
// +0x414 vs +0x41C equal, run the +0x27C check (rowed 0x407020) and the
// +0x27C conditioner (rowed 0x407BC3) with 0x27C riding edi; run the rowed
// 0x5B4C3C on this, then poke m_4+0x27C with 0 via rowed 0x5B034A.
// All callees rowed; 0x27C/0x414 family per 0x5B692F/0x5B2725.
class IMEManager
{
public:
	virtual void m00();
	virtual void m04();
	virtual void m08();
	virtual void m0C();
	virtual void m10();
	virtual void m14();
	virtual void m18();
	virtual void m1C();
	virtual void m20();
	virtual void m24();
	virtual void m28();
	virtual void m2C();
	virtual void m30();
	virtual void m34();
	virtual void m38();
	virtual void m3C();
	virtual void m40();
	virtual void m44();
};
extern IMEManager *TheIMEManager;

class Rva00407020
{
public:
	bool rva00407020();
};

class Rva004076EE
{
public:
	void rva00407BC3();
};

class Rva005B4BDB
{
public:
	void rva005B4C3C();
};

class Rva005B034ADwordSlot
{
public:
	void set(int v);
};

struct Rva005B4CC6Outer
{
	char pad[0x27C];
	char sub[4];
	char pad2[0x414 - 0x27C - 4];
	int m_414;
	int m_418;
	int m_41C;
};

struct Rva005B4CC6
{
	char pad[4];
	Rva005B4CC6Outer *m_4;
	void *m_8;
	char flagPad;
	unsigned char m_D;

	void Run();
};

void Rva005B4CC6::Run()
{
	if (m_D == 0) {
		TheIMEManager->m44();
		m_D = 1;
	}
	if (m_4->m_414 == m_4->m_41C) {
		((Rva00407020 *)((char *)m_4 + 0x27C))->rva00407020();
		((Rva004076EE *)((char *)m_4 + 0x27C))->rva00407BC3();
	}
	((Rva005B4BDB *)this)->rva005B4C3C();
	((Rva005B034ADwordSlot *)((char *)m_4 + 0x27C))->set(0);
}
