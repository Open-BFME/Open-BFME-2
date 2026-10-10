// cl: /MD
// ?rva0074011F@Rva0074011F@@QAEXXZ, retail 0x0074011F, 43 bytes.
// Releases two RefCount holders via inlined Release_Ref then nulls holder.
// Evidence: callers at 0x00066817 0x00066835 0x000D1C9F 0x007402A3; pattern matches TerrainTracks free precedent; container in 0x000D1C83 holds VB+IB pair.
class RefCountClass
{
public:
	virtual void Delete_This() = 0;
	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}
	int m_refs;
};
class Rva0074011F
{
public:
	void rva0074011F();
private:
	RefCountClass *m_p0;
	RefCountClass *m_p1;
};
void Rva0074011F::rva0074011F()
{
	if (m_p0)
	{
		m_p0->Release_Ref();
		m_p0 = 0;
	}
	if (m_p1)
	{
		m_p1->Release_Ref();
		m_p1 = 0;
	}
}

// ??1Rva0009A200@@QAE@XZ retail 0x001076E9 5 bytes, pinned under this name:
// the non-virtual destructor its scalar deleting destructor 0x0009A200 calls
// (also called at 0x0009A510). It releases the holder pair at offset 0, so
// the body is a tail jump into the release above.
class Rva0009A200
{
public:
	~Rva0009A200();
private:
	Rva0074011F m_00;
};

Rva0009A200::~Rva0009A200()
{
	m_00.rva0074011F();
}
