// cl: /O1 /G7 /arch:SSE /MD
// ?rva005CC342@Rva005CC342@@QAEXXZ retail 0x005CC342 58B
// Dispatch via iface at +0x14: slot0 gate then slot5 chooses tail slot8 else slot6 gate to tail slot7.
// Evidence: rowed callee 0x005E0D94 on same this plus virtual slots 0 5 6 7 8.
class Rva005E0D94
{
public:
	void rva005E0D94();
};

class Iface005CC342
{
public:
	virtual bool f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual bool f5();
	virtual bool f6();
	virtual void f7();
	virtual void f8();
};

class Rva005CC342
{
public:
	void rva005CC342();
private:
	char m_pad00[8];
	void *m_08;
	char m_pad0C[8];
	Iface005CC342 *m_14;
};

void Rva005CC342::rva005CC342()
{
	((Rva005E0D94 *)this)->rva005E0D94();
	if (!m_14->f0())
		return;
	if (m_14->f5())
		return m_14->f8();
	if (!m_14->f6())
		return;
	return m_14->f7();
}

class Rva005E1160Flag {
public:
    void rva005E1160(bool flag);
};
class Rva005CC30B {
public:
    void rva005CC30B();
    char pad[0x1C];
    Iface005CC342 *m_iface1C;
    __forceinline bool check() { return m_iface1C->f0() && (m_iface1C->f5() || m_iface1C->f6()) ? '\1' : '\0'; }
};
// Native55B5CC30B..5CC342 forwards slot0 && (slot5 || slot6) verdict to
// established receiver+8 setter. The receiver and interface identity unknown.
void Rva005CC30B::rva005CC30B()
{
    ((Rva005E1160Flag *)((char *)this + 8))->rva005E1160(check());
}
