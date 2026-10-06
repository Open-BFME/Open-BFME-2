// cl: /O1 /MD
// ?Rva002E8C23Call@@YAHHEPAURva002E8C23Param@@@Z @0x002E8C23 42B: free cdecl wrapper passing through two ints plus fields from ptr+0/+0xC to pinned 0x002E79A8; evidence pin ?rva002E79A8@@YAXHEHHH@Z and callers in 0x002EE1C7/0x002F9DBA
void __cdecl rva002E79A8(int a1, unsigned char a2, int a3, int a4, int a5);

struct Rva002E8C23Pair
{
	int m00;
	int m04;
};

struct Rva002E8C23Param
{
	Rva002E8C23Pair *m00;
	char _04[8];
	unsigned int m0C;
};

int __cdecl Rva002E8C23Call(int a1, unsigned char a2, Rva002E8C23Param *a3)
{
	int bits = (a3->m0C >> 4) & 0x3F;
	rva002E79A8(a1, a2, a3->m00->m00, a3->m00->m04, bits);
	return a1;
}
