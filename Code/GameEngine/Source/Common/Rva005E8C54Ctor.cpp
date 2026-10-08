// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
//
// ??0Rva005E8C54@@QAE@PAXH0PBURva005E8C54Source@@@Z, retail 0x005E8C54..
// 0x005E8CB0 (92 bytes, EH, RET 16), and the holder constructor that builds
// it, ??0Rva005E8CB0@@QAE@PAXH0PBURva005E8C54Source@@@Z, retail 0x005E8CB0..
// 0x005E8CF8 (72 bytes, EH, RET 16). No WorldBuilder names; both are
// address-derived.
//
// The 12-byte object keeps the source's +0x18 at +0x00 and builds its +0x04
// member through the rowed Rva005F86FE constructor (0x005F86FE). It then runs
// its own 0x005E8B66 (238 bytes, not yet rowed; pinned) with the second
// argument and, when the member reports entries (rowed 0x005F8408), its
// rowed forwarder 0x005F841F. The holder allocates it with operator new and
// keeps the pointer at +0x00. The earlier verdicts were blocked on
// 0x005F8408 and 0x005F841F, which are rowed now.

class Rva005F86FE
{
public:
	Rva005F86FE(void *a1, void *a2);
	virtual ~Rva005F86FE();
private:
	void *m_04;
};

// The member's rowed count and forwarder, spelled on this address class.
class Rva005F8427
{
public:
	int rva005F8408() const;
	void rva005F841F();
};

struct Rva005E8C54Source
{
	unsigned char m_pad00[0x18];
	void *m_18;
};

class Rva005E8C54
{
public:
	Rva005E8C54(void *a, int b, void *c, const Rva005E8C54Source *source);
	void rva005E8B66(int b);

private:
	void *m_source18;				// +0x00
	Rva005F86FE m_member04;			// +0x04
};

Rva005E8C54::Rva005E8C54(void *a, int b, void *c, const Rva005E8C54Source *source)
	: m_source18(source->m_18),
	  m_member04(a, c)
{
	rva005E8B66(b);
	if (reinterpret_cast<Rva005F8427 *>(&m_member04)->rva005F8408() > 0)
		reinterpret_cast<Rva005F8427 *>(&m_member04)->rva005F841F();
}

class Rva005E8CB0
{
public:
	Rva005E8CB0(void *a, int b, void *c, const Rva005E8C54Source *source);

private:
	Rva005E8C54 *m_object;			// +0x00
};

Rva005E8CB0::Rva005E8CB0(void *a, int b, void *c, const Rva005E8C54Source *source)
	: m_object(new Rva005E8C54(a, b, c, source))
{
}
