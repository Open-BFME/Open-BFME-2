// cl: /DNDEBUG /MD
// ?rva0046800B@Rva0046800B@@QAEXXZ retail 0x0046800B 30B
// Range-destroy helper over two Elem pointers at +0/+4 via rowed cdecl
// Destroy 0x00467DCD then free +0 via rowed _free 0x00030830 if non-null.
// Evidence: push [esi+4] push [esi] call Destroy, mov esi [esi] test, pop
// pair for cdecl cleanup under /O1, je over free, sole caller 0x004682E3
// unblocking 0x0046824A; neighbours share /O1. Honest Rva method name.
struct Elem00467DCD;
void __cdecl Rva00467DCDDestroy(Elem00467DCD *first, Elem00467DCD *last);
extern "C" void __cdecl free(void *block);

class Rva0046800B
{
public:
	void rva0046800B();
private:
	Elem00467DCD *m_first;
	Elem00467DCD *m_last;
};
void Rva0046800B::rva0046800B()
{
	Rva00467DCDDestroy(m_first, m_last);
	Elem00467DCD *p = m_first;
	if (p)
		free(p);
}
