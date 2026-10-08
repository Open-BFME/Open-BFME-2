// cl: /O1 /DNDEBUG /MD
//
// ?rva002D9F9F@Rva002D9F9FOwner@@QAEXPAVRva002D9F9FArg@@@Z @0x002D9F9F 58B: guarded
// pair-call (thiscall, 1 arg, void). Returns when arg slot-3 predicate
// is true; else builds two-byte {1,6} in the dead arg slot, invokes arg
// slot-10 with it, then the pinned 0x002D9D7C on this with (arg, &pair).
// Arg/vtable views are minimal placeholders for slot resolution.
// Exact identities unproven.
// Two-byte {1,6} pair lives in the dead arg slot; see body.

class Xfer;
class AudioEventRTS
{
public:
 void internalXfer(Xfer *xfer, const void *version);
};

class Rva002D9F9FArg
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10(void *p);
};

class Rva002D9F9FOwner
{
public:
	void rva002D9F9F(Rva002D9F9FArg *a);
};

// ?rva002D9F9F@Rva002D9F9FOwner@@QAEXPAVRva002D9F9FArg@@@Z
void Rva002D9F9FOwner::rva002D9F9F(Rva002D9F9FArg *a)
{
	if (a->v03())
		return;
	// Pair occupies the dead arg slot at [ebp+8]; int filler forces placement.
	int t;
	((unsigned char *)&t)[0] = 1;
	((unsigned char *)&t)[1] = 6;
	a->v10(&t);
	((AudioEventRTS *)this)->internalXfer((Xfer *)a, &t);
}
