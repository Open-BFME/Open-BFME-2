// cl: /MD
// ?rva0007E016@Rva0007E016@@QAEHHH@Z placeholder, retail 0x0007E016, 20 bytes.
// __thiscall forwarder to vtable slot 1 with two ints returning first.
// Evidence: callers 0x00082DD0 0x0027D9ED 0x0030D183 0x0030D19C; prev Disp32Dword no-flags next Thunk /O1 /MD.
class Rva0007E016 {
	virtual void f0();
	virtual void vfunc(int a0, int a1);
public:
	int rva0007E016(int a0, int a1);
};

int Rva0007E016::rva0007E016(int a0, int a1)
{
	vfunc(a0, a1);
	return a0;
}
