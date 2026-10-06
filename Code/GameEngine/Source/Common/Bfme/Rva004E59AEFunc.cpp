// ?Rva004E59AEFunc@@YAXPAP8Rva004E59AE@@AEXXZPAPAU1@1P81@AEXXZ@Z
// @0x004E59AE 34B free loop calling 0-arg method on each element then storing func
// cl: /MD
struct Rva004E59AE
{
	void rva();
};
typedef void (Rva004E59AE::*FuncType)();
void __cdecl Rva004E59AEFunc(FuncType *out, Rva004E59AE **first, Rva004E59AE **last, FuncType func)
{
	for (; first != last; ++first)
		((*first)->*func)();
	*out = func;
}
