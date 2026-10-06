// cl: /Oy-
// Family-4 split-range processors (68B each): each function processes the
// pointer range [a, b) with the element helper when the aligned span is 64
// bytes or less, else it runs the head helper over the first 64 bytes and
// the tail helper over the rest, returning the tail/head result. The b and c
// parameters are volatile-qualified: that is what keeps the compiler pushing
// them from memory instead of staging them in preserved registers. Helpers
// are opaque address-named pins; range, helper and function identities are
// unproven.
int Copy0021D289(void *a, void * volatile b, volatile int c);
int Copy0021D2B6(void *a, void * volatile b, volatile int c);
int Copy002B833C(void *a, void * volatile b, volatile int c);
int Copy002B6351(void *a, void * volatile b, volatile int c);
int Copy003C6437(void *a, void * volatile b, volatile int c);
int Copy003C3AB0(void *a, void * volatile b, volatile int c);

int Proc0021D905(void *a, void * volatile b, volatile int c)
{
	if ((((char *)b - (char *)a) & ~3) > 0x40)
	{
		Copy0021D289(a, (char *)a + 0x40, c);
		return Copy0021D2B6((char *)a + 0x40, b, c);
	}
	return Copy0021D289(a, b, c);
}

int Proc002B9177(void *a, void * volatile b, volatile int c)
{
	if ((((char *)b - (char *)a) & ~3) > 0x40)
	{
		Copy002B833C(a, (char *)a + 0x40, c);
		return Copy002B6351((char *)a + 0x40, b, c);
	}
	return Copy002B833C(a, b, c);
}

int Proc003C6973(void *a, void * volatile b, volatile int c)
{
	if ((((char *)b - (char *)a) & ~3) > 0x40)
	{
		Copy003C6437(a, (char *)a + 0x40, c);
		return Copy003C3AB0((char *)a + 0x40, b, c);
	}
	return Copy003C6437(a, b, c);
}
