// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva003FDB90@Rva003FDB90@@QAEXXZ @0x003FDB90 65B
// Chain-lane body calling just-landed 0x3FDC46; callees pin 0x3FB7DB plus
// rowed Random_Float plus pin 0x3FDAEB plus rowed 0x3FDC46 tail-jmp.
// Offsets 0x38 0x40 0x44 0x48 unsigned with 0.7f gate. VTABLE slot 3 at
// 0x837DA0 is not xfer shape here so honest Rva name.
class WWMath
{
public:
	static float Random_Float();
};

class Rva003FDCEB
{
public:
	void rva003FB7DB();
};

class Rva003FDD05Host
{
public:
	void rva003FDAEB();
};

class Rva003FDC46
{
public:
	void rva003FDC46();
};

class Rva003FDB90
{
public:
	void rva003FDB90();
private:
	char m_pad[0x38];
	unsigned int m_38;
	unsigned int m_3C;
	unsigned int m_40;
	unsigned int m_44;
	unsigned int m_48;
};

// ?rva003FDB90@Rva003FDB90@@QAEXXZ
void Rva003FDB90::rva003FDB90()
{
	((Rva003FDCEB *)this)->rva003FB7DB();
	if (m_38 > m_40 && m_38 < m_44) {
		if (WWMath::Random_Float() > 0.7f)
			((Rva003FDD05Host *)this)->rva003FDAEB();
	}
	if (m_38 > m_48)
		((Rva003FDC46 *)this)->rva003FDC46();
}
