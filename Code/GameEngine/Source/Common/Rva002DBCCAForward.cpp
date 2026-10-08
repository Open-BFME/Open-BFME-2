// cl: /O1 /DNDEBUG /MD
//
// ?rva002DBCCA@Rva002DBCCAOwner@@QAEXPAX@Z @0x002DBCCA 31B: virtual-slot
// forwarder (thiscall, void* arg, void). Retail calls the pinned 0x00053EE
// on the arg, then invokes vtable slot 12 of the arg with this+0x18. The
// arg class is carried as 12 pure-virtual fillers plus the slot-12 view so
// no dummy definitions are emitted. Honest address-derived names.

// The first call is the rowed Xfer::Version1 (0x000053EE).
class Xfer
{
public:
	void Version1();
};

class Rva002DBCCAArg
{
public:
	void rva000053EE();
	virtual void vf00() = 0;
	virtual void vf01() = 0;
	virtual void vf02() = 0;
	virtual void vf03() = 0;
	virtual void vf04() = 0;
	virtual void vf05() = 0;
	virtual void vf06() = 0;
	virtual void vf07() = 0;
	virtual void vf08() = 0;
	virtual void vf09() = 0;
	virtual void vf10() = 0;
	virtual void vf11() = 0;
	virtual void vf12(void *x);
};

class Rva002DBCCAOwner
{
public:
	void rva002DBCCA(void *a);
};

// ?rva002DBCCA@Rva002DBCCAOwner@@QAEXPAX@Z
void Rva002DBCCAOwner::rva002DBCCA(void *a)
{
	((Xfer *)a)->Version1();
	((Rva002DBCCAArg *)a)->vf12((char *)this + 0x18);
}
