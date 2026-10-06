// cl: /DNDEBUG /MD
// ??0FreelistPool@@QAE@HHHHHH@Z @0x001EB1CB 67B: FreelistPool ctor sets 0x80 plus alloc free defaults then init; calls 0x002AA35C.
class FreelistPool
{
public:
	FreelistPool(int a1, int a2, int a3, int a4, int a5, int a6);
	bool rva002AA35C(int a1, int a2, int a3, void* (__cdecl* a4)(int, int), int a5, int a6);
private:
	int m_00;
	void* m_04;
	void* m_head;
	void* (__cdecl* m_alloc)(int, int);
	void (__cdecl* m_free)(void*, int);
	int m_14;
};

void* __cdecl Rva0002FFC0Alloc(int size, int ignored);
void __cdecl Rva0002FFE0Free(void* ptr, int ignored);

FreelistPool::FreelistPool(int a1, int a2, int a3, int a4, int a5, int a6)
{
	m_00 = 0x80;
	m_04 = 0;
	m_head = 0;
	m_alloc = Rva0002FFC0Alloc;
	m_free = Rva0002FFE0Free;
	m_14 = 0;
	rva002AA35C(a1, a2, a3, (void* (__cdecl*)(int, int))a4, a5, a6);
}
