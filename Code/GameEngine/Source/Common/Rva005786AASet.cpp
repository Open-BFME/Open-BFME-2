// cl: /O1 /MD
// ?rva005786AA@Rva005786AA@@QAEXPAVRva005D32D4@@@Z @0x005786AA 35B: setter with same-pointer early-out then explicit dtor plus global operator delete on old.
// Evidence: callees pinned 0x005D32D4 ??1Rva005D32D4@@QAE@XZ and rowed 0x0002FD60 ??3@YAXPAX@Z; caller 0x00578803; same 35B shape as Rva0057866DSet precedent.
class Rva005D32D4
{
public:
	~Rva005D32D4();
};

void __cdecl operator delete(void *p);

class Rva005786AA
{
public:
	void rva005786AA(Rva005D32D4 *p);
private:
	void *m_ptr;
};

void Rva005786AA::rva005786AA(Rva005D32D4 *p)
{
	void *old = m_ptr;
	if (p == old)
		return;
	m_ptr = p;
	if (old == 0)
		return;
	((Rva005D32D4 *)old)->Rva005D32D4::~Rva005D32D4();
	operator delete(old);
}
