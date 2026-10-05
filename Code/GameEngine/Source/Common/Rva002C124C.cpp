// cl: /O1 /DNDEBUG /MD
// ?rva002C124C@Rva002C124C@@UAEHXZ @0x002C124C 46B.
// Honest-address wall walk over GameWindow list at +0xC via m_next +0x1F8,
// virtual slot 0x8C plus rowed 0x002C08EF, returns 0. Evidence: vtable slot
// 36 of 0x007C7C90 (GameWindowManager family), caller dtor 0x002C5398,
// callees rowed 0x002C08EF, prev/next flags.
class GameWindow
{
public:
	unsigned char m_pad0[0x08];
	unsigned int m_status;
	unsigned char m_padC[0x1EC];
	GameWindow *m_next;
};

class Rva002C08EF
{
public:
	void rva002C08EF();
};

class Rva002C124C
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
	virtual void p32(); virtual void p33(); virtual void p34();
	virtual void s35(GameWindow *win);
	virtual int rva002C124C();
private:
	char m_pad04[8];
	GameWindow *m_0C;
};

// ?p00@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p00() {}
// ?p01@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p01() {}
// ?p02@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p02() {}
// ?p03@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p03() {}
// ?p04@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p04() {}
// ?p05@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p05() {}
// ?p06@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p06() {}
// ?p07@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p07() {}
// ?p08@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p08() {}
// ?p09@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p09() {}
// ?p10@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p10() {}
// ?p11@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p11() {}
// ?p12@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p12() {}
// ?p13@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p13() {}
// ?p14@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p14() {}
// ?p15@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p15() {}
// ?p16@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p16() {}
// ?p17@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p17() {}
// ?p18@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p18() {}
// ?p19@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p19() {}
// ?p20@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p20() {}
// ?p21@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p21() {}
// ?p22@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p22() {}
// ?p23@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p23() {}
// ?p24@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p24() {}
// ?p25@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p25() {}
// ?p26@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p26() {}
// ?p27@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p27() {}
// ?p28@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p28() {}
// ?p29@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p29() {}
// ?p30@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p30() {}
// ?p31@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p31() {}
// ?p32@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p32() {}
// ?p33@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p33() {}
// ?p34@Rva002C124C@@UAEXXZ present-unmatched
void Rva002C124C::p34() {}
// ?s35@Rva002C124C@@UAEXPAVGameWindow@@@Z present-unmatched
void Rva002C124C::s35(GameWindow *win) { (void)win; }

int Rva002C124C::rva002C124C()
{
	GameWindow *win = m_0C;
	if (win)
	{
		GameWindow *cur = win;
		do
		{
			GameWindow *next = cur->m_next;
			s35(cur);
			cur = next;
		} while (cur);
	}
	((Rva002C08EF *)this)->rva002C08EF();
	return 0;
}
