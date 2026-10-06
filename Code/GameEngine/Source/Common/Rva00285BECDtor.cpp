// cl: /O1 /MD /EHsc
// ??1Rva00285BEC@@UAE@XZ retail 0x00285BEC 68B
// ??0Rva00285BEC@@QAE@ABV0@@Z retail 0x00285C30 88B: copy ctor copies +8/+0xC from src then m_10=-1 then rowed rva00285708. Evidence: same vptrs BFB700/BFB6F0 plus BBB554 base plus single caller 0x00286279.
// Two-base dtor: own vptrs BFB700 at +0 and BFB6F0 at +4, then under EH
// state 1 the rowed ?rva0028572A@Rva0028572AHost 0x0028572A on this (which
// unregisters from g_00DFE1A8 when m_10 is set); the inline base dtors then
// restore BBB554 (second base at +4, the Snapshot vtable) and BFB698 (+0).
// Names address-derived.

class Rva0028572AHost
{
public:
	void rva0028572A();
};

class Rva00285708Host
{
public:
	void rva00285708();
};

class Rva00285BECBase
{
public:
	virtual ~Rva00285BECBase() {}
};

class Rva00285BECSnapshotBase
{
public:
	virtual ~Rva00285BECSnapshotBase() {}
};

class Rva00285BEC : public Rva00285BECBase, public Rva00285BECSnapshotBase
{
public:
	struct Pair080C
	{
		int m_00;
		int m_04;
		Pair080C() {}
		Pair080C(int a, int b) : m_00(a), m_04(b) {}
		Pair080C(const Pair080C &src) : m_00(src.m_00), m_04(src.m_04) {}
	};
	Rva00285BEC(int a, int b);
	Rva00285BEC(const Rva00285BEC &src);
	virtual ~Rva00285BEC();

private:
	Pair080C m_08;
	int m_10;
};

Rva00285BEC::Rva00285BEC(int a, int b) : m_08(a, b), m_10(-1)
{
	((Rva00285708Host *)this)->rva00285708();
}

Rva00285BEC::Rva00285BEC(const Rva00285BEC &src)
{
	m_08.m_00 = src.m_08.m_00;
	m_08.m_04 = src.m_08.m_04;
	m_10 = -1;
	((Rva00285708Host *)this)->rva00285708();
}

Rva00285BEC::~Rva00285BEC()
{
	((Rva0028572AHost *)this)->rva0028572A();
}
