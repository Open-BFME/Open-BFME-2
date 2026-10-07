// cl: /MD
// ?rva005CC26E@Rva005CC26E@@QAEHPAX@Z @0x005CC26E 25B evidence: caller 0x0057491D lea ecx esi+0x5c push edi call; arg+0x10 compared to 0x70; true calls pin 0x005CC23B then returns 1 else 0
class Rva005CC23B
{
public:
	bool rva005CC23B();
};
class Rva005CC26E
{
public:
	int rva005CC26E(void *p);
};
int Rva005CC26E::rva005CC26E(void *p)
{
	if (*(int *)((char *)p + 0x10) != 0x70)
		return 0;
	((Rva005CC23B *)this)->rva005CC23B();
	return 1;
}
