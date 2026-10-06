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
