// cl: /O1 /MD
// ?rva0057873E@Rva0057873E@@QAEXPAVRva005D3C2B@@@Z @0x0057873E 35B: setter with same-pointer early-out then explicit dtor plus global operator delete on old.
// Evidence: callees pinned 0x005D3C2B ??1Rva005D3C2B@@QAE@XZ and rowed 0x0002FD60 ??3@YAXPAX@Z; caller 0x00578941; same 35B shape as Rva0057866DSet precedent.
class Rva005D3C2B
{
public:
	~Rva005D3C2B();
};

void __cdecl operator delete(void *p);

class Rva0057873E
{
public:
	void rva0057873E(Rva005D3C2B *p);
private:
	void *m_ptr;
};

void Rva0057873E::rva0057873E(Rva005D3C2B *p)
{
	void *old = m_ptr;
	if (p == old)
		return;
	m_ptr = p;
	if (old == 0)
		return;
	((Rva005D3C2B *)old)->Rva005D3C2B::~Rva005D3C2B();
	operator delete(old);
}
