// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00575AE1@Rva00575A3F@@QAEXHH@Z retail 0x00575AE1..0x00575B7B (154
// bytes EH RET 8) and ?rva00575B7B@Rva00575A3F@@QAEXHH@Z retail
// 0x00575B7B..0x00575C15 (154 bytes EH RET 8): the two-argument siblings of
// the pinned 0x00575A3F method. The unrowed forwarder 0x00575DFE calls the
// first with its +0x0C word when that is set and else the second with its
// +0x10 word (else 0x00575A3F with the value alone) passing the receiver's
// +0x04 object and its +0x08 value. When the +0x28 holder's object accepts
// the value (its slot 6) nothing happens. Otherwise the holder is cleared
// (rowed Rva000AD6F4::clear) and set (rowed 0x00575674) to a new 0x0C-byte
// Rva005CF7BF (rowed constructor 0x005CF751) built from the +0x04 base
// subobject / the +0x1C and +0x20 words / the two values the +0x18 object's
// +0x04 field yields (rowed getters 0x00328A83 and 0x00574AAC) / &+0x24 /
// the value and the extra word in the eighth (0x00575AE1) or ninth
// (0x00575B7B) position with zero in the other.
// ?rva00575A3F@Rva00575A3F@@QAEXH@Z retail 0x00575A3F..0x00575AE1 (162
// bytes EH RET 4), the one-argument form the rowed slot 0x00575DD2
// tail-calls: an accepting holder object is restarted (its slot 4), else
// the same clear and set with the value and two zeros.
//
// Evidence: WB twins 0x014D3C80 and 0x014D3DB0 (score 1.0) show the same
// holder test / clear / new / reset sequence with a null-checked this+4 base
// conversion as the first constructor argument and the 0x00328A83 getter
// evaluated into a temporary before the argument pushes; the hoisted
// Rva00575A3FWord / Rva00575A3FRef temporaries reproduce that order. Class
// identity and field meanings remain unresolved.

class Object;

class Rva000AD6F4
{
public:
	void clear();
};

class Rva00575674
{
public:
	void rva00575674(Object *object);
};

class Rva005CF7BF
{
public:
	Rva005CF7BF(void *owner, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
	virtual ~Rva005CF7BF();
private:
	unsigned char m_pad04[0x0C - 0x04];
};

class Rva00328A83PtrChaseField
{
public:
	int get() const;
};

class Rva00574AACAddDwordField
{
public:
	int get() const;
};

class Rva00575A3FCurrent
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void restart();					// slot 4
	virtual void slot5();
	virtual bool accepts(int value);		// slot 6
};

struct Rva00575A3FSource
{
	unsigned char m_pad00[0x04];
	void *m_field04;						// +0x04
};

struct Rva00575A3FRef
{
	void *m_object;
	Rva00575A3FRef(void *object) : m_object(object) {}
	const Rva00328A83PtrChaseField *first() const
	{
		return static_cast<const Rva00328A83PtrChaseField *>(m_object);
	}
	const Rva00574AACAddDwordField *second() const
	{
		return static_cast<const Rva00574AACAddDwordField *>(m_object);
	}
};

struct Rva00575A3FWord
{
	int m_value;
	Rva00575A3FWord(int value) : m_value(value) {}
	operator int() const { return m_value; }
};

class Rva00575A3FBase0
{
public:
	virtual void base0Slot0();
};

class Rva00575A3FBase4
{
public:
	virtual void base4Slot0();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva00575A3F : public Rva00575A3FBase0, public Rva00575A3FBase4
{
public:
	void rva00575A3F(int value);
	void rva00575AE1(int value, int extra);
	void rva00575B7B(int value, int extra);
private:
	Rva00575A3FSource *m_source18;			// +0x18
	int m_1C;								// +0x1C
	int m_20;								// +0x20
	int m_24;								// +0x24
	Rva00575A3FCurrent *m_current28;		// +0x28 owning holder
};

void Rva00575A3F::rva00575A3F(int value)
{
	Rva00575A3FCurrent *current = m_current28;
	if (current && current->accepts(value))
	{
		m_current28->restart();
		return;
	}
	reinterpret_cast<Rva000AD6F4 *>(&m_current28)->clear();
	reinterpret_cast<Rva00575674 *>(&m_current28)->rva00575674(reinterpret_cast<Object *>(
		new Rva005CF7BF(static_cast<Rva00575A3FBase4 *>(this), m_1C, m_20,
			Rva00575A3FWord(Rva00575A3FRef(m_source18->m_field04).first()->get()),
			Rva00575A3FRef(m_source18->m_field04).second()->get(),
			(int)&m_24, value, 0, 0)));
}

void Rva00575A3F::rva00575AE1(int value, int extra)
{
	Rva00575A3FCurrent *current = m_current28;
	if (current && current->accepts(value))
		return;
	reinterpret_cast<Rva000AD6F4 *>(&m_current28)->clear();
	reinterpret_cast<Rva00575674 *>(&m_current28)->rva00575674(reinterpret_cast<Object *>(
		new Rva005CF7BF(static_cast<Rva00575A3FBase4 *>(this), m_1C, m_20,
			Rva00575A3FWord(Rva00575A3FRef(m_source18->m_field04).first()->get()),
			Rva00575A3FRef(m_source18->m_field04).second()->get(),
			(int)&m_24, value, extra, 0)));
}

void Rva00575A3F::rva00575B7B(int value, int extra)
{
	Rva00575A3FCurrent *current = m_current28;
	if (current && current->accepts(value))
		return;
	reinterpret_cast<Rva000AD6F4 *>(&m_current28)->clear();
	reinterpret_cast<Rva00575674 *>(&m_current28)->rva00575674(reinterpret_cast<Object *>(
		new Rva005CF7BF(static_cast<Rva00575A3FBase4 *>(this), m_1C, m_20,
			Rva00575A3FWord(Rva00575A3FRef(m_source18->m_field04).first()->get()),
			Rva00575A3FRef(m_source18->m_field04).second()->get(),
			(int)&m_24, value, 0, extra)));
}
