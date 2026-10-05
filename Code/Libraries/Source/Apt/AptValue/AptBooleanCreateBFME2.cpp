// cl: /O2 /DNDEBUG /MD /EHsc
// ?Create@AptBoolean@@SAPAVAptValue@@_N@Z @0x006D88C0 263B. Pooled Apt Boolean factory (type 5).
// H1-B1: union + class-local sized new/delete, NO user dtor (same TU shape as int/float).
// Fast path reuses free-list head g_00E18028 at +8 next slot, checks vtbl index 5 and
// refcount 0 via rowed getters with AptBoolean.inl 0x4B/0x4D asserts, sets defined bit via
// rowed apply 0x006DBDB0, pushes to release vector 0x006E6C00, stores bool at +8.
// Slow path is new AptBoolean(value): allocBlock(0xC) via pool + base ctor 0x006DCCC0 type 5
// + derived vtable + bool payload. Base is 8B (vptr@0 + flags@4); union payload at +8;
// sizeof 0xC. Complete-dtor decl-only (never defined here); destroy funclet via existing
// pins 9469/9470 thunk-walks to rowed 51B provider 0x006DE350. No row at 0x006D6340,
// no naked/emit, no donor manual-flag/addPooled table. Evidence: seat-54-r15 packet,
// stash partials 5382-5384 ($T618 wall), rowed base ctor 0x006DCCC0 + forwarder 0x006D8680.
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
class AptBoolean : public BfmeAptValue006DCD20
{
public:
	union
	{
		AptBoolean *m_next;
		bool m_value;
	};
	AptBoolean(bool v) : BfmeAptValue006DCD20(5), m_value(v)
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
	static AptValue *Create(bool value);
};
extern AptBoolean *g_00E18028;
AptValue *AptBoolean::Create(bool value)
{
	AptBoolean *pNewBool = g_00E18028;
	if (pNewBool != 0)
	{
		g_00E18028 = pNewBool->m_next;
		if (!(((const Rva006DBB30SarDwordField *)pNewBool)->get() == 5))
		{
			g_bfmeAptAssertAtE17734("pNewBool->getVtblIndex() == AptVFT_Boolean", ".\\AptValue/AptBoolean.inl", 0x4B);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		if (!(((const AptValue *)pNewBool)->getRefCount() == 0))
		{
			g_bfmeAptAssertAtE17734("pNewBool->getRefCount() == 0", ".\\AptValue/AptBoolean.inl", 0x4D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((Rva006DBDB0DwordOrSetter *)pNewBool)->apply();
		g_releaseVectorAtE17710->rva006E6C00((AptValue *)pNewBool);
		pNewBool->m_value = value;
		return (AptValue *)pNewBool;
	}
	return (AptValue *)new AptBoolean(value);
}
