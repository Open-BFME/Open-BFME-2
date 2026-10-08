// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Target evidence: the two 32-bit thiscall workers consume an int carrying
// the argument-object pointer. Both test masks through 0x003EDE16 and
// 0x003EDE2A, inspect byte +0xE5, and walk the pointer range at +0x1C/+0x20.
// 0x003EDFD8 also calls the argument's +0x24/+0x28 vtable slots and compares
// the latter result with the word at g_00DFE1A8+0x3C. Their callback calls
// resolve to 0x005697F7 and 0x00569863. The target extent is the Ghidra span
// at each start (111 and 128 bytes); the next body begins at 0x003EE058.
// 0x003EDE44 (293 bytes, ret 4; the 0x0020D8F1 range loop's callee) runs the
// same test twice, on the +0x0C/+0x14 and the +0x08/+0x10 slots, clears either
// result through the +0x20/+0x24 flags when +0xE5 is set, and picks one
// pointer-to-member callback: 0x00569863 on entry, 0x005697F7 on exit and
// 0x00569628 when the x/y pairs from slots +0x00/+0x04 differ. Those pairs
// come back through hidden pointers and are compared with SSE ucomiss, hence
// /arch:SSE (the two smaller workers match either way).
// Structural inference: the argument vtable slot types and callback owners
// below capture only the observed ABI and dispatch shape. They do not name
// the underlying game classes.

struct Rva003EDE16
{
	bool rva003EDE16(const void *other) const;
private:
	unsigned char m_pad[0x28];
	unsigned int m_req[19];
	unsigned int m_ban[19];
};

struct Rva003EDE2A
{
	bool rva003EDE2A(const void *other) const;
private:
	unsigned char m_pad[0xC0];
	unsigned int m_req[4];
	unsigned int m_ban[4];
};

struct Rva0020DXXXElem
{
	void rva003EDC31();
	void rva003EDC16();
	void rva003EDE44(int x);
	void rva003EDF69(int x);
	void rva003EDFD8(int x);
};

// An 8-byte x/y pair returned through a hidden pointer (so not a POD in
// retail's source), compared field by field.
struct Rva004ABA81Pair
{
	Rva004ABA81Pair() {}
	__forceinline bool isExactlyEqualTo(const Rva004ABA81Pair &in) const { return x == in.x && y == in.y; }
	float x;
	float y;
};

struct Rva0020DXXXArg
{
	virtual Rva004ABA81Pair get00() = 0;
	virtual Rva004ABA81Pair get04() = 0;
	virtual void *get08() = 0;
	virtual const void *get0C() = 0;
	virtual void *get10() = 0;
	virtual const void *get14() = 0;
	virtual void *get18() = 0;
	virtual void *get1C() = 0;
	virtual bool get20() = 0;
	virtual bool get24() = 0;
	virtual int get28() = 0;
};

struct Rva005697F7
{
	void rva005697F7(void *arg);
};

struct Rva00569863
{
	void rva00569863(void *arg);
};

struct Rva00569628
{
	void rva00569628(void *arg);
};

// The callbacks share one pointer-to-member type; each pair class above is
// the address-derived owner of one of them.
typedef void (Rva00569863::*Rva003EDE44Callback)(void *arg);

class Rva0020D959Host;
extern Rva0020D959Host *g_00DFE1A8;

struct Rva00DFE1A8ClockView
{
	unsigned char m_pad[0x3C];
	int m_3C;
};

void Rva0020DXXXElem::rva003EDE44(int x)
{
	Rva0020DXXXArg *arg = (Rva0020DXXXArg *)x;
	bool wasIn;
	if (((Rva003EDE16 *)this)->rva003EDE16(arg->get0C())
		&& ((Rva003EDE2A *)this)->rva003EDE2A(arg->get14()))
		wasIn = true;
	else
		wasIn = false;
	bool nowIn;
	if (((Rva003EDE16 *)this)->rva003EDE16(arg->get08())
		&& ((Rva003EDE2A *)this)->rva003EDE2A(arg->get10()))
		nowIn = true;
	else
		nowIn = false;
	if (*(unsigned char *)((char *)this + 0xE5) != 0)
	{
		if (arg->get20())
			wasIn = false;
		if (arg->get24())
			nowIn = false;
	}
	int frame = arg->get28();
	if (frame <= ((Rva00DFE1A8ClockView *)g_00DFE1A8)->m_3C)
		nowIn = false;

	Rva003EDE44Callback callback;
	if (wasIn)
	{
		if (nowIn)
		{
			if (arg->get04().isExactlyEqualTo(arg->get00()))
				return;
			else
				callback = reinterpret_cast<Rva003EDE44Callback>(&Rva00569628::rva00569628);
		}
		else
			callback = reinterpret_cast<Rva003EDE44Callback>(&Rva005697F7::rva005697F7);
	}
	else
		callback = nowIn ? &Rva00569863::rva00569863 : 0;

	if (callback)
	{
		for (void **i = *(void ***)((char *)this + 0x1C);
			i != *(void ***)((char *)this + 0x20); ++i)
			(((Rva00569863 *)*i)->*callback)(arg);
	}
}

void Rva0020DXXXElem::rva003EDF69(int x)
{
	Rva0020DXXXArg *arg = (Rva0020DXXXArg *)x;
	bool run;
	if (((Rva003EDE16 *)this)->rva003EDE16(arg->get0C())
		&& ((Rva003EDE2A *)this)->rva003EDE2A(arg->get14()))
		run = true;
	else
		run = false;
	if (*(unsigned char *)((char *)this + 0xE5) != 0 && arg->get20())
		run = false;
	if (run)
	{
		for (void **i = *(void ***)((char *)this + 0x1C);
			i != *(void ***)((char *)this + 0x20); ++i)
			((Rva005697F7 *)*i)->rva005697F7(arg);
	}
}

void Rva0020DXXXElem::rva003EDFD8(int x)
{
	Rva0020DXXXArg *arg = (Rva0020DXXXArg *)x;
	bool run;
	if (((Rva003EDE16 *)this)->rva003EDE16(arg->get08())
		&& ((Rva003EDE2A *)this)->rva003EDE2A(arg->get10()))
		run = true;
	else
		run = false;
	if (*(unsigned char *)((char *)this + 0xE5) != 0 && arg->get24())
		run = false;
	int frame = arg->get28();
	if (frame <= ((Rva00DFE1A8ClockView *)g_00DFE1A8)->m_3C)
		run = false;
	if (run)
	{
		for (void **i = *(void ***)((char *)this + 0x1C);
			i != *(void ***)((char *)this + 0x20); ++i)
			((Rva00569863 *)*i)->rva00569863(arg);
	}
}
