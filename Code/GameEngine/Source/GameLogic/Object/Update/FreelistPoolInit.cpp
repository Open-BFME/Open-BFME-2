// cl: /DNDEBUG /MD
// ?rva002AA35C@FreelistPool@@QAE_NHHHP6APAXHH@ZHH@Z @0x002AA35C 63B: FreelistPool init via m_00/m_alloc/m_10/m_14 plus grow; caller 0x001EB1CB forwards 6 args; unblocks 0x001EB1CB.
class FreelistPool
{
public:
	bool rva002AA35C(int a1, int a2, int a3, void* (__cdecl* a4)(int, int), int a5, int a6);
private:
	bool grow(int arena, int size);
	int m_00;
	void* m_04;
	void* m_head;
	void* (__cdecl* m_alloc)(int size, int arg);
	int m_10;
	int m_14;
};

bool FreelistPool::rva002AA35C(int a1, int a2, int a3, void* (__cdecl* a4)(int, int), int a5, int a6)
{
	if (a1 != 0)
		m_00 = a1;
	if (a4 != 0)
		m_alloc = a4;
	if (a5 != 0)
		m_10 = a5;
	m_14 = a6;
	if (m_04 == 0)
		return grow(a2, a3);
	return false;
}
