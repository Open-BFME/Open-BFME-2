// cl: /MD
// ?Rva000515E4Less@@YA_NPBURva000515E4Key@@0@Z @0x000515E4 43B
// Free __cdecl less of {int+float} via two pointers; AL returns then xor-eax float tail.
// Evidence: caller 0x0005BD30 pushes ebp-0x10/0x18 and tests AL; unblocks 0x0005BD30 0x0005BDD2.
struct Rva000515E4Key
{
	int a;
	float b;
};

bool __cdecl Rva000515E4Less(const Rva000515E4Key *x, const Rva000515E4Key *y);

bool __cdecl Rva000515E4Less(const Rva000515E4Key *x, const Rva000515E4Key *y)
{
	if (x->a < y->a)
		return true;
	if (x->a > y->a)
		return false;
	return y->b > x->b;
}
