// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva005D0599@Rva005D0643@@UAEXHH@Z, retail 0x005D0599 105B (EH).
// Slot 0 of the vftable 0x00C75524 that the rowed ??1Rva005D0643 (0x005D0643)
// and its constructor 0x005D0AD5 install at +0x0C; that listener base restores
// 0x00C62A20 whose two slots are the empty RET8 0x0050B238. Overriding the
// third base the body runs with this at +0x0C: when its second argument equals
// the owner's (+0x04) word at +0x14 it takes and clears the +0x18 flag; builds a
// 12-byte Rva005CFA43 state through the rowed constructor 0x005D038C with the
// owner and the +0x14 word; and hands it to the owner's +0x1C state slot
// (rowed setter 0x00575674). The first argument is unused.
// Identities unproven; address-derived names.

class Object;

class Rva00575674
{
public:
	void rva00575674(Object *p);
};

struct Rva005D0599Owner
{
	char m_pad00[0x14];
	int m_14;                // +0x14
	char m_pad18[0x1C - 0x18];
	Rva00575674 m_state;     // +0x1C
};

class Rva005CF872
{
public:
	Rva005CF872(void *owner);
	virtual ~Rva005CF872();
	virtual void slot1();
	virtual void slot2();

protected:
	Rva005D0599Owner *m_owner; // +0x04
};

class Rva005CFA43 : public Rva005CF872
{
public:
	Rva005CFA43(void *owner, int opponent, bool change);
	virtual ~Rva005CFA43();

private:
	bool m_flag;
};

class Rva005D0643Base8
{
public:
	virtual void b0();
	virtual void b1();
	virtual void b2();
};

class Rva005D0643BaseC
{
public:
	virtual void rva005D0599(int unused, int id);
	virtual void c1(int, int);
};

class Rva005D0643 : public Rva005CF872, public Rva005D0643Base8, public Rva005D0643BaseC
{
public:
	virtual ~Rva005D0643();
	virtual void rva005D0599(int unused, int id);

private:
	unsigned int m_10;      // +0x10 timeGetTime
	int m_14;               // +0x14
	bool m_flag;            // +0x18
};

void Rva005D0643::rva005D0599(int, int id)
{
	if (id != m_owner->m_14)
		return;
	bool change = m_flag;
	m_flag = false;
	m_owner->m_state.rva00575674((Object *)new Rva005CFA43(m_owner, m_14, change));
}
