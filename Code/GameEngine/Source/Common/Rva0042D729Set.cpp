// cl: /O1 /MD
// ?rva0042D729@Rva0042D729@@QAEXPAVRva00577DE1OwningCell@@@Z @0x0042D729 35B: set holder at +0 clearing old via ForwardClear plus delete.
// Evidence: calls rowed ForwardClear 0x00577E3E plus rowed delete 0x0002FD60; caller 0x0042DD37; prev Rva0042D71ACond next Rva0042D7A3Set sibling pattern.
class Rva00577DE1OwningCell
{
public:
	void rva00577E3EForwardClear();
};

class Rva0042D729
{
public:
	void rva0042D729(Rva00577DE1OwningCell *newPtr);
private:
	Rva00577DE1OwningCell *m_00;
};

void operator delete(void *p);

void Rva0042D729::rva0042D729(Rva00577DE1OwningCell *newPtr)
{
	Rva00577DE1OwningCell *old = m_00;
	if (newPtr == old)
		return;
	m_00 = newPtr;
	if (old == 0)
		return;
	old->rva00577E3EForwardClear();
	operator delete(old);
}
