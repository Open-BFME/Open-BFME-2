// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch M. As in VslotSmallBodiesA-L, each class and method
// is address-derived unless the ledger already names it, and models only what
// its body touches; the comment above each gives the .rdata slot address that
// references it. Meanings are not recovered.

typedef int Int;
typedef bool Bool;

// slot at VA 0x00C3ADB0: true when the one thread in the +0x74 table is
// running (rowed ThreadClass::Is_Running).
class ThreadClass
{
public:
	Bool Is_Running();
};
class Rva00419D2A
{
public:
	Bool rva00419D2A();
private:
	char m_pad00[0x74];
	ThreadClass *m_threads[1];
};
Bool Rva00419D2A::rva00419D2A()
{
	for (Int i = 0; i < 1; ++i)
	{
		if (m_threads[i] && m_threads[i]->Is_Running())
			return true;
	}
	return false;
}

// slot at VA 0x00C3BE24: deleteOverrides on every non-NULL entry of the
// pointer array [+0x0C, +0x10) (rowed Overridable::deleteOverrides).
class Overridable
{
public:
	Overridable *deleteOverrides();
};
class Rva004210D0
{
public:
	void rva004210D0();
private:
	char m_pad00[0x0C];
	Overridable **m_begin;
	Overridable **m_end;
};
void Rva004210D0::rva004210D0()
{
	for (Overridable **it = m_begin; it != m_end; ++it)
	{
		if (*it)
			(*it)->deleteOverrides();
	}
}

// slot at VA 0x00C3CDCC: a message handler. Message 0x15 with first byte 1 is
// handled (1), running the rowed 0x00433D27 when bit 0 of the second byte is
// set and +0x27C is 0; anything else is not (0).
void Rva00433D27Enable();
class Rva00434132
{
public:
	Int rva00434132(Int message, unsigned char a, unsigned char b);
private:
	char m_pad00[0x27C];
	Int m_27C;
};
Int Rva00434132::rva00434132(Int message, unsigned char a, unsigned char b)
{
	if (message != 0x15)
		return 0;
	switch (a)
	{
	case 1:
		break;
	default:
		return 0;
	}
	if ((b & 1) && m_27C == 0)
		Rva00433D27Enable();
	return 1;
}
