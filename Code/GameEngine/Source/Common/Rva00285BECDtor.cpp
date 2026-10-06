// cl: /O1 /MD /EHsc
// ??1Rva00285BEC@@UAE@XZ retail 0x00285BEC 68B
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
	virtual ~Rva00285BEC();

private:
	unsigned char m_pad08[8];
	int m_10;
};

Rva00285BEC::~Rva00285BEC()
{
	((Rva0028572AHost *)this)->rva0028572A();
}
