// ??0Rva00285BEC@@QAE@HH@Z
// partial score=0.92 date=2026-10-06
// cl: /O1 /MD /EHsc
// ??1Rva00285BEC@@UAE@XZ retail 0x00285BEC 68B
// ??0Rva00285BEC@@QAE@HH@Z retail 0x00285B91 83B: two-int ctor stores BFB700/BFB6F0 then args then m_10=-1 then rowed rva00285708. Evidence: neighbour dtor TU layout plus callers 0x00286A3F 0x00287E57.
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
	virtual ~Rva00285BECBase() throw() {}
};

class Rva00285BECSnapshotBase
{
public:
	virtual ~Rva00285BECSnapshotBase() throw() {}
};

class Rva00285BEC : public Rva00285BECBase, public Rva00285BECSnapshotBase
{
public:
	Rva00285BEC(int a, int b);
	virtual ~Rva00285BEC();

private:
	int m_08;
	int m_0C;
	int m_10;
};

Rva00285BEC::Rva00285BEC(int a, int b)
{
	m_10 = -1;
	m_08 = a;
	m_0C = b;
	((Rva00285708Host *)this)->rva00285708();
}

Rva00285BEC::~Rva00285BEC()
{
	((Rva0028572AHost *)this)->rva0028572A();
}
