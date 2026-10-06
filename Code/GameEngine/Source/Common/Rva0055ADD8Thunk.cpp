// cl: /MD
// ?rva0055ADD8@Rva0055ADD8@@QAEHH@Z @ 0x0055ADD8, 10 bytes.
// Thunk forwarding constant 3 to vtable slot 7 ignoring its int arg.
// Evidence: retail mov eax [ecx] push 3 call [eax+0x1C] ret 4; callers
// 0x573CED 0x4ECCB1 pass through their own arg; vslot 7 of unknown class.
class Rva0055ADD8
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual int v7(int x);
	int rva0055ADD8(int ignored);
};

int Rva0055ADD8::rva0055ADD8(int ignored)
{
	(void)ignored;
	return v7(3);
}
