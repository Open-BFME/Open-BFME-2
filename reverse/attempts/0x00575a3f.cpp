// ?rva00575A3F@Rva00575A3F@@QAEXH@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00575A3F@Rva00575A3F@@QAEXH@Z, retail 0x00575A3F..0x00575AE1 (162
// bytes, EH, RET 4): the method the rowed slot 0x00575DD2 tail-calls on its
// +0x08 object. When the +0x28 holder's object accepts the value (its slot 6)
// it is restarted (slot 4). Otherwise the holder is cleared (rowed
// Rva000AD6F4::clear) and given a new 0x0C-byte Rva005CF7BF (rowed
// constructor 0x005CF751) built from the +0x04 subobject, the +0x1C and +0x20
// words, the two values the +0x18 object's +0x04 field yields (rowed getters
// 0x00328A83 and 0x00574AAC), the +0x24 member, the value and two zeros, then
// set (pinned 0x00575674).

class Rva000AD6F4
{
public:
	void clear();
};

class Rva00575674Sub
{
public:
	void rva00575674(void *object);
};

class Rva005CF7BF
{
public:
	Rva005CF7BF(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
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
#define V(n) virtual void c##n();
	V(0) V(1) V(2) V(3)
	virtual void restart();					// slot 4
	V(5)
	virtual bool accepts(int value);		// slot 6
#undef V
};

struct Rva00575A3FSource
{
	unsigned char m_pad00[0x04];
	void *m_field04;						// +0x04
};

class Rva00575A3F
{
public:
	void rva00575A3F(int value);
private:
	unsigned char m_pad00[0x04];
	unsigned char m_sub04[0x18 - 0x04];		// +0x04
	Rva00575A3FSource *m_source18;			// +0x18
	int m_1C;								// +0x1C
	int m_20;								// +0x20
	int m_24;								// +0x24
	Rva00575A3FCurrent *m_current28;		// +0x28
};

void Rva00575A3F::rva00575A3F(int value)
{
	if (m_current28 && m_current28->accepts(value))
	{
		m_current28->restart();
		return;
	}
	reinterpret_cast<Rva000AD6F4 *>(&m_current28)->clear();
	void *field = m_source18->m_field04;
	reinterpret_cast<Rva00575674Sub *>(&m_current28)->rva00575674(
		new Rva005CF7BF(m_sub04, m_1C, m_20,
			static_cast<const Rva00328A83PtrChaseField *>(field)->get(),
			static_cast<const Rva00574AACAddDwordField *>(field)->get(),
			(int)&m_24, value, 0, 0));
}
