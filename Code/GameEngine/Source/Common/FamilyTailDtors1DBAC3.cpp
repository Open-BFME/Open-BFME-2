// cl: /O1 /MD
// Twelve derived destructors sharing one shape: clear the field at +0xC,
// restore the class vtable, and tail-call the base destructor at 0x1DBAC3.
// Owners are unidentified, so each keeps an address name; the base is
// declared by its pinned destructor spelling. Deleting destructors follow.
// vslot 0x0035DD9C (?Rva0035DD9C@Rva0035DCF9@@UAEXXZ, 33B, slot 3 offset 0xC
// of vtable 0x00816574): hide windows at +0xC and +0x44 via rowed winHide
// 0x00313C64; clears +0x8/+0x9. Evidence: vtable 0x00816574.
// vslot 0x0035DD08 (?Rva0035DD08@Rva0035DCF9@@UAEXH@Z, 148B, slot 2 offset 0x8
// of vtable 0x00816574): range-select hide via rowed winHide 0x00313C64;
// sets +0x28 to -1 then to index in middle range. Evidence: vtable 0x00816574.
// vslot 0x0035E0F7 (?Rva0035E0F7@Rva0035E00F@@UAEXH@Z, 142B, slot 2 offset 0x8
// of vtable 0x00816594): same range-select shape with second window at +0x4C
// (not +0x44); first equality branch hides only m_44. Evidence: vtable
// 0x00816594 slot 2 plus rowed winHide 0x00313C64.

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
	virtual void Rva0035DD08(int index);
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
	int m_10;
	int m_14;
	char m_pad18[0x28 - 0x18];
	int m_28;
	char m_pad2C[0x44 - 0x2C];
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

void Rva0035DCF9::Rva0035DD08(int index)
{
	m_28 = -1;
	if (index < m_10)
		return;
	if (index > m_14)
		return;
	if (index == m_10) {
		if (!m_9 && m_C != 0 && m_44 != 0) {
			m_C->winHide(false);
			m_44->winHide(true);
			m_8 = true;
		}
	} else if (index == m_14) {
		if (m_9 && m_C != 0 && m_44 != 0) {
			m_C->winHide(true);
			m_44->winHide(false);
			m_8 = true;
		}
	}
	if (index <= m_10)
		return;
	if (index >= m_14)
		return;
	if (m_C != 0)
		m_C->winHide(true);
	if (m_44 != 0)
		m_44->winHide(true);
	m_28 = index;
}

class Rva0035E00F : public Rva001DBAC3Base
{
public:
	virtual ~Rva0035E00F();
	virtual void slot1();
	virtual void Rva0035E0F7(int index);
	virtual void slot3();
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
	int m_10;
	int m_14;
	char m_pad18[0x28 - 0x18];
	int m_28;
	char m_pad2C[0x4C - 0x2C];
	GameWindow *m_44;
};
Rva0035E00F::~Rva0035E00F() { m_C = 0; }
void famgenDelete(Rva0035E00F *p) { delete p; }

void Rva0035E00F::Rva0035E0F7(int index)
{
	m_28 = -1;
	if (index < m_10)
		return;
	if (index > m_14)
		return;
	if (index == m_10) {
		if (!m_9 && m_C != 0 && m_44 != 0) {
			m_44->winHide(true);
			m_8 = true;
		}
	} else if (index == m_14) {
		if (m_9 && m_C != 0 && m_44 != 0) {
			m_C->winHide(true);
			m_44->winHide(false);
			m_8 = true;
		}
	}
	if (index <= m_10)
		return;
	if (index >= m_14)
		return;
	if (m_C != 0)
		m_C->winHide(true);
	if (m_44 != 0)
		m_44->winHide(true);
	m_28 = index;
}

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

