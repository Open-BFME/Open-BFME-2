// cl: /DNDEBUG /MD
// ?rva002C08EF@Rva002C08EF@@QAEXXZ @0x002C08EF 137B: window-list drain with slot calls and delete
// Evidence: neighbours GadgetButtonImageHelpers 0x002C0505 and Rva002C0A89 0x002C0A89 same flags; GameWindow next +0x1F8 from Rva002C0A89; callers 0x002C0A74 0x002C1271; callees rowed operator delete 0x0002FD60; virtual slots 49/58/62/65
class GameWindow
{
public:
	virtual void *slot0(int arg);
private:
	unsigned char m_pad[0x1F8 - 4];
public:
	GameWindow *m_next;
};
struct List24Node
{
	int m_unk0;
	GameWindow *m_val;
	List24Node *m_next;
};
class Rva002C08EF
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
	virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
	virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
	virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
	virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
	virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
	virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43();
	virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47();
	virtual void p48();
	virtual void s49(int arg);
	virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53();
	virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57();
	virtual void s58(GameWindow *win, int a, int b, int c);
	virtual void p59(); virtual void p60(); virtual void p61();
	virtual void s62(GameWindow *win);
	virtual void p63(); virtual void p64();
	virtual void s65(GameWindow *win);
	void rva002C08EF();
private:
	unsigned char m_pad04[0x14 - 4];
	GameWindow *m_14;
	GameWindow *m_18;
	GameWindow *m_1C;
	GameWindow *m_20;
	List24Node *m_24;
	GameWindow *m_28;
};
void __cdecl operator delete(void *p);
void Rva002C08EF::rva002C08EF()
{
	GameWindow *cur = m_14;
	m_14 = 0;
	if (!cur)
		return;
	GameWindow *next;
	do {
		next = cur->m_next;
		if (m_1C == cur)
			s62(cur);
		if (m_20 == cur)
			s49(0);
		if (m_24 && cur == m_24->m_val)
			s65(m_24->m_val);
		if (m_18 == cur)
			m_18 = 0;
		if (m_28 == cur)
			m_28 = 0;
		s58(cur, 2, 0, 0);
		void *p = cur->slot0(0);
		::operator delete(p);
		cur = next;
	} while (next);
}
