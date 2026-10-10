// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ??0Rva005CDA3D@@QAE@PAXHHHHH@Z, retail 0x005CD9FF, 62 bytes, ret 0x18.
// Derived constructor over the rowed Rva005E663C base (0x005E663C): builds a stack holder
// whose vtable is 0x00875014 (class Rva005CD9AE, nine slots) and which stores this, passes it
// as the last integer argument with its own six arguments to the base, then clears the word at +0x0C and installs its own
// vtable 0x00875038 (class Rva005CDA3D, nine slots). No unwinding state is needed.
// Evidence: target bytes, the two vtable names in the data ledger and the rowed base
// constructor; class and field names beyond those vtable owners are neutral.

class Rva005CDA3D;

class Rva005CD9AE
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
	virtual void v8();
	Rva005CD9AE(Rva005CDA3D *owner) : m_owner(owner) {}
	Rva005CDA3D *m_owner;
};

class Rva005E67FE
{
public:
	void *m_field04;
	Rva005E67FE(void *held);
	virtual ~Rva005E67FE();
};

class Rva005E62F1;

class Rva005E663C : public Rva005E67FE
{
public:
	Rva005E62F1 *m08;
	virtual ~Rva005E663C();
	Rva005E663C(void *a0, int a1, int a2, int a3, int a4, int a5, int a6);
};

class Rva005CDA3D : public Rva005E663C
{
public:
	Rva005CDA3D(void *a0, int a1, int a2, int a3, int a4, int a5);
	virtual ~Rva005CDA3D();
private:
	int m_0C;
};

Rva005CDA3D::Rva005CDA3D(void *a0, int a1, int a2, int a3, int a4, int a5)
	: Rva005E663C(a0, a1, a2, a3, a4, a5, (int)&Rva005CD9AE(this))
{
	m_0C = 0;
}
