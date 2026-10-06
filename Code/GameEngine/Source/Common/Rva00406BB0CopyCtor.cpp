// cl: /EHsc /MD
// ??0Rva00406BB0@@QAE@ABV0@@Z @0x00406BB0 67B
// Copy ctor storing vtable 0x00838BA4 via inline base copy then member wide
// string at +4 via rowed StringBase copy ctor 0x00037050 and int at +8.
// Base carries the declared dtor that forces EH state 0 with homed this for
// funclet 0x0078507B. Unlocks 0x00406CD3.
template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
private:
	StringBase(const StringBase &other);
	friend class Rva00406BB0;
	friend class Rva00406BB0Base;
};

class Rva00406BB0Base
{
public:
	Rva00406BB0Base(const Rva00406BB0Base &other) {}
	virtual ~Rva00406BB0Base();
	virtual void keep() {}
};

class Rva00406BB0 : public Rva00406BB0Base
{
public:
	Rva00406BB0(const Rva00406BB0 &other);

private:
	StringBase<unsigned short> m_str04; // +4
	int m_08; // +8
};

Rva00406BB0::Rva00406BB0(const Rva00406BB0 &other)
	: Rva00406BB0Base(other), m_str04(other.m_str04), m_08(other.m_08)
{
}
