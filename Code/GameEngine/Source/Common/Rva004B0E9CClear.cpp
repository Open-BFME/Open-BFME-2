// cl: /O1 /DNDEBUG /MD
//
// ?rva004B0E9C@Rva004B0E9C@@QAEXXZ @0x004B0E9C 32B.
// When the pointer at +0x9C is live and the dword at [that+4]+0x4C is not
// -1, call 0x004DD2C0 on it and clear the slot.

class Rva004DD2C0Inner
{
public:
	char m_pad[0x4C];
	int m_field;
};

class Rva004DD2C0
{
public:
	char m_pad[4];
	Rva004DD2C0Inner *m_inner;
	void rva004DD2C0();
};

class Rva004B0E9C
{
public:
	void rva004B0E9C();

private:
	char m_pad[0x9C];
	Rva004DD2C0 *m_slot;
};

void Rva004B0E9C::rva004B0E9C()
{
	Rva004DD2C0 *slot = m_slot;
	if (slot != 0 && slot->m_inner->m_field != -1)
	{
		slot->rva004DD2C0();
		m_slot = 0;
	}
}
