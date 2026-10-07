// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Target facts: retail 0x004640BE is a 98-byte boundary. It clears this+0x68,
// calls virtual slot 17 through this-0x10, decrements the count at this+0x60
// only when nonzero, and on transition to zero updates condition bits in the
// Object pointer at this-8 before calling the rowed notifier 0x0028AE6D. It
// conditionally calls rowed map prune 0x00463A81 when this+0x50 is nonzero,
// then calls 0x0046391B on the same this-0x10 view and returns 1.
//
// Structural inference: the -0x10 receiver view is shared with the rowed
// Rva00463A81 prune method. The helper pin at 0x0046391B records only the
// direct zero-argument thiscall ABI observed here; its body remains deferred.
// Field names, owning class, and virtual-slot semantics remain address-derived.

class Object
{
public:
	void rva0028AE6D();
};

class Rva00463A81
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;

	void rva00463A81();
	void rva0046391B();
};

class Rva004640BE
{
public:
	int rva004640BE();
};

int Rva004640BE::rva004640BE()
{
	char *self = (char *)this;
	*(unsigned int *)(self + 0x68) = 0;
	Rva00463A81 *base = (Rva00463A81 *)(self - 0x10);
	base->slot17();

	unsigned int count = *(unsigned int *)(self + 0x60);
	if (count != 0)
	{
		--count;
		*(unsigned int *)(self + 0x60) = count;
		if (count == 0)
		{
			Object *object = *(Object **)(self - 8);
			unsigned int *conditionWords =
				(unsigned int *)((char *)object + 0x10C);
			unsigned int flags = *conditionWords;
			const unsigned int setMask = 0x400000;
			if ((flags & 0x200000) != 0 || (flags & setMask) == 0)
			{
				((unsigned char *)conditionWords)[2] &= 0xDF;
				*conditionWords |= setMask;
				object->rva0028AE6D();
			}
		}
	}

	if (*(void **)(self + 0x50) != 0)
		base->rva00463A81();
	base->rva0046391B();
	return 1;
}
