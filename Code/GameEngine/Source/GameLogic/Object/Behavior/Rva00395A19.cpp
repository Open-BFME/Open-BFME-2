// cl: /DNDEBUG /MD /EHsc
// ?rva00395A19@Rva00395A19@@QAEPAXI@Z RVA 0x00395A19 size 28 leaf vtable slot 0 calls rowed apply and delete.
class Rva00049C38ADwordImmSetter
{
public:
	void apply();
};
void __cdecl operator delete(void *p);
class Rva00395A19
{
public:
	void *rva00395A19(unsigned int flag);
};
void *Rva00395A19::rva00395A19(unsigned int flag)
{
	((Rva00049C38ADwordImmSetter *)this)->apply();
	if (!(flag & 1))
		return this;
	::operator delete(this);
	return this;
}
