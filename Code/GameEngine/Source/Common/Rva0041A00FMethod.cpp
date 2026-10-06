// cl: /MD
// ?rva0041A00F@Rva0041A00F@@QAEXXZ retail 0x0041A00F 56B method.
// Evidence: clears +0x80 via rowed 0x0009990D; stops thread +0x74
// via rowed 0x006105F0; virtual slot0 with 0 plus delete 0x0002FD60;
// chain caller 0x0041A662.
void __cdecl operator delete(void *p);
class Rva0009990D
{
public:
	void clear();
};
class ThreadClass
{
public:
	void Stop();
	virtual void *v0(int x);
};
class Rva0041A00F
{
public:
	void rva0041A00F();
private:
	char m_pad00[0x74];
	ThreadClass *m_thread74; // +0x74
	char m_pad78[8];
	Rva0009990D m_obj80; // +0x80
};
void Rva0041A00F::rva0041A00F()
{
	m_obj80.clear();
	if (m_thread74 == 0)
		return;
	m_thread74->Stop();
	void *p;
	if (m_thread74 != 0)
		p = m_thread74->v0(0);
	else
		p = 0;
	::operator delete(p);
	m_thread74 = 0;
}
