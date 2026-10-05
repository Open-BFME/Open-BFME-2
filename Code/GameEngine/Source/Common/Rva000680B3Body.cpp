// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Dump range 1 (0x000680B3 35B): dual guarded member dispatches. The first
// guard calls through +0x3850; the second restores esi before the branch
// and tail-jumps through +0x3854. Honest address-derived names; callees
// are pins (unrowed siblings 0x000EB3D1/0x000E7B04). No header edits.

class Rva000680B3Sub
{
public:
	void subA();
	void subB();
};

class Rva000680B3Host
{
public:
	void rva000680B3();

	char m_pad[0x3850];
	Rva000680B3Sub *m_3850; // +0x3850
	Rva000680B3Sub *m_3854; // +0x3854
};

void Rva000680B3Host::rva000680B3()
{
	if (m_3850)
		m_3850->subA();
	if (m_3854)
		m_3854->subB();
}
