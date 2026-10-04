// cl: /O1 /G7 /DNDEBUG /MD
// ?rva0029ACA0@Rva0029ACA0@@QAEXHI@Z @0x0029ACA0 39B
// Unlock lane: missing callee of 0x0029ACC7 loop (calls with (0,i) for i in 0..24).
// Evidence: frameless thiscall ret 8; guards (arg1!=0 return and (unsigned)arg2>=0x19
// return with jae); imul 0x14 strides with and [edx+ecx+0x4C],0 under /O1 and
// mov byte [eax+ecx],1 for (arg2+4)*0x14; neighbours /O1.
class Rva0029ACA0
{
public:
	void rva0029ACA0(int a, unsigned int b);
	void rva0029ACC7(int guard);
};
void Rva0029ACA0::rva0029ACA0(int a, unsigned int b)
{
	if (a != 0)
		return;
	if (b >= 0x19)
		return;
	*(unsigned int *)((char *)this + b * 0x14 + 0x4C) = 0;
	*(unsigned char *)((char *)this + (b + 4) * 0x14) = 1;
}
void Rva0029ACA0::rva0029ACC7(int guard)
{
	if (guard != 0)
		return;
	for (int i = 0; i < 0x19; i++)
		rva0029ACA0(0, (unsigned int)i);
}
