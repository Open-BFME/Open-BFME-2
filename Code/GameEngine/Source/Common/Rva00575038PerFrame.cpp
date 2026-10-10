// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva00575038@Rva00575038@@QAEXXZ @0x00575038 143B: the per-frame method
// the banked 0x00574EE9 attempts refer to. Runs three self updates
// (0x574EA2, 0x5748F2, 0x574EE9), member updates at +0x48 (0x5CB852),
// +0x28 (0x5C9AB4) and +0x5C (0x5CC2DC), the fastcall refresh 0x5745D8 on
// the +0x20 object, then, when that object yields a listener and
// TheLivingWorldLogic exists, tells the listener the next turn (slot 1) and
// either the logic's 0x2B3DD0 value (slot 5) or nothing (slot 6) depending
// on 0x2B2BAA. Clears the byte at +0x58 last. Retail rereads the global
// before every use and fetches the 0x2B3DD0 value before loading the
// listener's vtable, hence the named local. Receiver and member classes keep their existing
// address-derived names; offsets are from the retail bytes.

class Rva00574EA2 { public: void rva00574EA2(); void rva00574EE9(); };
class Rva005748F2 { public: void rva005748F2(); };
class Rva005CB852 { public: void rva005CB852(); };
class Rva005C9B76 { public: void rva005C9AB4(); };
class Rva005CC2C5 { public: void rva005CC2DC(); };
class Rva0042D71A { public: int get() const; };
class Rva002B4650 { public: bool rva002B2BAA(); int rva002B3DD0(); };
void __fastcall Rva005745D8Get(void *object);

class LivingWorldLogic
{
public:
	char pad0[0xfc];
	int turn;
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva00575038Listener
{
public:
	virtual void slot0();
	virtual void setTurn(int turn);
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void setValue(int value);
	virtual void clearValue();
};

class Rva00575038
{
public:
	void rva00575038();

private:
	char m_pad00[0x20];
	Rva0042D71A *m_source;      // +0x20
	char m_pad24[0x04];
	char m_member28[0x20];      // +0x28
	char m_member48[0x10];      // +0x48
	bool m_flag58;              // +0x58
	char m_pad59[0x03];
	char m_member5C[0x04];      // +0x5C
};

void Rva00575038::rva00575038()
{
	reinterpret_cast<Rva00574EA2 *>(this)->rva00574EA2();
	reinterpret_cast<Rva005748F2 *>(this)->rva005748F2();
	reinterpret_cast<Rva00574EA2 *>(this)->rva00574EE9();
	reinterpret_cast<Rva005CB852 *>(m_member48)->rva005CB852();
	reinterpret_cast<Rva005C9B76 *>(m_member28)->rva005C9AB4();
	reinterpret_cast<Rva005CC2C5 *>(m_member5C)->rva005CC2DC();
	Rva005745D8Get(m_source);
	Rva00575038Listener *listener = reinterpret_cast<Rva00575038Listener *>(m_source->get());
	if (listener && TheLivingWorldLogic)
	{
		listener->setTurn(TheLivingWorldLogic->turn + 1);
		if (reinterpret_cast<Rva002B4650 *>(TheLivingWorldLogic)->rva002B2BAA())
		{
			int value = reinterpret_cast<Rva002B4650 *>(TheLivingWorldLogic)->rva002B3DD0();
			listener->setValue(value);
		}
		else
			listener->clearValue();
	}
	m_flag58 = false;
}
