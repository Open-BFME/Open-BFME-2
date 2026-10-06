// ?wrapper@Rva00034C90@@QAEXXZ
// cl: /MD
// ?wrapper@Rva00034C90@@QAEXXZ @0x00034C90 104B address-derived refcount guard
// wrapper: m_pLock at +0x4E4 points at a CRITICAL_SECTION+refcount lock.
// EnterCriticalSection (IAT 0xBBA200) runs, the volatile +0x18 refcount is
// incremented, body 0x33930 runs, then the refcount is decremented and
// LeaveCriticalSection (IAT 0xBBA204) runs. Same lock layout as the rowed
// Rva00030DD0 addref at 0x00030DD0. The two IAT calls are declared
// dllimport+throw() so cl treats them as nothrow and omits the EH state reset
// retail does not carry.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs) throw();
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs) throw();

class Rva00034C90Lock
{
public:
	void *m_obj;
	Rva00034C90Lock(void *obj) : m_obj(obj)
	{
		if (m_obj)
		{
			EnterCriticalSection(m_obj);
			++*(volatile int *)((char *)m_obj + 0x18);
		}
	}
	~Rva00034C90Lock()
	{
		if (m_obj)
		{
			--*(volatile int *)((char *)m_obj + 0x18);
			LeaveCriticalSection(m_obj);
		}
	}
};

class Rva00034C90
{
public:
	void rva00033930();
	void wrapper();
private:
	char m_pad[0x4e4];
	void *m_pLock;
};

void Rva00034C90::wrapper()
{
	Rva00034C90Lock lock(m_pLock);
	rva00033930();
}
