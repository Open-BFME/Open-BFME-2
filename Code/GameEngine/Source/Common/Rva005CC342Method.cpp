// cl: /MD
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
