// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva005D0C87@@QAE@PAVRva005D0D85@@HHH@Z, retail 0x005D0C87..0x005D0D2D
// (166 bytes, EH, RET 16): the 0x20-byte implementation the rowed
// Rva005D0D85 constructor allocates (its destructor is 0x005D07E1). Two bases:
// an interface at +0x00 (vtable 0x00C75588 here, 0x00C75284 its own) and a
// listener at +0x04 (vtable 0x00C7557C here, 0x00C62A14 its own). The owner
// and the three arguments are kept at +0x08..+0x14, +0x18 is cleared and the
// +0x1C holder takes a new 8-byte callback (vtable 0x00C752A0) on this. The
// +0x10 object is then told the +0x14 object's +0x24 value (0x005CB84A, its
// member forwarder), this joins the +0x14 object's listener list at +0x08 and
// the listener base joins TheLivingWorldLogic's list at +0x2C (rowed append
// 0x005A0B4C). No WorldBuilder name is matched.

class Rva005D0D85;

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// ?rva005CB84A@Rva005CB84A@@QAEXH@Z, retail 0x005CB84A (8 bytes): a member
// forwarder into its +0x04 implementation's 0x005CB723 (not yet rowed;
// pinned), like its neighbour 0x005CB852.
class Rva005CB723
{
public:
	void rva005CB723(int value);
};

class Rva005CB84A
{
public:
	__declspec(noinline) void rva005CB84A(int value);
private:
	int m_00;
	Rva005CB723 *m_impl04;
};

void Rva005CB84A::rva005CB84A(int value)
{
	m_impl04->rva005CB723(value);
}

struct Rva005D0C87Source
{
	unsigned char m_pad00[0x08];
	Rva005A0B4CList m_listeners08;			// +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	int m_24;								// +0x24
};

class __declspec(novtable) Rva005D0C87Interface
{
public:
	virtual ~Rva005D0C87Interface();
};

class Rva005D06CBB2
{
public:
	~Rva005D06CBB2() {}
	virtual void s0();
	virtual void s1();
	virtual void s2();
};

class Rva005D0C87;

// The callback's owner pointer lives in a plain base, so it is stored before
// the callback's own vtable, as retail does.
struct Rva005D0C87CallbackBase
{
	Rva005D0C87CallbackBase(Rva005D0C87 *owner) : m_owner(owner) {}
	Rva005D0C87 *m_owner;
};

class Rva005D0C87Callback : public Rva005D0C87CallbackBase
{
public:
	Rva005D0C87Callback(Rva005D0C87 *owner) : Rva005D0C87CallbackBase(owner) {}
	virtual void c0();
	virtual void c1();
	virtual void c2();
};

class Rva005D0C87CallbackHolder
{
public:
	Rva005D0C87CallbackHolder(Rva005D0C87Callback *callback) : m_callback(callback) {}
	~Rva005D0C87CallbackHolder();
private:
	Rva005D0C87Callback *m_callback;
};

class Rva005D0C87 : public Rva005D0C87Interface, public Rva005D06CBB2
{
public:
	Rva005D0C87(Rva005D0D85 *owner, int a, int b, int c);
	virtual ~Rva005D0C87();
	virtual void s0();
	virtual void s2();

private:
	Rva005D0D85 *m_owner08;					// +0x08
	int m_a0C;								// +0x0C
	Rva005CB84A *m_b10;						// +0x10
	Rva005D0C87Source *m_c14;				// +0x14
	void *m_18;								// +0x18
	Rva005D0C87CallbackHolder m_callback1C;	// +0x1C
};

Rva005D0C87::Rva005D0C87(Rva005D0D85 *owner, int a, int b, int c)
	: m_owner08(owner),
	  m_a0C(a),
	  m_b10((Rva005CB84A *)b),
	  m_c14((Rva005D0C87Source *)c),
	  m_18(0),
	  m_callback1C(new Rva005D0C87Callback(this))
{
	m_b10->rva005CB84A(m_c14->m_24);
	m_c14->m_listeners08.append((Rva002BA8F1Listener *)this);
	((Rva005A0B4CList *)((char *)TheLivingWorldLogic + 0x2C))->append((Rva002BA8F1Listener *)static_cast<Rva005D06CBB2 *>(this));
}
