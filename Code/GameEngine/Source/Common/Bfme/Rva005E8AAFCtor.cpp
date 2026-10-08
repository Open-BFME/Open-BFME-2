// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
//
// The counted 0x24-byte Rva005E8AAF (vtable 0x00C77F5C; destructor 0x005E8AAF
// and deleting destructor 0x005E8A93 are rowed) and the helper that adds one
// to a member list. No WorldBuilder names; all address-derived.
//
// - ??0Rva005E8AAF@@QAE@ABVRva005E8908@@@Z, retail 0x005E89A2..0x005E89DD
//   (59 bytes, EH, RET 4): the counted base Rva0007DF07 (count at +0x04
//   cleared; its destructor is the shared vtable store 0x004E84A4) and a copy
//   of the 0x1C-byte record at +0x08 (rowed copy constructor 0x005E8943).
// - vslot 1, retail 0x005E8A31..0x005E8A93 (98 bytes, EH, RET 4): returns a
//   counted handle on a new copy of itself.
// - ?rva005E8ADF@@YAXPAVRva005F86FE@@ABVRva005E8908@@@Z, retail
//   0x005E8ADF..0x005E8B66 (135 bytes, EH, cdecl): wraps a new record in a
//   typed handle and passes a converted one to the list's rowed forwarder
//   0x005F88CE; both handles release through the rowed 0x0007DEEF. It is the
//   0x005E8F6F pattern for a constructor that can throw.

class Rva0007DF07
{
public:
	inline Rva0007DF07() : m_refCount(0) {}
	virtual ~Rva0007DF07() {}

	int m_refCount;					// +0x04
};

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

template <typename T>
class StringBase
{
public:
	StringBase(const StringBase &other);
	~StringBase();

private:
	void *m_data;
};

class Rva005E8908
{
public:
	Rva005E8908(const Rva005E8908 &other);
	~Rva005E8908();

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	StringBase<unsigned short> m_str14;
	StringBase<unsigned short> m_str18;
};

// The member list's generic counted handle (see Rva005F83B9Notify.cpp).
struct Rva005F888CRef
{
	Rva005F888CRef(Rva0007DF07 *object) : m_object(object) { if (object) ++object->m_refCount; }
	~Rva005F888CRef() { if (m_object) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(m_object)); }
	Rva0007DF07 *m_object;
};

class Rva005F86FE;

class Rva005F8427
{
public:
	void rva005F88CE(const Rva005F888CRef &ref);
};

class Rva005E8AAF : public Rva0007DF07
{
public:
	Rva005E8AAF(const Rva005E8908 &value);
	__forceinline Rva005E8AAF(const Rva005E8AAF &other) : m_08(other.m_08) {}
	virtual ~Rva005E8AAF();
	virtual Rva005F888CRef rva005E8A31() const;

private:
	Rva005E8908 m_08;				// +0x08
};

// A typed counted handle on it.
class Rva005E8AAFHandle
{
public:
	explicit Rva005E8AAFHandle(Rva005E8AAF *object) : m_object(object) { if (object) ++object->m_refCount; }
	~Rva005E8AAFHandle() { if (m_object) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(m_object)); }
	Rva005E8AAF *m_object;
};

Rva005E8AAF::Rva005E8AAF(const Rva005E8908 &value)
	: m_08(value)
{
}

Rva005F888CRef Rva005E8AAF::rva005E8A31() const
{
	return Rva005F888CRef(new Rva005E8AAF(*this));
}

void rva005E8ADF(Rva005F86FE *list, const Rva005E8908 &value)
{
	Rva005E8AAFHandle record(new Rva005E8AAF(value));
	reinterpret_cast<Rva005F8427 *>(list)->rva005F88CE(record.m_object);
}
