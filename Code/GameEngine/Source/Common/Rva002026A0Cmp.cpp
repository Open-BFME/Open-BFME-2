// cl: /DNDEBUG /MD
//
// ?rva002026A0@Rva002026A0@@QBEHXZ @0x002026A0 20B. Compare ints at +0x17d8
// and +0x17f0 returning 0/1. Evidence: retail mov eax [ecx+0x17d8] plus xor
// edx edx plus cmp eax [ecx+0x17f0] plus setge dl plus mov eax edx plus ret;
// same 0x17xx object as 0x00202633 (+0x176c) and 0x00202790 (+0x1770); caller
// 0x00518F1D in 0x00518D2B.
class Rva002026A0
{
public:
	int rva002026A0() const;
	char m_pad[0x17f4];
};

int Rva002026A0::rva002026A0() const
{
	return *(int *)((char *)this + 0x17d8) >= *(int *)((char *)this + 0x17f0);
}
