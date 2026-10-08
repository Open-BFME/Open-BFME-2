// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva005F4C8E@Rva005F4C52@@QAE?AV?$Rva005F4C8ERef@VRva005E6ED6Third@@@@HH@Z,
// retail 0x005F4C8E..0x005F4CF8 (106 bytes, EH, RET 12): slot 1 of
// Rva005F4C52's vtable. It returns a counted reference to the third
// interface (+0x14) of a new 0x2C-byte Rva005E6ED6 built from both arguments
// and the +0x08 member (0x005E6ED6, not yet rowed; pinned; it takes the
// hidden construct-virtual-bases flag 1). The count lives in a virtual base,
// so the reference reaches it through the interface's vbptr. No WorldBuilder
// name is matched.

class Rva005E6ED6Counted
{
public:
	virtual ~Rva005E6ED6Counted();
	void addRef() { ++m_refs; }
	int m_refs;
};

class Rva005E6ED6First : public virtual Rva005E6ED6Counted
{
public:
	virtual void first0();
	int m_08;
};

class Rva005E6ED6Second : public virtual Rva005E6ED6Counted
{
public:
	virtual void second0();
};

class Rva005E6ED6Third : public virtual Rva005E6ED6Counted
{
public:
	virtual void third0();
	int m_08;
};

class Rva005E6ED6 : public Rva005E6ED6First, public Rva005E6ED6Second, public Rva005E6ED6Third
{
public:
	Rva005E6ED6(int a, int b, void *owner);
private:
	int m_20;
};

template <class T>
class Rva005F4C8ERef
{
public:
	__forceinline Rva005F4C8ERef(T *p) : m_p(p) { if (p) p->addRef(); }
	Rva005F4C8ERef(const Rva005F4C8ERef &other);
	~Rva005F4C8ERef();
private:
	T *m_p;
};

class Rva005F4C52
{
public:
	Rva005F4C8ERef<Rva005E6ED6Third> rva005F4C8E(int a, int b);
private:
	unsigned char m_pad00[0x08];
	int m_08;
};

Rva005F4C8ERef<Rva005E6ED6Third> Rva005F4C52::rva005F4C8E(int a, int b)
{
	return Rva005F4C8ERef<Rva005E6ED6Third>(new Rva005E6ED6(a, b, &m_08));
}

// ?rva005FAB34@Rva005FAAA1@@QAE?AV?$Rva005F4C8ERef@VRva005E6ED6Second@@@@HH@Z,
// retail 0x005FAB34..0x005FAB9E (106 bytes, EH, RET 12): slot 5 of
// Rva005FAAA1's vtable, the same factory returning the second interface
// (+0x0C) of the new object.
class Rva005FAAA1
{
public:
	Rva005F4C8ERef<Rva005E6ED6Second> rva005FAB34(int a, int b);
private:
	unsigned char m_pad00[0x08];
	int m_08;
};

Rva005F4C8ERef<Rva005E6ED6Second> Rva005FAAA1::rva005FAB34(int a, int b)
{
	return Rva005F4C8ERef<Rva005E6ED6Second>(new Rva005E6ED6(a, b, &m_08));
}
