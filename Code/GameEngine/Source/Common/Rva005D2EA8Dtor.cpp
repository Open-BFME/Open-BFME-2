// cl: /MD /EHsc
// ??1Rva005D2EA8@@UAE@XZ retail 0x005D2EA8 73B
// Own vptr C75898, then if the listener at +4 is set it is told through its
// slot 0 with this; the rowed member dtor ??1Rva0052413E@@QAE@XZ tears down
// +0xC under EH state 0; the base inline dtor restores vtable BE2B78.
// Caller: rowed ??_GRva005D2EA8 0x005D2F62 (vtable 0x00C75898). Names
// address-derived.

class Rva0052413E
{
public:
	~Rva0052413E();

private:
	void *m_data[3];
};

class Rva005D2EA8Listener
{
public:
	virtual void notify(void *who) = 0;
};

class Rva005D2EA8Base
{
public:
	virtual ~Rva005D2EA8Base() {}
};

class Rva005D2EA8 : public Rva005D2EA8Base
{
public:
	virtual ~Rva005D2EA8();

private:
	Rva005D2EA8Listener *m_listener; // +0x04
	int m_08;
	Rva0052413E m_0C; // +0x0C
};

Rva005D2EA8::~Rva005D2EA8()
{
	if (m_listener != 0)
		m_listener->notify(this);
}
