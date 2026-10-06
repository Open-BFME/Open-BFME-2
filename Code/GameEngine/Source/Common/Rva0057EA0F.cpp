// cl: /DNDEBUG /MD
// ?rva0057EA0F@Rva0057EE5C@@QAEXXZ @0x0057EA0F 158B
// Refresh of the AptMpGameSetup +0xD0 member: reads holder at +0x58 via rowed
// 0x0043DA65, caches [edi+0x14] at +0x5C, copies the 0x28B block at +0x60 to
// +0x8C via rowed 0x002DB9B6 or resets via pinned 0x00559FAC after __cdecl
// compare 0x00559EDC, then vslot1(10 0) and rowed 0x0057E97A before tail jmp
// to rowed AptMpGameRules 0x0057E6C1. Evidence: packet disasm with rowed
// callees and callers in MpGameSetupSlots.cpp; neighbours in Common.
class Rva0043DA65
{
public:
	int rva0043DA65();
};

class Rva002DB9B6
{
public:
	void rva002DB9B6(void *out);
};

int __cdecl Rva00559EDCCompare(int *a, int *b);
void __cdecl Rva00559FAC(int mode, void *dst);

class Rva0057E97A
{
public:
	void rva0057E97A();
};

class AptMpGameRules
{
public:
	void rva0057E6C1();
};

class Rva0057EA0FSource
{
public:
	virtual void pad0() = 0;
	virtual void pad1() = 0;
	virtual void pad2() = 0;
	virtual void pad3() = 0;
	virtual void pad4() = 0;
	virtual void pad5() = 0;
	virtual void pad6() = 0;
	virtual void pad7() = 0;
	virtual void pad8() = 0;
	virtual void pad9() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual bool checkValid() = 0;
	char m_pad04[0x14 - 4];
	int m_id;
	char m_pad18[0x60 - 0x18];
	int m_data[10];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class Rva0057EE5C : public Rva005248D0
{
public:
	virtual void vslot1(int a, int b);
	void rva0057EA0F();
private:
	char m_pad04[0x58 - 4];
	Rva0043DA65 *m_holder;
	int m_5C;
	int m_60;
	char m_pad64[0x8C - 0x64];
	int m_8C[10];
};

void Rva0057EE5C::rva0057EA0F()
{
	int tmp = m_holder->rva0043DA65();
	int old = m_5C;
	Rva0057EA0FSource *p = (Rva0057EA0FSource *)tmp;
	int cur;
	if (p != 0)
		cur = p->m_id;
	else
		cur = -1;
	bool changed = cur != old;
	m_5C = cur;
	if (p != 0) {
		if (p->checkValid()) {
			if (!changed)
				return;
			((Rva002DB9B6 *)p)->rva002DB9B6(m_8C);
		} else {
			if (Rva00559EDCCompare(p->m_data, m_8C) == 0)
				return;
			((Rva002DB9B6 *)p)->rva002DB9B6(m_8C);
		}
	} else {
		if (!changed)
			return;
		Rva00559FAC(m_60, m_8C);
	}
	vslot1(10, 0);
	if (changed)
		((Rva0057E97A *)this)->rva0057E97A();
	((AptMpGameRules *)this)->rva0057E6C1();
}
