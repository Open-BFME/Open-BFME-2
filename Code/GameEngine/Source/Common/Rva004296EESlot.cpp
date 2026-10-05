// cl: /O1 /EHsc /MD
// ?rva004296EE@Rva0042CBB6@@QAEPAXI@Z @0x004296EE 28B: slot 1 of vtable 0x0083C6F4.
// Calls rowed apply 0x00429191 then conditional operator delete 0x0002FD60 on flag bit 0.
// Evidence: retail push esi/mov esi ecx/call apply/test byte esp+8 1/je/push esi/call delete/mov eax esi.
class Rva000429191DwordImmSetter
{
public:
	void apply();
};

void __cdecl operator delete(void *p);

class Rva0042CBB6
{
public:
	void *rva004296EE(unsigned int flag);
};

void *Rva0042CBB6::rva004296EE(unsigned int flag)
{
	((Rva000429191DwordImmSetter *)this)->apply();
	if (flag & 1)
		operator delete(this);
	return this;
}
