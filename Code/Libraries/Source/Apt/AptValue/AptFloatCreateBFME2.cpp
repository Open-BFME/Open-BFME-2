// cl: /O2 /DNDEBUG /MD /EHsc
// ?Rva008A4EA0MakeFloat@@YAPAVAptValue@@M@Z @0x006D8700 263B. Pooled Apt Float factory (type 6).
// H1 twin of landed int/bool: union + class-local sized new/delete, NO user dtor.
// Fast path reuses free-list head g_00E18024 at +8 next slot, checks vtbl index 6 and
// refcount 0 via rowed getters with AptFloat.inl 0x4B/0x4D asserts, sets defined bit via
// rowed apply 0x006DBDB0, pushes to release vector 0x006E6C00, stores float at +8.
// Slow path is new AptFloat(value): allocBlock(0xC) via pool + base ctor 0x006DCCC0 type 6
// + derived vtable (0x00CEA560 via derived-ctor codegen) + float payload. Base is 8B
// (vptr@0 + flags@4); union payload at +8; sizeof 0xC. Throwing-new cleanup funclet is the
// sized-free shape (push 0xC + block, call class-scoped sized operator delete) resolved to
// rowed forwarder 0x006D8680 via ??3AptFloat@@SAXPAXI@Z pin (pattern of 9471/9472).
// Free-function factory name matches existing pin 5669 + BFME1 donor Rva008A4EA0MakeFloat
// (donor slow-path manual flags/addPooled table NOT copied: contradicts rowed 6DCCC0
// release-vector semantics; donor shape escalated as union + 12B alloc idiom only).
// No row at 0x006D8680 for this name, no naked/emit, no bool-vtable copy.
// Evidence: seat-54-r15/r16 packets, string_xrefs AptFloat.inl->0x6d8700,
// landed int twin ?Create@AptInteger@@SAPAVAptValue@@H@Z this round.
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
class AptFloat : public BfmeAptValue006DCD20
{
public:
	union
	{
		AptFloat *m_next;
		float m_value;
	};
	AptFloat(float v) : BfmeAptValue006DCD20(6), m_value(v)
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
};
extern AptFloat *g_00E18024;
AptValue *Rva008A4EA0MakeFloat(float value)
{
	AptFloat *pNewFloat = g_00E18024;
	if (pNewFloat != 0)
	{
		g_00E18024 = pNewFloat->m_next;
		if (!(((const Rva006DBB30SarDwordField *)pNewFloat)->get() == 6))
		{
			g_bfmeAptAssertAtE17734("pNewFloat->getVtblIndex() == AptVFT_Float", ".\\AptValue/AptFloat.inl", 0x4B);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		if (!(((const AptValue *)pNewFloat)->getRefCount() == 0))
		{
			g_bfmeAptAssertAtE17734("pNewFloat->getRefCount() == 0", ".\\AptValue/AptFloat.inl", 0x4D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((Rva006DBDB0DwordOrSetter *)pNewFloat)->apply();
		g_releaseVectorAtE17710->rva006E6C00((AptValue *)pNewFloat);
		pNewFloat->m_value = value;
		return (AptValue *)pNewFloat;
	}
	return (AptValue *)new AptFloat(value);
}
