// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva005CE1EB@Rva005CDF6C@@QAEXXZ, retail 0x005CE1EB..0x005CE21C (49 bytes):
// slot 21 of Rva005CDF6C's vtable. The base's own slot (the shared empty body
// 0x000B3FD0) runs first; then, when the +0x18 object's rowed 0x004E0625
// query holds, the +0x14 object is told its +0x24 value (rowed forwarder
// 0x005CB84A) and the +0x1C object, if any, runs its rowed 0x005E88DD as a
// tail call. WorldBuilder's twin (0x015C19A0) is unnamed.

class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class Rva004E0625
{
public:
	int rva004E0625() const;
};

struct Rva005CE1EBSource : public Rva004E0625
{
	unsigned char m_pad00[0x24];
	int m_24;
};

class Rva005CB84A
{
public:
	void rva005CB84A(int value);
};

class Rva005E88DDNullTarget
{
public:
	void rva005E88DD();
};

class Rva005CDF6C
{
public:
	void rva005CE1EB();
private:
	unsigned char m_pad00[0x14];
	Rva005CB84A *m_14;
	Rva005CE1EBSource *m_18;
	Rva005E88DDNullTarget *m_1C;
};

void Rva005CDF6C::rva005CE1EB()
{
	reinterpret_cast<Rva000B3FD0 *>(this)->rva000B3FD0();
	if (m_18->rva004E0625())
	{
		m_14->rva005CB84A(m_18->m_24);
		if (m_1C)
			m_1C->rva005E88DD();
	}
}
