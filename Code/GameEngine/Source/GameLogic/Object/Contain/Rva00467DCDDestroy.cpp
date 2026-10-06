// cl: /DNDEBUG /MD
// ?Rva00467DCDDestroy@@YAXPAUElem00467DCD@@0@Z retail 0x00467DCD 25B
// Range destroy over 0xC elements calling rowed dtor 0x00466E23 at +0.
// Evidence: mov esi first jmp cmp loop with mov ecx esi call add esi 0xC
// cmp esi last jne plus ret (cdecl two pointers); step 0xC needs 12B elem
// with 8B Rva at +0; callers at 0x00467FE6 0x00468013; neighbours share
// /O1. Honest Rva free-function name.
class Rva00466E23
{
public:
	~Rva00466E23();
private:
	char m_pad[8];
};
struct Elem00467DCD
{
	Rva00466E23 m_rva;
	int m_08;
};
void __cdecl Rva00467DCDDestroy(Elem00467DCD *first, Elem00467DCD *last)
{
	for (; first != last; ++first)
		first->m_rva.~Rva00466E23();
}
