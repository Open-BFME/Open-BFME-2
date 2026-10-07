// cl: /O1 /MD
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0032B7A7@SidesList@@QAEXPAV1@@Z retail 0x0032B7A7 60 bytes.
// SidesList single-teamrec swap: rowed TeamsInfoRec::swap at 0x0032B651 for
// the record at +0xF44, plus rowed SidesListNotifier posts at 0x0032B540
// for this (+0x10) and other with callback at 0x005CB279.
// Evidence: +0xF44 teamrec via rowed emptyTeams at 0x0032D05C and pinned
// clear at 0x0032C9C6; +0x10 notifier via SidesList layout; caller at
// 0x0032F117 in load at 0x0032F0AA passing a temp SidesList.

// Retail callbacks are MSVC virtual member-pointer thunks for slots +0x1C
// and +0x20.  This describes the callback ABI; the listener identity is unknown.
class SidesListSwapListener
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
};
union SidesListSwapCallback
{
    void (SidesListSwapListener::*member)();
    void (*code)();
};

class TeamsInfoRec
{
public:
	void swap(TeamsInfoRec *other);
};

class SidesListNotifier
{
public:
	void post(void (*callback)(), void *owner, int other);
};

class SidesList
{
public:
	void rva0032B7A7(SidesList *other);
	void rva0032B833(SidesList *other);

private:
	char m_pad00[0x10];
	SidesListNotifier m_notifier;
	char m_pad[0xF44 - 0x11];
	TeamsInfoRec m_teamrec;
	char m_padF45[0xF7C - 0xF44 - sizeof(TeamsInfoRec)];
	unsigned char m_flagF7C;
};

void SidesList::rva0032B7A7(SidesList *other)
{
	SidesListSwapCallback callback;
	callback.member = &SidesListSwapListener::slot1C;
	m_teamrec.swap(&other->m_teamrec);
	m_notifier.post(callback.code, this, (int)other);
	other->m_notifier.post(callback.code, other, (int)this);
}

inline void sidesSwapByte(unsigned char &a, unsigned char &b)
{
    unsigned char temp = a;
    a = b;
    b = temp;
}

// Retail 0x0032B833..0x0032B871: exchange the byte at +0xF7C, then notify
// both owners through their +0x10 lists using the slot +0x20 vcall thunk.
// The field meaning and original method name are not established.
void SidesList::rva0032B833(SidesList *other)
{
    sidesSwapByte(m_flagF7C, other->m_flagF7C);
    SidesListSwapCallback callback;
    callback.member = &SidesListSwapListener::slot20;
    m_notifier.post(callback.code, this, (int)other);
    other->m_notifier.post(callback.code, other, (int)this);
}
