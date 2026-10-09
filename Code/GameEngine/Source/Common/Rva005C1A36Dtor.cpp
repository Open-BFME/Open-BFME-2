// cl: /DNDEBUG /MD /EHs

// ??1Rva005C1A36@@UAE@XZ, RVA 0x005C1A36, 79B. Chain lane: virtual dtor
// storing vtable 0x008743DC, releasing the held object at +0x2c through its
// vtable slot 0 with arg 0, deleting the returned pointer via rowed operator
// delete 0x0002FD60, nulling the member, then calling the rowed base dtor
// ??1AptStats@@UAE@XZ at 0x005DD1EA. Base is the proven0x2CB AptStats; held object remains at+0x2c.
// Held type unknown beyond slot 0 shape, modeled as a TU-local shim.
// Two callers in 0x00521977 plus its ??_G at 0x005C1A9E. Flags copy
// Rva005DD1EADtor.cpp for the EH state idiom.
// Consuming ABI view: the native AptStats ctor proves44B. Its retained
// virtual destructor provider owns the full vector/base cleanup.
class AptStats {public:virtual ~AptStats();private:char m_pad[0x2C-4];};

struct HeldSlot0 {
	virtual void *heldSlot0(int flags);
};

class Rva005C1A36 : public AptStats
{
public:
	virtual ~Rva005C1A36();
private:
	HeldSlot0 *m_2c;
};

void __cdecl operator delete(void *);

Rva005C1A36::~Rva005C1A36()
{
	HeldSlot0 *p = m_2c;
	void *q;
	if (p)
		q = p->heldSlot0(0);
	else
		q = 0;
	::operator delete(q);
	m_2c = 0;
}
