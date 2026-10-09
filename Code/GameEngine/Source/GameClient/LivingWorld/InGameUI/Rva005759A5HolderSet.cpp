// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Twin of rowed0057590E holder setter, adapted using native005759A5..575A3F
// 154B evidence: accepts at vslot5, 20B allocation, one additional20 field
// argument, current112B ctor005CE804. Owner at4,source18,words1C/20,holder28.
// Getter328A83 evaluated first via the same local-word temporary as sibling.
// Receiver and purpose remain unnamed; use existing pinned address spelling.
class Object;
class LivingWorldRegion;

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

struct FwdArg;
class Rva005CE804 {
public: Rva005CE804(void *owner,int context,int unused,int ui,int extra,FwdArg *region);
virtual ~Rva005CE804();
private: unsigned char storage[0x20-4];
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

class Rva005759A5Current
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void restart();					// slot 4
	virtual bool accepts(int value); // slot5
};

struct Rva005759A5Source
{
	unsigned char m_pad00[0x04];
	void *m_field04;						// +0x04
};

struct Rva005759A5Ref
{
	void *m_object;
	Rva005759A5Ref(void *object) : m_object(object) {}
	const Rva00328A83PtrChaseField *first() const
	{
		return static_cast<const Rva00328A83PtrChaseField *>(m_object);
	}
	const Rva00574AACAddDwordField *second() const
	{
		return static_cast<const Rva00574AACAddDwordField *>(m_object);
	}
};

struct Rva005759A5Word
{
	int m_value;
	Rva005759A5Word(int value) : m_value(value) {}
	operator int() const { return m_value; }
};

class Rva005759A5Base0
{
public:
	virtual void base0Slot0();
};

class Rva005759A5Base4
{
public:
	virtual void base4Slot0();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva005759A5 : public Rva005759A5Base0, public Rva005759A5Base4
{
public:
	void rva005759A5(int value);
private:
	Rva005759A5Source *m_source18;			// +0x18
	int m_1C;								// +0x1C
	int m_20;
	unsigned char m_pad24[0x28 - 0x24];
	Rva005759A5Current *m_current28;		// +0x28 owning holder
};

void Rva005759A5::rva005759A5(int value)
{
	Rva005759A5Current *current = m_current28;
	if (current && current->accepts(value))
	{
		m_current28->restart();
		return;
	}
	reinterpret_cast<Rva000AD6F4 *>(&m_current28)->clear();
	reinterpret_cast<Rva00575674 *>(&m_current28)->rva00575674(reinterpret_cast<Object *>(
		new Rva005CE804(static_cast<Rva005759A5Base4 *>(this), m_1C, m_20,
			Rva005759A5Word(Rva005759A5Ref(m_source18->m_field04).first()->get()),
			Rva005759A5Ref(m_source18->m_field04).second()->get(),
			(FwdArg *)value)));
}
