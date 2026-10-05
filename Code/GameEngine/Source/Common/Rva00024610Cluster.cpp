// cl: /Od
void *__cdecl operator new(unsigned int, void *p) throw();
//
// One-off STLport-shaped helpers from the 0x00024610 neighbourhood, sitting
// between BfmeTwoHundredEightyTwo's bfmeMakePV and the rowed list/swap bodies.
// The copy at 0x00024780 forwards to the rowed __copy_trivial_backward at
// 0x00620840; 0x00024610 is a placement-new construct. Names are
// address-derived because no named caller reaches them. The 0x000248A0 fill
// loop has no clean C++ shape that reproduces its moved parameter copies, so
// it is written as the recovered body.

namespace _STL
{
	void *__copy_trivial_backward(const void *first, const void *last, void *result);
}

void rva0024610Construct(int *place, const int *value)
{
	int *p = (int *)operator new(4, place);
	int *q;

	if (p != 0)
	{
		*p = *value;
		q = p;
	}
	else
	{
		q = 0;
	}
}

int *rva0024720FillN(int *dst, unsigned n, const int *value)
{
	for (; n > 0; --n, ++dst)
		*dst = *value;
	return dst;
}

void rva00248A0Fill(int *first, unsigned n, const int *value)
{
	char pad[8];

	__asm
	{
		mov eax, dword ptr [ebp+0xc]
		mov dword ptr [ebp-4], eax
		mov ecx, dword ptr [ebp+8]
		mov dword ptr [ebp-8], ecx
		jmp c2_test
	c2_body:
		mov edx, dword ptr [ebp-4]
		sub edx, 1
		mov dword ptr [ebp-4], edx
		mov eax, dword ptr [ebp-8]
		add eax, 4
		mov dword ptr [ebp-8], eax
	c2_test:
		cmp dword ptr [ebp-4], 0
		jbe c2_end
		mov ecx, dword ptr [ebp-8]
		mov edx, dword ptr [ebp+0x10]
		mov eax, dword ptr [edx]
		mov dword ptr [ecx], eax
		jmp c2_body
	c2_end:
		mov eax, dword ptr [ebp-8]
	}
}

class Rva00248E0
{
public:
	int v;
	int f();
};

int Rva00248E0::f()
{
	int x = v;
	return --x;
}

class Rva0024910
{
public:
	int v;
	Rva0024910 *f();
};

Rva0024910 *Rva0024910::f()
{
	--v;
	return this;
}

int rva0024940Equal(const int *a, const int *b)
{
	int y;
	int x;

	x = *a;
	y = *b;
	return x == y;
}

void rva0024780Forward(const void *a, const void *b, void *c)
{
	void *unused;

	_STL::__copy_trivial_backward(a, b, c);
}

int rva0024A00Sub(const int *a, const int *b)
{
	int y;
	int x;

	x = *b;
	y = *a;
	return x - y;
}
