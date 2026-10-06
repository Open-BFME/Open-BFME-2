// cl: /DNDEBUG /MD /EHsc
// ?Create@AptInteger@@SAPAVAptValue@@H@Z @0x006D8520 263B. Pooled Apt Integer factory (type 7).
// H1: union + class-local sized new/delete, NO user dtor (same TU shape as landed bool).
// Fast path reuses free-list head g_00E18020 at +8 next slot, checks vtbl index 7 and
// refcount 0 via rowed getters with AptInteger.inl 0x4B/0x4D asserts, sets defined bit via
// rowed apply 0x006DBDB0, pushes to release vector 0x006E6C00, stores int at +8.
// Slow path is new AptInteger(value): allocBlock(0xC) via pool + base ctor 0x006DCCC0 type 7
// + derived vtable (0x00CEA4C0 via derived-ctor codegen) + int payload. Base is 8B
// (vptr@0 + flags@4); union payload at +8; sizeof 0xC. Throwing-new cleanup funclet is the
// sized-free shape (push 0xC + block, call class-scoped sized operator delete) resolved to
// rowed forwarder 0x006D8680 via ??3AptInteger@@SAXPAXI@Z pin (pattern of 9471/9472).
// No row at 0x006D8680 for this name, no naked/emit, no donor manual-flag/addPooled table.
// Evidence: seat-54-r15 packet (H1 recipe + pools/type audit), stash partials 5382/5388
// ($T618 wall removed by newDerived), string_xrefs AptInteger.inl->0x6d8520, pins
// 1024/1025/1371 (AptInteger::Create at this RVA), rowed base ctor 0x006DCCC0.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue;
class AptValueVector
{
public:
	void rva006E6C00(AptValue *pValue);
};
extern AptValueVector *g_releaseVectorAtE17710;
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006DB160
{
public:
	void *allocBlock(int blockSize);
};
class Rva006DBB30SarDwordField
{
public:
	int get() const;
};
class AptValue
{
public:
	unsigned int getRefCount() const;
};
class Rva006DBDB0DwordOrSetter
{
public:
	void apply();
};
class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};
class BfmeAptValue006DCD20
{
public:
	virtual void vtableSlot0();
	BfmeAptValue006DCD20(int type);
	unsigned int m_flags;
	virtual ~BfmeAptValue006DCD20();
};
class AptInteger : public BfmeAptValue006DCD20
{
public:
	union
	{
		AptInteger *m_next;
		int m_value;
	};
	AptInteger(int v) : BfmeAptValue006DCD20(7), m_value(v)
	{
	}
	static void *operator new(unsigned int s)
	{
		return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock((int)s);
	}
	static void operator delete(void *p, unsigned int s)
	{
		g_pChainBlockAllocator->freeBlock(p, (int)s);
	}
	static AptValue *Create(int value);
};
extern AptInteger *g_00E18020;
AptValue *AptInteger::Create(int value)
{
	AptInteger *pNewInt = g_00E18020;
	if (pNewInt != 0)
	{
		g_00E18020 = pNewInt->m_next;
		if (!(((const Rva006DBB30SarDwordField *)pNewInt)->get() == 7))
		{
			g_bfmeAptAssertAtE17734("pNewInt->getVtblIndex() == AptVFT_Integer", ".\\AptValue/AptInteger.inl", 0x4B);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		if (!(((const AptValue *)pNewInt)->getRefCount() == 0))
		{
			g_bfmeAptAssertAtE17734("pNewInt->getRefCount() == 0", ".\\AptValue/AptInteger.inl", 0x4D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((Rva006DBDB0DwordOrSetter *)pNewInt)->apply();
		g_releaseVectorAtE17710->rva006E6C00((AptValue *)pNewInt);
		pNewInt->m_value = value;
		return (AptValue *)pNewInt;
	}
	return (AptValue *)new AptInteger(value);
}
