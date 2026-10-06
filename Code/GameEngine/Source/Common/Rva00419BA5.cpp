// cl: /MD
//
// ?rva00419BA5@Rva00419BA5@@QAEXXZ, retail 0x00419BA5, 19 bytes.
// Deletes result of virtual slot0 call with null-this guard: xor eax eax,
// cmp ecx eax je, mov edx [ecx] push eax call [edx], push eax call delete.
// Evidence: virtual call [edx] with 0 arg plus delete 0x0002FD60, callers 4
// including 0x00362570 0x0036261C, LINK 1 file 41B.
void __cdecl operator delete(void *);
class Rva00419BA5
{
public:
	virtual void *v0(int x);
	void rva00419BA5();
};
void Rva00419BA5::rva00419BA5()
{
	::operator delete(this ? v0(0) : 0);
}
