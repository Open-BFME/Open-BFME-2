// cl: /O1 /MD
//
// ?rva0054CC1B@Rva0054CC1B@@QAEXXZ @0x0054CC1B (26B).
// Releasing wrapper for ??1Rva0054C941: takes pointer at +0, nulls it with
// and [ecx] 0, destroys via rowed dtor then rowed operator delete.
// Chain from 0x0054C941, unblocks 0x0054D2CF, LINK BONUS via.
class Rva0054C941
{
public:
	~Rva0054C941();
};
void __cdecl operator delete(void *p);
class Rva0054CC1B
{
public:
	void rva0054CC1B();
private:
	Rva0054C941 *m_ptr;	// +0x00
};
void Rva0054CC1B::rva0054CC1B()
{
	Rva0054C941 *p = m_ptr;
	m_ptr = 0;
	if (p)
		delete p;
}
class Rva0054D2CF
{
public:
	virtual ~Rva0054D2CF();
private:
	Rva0054CC1B m_holder;	// +0x04 (vptr at +0x00)
};
Rva0054D2CF::~Rva0054D2CF()
{
	m_holder.rva0054CC1B();
}
