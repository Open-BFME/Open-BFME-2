// cl: /O1 /MD
// Twelve derived destructors sharing one shape: clear the field at +0xC,
// restore the class vtable, and tail-call the base destructor at 0x1DBAC3.
// Owners are unidentified, so each keeps an address name; the base is
// declared by its pinned destructor spelling. Deleting destructors follow.
// vslot 0x0035DD9C (?Rva0035DD9C@Rva0035DCF9@@UAEXXZ, 33B, slot 3 offset 0xC
// of vtable 0x00816574): hide windows at +0xC and +0x44 via rowed winHide
// 0x00313C64; clears +0x8/+0x9. Evidence: vtable 0x00816574.

class Rva001DBAC3Base { public: virtual ~Rva001DBAC3Base(); };

class GameWindow
{
public:
	int winHide(bool hide);
};

class Rva0035D47B : public Rva001DBAC3Base { public: virtual ~Rva0035D47B(); int m_pad[2]; int m_field; };
Rva0035D47B::~Rva0035D47B() { m_field = 0; }
void famgenDelete(Rva0035D47B *p) { delete p; }

class Rva0035D53C : public Rva001DBAC3Base { public: virtual ~Rva0035D53C(); int m_pad[2]; int m_field; };
Rva0035D53C::~Rva0035D53C() { m_field = 0; }
void famgenDelete(Rva0035D53C *p) { delete p; }

class Rva0035DA01 : public Rva001DBAC3Base { public: virtual ~Rva0035DA01(); int m_pad[2]; int m_field; };
Rva0035DA01::~Rva0035DA01() { m_field = 0; }
void famgenDelete(Rva0035DA01 *p) { delete p; }

class Rva0035DCF9 : public Rva001DBAC3Base
{
public:
	virtual ~Rva0035DCF9();
	virtual void slot1();
	virtual void slot2();
	virtual void Rva0035DD9C();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
private:
	char m_pad4[4];
	bool m_8;
	bool m_9;
	char m_padA[2];
	GameWindow *m_C;
	char m_pad10[0x44 - 0x10];
	GameWindow *m_44;
};
Rva0035DCF9::~Rva0035DCF9() { m_C = 0; }
void famgenDelete(Rva0035DCF9 *p) { delete p; }

void Rva0035DCF9::Rva0035DD9C()
{
	GameWindow *w1 = m_C;
	m_8 = false;
	m_9 = false;
	w1->winHide(true);
	m_44->winHide(true);
}

class Rva0035E00F : public Rva001DBAC3Base { public: virtual ~Rva0035E00F(); int m_pad[2]; int m_field; };
Rva0035E00F::~Rva0035E00F() { m_field = 0; }
void famgenDelete(Rva0035E00F *p) { delete p; }

class Rva0035E2CF : public Rva001DBAC3Base { public: virtual ~Rva0035E2CF(); int m_pad[2]; int m_field; };
Rva0035E2CF::~Rva0035E2CF() { m_field = 0; }
void famgenDelete(Rva0035E2CF *p) { delete p; }

class Rva0035E378 : public Rva001DBAC3Base { public: virtual ~Rva0035E378(); int m_pad[2]; int m_field; };
Rva0035E378::~Rva0035E378() { m_field = 0; }
void famgenDelete(Rva0035E378 *p) { delete p; }

class Rva0035ED92 : public Rva001DBAC3Base { public: virtual ~Rva0035ED92(); int m_pad[2]; int m_field; };
Rva0035ED92::~Rva0035ED92() { m_field = 0; }
void famgenDelete(Rva0035ED92 *p) { delete p; }

class Rva0035F1D0 : public Rva001DBAC3Base { public: virtual ~Rva0035F1D0(); int m_pad[2]; int m_field; };
Rva0035F1D0::~Rva0035F1D0() { m_field = 0; }
void famgenDelete(Rva0035F1D0 *p) { delete p; }

class Rva0035F42E : public Rva001DBAC3Base { public: virtual ~Rva0035F42E(); int m_pad[2]; int m_field; };
Rva0035F42E::~Rva0035F42E() { m_field = 0; }
void famgenDelete(Rva0035F42E *p) { delete p; }

class Rva0035FA2A : public Rva001DBAC3Base { public: virtual ~Rva0035FA2A(); int m_pad[2]; int m_field; };
Rva0035FA2A::~Rva0035FA2A() { m_field = 0; }
void famgenDelete(Rva0035FA2A *p) { delete p; }

class Rva0035FF76 : public Rva001DBAC3Base { public: virtual ~Rva0035FF76(); int m_pad[2]; int m_field; };
Rva0035FF76::~Rva0035FF76() { m_field = 0; }
void famgenDelete(Rva0035FF76 *p) { delete p; }

